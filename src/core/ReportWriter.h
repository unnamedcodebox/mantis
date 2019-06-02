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

namespace QXlsx
{
class Document;
}

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

    explicit ReportWriter(std::shared_ptr<Report> report);

    /**
     * Method using for writing report to file
     */
    void writeReportToFile();

private:
    std::shared_ptr<Report> m_report;
    std::shared_ptr<QXlsx::Document> m_document;

};

} // namespace mantis
