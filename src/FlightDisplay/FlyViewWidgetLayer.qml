/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

import QtLocation
import QtPositioning
import QtQuick.Window
import QtQml.Models

import QGroundControl
import QGroundControl.Controls
import QGroundControl.Controllers
import QGroundControl.Controls
import QGroundControl.FactSystem
import QGroundControl.FlightDisplay
import QGroundControl.FlightMap
import QGroundControl.Palette
import QGroundControl.ScreenTools
import QGroundControl.Vehicle

// This is the ui overlay layer for the widgets/tools for Fly View
Item {
    id: _root
    
    property int selectedButton: 1
    property var    parentToolInsets
    property var    totalToolInsets:        _totalToolInsets
    property bool   isViewer3DOpen:         false

    property var mapControl
    property var    _activeVehicle:         QGroundControl.multiVehicleManager.activeVehicle
    property var planMasterController
    property var    _planMasterController:  planMasterController
    property var    _missionController:     _planMasterController.missionController
    property var    _geoFenceController:    _planMasterController.geoFenceController
    property var    _rallyPointController:  _planMasterController.rallyPointController
    property var    _guidedController:      globals.guidedControllerFlyView
    property real   _margins:               ScreenTools.defaultFontPixelWidth / 2
    property real   _toolsMargin:           ScreenTools.defaultFontPixelWidth * 0.75
    property rect   _centerViewport:        Qt.rect(0, 0, width, height)
    property real   _rightPanelWidth:       ScreenTools.defaultFontPixelWidth * 30
    property alias  _gripperMenu:           gripperOptions
    property real   _layoutMargin:          ScreenTools.defaultFontPixelWidth * 0.75
    property bool   _layoutSpacing:         ScreenTools.defaultFontPixelWidth
    property bool   _showSingleVehicleUI:   true

    property bool utmspActTrigger



    QGCToolInsets {
        id:                     _totalToolInsets
        leftEdgeTopInset:       toolStrip.leftEdgeTopInset
        leftEdgeCenterInset:    toolStrip.leftEdgeCenterInset
        leftEdgeBottomInset:    virtualJoystickMultiTouch.visible ? virtualJoystickMultiTouch.leftEdgeBottomInset : parentToolInsets.leftEdgeBottomInset
        rightEdgeTopInset:      topRightPanel.rightEdgeTopInset
        rightEdgeCenterInset:   topRightPanel.rightEdgeCenterInset
        rightEdgeBottomInset:   bottomRightRowLayout.rightEdgeBottomInset
        topEdgeLeftInset:       toolStrip.topEdgeLeftInset
        topEdgeCenterInset:     mapScale.topEdgeCenterInset
        topEdgeRightInset:      topRightPanel.topEdgeRightInset
        bottomEdgeLeftInset:    virtualJoystickMultiTouch.visible ? virtualJoystickMultiTouch.bottomEdgeLeftInset : parentToolInsets.bottomEdgeLeftInset
        bottomEdgeCenterInset:  bottomRightRowLayout.bottomEdgeCenterInset
        bottomEdgeRightInset:   virtualJoystickMultiTouch.visible ? virtualJoystickMultiTouch.bottomEdgeRightInset : bottomRightRowLayout.bottomEdgeRightInset
    }

    FlyViewTopRightPanel {
        id:                     topRightPanel
        anchors.top:            parent.top
        anchors.right:          parent.right
        anchors.topMargin:      _layoutMargin
        anchors.rightMargin:    _layoutMargin
        maximumHeight:          parent.height - (bottomRightRowLayout.height + _margins * 5)

        property real topEdgeRightInset:    height + _layoutMargin
        property real rightEdgeTopInset:    width + _layoutMargin
        property real rightEdgeCenterInset: rightEdgeTopInset
    }

    ColumnLayout {
        id:                 topRightPanelBackground
        anchors.margins:    _layoutMargin
        anchors.top:        parent.top
        anchors.bottom:     bottomRightRowLayout.top
        anchors.right:      parent.right
        spacing:            _layoutSpacing
        visible:            !topRightPanel.visible
        
        Rectangle {
            id: backgroundRect
            width: 300
            height: 600
            color: Qt.rgba(0, 0, 0, 0.5)
            radius: 0

            // Container cho 2 button đặt ngang
            RowLayout {
                id: buttonRow
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: _layoutMargin
                spacing: 10

                
                QGCButton {
                    id: topRightPanelButton
                    text: qsTr("Chức năng")
                    backgroundColor:  selectedButton === 1 ? "#a2a200" : "gray"
                    textColor: "white"
                    primary: {
                        selectedButton === 1 ? true : false
                    }
                    visible: !topRightPanel.visible
                    onClicked: {
                        globals.selectedView = 0
                        selectedButton = 1
                        pageLoader.sourceComponent = pageShowTelemetryUAV
                        planMasterController.flyView = true
                        mapControl.planView = false
                        // removeAllItems()
                        
                    }
                    anchors.left: buttonRow.left
                    anchors.leftMargin: 20
                }

                Item { width: 1; Layout.fillWidth: true }

                QGCButton {
                    id: topRightPanelCloseButton
                    text: qsTr("Kế Hoạch Bay")
                    backgroundColor:  selectedButton === 2 ? "#a2a200" : "gray"
                    textColor: "white"
                    primary: {
                        selectedButton === 2 ? true : false
                    }
                    visible: !topRightPanel.visible
                    onClicked: {
                        globals.selectedView = 1
                        selectedButton = 2
                        pageLoader.sourceComponent = pageShowPlanFlightUAV
                        planMasterController.flyView = false
                        mapControl.planView = true
                        // removeAllItems()
                        insertTakeItemAfterCurrent()
                    }
                    anchors.right: buttonRow.right
                    anchors.rightMargin: 20
                }
            
            }

            Rectangle {
                id: divider
                anchors.top: buttonRow.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: 200
                height: 1
                color: "white"
            }

            Loader {
            id: pageLoader
            anchors.fill: parent
            anchors.topMargin: 60
            sourceComponent: pageShowTelemetryUAV 
        }


        }

        Rectangle {
            id: vehicleMessageRect
            anchors.topMargin: 20
            width: 300
            height: 200
            color: Qt.rgba(0, 0, 0, 0.5)
            radius: 0

            VehicleMessageList { 
                id: vehicleMessageList
            }
            }
    }

    
    Component {
        id: pageShowTelemetryUAV
        PageShowTelemetryUAV {
            color: "transparent"
            anchors.topMargin: 60
            anchors.fill: parent
        }
    }

    Component {
        id: pageShowPlanFlightUAV
        PageShowPlanFlightUAV {
            mapControl:         _root.mapControl
            planMasterController: _planMasterController
            color: "transparent"
            anchors.topMargin: 60
            anchors.fill: parent
        }
    }

    Column {
        id:                 infoBadgeContainer
        anchors.bottom: bottomRightRowLayout.top
        anchors.bottomMargin: 10
        anchors.right:      parent.right
        spacing:            8
        Repeater {
            model: _activeVehicle
            Row {
                id:                infoBadgeRow
                spacing: 8

                InfoBadge {
                    color: "#f39c12"
                    // iconSource: "qrc:/icons/clock.png"
                    title: "Thời gian"
                    value: _activeVehicle ? _activeVehicle.flightTime.valueString : "00:00:00"
                }

                InfoBadge {
                    color: "#2980b9"
                    // iconSource: "qrc:/icons/home.png"
                    title: "Nhà"
                    value: _activeVehicle ? _activeVehicle.distanceToHome.rawValue.toFixed(1) + "m" : qsTr("--.--")
                }

                InfoBadge {
                    color: "#27ae60"
                    // iconSource: "qrc:/icons/track.png"
                    title: "Tổng"
                    value: _activeVehicle ? _activeVehicle.distanceTraveled.rawValue.toFixed(1) + "m" : "0 m"
                }

                InfoBadge {
                    color: "#7f8c8d"
                    // iconSource: "qrc:/icons/waypoint.png"
                    title: "WP " + _activeVehicle ? _activeVehicle.currentMissionIndex : "0" 
                    value: _activeVehicle ? _activeVehicle.distanceToNextWP.rawValue.toFixed(1) + "m" : "0 m"
                }
            }
        }
    }

    // Repeater 

    FlyViewBottomRightRowLayout {
        id:                 bottomRightRowLayout
        anchors.margins:    _layoutMargin
        anchors.bottom:     parent.bottom
        anchors.right:      parent.right
        spacing:            _layoutSpacing

        property real bottomEdgeRightInset:     height + _layoutMargin
        property real bottomEdgeCenterInset:    bottomEdgeRightInset
        property real rightEdgeBottomInset:     width + _layoutMargin
    }

    FlyViewMissionCompleteDialog {
        missionController:      _missionController
        geoFenceController:     _geoFenceController
        rallyPointController:   _rallyPointController
    }

    GuidedActionConfirm {
        anchors.margins:            _toolsMargin
        anchors.top:                parent.top
        anchors.horizontalCenter:   parent.horizontalCenter
        z:                          QGroundControl.zOrderTopMost
        guidedController:           _guidedController
        guidedValueSlider:          _guidedValueSlider
        utmspSliderTrigger:         utmspActTrigger
    }

    //-- Virtual Joystick
    Loader {
        id:                         virtualJoystickMultiTouch
        z:                          QGroundControl.zOrderTopMost + 1
        anchors.right:              parent.right
        anchors.rightMargin:        anchors.leftMargin
        height:                     Math.min(parent.height * 0.25, ScreenTools.defaultFontPixelWidth * 16)
        visible:                    _virtualJoystickEnabled && !QGroundControl.videoManager.fullScreen && !(_activeVehicle ? _activeVehicle.usingHighLatencyLink : false)
        anchors.bottom:             parent.bottom
        anchors.bottomMargin:       bottomLoaderMargin
        anchors.left:               parent.left
        anchors.leftMargin:         ( y > toolStrip.y + toolStrip.height ? toolStrip.width / 2 : toolStrip.width * 1.05 + toolStrip.x)
        source:                     "qrc:/qml/QGroundControl/FlightDisplay/VirtualJoystick.qml"
        active:                     _virtualJoystickEnabled && !(_activeVehicle ? _activeVehicle.usingHighLatencyLink : false)

        property real bottomEdgeLeftInset:     parent.height-y
        property bool autoCenterThrottle:      QGroundControl.settingsManager.appSettings.virtualJoystickAutoCenterThrottle.rawValue
        property bool leftHandedMode:          QGroundControl.settingsManager.appSettings.virtualJoystickLeftHandedMode.rawValue
        property bool _virtualJoystickEnabled: QGroundControl.settingsManager.appSettings.virtualJoystick.rawValue
        property real bottomEdgeRightInset:    parent.height-y
        property var  _pipViewMargin:          _pipView.visible ? parentToolInsets.bottomEdgeLeftInset + ScreenTools.defaultFontPixelHeight * 2 :
                                               bottomRightRowLayout.height + ScreenTools.defaultFontPixelHeight * 1.5

        property var  bottomLoaderMargin:      _pipViewMargin >= parent.height / 2 ? parent.height / 2 : _pipViewMargin

        // Width is difficult to access directly hence this hack which may not work in all circumstances
        property real leftEdgeBottomInset:  visible ? bottomEdgeLeftInset + width/18 - ScreenTools.defaultFontPixelHeight*2 : 0
        property real rightEdgeBottomInset: visible ? bottomEdgeRightInset + width/18 - ScreenTools.defaultFontPixelHeight*2 : 0
        property real rootWidth:            _root.width
        property var  itemX:                virtualJoystickMultiTouch.x   // real X on screen

        onRootWidthChanged: virtualJoystickMultiTouch.status == Loader.Ready && visible ? virtualJoystickMultiTouch.item.uiTotalWidth = rootWidth : undefined
        onItemXChanged:     virtualJoystickMultiTouch.status == Loader.Ready && visible ? virtualJoystickMultiTouch.item.uiRealX = itemX : undefined

        //Loader status logic
        onLoaded: {
            if (virtualJoystickMultiTouch.visible) {
                virtualJoystickMultiTouch.item.calibration = true
                virtualJoystickMultiTouch.item.uiTotalWidth = rootWidth
                virtualJoystickMultiTouch.item.uiRealX = itemX
            } else {
                virtualJoystickMultiTouch.item.calibration = false
            }
        }
    }

    FlyViewToolStrip {
        id:                     toolStrip
        anchors.leftMargin:     _toolsMargin + parentToolInsets.leftEdgeCenterInset
        anchors.topMargin:      _toolsMargin + parentToolInsets.topEdgeLeftInset
        anchors.left:           parent.left
        anchors.verticalCenter: parent.verticalCenter
        z:                      QGroundControl.zOrderWidgets
        maxHeight:              parent.height - y - parentToolInsets.bottomEdgeLeftInset - _toolsMargin
        visible:                !QGroundControl.videoManager.fullScreen

        onDisplayPreFlightChecklist: {
            if (!preFlightChecklistLoader.active) {
                preFlightChecklistLoader.active = true
            }
            preFlightChecklistLoader.item.open()
        }

        property real topEdgeLeftInset:     visible ? y + height : 0
        property real leftEdgeTopInset:     visible ? x + width : 0
        property real leftEdgeCenterInset:  leftEdgeTopInset
    }  

    GripperMenu {
        id: gripperOptions
    }

    VehicleWarnings {
        anchors.centerIn:   parent
        z:                  QGroundControl.zOrderTopMost
    }

    Loader {
        id: preFlightChecklistLoader
        sourceComponent: preFlightChecklistPopup
        active: false
    }

    Component {
        id: preFlightChecklistPopup
        FlyViewPreFlightChecklistPopup {
            width: 600
            height: 400
            anchors.centerIn: parent
        }
    }
}
