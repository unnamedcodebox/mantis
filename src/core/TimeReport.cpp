/** @file
 * @brief     Time Report implentation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "TimeReport.h"

#include <QString>
#include <QDateTime>
#include <QDebug>

namespace mantis
{

const auto INPUT_DATE_FORMAT = QString{"ddd MMM dd hh:mm:ss yyyy"};
const auto OUTPUT_DATE_FORMAT = QString{"dd-MM-yyyy hh:mm:ss"};

ReportTable createTimeReport(ReportTable &table)
{
    auto reportTable = ReportTable{};
    if(!table.empty())
    {
        for(const auto& row : table)
        {
            auto date = QDateTime::fromString(row[2], INPUT_DATE_FORMAT);
            reportTable.push_back({date.toString(OUTPUT_DATE_FORMAT)});
        }
    }

    qDebug() << reportTable;
    return reportTable;
}

} // namespace mantis
