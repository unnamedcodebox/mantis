/** @file
 * @brief     Report Manager implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ReportManager.h"

#include "Properties.h"

#include "OrdinaryParser.h"
#include "QueryOrdinary.h"
#include "OrdinaryReport.h"
#include "TitanParser.h"
#include "TitanQuery.h"
#include "TitanReport.h"
#include "IsbParser.h"
#include "IsbQuery.h"
#include "IsbReport.h"

#include <QDebug>

#include <memory>

namespace mantis
{

using namespace device_groups;
using namespace report_properties;

namespace {

std::unique_ptr<Query> createQuery(
    QVariantMap reportInfo)
{
    std::unique_ptr<Query> query;
    auto group = getReportProperty(reportInfo, GROUP);
    auto beginDate = getReportProperty(reportInfo, BEGIN_DATE);
    auto endDate = getReportProperty(reportInfo, END_DATE);

    if (group == ORDINARY)
    {
        auto deviceList = getDeviceList(reportInfo);
        query.reset(
            new QueryOrdinary(AppName::ICS, deviceList, beginDate, endDate));
    }
    else if (group == TITAN)
    {
        query.reset(new TitanQuery(AppName::ICS, beginDate, endDate));
    }
    else if (group == ISB)
    {
        query.reset(new IsbQuery(AppName::PCS, beginDate, endDate));
    }
    return query;
}

std::unique_ptr<Parser> createParser(const QString& group)
{
    std::unique_ptr<Parser> parser;

    if (group == ORDINARY)
    {
        parser.reset(new OrdinaryParser());
    }
    else if (group == TITAN)
    {
        parser.reset(new TitanParser());
    }
    else if (group == ISB)
    {
        parser.reset(new IsbParser());
    }
    return parser;
}

std::unique_ptr<Report> createReportFactoryMethod(
    QVariantMap reportInfo)
{
    std::unique_ptr<Report> report;
    auto group = getReportProperty(reportInfo, GROUP);
    auto title = getReportProperty(reportInfo, TITLE);
    auto beginDate = getReportProperty(reportInfo, BEGIN_DATE);
    auto endDate = getReportProperty(reportInfo, END_DATE);
    auto subtype = getReportProperty(reportInfo, SUB_TYPE);

    if (group == ORDINARY)
    {
        auto deviceList = getDeviceList(reportInfo);
        report.reset(new OrdinaryReport(title, subtype, beginDate, endDate, deviceList));
    }
    else if (group == TITAN)
    {
        report.reset(new TitanReport(title, subtype, beginDate, endDate));
    }
    else if (group == ISB)
    {
        report.reset(new IsbReport(title, subtype, beginDate, endDate));
    }
    return report;
}

} // namespace

ReportManager::ReportManager(std::shared_ptr<Database> database):
    m_database(std::move(database))
{

}

void ReportManager::createReport(QVariantMap reportInfo)
{
    using namespace report_properties;

    auto group = getReportProperty(reportInfo, GROUP);
    // todo: add update method
    m_query = createQuery(reportInfo);
    m_parser = createParser(group);
    m_report = createReportFactoryMethod(reportInfo);
    // todo: add create report method
    auto table = m_database->sendQuery(m_query->get());
    auto reportTable = m_parser->parseTable(table);
    m_report->setReportTable(reportTable);
    // todo: add write report method
    qDebug() << m_query->get();

    if(m_report->subtype() == report_subtypes::TIME_REPORT)
    {
        m_report->createTimeReportTable(reportTable);
    }

    //todo: add file writer

    //    auto deviceList = map["device_list"].toStringList();
    //    qDebug() << "this is my deviceList" << deviceList;
}

} // namespace mantis
