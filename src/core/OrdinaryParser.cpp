/** @file
 * @brief     Ordinary devices parser declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "OrdinaryParser.h"
#include <regex>
#include <map>
#include <vector>
#include <QString>
#include <QDateTime>
#include <iostream>

namespace mantis
{

namespace
{

const auto NAME = "name";
const auto STATE = "state";
const auto TIME = "time";

auto parseDate(
    const QString& date,
    const QString& inputDateFormat,
    const QString& outputDateFormat)
{
    auto dateTime = QDateTime::fromString(date, inputDateFormat);
    return dateTime.toString(outputDateFormat);
}

} // namespace

auto parseOrdinaryMessage(
    const ParserConfiguration& config, const QString& message)
{
    std::smatch match;
    auto messageStd = message.toStdString();
    auto found
        = std::regex_search(messageStd, match, std::regex(*config.regExp));

    auto name = std::string();
    auto state = std::string();

    if (found)
    {
        name = match[static_cast<size_t>(*config.deviceMatch)].str();
        state = match[static_cast<size_t>(*config.stateMatch)].str();
    }

    std::smatch dateMatch;

    auto foundDate = std::
        regex_search(messageStd, dateMatch, std::regex(*config.dateRegExp));

    auto time = parseDate(
        QString::fromStdString(dateMatch[1].str()),
        QString::fromStdString(*config.inputDateFormat),
        QString::fromStdString(*config.outputDateFormat));

    auto data
        = std::map<QString, QString>{ { NAME, QString::fromStdString(name) },
                                      { STATE, QString::fromStdString(state) },
                                      { TIME, time } };
    std::cout << "DATE MATCH" << dateMatch[1].str();
    return data;
}

auto encodeStateMessage(
    const ParserConfiguration& config, const QString& message)
{
    auto messageStd = message.toStdString();

    std::smatch match;
    auto found
        = std::regex_search(messageStd, match, std::regex(*config.regExp));

    auto name = std::string();
    auto state = std::string();

    if (found)
    {
        name = match[static_cast<size_t>(*config.deviceMatch)].str();
        state = match[static_cast<size_t>(*config.stateMatch)].str();
    }

    auto states = config.states.get();
    auto find = states.find(state);
    if (find != states.end())
    {
        state = find->second;
    }
    else
    {
        state = *config.defaultState;
    }

    std::smatch dateMatch;
    auto foundDate = std::
        regex_search(messageStd, dateMatch, std::regex(*config.dateRegExp));
    auto time = parseDate(
        QString::fromStdString(dateMatch[1].str()),
        QString::fromStdString(*config.inputDateFormat),
        QString::fromStdString(*config.outputDateFormat));

    auto data
        = std::map<QString, QString>{ { NAME, QString::fromStdString(name) },
                                      { STATE, QString::fromStdString(state) },
                                      { TIME, time } };

    return data;
}

auto encodeDeviceMessage(
    const ParserConfiguration& config, const QString& message)
{

    auto messageStd = message.toStdString();

    std::smatch match;
    auto found
        = std::regex_search(messageStd, match, std::regex(*config.regExp));

    auto name = std::string();
    auto state = std::string();

    if (found)
    {
        name = match[static_cast<size_t>(*config.deviceMatch)].str();
        state = match[static_cast<size_t>(*config.stateMatch)].str();
    }

    auto find = *config.devices->find(name);
    if (find != *config.devices->end())
    {
        name = find.second;
    }
    else
    {
        name = *config.defaultState;
    }

    std::smatch dateMatch;
    auto foundDate = std::
        regex_search(messageStd, dateMatch, std::regex(*config.dateRegExp));
    auto time = parseDate(
        QString::fromStdString(dateMatch[1].str()),
        QString::fromStdString(*config.inputDateFormat),
        QString::fromStdString(*config.outputDateFormat));

    auto data
        = std::map<QString, QString>{ { NAME, QString::fromStdString(name) },
                                      { STATE, QString::fromStdString(state) },
                                      { TIME, time } };

    return data;
}

auto encodeAllFromMessage(
    const ParserConfiguration& config, const QString& message)
{
    auto messageStd = message.toStdString();

    std::smatch match;
    auto found
        = std::regex_search(messageStd, match, std::regex(*config.regExp));

    auto name = std::string();
    auto state = std::string();

    if (found)
    {
        name = match[static_cast<size_t>(*config.deviceMatch)].str();
        state = match[static_cast<size_t>(*config.stateMatch)].str();
    }

    auto states = config.states.get();
    auto find = states.find(state);
    if (find != states.end())
    {
        state = find->second;
    }
    else
    {
        state = *config.defaultState;
    }

    auto devices = config.devices.get();
    auto findDevice = devices.find(name);
    if (findDevice!= devices.end())
    {
        name = findDevice->second;
    }
    else
    {
        name = *config.defaultDevice;
    }



    std::smatch dateMatch;
    auto foundDate = std::
        regex_search(messageStd, dateMatch, std::regex(*config.dateRegExp));
    auto time = parseDate(
        QString::fromStdString(dateMatch[1].str()),
        QString::fromStdString(*config.inputDateFormat),
        QString::fromStdString(*config.outputDateFormat));

    auto data
        = std::map<QString, QString>{ { NAME, QString::fromStdString(name) },
                                      { STATE, QString::fromStdString(state) },
                                      { TIME, time } };

    return data;
}

OrdinaryParserNew::OrdinaryParserNew(ParserConfiguration config)
    : m_conf(config)
{
}

ReportTable OrdinaryParserNew::parseTable(Table& table)
{
    auto reportTable = ReportTable{};
    auto deviceStates = std::map<QString, QString>{};
    for (auto& row: table)
    {
        auto data = parseMessage(row.at("msg"));

        if (deviceStates.find(data.at(NAME)) != deviceStates.end())
        {
            if (deviceStates.at(data.at(NAME)) != data.at(STATE))
            {
                reportTable.push_back(
                    { data.at(NAME), data.at(STATE), data.at(TIME) });
                deviceStates[data.at(NAME)] = data.at(STATE);
            }
        }
        else
        {

            reportTable.push_back(
                { data.at(NAME), data.at(STATE), data.at(TIME) });
            deviceStates[data.at(NAME)] = data.at(STATE);
        }
    }
    return reportTable;
}

std::map<QString, QString>
OrdinaryParserNew::parseMessage(std::vector<QString>& message)
{
    return {};
}

std::map<QString, QString>
OrdinaryParserNew::parseMessage(const QString& message)
{
    auto result = std::map<QString, QString>{};

    if (!m_conf.encodeStates & !m_conf.encodeDevice)
    {
        result = parseOrdinaryMessage(m_conf, message);
    }
    if (m_conf.encodeStates & !m_conf.encodeDevice)
    {
        result = encodeStateMessage(m_conf, message);
    }
    if (!m_conf.encodeStates & m_conf.encodeDevice)
    {
        result = encodeDeviceMessage(m_conf, message);
    }
    if (m_conf.encodeStates & m_conf.encodeDevice)
    {
        result = encodeAllFromMessage(m_conf, message);
    }

    return result;
}

ParserConfiguration &OrdinaryParserNew::config()
{
    return m_conf;
}

} // namespace mantis
