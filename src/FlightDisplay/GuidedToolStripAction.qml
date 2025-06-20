/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QGroundControl.Controls

ToolStripAction {
    property int    actionID
    property string message
    property string actionData
    property var _guidedController: globals.guidedControllerFlyView



    onTriggered: {
        _guidedController.closeAll()
        _guidedController.confirmAction(actionID)
    }
}
