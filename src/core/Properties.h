/** @file
 * @brief     Mantis properties accumulation header
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

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
const auto WITH_TIMESTAMP = "timestamp";
const auto SEPARATED = "separated";

} // namespace device_groups

namespace device_id
{
const auto COMMUTATION_STATION = "commutation_station";
const auto SNMP = "snmp";
const auto LOUDSPEAKER = "loudspeaker";
const auto TITAN = "titan";
const auto ISB_ID = "isb";

} // namespace device_id

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

namespace date_format
{

const auto INPUT_DATE_FORMAT = QString{ "ddd MMM dd hh:mm:ss yyyy" };
const auto OUTPUT_DATE_FORMAT = QString{ "dd-MM-yyyy hh:mm:ss" };

using TimeStateTable
    = std::map<QString, std::map<QString, std::map<QString, int>>>;
using TitanTimeStateTalbe = std::map<QString, std::map<QString, int>>;

/**
 * Convert seconds to report time format
 */
QString secondsToTime(int value);

} // namespace date_format

} // namespace mantis
