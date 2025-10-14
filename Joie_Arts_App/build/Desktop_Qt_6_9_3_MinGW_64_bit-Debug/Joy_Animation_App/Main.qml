import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id:window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
            text: "Hello World"
            anchors.centerIn: parent
            onClicked: window.close()
    }
}
