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
#include <QRegExp>

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

    Table sendQuery(const QString& query);

    inline bool isOpened() const
    {
        return m_opened;
    }

private:
   boost::property_tree::ptree m_config;
   QSqlDatabase m_database;
   QSqlQuery m_query;
   bool m_opened = false;
};

} // namespace mantis
