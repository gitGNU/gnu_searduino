// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 360
    height: 360
    MouseArea {
        x: 5
        y: 0
        anchors.rightMargin: -5
        anchors.bottomMargin: 0
        anchors.leftMargin: 5
        anchors.topMargin: 0
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }

        Rectangle {
            id: page
            x: 17
            y: 16
            width: 200
            height: 200
            color: "#343434"
        }
    }
    states: [
        State {
            name: "State1"
        }
    ]
}
