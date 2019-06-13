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

const auto ISB_SIMPLE_RANGE_TITLE = "A1:G1";
const auto ISB_SIMPLE_RANGE_INFO = "A2:G2";

const auto ISB_TIME_REPORT_RANGE_TITLE = "A1:D1";
const auto ISB_TIME_REPORT_RANGE_INFO = "A2:D2";

} // ranges

std::map<QString, QString> getFormatRanges(Headers type, QString subtype)
{
    using namespace ranges;
    switch (type)
    {
    case Headers::STANDARD:
        return subtype == SIMPLE_REPORT ? std::map<QString, QString>{ { TITLE_RANGE, STANDARD_RANGE_TITLE },
                 { INFO_RANGE, STANDARD_RANGE_INFO } } :
        std::map<QString, QString>{{ TITLE_RANGE, ISB_TIME_REPORT_RANGE_TITLE },
        { INFO_RANGE, ISB_TIME_REPORT_RANGE_INFO }};
    case Headers::ISB:
        return subtype == SIMPLE_REPORT
                   ? std::map<QString, QString>{ { TITLE_RANGE,
                                                   ISB_SIMPLE_RANGE_TITLE },
                                                 { INFO_RANGE,
                                                   ISB_SIMPLE_RANGE_INFO } }
                   : std::map<QString, QString>{
                         { TITLE_RANGE, ISB_TIME_REPORT_RANGE_TITLE },
                         { INFO_RANGE, ISB_TIME_REPORT_RANGE_INFO }
                     };
    case Headers::TITAN:
        return subtype == SIMPLE_REPORT
                   ? std::map<QString, QString>{ { TITLE_RANGE,
                                                   STANDARD_RANGE_TITLE },
                                                 { INFO_RANGE,
                                                   STANDARD_RANGE_TITLE } }
                   : std::map<QString, QString>{
                         { TITLE_RANGE, ISB_TIME_REPORT_RANGE_TITLE },
                         { INFO_RANGE, ISB_TIME_REPORT_RANGE_INFO }
                     };
    default:
        return {};
    }
}

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

Headers getHeadersType(QString id)
{
    std::map<QString, Headers> headersType{
        { device_id::COMMUTATION_STATION, Headers::STANDARD },
        { device_id::LOUDSPEAKER, Headers::STANDARD },
        { device_id::SNMP, Headers::STANDARD },
        { device_groups::TITAN, Headers::TITAN },
        { device_groups::ISB, Headers::ISB }
    };

    return headersType[id];
}

QStringList getHeaders(Headers type, QString subtype)
{
    static const auto headers = std::map<
        Headers,
        std::map<QString, QStringList>>{
        { Headers::STANDARD,
          { { SIMPLE_REPORT,
              { "Наименование", "Состояние", "Время перехода в состояние" } },
            { TIME_REPORT,
              { "Наименование", "Состояние", "Количество","Общее время в состоянии" } } } },
        { Headers::TITAN,
          { { SIMPLE_REPORT,
              { "Наименование", "Состояние", "Время перехода в состояние" } },
            { TIME_REPORT,
              { "Наименование", "Состояние", "Кол-во переходов", "Общее время в состоянии" } } } },

        { Headers::ISB,
          { { SIMPLE_REPORT,
              { "Размещение",
                "Тип",
                "Идентификатор",
                "Сквозной идентификатор",
                "Состояние",
                "Заряд батареи (только для UPS)" } },
            { TIME_REPORT,
              { "Название устройства (Расположение, Тип, Ун. ид., Сквозной "
                "ид.)",
                "Состояние",
                "Переходы в состояние",
                "Общее время в состоянии" } } } }
    };

    return headers.at(type).at(subtype);
}

std::shared_ptr<QXlsx::Document> createDocument(const std::shared_ptr<Report>& report)
{
    QTXLSX_USE_NAMESPACE

    auto document = std::make_shared<QXlsx::Document>();
    auto headersType
        = getHeadersType(report->id());
    auto headers = getHeaders(headersType, report->subtype());
    auto formatRanges = getFormatRanges(headersType, report->subtype());
    auto reportInfo = createReportInfo(report->beginDate(), report->endDate());
    document->write(cells::TITLE_CELL, report->title());
    document->write(cells::INFO_CELL, reportInfo);

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
        document->setColumnWidth(columnCounter, columnName.length() + 10);
        document->write(cells::HEADERS_ROW, columnCounter, columnName, headersFormat);
        ++columnCounter;
    }

    return document;
}

void writeReportTableToDocument(std::shared_ptr<QXlsx::Document> document,
                                std::shared_ptr<Report> report)
{
    auto rowCounter = cells::REPORT_TABLE_START_POSITION;

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

ReportWriter::ReportWriter(std::shared_ptr<Report> report):
    m_report(report)
{

}

void ReportWriter::writeReportToFile()
{
    QTXLSX_USE_NAMESPACE

    auto document = createDocument(m_report);
    writeReportTableToDocument(document, m_report);

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
