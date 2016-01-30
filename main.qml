import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 550
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Grid {
        columns: 5
        rows: 5
        anchors.centerIn: parent
        Repeater {
            model: game.board
            Rectangle {
                id: slot
                width: 100
                height: 100
                border.width: 1
                color: "white"
                Text {
                    anchors.centerIn: parent
                    text: modelData
                    fontSizeMode: Text.Fit
                    font.pixelSize: 72
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var success = game.playIn(index)
                        if (!success) {
                            errorAnimation.start();
                        }
                    }
                }
                SequentialAnimation {
                    id: errorAnimation
                    ColorAnimation {
                        target: slot
                        property: "color"
                        from: "white"
                        to: "red"
                        easing.type: Easing.OutQuad
                        duration: 125
                    }
                    ColorAnimation {
                        target: slot
                        property: "color"
                        from: "red"
                        to: "white"
                        easing.type: Easing.InQuad
                        duration: 125
                    }
                }
            }
        }
    }
}
