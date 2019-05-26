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
