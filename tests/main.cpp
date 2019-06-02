//#include "../src/core/Database.h"
//#include "../src/core/OrdinaryParser.h"
//#include "../src/core/TitanParser.h"
//#include "../src/core/IsbParser.h"

#include <QGuiApplication>
#include <QTranslator>

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
