import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Window 2.0
import QtQml 2.0
import Qt.labs.location 1.0
import database.package.qml 1.0

Rectangle {
    id: rectangle

    width: Screen.width
    height: Screen.height
    visible: true

    property double lat: db.getLat()
    property double lon: db.getLon()

    property var item
    property double latIcon
    property double lonIcon

    DatabasePackage {
        id: db
    }

    Plugin {
        id: mapPlugin
        name: "mapboxgl"
    }

    function addMarker(latitude, longitude) {
        var Component = Qt.createComponent("qrc:/marker.qml")
        item = Component.createObject(rectangle, {
                                          "coordinate": QtPositioning.coordinate(
                                                            latitude, longitude)
                                      })

        map.addMapItem(item)
    }

    Map {

        MapCircle {
            id: circle
            color: 'green'
            border.width: 3
            radius: 100
        }

        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(lat, lon)
        zoomLevel: 12
        Timer {
            interval: 1000
            repeat: true
            running: true
            onTriggered: {

            }
        }

        Timer {
            repeat: true
            running: true
            interval: 1000
            onTriggered: {
                circle.center = QtPositioning.coordinate(db.getLat(), db.getLon())
                map.removeMapItem(item)
                latIcon = db.getLat()
                lonIcon = db.getLon()

                addMarker(latIcon, lonIcon)
            }
        }
    }
}
