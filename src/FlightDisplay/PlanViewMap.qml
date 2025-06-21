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
import QtLocation
import QtPositioning
import QtQuick.Dialogs
import QtQuick.Layouts

import QGroundControl
import QGroundControl.Controllers
import QGroundControl.Controls
import QGroundControl.FlightDisplay
import QGroundControl.FlightMap
import QGroundControl.Palette
import QGroundControl.ScreenTools
import QGroundControl.Vehicle
import QGroundControl.UTMSP

FlightMap {
    id:            editorMap
    anchors.fill:               parent
    mapName:                    "MissionEditor"
    allowGCSLocationCenter:     true
    allowVehicleLocationCenter: true
    planView:                   true

    zoomLevel:                  QGroundControl.flightMapZoom
    center:                     QGroundControl.flightMapPosition

    // This is the center rectangle of the map which is not obscured by tools
    property rect centerViewport:   Qt.rect(_leftToolWidth + _margin,  _margin, editorMap.width - _leftToolWidth - _rightToolWidth - (_margin * 2), (terrainStatus.visible ? terrainStatus.y : height - _margin) - _margin)

    property real _leftToolWidth:       toolStrip.x + toolStrip.width
    property real _rightToolWidth:      rightPanel.width + rightPanel.anchors.rightMargin
    property real _nonInteractiveOpacity:  0.5

    // Initial map position duplicates Fly view position
    Component.onCompleted: editorMap.center = QGroundControl.flightMapPosition

    QGCMapPalette { id: mapPal; lightColors: editorMap.isSatelliteMap }

    onZoomLevelChanged: {
        QGroundControl.flightMapZoom = editorMap.zoomLevel
    }
    onCenterChanged: {
        QGroundControl.flightMapPosition = editorMap.center
    }

    onMapClicked: (mouse) => {
        // Take focus to close any previous editing
        editorMap.focus = true
        if (!mainWindow.allowViewSwitch()) {
            return
        }
        var coordinate = editorMap.toCoordinate(Qt.point(mouse.x, mouse.y), false /* clipToViewPort */)
        coordinate.latitude = coordinate.latitude.toFixed(_decimalPlaces)
        coordinate.longitude = coordinate.longitude.toFixed(_decimalPlaces)
        coordinate.altitude = coordinate.altitude.toFixed(_decimalPlaces)
        if(_utmspEnabled){
            QGroundControl.utmspManager.utmspVehicle.updateLastCoordinates(coordinate.latitude, coordinate.longitude)
        }
        
        switch (_editingLayer) {
        case _layerMission:
            if (addWaypointRallyPointAction.checked) {
                insertSimpleItemAfterCurrent(coordinate)
            } else if (_addROIOnClick) {
                insertROIAfterCurrent(coordinate)
                _addROIOnClick = false
            }

            break
        case _layerRallyPoints:
            if (_rallyPointController.supported && addWaypointRallyPointAction.checked) {
                _rallyPointController.addPoint(coordinate)
            }
            break

        case _layerUTMSP:
            if (addWaypointRallyPointAction.checked) {
                insertSimpleItemAfterCurrent(coordinate)
            } else if (_addROIOnClick) {
                insertROIAfterCurrent(coordinate)
                _addROIOnClick = false
            }
            break
        }
    }

    // Add the mission item visuals to the map
    Repeater {
        model: _missionController.visualItems
        delegate: MissionItemMapVisual {
            map:         editorMap
            opacity:     _editingLayer == _layerMission || _editingLayer == _layerUTMSP ? 1 : editorMap._nonInteractiveOpacity
            interactive: _editingLayer == _layerMission || _editingLayer == _layerUTMSP
            vehicle:     _planMasterController.controllerVehicle
            onClicked:   (sequenceNumber) => { _missionController.setCurrentPlanViewSeqNum(sequenceNumber, false) }
        }
    }

    // Add lines between waypoints
    MissionLineView {
        showSpecialVisual:  _missionController.isROIBeginCurrentItem
        model:              _missionController.simpleFlightPathSegments
        opacity:            _editingLayer == _layerMission ||  _editingLayer == _layerUTMSP  ? 1 : editorMap._nonInteractiveOpacity
    }

    // Direction arrows in waypoint lines
    MapItemView {
        model: _editingLayer == _layerMission ||_editingLayer == _layerUTMSP ? _missionController.directionArrows : undefined

        delegate: MapLineArrow {
            fromCoord:      object ? object.coordinate1 : undefined
            toCoord:        object ? object.coordinate2 : undefined
            arrowPosition:  3
            z:              QGroundControl.zOrderWaypointLines + 1
        }
    }

    // Incomplete segment lines
    MapItemView {
        model: _missionController.incompleteComplexItemLines

        delegate: MapPolyline {
            path:       [ object.coordinate1, object.coordinate2 ]
            line.width: 1
            line.color: "red"
            z:          QGroundControl.zOrderWaypointLines
            opacity:    _editingLayer == _layerMission ? 1 : editorMap._nonInteractiveOpacity
        }
    }

    // UI for splitting the current segment
    MapQuickItem {
        id:             splitSegmentItem
        anchorPoint.x:  sourceItem.width / 2
        anchorPoint.y:  sourceItem.height / 2
        z:              QGroundControl.zOrderWaypointLines + 1
        visible:        _editingLayer == _layerMission ||  _editingLayer == _layerUTMSP

        sourceItem: SplitIndicator {
            onClicked:  _missionController.insertSimpleMissionItem(splitSegmentItem.coordinate,
                                                                    _missionController.currentPlanViewVIIndex,
                                                                    true /* makeCurrentItem */)
        }

        function _updateSplitCoord() {
            if (_missionController.splitSegment) {
                var distance = _missionController.splitSegment.coordinate1.distanceTo(_missionController.splitSegment.coordinate2)
                var azimuth = _missionController.splitSegment.coordinate1.azimuthTo(_missionController.splitSegment.coordinate2)
                splitSegmentItem.coordinate = _missionController.splitSegment.coordinate1.atDistanceAndAzimuth(distance / 2, azimuth)
            } else {
                coordinate = QtPositioning.coordinate()
            }
        }

        Connections {
            target:                 _missionController
            function onSplitSegmentChanged()  { splitSegmentItem._updateSplitCoord() }
        }

        Connections {
            target:                 _missionController.splitSegment
            function onCoordinate1Changed()   { splitSegmentItem._updateSplitCoord() }
            function onCoordinate2Changed()   { splitSegmentItem._updateSplitCoord() }
        }
    }

    // Add the vehicles to the map
    MapItemView {
        model: QGroundControl.multiVehicleManager.vehicles
        delegate: VehicleMapItem {
            vehicle:        object
            coordinate:     object.coordinate
            map:            editorMap
            size:           ScreenTools.defaultFontPixelHeight * 3
            z:              QGroundControl.zOrderMapItems - 1
        }
    }

    GeoFenceMapVisuals {
        map:                    editorMap
        myGeoFenceController:   _geoFenceController
        interactive:            _editingLayer == _layerGeoFence
        homePosition:           _missionController.plannedHomePosition
        planView:               true
        opacity:                _editingLayer != _layerGeoFence ? editorMap._nonInteractiveOpacity : 1
    }

    RallyPointMapVisuals {
        map:                    editorMap
        myRallyPointController: _rallyPointController
        interactive:            _editingLayer == _layerRallyPoints
        planView:               true
        opacity:                _editingLayer != _layerRallyPoints ? editorMap._nonInteractiveOpacity : 1
    }

    UTMSPMapVisuals {
        id: utmspvisual
        enabled:                _utmspEnabled
        map:                    editorMap
        currentMissionItems:    _visualItems
        myGeoFenceController:   _geoFenceController
        interactive:            _editingLayer == _layerUTMSP
        homePosition:           _missionController.plannedHomePosition
        planView:               true
        opacity:                _editingLayer != _layerUTMSP ? editorMap._nonInteractiveOpacity : 1
        resetCheck:             _resetGeofencePolygon
    }

    Connections {
        target: utmspEditor
        function onResetGeofencePolygonTriggered() {
            resetTimer.start()
        }
    }
    Timer {
        id: resetTimer
        interval: 2500
        running: false
        repeat: false
        onTriggered: {
            _resetGeofencePolygon = true
        }
    }
}