/** @file
 * @brief     Ordinary Report implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "OrdinaryReport.h"

#include <QDateTime>

namespace mantis
{

using namespace report_properties;

OrdinaryReport::OrdinaryReport(
    QString id,
    QString title,
    QString subtype,
    QString beginDate,
    QString endDate,
    QStringList deviceList)
    : m_id(std::move(id))
    , m_title(std::move(title))
    , m_subtype(std::move(subtype))
    , m_beginDate(std::move(beginDate))
    , m_endDate(std::move(endDate))
    , m_deviceList(std::move(deviceList))
{
}

QString OrdinaryReport::id()
{
    return m_id;
}

QString OrdinaryReport::title()
{
    return m_title;
}

QString OrdinaryReport::subtype()
{
    return m_subtype;
}

QString OrdinaryReport::beginDate()
{
    return m_beginDate;
}

QString OrdinaryReport::endDate()
{
    return m_endDate;
}

const ReportTable &OrdinaryReport::getReportTable() const
{
    return m_reportTable;
}

void OrdinaryReport::setReportTable(ReportTable &table)
{
    m_reportTable = table;
}

void OrdinaryReport::createTimeReportTable(ReportTable& table)
{
    using namespace date_format;

    for (auto& device: m_deviceList)
    {
        device.replace(QString(","), "");
    }

    auto timeReport = ReportTable{};
    if (!table.empty())
    {
        for (auto& device: m_deviceList)
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

    m_reportTable = std::move(timeReport);
}

} // namespace mantis
