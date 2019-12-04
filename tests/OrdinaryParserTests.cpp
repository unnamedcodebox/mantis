#include "../core/OrdinaryParser.h"

#include <QDebug>

#include <gtest/gtest.h>

#include <memory>

using namespace mantis;

TEST(ParseOrdinaryMessageWithRegExp, Positive)
{
    auto message = QString("[c] 'Mon Mar 25 16:48:46 2019' 'ruberoid' <2920,2916,1000,1000,1000> [s] Обновление состояния:(СЦКУ, № 1, ) = 0 CODE ( Не отвечает ) {user}");
    auto ordinary = std::make_unique<mantis::OrdinaryParser>();

    auto parsedMessage = ordinary->parseMessage(message);
    qDebug() << parsedMessage;

    EXPECT_EQ(QString{"СЦКУ, № 1"}.toStdString(), parsedMessage[QString{"name"}].toStdString());
    EXPECT_EQ(QString{"Не отвечает"}.toStdString(), parsedMessage[QString{"state"}].toStdString());
}
