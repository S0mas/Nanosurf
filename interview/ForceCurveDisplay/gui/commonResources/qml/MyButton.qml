import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: control
    font.pointSize: 14
    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? Qt.darker(colors.mainOrange) : colors.mainOrange
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        border.color: control.down ? Qt.darker(colors.mainOrange) : colors.mainOrange
        border.width: 1
        radius: 2
        color: control.hovered ? "#202020" : "#303030"
    }
}
