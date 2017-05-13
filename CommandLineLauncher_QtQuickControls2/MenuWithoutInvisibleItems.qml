import QtQuick 2.4
import QtQuick.Controls 2.1

Menu {
    readonly property int itemCount: contentItem.count

    onOpened: {
        for (var i = itemCount - 1; i >= 0; --i)
            if (itemAt(i).hasOwnProperty("visible") && !itemAt(i).visible)
                removeItem(i)
    }
}
