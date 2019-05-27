/** @file
 * @brief     Mantis properties accumulation header
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "AppName.h"

#include <QString>
#include <QVariantMap>

namespace mantis
{

namespace database_properties
{

const auto DRIVER = "driver";
const auto HOST_ADDRESS = "hostaddr";
const auto DB_NAME = "dbname";
const auto USERNAME = "username";
const auto PASSWORD = "password";

const auto TIME_REPORTED = "timeReported";
const auto MESSAGE = "msg";

} // namespace database_properties

namespace device_groups
{

const auto ORDINARY = "ordinary";
const auto TITAN = "titan";
const auto ISB = "isb";

} // namespace device_groups

namespace report_subtypes
{

const auto SIMPLE_REPORT = "simpleReport";
const auto TIME_REPORT = "timeReport";

} // namespace report_subtypes

namespace report_properties
{

const auto ID = "id";
const auto GROUP = "group";
const auto TITLE = "title";
const auto BEGIN_DATE = "begin_date";
const auto END_DATE = "end_date";
const auto SUB_TYPE = "sub_type";
const auto DEVICE_LIST = "device_list";

QString getReportProperty(QVariantMap reportInfo, QString property);

QStringList getDeviceList(QVariantMap reportInfo);

} // namespace report_properties

} // namespace mantis
