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
    color: "orange"

    Row {
        anchors.centerIn: parent
        spacing: 6

        Image {
            id: icon
            width: 24
            height: 24
            source: ""
        }

        Column {
            spacing: 2
            Text {
                id: titleLabel
                text: ""
                color: "white"
                font.pixelSize: 11
            }
            Text {
                id: valueLabel
                text: ""
                color: "white"
                font.pixelSize: 11
            }
        }
    }
}
