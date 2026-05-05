import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: "Furry Wonderland"
    color: "#f0f0f0"

    StackView {
        id: stackView
        initialItem: homePageComponent
        anchors.fill: parent
    }

    Component {
        id: homePageComponent
        HomePage { }
    }
}