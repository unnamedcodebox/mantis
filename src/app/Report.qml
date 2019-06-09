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
        anchors.margins: 10
        Label {
            id: screenTitle
            font.pixelSize: 18
            text: components[uiController.switchedIndex].title
            horizontalAlignment: Text.AlignHCenter
            Layout.maximumWidth: 700
            wrapMode: Text.Wrap
            color: "#FFFFFF"
            Layout.alignment: Qt.AlignHCenter
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
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft
            Layout.margins: 20
            Row {
                id: periodSetter

                spacing: 10
                Layout.alignment: Qt.AlignVCenter
                property string dateFormat: qsTr("dd/mm/yyyy")
                Label {

                    id: dateChoiceText
                    Layout.alignment: Qt.AlignVCenter
                    font.pixelSize: 14
                    color: "#FFFFFF"
                    text: qsTr("Set begin and end date")
                    height: 40
                }
                TextField {
                    id: beginDate
                    Layout.alignment: Qt.AlignVCenter
                    placeholderText: periodSetter.dateFormat

                }
                TextField {
                    id: endDate
                    Layout.alignment: Qt.AlignVCenter
                    placeholderText: periodSetter.dateFormat
                }
            }
            ListView {
                id: listView
                model: components[uiController.switchedIndex].device_list
                property int indexed: 0
                height: 200
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 10
                clip: true
                delegate: checkBoxDelegate
            }
            CheckBox {
                id: checkAllDevices
                text: qsTr("Get report for all device")
                property bool used: components[uiController.switchedIndex].group === "ordinary"
                visible: used
                checked: !used
                contentItem: Text {
                    text: checkAllDevices.text
                    font: checkAllDevices.font
                    opacity: enabled ? 1.0 : 0.3
                    color: checkAllDevices.down ? "#17a81a" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: checkAllDevices.indicator.width + checkAllDevices.spacing
                }
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
                contentItem: Text {
                    text: simpleReport.text
                    font: simpleReport.font
                    opacity: enabled ? 1.0 : 0.3
                    color: simpleReport.down ? "#17a81a" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: simpleReport.indicator.width + simpleReport.spacing
                }
            }
            RadioButton {
                id: timeReport
                property string subType: "timeReport"
                text: qsTr("Create a time report")
                contentItem: Text {
                    text: timeReport.text
                    font: timeReport.font
                    opacity: enabled ? 1.0 : 0.3
                    color: timeReport.down ? "#17a81a" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: timeReport.indicator.width + timeReport.spacing
                }
            }
        }
        Row {
            Layout.leftMargin: 20
            spacing: 50
            Button {
                id: backToReportSwitcher
                text: qsTr("Back to report switcher")
                onClicked: {
                    reportSwitcher.loadSwitcher()
                }
            }
            Button {
                id: createReport
                text: qsTr("Create report")
                onClicked: {
                    var subtype = simpleReport.checked ? simpleReport.subType : timeReport.subType
                    var reportId = components[uiController.switchedIndex].id
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
                        "group": components[uiController.switchedIndex].group,
                        "title": components[uiController.switchedIndex].title,
                        "id": components[uiController.switchedIndex].id,
                        "sub_type": subtype,
                        "device_list": reportDeviceList
                    }
                    uiController.sendReportInfo(reportInfo)
                    createReport.enabled = false
                    backToReportSwitcher.enabled = false
                }
            }
        }
    }

    Popup {
        id: reportCreated
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        width: 450
        height: 450
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose
        visible: false
        onClosed: {
            statusText.text = ""
            closePopupButton.enabled = false
            openReportFile.enabled = false
        }
        Item {
            id: popupItem
            width: reportCreated.width
            height: reportCreated.height
            Column {
                anchors.centerIn: parent
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 10
                spacing: 20
                Text {
                    id: reportCreationText
                    text: qsTr("Report creates")
                    font.pixelSize: 16
                    font.bold: true
                }
                BusyIndicator {
                    id: indicator
                    running: false
                    width: 150
                    Connections {
                        target: createReport
                        onClicked: {
                            indicator.running = true
                            reportCreated.visible = true
                        }
                    }
                    Connections {
                        target: uiController
                        onReportCreated: {
                            indicator.running = false
                            createReport.enabled = true
                            backToReportSwitcher.enabled = true
                        }
                    }
                }
                Text {
                    id: statusText
                }


            }
            Row {
                spacing: 10
                Button {
                    id: closePopupButton
                    enabled: false
                    text: qsTr("Back to report creation")
                    onClicked: {
                        reportCreated.close()
                    }
                }
                Button {
                    id: openReportFile
                    //anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    enabled: false
                    text: qsTr("Open report file")
                    onClicked: {
                        reportCreated.close()
                        uiController.openReportFile()
                    }
                    Connections {
                        target: uiController
                        onReportCreated: {
                            closePopupButton.enabled = true
                            openReportFile.enabled = true
                        }
                    }
                }
            }
        }

        Connections {
            target: uiController
            onReportCreated: {
                reportCreated.visible = true
                statusText.text = message
            }
        }
    }
}
