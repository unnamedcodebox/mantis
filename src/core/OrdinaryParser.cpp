/** @file
 * @brief     Ordinary devices parser implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "OrdinaryParser.h"
#include "SplitDatabaseMessage.h"

#include <QDateTime>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <regex>
#include <iomanip>

namespace mantis
{

namespace {

const auto NAME = "name";
const auto STATE = "state";
const auto MSG = "msg";
const auto TIME = "time";

const auto INPUT_DATE_FORMAT = QString{"ddd MMM dd hh:mm:ss yyyy"};
const auto OUTPUT_DATE_FORMAT = QString{"dd-MM-yyyy hh:mm:ss"};

auto parseDate(
    const QString& date,
    const QString& inputDateFormat,
    const QString& outputDateFormat)
{
    auto dateTime = QDateTime::fromString(date, inputDateFormat);
    return dateTime.toString(outputDateFormat);
}
} // anonymous

ReportTable OrdinaryParser::parseTable(Table& table)
{
    auto reportTable = ReportTable{};
    auto deviceStates = std::map<QString, QString>{};
    for (auto& row: table)
    {
        //auto parts = splitDatabaseMessage(row.at(MSG));
        //auto data = parseMessage(parts);

        auto data = parseMessage(row.at(MSG));

        if (deviceStates.find(data.at(NAME)) != deviceStates.end())
        {
            if (deviceStates.at(data.at(NAME)) != data.at(STATE))
            {
                reportTable.push_back(
                    { data.at(NAME), data.at(STATE), data.at(TIME) });
                deviceStates[data.at(NAME)] = data.at(STATE);
            }
        }
        else
        {

            reportTable.push_back(
                { data.at(NAME), data.at(STATE), data.at(TIME) });
            deviceStates[data.at(NAME)] = data.at(STATE);
        }
    }
    return reportTable;
}

std::map<QString, QString>
OrdinaryParser::parseMessage(std::vector<QString>& message)
{
    message[9] = message[9].replace(QObject::tr("State update:"), "");
    message[9] = message[9].replace(QString("("), "");
    message[9] = message[9].replace(QString(")"), "");
    message[9] = message[9].replace(QString(","), "");
    message[10] = message[10].replace(QString("("), "");
    message[10] = message[10].replace(QString(")"), "");
    message[10] = message[10].replace(QString("0 CODE "), "");

    auto time = parseDate(message[2], INPUT_DATE_FORMAT, OUTPUT_DATE_FORMAT);

    auto data = std::map<QString, QString>{ { NAME, message[9].trimmed() },
                                            { STATE, message[10].trimmed() },
                                          { TIME, time }};
    return data;
}

std::map<QString, QString>
OrdinaryParser::parseMessage(const QString& message)
{
    //auto regExp = "Обновление состояния:\\((.*\\,\\s)\\) = 0 CODE \\(\\s([^0-9])\\s\\)";
    auto regExp = "Обновление состояния:\\((.*)\\, \\) = 0 CODE \\( (.*) \\)";

    auto deviceMatched = "1";
    auto stateMatcher = "2";

    auto parseToInt = [](const QString& matchedGroup)
    {
        return matchedGroup.toInt();
    };

    auto deviceMatch = parseToInt(deviceMatched);
    auto stateMatch = parseToInt(stateMatcher);

    std::smatch match;
    auto messageStd = message.toStdString();
    auto found = std::regex_search(messageStd, match, std::regex(regExp));

    auto name = std::string();
    auto state = std::string();

    if(found)
    {
        name = match[static_cast<size_t>(deviceMatch)].str();
        state = match[static_cast<size_t>(stateMatch)].str();
    }

    auto dateRegExp = "\\[c\\] \\'(.*\)\' \\'";

    std::smatch dateMatch;

    auto foundDate = std::regex_search(messageStd, dateMatch, std::regex(dateRegExp));

    auto time = parseDate(QString::fromStdString(dateMatch[1].str()), INPUT_DATE_FORMAT, OUTPUT_DATE_FORMAT);

    auto data = std::map<QString, QString>{ { NAME, QString::fromStdString(name) },
                                            { STATE, QString::fromStdString(state) },
                                          { TIME, time }};
    std::cout << "DATE MATCH" << dateMatch[1].str() << "///";
    return data;
}


} // namespace mantis
