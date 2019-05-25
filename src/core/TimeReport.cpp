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

/**
 * Convert seconds to report time format
 */
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
using TitanTimeStateTalbe = std::map<QString, std::map<QString, int>>;

ReportTable createTimeReportTable(ReportTable& table, QStringList deviceList)
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

ReportTable createTitanTimeReportTable(ReportTable& table)
{
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

    return resultStateTime;
}

ReportTable createIsbTimeReportTable(ReportTable& table)
{
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
                        fromString(deviceReport[6].replace("+03",""), "yyyy-MM-dd HH:mm:ss");
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
                        fromString(deviceReport[6].replace("+03",""), "yyyy-MM-dd HH:mm:ss");

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
                = (stateKey.first == QString{ "Исправно" }
                       ? QString{ "---" }
                       : QString::number(stateKey.second.at("stateCounter")));
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

    return tempArr;
}

} // namespace mantis
