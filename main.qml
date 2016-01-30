import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    title: qsTr("Jätkänshakki - 5-in-a-row Tic Tac Toe")

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


    Dialog {
        id: newDialog
        title: "New game"
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            console.log("New game with " + rows.value + " rows and " + columns.value + " columns ")
            game.newGame(rows.value, columns.value)
            grid.rows = rows.value
            grid.columns = columns.value
            winnerText.text = qsTr("Make a move!")
        }

        ColumnLayout {
            RowLayout {
                Label {
                    text: "Amount of rows:"
                }
                SpinBox {
                    id: rows
                    minimumValue: 5
                    value: 5
                }
            }
            RowLayout {
                Label {
                    text: "Amount of columns:"
                }
                SpinBox {
                    id: columns
                    minimumValue: 5
                    value: 5
                }
            }
        }
    }

}

