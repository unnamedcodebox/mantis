/** @file
 * @brief     Database implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "Database.h"

#include "Properties.h"

#include <QDebug>
#include <QtSql/QSql>
#include <QStringList>
#include <QVariant>

namespace mantis
{

using namespace database_properties;

void Database::init()
{
    if (!m_config.empty())
    {
        m_database = QSqlDatabase::addDatabase(
            QString::fromStdString(m_config.get<std::string>(DRIVER)));
        m_database.setHostName(
            QString::fromStdString(m_config.get<std::string>(HOST_ADDRESS)));
        m_database.setDatabaseName(
            QString::fromStdString(m_config.get<std::string>(DB_NAME)));
        m_database.setUserName(
            QString::fromStdString(m_config.get<std::string>(USERNAME)));

        boost::optional<boost::property_tree::ptree&> pass
            = m_config.get_child_optional(PASSWORD);
        if (pass)
        {
            m_database.setPassword(
                QString::fromStdString(m_config.get<std::string>(PASSWORD)));
        }
        m_opened = m_database.open();
        qDebug() << "CONNECTED TO DATABASE: " << m_opened;
    }
}

Database::Database(boost::property_tree::ptree config):
    m_config(std::move(config))
{
   init();
}

Table Database::sendQuery(const QString& queryString, bool selectTimeReported)
{
    if (opened())
    {
        auto table = Table{};
        auto query = QSqlQuery{};
        query.exec(queryString);
        qDebug() << "Query size is: " << query.size();

        while (query.next())
        {
            auto part = std::map<QString, QString>();
            if(selectTimeReported)
            {
                part[TIME_REPORTED] = query.value(TIME_REPORTED).toString();
            }
            part[MESSAGE] = query.value(MESSAGE).toString();
            table.push_back(part);
        }
        return table;
    }
    return {};
}

bool Database::opened()
{
    return m_opened;
}

} // namespace mantis



