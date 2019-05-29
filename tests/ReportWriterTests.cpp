#include "../core/ReportWriter.h"
#include "../core/IsbReport.h"

#include <gtest/gtest.h>

#include <memory>

TEST(ReportWriterTest, Positive)
{
    using namespace mantis;
    auto writer = std::make_shared<ReportWriter>(Headers::ISB);
    auto report = std::make_shared<
        IsbReport>("TEST TITLE", "timeReport", "01/03/2019", "03/04/2019");
    writer->writeReportToFile(report);
}

