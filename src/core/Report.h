/** @file
 * @brief     Report interface declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Database.h"

#include <QString>

#include <map>
#include <vector>


namespace mantis
{

using ReportTable = std::vector<std::vector<QString>>;

/**
 * Interface for Report
 */
class Report
{

public:
    /**
     * Get report title
     */
    virtual QString title() = 0;

    /**
     * Get report subtype
     */
    virtual QString subtype() = 0;

    /**
     * Get report begin date
     */
    virtual QString beginDate() = 0;

    /**
     * Get report end date
     */
    virtual QString endDate() = 0;

    /**
     * Create time report table
     */
    virtual void createTimeReportTable(ReportTable& table) = 0;

    virtual ~Report() = default;
};

} // namespace mantis
