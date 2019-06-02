/** @file
 * @brief     Ordinary Report implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "OrdinaryReport.h"

namespace mantis
{

using namespace report_properties;

OrdinaryReport::OrdinaryReport(
    QString id,
    QString title,
    QString subtype,
    QString beginDate,
    QString endDate,
    QStringList deviceList)
    : m_id(std::move(id))
    , m_title(std::move(title))
    , m_subtype(std::move(subtype))
    , m_beginDate(std::move(beginDate))
    , m_endDate(std::move(endDate))
    , m_deviceList(std::move(deviceList))
{
}

QString OrdinaryReport::id()
{
    return m_id;
}

QString OrdinaryReport::title()
{
    return m_title;
}

QString OrdinaryReport::subtype()
{
    return m_subtype;
}

QString OrdinaryReport::beginDate()
{
    return m_beginDate;
}

QString OrdinaryReport::endDate()
{
    return m_endDate;
}

const ReportTable &OrdinaryReport::getReportTable() const
{
    return m_reportTable;
}

void OrdinaryReport::setReportTable(ReportTable &table)
{
    m_reportTable = table;
}

void OrdinaryReport::createTimeReportTable(ReportTable& table)
{
    // TODO
}

} // namespace mantis
