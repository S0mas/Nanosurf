import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import QtQuick.Dialogs 1.3

Item {
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        spacing: 0
        ColumnLayout {
            spacing: 5
            Layout.maximumWidth: 200
            Image {
                Layout.preferredWidth: 200
                Layout.preferredHeight: 50
                fillMode: Image.PreserveAspectFit
                source: "qrc:/commonResources/img/logo.svg"
                opacity: 0.85
            }
            MyButton {
                id: loadDataButton
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                onClicked: fileDialog.open()
                text: "load data"
                opacity: 0.7
            }
            MyButton {
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                onClicked: backendController.filterData()
                text: "filter data"
                opacity: 0.7
            }
            Item {
                Layout.fillHeight: true
            }
        }
        Chart {
            Layout.fillWidth: true
            Layout.fillHeight: true
            opacity: 0.85
        }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: ["Csv data files (*.csv)"]
        onAccepted: {
            backendController.updateFileName(fileDialog.fileUrl)
            backendController.loadData()
        }
    }
}
