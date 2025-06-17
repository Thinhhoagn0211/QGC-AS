/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick
import QtQuick.Controls
import QtQml.Models
import QtQuick.Layouts

import QGroundControl
import QGroundControl.ScreenTools
import QGroundControl.Controls
import QGroundControl.FlightDisplay
import QGroundControl.Vehicle

// ColumnLayout {
//     spacing: 0.8 * ScreenTools.defaultFontPixelWidth

//     property real _verticalMargin: ScreenTools.defaultFontPixelHeight / 2

//     Loader {
//         id:     modelContainer
//         source: "qrc:/qml/QGroundControl/FlightDisplay/DefaultChecklist.qml"
//     }

//     property bool allChecksPassed:  false
//     property var  vehicleCopy:      globals.activeVehicle

//     onVehicleCopyChanged: {
//         if (checkListRepeater.model) {
//             checkListRepeater.model.reset()
//         }
//     }

//     onAllChecksPassedChanged: {
//         if (allChecksPassed) {
//             globals.activeVehicle.checkListState = Vehicle.CheckListPassed
//         } else {
//             globals.activeVehicle.checkListState = Vehicle.CheckListFailed
//         }
//     }

//     function _handleGroupPassedChanged(index, passed) {
//         if (passed) {
//             // Collapse current group
//             var group = checkListRepeater.itemAt(index)
//             group._checked = false
//             // Expand next group
//             if (index + 1 < checkListRepeater.count) {
//                 group = checkListRepeater.itemAt(index + 1)
//                 group.enabled = true
//                 group._checked = true
//             }
//         }

//         // Walk the list and check if any group is failing
//         var allPassed = true
//         for (var i=0; i < checkListRepeater.count; i++) {
//             if (!checkListRepeater.itemAt(i).passed) {
//                 allPassed = false
//                 break
//             }
//         }
//         allChecksPassed = allPassed;
//     }

//     //-- Pick a checklist model that matches the current airframe type (if any)
//     function _updateModel() {
//         var vehicle = globals.activeVehicle
//         if (!vehicle) {
//             vehicle = QGroundControl.multiVehicleManager.offlineEditingVehicle
//         }

//         if(vehicle.multiRotor) {
//             modelContainer.source = "qrc:/qml/QGroundControl/FlightDisplay/MultiRotorChecklist.qml"
//         } else if(vehicle.vtol) {
//             modelContainer.source = "qrc:/qml/QGroundControl/FlightDisplay/VTOLChecklist.qml"
//         } else if(vehicle.rover) {
//             modelContainer.source = "qrc:/qml/QGroundControl/FlightDisplay/RoverChecklist.qml"
//         } else if(vehicle.sub) {
//             modelContainer.source = "qrc:/qml/QGroundControl/FlightDisplay/SubChecklist.qml"
//         } else if(vehicle.fixedWing) {
//             modelContainer.source = "qrc:/qml/QGroundControl/FlightDisplay/FixedWingChecklist.qml"
//         } else {
//             modelContainer.source = "qrc:/qml/QGroundControl/FlightDisplay/DefaultChecklist.qml"
//         }
//         return
//     }

//     Component.onCompleted: {
//         _updateModel()
//     }

//     onVisibleChanged: {
//         if(globals.activeVehicle) {
//             if(visible) {
//                 _updateModel()
//             }
//         }
//     }

//     // We delay the updates when a group passes so the user can see all items green for a moment prior to hiding
//     Timer {
//         id:         delayedGroupPassed
//         interval:   750

//         property int index

//         onTriggered: _handleGroupPassedChanged(index, true /* passed */)
//     }

//     function groupPassedChanged(index, passed) {
//         if (passed) {
//             delayedGroupPassed.index = index
//             delayedGroupPassed.restart()
//         } else {
//             _handleGroupPassedChanged(index, passed)
//         }
//     }

//     // Header/title of checklist
//     RowLayout {
//         Layout.fillWidth:   true
//         height:             1.75 * ScreenTools.defaultFontPixelHeight
//         spacing:            0

//         QGCLabel {
//             Layout.fillWidth:   true
//             text:               allChecksPassed ? qsTr("(Passed)") : qsTr("In Progress")
//             font.pointSize:     ScreenTools.mediumFontPointSize
//         }
//         QGCButton {
//             width:              1.2 * ScreenTools.defaultFontPixelHeight
//             height:             1.2 * ScreenTools.defaultFontPixelHeight
//             Layout.alignment:   Qt.AlignVCenter
//             onClicked:          checkListRepeater.model.reset()

//             QGCColoredImage {
//                 source:         "/qmlimages/MapSyncBlack.svg"
//                 color:          qgcPal.buttonText
//                 anchors.fill:   parent
//             }
//         }
//     }

//     // All check list items
//     Repeater {
//         id:     checkListRepeater
//         model:  modelContainer.item.model
//     }
// }


Item {
    width: 800
    height: 600

    property int selectedIndex: 0
    property string numberOfGPS: "0"
    property string batteryVoltage: "0v"
    property string gpsStatus: ""
    property string na:                 qsTr("N/A", "No data to display")
    property string valueNA:            qsTr("--.--", "No data to display")
    
    Timer {
        id: updateTimer
        interval: 1000 // Cập nhật mỗi giây
        running: true
        repeat: true
        onTriggered: {
            numberOfGPS = _activeVehicle.gps.count.valueString
            // batteryVoltage = _activeVehicle.batteries[0].voltage.rawValue + " " + _activeVehicle.batteries[0].voltage.units
            gpsStatus = _activeVehicle.gps.lock.enumStringValue
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // RowLayout chứa các nút
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            // Button 1
            QGCButton {
                text: "Thông số tổng quan"
                Layout.fillWidth: true
                background: Rectangle {
                    color: selectedIndex === 0 ? "darkblue" : "lightgray"
                    radius: 4
                }
                onClicked: selectedIndex = 0
            }

            // Button 2
            QGCButton {
                text: "Cảm biến"
                Layout.fillWidth: true
                background: Rectangle {
                    color: selectedIndex === 1 ? "darkblue" : "lightgray"
                    radius: 4
                }
                onClicked: selectedIndex = 1
            }

            // Button 3
            QGCButton {
                text: "Động cơ và cánh lái"
                Layout.fillWidth: true
                background: Rectangle {
                    color: selectedIndex === 2 ? "darkblue" : "lightgray"
                    radius: 4
                }
                onClicked: selectedIndex = 2
            }
        }

        // StackLayout chứa các trang
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: selectedIndex

            Item {
                width: 300
                height: 200
                
                Layout.fillWidth: true

            GridLayout {
                id: grid
                columns: 4
                rowSpacing: 6
                columnSpacing: 12
                anchors.centerIn: parent

                // --- Hàng đầu tiên: tiêu đề ---
                Label {
                    text: "Thông số"
                    font.bold: true
                    color: "white"
                }
                Label {
                    text: "Giá trị"
                    font.bold: true
                    color: "white"
                }
                Label {
                    text: "Trạng thái"
                    font.bold: true
                    color: "white"
                }
                Label {
                    text: "Thông tin"
                    font.bold: true
                    color: "white"
                }

                // --- Hàng 2 ---
                Label { text: "Số lượng GPS"; color: "white" }
                Label { text: numberOfGPS; color: "white" }
                Label { text: "Bình thường"; color: "white" }
                Label { text: "Số lượng GPS bắt được càng nhiều thì vị trí máy bay sẽ hiển thị chính xác nhất"; color: "white"; wrapMode: Text.WordWrap }

                // --- Hàng 3 ---
                Label { text: "Trạng thái GPS"; color: "white" }
                Label { text: gpsStatus; color: "white" }
                Label { text: "Ổn định"; color: "white" }
                Label { text: "3D Lock hoặc 3D Fixed là trạng thái máy bay đã xác định được vị trí. Sẵn sàng để bay"; color: "white"; wrapMode: Text.WordWrap }

                // --- Hàng 4 ---
                Label { text: "Trạng thái pin"; color: "white" }
                Label { text: batteryVoltage; color: "white" }
                Label { text: "Ổn định"; color: "white" }
                Label { text: "Điện áp pin khi dưới 3.5vol/cell chuyến bay sẽ không an toàn. Sạc đầy pin trước khi bay!"; color: "white"; wrapMode: Text.WordWrap }

                // --- Hàng 5 ---
                Label { text: "Cảm biến tốc độ gió"; color: "white" }
                Label { text: "450 ppm"; color: "white" }
                Label { text: "Tốt"; color: "white" }
                Label { text: "Tốc độ cảm biến khi chưa bay thường là dao động từ 0-10km/h"; color: "white" ; wrapMode: Text.WordWrap }
            }
            }

            Rectangle {
                color: "transparent"
                Label {
                    anchors.centerIn: parent
                    text: "This is Page 2"
                }
            }

            Rectangle {
                color: "transparent"
                Label {
                    anchors.centerIn: parent
                    text: "This is Page 3"
                }
            }
        }
    }
}