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

namespace {

std::unique_ptr<Query> createQuery(
    const QString& group,
    const QString& beginDate,
    const QString& endDate,
    const QStringList& deviceList = QStringList{})
{
    std::unique_ptr<Query> query;

    if (group == ORDINARY)
    {
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
    const QString& group,
    const QString& title,
    const QString& beginDate,
    const QString endDate,
    const QStringList& deviceList)
{
    std::unique_ptr<Report> report;

    if (group == ORDINARY)
    {
        report.reset(new OrdinaryReport());
    }
    else if (group == TITAN)
    {
        report.reset(new TitanReport());
    }
    else if (group == ISB)
    {
        report.reset(new IsbReport());
    }
    return report;
}

} // namespace

void ReportManager::createReport(QVariantMap reportInfo)
{
    using namespace report_properties;
    auto id = reportInfo[report_properties::ID].toString();
    auto group = reportInfo[report_properties::GROUP].toString();
    auto title = reportInfo[report_properties::TITLE].toString();
    auto subtype = reportInfo[report_properties::SUB_TYPE].toString();
    auto beginDate = reportInfo[report_properties::BEGIN_DATE].toString();
    auto endDate = reportInfo[report_properties::END_DATE].toString();
    auto deviceList = QStringList{};
    if (group == ORDINARY)
    {
        auto deviceList
            = reportInfo[report_properties::DEVICE_LIST].toStringList();
    }
    auto query = createQuery(group, beginDate, endDate, deviceList);
    auto parser = createParser(group);
    auto report = createReportFactoryMethod(
        group, title, beginDate, endDate, deviceList);
    qDebug() << group;

//    auto deviceList = map["device_list"].toStringList();
//    qDebug() << "this is my deviceList" << deviceList;
}

} // namespace mantis
