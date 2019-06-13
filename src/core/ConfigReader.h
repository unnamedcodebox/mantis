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

} // config

} // mantis
