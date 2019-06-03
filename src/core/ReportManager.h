/** @file
 * @brief     Report Manager declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Database.h"
#include "Query.h"
#include "Parser.h"
#include "Report.h"
#include "ReportWriter.h"

#include <QObject>
#include <QVariantMap>

namespace mantis
{

/**
 * Class describes manager using for report creation and write it to file
 */
class ReportManager: public QObject
{
    Q_OBJECT
public:
    ReportManager(std::shared_ptr<Database> database);

public slots:

    /**
     * Create report based on report info: id, title, group etc
     */
    void createReport(QVariantMap reportInfo);

signals:
    void reportCreated(QString message);

private:
    std::shared_ptr<Database> m_database;
    std::unique_ptr<Query> m_query;
    std::unique_ptr<Parser> m_parser;
    std::shared_ptr<Report> m_report;
    std::unique_ptr<ReportWriter> m_writer;

};

} // namespace mantis
