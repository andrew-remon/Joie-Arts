import QtQuick
import QtQuick.Controls

Slider {
    id: control

    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 6
        width: control.availableWidth
        height: implicitHeight
        radius: 3
        color: "#444"

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: "#883eaf"
            radius: 3
        }
    }


    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * control.availableWidth - width / 2
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 20
        implicitHeight: 20
        radius: 10
        color: "white"
        border.color: "#883eaf"
        border.width: 2
    }
}
