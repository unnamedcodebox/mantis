/** @file
 * @brief     Config Reader functions declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include <QVariantList>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Configuration.h"

namespace mantis
{

namespace config
{

/**
 * Read config from JSON file to property tree
 */
boost::property_tree::ptree fromFile(const std::string& fileName);

/**
 * Read components configuration from file
 */
QVariantList readReportsConfiguration(const std::string& fileName);

template <typename Field, typename PropertyTree, typename Key>
void readField(Field& field, PropertyTree& tree, const Key& key)
{
    auto value
        = tree.get().template get_optional<std::remove_reference_t<decltype(*field)> >(
                  key);
    if (value)
    {
        field = *value;
    }
}

template <typename Field, typename PropertyTree, typename Key>
void readMappedField(Field& field, PropertyTree& tree, const Key& key)
{
    auto mapped = tree.get().get_child_optional(key);

    if (mapped)
    {
        auto record = std::map<std::string, std::string>{};

        for (auto& element : *mapped)
        {
            record[element.first] = element.second.data();
        }
        field = record;
    }
}

/**
 * @brief readParserConfiguration - Returns parser configuration from json
 * @param directory
 * @return
 */

ParserConfiguration readParserConfiguration(const std::string& directory);

/**
 * @brief readParserConfiguration - Returns parser configuration from json
 * @param directory
 * @return
 */

DocumentConfiguration readDocumentConfiguration(const std::string& directory, const std::string &subtype);


QueryConfiguration readQueryConfiguration(const std::string& directory);

} // config

} // mantis
