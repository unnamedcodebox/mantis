#include "Properties.h"

namespace mantis
{

namespace report_properties
{

QString getReportProperty(QVariantMap reportInfo, QString property)
{
    return reportInfo[property].toString();
}

QStringList getDeviceList(QVariantMap reportInfo)
{
    return reportInfo[report_properties::DEVICE_LIST].toStringList();
}
} // namespace report_properties

} // namespace mantis
