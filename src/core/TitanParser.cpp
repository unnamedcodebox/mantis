/** @file
 * @brief     Titan device parser implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */


#include "TitanParser.h"
#include "SplitDatabaseMessage.h"

#include <QRegExp>

namespace mantis
{

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
        reportTable.push_back({data.at("name"), data.at("state"), row.at("timeReported")});
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

    auto data = std::map<QString, QString>{{"name" , "CДВ РПДУ Титан-М"}, {"state" , state}};

    return data;
}

} // namespace mantis
