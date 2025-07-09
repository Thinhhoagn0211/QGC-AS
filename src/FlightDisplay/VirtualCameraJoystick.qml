/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick
import QGroundControl
import QGroundControl.ScreenTools
import QGroundControl.Controls
import QGroundControl.Palette
import QGroundControl.Vehicle

Item {
    id: virtualCameraJoysticks

    property var   _activeVehicle:            QGroundControl.multiVehicleManager.activeVehicle
    property var  gimbalController:             _activeVehicle ? _activeVehicle.gimbalController : undefined
    property bool gimbalAvailable: gimbalController != null && gimbalController !== undefined
    property bool  _initialConnectComplete:   _activeVehicle ? _activeVehicle.initialConnectComplete : false
    property real  leftYAxisValue:            autoCenterThrottle ? height / 2 : height
    property var   calibration:               false
    property var   uiTotalWidth
    property var   uiRealX

    Timer {
        id: gimbalJoystickTimer
        interval: 100
        repeat: true
        // running: true
        onTriggered: {
            if (gimbalController) {
                // These are [-1, 1] ranges
                let x = gimbalStick.xAxis
                let y = gimbalStick.yAxis

                // Apply some scaling if needed here, or send as-is
                gimbalController.gimbalOnScreenControl(x, y, false, true, true)
                console.log("Gimbal Joystick: xAxis: " + x + ", yAxis: " + y);
            }
        }
    }


    onHeightChanged:        { keepYAxisWhileChanged() }
    onWidthChanged:         { keepXAxisWhileChanged() }
    onCalibrationChanged:   { calibration ? calibrateJoysticks() : undefined }

    function calibrateJoysticks() {
        if( virtualCameraJoysticks.visible ) {
        keepXAxisWhileChanged()
        leftYAxisValue = gimbalStick.yAxisReCentered() // Keep track of the correct leftYAxisValue while the width is adjusted at first start up
        }
    }

    function keepYAxisWhileChanged () {
        if( virtualCameraJoysticks.visible ) {
            gimbalStick.resize( leftYAxisValue )
        }
    }

    function keepXAxisWhileChanged () {
        if( virtualCameraJoysticks.visible ) {
            gimbalStick.reCenter()
        }
    }

    JoystickThumbPad {
        id:                     gimbalStick
        anchors.leftMargin:     xPositionDelta
        anchors.bottomMargin:   -yPositionDelta
        anchors.left:           parent.left
        anchors.bottom:         parent.bottom
        width:                  parent.height
        height:                 parent.height
        yAxisPositiveRangeOnly: _activeVehicle && !_activeVehicle.rover && !leftHandedMode
        yAxisReCenter:          true
        onStickMoved: handleStickActivity()
    }

    function handleStickActivity() {
        if (Math.abs(gimbalStick.xAxis) > 0.01 || Math.abs(gimbalStick.yAxis) > 0.01) {
            gimbalJoystickTimer.start()
        } else {
            gimbalJoystickTimer.stop()
            if (gimbalController) {
                // Stop movement when stick released
                gimbalController.gimbalOnScreenControl(0, 0, false, true, true)
            }
        }
    }

}
