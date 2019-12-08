/** @file
 * @brief     Report Writer implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ReportWriter.h"

#include "Properties.h"

#include <QDateTime>
#include <QFont>
#include <QFontMetrics>
#include <QtXlsx>
#include "xlsxformat.h"

#include <stdlib.h>

namespace mantis
{

using namespace device_groups;
using namespace report_properties;
using namespace report_subtypes;

namespace
{

namespace cells
{

const auto TITLE_CELL = "A1";
const auto INFO_CELL = "A2";

const auto HEADERS_ROW = 3;
const auto REPORT_TABLE_START_POSITION = 4;

} // cells

namespace ranges
{
const auto TITLE_RANGE = "titleRange";
const auto INFO_RANGE = "infoRange";

const auto STANDARD_RANGE_TITLE = "A1:C1";
const auto STANDARD_RANGE_INFO = "A2:C2";

const auto TIME_REPORT_RANGE_TITLE = "A1:D1";
const auto TIME_REPORT_RANGE_INFO = "A2:D2";

} // ranges

QString createReportInfo(QString beginDate, QString endDate)
{
    return QObject::tr("Report created from period on %1 to %2").arg(beginDate,endDate);
}

QString createFileName()
{
    return QDateTime::currentDateTime().toString("MM_dd_yyyy_hh_mm") + ".xlsx";
}

QString createPath(const QString& reportId, const QString& reportSubtype)
{
    auto path = QString{ "/home/%1/Documents/Reports/%2/%3/" }.arg(
        QString::fromStdString(std::string(getenv("USER"))), reportId, reportSubtype);

    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(path);
    }

    return path;
}

QStringList getDefaultHeaders(QString subtype)
{
    auto headers = std::map<QString, QStringList>{
        { SIMPLE_REPORT,
          QStringList{
              "Наименование", "Состояние", "Время перехода в состояние" } },
        { TIME_REPORT,
          { "Наименование",
            "Состояние",
            "Кол-во переходов",
            "Общее время в состоянии" } }
    };

    return headers.at(subtype);
}

std::map<QString, QString> getDefaultFormatRanges(QString subtype)
{
    using namespace ranges;
    return subtype == SIMPLE_REPORT
               ? std::map<QString, QString>{ { TITLE_RANGE,
                                               STANDARD_RANGE_TITLE },
                                             { INFO_RANGE,
                                               STANDARD_RANGE_INFO } }
               : std::map<QString, QString>{
                     { TITLE_RANGE, TIME_REPORT_RANGE_TITLE },
                     { INFO_RANGE, TIME_REPORT_RANGE_INFO }
                 };
}

std::map<QString, QString> createFormatRanges(QString subtype, DocumentConfiguration config)
{
    using namespace ranges;
    auto ranges = std::map<QString, QString>{};

    if(config.titleRange.is_initialized() & config.infoRange.is_initialized())
    {
            ranges = { { TITLE_RANGE,
                         QString::fromStdString(*config.titleRange) },
                       { INFO_RANGE,
                         QString::fromStdString(*config.infoRange)} };
    }
    else {
        ranges = getDefaultFormatRanges(subtype);
    }

    return ranges;
}

std::shared_ptr<QXlsx::Document> createDocument(const std::shared_ptr<Report>& report, const DocumentConfiguration& conf)
{
    QTXLSX_USE_NAMESPACE

    auto document = std::make_shared<QXlsx::Document>();
    if(conf.useDefaults)
    {
        auto headers = getDefaultHeaders(report->subtype());
        auto formatRanges = getDefaultFormatRanges(report->subtype());
        auto reportInfo = createReportInfo(report->beginDate(), report->endDate());
        document->write(cells::TITLE_CELL, report->title());
        document->write(cells::INFO_CELL, reportInfo);

        Format titleFormat;
        titleFormat.setHorizontalAlignment(Format::AlignHCenter);
        titleFormat.setVerticalAlignment(Format::AlignVCenter);
        auto headersFormat = titleFormat;
        headersFormat.setFontBold(true);

        document
            ->mergeCells(formatRanges.at(ranges::TITLE_RANGE), headersFormat);
        document->mergeCells(formatRanges.at(ranges::INFO_RANGE), titleFormat);

        auto columnCounter = 1;

        for (const auto& columnName : headers)
        {
            document->setColumnWidth(columnCounter, columnName.length() + 20);
            document->write(
                cells::HEADERS_ROW, columnCounter, columnName, headersFormat);
            ++columnCounter;
        }
    }
    else
    {
        auto headers = conf.headers ? *conf.headers
                                    : getDefaultHeaders(report->subtype());
        auto formatRanges = createFormatRanges(report->subtype(), conf);
        auto reportInfo
            = conf.infoString
                  ? QString::fromStdString(*conf.infoString)
                  : createReportInfo(report->beginDate(), report->endDate());
        document->write(
            conf.titleCell ? QString::fromStdString(*conf.titleCell)
                           : cells::TITLE_CELL, conf.title ? QString::fromStdString(*conf.title) :
            report->title());
        document->write(conf.infoCell ? QString::fromStdString(*conf.infoCell) : cells::INFO_CELL, reportInfo);

        Format titleFormat;
        titleFormat.setHorizontalAlignment(Format::AlignHCenter);
        titleFormat.setVerticalAlignment(Format::AlignVCenter);
        auto headersFormat = titleFormat;
        headersFormat.setFontBold(true);

        document->mergeCells(formatRanges.at(ranges::TITLE_RANGE), headersFormat);
        document->mergeCells(formatRanges.at(ranges::INFO_RANGE), titleFormat);

        auto columnCounter = 1;

        for (const auto& columnName: headers)
        {
            document->setColumnWidth(columnCounter, columnName.length() + 20);
            document->write(conf.headersRow ? *conf.headersRow : cells::HEADERS_ROW, columnCounter, columnName, headersFormat);
            ++columnCounter;
        }
    }

    return document;
}

void writeReportTableToDocument(std::shared_ptr<QXlsx::Document> document,
                                std::shared_ptr<Report> report, const DocumentConfiguration& conf)
{
    auto rowCounter = cells::REPORT_TABLE_START_POSITION;

    if(!conf.useDefaults)
    {
        if(conf.reportTableStartPosition)
        {
            rowCounter = *conf.reportTableStartPosition;
        }
    }

    for(const auto& row : report->getReportTable())
    {
        auto columnCounter = 1;
        for (const auto& column : row)
        {
            document->write(rowCounter, columnCounter, column);
            ++columnCounter;
        }
        ++rowCounter;
    }
}

} // anonymous

ReportWriter::ReportWriter(std::shared_ptr<Report> report, const DocumentConfiguration &config):
    m_report(report), m_conf(config)
{

}

void ReportWriter::writeReportToFile()
{
    QTXLSX_USE_NAMESPACE

    auto document = createDocument(m_report, m_conf);
    writeReportTableToDocument(document, m_report, m_conf);

    auto path = createPath(m_report->id(), m_report->subtype());
    auto fileName = createFileName();
    m_reportPath = path + fileName;
    document->saveAs(m_reportPath);
}

QString ReportWriter::createdReportPath()
{
    return m_reportPath;
}

} // namespace mantis
