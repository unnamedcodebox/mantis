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

    QXlsx::Document xlsx;
    auto counter = 1;
    for(auto& it : ruberoid)
    {
        xlsx.write("A" + QString::number(counter), it);
        ++counter;
    }

    auto path = QString{"/home/" + QString::fromStdString(std::string(getenv("USER"))) + "/Documents/Reports/"};
    QDir dir(path);
    if (!dir.exists()){
      dir.mkpath(path);
    }
    xlsx.saveAs(path + "Test.xlsx");

    EXPECT_EQ(1, loudspeaker.size());
    EXPECT_EQ("1", std::string{getenv("USER")});
    EXPECT_EQ(1, loudspeaker.size());

//    qDebug() << ruberoid;
//    qDebug() << snmp;
//    qDebug() << loudspeaker;
}
