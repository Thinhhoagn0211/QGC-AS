import QtQuick
import QtQuick.Layouts
import QGroundControl
import QGroundControl.Controls
import QGroundControl.Controllers
Rectangle {
    
    RowLayout {
        id: quickActionsRow
        Layout.fillWidth: true
        Layout.topMargin: 20
        Layout.alignment: Qt.AlignHCenter
        spacing: 10

        QGCButton {
            id: returnToHomeButton
            text: qsTr("Trở về nhà")
            visible: true
            backgroundColor: "darkblue"
            onClicked: {
                _guidedController.closeAll()
                _guidedController.confirmAction(_guidedController.actionRTL)
            }
        }

        QGCButton {
            id: emergencyLandingButton
            text: qsTr("Hạ cánh khẩn cấp")
            visible: true
            backgroundColor: "red"
            onClicked: {
                _guidedController.closeAll()
                _guidedController.confirmAction(_guidedController.actionLand)
            }
        }
    }

    QGCButton {
        id: preCheckFlightConditionsButton
        text: qsTr("Kiểm tra trước chuyến bay")
        visible: true
        backgroundColor: "darkblue"
        // onClicked: topRightPanel.visible = false
        anchors.top: quickActionsRow.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            topRightPanel.visible = false
            if (!preFlightChecklistLoader.active) {
                preFlightChecklistLoader.active = true
            }
            preFlightChecklistLoader.item.open()
        }
    }

    Repeater {
        model: _activeVehicle ? _activeVehicle.batteries : 0
    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: preCheckFlightConditionsButton.bottom
        anchors.topMargin: 20
        spacing: 8

        MetricsRow { label: "Số lượng GPS"; value: _activeVehicle ? _activeVehicle.gps.count.valueString : qsTr("N/A") }
        MetricsRow { label: "Latitude"; value: _activeVehicle ? globals.activeVehicle.latitude.toFixed(5): qsTr("--.--") }
        MetricsRow { label: "Longitude"; value: _activeVehicle ? globals.activeVehicle.longitude.toFixed(5): qsTr("--.--") }
        MetricsRow { label: "Tốc độ máy bay"; value: _activeVehicle ? globals.activeVehicle.airSpeed.rawValue.toFixed(1) + " m/s" : qsTr("--.--") }
        MetricsRow { label: "Tốc độ mặt đất"; value: _activeVehicle ? globals.activeVehicle.groundSpeed.rawValue.toFixed(1) + " m/s" : qsTr("--.--") }
        MetricsRow { label: "Tốc độ gió"; value: _activeVehicle ? globals.activeVehicle.airSpeed.value + " m/s" : qsTr("--.--") }
        MetricsRow { label: "Khoảng cách về nhà"; value: _activeVehicle ? _activeVehicle.distanceToHome.rawValue.toFixed(1) : qsTr("--.--") }
        MetricsRow { label: "Độ cao tương đối"; value: _activeVehicle ? _activeVehicle.altitudeRelative.value.toFixed(1) + "m" : qsTr("--.--") }
        MetricsRow { label: "Dung lượng pin"; value: object.percentRemaining.valueString + " " + object.percentRemaining.units }
        MetricsRow { label: "Trạng thái"; value: object.chargeState.enumStringValue }
        MetricsRow { label: "Thời gian còn lại"; value: object.timeRemainingStr.value }
        MetricsRow { label: "Điện áp máy bay"; value: object.voltage.valueString + " " + object.voltage.units }
        MetricsRow { label: "Dòng xả"; value: object.mahConsumed.valueString + " " + object.mahConsumed.units }
        MetricsRow { label: "Nhiệt độ"; value: object.temperature.valueString + " " + object.temperature.units }
    }

    }
    
}