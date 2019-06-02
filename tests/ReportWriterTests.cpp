#include "../core/Properties.h"

#include "../core/ReportWriter.h"
#include "../core/IsbReport.h"

#include <gtest/gtest.h>

#include <memory>

TEST(ReportWriterCommutationStationSimpleReportTest, Positive)
{
    using namespace mantis;
    auto report = std::make_shared<IsbReport>(
        device_id::COMMUTATION_STATION,
        "Формирование обобщенных справок по состоянию ИСБ 'МНС-контроль'",
        "timeReport",
        "01/03/2019",
        "03/04/2019");
    auto reportTable = ReportTable{ { "device 1", "Ok", "25-03-2018" },
                                    { "device 2", "Ok", "26-03-2018" },
                                    { "device 3", "Ok", "26-03-2018" } };
    report->setReportTable(reportTable);
    auto writer = std::make_shared<ReportWriter>(report);
    writer->writeReportToFile();
}

TEST(ReportWriterCommutationStationTimeReportTest, Positive)
{
    using namespace mantis;
    auto report = std::make_shared<IsbReport>(
        device_id::COMMUTATION_STATION,
        "Формирование обобщенных справок по состоянию ИСБ 'МНС-контроль'",
        "timeReport",
        "01/03/2019",
        "03/04/2019");
    auto reportTable = ReportTable{ { "device 1", "Ok", "25-03-2018" },
                                    { "device 2", "Ok", "26-03-2018" },
                                    { "device 3", "Ok", "26-03-2018" } };
    report->setReportTable(reportTable);
    auto writer = std::make_shared<ReportWriter>(report);
    writer->writeReportToFile();
}
