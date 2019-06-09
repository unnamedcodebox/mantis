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
#include <QObject>
#include <QRegExp>

namespace mantis
{

namespace  {

QString getState(int stateCode)
{
    std::map<int, QString> states = { { 0, QObject::tr("OK") },
                                      { 1, QObject::tr("Emergency cooling") },
                                      { 2, QObject::tr("Emergency heat") },
                                      { 3, QObject::tr("Overhead") },
                                      { 4, QObject::tr("Emergency pneumatic") },
                                      { 5, QObject::tr("Emergency network") } };

    auto stateExists = states.find(stateCode);
    return stateExists != states.end() ? states.at(stateCode) : QObject::tr("OK");
}

} // anonymous

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

ReportTable TitanParser::parseTable(Table &table)
{
    auto reportTable = ReportTable{};

    auto counter = 1;
    auto currentState = QString();
    for(auto& row : table)
    {
        auto parts = splitDatabaseMessage(row.at("msg"));
        auto data = parseMessage(parts);
        if(counter == 1)
        {
            reportTable.push_back(
                { data.at("name"), data.at("state"), data.at("time") });
            currentState = data.at("state");
        }
        else {
            if(!(data.at("state") == currentState))
            {
                reportTable.push_back(
                    { data.at("name"), data.at("state"), data.at("time") });
                currentState = data.at("state");
            }
        }
        ++counter;
    }

    return reportTable;
}

std::map<QString, QString> TitanParser::parseMessage(std::vector<QString> &message)
{
    message[10] = message[10].replace(QObject::tr("0 CODE ( RPDU, № 1 - "), QString());
    message[10] = message[10].replace(QString(" ) "), QString(""));

    auto state = getState(message[10].toInt());
    auto time = parseDate(message[2], INPUT_DATE_FORMAT, OUTPUT_DATE_FORMAT);
    auto data = std::map<QString, QString>{{"name" , QObject::tr("RPDU")}, {"state" , state}, {"time", time}};

    return data;
}

} // namespace mantis
