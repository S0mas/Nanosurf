import QtQuick 2.15

Item {
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.95
        Rectangle {
            width: parent.width - 40
            height: parent.height - 50
            anchors.centerIn: parent
            color: "transparent"
            border.width: 1
            border.color: colors.mainOrange
            opacity: 0.85
        }
    }
}
