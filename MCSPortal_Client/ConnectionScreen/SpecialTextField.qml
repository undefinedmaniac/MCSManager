import QtQuick 2.9
import QtQuick.Controls 2.2
import "../Style"

TextField {
    id: root

    property alias border: background.border
    property alias backgroundColor: background.color

    property string highlightActiveColor: Style.highlight
    property string highlightInactiveColor: Style.border

    implicitWidth: 200
    implicitHeight: 30

    selectByMouse: true
    color: Style.text

    font.pixelSize: Style.textSize

    background: Rectangle {
        id: background
        anchors.fill: parent
        color: Style.element
        border.width: 2
        border.color: parent.activeFocus ? highlightActiveColor : highlightInactiveColor
    }
}
