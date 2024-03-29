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

namespace
{

const auto SECONDS = "delta";
const auto STATE_COUNTER = "stateCounter";

} // anonymous

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
    , m_deviceList(deviceList)
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

    auto timeStateTable = TimeStateTable{};

    if (!table.empty())
    {
        for (auto& device: m_deviceList)
        {
            auto currentState = QString{};
            auto previousState = QString{};
            auto previousStateDateTime = QDateTime{};
            auto currentStateDateTime = QDateTime{};

            for (const auto& row: table)
            {
                if (device == row[0])
                {
                    if (timeStateTable.find(device) == timeStateTable.end())
                    {
                        currentState = row[1];
                        currentStateDateTime = QDateTime::fromString(row[2], OUTPUT_DATE_FORMAT);
                        timeStateTable[device][currentState][SECONDS] = 0;
                        timeStateTable[device][currentState][STATE_COUNTER] = 1;
                    }
                    else
                    {
                        previousState = currentState;
                        currentState = row[1];
                        previousStateDateTime = currentStateDateTime;
                        currentStateDateTime = QDateTime::fromString(row[2], OUTPUT_DATE_FORMAT);
                        auto seconds = previousStateDateTime.secsTo(currentStateDateTime);

                        timeStateTable[device][previousState][SECONDS] += seconds;
                        if (currentState != previousState)
                        {
                            timeStateTable[device][previousState][STATE_COUNTER] += 1;
                        }
                    }
                }
            }
        }

        auto resultTable = ReportTable{};
        for (auto device : timeStateTable)
        {
            for (auto& state : device.second)
            {
                resultTable.push_back(
                    { device.first,
                      state.first,
                      QString::number(state.second.at(STATE_COUNTER)),
                      secondsToTime(state.second.at(SECONDS)) });
            }
        }
        m_reportTable = resultTable;
    }
}

} // namespace mantis
