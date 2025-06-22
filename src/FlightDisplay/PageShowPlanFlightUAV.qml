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

Rectangle {
    id: _root
    

    property var mapControl
    property var _mapControl:            mapControl
    property var planMasterController


    ColumnLayout {
        id: mainLayout
        spacing: 10

        RowLayout {
            id: actionButtonsRow
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            QGCButton {
                id: uploadButton
                text: qsTr("Tải lên")
                enabled:     planMasterController._utmspEnabled ? !planMasterController._controllerSyncInProgress && UTMSPStateStorage.enableMissionUploadButton : !planMasterController._controllerSyncInProgress
                visible:     !planMasterController._controllerOffline && !planMasterController._controllerSyncInProgress
                implicitWidth: 50
                implicitHeight: 25
                backgroundColor: "lightgreen"
                onClicked: {
                    if (planMasterController._utmspEnabled) {
                        console.log("UTMSP upload button clicked")
                        QGroundControl.utmspManager.utmspVehicle.triggerActivationStatusBar(true);
                        UTMSPStateStorage.removeFlightPlanState = true
                        UTMSPStateStorage.indicatorDisplayStatus = true
                    }
                    console.log("Upload button clicked")
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

            QGCButton {
                id: openFileButton
                text: qsTr("Mở file")
                visible: true
                backgroundColor: "lightblue"
                implicitWidth: 50
                implicitHeight: 25
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

            QGCButton {
                id: saveFileButton
                text: qsTr("Lưu file")
                visible: true
                backgroundColor: "darkgray"
                implicitWidth: 50
                implicitHeight: 25
                onClicked: {
                    planMasterController.saveToSelectedFile()
                }
            }

            QGCButton {
                id: downloadButton
                text: qsTr("Tải xuống")
                visible: true
                implicitWidth: 50
                implicitHeight: 25
                backgroundColor: "gray"
                onClicked: {
                    downloadClicked(_overwriteText)
                }
            }

            QGCButton {
                id: deleteButton
                text: qsTr("Xóa")
                visible: true
                implicitWidth: 50
                implicitHeight: 25
                backgroundColor: "lightyellow"
                onClicked: {
                    clearButtonClicked()
                }
            }

        }
        
        // Column {
        //     spacing: 10
        //     Text {
        //         text: "Cài đặt chung"
        //         font.bold: true
        //         font.pointSize: ScreenTools.defaultFontPointSize * 1.2
        //         color: "white"
        //     }

        //     GridLayout {
        //         id: gridSetAltitude
        //         columns: 2
        //         Layout.fillWidth: true
        //         Layout.fillHeight: true
        //         rowSpacing: 10
        //         columnSpacing: 10

        //         // Row 1
        //         Text {
        //             text: "Label 1"
        //             font.pixelSize: 16
        //         }

        //         Rectangle {
        //             width: 100
        //             height: 30
        //             color: "lightblue"
        //         }

        //         // Row 2
        //         Text {
        //             text: "Label 2"
        //             font.pixelSize: 16
        //         }

        //         Rectangle {
        //             width: 100
        //             height: 30
        //             color: "lightgreen"
        //         }

        //     }


        //     QGCCheckBox {
        //         id: takeoffCheckBox
        //         text: qsTr("Tạo thêm điểm cất cánh")
        //     }

        //     QGCCheckBox {
        //         id: landingCheckBox
        //         text: qsTr("Tạo thêm điểm hạ cánh")
        //     }


        //     Item {
        //         id:                     missionItemEditor
        //         anchors.left:           parent.left
        //         anchors.right:          parent.right
        //         anchors.top:            landingCheckBox.bottom
        //         anchors.topMargin:      ScreenTools.defaultFontPixelHeight * 0.25
        //         anchors.bottom:         parent.bottom
        //         anchors.bottomMargin:   ScreenTools.defaultFontPixelHeight * 0.25
        //         visible:                _editingLayer == _layerMission && !planControlColapsed
        //         QGCListView {
        //             id:                 missionItemEditorListView
        //             anchors.fill:       parent
        //             spacing:            ScreenTools.defaultFontPixelHeight / 4
        //             orientation:        ListView.Vertical
        //             model:              _missionController.visualItems
        //             cacheBuffer:        Math.max(height * 2, 0)
        //             clip:               true
        //             currentIndex:       _missionController.currentPlanViewSeqNum
        //             highlightMoveDuration: 250
        //             visible:            _editingLayer == _layerMission && !planControlColapsed
        //             delegate: MissionItemEditor {
        //                 map:            mapControl
        //                 masterController:  planMasterController
        //                 missionItem:    object
        //                 width:          missionItemEditorListView.width
        //                 readOnly:       false
        //                 onClicked: (sequenceNumber) => { setCurrentPlanViewSeqNum(object.sequenceNumber, false) }
        //                 onRemove: {
        //                     var removeVIIndex = index
        //                     removeVisualItem(removeVIIndex)
        //                     if (removeVIIndex >= _missionController.visualItems.count) {
        //                         removeVIIndex--
        //                     }
        //                 }
        //                 onSelectNextNotReadyItem:   selectNextNotReady()
        //             }
        //         }
        //     }
        // }
        
    }
    

}