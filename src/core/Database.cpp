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

Database::Database(boost::property_tree::ptree config)
{
    if (!config.empty())
    {
        m_database = QSqlDatabase::addDatabase("QPSQL");
        m_database.setHostName("127.0.0.1");
        m_database.setDatabaseName("SBAJournal");
        m_database.setUserName("phpuser");
    }
}

Table Database::sendQuery(const QString& query)
{
    if (open())
    {
        auto table = Table{};
        auto query = QSqlQuery{};
        query.exec("SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE "
                   "\"appName\"='ics' AND \"timeReported\">='01/03/2019' AND "
                   "\"timeReported\"<'03/04/2019' AND \"msg\" LIKE "
                   "'%failure(agent199, )%' ORDER BY \"timeReported\";");

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



