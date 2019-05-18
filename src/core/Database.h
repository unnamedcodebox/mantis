/** @file
 * @brief     Database declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "AppName.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>

#include <boost/property_tree/ptree.hpp>

#include <vector>
#include <map>

namespace mantis
{

using Table = std::vector<std::map<QString, QString>>;

class Database
{

public:
    explicit Database(boost::property_tree::ptree config);

    /**
     * Init database connection
     */
    void init();

    Table sendQuery(const QString& queryString);

    bool opened();

private:
    boost::property_tree::ptree m_config;
    QSqlDatabase m_database;
    bool m_opened = false;
};

} // namespace mantis
