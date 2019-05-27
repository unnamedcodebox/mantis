/** @file
 * @brief     Ordinary Report implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "TitanReport.h"

namespace mantis
{
using namespace report_properties;

TitanReport::TitanReport(
    QString title,
    QString subtype,
    QString beginDate,
    QString endDate)
    : m_title(std::move(title))
    , m_subtype(std::move(subtype))
    , m_beginDate(std::move(beginDate))
    , m_endDate(std::move(endDate))
{
}

QString TitanReport::title()
{
    return m_title;
}

QString TitanReport::subtype()
{

}

QString TitanReport::beginDate()
{
    return m_beginDate;
}

QString TitanReport::endDate()
{
    return m_endDate;
}

void TitanReport::createTimeReportTable(ReportTable& table)
{
    // TODO
}

} // namespace mantis
