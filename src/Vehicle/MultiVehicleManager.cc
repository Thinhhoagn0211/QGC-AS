/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "MultiVehicleManager.h"
#include "MAVLinkProtocol.h"
#include "QGCApplication.h"
#include "ParameterManager.h"
#include "SettingsManager.h"
#include "MavlinkSettings.h"
#include "FirmwareUpgradeSettings.h"
#include "QGCCorePlugin.h"
#include "QGCOptions.h"
#include "LinkManager.h"
#include "Vehicle.h"
#include "VehicleLinkManager.h"
#include "Autotune.h"
#include "LinkInterface.h"
#include "RemoteIDManager.h"
#include "VehicleObjectAvoidance.h"
#include "TrajectoryPoints.h"
#include "QmlObjectListModel.h"
#ifdef Q_OS_IOS
#include "MobileScreenMgr.h"
#elif defined(Q_OS_ANDROID)
#include "AndroidInterface.h"
#endif
#include "QGCLoggingCategory.h"

#include <QtCore/qapplicationstatic.h>
#include <QtCore/QTimer>
#include <QtQml/QQmlEngine>

QGC_LOGGING_CATEGORY(MultiVehicleManagerLog, "qgc.vehicle.multivehiclemanager")

Q_APPLICATION_STATIC(MultiVehicleManager, _multiVehicleManagerInstance);

MultiVehicleManager::MultiVehicleManager(QObject *parent)
    : QObject(parent)
    , _gcsHeartbeatTimer(new QTimer(this))
    , _vehicles(new QmlObjectListModel(this))
    , _selectedVehicles(new QmlObjectListModel(this))
{
    // qCDebug(MultiVehicleManagerLog) << Q_FUNC_INFO << this;
}

MultiVehicleManager::~MultiVehicleManager()
{
    // qCDebug(MultiVehicleManagerLog) << Q_FUNC_INFO << this;
}

MultiVehicleManager *MultiVehicleManager::instance()
{
    return _multiVehicleManagerInstance();
}

void MultiVehicleManager::registerQmlTypes()
{
    (void) qmlRegisterUncreatableType<MultiVehicleManager>      ("QGroundControl.MultiVehicleManager",  1, 0, "MultiVehicleManager",    "Reference only");
    (void) qmlRegisterUncreatableType<Vehicle>                  ("QGroundControl.Vehicle",              1, 0, "Vehicle",                "Reference only");
    (void) qmlRegisterUncreatableType<VehicleLinkManager>       ("QGroundControl.Vehicle",              1, 0, "VehicleLinkManager",     "Reference only");
    (void) qmlRegisterUncreatableType<Autotune>                 ("QGroundControl.Vehicle",              1, 0, "Autotune",               "Reference only");
    (void) qmlRegisterUncreatableType<RemoteIDManager>          ("QGroundControl.Vehicle",              1, 0, "RemoteIDManager",        "Reference only");
    (void) qmlRegisterUncreatableType<TrajectoryPoints>         ("QGroundControl.FlightMap",            1, 0, "TrajectoryPoints",       "Reference only");
    (void) qmlRegisterUncreatableType<VehicleObjectAvoidance>   ("QGroundControl.Vehicle",              1, 0, "VehicleObjectAvoidance", "Reference only");
    (void) qRegisterMetaType<Vehicle::MavCmdResultFailureCode_t>("MavCmdResultFailureCode_t");
}

void MultiVehicleManager::init()
{
    if (_initialized) {
        return;
    }

    _offlineEditingVehicle = new Vehicle(Vehicle::MAV_AUTOPILOT_TRACK, Vehicle::MAV_TYPE_TRACK, this);
    // wait heartbeat info to be received before sending GCS heartbeat
    (void) connect(MAVLinkProtocol::instance(), &MAVLinkProtocol::vehicleHeartbeatInfo, this, &MultiVehicleManager::_vehicleHeartbeatInfo);

    _gcsHeartbeatTimer->setInterval(kGCSHeartbeatRateMSecs);
    _gcsHeartbeatTimer->setSingleShot(false);
    (void) connect(_gcsHeartbeatTimer, &QTimer::timeout, this, &MultiVehicleManager::_sendGCSHeartbeat);
    _gcsHeartbeatTimer->start();

    _initialized = true;
}

void MultiVehicleManager::_vehicleHeartbeatInfo(LinkInterface* link, int vehicleId, int componentId, int vehicleFirmwareType, int vehicleType)
{
    if (componentId != MAV_COMP_ID_AUTOPILOT1) {
        // Don't create vehicles for components other than the autopilot
        qCDebug(MultiVehicleManagerLog) << "Ignoring heartbeat from unknown component port:vehicleId:componentId:fwType:vehicleType"
                                        << link->linkConfiguration()->name()
                                        << vehicleId
                                        << componentId
                                        << vehicleFirmwareType
                                        << vehicleType;
        return;
    }

#ifndef QGC_NO_ARDUPILOT_DIALECT
    // When you flash a new ArduCopter it does not set a FRAME_CLASS for some reason. This is the only ArduPilot variant which
    // works this way. Because of this the vehicle type is not known at first connection. In order to make QGC work reasonably
    // we assume ArduCopter for this case.
    if ((vehicleType == MAV_TYPE_GENERIC) && (vehicleFirmwareType == MAV_AUTOPILOT_ARDUPILOTMEGA)) {
        vehicleType = MAV_TYPE_QUADROTOR;
    }
#endif

    switch (vehicleType) {
    case MAV_TYPE_GCS:
    case MAV_TYPE_ONBOARD_CONTROLLER:
    case MAV_TYPE_GIMBAL:
    case MAV_TYPE_ADSB:
        // These are not vehicles, so don't create a vehicle for them
        return;
    default:
        break;
    }
    // if number of vehicles is greater than 0 and multi vehicle mode is not enabled, do not add new vehicle
    if ((_vehicles->count() > 0) && !QGCCorePlugin::instance()->options()->multiVehicleEnabled()) {
        return;
    }
    
    // If the vehicle is already in the list, do not add it again
    if (_ignoreVehicleIds.contains(vehicleId) || getVehicleById(vehicleId) || (vehicleId == 0)) {
        return;
    }

    qCDebug(MultiVehicleManagerLog) << "Adding new vehicle link:vehicleId:componentId:vehicleFirmwareType:vehicleType "
                                    << link->linkConfiguration()->name()
                                    << vehicleId
                                    << componentId
                                    << vehicleFirmwareType
                                    << vehicleType;

    // If the vehicle is using the same system id as QGC, show a warning message
    if (vehicleId == MAVLinkProtocol::instance()->getSystemId()) {
        qgcApp()->showAppMessage(tr("Warning: A vehicle is using the same system id as %1: %2").arg(QCoreApplication::applicationName()).arg(vehicleId));
    }

    // create a new vehicle instance
    Vehicle *const vehicle = new Vehicle(link, vehicleId, componentId, (MAV_AUTOPILOT)vehicleFirmwareType, (MAV_TYPE)vehicleType, this);
    
    // Trigger if QGC sends request for protocol version, it will request device to send its protocol version
    (void) connect(vehicle, &Vehicle::requestProtocolVersion, this, &MultiVehicleManager::_requestProtocolVersion);
    // Trigger if QGC check if all links are removed, it will delete the vehicles
    (void) connect(vehicle->vehicleLinkManager(), &VehicleLinkManager::allLinksRemoved, this, &MultiVehicleManager::_deleteVehiclePhase1);
    // Trigger if QGC check if vehicle parameters are ready, it will update the parameter ready vehicle available state
    (void) connect(vehicle->parameterManager(), &ParameterManager::parametersReadyChanged, this, &MultiVehicleManager::_vehicleParametersReadyChanged);
    // append the vehicle to the vehicles list
    _vehicles->append(vehicle);

    // Send QGC heartbeat ASAP, this allows PX4 to start accepting commands
    _sendGCSHeartbeat();

    SettingsManager::instance()->firmwareUpgradeSettings()->defaultFirmwareType()->setRawValue(vehicleFirmwareType);

    // emit signals to notify about the new vehicle
    emit vehicleAdded(vehicle);

    if (_vehicles->count() > 1) {
        qgcApp()->showAppMessage(tr("Connected to Vehicle %1").arg(vehicleId));
    } else {
        // This is the first vehicle, so set it as the active vehicle
        setActiveVehicle(vehicle);
    }

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    if (_vehicles->count() == 1) {
        qCDebug(MultiVehicleManagerLog) << "keepScreenOn";
        #if defined(Q_OS_ANDROID)
            AndroidInterface::setKeepScreenOn(true);
        #elif defined(Q_OS_IOS)
            MobileScreenMgr::setKeepScreenOn(true);
        #endif
    }
#endif
}

void MultiVehicleManager::_requestProtocolVersion(unsigned version) const
{
    // check if len of vehicles is 0, if so, set the version of MAVLINK to the requested version
    if (_vehicles->count() == 0) {
        MAVLinkProtocol::instance()->setVersion(version);
        return;
    }

    // loop through all vehicles and find the maximum protocol version of MAVLink
    unsigned maxversion = 0;
    for (int i = 0; i < _vehicles->count(); i++) {
        const Vehicle *const vehicle = qobject_cast<const Vehicle*>(_vehicles->get(i));
        if (vehicle && (vehicle->maxProtoVersion() > maxversion)) {
            maxversion = vehicle->maxProtoVersion();
        }
    }

    // if the maximum version is less than the requested version, set the version to the maximum version
    if (MAVLinkProtocol::instance()->getCurrentVersion() != maxversion) {
        MAVLinkProtocol::instance()->setVersion(maxversion);
    }
}

void MultiVehicleManager::_deleteVehiclePhase1(Vehicle *vehicle)
{
    qCDebug(MultiVehicleManagerLog) << Q_FUNC_INFO << vehicle;
    // loop through the vehicles list and remove the vehicle from list
    bool found = false;
    for (int i = 0; i < _vehicles->count(); i++) {
        if (_vehicles->get(i) == vehicle) {
            (void) _vehicles->removeAt(i);
            found = true;
            break;
        }
    }

    if (!found) {
        qCWarning(MultiVehicleManagerLog) << "Vehicle not found in map!";
    }

    deselectVehicle(vehicle->id());
    // If the vehicle being removed is the active vehicle, we need to clear it
    _setActiveVehicleAvailable(false);
    // set parameter ready vehicle available to false
    _setParameterReadyVehicleAvailable(false);
    // Emit the vehicleRemoved signal to notify Qml and other listeners
    emit vehicleRemoved(vehicle);
    // Prepare the vehicle for deletion
    vehicle->prepareDelete();

#if defined(Q_OS_ANDROID) || defined (Q_OS_IOS)
    if (_vehicles->count() == 0) {
        qCDebug(MultiVehicleManagerLog) << "restoreScreenOn";
        #if defined(Q_OS_ANDROID)
            AndroidInterface::setKeepScreenOn(false);
        #elif defined(Q_OS_IOS)
            MobileScreenMgr::setKeepScreenOn(false);
        #endif
    }
#endif

    // We must let the above signals flow through the system as well as get back to the main loop event queue
    // before we can actually delete the Vehicle. The reason is that Qml may be holding on to references to it.
    // Even though the above signals should unload any Qml which has references, that Qml will not be destroyed
    // until we get back to the main loop. So we set a short timer which will then fire after Qt has finished
    // doing all of its internal nastiness to clean up the Qml. This works for both the normal running case
    // as well as the unit testing case which of course has a different signal flow!
    QTimer::singleShot(20, this, [this, vehicle]() {
        _deleteVehiclePhase2(vehicle);
    });
}

void MultiVehicleManager::_deleteVehiclePhase2(Vehicle *vehicle)
{
    qCDebug(MultiVehicleManagerLog) << Q_FUNC_INFO << vehicle;

    /// Qml has been notified of vehicle about to go away and should be disconnected from it by now.
    /// This means we can now clear the active vehicle property and delete the Vehicle for real.

    Vehicle *newActiveVehicle = nullptr;
    if (_vehicles->count() > 0) {
        newActiveVehicle = qobject_cast<Vehicle*>(_vehicles->get(0));
    }

    _setActiveVehicle(newActiveVehicle);

    if (_activeVehicle) {
        _setActiveVehicleAvailable(true);
        if (_activeVehicle->parameterManager()->parametersReady()) {
            _setParameterReadyVehicleAvailable(true);
        }
    }

    vehicle->deleteLater();
}

void MultiVehicleManager::setActiveVehicle(Vehicle *vehicle)
{
    qCDebug(MultiVehicleManagerLog) << Q_FUNC_INFO << vehicle;
    // if vehicle is not active, set it as active vehicle
    if (vehicle != _activeVehicle) {
        if (_activeVehicle) {
            // The sequence of signals is very important in order to not leave Qml elements connected
            // to a non-existent vehicle.

            // First we must signal that there is no active vehicle available. This will disconnect
            // any existing ui from the currently active vehicle.
            _setActiveVehicleAvailable(false);
            _setParameterReadyVehicleAvailable(false);
        }
        QTimer::singleShot(20, this, [this, vehicle]() {
            _setActiveVehiclePhase2(vehicle);
        });
    }
}

void MultiVehicleManager::_setActiveVehiclePhase2(Vehicle *vehicle)
{
    qCDebug(MultiVehicleManagerLog) << Q_FUNC_INFO << vehicle;
    // pick current vehicle as active vehicle
    _setActiveVehicle(vehicle);
    // check if _activeVehicle is not null
    if (_activeVehicle) {
        _setActiveVehicleAvailable(true);
        // If the active vehicle has parameters ready, set the parameter ready vehicle available to true
        if (_activeVehicle->parameterManager()->parametersReady()) {
            _setParameterReadyVehicleAvailable(true);
        }
    }
}

void MultiVehicleManager::_vehicleParametersReadyChanged(bool parametersReady)
{
    // get signal from sender, and convert it to ParameterManager type
    ParameterManager *const paramMgr = qobject_cast<ParameterManager*>(sender());
    // if the sender is not a ParameterManager, return
    if (!paramMgr) {
        return;
    }   
    // if the parameter manager is not for the active vehicle, do not set the parameter ready vehicle available
    if (paramMgr->vehicle() == _activeVehicle) {
        _setParameterReadyVehicleAvailable(parametersReady);
    }
}

void MultiVehicleManager::_sendGCSHeartbeat()
{
    if (!SettingsManager::instance()->mavlinkSettings()->sendGCSHeartbeat()->rawValue().toBool()) {
        return;
    }

    const QList<SharedLinkInterfacePtr> sharedLinks = LinkManager::instance()->links();
    for (const SharedLinkInterfacePtr link: sharedLinks) {
        if (!link->isConnected()) {
            continue;
        }

        const SharedLinkConfigurationPtr linkConfiguration = link->linkConfiguration();
        if (linkConfiguration->isHighLatency()) {
            continue;
        }

        mavlink_message_t message{};
        (void) mavlink_msg_heartbeat_pack_chan(
            MAVLinkProtocol::instance()->getSystemId(),
            MAVLinkProtocol::instance()->getComponentId(),
            link->mavlinkChannel(),
            &message,
            MAV_TYPE_GCS,
            MAV_AUTOPILOT_INVALID,
            MAV_MODE_MANUAL_ARMED,
            0,
            MAV_STATE_ACTIVE
        );

        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        const uint16_t len = mavlink_msg_to_send_buffer(buffer, &message);
        (void) link->writeBytesThreadSafe(reinterpret_cast<const char*>(buffer), len);
    }
}

void MultiVehicleManager::selectVehicle(int vehicleId)
{
    // Check if the vehicle is already selected
    if(!_vehicleSelected(vehicleId)) {
        // If the vehicle is not selected, check if it exists
        Vehicle *const vehicle = getVehicleById(vehicleId);
        _selectedVehicles->append(vehicle);
        return;
    }
}

void MultiVehicleManager::deselectVehicle(int vehicleId)
{
    // Check if the vehicle is selected, if so, remove it from the selected vehicles list
    for (int i = 0; i < _selectedVehicles->count(); i++) {
        Vehicle *const vehicle = qobject_cast<Vehicle*>(_selectedVehicles->get(i));
        if (vehicle->id() == vehicleId) {
            _selectedVehicles->removeAt(i);
            return;
        }
    }
}

void MultiVehicleManager::deselectAllVehicles()
{
    // Clear the selected vehicles list
    _selectedVehicles->clear();
}

bool MultiVehicleManager::_vehicleSelected(int vehicleId)
{
    // Check if the vehicle is selected, if so, return true, otherwise return false
    for (int i = 0; i < _selectedVehicles->count(); i++) {
        Vehicle *const vehicle = qobject_cast<Vehicle*>(_selectedVehicles->get(i));
        if (vehicle->id() == vehicleId) {
            return true;
        }
    }
    return false;
}

Vehicle *MultiVehicleManager::getVehicleById(int vehicleId) const
{
    // get vehicle by id
    for (int i = 0; i < _vehicles->count(); i++) {
        Vehicle *const vehicle = qobject_cast<Vehicle*>(_vehicles->get(i));
        if (vehicle->id() == vehicleId) {
            return vehicle;
        }
    }

    return nullptr;
}

void MultiVehicleManager::_setActiveVehicle(Vehicle *vehicle)
{
    // set the active vehicle to the given vehicle
    if (vehicle != _activeVehicle) {
        _activeVehicle = vehicle;
        emit activeVehicleChanged(vehicle);
    }
}

void MultiVehicleManager::_setActiveVehicleAvailable(bool activeVehicleAvailable)
{
    if (activeVehicleAvailable != _activeVehicleAvailable) {
        _activeVehicleAvailable = activeVehicleAvailable;
        emit activeVehicleAvailableChanged(activeVehicleAvailable);
    }
}

void MultiVehicleManager::_setParameterReadyVehicleAvailable(bool parametersReady)
{
    if (parametersReady != _parameterReadyVehicleAvailable) {
        _parameterReadyVehicleAvailable = parametersReady;
        parameterReadyVehicleAvailableChanged(parametersReady);
    }
}
