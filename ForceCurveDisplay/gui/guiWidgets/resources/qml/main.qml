import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import "../../commonResources/qml"

Item {
    id: mainWindow
    width: 1200
    height: 600
    opacity: 0

    BackgroundWindow {
        id: background
        anchors.fill: parent
        MyDragHandler {
            width: parent.width
            height: parent.height/9
            ButtonImage {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: 5
                anchors.rightMargin: 5
                nWidth: 12
                nHeight: 12
                source: "qrc:/commonResources/img/cross.png"
                onClicked: Qt.quit()
                opacity: 0.7
            }
        }
    }

    AppView {
        id: view
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 30
        anchors.bottomMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
    }

    Colors {
        id: colors
    }

    Behavior on opacity { NumberAnimation { duration: 1000 } }
    Component.onCompleted: opacity = 1
}

