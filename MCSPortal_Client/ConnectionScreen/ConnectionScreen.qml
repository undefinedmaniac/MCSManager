import QtQuick 2.9
import "../Style"

Item {
    id: root

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.background

        MouseArea {
            anchors.fill: parent
            onClicked: focus = true
        }
    }

    SpecialTextField {
        width: 200
        height: 30
    }
}
