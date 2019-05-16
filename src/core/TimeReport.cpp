/** @file
 * @brief     Time Report implentation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "TimeReport.h"

#include <QDateTime>
#include <QDebug>
#include <QString>

namespace mantis
{

namespace
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

} // namespace

const auto INPUT_DATE_FORMAT = QString{ "ddd MMM dd hh:mm:ss yyyy" };
const auto OUTPUT_DATE_FORMAT = QString{ "dd-MM-yyyy hh:mm:ss" };

using TimeStateTable
    = std::map<QString, std::map<QString, std::map<QString, int>>>;

ReportTable createTimeReport(ReportTable& table, QStringList deviceList)
{
    for (auto& device: deviceList)
    {
        device.replace(QString(","), "");
    }

    auto timeReport = ReportTable{};
    if (!table.empty())
    {
        for (auto& device: deviceList)
        {
            auto currentState = QString{};
            auto previousState = QString{};
            auto previousStateDateTime = QDateTime{};
            auto currentStateDateTime = QDateTime{};
            auto timeStateTable = TimeStateTable{};
            for (const auto& row: table)
            {
                if (device == row[0])
                {
                    if (timeStateTable.find(device) == timeStateTable.end())
                    {
                        currentState = row[1];
                        currentStateDateTime
                            = QDateTime::fromString(row[2], OUTPUT_DATE_FORMAT);
                        timeStateTable[device][currentState]["delta"] = 0;
                        timeStateTable[device][currentState]["stateCounter"]
                            = 1;
                    }
                    else
                    {
                        previousState = currentState;
                        currentState = row[1];

                        previousStateDateTime = currentStateDateTime;
                        currentStateDateTime
                            = QDateTime::fromString(row[2], OUTPUT_DATE_FORMAT);

                        auto delta_h = previousStateDateTime.secsTo(
                            currentStateDateTime);
                        auto stateTime = secondsToTime(delta_h);
                        timeReport.push_back(
                            { device, previousState, stateTime });
                        timeStateTable[device][previousState]["delta"]
                            += delta_h;
                        if (currentState != previousState)
                        {
                            timeStateTable[device][previousState]
                                          ["stateCounter"]
                                += 1;
                        }
                    }
                }
            }
        }
    }

    return timeReport;
}

TimeReport::TimeReport(ReportTable& table, QStringList& deviceList) {}

} // namespace mantis
