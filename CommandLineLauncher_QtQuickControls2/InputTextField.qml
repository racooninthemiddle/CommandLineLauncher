import QtQuick 2.4
import QtQuick.Controls 2.1

TextField {
    id: textField
    selectByMouse: true
    persistentSelection: true

    ContextMenuMouseArea {
        anchors.fill: parent
        menu: EditContextMenu { relatedTo: textField }
    }
}
