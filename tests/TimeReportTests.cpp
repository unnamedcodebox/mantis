#include "../config/ConfigReader.h"

#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/SplitDatabaseMessage.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"

#include "../core/TimeReport.h"

#include <QDebug>

#include <gtest/gtest.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <memory>

TEST(TimeReportOrdinary, Positive)
{
    using namespace mantis;
    auto table = mantis::Table{ { { "timeReported", "2019-03-30 08:25:38" },
                                  { "msg",
                                    "[c] 'Mon Mar 25 16:48:47 2019' 'ruberoid' "
                                    "<2920,2916,1000,1000,1000> "
                                    "[s] Обновление состояния:(СЦКУ, № 1, ) = "
                                    "0 CODE ( Исправно ) {user}" } },
                                { { "timeReported", "2019-03-30 08:25:38" },
                                  { "msg",
                                    "[c] 'Mon Mar 25 16:57:47 2019' 'ruberoid' "
                                    "<2920,2916,1000,1000,1000> "
                                    "[s] Обновление состояния:(СЦКУ, № 1, ) = "
                                    "0 CODE ( Не отвечает ) {user}" } },
                                { { "timeReported", "2019-03-30 08:25:38" },
                                  { "msg",
                                    "[c] 'Mon Mar 25 18:39:13 2019' 'ruberoid' "
                                    "<2920,2916,1000,1000,1000> "
                                    "[s] Обновление состояния:(СЦКУ, № 1, ) = "
                                    "0 CODE ( Исправно ) {user}" } } };

    auto parser = std::make_unique<mantis::OrdinaryParser>();
    auto reportTable = parser->parseTable(table);
    auto deviceList = readDeviceListFromFile("device_list.json", "state_tech");
    auto timeReport = createTimeReport(reportTable, deviceList);
    qDebug() << timeReport;
    EXPECT_EQ(3, reportTable.size());
}
