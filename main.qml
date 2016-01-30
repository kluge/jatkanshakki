import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    title: qsTr("Jätkänshakki - 5-in-a-row Tic Tac Toe")
    width: 640
    height: 600

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

    ColumnLayout {
        id: topLayout
        anchors.centerIn: parent
        anchors.margins: 10
        Grid {
            columns: 5
            rows: 5
            Repeater {
                model: game.board
                Square {
                    text: modelData
                }
            }
        }
        Label {
            id: winnerText
            Layout.alignment: Qt.AlignHCenter
            text: "Make a move!"
            font.pixelSize: 25
        }
    }

    function setWinner(winner) {
        console.log("setWinner called with " + winner)
        switch (winner) {
        case 0:
            winnerText.text = qsTr("Draw!")
            break
        case 1:
            winnerText.text = qsTr("Winner: X")
            break
        case 2:
            winnerText.text = qsTr("Winner: O")
            break
        }
    }

    Component.onCompleted: {
        game.gameOver.connect(setWinner)
    }

}
