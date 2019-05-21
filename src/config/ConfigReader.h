/** @file
 * @brief     Config Reader declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include <QString>
#include <QStringList>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

namespace mantis
{

struct ReportInfo
{
    QString id;
    QString title;
    QStringList deviceList;

    operator QString() const { return id + title + deviceList.join(" |"); }

};

namespace config
{

/**
 * Read config from JSON file to property tree
 */
boost::property_tree::ptree fromFile(const std::string& fileName);

} // config

QStringList readDeviceListFromFile(const std::string& fileName, const std::string& reportName);

std::vector<ReportInfo> readReportsConfiguration(const std::string& fileName);

} // mantis
