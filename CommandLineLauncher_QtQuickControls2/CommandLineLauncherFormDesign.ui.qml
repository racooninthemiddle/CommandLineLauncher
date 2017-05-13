import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 400
    height: 400
    antialiasing: false
    opacity: 1
    visible: true

    property alias textCommand: textCommand
    property alias textOutput: textOutput
    property alias buttonRun: buttonRun
    property alias textStatus: textStatus
    property alias buttonTerminate: buttonTerminate

    ColumnLayout {
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent

        RowLayout {
            height: 100
            Layout.fillHeight: false
            Layout.fillWidth: true
            Layout.minimumWidth: 1
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            Text {
                text: qsTr("Command:")
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }
            InputTextField {
                id: textCommand
                Layout.fillWidth: true
            }
            Button {
                id: buttonRun
                text: qsTr("Run")
                anchors.verticalCenter: parent.verticalCenter
            }
        }


        Flickable {
            Layout.fillHeight: true
            Layout.fillWidth: true

            TextArea.flickable: OutputTextArea {
                id: textOutput
            }

            ScrollBar.vertical: ScrollBar {
            }
            ScrollBar.horizontal: ScrollBar {
            }
        }

        RowLayout {
            Layout.fillWidth: true
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: qsTr("Status: ")
                anchors.bottom: parent.bottom
            }
            Text {
                id: textStatus
                text: qsTr("Not running.")
                Layout.fillWidth: true
                anchors.bottom: parent.bottom
            }
            Button {
                id: buttonTerminate
                text: qsTr("Terminate")
                visible: false
            }
        }
    }
}
