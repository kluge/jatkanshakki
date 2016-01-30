import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 550
    title: qsTr("Jätkänshakki - 5-in-a-row Tic Tac Toe")

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
            Square {
                text: modelData
            }
        }
    }
}
