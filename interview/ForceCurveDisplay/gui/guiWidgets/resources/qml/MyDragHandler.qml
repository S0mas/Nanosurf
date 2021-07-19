import QtQuick 2.15

Item {
    property int xOffset
    property int yOffset
    MouseArea {
        anchors.fill: parent
        property var clickPos
        onPressed: clickPos  = Qt.point(mouse.x+ xOffset,mouse.y + yOffset)
        onPositionChanged: {
            positionSetter.updatePosition(mousePosition.cursorPos().x , mousePosition.cursorPos().y)
            //console.log(mousePosition.cursorPos().x + " " + clickPos.x)
            //console.log(mousePosition.cursorPos().y + " " + clickPos.y)
        }
    }
}
