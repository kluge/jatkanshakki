import QtQuick 2.5

Item {
    id: square
    property alias color: rect.color
    property alias text: label.text
    width: 50
    height: 50
    Rectangle {
        id: rect
        width: square.width
        height: square.height
        border.width: 1
        color: "white"
        Text {
            id: label
            anchors.centerIn: parent
            fontSizeMode: Text.Fit
            font.pixelSize: 36
            color: gameRunning ? "black" : (winner == text ? "green" : "grey")
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (gameRunning) {
                    var success = game.playIn(index)
                    if (!success) {
                        errorAnimation.start();
                    }
                }
            }
        }

    }
    SequentialAnimation {
        id: errorAnimation
        ColorAnimation {
            target: square
            property: "color"
            from: "white"
            to: "red"
            easing.type: Easing.OutQuad
            duration: 125
        }
        ColorAnimation {
            target: square
            property: "color"
            from: "red"
            to: "white"
            easing.type: Easing.InQuad
            duration: 125
        }
    }
}
