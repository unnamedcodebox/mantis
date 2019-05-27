/** @file
 * @brief     ISB Query declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Query.h"

#include <QString>
#include <QStringList>

namespace mantis
{

/**
 * Class implements query for ISB system
 */
class IsbQuery: public Query
{
public:
    IsbQuery(
        AppName appName,
        QString beginDate,
        QString endDate);

    /**
     * Reimplemented from Query
     */
    virtual void init() override;

    /**
     * Reimplemented from Query
     */
    virtual QString get() override;

private:
    AppName m_appName;
    QString m_beginDate;
    QString m_endDate;
    QString m_query;
};

} // namespace mantis
