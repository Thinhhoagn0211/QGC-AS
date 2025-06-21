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
    property var    _planMasterController:  planMasterController
    property bool   _controllerValid:           _planMasterController !== undefined && _planMasterController !== null
    property var    _currentMissionItem:        _planMasterController.missionController.currentPlanViewItem
    property var    _controllerDirty:           _controllerValid ? _planMasterController.dirty : false
    property var    _controllerSyncInProgress:  _controllerValid ? _planMasterController.syncInProgress : false
    property bool   _utmspEnabled:                       QGroundControl.utmspSupported
    property string _overwriteText: qsTr("Plan overwrite")
    property var    _missionController:                 _planMasterController.missionController
    property bool   _controllerOffline:         _controllerValid ? _planMasterController.offline : true
    property var    _appSettings:                       QGroundControl.settingsManager.appSettings



    function selectNextNotReady() {
        var foundCurrent = false
        for (var i=0; i<_missionController.visualItems.count; i++) {
            var vmi = _missionController.visualItems.get(i)
            if (vmi.readyForSaveState === VisualMissionItem.NotReadyForSaveData) {
                _missionController.setCurrentPlanViewSeqNum(vmi.sequenceNumber, true)
                break
            }
        }
    }

    function showLoadFromFileOverwritePrompt(title) {
        mainWindow.showMessageDialog(title,
        qsTr("You have unsaved/unsent changes. Loading from a file will lose these changes. Are you sure you want to load from a file?"),
        Dialog.Yes | Dialog.Cancel,
        function() { _planMasterController.loadFromSelectedFile() } )
    }


    function downloadClicked(title) {
        if (_planMasterController.dirty) {
            mainWindow.showMessageDialog(title,
                                         qsTr("You have unsaved/unsent changes. Loading from the Vehicle will lose these changes. Are you sure you want to load from the Vehicle?"),
                                         Dialog.Yes | Dialog.Cancel,
                                         function() { _planMasterController.loadFromVehicle() })
        } else {
            _planMasterController.loadFromVehicle()
        }
    }

    
    function clearButtonClicked() {
        mainWindow.showMessageDialog(qsTr("Clear"),
                                     qsTr("Are you sure you want to remove all mission items and clear the mission from the vehicle?"),
                                     Dialog.Yes | Dialog.Cancel,
                                     function() { _planMasterController.removeAllFromVehicle();
                                                  _missionController.setCurrentPlanViewSeqNum(0, true);
                                                  if(_utmspEnabled)
                                                    {_resetRegisterFlightPlan = true;
                                                      QGroundControl.utmspManager.utmspVehicle.triggerActivationStatusBar(false);
                                                      UTMSPStateStorage.startTimeStamp = "";
                                                      UTMSPStateStorage.showActivationTab = false;
                                                      UTMSPStateStorage.flightID = "";
                                                      UTMSPStateStorage.enableMissionUploadButton = false;
                                                      UTMSPStateStorage.indicatorPendingStatus = true;
                                                      UTMSPStateStorage.indicatorApprovedStatus = false;
                                                      UTMSPStateStorage.indicatorActivatedStatus = false;
                                                      UTMSPStateStorage.currentStateIndex = 0}})
    }

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
                enabled:     _utmspEnabled ? !_controllerSyncInProgress && UTMSPStateStorage.enableMissionUploadButton : !_controllerSyncInProgress
                visible:     !_controllerOffline && !_controllerSyncInProgress
                implicitWidth: 50
                implicitHeight: 25
                backgroundColor: "lightgreen"
                onClicked: {
                    if (_utmspEnabled) {
                        QGroundControl.utmspManager.utmspVehicle.triggerActivationStatusBar(true);
                        UTMSPStateStorage.removeFlightPlanState = true
                        UTMSPStateStorage.indicatorDisplayStatus = true
                    }
                    _planMasterController.upload();
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
                    if (_planMasterController.dirty) {
                        showLoadFromFileOverwritePrompt(columnHolder._overwriteText)
                    } else {
                        _planMasterController.loadFromSelectedFile()
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
                    _planMasterController.saveToSelectedFile()
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
                    // dropPanel.hide()
                    clearButtonClicked()
                }
            }

        }
        
        ColumnLayout {
            spacing: 10
            Text {
                text: "Cài đặt chung"
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
                    text: "Label 1"
                    font.pixelSize: 16
                }

                Rectangle {
                    width: 100
                    height: 30
                    color: "lightblue"
                }

                // Row 2
                Text {
                    text: "Label 2"
                    font.pixelSize: 16
                }

                Rectangle {
                    width: 100
                    height: 30
                    color: "lightgreen"
                }

            }


            QGCCheckBox {
                id: takeoffCheckBox
                text: qsTr("Tạo thêm điểm cất cánh")
            }

            QGCCheckBox {
                id: landingCheckBox
                text: qsTr("Tạo thêm điểm hạ cánh")
            }


            Item {
                id:                     missionItemEditor
                anchors.left:           parent.left
                anchors.right:          parent.right
                anchors.top:            landingCheckBox.bottom
                anchors.topMargin:      ScreenTools.defaultFontPixelHeight * 0.25
                anchors.bottom:         parent.bottom
                anchors.bottomMargin:   ScreenTools.defaultFontPixelHeight * 0.25
                visible:                mapControl._editingLayer == mapControl._layerMission && !mapControl.planControlColapsed
                QGCListView {
                    id:                 missionItemEditorListView
                    anchors.fill:       parent
                    spacing:            ScreenTools.defaultFontPixelHeight / 4
                    orientation:        ListView.Vertical
                    model:              _missionController.visualItems
                    cacheBuffer:        Math.max(height * 2, 0)
                    clip:               true
                    currentIndex:       _missionController.currentPlanViewSeqNum
                    highlightMoveDuration: 250
                    visible:            mapControl._editingLayer == mapControl._layerMission && !mapControl.planControlColapsed
                    delegate: MissionItemEditor {
                        map:            mapControl
                        masterController:  _planMasterController
                        missionItem:    object
                        width:          missionItemEditorListView.width
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

    PlanMasterController {
        id:         planMasterController
        flyView:    false

        Component.onCompleted: {
            _planMasterController.start()
            _missionController.setCurrentPlanViewSeqNum(0, true)
        }

        onPromptForPlanUsageOnVehicleChange: {
            if (!_promptForPlanUsageShowing) {
                _promptForPlanUsageShowing = true
                promptForPlanUsageOnVehicleChangePopupComponent.createObject(mainWindow).open()
            }
        }

        function waitingOnIncompleteDataMessage(save) {
            var saveOrUpload = save ? qsTr("Save") : qsTr("Upload")
            mainWindow.showMessageDialog(qsTr("Unable to %1").arg(saveOrUpload), qsTr("Plan has incomplete items. Complete all items and %1 again.").arg(saveOrUpload))
        }

        function waitingOnTerrainDataMessage(save) {
            var saveOrUpload = save ? qsTr("Save") : qsTr("Upload")
            mainWindow.showMessageDialog(qsTr("Unable to %1").arg(saveOrUpload), qsTr("Plan is waiting on terrain data from server for correct altitude values."))
        }

        function checkReadyForSaveUpload(save) {
            if (readyForSaveState() == VisualMissionItem.NotReadyForSaveData) {
                waitingOnIncompleteDataMessage(save)
                return false
            } else if (readyForSaveState() == VisualMissionItem.NotReadyForSaveTerrain) {
                waitingOnTerrainDataMessage(save)
                return false
            }
            return true
        }

        function upload() {
            if (!checkReadyForSaveUpload(false /* save */)) {
                return
            }
            switch (_missionController.sendToVehiclePreCheck()) {
                case MissionController.SendToVehiclePreCheckStateOk:
                    sendToVehicle()
                    break
                case MissionController.SendToVehiclePreCheckStateActiveMission:
                    mainWindow.showMessageDialog(qsTr("Send To Vehicle"), qsTr("Current mission must be paused prior to uploading a new Plan"))
                    break
                case MissionController.SendToVehiclePreCheckStateFirwmareVehicleMismatch:
                    mainWindow.showMessageDialog(qsTr("Plan Upload"),
                                                 qsTr("This Plan was created for a different firmware or vehicle type than the firmware/vehicle type of vehicle you are uploading to. " +
                                                      "This can lead to errors or incorrect behavior. " +
                                                      "It is recommended to recreate the Plan for the correct firmware/vehicle type.\n\n" +
                                                      "Click 'Ok' to upload the Plan anyway."),
                                                 Dialog.Ok | Dialog.Cancel,
                                                 function() { _planMasterController.sendToVehicle() })
                    break
            }
        }

        function loadFromSelectedFile() {
            fileDialog.title =          qsTr("Select Plan File")
            fileDialog.planFiles =      true
            fileDialog.nameFilters =    _planMasterController.loadNameFilters
            fileDialog.openForLoad()
        }

        function saveToSelectedFile() {
            if (!checkReadyForSaveUpload(true /* save */)) {
                return
            }
            fileDialog.title =          qsTr("Save Plan")
            fileDialog.planFiles =      true
            fileDialog.nameFilters =    _planMasterController.saveNameFilters
            fileDialog.openForSave()
        }

        function fitViewportToItems() {
            mapFitFunctions.fitMapViewportToMissionItems()
        }

        function saveKmlToSelectedFile() {
            if (!checkReadyForSaveUpload(true /* save */)) {
                return
            }
            fileDialog.title =          qsTr("Save KML")
            fileDialog.planFiles =      false
            fileDialog.nameFilters =    ShapeFileHelper.fileDialogKMLFilters
            fileDialog.openForSave()
        }
    }


    QGCFileDialog {
        id:             fileDialog
        folder:         _appSettings ? _appSettings.missionSavePath : ""

        property bool planFiles: true    ///< true: working with plan files, false: working with kml file

        onAcceptedForSave: (file) => {
            if (planFiles) {
                _planMasterController.saveToFile(file)
            } else {
                _planMasterController.saveToKml(file)
            }
            close()
        }

        onAcceptedForLoad: (file) => {
            _planMasterController.loadFromFile(file)
            _planMasterController.fitViewportToItems()
            _missionController.setCurrentPlanViewSeqNum(0, true)
            close()
        }
    }
}