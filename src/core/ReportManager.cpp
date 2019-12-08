/** @file
 * @brief     Report Manager implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ReportManager.h"

#include "Properties.h"

#include "ConfigReader.h"
#include "OrdinaryParser.h"
#include "OrdinaryQuery.h"
#include "OrdinaryParser.h"
#include "OrdinaryReport.h"

#include <QDebug>

#include <memory>

namespace mantis
{

using namespace device_groups;
using namespace report_properties;

namespace {

enum class Status: int
{
    SUCCESS
};

QString getStatusMessage(Status status)
{
    switch(status)
    {
    case Status::SUCCESS:
    return QObject::tr("Report successfully created");
    }
}

std::unique_ptr<Parser> createParser(const QString& group)
{
    std::unique_ptr<Parser> parser;

    auto configFile = "reports_configuration/" + group.toStdString() + "/parser.json";

    auto configuration = config::readParserConfiguration(configFile);

    parser.reset(new OrdinaryParserNew(configuration));


    return parser;
}

DocumentConfiguration createDocumentConfiguration(const QString& id, const QString& subtype)
{
    auto configFile = "reports_configuration/" + id.toStdString() + "/document.json";

    auto configuration = config::readDocumentConfiguration(configFile, subtype.toStdString());

    return configuration;

}

QueryConfiguration createQueryConfiguration(const QString& id)
{
    auto configFile = "reports_configuration/" + id.toStdString() + "/query.json";

    auto configuration = config::readQueryConfiguration(configFile);

    return configuration;
}

std::unique_ptr<Query> createQuery(
    QVariantMap reportInfo)
{
    std::unique_ptr<Query> query;
    auto id = getReportProperty(reportInfo, ID);
    auto group = getReportProperty(reportInfo, GROUP);
    auto beginDate = getReportProperty(reportInfo, BEGIN_DATE);
    auto endDate = getReportProperty(reportInfo, END_DATE);

    if (group == ORDINARY)
    {
        auto deviceList = getDeviceList(reportInfo);
        auto config = createQueryConfiguration(id);
        query.reset(
            new OrdinaryQuery(deviceList, beginDate, endDate, config));
    }

    return query;
}

std::shared_ptr<Report> createReportFactoryMethod(
    QVariantMap reportInfo)
{
    auto group = getReportProperty(reportInfo, GROUP);
    auto id = getReportProperty(reportInfo, ID);
    auto title = getReportProperty(reportInfo, TITLE);
    auto beginDate = getReportProperty(reportInfo, BEGIN_DATE);
    auto endDate = getReportProperty(reportInfo, END_DATE);
    auto subtype = getReportProperty(reportInfo, SUB_TYPE);

    if (group == ORDINARY)
    {
        auto deviceList = getDeviceList(reportInfo);
        return std::make_shared<OrdinaryReport>(id, title, subtype, beginDate, endDate, deviceList);
    }

    return {};
}

} // namespace

ReportManager::ReportManager(boost::property_tree::ptree config):
    m_config(config)
{

}

void ReportManager::start()
{
    m_database = std::make_shared<Database>(m_config);
}

void ReportManager::createReport(QVariantMap reportInfo)
{
    using namespace report_properties;

    auto group = getReportProperty(reportInfo, GROUP);
    auto id = getReportProperty(reportInfo, ID);

    m_query = createQuery(reportInfo);

    m_parser = createParser(id);
    m_report = createReportFactoryMethod(reportInfo);

    auto table = m_database->sendQuery(m_query->get());
    qDebug() << table;
    auto reportTable = m_parser->parseTable(table);
    qDebug() << reportTable;
    m_report->setReportTable(reportTable);

    if (m_report->subtype() == report_subtypes::TIME_REPORT)
    {
        m_report->createTimeReportTable(reportTable);
    }

    auto documentConfig = createDocumentConfiguration(id, m_report->subtype());
    m_writer = std::make_unique<ReportWriter>(m_report, documentConfig);
    m_writer->writeReportToFile();

    emit reportCreated(getStatusMessage(Status::SUCCESS));
    emit sendReportPath(m_writer->createdReportPath());
}

} // namespace mantis
