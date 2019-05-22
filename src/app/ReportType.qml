import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: turboRect
    anchors.fill: parent
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#14264d"
        }
        GradientStop {
            position: 1.0
            color: "#017ead"
        }
    }
    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        Label {
            id: screenTitle
            font.pixelSize: 42
            text: qsTr("ISP - Report Creator")
            color: "#FFFFFF"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ColumnLayout {
            id: checkboxColumn
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft

            ListView {
                id: listView
                model: components
                property int indexed: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 10
                clip: true

                delegate: RadioDelegate {
                    id: control
                    text: modelData.title
                    contentItem: Text {
                        text: control.text
                        font: control.font
                        wrapMode: Text.WordWrap
                        width: 500
                        opacity: enabled ? 1.0 : 0.3
                        color: listView.isCurrentItem ? "#AAAAAA" : "#FFFFFF"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: control.indicator.width + control.spacing
                    }
                    onClicked: {
                        listView.currentIndex = index
                        listView.indexed = index
                    }
                    indicator: Rectangle {
                        implicitWidth: 26
                        implicitHeight: 26
                        x: control.leftPadding
                        y: parent.height / 2 - height / 2
                        radius: 3
                        border.color: control.down ? "#17a81a" : "#21be2b"

                        Rectangle {
                            width: 14
                            height: 14
                            x: 6
                            y: 6
                            radius: 2
                            color: control.down ? "#17a81a" : "#21be2b"
                            visible: control.checked
                        }
                    }
                }
            }
        }

        Button {
            id: selectReport
            text: qsTr("Выбрать тип отчета")
            onClicked: {
                watcher.buttonClicked(listView.indexed)
            }
        }
    }
}
