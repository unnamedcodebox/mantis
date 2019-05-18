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
namespace
{

const auto DRIVER = "driver";
const auto HOST_ADDRESS = "hostaddr";
const auto DB_NAME = "dbname";
const auto USERNAME = "username";
const auto PASSWORD = "password";

QSqlDatabase createDatabase(boost::property_tree::ptree config)
{
    if (!config.empty())
    {
        auto database = QSqlDatabase::addDatabase(
            QString::fromStdString(config.get<std::string>(DRIVER)));
        database.setHostName(
            QString::fromStdString(config.get<std::string>(HOST_ADDRESS)));
        database.setDatabaseName(
            QString::fromStdString(config.get<std::string>(DB_NAME)));
        database.setUserName(
            QString::fromStdString(config.get<std::string>(USERNAME)));

        boost::optional<boost::property_tree::ptree&> pass
            = config.get_child_optional(PASSWORD);
        if (pass)
        {
            database.setPassword(
                QString::fromStdString(config.get<std::string>(PASSWORD)));
        }

        return database;
    }
    return {};
}
} // namespace

Database::Database(boost::property_tree::ptree config)
{
    m_database = createDatabase(config);
}

Table Database::sendQuery(const QString& query)
{
    if (open())
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

bool Database::open()
{
    return m_database.open();
}

} // namespace mantis



