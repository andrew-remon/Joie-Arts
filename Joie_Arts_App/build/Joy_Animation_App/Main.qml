import Joy_Animation_App
import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls.Fusion
import Qt.labs.platform as Platform
import QtQuick.Window

ApplicationWindow {
    Material.theme: Material.Dark
    property bool hovered : false
    property string currentOpenPanel: ""
    property bool cropModeActive: false

    id:window
    visibility: "Maximized"

    width: 1500
    height: 1000
    color: darkMode.checked ? "#121212" : "#f5f5f5"
    visible: true
    title: qsTr("Joie Arts")

    Filters_Class { id: filters }


    //===============Dialogs
    FileDialog {
        id: loadDialog
        title: "Select an image"
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]
        onAccepted: { filters.loadImage(selectedFile) }
    }
    Platform.FileDialog {
        id: saveDialog
        title: "Save Image as"
        fileMode: Platform.FileDialog.SaveFile
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]
        onAccepted: { filters.saveImage(file) }
    }
    FileDialog {
        id: mergeDialog
        title: "Select image to merge with"
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]
        onAccepted: {
            filters.loadSecondImage(selectedFile)
            currentOpenPanel = "merge"
        }
    }
    Dialog {
        id: resizeDialog
        title: "Resize Image"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 250
        height: 160
        anchors.centerIn: parent

        property int newWidth: 0
        property int newHeight: 0

        Column {
            anchors.centerIn: parent
            spacing: 10

            TextField {
                id: widthField
                placeholderText: "Enter width"
                inputMethodHints: Qt.ImhDigitsOnly
            }

            TextField {
                id: heightField
                placeholderText: "Enter height"
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }
        onAccepted: {
            newWidth = parseInt(widthField.text)
            newHeight = parseInt(heightField.text)
            if (!isNaN(newWidth) && !isNaN(newHeight)) {
                filters.resize(newWidth, newHeight)
            }
        }
    }

    //===============Top Bar
    Rectangle{
        id : top_bar
        color: darkMode.checked ? "#202020" : "#dddddd"
        height:60
        width: parent.width
        anchors.top: parent.top

        Row {
            id: appHeader
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing : 10
            padding : 10



            Image {
                source: "qrc:/assets/JA_Logo.svg"
                width: 60
                height: 60
                fillMode: Image.PreserveAspectFit

            }

            Label {
                id: appName
                text: "Joie Arts"
                color: darkMode.checked ? "white" : "black"
                font.bold: true
                font.pixelSize: 24
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                id: switchLabel
                text: darkMode.checked ? " ☾ " : " ☀ "
                color: darkMode.checked ? "white" : "black"
                font.pixelSize: 24

                anchors.verticalCenter: parent.verticalCenter

            }

            Switch {
                id: darkMode
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 7
                checked: true
                indicator: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 22
                    radius: 11
                    color: darkMode.checked ? "#883eaf" : "#888"
                    border.color: "#444"
                    Rectangle {
                        width: 18; height: 18
                        radius: 9
                        anchors.verticalCenter: parent.verticalCenter
                        x: darkMode.checked ? parent.width - width - 2 : 2
                        color: "white"
                        Behavior on x { NumberAnimation { duration: 150 } }
                    }
                }
                onToggled: window.color = checked ? "#121212" : "#f5f5f5"
            }
        }

        Row {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            spacing: 20

            Repeater {
                model: [
                    {label:"↶", action: function(){ filters.undo() }},
                    {label:"↷", action: function(){ filters.redo() }},
                    {label:"Open Image", action: function(){ loadDialog.open() }},
                    {label:"Reset", action: function(){ filters.reset() }},
                    {label:"Save Image", action: function(){ saveDialog.open() }},
                    {label:"Exit", action: function(){ window.close() } }
                ]
                delegate: Rectangle {
                    width: (modelData.label === "↶" || modelData.label === "↷") ? 40 : 100
                    height: (modelData.label === "↶" || modelData.label === "↷") ? 40 : 36
                    radius: (modelData.label === "↶" || modelData.label === "↷") ? width / 2 : 6

                    property bool hovered: false
                    color: modelData.label === "Exit" ? (hovered ? "#8B0000" : "#444") : (hovered ? "#883eaf" : "#444")
                    Text {
                        anchors.centerIn: parent
                        text: modelData.label
                        color: "white"
                        font.pixelSize: 14
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.hovered = true
                        onExited: parent.hovered = false
                        onClicked: modelData.action()
                    }
                }
            }
        }
    }


    //===============Bottom Bar
    Rectangle {
        id: bottomBar
        color: darkMode.checked ? "#333" : "#999999"
        height: 50
        width: parent.width
        anchors.bottom: parent.bottom
        z: 2

        Row {
            anchors.centerIn: parent
            spacing: 30
            Label { text: preview.source.toString().split("/").pop().split("?")[0]; color: darkMode.checked ? "#cccccc" : "#121212" }
            Label { text: preview.sourceSize.width + 'x'+ preview.sourceSize.height ; color: darkMode.checked ? "#cccccc" : "#121212" }
        }
    }
    //===============Closed pannels
    Rectangle {
        id: flipPanel
        width: parent.width
        height: 100
        color: darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            Repeater{
                model:[
                {label:"Flip Horizontal" ,action: function(){ filters.applyFlipFilter(1)}},
                {label:"Flip Vertical" ,action: function(){ filters.applyFlipFilter(2)}}
                ]
                delegate: Rectangle {
                    width:   100
                    height:  36
                    radius:  6

                    property bool hovered: false
                    color: (hovered ? "#883eaf" : "#444")
                    Text {
                        anchors.centerIn: parent
                        text: modelData.label
                        color: "white"
                        font.pixelSize: 14
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.hovered = true
                        onExited: parent.hovered = false
                        onClicked: modelData.action()
                    }
                }
        }
        }
        states: [ State { name: "open"; when: currentOpenPanel === "flip"; PropertyChanges { target: flipPanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }

    Rectangle {
        id: rotatePanel
        width: parent.width
        height: 100
        color:  darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            Repeater{
                model:[
                {label:"Rotate 90°" ,action: function(){ filters.applyRotatefilter(3) }},
                {label:"Rotate 180°" ,action: function(){ filters.applyRotatefilter(2)}},
                {label:"Rotate 270°" ,action: function(){ filters.applyRotatefilter(1)}}
                ]
                delegate: Rectangle {
                    width:   100
                    height:  36
                    radius:  6

                    property bool hovered: false
                    color: (hovered ? "#883eaf" : "#444")
                    Text {
                        anchors.centerIn: parent
                        text: modelData.label
                        color: "white"
                        font.pixelSize: 14
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.hovered = true
                        onExited: parent.hovered = false
                        onClicked: modelData.action()
                    }
                }
            }
        }
        states: [ State { name: "open"; when: currentOpenPanel === "rotate"; PropertyChanges { target: rotatePanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }

    Rectangle {
        id: mergePanel
        width: parent.width
        height: 100
        color: darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            Repeater{
                model:[
                {label:"Merge Overlaped Only" ,action: function(){ filters.applyMergeFilter(2) }},
                {label:"Merge Whole Picture" ,action: function(){ filters.applyMergeFilter(1) }}
                ]
                delegate: Rectangle {
                    width:   160
                    height:  36
                    radius:  6

                    property bool hovered: false
                    color: (hovered ? "#883eaf" : "#444")
                    Text {
                        anchors.centerIn: parent
                        text: modelData.label
                        color: "white"
                        font.pixelSize: 14
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.hovered = true
                        onExited: parent.hovered = false
                        onClicked: modelData.action()
                    }
                }
            }
        }
        states: [ State { name: "open"; when: currentOpenPanel === "merge"; PropertyChanges { target: mergePanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }

    Rectangle {
        id: brightnessPanel
        width: parent.width
        height: 100
        color: darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            Label {
                id: brightnessLabel
                text: "Brightness: " + brightnessCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider {
                id: brightnessCustomSlider
                from: 0.0
                to: 2.0
                value: 1.0
                stepSize: 0.1
                width: 120
                onValueChanged: brightnessLabel.text = "Brightness: " + value.toFixed(1)
                onPressedChanged: if (!pressed) filters.applyDarkenOrLighten(value)
            }
            Label {
                id: gammaLabel
                text: "Gamma: " + gammaCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider {
                id: gammaCustomSlider
                from: 0.0
                to: 2.0
                value: 1.0
                stepSize: 0.1
                width: 120
                onValueChanged: gammaLabel.text = "Gamma: " + value.toFixed(1)
                onPressedChanged: if (!pressed) filters.applyGamma(value)
            }
            Label {
                id: contrastLabel
                text: "Contrast: " + contrastCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider {
                id: contrastCustomSlider
                from: 0.0
                to: 2.0
                value: 1.0
                stepSize: 0.1
                width: 120
                onValueChanged: contrastLabel.text = "Contrast: " + value.toFixed(1)
                onPressedChanged: if (!pressed) filters.applyContrast(value)
            }
            Label {
                id: noiseLabel
                text: "Noise: " + noiseCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider {
                id: noiseCustomSlider
                from: 0.0
                to: 100
                value: 0
                stepSize: 1
                width: 120
                onValueChanged: noiseLabel.text = "Noise: " + value.toFixed(1)
                onPressedChanged: if (!pressed) filters.applyNoise(value)
            }
            Label {
                id: vignetteLabel
                text: "Vignette: " + vignetteCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider {
                id: vignetteCustomSlider
                from: 0.0
                to: 2.0
                value: 0
                stepSize: 0.1
                width: 120
                onValueChanged: vignetteLabel.text = "Vignette: " + value.toFixed(1)
                onPressedChanged: if (!pressed) filters.applyVignette(value)
            }
        }

        states: [ State { name: "open"; when: currentOpenPanel === "Brightness"; PropertyChanges { target: brightnessPanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }

    Rectangle {
        id: framePanel
        width: parent.width
        height: 100
        color: darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        property int frameType: 0;
        property int frameR: 128;
        property int frameG: 128;
        property int frameB: 128;

        ColorDialog {
            id: colorDialog
            title: "Please select a color"
            onAccepted: {
                var chosenColor = colorDialog.selectedColor;
                framePanel.frameR = Math.round(chosenColor.r * 255);
                framePanel.frameG = Math.round(chosenColor.g * 255);
                framePanel.frameB = Math.round(chosenColor.b * 255);
            }
        }
        ButtonGroup {
                id: filterGroup
                exclusive: true
            }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            RadioButton{id:frame1 ;text: "Normal Frame"; ButtonGroup.group: filterGroup; onClicked: {if (checked) {framePanel.frameType = 1}}}
            RadioButton{id:frame3 ;text: "Double Frame"; ButtonGroup.group: filterGroup; onClicked: {if (checked) {framePanel.frameType = 3}}}
            RadioButton{id:frame2 ;text: "Film Filter"; ButtonGroup.group: filterGroup; onClicked: {if (checked) {framePanel.frameType = 2}}}
            Label {
                visible: (frame1.checked || frame3.checked) ? true : false
                id: thicknessLabel
                text: (frame3.checked) ? "Outer Thickness: " + thicknessCustomSlider.value.toFixed(1) : "Thickness: " + thicknessCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider{visible: (frame1.checked || frame3.checked) ? true : false ;id: thicknessCustomSlider ; from: 0.0 ; to: 50 ; value: 0 ; stepSize: 1 ; width: 120 }
            Label {
                visible: frame3.checked
                id: outerThicknessLabel
                text: "Inner Thickness: " + innerThicknessCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider{visible: (frame3.checked) ? true : false ;id: innerThicknessCustomSlider ; from: 0.0 ; to: 50 ; value: 0 ; stepSize: 1 ; width: 120 }
            Label {
                visible: frame3.checked
                id: gapLabel
                text: "Gap: " + gapCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }
            CustomSlider{visible: (frame3.checked) ? true : false ;id: gapCustomSlider ; from: 0.0 ; to: 50 ; value: 0 ; stepSize: 1 ; width: 120 }
            Rectangle {id: colorDisplay
                visible: (frame1.checked || frame3.checked) ? true : false
                width: 36
                height: 36
                radius: 4
                color: Qt.rgba(framePanel.frameR / 255, framePanel.frameG / 255, framePanel.frameB / 255, 1)
                border.color: "#333" }
            Rectangle {
                width: 100
                height: 36
                radius: 6

                visible: frame1.checked || frame3.checked

                property bool hovered: false
                color: (hovered ? "#883eaf" : "#444")

                Text {
                    anchors.centerIn: parent
                    text: "Color Picker"
                    color: "white"
                    font.pixelSize: 14
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.hovered = true
                    onExited: parent.hovered = false
                    onClicked: {
                        colorDialog.open()
                    }
                }
            }

            Rectangle {
                width: 100
                height: 36
                radius: 6


                property bool hovered: false
                color: (hovered ? "#883eaf" : "#444")

                Text {
                    anchors.centerIn: parent
                    text: "Apply Frame"
                    color: "white"
                    font.pixelSize: 14
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.hovered = true
                    onExited: parent.hovered = false
                    onClicked: {
                        filters.applyFrame(framePanel.frameType, thicknessCustomSlider.value, innerThicknessCustomSlider.value, gapCustomSlider.value, framePanel.frameR, framePanel.frameG, framePanel.frameB)
                    }
                }
            }
        }
        states: [ State { name: "open"; when: currentOpenPanel === "frame"; PropertyChanges { target: framePanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }

    Rectangle {
        id: skewPanel
        width: parent.width
        height: 100
        color: darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            Label {
                id: skewnessLabel
                text: "Skewness: " + skewnessCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                }
            CustomSlider{id: skewnessCustomSlider ; from: -89 ; to: 89 ; value: 0 ; stepSize: 1 ; width: 120
                onValueChanged: skewnessLabel.text = "Skewness: " + value.toFixed(1)
                onPressedChanged: if (!pressed) filters.skewImage(value)
            }
        }
        states: [ State { name: "open"; when: currentOpenPanel === "skew"; PropertyChanges { target: skewPanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }

    Rectangle {
        id: huePanel
        width: parent.width
        height: 100
        color: darkMode.checked ? "#2b2b2b" : "#7c7c7c"
        radius: 12
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height
        z: 1
        property int r;
        property int g;
        property int b;
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            padding: 12
            Label {
                id: redHueLabel
                text: "Red: " + redCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                }
            CustomSlider{id: redCustomSlider ; from: 0 ; to: 255 ; value: 0 ; stepSize: 1 ; width: 120
                onValueChanged: redHueLabel.text = "Red: " + value.toFixed(1)
                onPressedChanged: if (!pressed) (huePanel.r = redCustomSlider.value)
            }
            Label {
                id: greenHueLabel
                text: "Green: " + greenCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                }
            CustomSlider{id: greenCustomSlider ; from: 0 ; to: 255 ; value: 0 ; stepSize: 1 ; width: 120
                onValueChanged: greenHueLabel.text = "Green: " + value.toFixed(1)
                onPressedChanged: if (!pressed) (huePanel.g= greenCustomSlider.value)
            }
            Label {
                id: blueHueLabel
                text: "Blue: " + blueCustomSlider.value.toFixed(1)
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                }
            CustomSlider{id: blueCustomSlider ; from: 0 ; to: 255 ; value: 0 ; stepSize: 1 ; width: 120
                onValueChanged: blueHueLabel.text = "Blue: " + value.toFixed(1)
                onPressedChanged: if (!pressed) (huePanel.b= blueCustomSlider.value)
            }
            Rectangle {
                width: 160
                height: 36
                radius: 6

                property bool hovered: false
                color: (hovered ? "#883eaf" : "#444")

                Text {
                    anchors.centerIn: parent
                    text: "Apply Hue Change"
                    color: "white"
                    font.pixelSize: 14
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.hovered = true
                    onExited: parent.hovered = false
                    onClicked: {
                        filters.applyHue(huePanel.r,huePanel.g,huePanel.b)
                    }
                }
            }

        }
        states: [ State { name: "open"; when: currentOpenPanel === "hue"; PropertyChanges { target: huePanel; y: parent.height - height - 10 } } ]
        transitions: [
            Transition { from: ""; to: "open"; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.OutCubic } },
            Transition { from: "open"; to: ""; NumberAnimation { properties: "y"; duration: 300; easing.type: Easing.InCubic } }
        ]
    }


    //===============Right Panel
    ColumnLayout {
        id: rightPanel
        anchors.bottom: bottomBar.top
        anchors.right: parent.right
        Layout.preferredWidth: 300
        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: Qt.rgba(0, 0, 0, 0)
            Label {
                text: "Adjustments"
                color: "white"
            }
        }
    }
    //===============Left Panel
    Rectangle {
        id: leftPanel
        anchors.top: top_bar.bottom
        anchors.left: parent.left
        anchors.bottom: bottomBar.top
        width: 250
        color: darkMode.checked ? "#252525" : "#aaaaaa"
        z: 0

        property var panelButtonsModel: [
            {label:"Crop",       action: function() { cropModeActive = !cropModeActive }},
            {label:"Resize",     action: function(){ resizeDialog.open() }},
            {label:"Flip",       action: function() { currentOpenPanel = (currentOpenPanel === "flip" ? "" : "flip") }},
            {label:"Rotate",     action: function() { currentOpenPanel = (currentOpenPanel === "rotate" ? "" : "rotate") }},
            {label:"Frame",      action: function() { currentOpenPanel = (currentOpenPanel === "frame" ? "" : "frame") }},
            {label:"Skew",       action: function() { currentOpenPanel = (currentOpenPanel === "skew" ? "" : "skew") }},
            {label:"Hue Options",action: function() { currentOpenPanel = (currentOpenPanel === "hue" ? "" : "hue") }},
            {label:"Edit Photo", action: function() { currentOpenPanel = (currentOpenPanel === "Brightness" ? "" : "Brightness") }}
        ]

        property var filterButtonsModel: [
            {label:"Black & White", action: function(){ filters.applyBnW() }},
            {label:"Invert",        action: function(){ filters.applyInvert() }},
            {label:"Blur",          action: function(){ filters.applyBlur() }},
            {label:"Merge",         action: function(){ mergeDialog.open() }},
            {label:"Cel Shading",   action: function(){ filters.applyToonyEffect()}},
            {label:"Midnight",      action: function(){ filters.applyNightyeffect() }},
            {label:"Detect Edge",   action: function(){ filters.applyEdgeDetetction()}},
            {label:"Oil Paint",     action: function(){ filters.applyOilFilter() }},
            {label:"Emboss",        action: function(){ filters.applyEmboss()}},
            {label:"Pixelate",     action: function(){ filters.applyPixelArt() }},
            {label:"Fish Eye",      action: function(){ filters.applyFishEye() }},
            {label:"Purplize",      action: function(){ filters.applyMidNight() }},
            {label:"Glitch",        action: function(){ filters.applyGlitch() }},
            {label:"Sharpen",       action: function(){ filters.sharpen() }},
            {label:"Gray Scale",    action: function(){ filters.applyGrayscale()} },
            {label:"Sunlight",      action: function(){ filters.applyNaturalSunlight() }},
            {label:"InfraRed",      action: function(){ filters.applyInfraRed() }},
            {label:"TV Static",     action: function(){ filters.applyTVstatic() }}
        ]

        ColumnLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            spacing: 15

            Label {
                text: "Direct Filters"
                font.bold: true
                color: darkMode.checked ? "#cccccc" : "#121212"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }
            Rectangle {
                height: 1
                color: "#555"
                Layout.fillWidth: true
                Layout.bottomMargin: 5
            }

            GridLayout {
                Layout.alignment: Qt.AlignHCenter
                columns: 2
                columnSpacing: 10
                rowSpacing: 10
                Repeater {
                    model: leftPanel.filterButtonsModel
                    delegate: Rectangle {
                        implicitWidth: 100
                        height: 36
                        radius: 6
                        property bool hovered: false
                        color: hovered ? "#883eaf" : "#444"
                        Text { anchors.centerIn: parent; text: modelData.label; color: "white"; font.pixelSize: 14 }
                        MouseArea { anchors.fill: parent; hoverEnabled: true; onEntered: parent.hovered = true; onExited: parent.hovered = false; onClicked: { modelData.action(); } }
                    }
                }
            }

            Label {
                text: "Panels"
                font.bold: true
                color: darkMode.checked ? "#cccccc" : "#121212"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                Layout.topMargin: 20
            }
            Rectangle {
                height: 1
                color: "#555"
                Layout.fillWidth: true
                Layout.bottomMargin: 5
            }

            GridLayout {
                Layout.alignment: Qt.AlignHCenter
                columns: 2
                columnSpacing: 10
                rowSpacing: 10
                Repeater {
                    model: leftPanel.panelButtonsModel
                    delegate: Rectangle {
                        implicitWidth: 100
                        height: 36
                        radius: 6
                        property bool hovered: false
                        color: hovered ? "#883eaf" : "#444"
                        Text { anchors.centerIn: parent; text: modelData.label; color: "white"; font.pixelSize: 14 }
                        MouseArea { anchors.fill: parent; hoverEnabled: true; onEntered: parent.hovered = true; onExited: parent.hovered = false; onClicked: { modelData.action(); } }
                    }
                }
            }
        }
    }



    //===============Image Preview
    Rectangle {
        id: imageArea
        color: "#303030"
        radius: 8
        anchors.right: parent.right
        anchors.top: top_bar.bottom
        anchors.left: leftPanel.right
        anchors.bottom: bottomBar.top
        anchors.margins: 10
        anchors.bottomMargin: 70
        height: parent.height * 0.6
        width: parent.width * 0.70
        z:4
        Image {
            id: preview
            anchors.centerIn: parent
            width: parent.width * 0.95
            height: parent.height * 0.95
            fillMode: Image.PreserveAspectFit
            source: filters.imageSource
        }


       Rectangle {
               id: cropOverlay
               anchors.fill: preview
               color: "transparent"
               visible: cropModeActive
               z: 12


               Rectangle {
                   id: cropBox
                   x: parent.width / 4
                   y: parent.height / 4
                   width: parent.width / 2
                   height: parent.height / 2
                   color: "transparent"
                   border.color: "white"
                   border.width: 2


                   MouseArea {
                       anchors.fill: parent
                       cursorShape: pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor
                       drag.target: cropBox
                       drag.minimumX: 0
                       drag.minimumY: 0
                       drag.maximumX: cropOverlay.width - cropBox.width
                       drag.maximumY: cropOverlay.height - cropBox.height
                   }


                   Repeater {
                       model: 2
                       delegate: Rectangle {

                           x: (cropBox.width / 3) * (index + 1)
                           width: 1
                           height: cropBox.height
                           color: "#ffffff80"
                       }
                   }
                   Repeater {
                       model: 2
                       delegate: Rectangle {

                           y: (cropBox.height / 3) * (index + 1)
                           width: cropBox.width
                           height: 1
                           color: "#ffffff80"
                       }
                   }


                   Repeater {
                       model: [
                           { name: "tl", cursor: Qt.SizeFDiagCursor, hAnchor: "left", vAnchor: "top"},
                           { name: "tr", cursor: Qt.SizeBDiagCursor, hAnchor: "right", vAnchor: "top"},
                           { name: "bl", cursor: Qt.SizeBDiagCursor, hAnchor: "left", vAnchor: "bottom"},
                           { name: "br", cursor: Qt.SizeFDiagCursor, hAnchor: "right", vAnchor: "bottom"}
                       ]
                       delegate: Rectangle {
                           id: handle
                           width: 12; height: 12
                           radius: 6
                           color: "white"
                           anchors.horizontalCenter: cropBox[modelData.hAnchor]
                           anchors.verticalCenter: cropBox[modelData.vAnchor]

                           MouseArea {
                               anchors.fill: parent
                               anchors.margins: -4
                               cursorShape: modelData.cursor
                               property point dragStart: Qt.point(0, 0)
                               property point boxStart: Qt.point(0, 0)
                               property size boxSize: Qt.size(0, 0)

                               onPressed: {
                                   dragStart = mapToItem(cropOverlay, mouseX, mouseY)
                                   boxStart = Qt.point(cropBox.x, cropBox.y)
                                   boxSize = Qt.size(cropBox.width, cropBox.height)
                               }

                               onPositionChanged: {
                                   var currentPos = mapToItem(cropOverlay, mouseX, mouseY)
                                   var dx = currentPos.x - dragStart.x
                                   var dy = currentPos.y - dragStart.y

                                   var newX = boxStart.x
                                   var newY = boxStart.y
                                   var newW = boxSize.width
                                   var newH = boxSize.height

                                   if (modelData.hAnchor === "left") {
                                       newX = Math.min(boxStart.x + dx, boxStart.x + boxSize.width - 20)
                                       newW = Math.max(20, boxSize.width - (newX - boxStart.x))
                                   } else { // right
                                       newW = Math.max(20, boxSize.width + dx)
                                   }

                                   if (modelData.vAnchor === "top") {
                                       newY = Math.min(boxStart.y + dy, boxStart.y + boxSize.height - 20)
                                       newH = Math.max(20, boxSize.height - (newY - boxStart.y))
                                   } else { // bottom
                                       newH = Math.max(20, boxSize.height + dy)
                                   }

                                   cropBox.x = newX
                                   cropBox.y = newY
                                   cropBox.width = newW
                                   cropBox.height = newH
                               }
                           }
                       }
                   }
               }
               Row {
                   anchors.bottom: cropOverlay.bottom
                   anchors.horizontalCenter: cropOverlay.horizontalCenter
                   anchors.bottomMargin: 20
                   spacing: 15


                   Rectangle {
                       width: 100
                       height: 36
                       radius: 6

                       property bool hovered: false
                       color: (hovered ? "#883eaf" : "#444")

                       Text {
                           anchors.centerIn: parent
                           text: "Confirm Crop"
                           color: "white"
                           font.pixelSize: 14
                       }
                       MouseArea {
                           anchors.fill: parent
                           hoverEnabled: true
                           onEntered: parent.hovered = true
                           onExited: parent.hovered = false
                           onClicked: {
                            var scaleRatioX = preview.sourceSize.width / preview.paintedWidth
                            var scaleRatioY = preview.sourceSize.height / preview.paintedHeight

                            var offsetX = (preview.width - preview.paintedWidth) / 2
                            var offsetY = (preview.height - preview.paintedHeight) / 2

                            var cropX = (cropBox.x - offsetX) * scaleRatioX
                            var cropY = (cropBox.y - offsetY) * scaleRatioY
                            var cropW = cropBox.width * scaleRatioX
                            var cropH = cropBox.height * scaleRatioY


                            filters.crop(cropX, cropY, cropW, cropH)


                            cropModeActive = false
                           }
                       }
                   }
                   Rectangle {
                   width: 100
                   height: 36
                   radius: 6



                   property bool hovered: false
                   color: (hovered ? "#883eaf" : "#444")

                   Text {
                       anchors.centerIn: parent
                       text: "Cancel"
                       color: "white"
                       font.pixelSize: 14
                   }
                   MouseArea {
                       anchors.fill: parent
                       hoverEnabled: true
                       onEntered: parent.hovered = true
                       onExited: parent.hovered = false
                       onClicked: {
                           cropModeActive = false
                        }
                    }
                }
            }
        }
    }
}

