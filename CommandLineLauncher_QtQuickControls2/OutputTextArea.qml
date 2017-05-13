import QtQuick 2.4
import QtQuick.Controls 2.1

TextArea {
    id: textArea
    readOnly: true
    selectByMouse: true

    ContextMenuMouseArea {
        anchors.fill: parent
        menu: EditContextMenu { relatedTo: textArea }
    }
}
