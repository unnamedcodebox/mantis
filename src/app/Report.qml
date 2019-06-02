import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
//import Qt.labs.calendar 1.0
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
        Layout.margins: 25
        Label {
            id: screenTitle
            font.pixelSize: 18
            text: components[watcher.m_index].title
            width: parent.width
            wrapMode: Text.WordWrap
            color: "#FFFFFF"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Component {
            id: checkBoxDelegate
            CheckBox {
                text: modelData
                font.pixelSize: 14
                id: control
                contentItem: Text {
                    text: control.text
                    font: control.font
                    opacity: enabled ? 1.0 : 0.3
                    color: control.down ? "#17a81a" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: control.indicator.width + control.spacing
                }
                indicator: Rectangle {
                    implicitWidth: 20
                    implicitHeight: 20
                    x: control.leftPadding
                    y: parent.height / 2 - height / 2
                    radius: 3
                    border.color: control.activeFocus ? "darkblue" : "gray"
                    border.width: 1
                    Rectangle {
                        visible: control.checked
                        color: "#555"
                        border.color: "#333"
                        radius: 1
                        anchors.margins: 4
                        anchors.fill: parent
                    }
                }
            }
        }
        ColumnLayout {
            id: checkboxColumn
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
            Row {
                spacing: 10
                Layout.alignment: Qt.AlignVCenter
                Text {
                    Layout.alignment: Qt.AlignVCenter
                    id: dateChoiceText
                    color: "#FFFFFF"
                    text: qsTr("Set begin and end date")
                }
                TextField {
                    id: beginDate
                    Layout.alignment: Qt.AlignVCenter
                    placeholderText: "dd/mm/yyyy"
                }
                TextField {
                    id: endDate
                    Layout.alignment: Qt.AlignVCenter
                    placeholderText: "dd/mm/yyyy"
                }
            }
            ListView {
                id: listView
                model: components[watcher.m_index].device_list
                visible: components[watcher.m_index].group === "ordinary"
                property int indexed: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 10
                clip: true
                delegate: checkBoxDelegate
            }
            CheckBox {
                id: checkAllDevices
                text: qsTr("Get report for all device")
                property bool used: components[watcher.m_index].group === "ordinary"
                visible: used
                checked: !used
                onCheckedChanged: {
                    for (var child in listView.contentItem.children) {
                        listView.contentItem.children[child].checked = checkAllDevices.checkState
                    }
                }
            }
            RadioButton {
                id: simpleReport
                property string subType: "simpleReport"
                checked: true
                text: qsTr("Create a simple report")
            }
            RadioButton {
                id: timeReport
                property string subType: "timeReport"
                text: qsTr("Create a time report")
            }
        }
        Row {
            spacing: 50
            Button {
                id: backToReportSwitcher
                text: qsTr("Вернуться к выбору отчета")
                onClicked: {
                    reportSwitcher.loadSwitcher()
                }
            }
            Button {
                id: createReport
                text: qsTr("Сформировать отчет")
                onClicked: {
                    var subtype = simpleReport.checked ? simpleReport.subType : timeReport.subType
                    var reportId = components[watcher.m_index].id
                    var reportDeviceList = []

                    for (var child in listView.contentItem.children) {
                        if (listView.contentItem.children[child].checked === true) {
                            reportDeviceList.push(
                                        listView.contentItem.children[child].text)
                            console.log(listView.contentItem.children[child].text)
                        }
                    }
                    var reportInfo = {
                        "begin_date": beginDate.text,
                        "end_date": endDate.text,
                        "group": components[watcher.m_index].group,
                        "title": components[watcher.m_index].title,
                        "id": components[watcher.m_index].id,
                        "sub_type": subtype,
                        "device_list": reportDeviceList
                    }
                    watcher.reportPropertiesSetted(beginDate.text,
                                                   endDate.text,
                                                   reportId, subtype)
                    watcher.takeVariantMap(reportInfo)
                    reportManager.createReport(reportInfo)
                }
            }
        }
    }
}
