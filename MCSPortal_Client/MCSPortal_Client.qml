import QtQuick 2.9
import QtQuick.Window 2.3
import "./ConnectionScreen"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("MCSPortal Client")

    ConnectionScreen {
        anchors.fill: parent
    }
}
