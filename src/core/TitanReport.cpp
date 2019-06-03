/** @file
 * @brief     Ordinary Report implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "TitanReport.h"

#include <QDateTime>

namespace mantis
{
using namespace report_properties;

TitanReport::TitanReport(
    QString id,
    QString title,
    QString subtype,
    QString beginDate,
    QString endDate)
    : m_id(std::move(id))
    , m_title(std::move(title))
    , m_subtype(std::move(subtype))
    , m_beginDate(std::move(beginDate))
    , m_endDate(std::move(endDate))
{
}

QString TitanReport::id()
{
    return m_id;
}

QString TitanReport::title()
{
    return m_title;
}

QString TitanReport::subtype()
{
    return m_subtype;
}

QString TitanReport::beginDate()
{
    return m_beginDate;
}

QString TitanReport::endDate()
{
    return m_endDate;
}

const ReportTable &TitanReport::getReportTable() const
{
    return m_reportTable;
}

void TitanReport::setReportTable(ReportTable &table)
{
    m_reportTable = table;
}

void TitanReport::createTimeReportTable(ReportTable& table)
{
    using namespace date_format;


    auto currentState = QString{};
    auto previousState = QString{};
    auto previousStateDateTime = QDateTime{};
    auto currentStateDateTime = QDateTime{};
    auto dateTimeReport = ReportTable{};
    auto stateTimeTotalCountTable = TitanTimeStateTalbe{};

    for (auto& row: table)
    {
        if (currentState == "")
        {
            currentState = row[1];
            currentStateDateTime
                = QDateTime::fromString(row[2], OUTPUT_DATE_FORMAT);
            stateTimeTotalCountTable[currentState]["delta"] = 0;
            stateTimeTotalCountTable[currentState]["stateCounter"] = 1;
        }
        else
        {
            previousState = currentState;
            currentState = row[1];

            previousStateDateTime = currentStateDateTime;
            currentStateDateTime = currentStateDateTime
                = QDateTime::fromString(row[2], OUTPUT_DATE_FORMAT);

            auto delta_h = previousStateDateTime.secsTo(currentStateDateTime);
            auto stateTime = secondsToTime(delta_h);
            dateTimeReport.push_back({ previousState, stateTime });
            stateTimeTotalCountTable[previousState]["delta"] += delta_h;
            if (currentState != previousState)
            {
                stateTimeTotalCountTable[previousState]["stateCounter"] += 1;
            }
        }
    }

    auto resultStateTime = ReportTable{};
    auto titleCounter = 0;
    for (auto& state: stateTimeTotalCountTable)
    {
        auto time = secondsToTime(state.second.at("delta"));
        if (!titleCounter)
        {
            resultStateTime.push_back(
                { table[0][0],
                  state.first,
                  QString::number(state.second.at("stateCounter")),
                  time });
        }
        else
        {
            resultStateTime.push_back(
                { table[0][0],
                  state.first,
                  QString::number(state.second.at("stateCounter")),
                  time });
        }
        ++titleCounter;
    }
    m_reportTable = resultStateTime;
}

} // namespace mantis
