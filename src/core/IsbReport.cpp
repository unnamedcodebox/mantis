/** @file
 * @brief     Ordinary Report implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "IsbReport.h"

namespace mantis
{
using namespace report_properties;

IsbReport::IsbReport(
    QString id,
    QString title,
    QString subtype,
    QString beginDate,
    QString endDate)
    : m_id(std::move(id))
    , m_title(std::move(title))
    , m_subtype(std::move(subtype))
    , m_beginDate(std::move(beginDate))
    , m_endDate(std::move(endDate))
{
}

QString IsbReport::id()
{
    return m_id;
}

QString IsbReport::title()
{
    return m_title;
}

QString IsbReport::subtype()
{
    return m_subtype;
}

QString IsbReport::beginDate()
{
    return m_beginDate;
}

QString IsbReport::endDate()
{
    return m_endDate;
}

const ReportTable &IsbReport::getReportTable() const
{
    return m_reportTable;
}

void IsbReport::setReportTable(ReportTable &table)
{
    m_reportTable = table;
}

void IsbReport::createTimeReportTable(ReportTable& table)
{
    // TODO
}

} // namespace mantis
