/** @file
 * @brief     Ordinary Query implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "QueryOrdinary.h"

#include <QObject>

namespace mantis
{

QueryOrdinary::QueryOrdinary(
    AppName appName, QStringList deviceList, QString beginDate, QString endDate):
    m_appName(std::move(appName)),
    m_deviceList(std::move(deviceList)),
    m_beginDate(std::move(beginDate)),
    m_endDate(std::move(endDate))
{
    init();
}

void QueryOrdinary::init()
{
//    TODO: devices empty checking
    auto devices = m_deviceList.join("|");
    auto parts = QStringList{};
    parts.push_back(
        "SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE \"appName\"='"
        + getAppName(m_appName) + "'");
    parts.push_back(
        m_beginDate.length() > 0 ? "AND \"timeReported\">='" + m_beginDate+ "'" : "");
    parts.push_back("AND \"timeReported\"<='" + m_endDate + "'");
    parts.push_back("AND \"msg\" LIKE " + QObject::tr("'%State update%'"));
    parts.push_back("AND \"msg\" SIMILAR to '%(" + devices + ")%'");
    parts.push_back("ORDER BY \"timeReported\";");

    m_query = parts.join(" ");
}

QString QueryOrdinary::get()
{
    return m_query;
}

}; // namespace mantis
