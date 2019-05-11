#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/SplitDatabaseMessage.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"

#include "../core/TimeReport.h"

#include <QDebug>

#include <gtest/gtest.h>

#include <memory>

TEST(TimeReportOrdinary, Positive)
{
    using namespace mantis;
    auto table = mantis::Table{ { { "timeReported", "2019-03-30 08:25:38" },
                                  { "msg",
            "[c] 'Mon Mar 25 16:48:47 2019' 'ruberoid' <2920,2916,1000,1000,1000> "
            "[s] Обновление состояния:(СЦКУ, № 1, ) = 0 CODE ( Исправно ) {user}" } }};

    auto parser = std::make_unique<mantis::OrdinaryParser>();
    auto reportTable = parser->parseTable(table);
    auto timeReport = createTimeReport(reportTable);

    EXPECT_EQ(1, reportTable.size());
}
