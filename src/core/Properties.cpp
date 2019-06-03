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
}

namespace date_format
{

QString secondsToTime(int value)
{
    int day = value / (24 * 3600);
    value = value % (24 * 3600);
    int hour = value / 3600;
    value %= 3600;
    int minutes = value / 60;
    value %= 60;
    int seconds = value;

    return day != 0 ? QObject::tr("%1 d, %2 h, %3 m, %4 s")
                          .arg(
                              QString::number(day),
                              QString::number(hour),
                              QString::number(minutes),
                              QString::number(seconds))
                    : QObject::tr("%1 h, %2 m, %3 s")
                          .arg(
                              QString::number(hour),
                              QString::number(minutes),
                              QString::number(seconds));
}

} // namespace date_format

// namespace report_properties

} // namespace mantis
