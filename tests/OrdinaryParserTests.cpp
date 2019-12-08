#include "../core/OrdinaryParserNew.h"

#include "ConfigReader.h"

#include <QDebug>

#include <gtest/gtest.h>

#include <memory>

using namespace mantis;

TEST(OrdinaryParserOrdinaryMessage, Positive)
{
    auto message = QString("[c] 'Mon Mar 25 16:48:46 2019' 'test' <2920,2916,1000,1000,1000> [s] Обновление состояния:(Устройство, № 1, ) = 0 CODE ( Исправно ) {user}");
    auto parserConfig = config::readParserConfiguration("test_parsers_configuration/ordinaryParser.json");
    auto ordinary = std::make_unique<mantis::OrdinaryParserNew>(parserConfig);

    auto parsedMessage = ordinary->parseMessage(message);
    qDebug() << parsedMessage;

    EXPECT_EQ(QString{"Устройство, № 1"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Исправно"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

TEST(OrdinaryParserEncodeState, Positive)
{
    auto message = QString("[c] 'Mon Mar 25 16:48:46 2019' 'test' <2920,2916,1000,1000,1000> [s] Обновление состояния:(Устройство 2, ) = 0 CODE ( 0001 ) {user}");
    auto parserConfig = config::readParserConfiguration("test_parsers_configuration/ordinaryParser.json");
    auto ordinary = std::make_unique<mantis::OrdinaryParserNew>(parserConfig);
    ordinary->config().encodeStates = true;

    auto parsedMessage = ordinary->parseMessage(message);
    qDebug() << parsedMessage;

    EXPECT_EQ(QString{"Устройство 2"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Состояние по умолчанию (ТЕСТ)"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

TEST(OrdinaryParserEncodeDevice, Positive)
{
    auto message = QString("[c] 'Mon Mar 25 16:48:46 2019' 'test' <2920,2916,1000,1000,1000> [s] Обновление состояния:(C01234, ) = 0 CODE ( Не отвечает ) {user}");
    auto parserConfig = config::readParserConfiguration("test_parsers_configuration/ordinaryParser.json");
    auto ordinary = std::make_unique<mantis::OrdinaryParserNew>(parserConfig);

    ordinary->config().encodeStates = false;
    ordinary->config().encodeDevice = true;

    auto parsedMessage = ordinary->parseMessage(message);
    qDebug() << parsedMessage;

    EXPECT_EQ(QString{"Коммутатор 24"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Не отвечает"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

TEST(OrdinaryParserEncodeAll, Positive)
{
    auto message = QString("[c] 'Mon Mar 25 16:48:46 2019' 'test' <2920,2916,1000,1000,1000> [s] Обновление состояния:(C0A2FFDD, ) = 0 CODE ( 30201020 ) {user}");
    auto parserConfig = config::readParserConfiguration("test_parsers_configuration/ordinaryParser.json");
    auto ordinary = std::make_unique<mantis::OrdinaryParserNew>(parserConfig);

    ordinary->config().encodeStates = true;
    ordinary->config().encodeDevice = true;

    auto parsedMessage = ordinary->parseMessage(message);
    qDebug() << parsedMessage;

    EXPECT_EQ(QString{"Видеокамера - 1 - 4"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Состояние по умолчанию (ТЕСТ)"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}

