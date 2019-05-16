/** @file
 * @brief     Config Reader implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ConfigReader.h"

namespace mantis {

QStringList readDeviceListFromFile(
    const std::string& fileName, const std::string& reportName)
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
