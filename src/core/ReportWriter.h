/** @file
 * @brief     Report Writer declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Report.h"
#include "Configuration.h"

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
    ISB,
    TITAN
};

/**
 * Class using for writing report to file
 */
class ReportWriter
{
public:

    ReportWriter(std::shared_ptr<Report> report, const DocumentConfiguration& config);

    /**
     * Method using for writing report to file
     */
    void writeReportToFile();

    /**
     * Get created report path
     */
    QString createdReportPath();


private:
    std::shared_ptr<Report> m_report;
    std::shared_ptr<QXlsx::Document> m_document;
    QString m_reportPath;
    DocumentConfiguration m_conf;

};

} // namespace mantis
