/** @file
 * @brief     Config Reader implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ConfigReader.h"
#include <QVariantMap>
#include <QDebug>
namespace mantis {

QStringList readDeviceListFromFile(
    const std::string& fileName, const std::string& reportName)
{
    return {};
}
namespace config
{
boost::property_tree::ptree fromFile(const std::string &fileName)
{
    boost::property_tree::ptree config;
    boost::property_tree::read_json(fileName, config);

    return config;
}
}

QVariantList readReportsConfiguration(const std::string &fileName)
{
    const auto COMPONENTS = "components";
    const auto ID = "id";
    const auto TITLE = "title";
    const auto DEVICE_LIST = "device_list";

    auto config = config::fromFile(fileName);
    auto deviceTree = config.get_child(COMPONENTS);
    auto components = QVariantList{};

    for (auto& deviceNode: deviceTree)
    {
        auto id
            = QString::fromStdString(deviceNode.second.get<std::string>(ID));
        auto title
            = QString::fromStdString(deviceNode.second.get<std::string>(TITLE));
        auto deviceList = QStringList{};

        boost::optional<boost::property_tree::ptree&> listExists
            = deviceNode.second.get_child_optional(DEVICE_LIST);
        if(listExists)
        {
            for (const auto& it: *listExists)
            {
                deviceList.push_back(
                    QString::fromStdString(it.second.get_value<std::string>()));
            }
        }
        components.push_back(QVariantMap{{ID, id},{TITLE, title},{DEVICE_LIST, deviceList}});
    }

qDebug() << components;
    return components;
}

// config

} // mantis
