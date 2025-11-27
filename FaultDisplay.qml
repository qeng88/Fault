// FaultDisplay.qml
import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    width: 400
    height: 300
    color: "#f0f0f0"
    border.color: "#cccccc"
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: 10

        Label {
            text: "故障列表"
            font.bold: true
            font.pixelSize: 16
            color: "red"
        }

        ListView {
            id: faultListView
            width: parent.width
            height: parent.height - 40
            model: faultManager.faultList
            clip: true

            delegate: Rectangle {
                width: faultListView.width
                height: 30
                color: index % 2 === 0 ? "#ffffff" : "#f8f8f8"
                border.color: "#eeeeee"

                Row {
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10

                    Rectangle {
                        width: 12
                        height: 12
                        radius: 6
                        color: "red"
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        text: modelData
                        color: "red"
                        font.pixelSize: 14
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                text: "暂无故障"
                color: "gray"
                font.pixelSize: 14
                visible: faultListView.count === 0
            }
        }
    }
}
