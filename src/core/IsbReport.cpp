/** @file
 * @brief     Ordinary Report implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "IsbReport.h"

#include <QDateTime>

namespace mantis
{
using namespace report_properties;

IsbReport::IsbReport(
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

QString IsbReport::id()
{
    return m_id;
}

QString IsbReport::title()
{
    return m_title;
}

QString IsbReport::subtype()
{
    return m_subtype;
}

QString IsbReport::beginDate()
{
    return m_beginDate;
}

QString IsbReport::endDate()
{
    return m_endDate;
}

const ReportTable &IsbReport::getReportTable() const
{
    return m_reportTable;
}

void IsbReport::setReportTable(ReportTable &table)
{
    m_reportTable = table;
}

void IsbReport::createTimeReportTable(ReportTable& table)
{
    using namespace date_format;

    auto currentState = QString{};
    auto previousState = QString{};
    auto previousStateDateTime = QDateTime{};
    auto currentStateDateTime = QDateTime{};
    auto dateTimeReport = ReportTable{};
    auto stateTimeTotalCountTable = TimeStateTable{};
    auto deviceArray = std::set<std::vector<QString>>{};

    for (auto& deviceReport: table)
    {
        deviceArray.insert({ deviceReport[0],
                             deviceReport[1],
                             deviceReport[2],
                             deviceReport[3] });
    }

    for (auto& device: deviceArray)
    {
        for (auto& deviceReport: table)
        {

            if (device[0] == deviceReport[0] && device[1] == deviceReport[1]
                && device[2] == deviceReport[2] && device[3] == deviceReport[3])
            {
                auto deviceLongName = deviceReport[0] + " , " + deviceReport[1]
                                      + " , " + deviceReport[2] + " , "
                                      + deviceReport[3];
                if (stateTimeTotalCountTable.find(deviceLongName)
                    == stateTimeTotalCountTable.end())
                {
                    currentState = deviceReport[4];
                    currentStateDateTime = currentStateDateTime = QDateTime::
                        fromString(deviceReport[6], "yyyy-MM-dd HH:mm:ss");
                    stateTimeTotalCountTable[deviceLongName][currentState]
                                            ["delta"]
                        = 0;
                    stateTimeTotalCountTable[deviceLongName][currentState]
                                            ["stateCounter"]
                        = 0;
                }
                else
                {
                    previousState = currentState;
                    currentState = deviceReport[4];

                    previousStateDateTime = currentStateDateTime;
                    currentStateDateTime = currentStateDateTime = QDateTime::
                        fromString(deviceReport[6], "yyyy-MM-dd HH:mm:ss");

                    auto delta_h
                        = previousStateDateTime.secsTo(currentStateDateTime);
                    auto stateTime = secondsToTime(delta_h);

                    dateTimeReport.push_back(
                        { deviceLongName, previousState, stateTime });
                    stateTimeTotalCountTable[deviceLongName][previousState]
                                            ["delta"]
                        += delta_h;
                    if (currentState != previousState)
                    {
                        stateTimeTotalCountTable[deviceLongName][previousState]
                                                ["stateCounter"]
                            += 1;
                    }
                }
            }
        }
    }

    auto tempArr = ReportTable{};
    auto previousDeviceKey = QString{};
    for (auto& deviceKey: stateTimeTotalCountTable)
    {
        for (auto& stateKey: deviceKey.second)
        {
            auto time = secondsToTime(stateKey.second.at("delta"));
            auto stateCounter
                = /*(stateKey.first == QString{ "Исправно" }
                       ? QString{ "---" }
                       :*/ QString::number(stateKey.second.at("stateCounter"))/*)*/;
            if (previousDeviceKey != deviceKey.first)
            {
                tempArr.push_back(
                    { deviceKey.first, stateKey.first, stateCounter, time });
            }
            else
            {
                tempArr.push_back(
                    { deviceKey.first, stateKey.first, stateCounter, time });
                // array_push(tempArr, array(":::", stateKey,
                // timeValue["stateCounter"], time));
            }
            previousDeviceKey = deviceKey.first;
        }
    }
    // dateTimeReport->setData(tempArr);
    // return dateTimeReport;

    m_reportTable = std::move(tempArr);
}

} // namespace mantis
