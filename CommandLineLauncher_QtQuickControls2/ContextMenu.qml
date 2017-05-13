import QtQuick 2.4
import QtQuick.Controls 2.1

MenuWithoutInvisibleItems {
    property Item relatedTo

    function openAtPosition(xPos, yPos) {
        x = xPos
        y = yPos
        open()
    }

    onClosed: relatedTo.forceActiveFocus()
}
