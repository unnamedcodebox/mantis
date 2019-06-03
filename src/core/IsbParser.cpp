/** @file
 * @brief     Isb devices parser implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */


#include "IsbParser.h"
#include "SplitDatabaseMessage.h"

#include <QRegExp>

#include <QDebug>

namespace mantis
{
const auto PLACEMENT = "placement";
const auto TYPE = "type";
const auto THROUGH_ID = "throughId";
const auto UNIQUE_ID = "uniqueId";
const auto STATE = "state";
const auto BATTERY_STATE = "batteryState";
const auto TIME_REPORTED = "timeReported";

IsbParser::IsbParser(
    std::map<QString, QString> placement,
    std::map<QString, QString> type,
    std::map<QString, QString> subsystemId)
    : m_placement(std::move(placement))
    , m_equipmentType(std::move(type))
    , m_subsystemId(std::move(subsystemId))
{
}

ReportTable IsbParser::parseTable(Table& table)
{
    auto reportTable = ReportTable{};

    for (const auto& row: table)
    {
        auto parts = splitDatabaseMessage(row.at("msg"), AppName::PCS);
        auto data = parseMessage(parts);
        auto timeReported = row.at(TIME_REPORTED);
        reportTable.push_back(
            { data.at(PLACEMENT),
              data.at(TYPE),
              data.at(THROUGH_ID),
              data.at(UNIQUE_ID),
              data.at(STATE),
              data.at(BATTERY_STATE),
              timeReported.replace("T", " ").remove(".000") });
    }

    return reportTable;
}

std::map<QString, QString>
IsbParser::parseMessage(std::vector<QString>& message)
{

    auto counter = message.size();
    auto placement = QString{};
    auto type = QString{};
    auto subsystemId = QString{};
    auto batteryState = QString{};
    auto state = QString{};

    if (m_placement.find(message[0]) != m_placement.end())
    {
        placement = m_placement[message[0]];
    }
    else
    {
        for (const auto& encode: m_placement)
        {
            auto contains = message[0].contains(encode.first, Qt::CaseInsensitive);

            //        auto match
            //            = QRegExp(encode.first, Qt::CaseInsensitive,
            //            QRegExp::Wildcard)
            //                  .indexIn(message[0]);
            //        if (match == 0)
            //        {
            //            if (encode.first == message[0])
            //            {
            //                placement = encode.second;
            //                break;
            //            }
            //            else
            //            {
            //                placement
            //                    = message[0].replace(QRegExp(encode.first),
            //                    encode.second);
            //            }
            //        }
            if (contains)
            {
                if (QString::
                        compare(encode.first, message[0], Qt::CaseInsensitive)
                    == 0)
                {
                    placement = encode.second;
                }
                else
                {
                    placement = message[0].replace(
                        QRegExp(encode.first), encode.second + " ");
                }
            }
        }
    }

    type = m_equipmentType[message[1]];

    //    auto idFind = m_subsystemBitIdentifier.find(message[4])
    //    subsystemId = m_subsystemBitIdentifier[]

    switch (counter)
    {
    case 5:
        state = "Исправно";
        break;
    case 6:
        state = message[5];
        break;
    case 7:
        state = message[6];
        break;
    }

    batteryState = (counter == 7) ? message[5] : "---";

    auto data = std::map<QString, QString>{
        { PLACEMENT, placement }, { TYPE, type },
        { THROUGH_ID, message[2] }, { UNIQUE_ID, message[3] },
        { STATE, state },         { BATTERY_STATE, batteryState }
    };

    return data;
}

} // namespace mantis
