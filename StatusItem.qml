import QtQuick 6.0

Rectangle {
    width: 300
    height: 50
    color: "white"
    border.color: "#ccc"
    radius: 8

    property string label: ""
    property int statusValue: 0
    property color barColor: "gray"

    Row {
        spacing: 10
        anchors.centerIn: parent

        Text {
            text: parent.parent.label
            font.bold: true
            width: 50
        }

        Rectangle {
            width: 150
            height: 20
            color: "#eee"
            radius: 10
            clip: true

            Rectangle {
                width: (parent.width * (parent.parent.parent.statusValue / 100))
                height: parent.height
                color: parent.parent.parent.barColor
                radius: 10
            }
        }

        Text {
            text: parent.parent.parent.statusValue + "%"
            width: 40
        }
    }
}