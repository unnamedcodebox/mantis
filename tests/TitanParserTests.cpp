//#include "../core/TitanParser.h"

//#include <QDebug>

//#include <gtest/gtest.h>

//#include <memory>

//using namespace mantis;

//namespace
//{

//constexpr auto STATE = "state";

//}

//TEST(ParseTitanParserWithRegExp, Positive)
//{
//    auto parser = std::make_unique<mantis::TitanParser>();

//    auto message
//        = QString("[c] 'Mon Mar 25 12:16:16 2019' 'agent199' "
//                  "<2924,2921,1000,1000,1000> [s] Обновление состояния:(РПДУ "
//                  "Титан, № 1, ) = 0 CODE ( Не отвечает ) {user}");
//    auto parsedMessage = parser->parseMessage(message);

//    qDebug() << parsedMessage;

//    EXPECT_EQ(
//        QString{ "Неизвестно" }.toStdString(),
//        parsedMessage[QString{ STATE }].toStdString());

//    auto okMessage = QString(
//        "[c] 'Mon Mar 25 12:16:16 2019' 'agent199' <2924,2921,1000,1000,1000> "
//        "[s] Обновление состояния:(РПДУ Титан, № 1, ) = 0 CODE ( 0 ) {user}");
//    auto parsedOkMessage = parser->parseMessage(okMessage);

//    qDebug() << parsedOkMessage;

//    EXPECT_EQ(
//        QString{ "Исправно" }.toStdString(),
//        parsedOkMessage[QString{ STATE }].toStdString());

//    auto emergencyCoolingMessage = QString(
//        "[c] 'Mon Mar 25 12:16:16 2019' 'agent199' <2924,2921,1000,1000,1000> "
//        "[s] Обновление состояния:(РПДУ Титан, № 1, ) = 0 CODE ( 1 ) {user}");
//    auto coolingParsedMessage = parser->parseMessage(emergencyCoolingMessage);

//    qDebug() << coolingParsedMessage;

//    EXPECT_EQ(
//        QString{ "Авария - Охлаждение" }.toStdString(),
//        coolingParsedMessage[QString{ STATE }].toStdString());
//}
