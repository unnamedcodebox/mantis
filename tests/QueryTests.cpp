//#include "../core/IsbQuery.h"
//#include "../core/QueryOrdinary.h"
//#include "../core/TitanQuery.h"

//#include <gtest/gtest.h>

//#include <QString>

//#include <memory>
//#include <string>

//TEST(InitQueryOrdinary, Positive)
//{
//    using namespace mantis;

//    auto query = std::make_unique<QueryOrdinary>(
//        AppName::ICS,
//        QStringList{ "device1", "device2", "device3" },
//        "01/06/2019",
//        "01/07/2019");
//    auto excepted = QString{ "SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE "
//                    "\"appName\"='ics' AND \"timeReported\">='01/06/2019' AND "
//                    "\"timeReported\"<='01/07/2019' AND \"msg\" LIKE "
//                    "'%Обновление состояния%' AND \"msg\" SIMILAR to "
//                    "'%(device1|device2|device3)%' ORDER BY \"timeReported\";"};
//    EXPECT_EQ(excepted.toStdString(), query->get().toStdString());
//}

//TEST(InitTitanQuery, Positive)
//{
//    using namespace mantis;

//    auto query = std::make_unique<
//        TitanQuery>(AppName::ICS, "01/06/2019", "01/07/2019");
//    auto excepted
//        = QString{ "SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE "
//                   "\"appName\"='ics' AND \"timeReported\">='01/06/2019' AND "
//                   "\"timeReported\"<='01/07/2019' AND \"msg\" LIKE "
//                   "'%failure(agent199, )%' ORDER BY \"timeReported\";" };
//    EXPECT_EQ(excepted.toStdString(), query->get().toStdString());
//}

//TEST(InitIsbQuery, Positive)
//{
//    using namespace mantis;

//    auto query = std::make_unique<
//        IsbQuery>(AppName::PCS, "01/06/2019", "01/07/2019");
//    auto excepted
//        = QString{ "SELECT \"msg\", \"timeReported\" FROM \"Event\" WHERE "
//                   "\"appName\"='PCS' AND \"timeReported\">='01/06/2019' AND "
//                   "\"timeReported\"<='01/07/2019' ORDER BY \"timeReported\";" };
//    EXPECT_EQ(excepted.toStdString(), query->get().toStdString());
//}
