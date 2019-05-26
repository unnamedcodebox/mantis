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

QString OrdinaryReport::title()
{
    return m_title;
}

QString OrdinaryReport::subtype()
{

}

QString OrdinaryReport::beginDate()
{
    return m_beginDate;
}

QString OrdinaryReport::endDate()
{
    return m_endDate;
}

void OrdinaryReport::createTimeReportTable(ReportTable& table)
{
    // TODO
}

} // namespace mantis
