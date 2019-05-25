/** @file
 * @brief     Titan device parser implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */


#include "TitanParser.h"
#include "SplitDatabaseMessage.h"

#include <QDateTime>
#include <QRegExp>

namespace mantis
{

namespace {

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

TitanParser::TitanParser(std::map<int, QString> states):
    m_states(std::move(states))
{

}

ReportTable TitanParser::parseTable(Table &table)
{
    auto reportTable = ReportTable{};

    for(const auto& row : table)
    {
        auto parts = splitDatabaseMessage(row.at("msg"));
        auto data = parseMessage(parts);
        reportTable.push_back({data.at("name"), data.at("state"), data.at("time")});
    }

    return reportTable;
}

std::map<QString, QString> TitanParser::parseMessage(std::vector<QString> &message)
{
    auto state = QString();
    message[10] = message[10].replace(QString("0 CODE ( РПДУ Титан, № 1 - "), QString());
    message[10] = message[10].replace(QString(" ) "), QString(""));

    auto stateExists = m_states.find(message[10].toInt());
    state = stateExists != m_states.end() ? m_states.at(message[10].toInt()) : QString("Исправно");

    auto time = parseDate(message[2], INPUT_DATE_FORMAT, OUTPUT_DATE_FORMAT);

    auto data = std::map<QString, QString>{{"name" , "CДВ РПДУ Титан-М"}, {"state" , state}, {"time", time}};

    return data;
}

} // namespace mantis
