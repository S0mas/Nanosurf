import QtQuick 2.15
import QtGraphicalEffects 1.15

Item {
    property alias source: img.source
    signal clicked()
    property double nWidth: 0
    property double nHeight: 0

    width: nWidth*1.1
    height: nHeight*1.1

    Image {
        id: img
        anchors.centerIn: parent
        width: nWidth
        height: nHeight
        fillMode: Image.PreserveAspectFit
        layer.enabled: true
        layer.effect: ColorOverlay {
            color: area.containsMouse ? Qt.darker("#ea390d") : "#ea390d"
        }
    }
    MouseArea {
        id: area
        anchors.fill: parent
        onClicked: parent.clicked()
        hoverEnabled: true
    }
}
