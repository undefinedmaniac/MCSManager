import QtQuick 2.9
import QtQuick.Controls 2.2
import "../Style"


Item {
    id: root

    property alias font: field.font
    property alias border: background.border
    property alias backgroundColor: background.color
    property alias textColor: field.color

    property string highlightActiveColor: Style.highlight
    property string highlightInactiveColor: Style.border

    TextField {
        id: field

        anchors.fill: parent

        selectByMouse: true

        font.pixelSize: Style.textSizes

        background: Rectangle {
            id: background
            anchors.fill: parent
            color: Style.white
            border.width: 2
            border.color: parent.activeFocus ? highlightActiveColor : highlightInactiveColor
        }
    }
}
