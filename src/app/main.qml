import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "."

Window {
    visible: true
    width: 1000
    height: 700
    minimumWidth: 700
    minimumHeight: 500
    title: qsTr("IaRS - Report creation")

    Loader {
        id: reportSwitcher
        anchors.fill: parent
        source: "qrc:/ReportType.qml"
        function loadSwitcher(){reportSwitcher.source = "qrc:/ReportType.qml"}
    }
    Connections {
        target: uiController
        onReportSwitched: {
            reportSwitcher.source = "qrc:/Report.qml"
        }
    }
}
