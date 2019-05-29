/** @file
 * @brief     Report Writer implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ReportWriter.h"

#include "Properties.h"

#include <QtXlsx>
#include "xlsxformat.h"

#include <stdlib.h>


namespace mantis
{
using namespace device_groups;
using namespace report_properties;
using namespace report_subtypes;

QStringList getHeaders(Headers type, QString subtype)
{
    static const auto headers = std::map<
        Headers,
        std::map<QString, QStringList>>{
        { Headers::STANDARD,
          { { SIMPLE_REPORT,
              { "Наименование", "Состояние", "Время перехода в состояние" } },
            { TIME_REPORT,
              { "Наименование", "Состояние", "Общее время в состоянии" } } } },

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

ReportWriter::ReportWriter(Headers type) : m_headersType(std::move(type)) {}

void ReportWriter::writeReportToFile(const std::shared_ptr<Report>& report)
{
    QTXLSX_USE_NAMESPACE

    QXlsx::Document document;
    auto headers = getHeaders(m_headersType, report->subtype());
    document.write("A1", report->title());
    auto counter = 1;
    Format titleFormat;
    titleFormat.setHorizontalAlignment(Format::AlignHCenter);
    titleFormat.setVerticalAlignment(Format::AlignVCenter);
    titleFormat.setTextWarp(true);

    document.mergeCells("A1:C1", titleFormat);
    ++counter;
    auto columnCounter = 0;
    for (const auto& column : headers)
    {
        document.write(counter,columnCounter, column);
        ++columnCounter;
    }

//    auto www = std::vector<QString>{};
//    for(auto& it : www)
//    {
//        document.write("A" + QString::number(counter), it);
//        ++counter;
//    }

    auto path = QString{"/home/" + QString::fromStdString(std::string(getenv("USER"))) + "/Documents/Reports/"};
    QDir dir(path);
    if (!dir.exists()){
      dir.mkpath(path);
    }
    document.saveAs(path + "report.xlsx");
}

} // namespace mantis
