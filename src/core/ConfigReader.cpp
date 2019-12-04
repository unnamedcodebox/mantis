/** @file
 * @brief     Config Reader functions implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ConfigReader.h"
#include <QVariantMap>
#include <QString>
#include <QStringList>

namespace mantis
{

namespace config
{

namespace
{

const auto COMPONENTS = "components";
const auto ID = "id";
const auto GROUP = "group";
const auto ORDINARY = "ordinary";
const auto TITLE = "title";
const auto DEVICE_LIST = "device_list";

const auto PARSER_CONFIG = "parserConfig";

} // anonymous

boost::property_tree::ptree fromFile(const std::string& fileName)
{
    boost::property_tree::ptree config;
    boost::property_tree::read_json(fileName, config);

    return config;
}

QVariantList readReportsConfiguration(const std::string& fileName)
{
    auto config = config::fromFile(fileName);
    auto deviceTree = config.get_child(COMPONENTS);
    auto components = QVariantList{};

    for (auto& deviceNode : deviceTree)
    {
        auto id
            = QString::fromStdString(deviceNode.second.get<std::string>(ID));
        auto title
            = QString::fromStdString(deviceNode.second.get<std::string>(TITLE));
        auto group
            = QString::fromStdString(deviceNode.second.get<std::string>(GROUP));
        auto deviceList = QStringList{};
        boost::optional<boost::property_tree::ptree&> listExists
            = deviceNode.second.get_child_optional(DEVICE_LIST);

        auto parserConfig = deviceNode.second.get_optional<std::string>(PARSER_CONFIG);

        if (group == ORDINARY)
        {
            for (const auto& it : *listExists)
            {
                deviceList.push_back(
                    QString::fromStdString(it.second.get_value<std::string>()));
            }
            components.push_back(QVariantMap{ { ID, id },
                                              { GROUP, group },
                                              { TITLE, title },
                                              { DEVICE_LIST, deviceList }
                                 });
        }
        else
        {
            components.push_back(QVariantMap{
                { ID, id },
                { GROUP, group },
                { TITLE, title },
            });
        }
    }
    return components;
}

} // namespace config

// config

} // namespace mantis
