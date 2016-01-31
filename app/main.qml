import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    title: qsTr("Jätkänshakki - 5-in-a-row Tic Tac Toe")

    property bool gameRunning: true
    property string winner: ""

    menuBar: MenuBar {
        Menu {
            title: qsTr("Game")
            MenuItem {
                text: qsTr("&New game")
                shortcut: "Ctrl+N"
                onTriggered: newDialog.open();
            }
            MenuItem {
                text: qsTr("Exit")
                shortcut: "Ctrl+Q"
                onTriggered: Qt.quit();
            }
        }
    }

    ColumnLayout {
        id: topLayout
        anchors.fill: parent
        anchors.margins: 10
        Grid {
            id: grid
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

    function setWinner(arg) {
        console.log("setWinner called with " + arg)
        gameRunning = false;

        switch (arg) {
        case 0:
            winner = ""
            winnerText.text = qsTr("Draw!")
            break
        case 1:
            winner = "X"
            winnerText.text = qsTr("Winner: X")
            break
        case 2:
            winner = "O"
            winnerText.text = qsTr("Winner: O")
            break
        }
    }

    Component.onCompleted: {
        game.gameOver.connect(setWinner)
    }


    Dialog {
        id: newDialog
        width: 255
        height: 120
        title: "New game"
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            console.log("New game with " + rows.value + " rows and difficulty " + difficulty.currentIndex)
            game.newGame(rows.value, difficulty.currentIndex)
            grid.rows = rows.value
            grid.columns = rows.value
            winnerText.text = qsTr("Make a move!")
            gameRunning = true;
        }
        GridLayout {
            columns: 2

            Label {
                text: "Amount of rows:"
            }
            SpinBox {
                id: rows
                minimumValue: 5
                value: 5
            }

            Label {
                text: "Opponent difficulty:"
            }
            ComboBox {
                id: difficulty
                currentIndex: 0
                model: ["Trivial", "Easy"]
            }
        }
    }
}


