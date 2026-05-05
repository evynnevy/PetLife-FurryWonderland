import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.petlife 1.0

Item {
    id: roomPage

    property bool statusExpanded: true

    PetStatus {
        id: petStatus
    }

    // 背景图片
    Image {
        anchors.fill: parent
        source: "qrc:/images/pet_room.png"
        fillMode: Image.PreserveAspectCrop
        opacity: 0.9
    }

    // 半透明遮罩
    Rectangle {
        anchors.fill: parent
        color: "#60000000"
        z: 0
    }

    // 宠物图片（呼吸动画）
    Image {
        id: petImage
        source: "qrc:/images/Samoyed.png"
        width: parent.width * 0.5
        height: width * 0.75
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -20
        fillMode: Image.PreserveAspectFit
        z: 2
        NumberAnimation on scale {
            from: 0.98; to: 1.02; duration: 2000; loops: Animation.Infinite; easing.type: Easing.InOutSine
        }
    }

    // 可折叠状态卡片
    Rectangle {
        id: statusCard
        width: parent.width * 0.9
        anchors.top: parent.top; anchors.topMargin: 20; anchors.horizontalCenter: parent.horizontalCenter
        height: statusExpanded ? 280 : 70
        radius: 24
        color: "#E6FFFFFF"
        border.color: "#CCCCCC"; border.width: 1
        z: 5
        Behavior on height { NumberAnimation { duration: 200; easing.type: Easing.OutQuad } }

        Column {
            width: parent.width; spacing: 8; anchors.top: parent.top; anchors.topMargin: 12

            Rectangle {
                width: parent.width; height: 46; color: "transparent"
                Row {
                    spacing: 8; anchors.centerIn: parent
                    Text { text: "🐾 宠物状态"; font.pixelSize: 22; font.bold: true; color: "#2C3E50" }
                    Text {
                        text: statusExpanded ? "▲" : "▼"; font.pixelSize: 20; color: "#7F8C8D"
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: statusExpanded = !statusExpanded }
                    }
                }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: statusExpanded = !statusExpanded }
            }

            Column {
                width: parent.width; spacing: 10; visible: statusExpanded; anchors.horizontalCenter: parent.horizontalCenter
                StatusItem { label: "💪 健康"; statusValue: petStatus.health; barColor: "#FF6B6B" }
                StatusItem { label: "🍗 饥饿"; statusValue: petStatus.hunger; barColor: "#FFA559" }
                StatusItem { label: "😴 困倦"; statusValue: petStatus.sleepiness; barColor: "#6C91B2" }
                StatusItem { label: "😊 心情"; statusValue: petStatus.mood; barColor: "#6BCB77" }
            }
        }
    }

    // 底部按钮行
    Row {
        spacing: 24
        anchors.bottom: parent.bottom; anchors.bottomMargin: 40; anchors.horizontalCenter: parent.horizontalCenter
        z: 5

        Button {
            text: "🍖\n喂食"; font.pixelSize: 20
            width: 80; height: 80
            background: Rectangle { radius: 40; color: parent.pressed ? "#DDDDDD" : "#F5F5F5"; border.color: "#CCCCCC"; border.width: 1 }
            onClicked: petStatus.feed()
        }
        Button {
            text: "🎾\n玩耍"; font.pixelSize: 20
            width: 80; height: 80
            background: Rectangle { radius: 40; color: parent.pressed ? "#DDDDDD" : "#F5F5F5"; border.color: "#CCCCCC"; border.width: 1 }
            onClicked: petStatus.play()
        }
        Button {
            text: "😴\n休息"; font.pixelSize: 20
            width: 80; height: 80
            background: Rectangle { radius: 40; color: parent.pressed ? "#DDDDDD" : "#F5F5F5"; border.color: "#CCCCCC"; border.width: 1 }
            onClicked: petStatus.rest()
        }
        Button {
            text: "💊\n治疗"; font.pixelSize: 20
            width: 80; height: 80
            background: Rectangle { radius: 40; color: parent.pressed ? "#DDDDDD" : "#F5F5F5"; border.color: "#CCCCCC"; border.width: 1 }
            onClicked: petStatus.heal()
        }
        Button {
            text: "🏠\n返回"; font.pixelSize: 20
            width: 80; height: 80
            background: Rectangle { radius: 40; color: parent.pressed ? "#DDDDDD" : "#F5F5F5"; border.color: "#CCCCCC"; border.width: 1 }
                onClicked: {
                    if (typeof StackView !== "undefined" && StackView.view) {
                        StackView.view.pop();
                        return;
                    }

                    var p = parent;
                    while (p) {
                        if (p.objectName === "stackView" || (typeof p.pop === "function" && p.pop !== undefined)) {
                            p.pop();
                            break;
                        }
                        p = p.parent;
                    }
                    console.log("🏠\n返回");
                }
            }
    }

    Text {
        anchors.bottom: parent.bottom; anchors.bottomMargin: 12; anchors.horizontalCenter: parent.horizontalCenter
        text: "点击卡片头部可收起状态栏"; font.pixelSize: 12; color: "#FFFFFFCC"; z: 5
    }
}