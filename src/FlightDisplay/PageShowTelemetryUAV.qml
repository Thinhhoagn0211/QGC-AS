import QtQuick
import QtQuick.Layouts
import QGroundControl
import QGroundControl.Controls
import QGroundControl.Controllers

Item {
    id: _root
    // anchors.fill: parent

    Item {
        id: contentItem
        width: childrenRect.width
        height: childrenRect.height
        anchors.horizontalCenter: parent.horizontalCenter

        ColumnLayout {
            spacing: 20

            QGCButton {
                text: qsTr("Start flying - Automatic mode")
                backgroundColor: "green"
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    if (_activeVehicle) {
                        _guidedController.confirmAction(_guidedController.actionSetFlightMode, "TakeOff")
                        _guidedController.confirmAction(_guidedController.actionSetFlightMode, "Mission")
                    }
                }
            }

            RowLayout {
                id: quickActionsRow
                
                spacing: 10

                QGCButton {
                    text: qsTr("Return to home")
                    backgroundColor: "darkblue"
                    onClicked: {
                        _guidedController.closeAll()
                        _guidedController.confirmAction(_guidedController.actionSetFlightMode, "Safe Recovery")
                    }
                }

                QGCButton {
                    text: qsTr("Land")
                    backgroundColor: "red"
                    onClicked: {
                        _guidedController.closeAll()
                        _guidedController.confirmAction(_guidedController.actionLand)
                    }
                }
            }

            ColumnLayout {
                id: metricsColumn
                spacing: 8
                visible: _activeVehicle !== undefined

                MetricsRow { label: qsTr("GPS numbers"); value: _activeVehicle ? _activeVehicle.gps.count.valueString : qsTr("N/A") }
                MetricsRow { label: qsTr("Latitude"); value: _activeVehicle ? _activeVehicle.latitude.toFixed(5) : qsTr("--.--") }
                MetricsRow { label: qsTr("Longitude"); value: _activeVehicle ? _activeVehicle.longitude.toFixed(5) : qsTr("--.--") }
                MetricsRow { label: qsTr("Vehicle speed"); value: _activeVehicle ? _activeVehicle.airSpeed.rawValue.toFixed(1) + " m/s" : qsTr("--.--") }
                MetricsRow { label: qsTr("Ground speed"); value: _activeVehicle ? _activeVehicle.groundSpeed.rawValue.toFixed(1) + " m/s" : qsTr("--.--") }
                MetricsRow { label: qsTr("Wind speed"); value: _activeVehicle ? _activeVehicle.windSpeed.value + " m/s" : qsTr("--.--") }                
                MetricsRow { label: qsTr("Relative height"); value: _activeVehicle ? _activeVehicle.altitudeRelative.value.toFixed(1) + "m" : qsTr("--.--") }
                MetricsRow { label: qsTr("Battery capacity"); value: (_activeVehicle && _activeVehicle.batteries) ? _activeVehicle.batteries.get(0).percentRemaining.rawValue.toFixed(1) + "%" : qsTr("N/A") }
                MetricsRow { label: qsTr("Time remaining"); value: (_activeVehicle && _activeVehicle.batteries) ? 
                    _activeVehicle.batteries.get(0).timeRemaining.rawValue.toFixed(1) + " phút" : qsTr("N/A") }
                MetricsRow { label: qsTr("Voltage"); value: (_activeVehicle && _activeVehicle.batteries) ? _activeVehicle.batteries.get(0).voltage.value + " V" : qsTr("N/A") }
                MetricsRow { label: qsTr("Current");  value: (_activeVehicle && _activeVehicle.batteries) ? _activeVehicle.batteries.get(0).current.value + " A" : qsTr("N/A") }

            }
        }
    }

}