import QtQuick
import QtQuick.Layouts
import QGroundControl
import QGroundControl.Controls
import QGroundControl.Controllers

Item {
    id: _root
    anchors.fill: parent

    // Item trung gian để căn giữa nội dung
    Item {
        id: contentItem
        width: childrenRect.width
        height: childrenRect.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20

        Column {
            spacing: 20

            Row {
                id: quickActionsRow
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                QGCButton {
                    text: qsTr("Trở về nhà")
                    backgroundColor: "darkblue"
                    onClicked: {
                        _guidedController.closeAll()
                        _guidedController.confirmAction(_guidedController.actionSetFlightMode, "Safe Recovery")
                    }
                }

                QGCButton {
                    text: qsTr("Hạ cánh khẩn cấp")
                    backgroundColor: "red"
                    onClicked: {
                        _guidedController.closeAll()
                        _guidedController.confirmAction(_guidedController.actionLand)
                    }
                }
            }

            Column {
                id: metricsColumn
                spacing: 8
                anchors.horizontalCenter: parent.horizontalCenter
                visible: _activeVehicle !== undefined

                MetricsRow { label: "Số lượng GPS"; value: _activeVehicle ? _activeVehicle.gps.count.valueString : qsTr("N/A") }
                MetricsRow { label: "Latitude"; value: _activeVehicle ? _activeVehicle.latitude.toFixed(5) : qsTr("--.--") }
                MetricsRow { label: "Longitude"; value: _activeVehicle ? _activeVehicle.longitude.toFixed(5) : qsTr("--.--") }
                MetricsRow { label: "Tốc độ máy bay"; value: _activeVehicle ? _activeVehicle.airSpeed.rawValue.toFixed(1) + " m/s" : qsTr("--.--") }
                MetricsRow { label: "Tốc độ mặt đất"; value: _activeVehicle ? _activeVehicle.groundSpeed.rawValue.toFixed(1) + " m/s" : qsTr("--.--") }
                MetricsRow { label: "Tốc độ gió"; value: _activeVehicle ? _activeVehicle.windSpeed.value + " m/s" : qsTr("--.--") }                
                MetricsRow { label: "Độ cao tương đối"; value: _activeVehicle ? _activeVehicle.altitudeRelative.value.toFixed(1) + "m" : qsTr("--.--") }
                MetricsRow { label: "Dung lượng pin"; value: _activeVehicle.batteries.get(0).percentRemaining.rawValue.toFixed(1) + "%" }
                MetricsRow { label: "Thời gian còn lại"; value: _activeVehicle.batteries.get(0).timeRemaining.rawValue ? 
                    _activeVehicle.batteries.get(0).timeRemaining.rawValue.toFixed(1) + " phút" : qsTr("N/A") }
                MetricsRow { label: "Điện áp máy bay"; value: _activeVehicle.batteries.get(0).voltage.value + " V" }
                MetricsRow { label: "Dòng xả"; value: _activeVehicle.batteries.get(0).current.value + " A" }

            }
        }
    }

}



        // QGCButton {
        //     id: preCheckFlightConditionsButton
        //     text: qsTr("Kiểm tra trước chuyến bay")
        //     visible: true
        //     backgroundColor: "darkblue"
        //     // onClicked: topRightPanel.visible = false
        //     anchors.top: quickActionsRow.bottom
        //     anchors.topMargin: 20
        //     anchors.horizontalCenter: parent.horizontalCenter

        //     onClicked: {
        //         topRightPanel.visible = false
        //         if (!preFlightChecklistLoader.active) {
        //             preFlightChecklistLoader.active = true
        //         }
        //         preFlightChecklistLoader.item.open()
        //     }
        // }