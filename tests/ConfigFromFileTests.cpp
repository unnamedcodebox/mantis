#include <QDebug>
#include <QString>
#include <QtXlsx>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <stdlib.h>

#include <gtest/gtest.h>

QStringList readDeviceListFromFile(const std::string& fileName, const std::string& reportName)
{
    boost::property_tree::ptree config;
    boost::property_tree::read_json(fileName, config);
    auto deviceTree = config.get_child(reportName);
    auto deviceList = QStringList{};
    for (auto& it: deviceTree)
    {
        deviceList.push_back(
            QString::fromStdString(it.second.get_value<std::string>()));
    }

    return deviceList;
}

TEST(readDeviceListFromConfigFile, Positive)
{
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

    qDebug() << ruberoid;
    qDebug() << snmp;
    qDebug() << loudspeaker;
}
