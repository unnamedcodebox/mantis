/** @file
 * @brief     Config Reader implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ConfigReader.h"
#include <QDebug>
namespace mantis {

QStringList readDeviceListFromFile(
    const std::string& fileName, const std::string& reportName)
{
    auto config = config::fromFile(fileName);
    auto deviceTree = config.get_child("commutation_station.device_list");
//    auto deviceTree = settings.get_child("device_list");
    auto deviceList = QStringList{};
    for (auto& it: deviceTree)
    {
        deviceList.push_back(
            QString::fromStdString(it.second.get_value<std::string>()));
    }
qDebug() << deviceList;
    return deviceList;
}
namespace config
{
boost::property_tree::ptree fromFile(const std::string &fileName)
{
    boost::property_tree::ptree config;
    boost::property_tree::read_json(fileName, config);

    return config;
}
} // config

} // mantis
