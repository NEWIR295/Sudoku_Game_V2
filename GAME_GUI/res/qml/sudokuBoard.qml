import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5

Rectangle {
    id: frame
    color: "transparent"
    border.color: "gray"
    border.width: 6

    Rectangle {
        id: container
        anchors.fill: parent
        anchors.margins: frame.border.width
        color: "blue"

        GridLayout {
            id: root
            anchors.fill: parent
            anchors.margins: 4
            rows: 9
            columns: 9
            rowSpacing: 1
            columnSpacing: 1

            property var board: sudokuBoard     // receives 9×9 array from C++

            Repeater {
                model: 81

                delegate: Rectangle {
                    width: 40
                    height: 40
                    border.width: 1
                    border.color: "blue"
                    color: cell.activeFocus ? "yellow" : "red"

                    TextField {
                        id: cell
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 20
                        maximumLength: 1
                        color: "black"
                        background: Rectangle {
                            color: "transparent"
                        }
                        text: root.board[Math.floor(index / 9)][index % 9] === 0
                              ? ""
                              : root.board[Math.floor(index / 9)][index % 9]
                    }
                }
            }
        }

        Item {
            id: subgridOverlay
            anchors.fill: root
            anchors.margins: root.columnSpacing
            Repeater {
                model: 9
                delegate: Rectangle {
                    readonly property real cellWidth: subgridOverlay.width / 3
                    readonly property real cellHeight: subgridOverlay.height / 3
                    readonly property real pad: 2
                    width: cellWidth - pad * 2
                    height: cellHeight - pad * 2
                    x: (index % 3) * cellWidth + pad
                    y: Math.floor(index / 3) * cellHeight + pad
                    color: "transparent"
                    border.width: 1
                    border.color: "white"
                }
            }
        }
    }
}
