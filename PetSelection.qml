import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: petSelectionPage
    title: "🐱选择宠物🐶"
    background: Rectangle { color: "#f0f0f0" }

    // 标题
    Label {
        text: "🐾 选择你的小伙伴"
        font.pixelSize: 28
        font.bold: true
        color: "#2C3E50"
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    GridView {
        id: gridView
        anchors.fill: parent
        anchors.margins: 40
        anchors.topMargin: 100
        cellWidth: (parent.width - 80) / 2
        cellHeight: cellWidth * 0.9
        model: petModel.pets
        clip: true

        delegate: Rectangle {
            width: gridView.cellWidth - 20
            height: gridView.cellHeight - 20
            radius: 20
            color: mouseArea.pressed ? "#E6E6E6" : "#FFFFFF"
            border.color: "#CCCCCC"
            border.width: 1
            layer.enabled: true
            Behavior on color { ColorAnimation { duration: 100 } }

            Column {
                anchors.centerIn: parent
                spacing: 12
                width: parent.width - 20

                Image {
                    source: modelData.imagePath
                    width: parent.width * 0.7
                    height: width
                    fillMode: Image.PreserveAspectFit
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: modelData.name
                    font.pixelSize: 20
                    font.bold: true
                    color: "#2C3E50"
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: "点击选择"
                    font.pixelSize: 14
                    color: "#7F8C8D"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    petModel.selectPet(modelData.id);
                    stackView.pop();
                }
            }

            scale: mouseArea.containsMouse ? 1.02 : 1.0
            Behavior on scale { NumberAnimation { duration: 150 } }
        }
    }

    // 返回按钮
    Button {
        text: "← 返回"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 20
        font.pixelSize: 18
        background: Rectangle {
            color: "#DDDDDD"
            radius: 10
        }
        onClicked: stackView.pop()
    }
}