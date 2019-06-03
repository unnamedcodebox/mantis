/** @file
 * @brief     Titan Query declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "TitanQuery.h"

#include <QString>
#include <QStringList>

namespace mantis
{

TitanQuery::TitanQuery(AppName appName, QString beginDate, QString endDate):
    m_appName(std::move(appName)),
    m_beginDate(std::move(beginDate)),
    m_endDate(std::move(endDate))
{
    init();
}

void TitanQuery::init()
{
    auto parts = QStringList{};
    parts.push_back(
        "SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE \"appName\"='"
        + getAppName(m_appName) + "'");
    parts.push_back(
        m_beginDate.length() > 0 ? "AND \"timeReported\">='" + m_beginDate + "'"
                                 : "");
    parts.push_back("AND \"timeReported\"<='" + m_endDate + "'");
    parts.push_back("AND \"msg\" LIKE '%failure(agent199, )%'");
    parts.push_back("ORDER BY \"timeReported\";");

    m_query = parts.join(" ");
}

QString TitanQuery::get()
{
    return m_query;
}

} // namespace mantis

