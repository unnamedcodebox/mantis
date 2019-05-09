/** @file
 * @brief     Ordinary devices parser implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "OrdinaryParser.h"
#include "SplitDatabaseMessage.h"

namespace mantis
{

ReportTable OrdinaryParser::parseTable(Table &table)
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

std::map<QString, QString>
OrdinaryParser::parseMessage(std::vector<QString>& message)
{
    message[9] = message[9].replace(QString("Обновление состояния:"), "");
    message[9] = message[9].replace(QString("("), "");
    message[9] = message[9].replace(QString(")"), "");
    message[9] = message[9].replace(QString(","), "");
    message[10] = message[10].replace(QString("("), "");
    message[10] = message[10].replace(QString(")"), "");
    message[10] = message[10].replace(QString("0 CODE "), "");

    auto data = std::map<QString, QString>{ { "name", message[9].trimmed() },
                                            { "state", message[10].trimmed() } };
    return data;
}

} // namespace mantis
