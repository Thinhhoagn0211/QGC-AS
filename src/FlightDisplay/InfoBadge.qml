// InfoBadge.qml
import QtQuick
import QtQuick.Controls

Rectangle {
    id: badge
    property alias iconSource: icon.source
    property alias title: titleLabel.text
    property alias value: valueLabel.text

    width: 110
    height: 40
    radius: 20
    color: "orange" // mặc định

    Row {
        anchors.centerIn: parent
        spacing: 6

        Image {
            id: icon
            width: 16
            height: 16
            source: "" // sẽ được gán từ bên ngoài
        }

        Column {
            spacing: 2
            Text {
                id: titleLabel
                text: "Tiêu đề"
                color: "white"
                font.pixelSize: 11
            }
            Text {
                id: valueLabel
                text: "Giá trị"
                color: "white"
                font.pixelSize: 11
            }
        }
    }
}
