import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    width: 1280
    height: 720

    Image {
        anchors.fill: parent
        source: "qrc:/images/home_planet.png"
        fillMode: Image.PreserveAspectCrop
    }

    Button {
        id: enterRoomButton
        text: "进入房间"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 180
        font.pixelSize: 30
        font.family: "Arial"
        font.bold: true

        background: Rectangle {
            color: "#90EE90"
            radius: 8
            border.color: "#228B22"
            border.width: 2
        }

        onClicked: {
            console.log("点击了‘进入房间’");
            stackView.push(roomPageComponent)
        }
    }

    Component {
        id: roomPageComponent
        RoomPage { }
    }

    Button {
        id: selectPetButton
        text: "选择宠物"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 180
        font.pixelSize: 30
        font.family: "Arial"
        font.bold: true

        background: Rectangle {
            color: "#FFD966"
            radius: 8
            border.color: "#B8860B"
            border.width: 2
        }

        onClicked: {
            stackView.push(petSelectionComponent)
        }
    }

    Component {
        id: petSelectionComponent
        PetSelection { }
    }
}