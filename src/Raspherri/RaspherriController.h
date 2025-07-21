#pragma once

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QtNetwork/QUdpSocket>
#include "MAVLinkLib.h"
#include "Gimbal.h"

Q_DECLARE_LOGGING_CATEGORY(RaspherriControllerLog)

class QmlObjectListModel;
class Vehicle;

class RaspherriController : public QObject 
{
    Q_OBJECT
    Q_MOC_INCLUDE("QmlObjectListModel.h")
    Q_PROPERTY(Gimbal *activeGimbal READ activeGimbal WRITE setActiveGimbal NOTIFY activeGimbalChanged)
    Q_PROPERTY(QString targetIp READ targetIp WRITE setTargetIp NOTIFY targetIpChanged)
    Q_PROPERTY(int targetPort READ targetPort WRITE setTargetPort NOTIFY targetPortChanged)
    Q_PROPERTY(qreal                zoomLevel               READ zoomLevel              WRITE  setZoomLevel         NOTIFY zoomLevelChanged)

public:
    RaspherriController(Vehicle *vehicle);
    ~RaspherriController() override;

    QString targetIp() const { return _targetIp; }
    void setTargetIp(const QString &ip);
    int targetPort() const { return _targetPort; }
    void setTargetPort(int port);
    
    Gimbal *activeGimbal() const { return _activeGimbal; }
    QmlObjectListModel *gimbals() const { return _gimbals; }
    
    void setActiveGimbal(Gimbal *gimbal);
    qreal zoomLevel() const { return _zoomLevel; }
    void setZoomLevel(qreal level);

    void sendPitchYawFlags(uint32_t flags);
    Q_INVOKABLE void gimbalOnScreenControl(float panpct, float tiltpct, bool clickAndPoint, bool clickAndDrag, bool rateControl, bool retract = false, bool neutral = false, bool yawlock = false);
    Q_INVOKABLE void sendPitchBodyYaw(float pitch, float yaw, bool showError = true);
    Q_INVOKABLE void sendPitchAbsoluteYaw(float pitch, float yaw, bool showError = true);
    Q_INVOKABLE void toggleGimbalRetracted(bool set = false);
    Q_INVOKABLE void toggleGimbalYawLock(bool set = false);
    Q_INVOKABLE void acquireGimbalControl();
    Q_INVOKABLE void releaseGimbalControl();
    Q_INVOKABLE void sendRate();
    Q_INVOKABLE void sendCommandLong(
        int command,
        float param1 = 0, float param2 = 0, float param3 = 0,
        float param4 = 0, float param5 = 0, float param6 = 0, float param7 = 0,
        int targetSystem = 1, int targetComponent = 1);

public slots:
    void gimbalYawLock(bool yawLock) { toggleGimbalYawLock(yawLock); }
    Q_INVOKABLE void centerGimbal();
    void gimbalPitchStart(int direction);
    void gimbalYawStart(int direction);
    void gimbalPitchStop();
    void gimbalYawStop();

signals:
    void targetIpChanged();
    void targetPortChanged();
    void zoomLevelChanged();
    void activeGimbalChanged();
    void showAcquireGimbalControlPopup(); // This triggers a popup in QML asking the user for aproval to take control

private slots:
    void _mavlinkMessageReceived(const mavlink_message_t &message);
    void _rateSenderTimeout();
private:
    struct GimbalPairId {
        GimbalPairId() = default;
        GimbalPairId(uint8_t _managerCompid, uint8_t _deviceId)
            : managerCompid(_managerCompid)
            , deviceId(_deviceId) {}

        // In order to use this as a key, we need to implement <,
        bool operator<(const GimbalPairId &other) const {
            // We compare managerCompid primarily, if they are equal, we compare the deviceId
            if (managerCompid < other.managerCompid) {
                return true;
            } else if (managerCompid > other.managerCompid) {
                return false;
            } else if (deviceId < other.deviceId) {
                return true;
            } else {
                return false;
            }
        }

        bool operator==(const GimbalPairId &other) const {
            return (managerCompid == other.managerCompid) && (deviceId == other.deviceId);
        }

        uint8_t managerCompid = 0;
        uint8_t deviceId = 0;
    };
    QTimer _rateSenderTimer;
    void _initSocket();
    QUdpSocket *_udpSocket = nullptr;
    QString _targetIp = "192.168.1.29";
    int _targetPort = 14550;
    uint8_t _sysId = 255;
    uint8_t _compId = 190;
    qreal _zoomLevel = 0.0;
    void _requestGimbalInformation(uint8_t compid);
    void _handleHeartbeat(const mavlink_message_t &message);
    void _handleGimbalManagerInformation(const mavlink_message_t &message);
    void _handleGimbalManagerStatus(const mavlink_message_t &message);
    void _handleGimbalDeviceAttitudeStatus(const mavlink_message_t &message);
    void _checkComplete(Gimbal &gimbal, GimbalPairId pairId);
    bool _tryGetGimbalControl();
    bool _yawInVehicleFrame(uint32_t flags);
    
    Gimbal *_activeGimbal = nullptr;
    struct PotentialGimbalManager {
        unsigned requestGimbalManagerInformationRetries = 6;
        bool receivedInformation = false;
    };
    QMap<uint8_t, PotentialGimbalManager> _potentialGimbalManagers; // key is compid

    QMap<GimbalPairId, Gimbal*> _potentialGimbals;
    QmlObjectListModel *_gimbals = nullptr;

    Vehicle *_vehicle = nullptr;
    static constexpr const char *_gimbalFactGroupNamePrefix = "gimbal";
};
