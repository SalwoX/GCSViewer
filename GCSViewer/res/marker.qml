import QtQuick 2.0
import QtLocation 5.12

MapQuickItem {
    id: marker
    anchorPoint.x: marker.width / 2
    anchorPoint.y: marker.height
    sourceItem: Image {
        id: icon
        source: "file:/home/salwox/MuninnGCS/res/drone.png"
        sourceSize.width: 64
        sourceSize.height: 64
    }
}
