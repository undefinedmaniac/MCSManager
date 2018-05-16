import QtQuick 2.9
import QtQuick.Layouts 1.3
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

    ColumnLayout {
        id: textFieldLayout

        anchors.centerIn: parent

        RowLayout {
            Text {
                text: "Hostname / IP"
                color: Style.text
            }

            SpecialTextField {
                id: ipField
            }
        }

        RowLayout {
            Text {
                text: "Port"
                color: Style.text
            }

            SpecialTextField {
                id: portField
            }
        }
    }
}
