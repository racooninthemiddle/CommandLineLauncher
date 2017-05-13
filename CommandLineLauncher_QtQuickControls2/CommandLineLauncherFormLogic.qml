import QtQuick 2.4

import CommandLineLauncherBackend 1.0

CommandLineLauncherFormDesign {
    CommandLineLauncherBackend {
        id: backend
    }

    Component.onCompleted: {
        textCommand.text = "ping -n 6 127.0.0.1"
        run()
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Return)
            run()
    }

    buttonRun.onClicked: {
        run()
    }

    function run() {
        if (backend.isRunning)
            return
        backend.start(textCommand.text)
    }

    Connections {
        target: backend
        onOutputChanged: {
            textOutput.text = backend.output
        }
        onStatusChanged: {
            textStatus.text = backend.statusDescription
            textOutput.text = backend.output

            var isRunning = backend.isRunning
            buttonRun.enabled = !isRunning

            if (isRunning && !buttonTerminate.visible && !terminateButtonTimer.running) {
                terminateButtonTimer.start()
            }
            else if (!isRunning) {
                buttonTerminate.visible = false
                terminateButtonTimer.stop()
            }
        }
    }

    Timer {
        id: terminateButtonTimer
        interval: 2000
        onTriggered: {
            if (backend.isRunning)
                buttonTerminate.visible = true
        }
    }

    buttonTerminate.onClicked: {
        backend.terminate()
    }
}
