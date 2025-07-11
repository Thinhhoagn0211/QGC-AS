// InfoBadge.qml
import QtQuick
import QtQuick.Controls
import QGroundControl.ScreenTools
Rectangle {
    id: badge
    property alias iconSource: icon.source
    property alias title: titleLabel.text
    property alias value: valueLabel.text

    width: Math.min(_defaultWidth, _maxWidth)
    height: _outerRadius * 2
    radius: _outerRadius * 0.75
    color: "orange"


    property real   _defaultWidth:      mainWindow.width * 0.05
    property real   _maxWidth:          ScreenTools.defaultFontPixelHeight * 5
    property real   _innerRadius:       (width - (_topBottomMargin * 3)) / 4
    property real   _outerRadius:       _innerRadius + _topBottomMargin
    property real   _spacing:           ScreenTools.defaultFontPixelHeight * 0.33
    property real   _topBottomMargin:   (width * 0.05) / 2

    Row {
        anchors.centerIn: parent
        spacing: 6

        Image {
            id: icon
            width: ScreenTools.defaultFontPixelHeight 
            height: ScreenTools.defaultFontPixelHeight 
            source: ""
        }

        Column {
            spacing: 2
            Text {
                id: titleLabel
                text: ""
                color: "white"
                font.pixelSize: ScreenTools.defaultFontPixelHeight * 0.5
            }
            Text {
                id: valueLabel
                text: ""
                color: "white"
                font.pixelSize: ScreenTools.defaultFontPixelHeight * 0.5
            }
        }
    }
}
