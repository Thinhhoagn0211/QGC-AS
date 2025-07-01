import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtLocation
import QtPositioning
import QtQuick.Layouts
import QtQuick.Window

import QGroundControl
import QGroundControl.FlightMap
import QGroundControl.ScreenTools
import QGroundControl.Controls
import QGroundControl.FactSystem
import QGroundControl.FactControls
import QGroundControl.Palette
import QGroundControl.Controllers
import QGroundControl.ShapeFileHelper
import QGroundControl.FlightDisplay
import QGroundControl.UTMSP

Item {
    id: _root

    property var mapControl
    property var _mapControl:            mapControl
    property var planMasterController

    Item {
        id: contentItem
        width: childrenRect.width
        height: childrenRect.height
        anchors.horizontalCenter: parent.horizontalCenter


        ColumnLayout {
            spacing: 12

            RowLayout {
                spacing: 10

                QGCButtonMission {
                    id: uploadButton
                    text: qsTr("Upload")
                    pointSize:         ScreenTools.smallFontPointSize
                    implicitWidth: ScreenTools.implicitButtonWidth
                    implicitHeight: ScreenTools.implicitButtonHeight
                    backgroundColor: "green"
                    onClicked: {
                        if (planMasterController._utmspEnabled) {
                            QGroundControl.utmspManager.utmspVehicle.triggerActivationStatusBar(true);
                            UTMSPStateStorage.removeFlightPlanState = true
                            UTMSPStateStorage.indicatorDisplayStatus = true
                        }
                        planMasterController.upload();
                    }
                    PropertyAnimation on opacity {
                        easing.type:    Easing.OutQuart
                        from:           0.5
                        to:             1
                        loops:          Animation.Infinite
                        running:        _controllerDirty && !_controllerSyncInProgress
                        alwaysRunToEnd: true
                        duration:       2000
                    }
                }

                QGCButtonMission {
                    id: openFileButton
                    text: qsTr("Open file")
                    visible: true
                    pointSize:         ScreenTools.smallFontPointSize
                    implicitWidth: ScreenTools.implicitButtonWidth
                    implicitHeight: ScreenTools.implicitButtonHeight
                    backgroundColor: "blue"
                    onClicked: {
                        // dropPanel.hide()
                        if (planMasterController.dirty) {
                            console.log("Open file button clicked with unsaved changes")
                            showLoadFromFileOverwritePrompt(planMasterController._overwriteText)
                        } else {
                            console.log("Open file button clicked without unsaved changes")
                            planMasterController.loadFromSelectedFile()
                        }
                    }
                }

                QGCButtonMission {
                    id: saveFileButton
                    text: qsTr("Save")
                    pointSize:         ScreenTools.smallFontPointSize
                    implicitWidth: ScreenTools.implicitButtonWidth
                    implicitHeight: ScreenTools.implicitButtonHeight
                    visible: true
                    backgroundColor: "darkgray"
                    onClicked: {
                        planMasterController.saveToSelectedFile()
                    }
                }

                QGCButtonMission {
                    id: downloadButton
                    text: qsTr("Download")
                    pointSize:         ScreenTools.smallFontPointSize
                    implicitWidth: ScreenTools.implicitButtonWidth
                    implicitHeight: ScreenTools.implicitButtonHeight
                    visible: true
                    backgroundColor: "gray"
                    onClicked: {
                        downloadClicked(_overwriteText)
                    }
                }

                QGCButtonMission {
                    id: deleteButton
                    text: qsTr("Delete")
                    pointSize:         ScreenTools.smallFontPointSize
                    implicitWidth: ScreenTools.implicitButtonWidth
                    implicitHeight: ScreenTools.implicitButtonHeight
                    visible: true
                    backgroundColor: "orange"
                    onClicked: {
                        clearButtonClicked()
                    }
                }

            }

            Rectangle {
                id: settingsVehiclePlanRect
                width: 250
                height: 175
                color: "transparent"
                border.color: "white"
                border.width: 1

                ColumnLayout {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    spacing: 5

                    Text {
                        text: qsTr("General settings:")
                        font.bold: true
                        font.pointSize: ScreenTools.defaultFontPointSize * 1.2
                        color: "white"
                    }

                    GridLayout {
                        id: gridSetAltitude
                        columns: 2
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        rowSpacing: 10
                        columnSpacing: 10

                        // Row 1
                        Text {
                            text: qsTr("Takeoff altitude:")
                            font.pixelSize: ScreenTools.defaultFontPointSize * 1.2
                            color: "white"
                        }

                        QGCTextField {
                            id: takeoffAltitudeField
                            placeholderText: qsTr("Enter takeoff altitude")
                            width: 150
                            text: "100.0"
                            color: "transparent"
                            // textColor: "white"
                        }

                        // Row 2
                        Text {
                            text: qsTr("Landing altitude:")
                            font.pixelSize: ScreenTools.defaultFontPointSize * 1.2
                            color: "white"
                        }

                        QGCTextField {
                            id: landingAltitudeField
                            placeholderText: qsTr("Enter landing altitude")
                            width: 150
                            color: "transparent"
                            // textColor: "white"
                            text: "50" // Default value, can be changed later
                        }
                    }

                    QGCCheckBox {
                        id: takeoffCheckBox
                        text: qsTr("Create takeoff point")
                    }

                    QGCCheckBox {
                        id: landingCheckBox
                        text: qsTr("Create landing point")
                    }
                }   
            }
        
            Item {
                id:                     missionItemEditor
                visible:                true
                ListView {
                    width: contentItem.width
                    height: 200
                    model: _missionController.visualItems
                    cacheBuffer: Math.max(height * 2, 0)
                    clip: true
                    currentIndex: _missionController.currentPlanViewSeqNum
                    highlightMoveDuration: 250
                    visible: true
                    delegate: MissionItemDelegate {
                        map:            mapControl
                        masterController:  planMasterController
                        missionItem:    object
                        width:          contentItem.width
                        readOnly:       false
                        onClicked: (sequenceNumber) => { _missionController.setCurrentPlanViewSeqNum(object.sequenceNumber, false) }
                        onRemove: {
                            var removeVIIndex = index
                            _missionController.removeVisualItem(removeVIIndex)
                            if (removeVIIndex >= _missionController.visualItems.count) {
                                removeVIIndex--
                            }
                        }
                        onSelectNextNotReadyItem:   selectNextNotReady()
                    }
                }
            }


        }
    }

}