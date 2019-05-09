/** @file
 * @brief     Isb devices parser declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Parser.h"

#include <map>
#include <vector>
#include <QString>


namespace mantis
{

namespace  {

std::map<QString, QString> initPlacement
    = { { "UPR", "Здание управления" },
        { "TZ", "Техническое здание" },
        { "KPP", "Контрольно-пропускной пункт" },
        { "KTP", "Контрольно-транспортный пункт" },
        { "AP", "Антенный павильон" } };

std::map<QString, QString> initType = {
    { "PCS", "Прибор контроля состояния (ПКС)" },
    { "PC", "СПЭВМ" },
    { "SVI", "Видеосервер" },
    { "SW", "Коммутатор" },
    { "SOP", "Сервер ОПС" },
    { "AS", "Телевизионная IP-камера" },
    { "ARK", "Блок центральный процессорный" },
    { "UPS", "Источник бесперебойного питания" },
};

std::map<QString, QString> initSubsystemId
    = { { "0x01", "Система охранной сигнализации" },
        { "0x02", "Система охранного телевидения" },
        { "0x04", "Система пожарной сигнализации" },
        { "0x08", "Система оповещения и управления эвакуацией" },
        { "0x10", "Система контроля и управления доступом" },
        { "0x20",
          "Система передачи данных и сетевого компьютерного управления" },
        { "0x40", "Система бесперебойного питания" } };

//std::map<QString, QString> uniqueId = {
//    { "8", "DELTA RT1K" },
//    { "7", "IKS-G6524A-4GTXFSP-HV-HV" },
//    { "35", "IP-камера AXIS P1365E - MK II" },
//    { "32", "IP-камера AXIS P3225 - LVE" },
//    { "33", "IP-камера AXIS P3225 - LVE" },
//    { "34", "IP-камера AXIS Q1765 - LE" },
//    { "11", "БЦП Р-08" },
//    { "12", "БЦП Р-08" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },
//    { "9", "DELTA RT1K" },

//};

} // anonymous

class IsbParser: public Parser
{

public:
    IsbParser(
        std::map<QString, QString> placement = initPlacement,
        std::map<QString, QString> type = initType,
        std::map<QString, QString> subsystemId = initSubsystemId);

    /**
     * Reimplemented from Parser
     */
    virtual ReportTable parseTable(Table& table) override;

    /**
     * Reimplemented from Parser
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) override;

private:
    std::map<QString, QString> m_placement;
    std::map<QString, QString> m_equipmentType;
    std::map<QString, QString> m_subsystemId;
    std::map<QString, QString> m_uniqueId;

};

} // namespace mantis
