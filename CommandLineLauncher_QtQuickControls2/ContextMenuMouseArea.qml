import QtQuick 2.4
import QtQuick.Controls 2.1

MouseArea {
    property Menu menu
    acceptedButtons: Qt.RightButton
    onClicked: menu.openAtPosition(mouseX, mouseY)
}
