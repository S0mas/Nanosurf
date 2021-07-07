import QtQuick 2.15

Item {
    property int xOffset
    property int yOffset
    property QtObject target
    MouseArea {
        anchors.fill: parent
        property var clickPos
        onPressed: clickPos  = Qt.point(mouse.x+ xOffset,mouse.y + yOffset)
        onPositionChanged: {
            target.x = mousePosition.cursorPos().x - clickPos.x
            target.y = mousePosition.cursorPos().y - clickPos.y
        }
    }
}
