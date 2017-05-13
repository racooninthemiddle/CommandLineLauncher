import QtQuick 2.4
import QtQuick.Controls 2.1

ContextMenu {
    MenuItem {
        text: qsTr("Cut")
        visible: !relatedTo.readOnly
        enabled: relatedTo.selectedText
        onTriggered: relatedTo.cut()
    }

    MenuItem {
        text: qsTr("Copy")
        enabled: relatedTo.selectedText
        onTriggered: relatedTo.copy()
    }

    MenuItem {
        text: qsTr("Paste")
        visible: !relatedTo.readOnly
        enabled: relatedTo.canPaste
        onTriggered: relatedTo.paste()
    }

    MenuSeparator {}

    MenuItem {
        text: qsTr("Select All")
        enabled: relatedTo.text
        onTriggered: relatedTo.selectAll()
    }
}
