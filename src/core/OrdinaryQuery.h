/** @file
 * @brief     Ordinary Query declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Query.h"
#include "Configuration.h"

#include <QString>
#include <QStringList>

namespace mantis
{
/**
 * Class using for implement query for ordinary devices
 */
class OrdinaryQuery: public Query
{
public:
    OrdinaryQuery(
        QStringList deviceList,
        QString beginDate,
        QString endDate, QueryConfiguration configuration);

    /**
     * Reimplemented from Query
     */
    virtual void init() override;

    /**
     * Reimplemented from Query
     */
    virtual QString get() override;

    QueryConfiguration& config();

private:
    QStringList m_deviceList;
    QString m_beginDate;
    QString m_endDate;
    QString m_query;
    QueryConfiguration m_conf;
};

} // namespace mantis
