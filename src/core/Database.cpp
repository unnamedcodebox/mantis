/** @file
 * @brief     Database implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "Database.h"

#include <QtSql/QSql>
#include <QStringList>
#include <QVariant>

namespace mantis
{

const auto DRIVER = "driver";
const auto HOST_ADDRESS = "hostaddr";
const auto DB_NAME = "dbname";
const auto USERNAME = "username";
const auto PASSWORD = "password";

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
    }
}

Database::Database(boost::property_tree::ptree config):
    m_config(std::move(config))
{
   init();
}

Table Database::sendQuery(const QString& query)
{
    if (opened())
    {
        auto table = Table{};
        auto query = QSqlQuery{};
        query.exec();

        while (query.next())
        {
            QString timeReported = query.value("timeReported").toString();
            QString msg = query.value("msg").toString();
        }

    }
}

bool Database::opened()
{
    return m_opened;
}

} // namespace mantis



