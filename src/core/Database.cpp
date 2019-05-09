/** @file
 * @brief     Database implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "Database.h"

#include <QtSql/QSql>

#include <QDebug>

#include <QStringList>

#include <iostream>

namespace mantis
{

Database::Database(boost::property_tree::ptree config):
    m_config(std::move(config))
{
    m_database = QSqlDatabase::addDatabase("QPSQL");
//    m_database.setHostName("172.31.1.226");
    m_database.setHostName("127.0.0.1");
    m_database.setDatabaseName("SBAJournal");
    m_database.setUserName("phpuser");

    m_opened = m_database.open();

    if (m_opened)
    {
//        m_query = QSqlQuery{};
//        m_query.exec("SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE "
//                     "\"appName\"='ics' AND \"timeReported\">='01/03/2019' AND "
//                     "\"timeReported\"<'03/04/2019' AND \"msg\" LIKE "
//                     "'%failure(agent199, )%' ORDER BY \"timeReported\";");

//        while (m_query.next())
//        {
//            QString timeReported = m_query.value("timeReported").toString();
//            QString msg = m_query.value("msg").toString();
//            qDebug() << timeReported << msg;
//        }
    }
}

} // namespace mantis



