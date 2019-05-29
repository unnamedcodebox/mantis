/** @file
 * @brief     Report Writer declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Report.h"

#include <QString>
#include <QStringList>

#include <memory>

namespace mantis
{

enum class Headers : int
{
    STANDARD,
    ISB
};

/**
 * Class using for writing report to file
 */
class ReportWriter
{
public:
    explicit ReportWriter(Headers type);
    /**
     * Method using for writing report to file
     */
    void writeReportToFile(const std::shared_ptr<Report>& report);
private:
    Headers m_headersType;
    QString m_info;

};

} // namespace mantis
