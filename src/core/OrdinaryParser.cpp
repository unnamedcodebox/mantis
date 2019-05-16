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

#include <QDebug>

namespace mantis
{

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

ReportTable OrdinaryParser::parseTable(Table &table)
{
    auto reportTable = ReportTable{};

    for(const auto& row : table)
    {
        auto parts = splitDatabaseMessage(row.at("msg"));
        auto data = parseMessage(parts);
//        reportTable.push_back({data.at("name"), data.at("state"), row.at("timeReported")});
        reportTable.push_back({data.at("name"), data.at("state"), data.at("time")});
    }

    return reportTable;
}

std::map<QString, QString>
OrdinaryParser::parseMessage(std::vector<QString>& message)
{
    qDebug() << message;

    message[9] = message[9].replace(QString("Обновление состояния:"), "");
    message[9] = message[9].replace(QString("("), "");
    message[9] = message[9].replace(QString(")"), "");
    message[9] = message[9].replace(QString(","), "");
    message[10] = message[10].replace(QString("("), "");
    message[10] = message[10].replace(QString(")"), "");
    message[10] = message[10].replace(QString("0 CODE "), "");

    auto time = parseDate(message[2], INPUT_DATE_FORMAT, OUTPUT_DATE_FORMAT);

    auto data = std::map<QString, QString>{ { "name", message[9].trimmed() },
                                            { "state", message[10].trimmed() },
                                          { "time", time }};
    return data;
}

} // namespace mantis
