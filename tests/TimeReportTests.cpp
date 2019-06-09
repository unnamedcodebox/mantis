//#include "../config/ConfigReader.h"

//#include "../core/Database.h"
//#include "../core/OrdinaryParser.h"
//#include "../core/SplitDatabaseMessage.h"
//#include "../core/TitanParser.h"
//#include "../core/IsbParser.h"

//#include <QDebug>
//#include <QFile>
//#include <gtest/gtest.h>

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

//#include <memory>

//TEST(TimeReportOrdinary, Positive)
//{
//    using namespace mantis;
//    auto table = mantis::Table{ { { "timeReported", "2019-03-30 08:25:38" },
//                                  { "msg",
//                                    "[c] 'Mon Mar 25 16:48:47 2019' 'ruberoid' "
//                                    "<2920,2916,1000,1000,1000> "
//                                    "[s] Обновление состояния:(СЦКУ, № 1, ) = "
//                                    "0 CODE ( Исправно ) {user}" } },
//                                { { "timeReported", "2019-03-30 08:25:38" },
//                                  { "msg",
//                                    "[c] 'Mon Mar 25 16:57:47 2019' 'ruberoid' "
//                                    "<2920,2916,1000,1000,1000> "
//                                    "[s] Обновление состояния:(СЦКУ, № 1, ) = "
//                                    "0 CODE ( Не отвечает ) {user}" } },
//                                { { "timeReported", "2019-03-30 08:25:38" },
//                                  { "msg",
//                                    "[c] 'Mon Mar 25 18:39:13 2019' 'ruberoid' "
//                                    "<2920,2916,1000,1000,1000> "
//                                    "[s] Обновление состояния:(СЦКУ, № 1, ) = "
//                                    "0 CODE ( Исправно ) {user}" } } };

//    auto parser = std::make_unique<mantis::OrdinaryParser>();
//    auto reportTable = parser->parseTable(table);
//    auto deviceList = readDeviceListFromFile("device_list.json", "state_tech");
//    //auto timeReport = createTimeReportTable(reportTable, deviceList);
//    qDebug() << timeReport;
//    EXPECT_EQ(3, reportTable.size());
//}

//TEST(createTitanTimeReportTableTest, Positive)
//{
//    using namespace mantis;
//    auto parser = std::make_unique<mantis::TitanParser>();
//    auto table = mantis::Table{
//         {{"msg" ,
//        "[c] 'Thu Mar 28 12:08:01 2019' 'agent199' <7848,7847,1000,1000,1000> "
//        "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 0 ) {user}"}},
//    {{"msg" ,
//            "[c] 'Fri Mar 29 06:33:15 2019' 'agent199' <7848,7847,1000,1000,1000> "
//            "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 2 ) {user}"}},
//    {{"msg" ,
//            "[c] 'Fri Mar 29 06:33:15 2019' 'agent199' <7848,7847,1000,1000,1000> "
//            "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 1 ) {user}"}},
//    {{"msg" ,
//            "[c] 'Fri Mar 29 12:33:15 2019' 'agent199' <7848,7847,1000,1000,1000> "
//            "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 2 ) {user}"}},
//    {{"msg" ,
//            "[c] 'Fri Mar 29 16:33:15 2019' 'agent199' <7848,7847,1000,1000,1000> "
//            "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 4 ) {user}"}},
//    {{"msg" ,
//            "[c] 'Fri Mar 29 19:33:47 2019' 'agent199' <7848,7847,1000,1000,1000> "
//            "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 1 ) {user}"}},
//    {{"msg" ,
//            "[c] 'Fri Mar 29 23:32:11 2019' 'agent199' <7848,7847,1000,1000,1000> "
//            "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 0 ) {user}"}}

//    };
//    auto reportTable = parser->parseTable(table);
//    auto timeReportTable = createTitanTimeReportTable(reportTable);
//    qDebug() << reportTable;
//    qDebug() << "timeReportTable" << timeReportTable;
//}

//TEST(createIsbTimeReportTable, Positive)
//{
//    using namespace mantis;
//    auto parser = std::make_unique<IsbParser>();
//    auto table = readTestTableFromFile("isbTests.json");
////    QString filename="isbTests.txt";
////       QFile file(filename);
////       if(!file.exists()){
////           qDebug() << "NO existe el archivo "<<filename;
////       }else{
////           qDebug() << filename<<" encontrado...";
////       }
////       QString line;

////       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
////           QTextStream stream(&file);
////           while (!stream.atEnd()){
////               line = stream.readLine();
////               table.push_back({{"msg", line}});
////           }
////       }
////       file.close();
//    auto reportTable = parser->parseTable(table);
//    auto timeReportTable = createIsbTimeReportTable(reportTable);
//    qDebug() << reportTable;
//    qDebug() << "timeReportTable" << timeReportTable;
//}
