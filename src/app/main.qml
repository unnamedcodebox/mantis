import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 1000
    height: 700
    minimumWidth: 700
    minimumHeight: 500
    title: qsTr("ИСП - формирование справок")
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
        Label {
            id: screenTitle
            font.pixelSize: 42
            text: qsTr("ISP - Report Creator")
            color: "#FFFFFF"
            anchors.horizontalCenter: turboRect.horizontalCenter
        }
        Component {
            id: checkBoxDelegate
            CheckBox {
                text: modelData
                font.pixelSize: 18
                id: control
                contentItem: Text {
                    text: control.text
                    font: control.font

                    opacity: enabled ? 1.0 : 0.3
                    color: control.down ? "#17a81a" : "#21be2b"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: control.indicator.width + control.spacing
                }
            }
        }
        ColumnLayout {
            id: checkboxColumn
            anchors.top: screenTitle.bottom
            anchors.fill: parent
            anchors.topMargin: 15



            ListView {
                model: reportData
                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Layout.margins: 10
                clip: true
                delegate: checkBoxDelegate
            }

            Button {
                id: selectReport
                text: qsTr("Выбрать тип отчета")
            }
        }

    }
}
