/** @file
 * @brief     Ordinary Report declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Report.h"

#include <QString>
#include <QStringList>

namespace mantis
{

/**
 * Class describes Report for Titan
 */
class TitanReport: public Report
{

public:
    /**
     * Reimplemented from Report
     */
    virtual QString title() override;

    /**
     * Reimplemented from Report
     */
    virtual QString subtype();

    /**
     * Reimplemented from Report
     */
    virtual QString beginDate() override;

    /**
     * Reimplemented from Report
     */
    virtual QString endDate() override;

    /**
     * Reimplemented from Report
     */
    virtual void createTimeReportTable(ReportTable& table) override;

private:
    QString m_title;
    QString m_beginDate;
    QString m_endDate;
    ReportTable m_reportTable;

};

} // namespace mantis
