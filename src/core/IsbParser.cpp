/** @file
 * @brief     Isb devices parser implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */


#include "IsbParser.h"
#include "SplitDatabaseMessage.h"
#include <QObject>

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

IsbParser::IsbParser()
    : m_placement({ { "UPR", QObject::tr("Control building") },
                    { "TZ", QObject::tr("Technical building") },
                    { "KPP", QObject::tr("Control checkpoint") },
                    { "KTP", QObject::tr("Control Transport checkpoint") },
                    { "AP", QObject::tr("Aerials pavillion") } })
    , m_equipmentType({
          { "PCS", QObject::tr("Control state device") },
          { "PC", QObject::tr("SPVM") },
          { "SVI", QObject::tr("Videoserver") },
          { "SW", QObject::tr("Commutator") },
          { "SOP", QObject::tr("Server OPS") },
          { "AS", QObject::tr("Television IP-Camera" )},
          { "ARK", QObject::tr("Central processor block") },
          { "UPS", QObject::tr("Uninterrupted power supply") },
      })
{
}

ReportTable IsbParser::parseTable(Table& table)
{
    auto reportTable = ReportTable{};
    auto deviceStates = std::map<std::vector<QString>, QString>{};

    for (const auto& row: table)
    {
        auto parts = splitDatabaseMessage(row.at("msg"), AppName::PCS);
        auto data = parseMessage(parts);
        auto timeReported = row.at(TIME_REPORTED);
        auto deviceName = std::vector<QString>{ data.at(PLACEMENT),
                                                data.at(TYPE),
                                                data.at(THROUGH_ID),
                                                data.at(UNIQUE_ID) };
        if(deviceStates.find(deviceName) == deviceStates.end())
        {
            reportTable.push_back(
                { data.at(PLACEMENT),
                  data.at(TYPE),
                  data.at(THROUGH_ID),
                  data.at(UNIQUE_ID),
                  data.at(STATE),
                  data.at(BATTERY_STATE),
                  timeReported.replace("T", " ").remove(".000") });
            deviceStates[deviceName] = data.at(STATE);
        }
        else {
            if (deviceStates.at(deviceName) != data.at(STATE))
            {
                reportTable.push_back(
                    { data.at(PLACEMENT),
                      data.at(TYPE),
                      data.at(THROUGH_ID),
                      data.at(UNIQUE_ID),
                      data.at(STATE),
                      data.at(BATTERY_STATE),
                      timeReported.replace("T", " ").remove(".000") });
                deviceStates[deviceName] = data.at(STATE);
            }
        }

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

    switch (counter)
    {
    case 5:
        state = QObject::tr("OK");
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
