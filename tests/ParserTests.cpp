#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/SplitDatabaseMessage.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"

#include "../core/TimeReport.h"

#include <QDebug>

#include <gtest/gtest.h>

#include <memory>

using namespace mantis;

TEST(getAppNameTestPositive, Positive)
{
    EXPECT_EQ("ics", getAppName(AppName::ICS).toStdString());
    EXPECT_EQ("PCS", getAppName(AppName::PCS).toStdString());
}

TEST(ParseOrdinaryMessage, Positive)
{
    auto message = QString(
        "[c] 'Mon Mar 25 16:48:47 2019' 'ruberoid' <2920,2916,1000,1000,1000> "
        "[s] Обновление состояния:(СЦКУ, № 1, ) = 0 CODE ( Исправно ) {user}");
    auto ordinary = std::make_unique<mantis::OrdinaryParser>();
    auto parts = splitDatabaseMessage(message);
    auto parsedMessage = ordinary->parseMessage(parts);
    qDebug() << parsedMessage;
    EXPECT_EQ(12, parts.size());
    EXPECT_EQ(QString{"СЦКУ № 1"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Исправно"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

TEST(ParseTitanMessage, Positive)
{
    auto message = QString(
        "[c] 'Sat Mar 30 08:25:38 2019' 'agent199' <7741,7740,1000,1000,1000> "
        "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 2 ) {user}");
    auto titan = std::make_unique<mantis::TitanParser>();
    auto parts = splitDatabaseMessage(message);
    auto parsedMessage = titan->parseMessage(parts);
    qDebug() << parsedMessage;
    EXPECT_EQ(12, parts.size());
    EXPECT_EQ(QString{"CДВ РПДУ Титан-М"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Авария накала"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

TEST(ParseTitanMessageOk, Positive)
{
    auto message = QString(
        "[c] 'Sat Mar 30 08:25:38 2019' 'agent199' <7741,7740,1000,1000,1000> "
        "[s] failure(agent199, ) = 0 CODE ( РПДУ Титан, № 1 - 0 ) {user}");
    auto titan = std::make_unique<mantis::TitanParser>();
    auto parts = splitDatabaseMessage(message);
    auto parsedMessage = titan->parseMessage(parts);
    EXPECT_EQ(12, parts.size());
    EXPECT_EQ(QString{"CДВ РПДУ Титан-М"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Исправно"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

TEST(ParseIsbMessage, Positive)
{
    auto isbParser = std::make_shared<mantis::IsbParser>();
    auto message = QString("UPR:PCS:1:1:0x7F:Не отвечает");
    auto parts = splitDatabaseMessage(message, AppName::PCS);
    auto parsedMessage = isbParser->parseMessage(parts);

    EXPECT_EQ(6, parts.size());
    EXPECT_EQ(QString{"Здание управления"}.toStdString(), parsedMessage[QString{"placement"}].toStdString());
    EXPECT_EQ(QString{"Прибор контроля состояния (ПКС)"}.toStdString(), parsedMessage[QString{"type"}].toStdString());
    EXPECT_EQ(QString{"1"}.toStdString(), parsedMessage[QString{"throughId"}].toStdString());
    EXPECT_EQ(QString{"1"}.toStdString(), parsedMessage[QString{"uniqueId"}].toStdString());
    EXPECT_EQ(QString{"Не отвечает"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
    EXPECT_EQ(QString{"---"}.toStdString(), parsedMessage[QString{"batteryState"}].toStdString());
}

TEST(ParseIsbMessageTZ, Positive)
{
    auto isbParser2 = std::make_shared<mantis::IsbParser>();
    auto message = QString{"TZ3:PCS:1:5:0x20"};
    auto parts = splitDatabaseMessage(message, AppName::PCS);
    auto parsedMessage = isbParser2->parseMessage(parts);

    EXPECT_EQ(5, parts.size());
    EXPECT_EQ(QString{"Техническое здание 3"}.toStdString(), parsedMessage[QString{"placement"}].toStdString());
    EXPECT_EQ(QString{"Прибор контроля состояния (ПКС)"}.toStdString(), parsedMessage[QString{"type"}].toStdString());
    EXPECT_EQ(QString{"1"}.toStdString(), parsedMessage[QString{"throughId"}].toStdString());
    EXPECT_EQ(QString{"5"}.toStdString(), parsedMessage[QString{"uniqueId"}].toStdString());
    EXPECT_EQ(QString{"Исправно"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
    EXPECT_EQ(QString{"---"}.toStdString(), parsedMessage[QString{"batteryState"}].toStdString());
}


TEST(ParseIsbMessageSimple, Positive)
{
    auto isbParser3 = std::make_shared<mantis::IsbParser>();
    auto message = QString{"KPP:SW:1:5:0x20"};
    auto parts = splitDatabaseMessage(message, AppName::PCS);
    auto parsedMessage = isbParser3->parseMessage(parts);

    EXPECT_EQ(5, parts.size());
    EXPECT_EQ(QString{"Контрольно-пропускной пункт"}.toStdString(), parsedMessage[QString{"placement"}].toStdString());
    EXPECT_EQ(QString{"Коммутатор"}.toStdString(), parsedMessage[QString{"type"}].toStdString());
    EXPECT_EQ(QString{"1"}.toStdString(), parsedMessage[QString{"throughId"}].toStdString());
    EXPECT_EQ(
        QString{ "5" }.toStdString(),
        parsedMessage[QString{ "uniqueId" }].toStdString());
    EXPECT_EQ(
        QString{ "Исправно" }.toStdString(),
        parsedMessage[QString{ "state" }].toStdString());
    EXPECT_EQ(
        QString{ "---" }.toStdString(),
        parsedMessage[QString{ "batteryState" }].toStdString());
}

TEST(ParseTitanTable, Positive)
{
    auto table = mantis::Table{ { { "timeReported", "2019-03-30 08:25:38" },
                                  { "msg",
                                    "[c] 'Mar 30 08:25:38 2019' 'agent199' "
                                    "<7741,7740,1000,1000,1000> "
                                    "[s] failure(agent199, ) = 0 CODE ( РПДУ "
                                    "Титан, № 1 - 0 ) {user}" } },
                                { { "timeReported", "2019-03-30 12:18:17" },
                                  { "msg",
                                    "[c] 'Mar 30 08:25:38 2019' 'agent199' "
                                    "<7741,7740,1000,1000,1000> "
                                    "[s] failure(agent199, ) = 0 CODE ( РПДУ "
                                    "Титан, № 1 - 2 ) {user}" } },
                                { { "timeReported", "2019-03-31 13:54:19" },
                                  { "msg",
                                    "[c] 'Mar 31 08:25:38 2019' 'agent199' "
                                    "<7741,7740,1000,1000,1000> "
                                    "[s] failure(agent199, ) = 0 CODE ( РПДУ "
                                    "Титан, № 1 - 0 ) {user}" } },
                                { { "timeReported", "2019-04-01 21:25:38" },
                                  { "msg",
                                    "[c] 'Apr 01 08:25:38 2019' 'agent199' "
                                    "<7741,7740,1000,1000,1000> "
                                    "[s] failure(agent199, ) = 0 CODE ( РПДУ "
                                    "Титан, № 1 - 3 ) {user}" } },
                                { { "timeReported", "2019-02-04 16:29:54" },
                                  { "msg",
                                    "[c] 'Apr 04 08:25:38 2019' 'agent199' "
                                    "<7741,7740,1000,1000,1000> "
                                    "[s] failure(agent199, ) = 0 CODE ( РПДУ "
                                    "Титан, № 1 - 5 ) {user}" } } };

    auto parser = std::make_unique<mantis::TitanParser>();
    auto reportTable = parser->parseTable(table);

    EXPECT_EQ(5, reportTable.size());
}
