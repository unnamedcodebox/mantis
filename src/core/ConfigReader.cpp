/** @file
 * @brief     Config Reader functions implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "ConfigReader.h"
#include "DocumentProperties.h"
#include <QVariantMap>
#include <QString>
#include <QStringList>

#include <iostream>

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
const auto REPORT_CONFIG = "reportConfig";

const auto PARSER_CONFIG = "parserConfig";

// namespace configuration_fields
//{

const auto MAIN = "main.json";
const auto PARSER = "parser.json";
const auto DOCUMENT = "document.json";
const auto QUERY = "query.json";
const auto DEVICES_DOC = "devices.json";
const auto STATES_DOC = "states.json";

// namespace parser_fields
//{

constexpr auto STATE_MESSAGE = "stateMessage";
constexpr auto REG_EXP = "regExp";
constexpr auto DEVICE_MATCH = "deviceMatch";
constexpr auto STATE_MATCH = "stateMatch";
constexpr auto DEVICES = "devices";
constexpr auto STATES = "states";

//} // namespace parser_fields

namespace query
{

constexpr auto FIELDS = "fields";
constexpr auto GROUP = "group";
constexpr auto TABLE_NAME = "tableName";
constexpr auto STATEMENT = "statement";
constexpr auto MODIFICATORS_IN_STATEMENT = "modificatorsInStatement";
constexpr auto USE_RAW_STRING = "useRawString";
const auto RAW_STRING = "rawString";

constexpr auto TIMESTAMP = "timestamp";
const auto MESSAGE = "message";

} // namespace query_fields

//} // namespace configuration_fields

} // namespace

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
                                              { DEVICE_LIST, deviceList } });
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

ParserConfiguration readParserConfiguration(const std::string& directory)
{

    auto config = config::fromFile(directory);

    auto parserConfig = ParserConfiguration();

    auto stateMessage = config.get_child_optional(STATE_MESSAGE);

    if (stateMessage)
    {
        readField(parserConfig.regExp, stateMessage, REG_EXP);
        parserConfig.encodeDevice
            = stateMessage.get().get<bool>("encodeDevice");
        parserConfig.encodeStates
            = stateMessage.get().get<bool>("encodeStates");
        readField(parserConfig.deviceMatch, stateMessage, DEVICE_MATCH);
        readField(parserConfig.stateMatch, stateMessage, STATE_MATCH);
        readField(parserConfig.defaultState, stateMessage, "defaultState");
        readField(parserConfig.defaultDevice, stateMessage, "defaultDevice");

        readMappedField(parserConfig.devices, stateMessage, DEVICES);
        readMappedField(parserConfig.states, stateMessage, STATES);
    }

    auto timeMessage = config.get_child_optional("timeMessage");
    if (timeMessage)
    {
        readField(parserConfig.dateRegExp, timeMessage, "regExp");
        readField(parserConfig.timeMatch, timeMessage, "timeMatch");
        readField(parserConfig.inputDateFormat, timeMessage, "input");
        readField(parserConfig.outputDateFormat, timeMessage, "output");
    }

    return parserConfig;
}

DocumentConfiguration readDocumentConfiguration(
    const std::string& directory, const std::string& subtype)
{
    auto config = config::fromFile(directory);
    auto document = DocumentConfiguration();

    document.subtype = subtype;

    auto subtypeConfig = config.get_child_optional(subtype);

    document.useDefaults = config.get<bool>(doc::USE_DEFAULTS);

    if (subtypeConfig)
    {
        readField(document.title, subtypeConfig, doc::TITLE);
        readField(document.titleCell, subtypeConfig, doc::TITLE_CELL);
        readField(document.infoCell, subtypeConfig, doc::INFO_CELL);
        readField(document.titleRange, subtypeConfig, doc::TITLE_RANGE);
        readField(document.infoRange, subtypeConfig, doc::INFO_RANGE);

        boost::optional<boost::property_tree::ptree&> headers
            = subtypeConfig->get_child_optional(doc::HEADERS);

        if (headers)
        {
            document.headers = QStringList{};
            for (const auto& it : *headers)
            {
                document.headers->push_back(
                    QString::fromStdString(it.second.get_value<std::string>()));
            }
        }

        readField(document.headersRow, subtypeConfig, doc::HEADERS_ROW);

        readField(
            document.reportTableStartPosition,
            subtypeConfig,
            doc::REPORT_TABLE_START_POSITION);
        readField(document.infoString, subtypeConfig, doc::INFO_STRING);
    }

    return document;
}

QueryConfiguration readQueryConfiguration(const std::string& directory)
{

    using namespace query;
    auto tree = config::fromFile(directory);
    auto config = boost::make_optional(tree);

    auto queryConfig = QueryConfiguration();

    queryConfig.useRawString = config.get().get<bool>(USE_RAW_STRING);
    queryConfig.modificatorsInStatement = config.get().get<bool>(MODIFICATORS_IN_STATEMENT);

    readMappedField(queryConfig.fields, config, FIELDS);
    readField(queryConfig.group, config, query::GROUP);
    readField(queryConfig.tableName, config, TABLE_NAME);
    readField(queryConfig.whereStatement, config, STATEMENT);
    readField(queryConfig.rawString, config, RAW_STRING);

    return queryConfig;
}

} // namespace config

// config

} // namespace mantis
