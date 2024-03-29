/** @file
 * @brief     Database declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>

#include <boost/property_tree/ptree.hpp>

#include <vector>
#include <map>

namespace mantis
{

using Table = std::vector<std::map<QString, QString>>;

/**
 * Class describes Database
 */
class Database
{
public:
    explicit Database(boost::property_tree::ptree config);

    /**
     * Init database method
     */
    void init();

    /**
     * Send query to database method, returns selected from database data
     */
    Table sendQuery(const QString& queryString, bool selectTimeReported = true);

    /**
     * Method returns database opened status
     */
    bool opened();

private:
    boost::property_tree::ptree m_config;
    QSqlDatabase m_database;
    bool m_opened = false;
};
} // namespace mantis
