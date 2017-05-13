import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    property alias textCommand: textCommand
    property alias textOutput: textOutput
    property alias buttonRun: buttonRun
    property alias textStatus: textStatus
    property alias buttonTerminate: buttonTerminate

    property int commonSpacing: 5

    ColumnLayout {
        spacing: commonSpacing
        anchors.leftMargin: commonSpacing
        anchors.rightMargin: commonSpacing
        anchors.bottomMargin: commonSpacing
        anchors.topMargin: commonSpacing
        anchors.fill: parent

        RowLayout {
            spacing: commonSpacing

            Text {
                text: qsTr("Command:")
                anchors.verticalCenter: parent.verticalCenter
            }


            InputTextField {
                id: textCommand
                anchors.verticalCenter: parent.verticalCenter
                Layout.fillWidth: true
                placeholderText: qsTr("Enter command here.")
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
                 placeholderText: qsTr("No output.")
            }

            ScrollBar.vertical: ScrollBar {}
            ScrollBar.horizontal: ScrollBar {}
        }

        RowLayout {
            spacing: commonSpacing

            Text {
                anchors.bottom: parent.bottom
                text: qsTr("Status:")
            }
            Text {
                id: textStatus
                anchors.bottom: parent.bottom
                Layout.fillWidth: true
                text: qsTr("Not running.")
            }
            Button {
                id: buttonTerminate
                anchors.bottom: parent.bottom
                visible: false
                text: qsTr("Terminate")
            }
        }
    }
}
