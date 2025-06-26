import QGroundControl.FlightDisplay

GuidedToolStripAction {
    text:       _guidedController.settingsTitle
    message:    qsTr("Settings")
    iconSource: "/res/setting.svg"
    visible:    true
    actionID:   _guidedController.actionSettings
}
