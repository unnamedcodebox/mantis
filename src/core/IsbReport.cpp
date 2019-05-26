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

QString IsbReport::title()
{
    return m_title;
}

QString IsbReport::subtype()
{

}

QString IsbReport::beginDate()
{
    return m_beginDate;
}

QString IsbReport::endDate()
{
    return m_endDate;
}

void IsbReport::createTimeReportTable(ReportTable& table)
{
    // TODO
}

} // namespace mantis
