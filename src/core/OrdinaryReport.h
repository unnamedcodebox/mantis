/** @file
 * @brief     Ordinary Report declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Report.h"

#include "Properties.h"

#include <QString>
#include <QStringList>

namespace mantis
{

/**
 * Class describes Report for group Ordinary
 */
class OrdinaryReport: public Report
{

public:
    OrdinaryReport(
        QString id,
        QString title,
        QString subtype,
        QString beginDate,
        QString endDate,
        QStringList deviceList);

    /**
     * Reimplemented from Report
     */
    virtual QString id() override;

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
    virtual const ReportTable& getReportTable() const override;

    /**
     * Reimplemented from Report
     */
    virtual void setReportTable(ReportTable& table) override;

    /**
     * Reimplemented from Report
     */
    virtual void createTimeReportTable(ReportTable& table) override;

private:
    QString m_id;
    QString m_title;
    QString m_subtype;
    QString m_beginDate;
    QString m_endDate;
    QStringList m_deviceList;
    ReportTable m_reportTable;

};

} // namespace mantis
