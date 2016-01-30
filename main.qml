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
            model: boardModel
            Rectangle {
                width: 100
                height: 100
                border.width: 1
                Text {
                    anchors.centerIn: parent
                    text: modelData
                    fontSizeMode: Text.Fit
                    font.pixelSize: 72
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Clicked in " + index)
                        game.playIn(index)
                    }
                }
            }
        }
    }
}
