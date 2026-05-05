import QtQuick 6.0

Rectangle {
    height: 70
    color: "white"
    border.color: "#ccc"
    radius: 8

    property string label: ""
    property int statusValue: 0
    property color barColor: "gray"

    Column {
        spacing: 4
        anchors.centerIn: parent
        width: parent.width - 10

        Text {
            text: label
            font.bold: true
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: Math.min(160, parent.width * 0.7)
            height: 16
            color: "#eee"
            radius: 8
            clip: true
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                width: (parent.width * (statusValue / 100))
                height: parent.height
                color: barColor
                radius: 8
                Behavior on width { NumberAnimation { duration: 200 } }
            }
        }

        Text {
            text: statusValue + "%"
            font.pixelSize: 12
            color: barColor
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
