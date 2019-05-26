/** @file
 * @brief     Report Manager declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Database.h"

#include <QVariantMap>

namespace mantis
{

/**
 * Class describes manager using for report creation and write it to file
 */
class ReportManager
{
public:
    /**
     * Create report based on report info: it, title, group etc
     */
    void createReport(QVariantMap reportInfo);

};

} // namespace mantis
