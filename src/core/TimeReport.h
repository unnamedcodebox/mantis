/** @file
 * @brief     Time Report declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Parser.h"

#include <QStringList>

namespace mantis
{

ReportTable createTimeReportTable(ReportTable& table, QStringList deviceList = QStringList{});
ReportTable createTitanTimeReportTable(ReportTable& table);
ReportTable createIsbTimeReportTable(ReportTable& table);

class TimeReport
{
    TimeReport(ReportTable& table, QStringList& deviceList);
private:
    ReportTable m_table;
    QStringList m_deviceList;
};

} // namespace mantis
