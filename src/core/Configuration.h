/** @file
 * @brief     Configuration declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Database.h"
#include "Parser.h"

#include <QString>
#include <QStringList>

#include <map>
#include <vector>

#include<boost/optional.hpp>


namespace mantis
{

/**
 * @brief The ParserConfiguration struct describes parser model
 */
struct ParserConfiguration
{
    boost::optional<std::string> regExp;

    bool encodeDevice;
    bool encodeStates;

    boost::optional<int> deviceMatch;
    boost::optional<int> stateMatch;

    boost::optional<std::map<std::string, std::string>> devices;
    boost::optional<std::map<std::string, std::string>> states;

    boost::optional<std::string> defaultDevice;
    boost::optional<std::string> defaultState;

    boost::optional<std::string> dateRegExp;
    boost::optional<int> timeMatch;
    boost::optional<std::string> inputDateFormat;
    boost::optional<std::string> outputDateFormat;

    ParserConfiguration() = default;
};


/**
 * @brief The DocumentConfiguration struct describes document model
 */
struct DocumentConfiguration
{
    bool useDefaults;

    boost::optional<std::string> subtype;

    boost::optional<std::string> title;
    boost::optional<std::string> titleCell;
    boost::optional<std::string> infoCell;
    boost::optional<std::string> titleRange;
    boost::optional<std::string> infoRange;
    boost::optional<QStringList> headers;

    boost::optional<int> headersRow;
    boost::optional<int> reportTableStartPosition;

    boost::optional<std::string> infoString;
};

struct QueryConfiguration
{
    bool useRawString;
    bool modificatorsInStatement;

    boost::optional<std::string> group;
    boost::optional<std::map<std::string, std::string>> fields;

    boost::optional<std::string> tableName;
    boost::optional<std::string> whereStatement;

    boost::optional<std::string> rawString;
};

/**
 * @brief The Congfiguration struct describes report model
 */
struct Configuration
{
    QString group;

    boost::optional<ParserConfiguration> parser;
    boost::optional<DocumentConfiguration> document;
    boost::optional<QueryConfiguration> query;

};

} // namespace mantis
