import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "."

Rectangle {
    id: report
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
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft

            ListView {
                id: listView
                model: components[watcher.m_index].device_list
                property int indexed: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 10
                clip: true

                delegate: checkBoxDelegate
            }
        }

        Row {
            spacing: 50
            Button {
                id: backToReportSwitcher
                text: qsTr("Вернуться к выбору отчета")
                onClicked: {
                    reportSwitcher.loadSwitcher()
                }}
            Button {
                id: createReport
                text: qsTr("Сформировать отчет")
                onClicked: {
                    watcher.buttonClicked(listView.indexed)
                }
            }

        }
    }
}
