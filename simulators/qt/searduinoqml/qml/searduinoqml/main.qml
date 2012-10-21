// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 360
    height: 360
    MouseArea {
        x: 0
        y: 0
        width: 360
        height: 360
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }

        Grid {
            id: grid1
            x: 0
            y: 0
            width: 360
            height: 360

            Text {
                id: text1
                x: 135
                y: 224
                text: qsTr("text")
                font.pixelSize: 12
            }

            Text {
                id: text2
                x: 63
                y: 235
                text: qsTr("text")
                font.pixelSize: 12
            }
        }
    }
}
