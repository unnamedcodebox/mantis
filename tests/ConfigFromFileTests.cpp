#include "../config/ConfigReader.h"

#include <QDebug>

#include <QtXlsx>

#include <string>
#include <stdlib.h>

#include <gtest/gtest.h>

TEST(readDeviceListFromConfigFile, Positive)
{
    using namespace mantis;
    auto ruberoid = readDeviceListFromFile("device_list.json", "state_tech");
    auto snmp = readDeviceListFromFile("device_list.json", "state_snmp");
    auto loudspeaker
        = readDeviceListFromFile("device_list.json", "state_loudspeaker");

    EXPECT_EQ(1, loudspeaker.size());
    EXPECT_EQ("1", std::string{getenv("USER")});
    EXPECT_EQ(1, loudspeaker.size());

}

TEST(readReportsConfiguration, Positive)
{
    auto configuration = mantis::readReportsConfiguration("device_list.json");
}
