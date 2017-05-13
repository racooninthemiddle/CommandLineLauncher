import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: "Command Line Launcher"

    CommandLineLauncherFormLogic {
        anchors.fill: parent
    }
}
