///** @file
// * @brief     ConfiguredParserDeclaration
// *
// * @ingroup   MANTIS
// *
// * @copyright (C) 2019
// */

//#include "ConfiguredParser.h"
//#include "ConfigReader.h"
//#include <regex>
//#include <map>
//#include <QString>
//#include <boost/property_tree/ptree.hpp>

//namespace mantis
//{

//namespace
//{

//using ParserOptions = std::map<QString, QString>;

//bool optionExists(const ParserOptions& options, const QString& key)
//{
//    return options.find(key) != options.end();
//}

//} // namespace

//ConfiguredParser::ConfiguredParser(const QString config) : m_config(config) {}

//void ConfiguredParser::init()
//{
//    auto config = config::fromFile(m_config.toStdString());

//    auto stateMessage = config.get_child_optional("stateMessage");

//    if (stateMessage)
//    {
//        auto regExp = stateMessage.get().get_optional<std::string>("regExp");
//        if (regExp)
//        {
//            m_options["regExp"] = QString::fromStdString(*regExp);
//        }

//        auto deviceMatch
//            = stateMessage.get().get_optional<std::string>("deviceMatch");
//        if (deviceMatch)
//        {
//            m_options["deviceMatch"] = QString::fromStdString(*deviceMatch);
//        }

//        auto stateMatch
//            = stateMessage.get().get_optional<std::string>("stateMatch");
//        if (stateMatch)
//        {
//            m_options["stateMatch"] = QString::fromStdString(*stateMatch);
//        }

//        auto states = config.get_child_optional("states");

//        if (states)
//        {
//            auto statesRecord = std::map<QString, QString>{};

//            for (auto& state : *states)
//            {
//                m_states[QString::fromStdString(state.first)]
//                    = QString::fromStdString(state.second.data());
//            }
//            m_states = statesRecord;
//        }
//    }

//    auto timeMessage = config.get_child_optional("timeMessage");
//    if (timeMessage)
//    {
//        auto regExp = timeMessage.get().get_optional<std::string>("timeRegExp");
//        if (regExp)
//        {
//            m_options["timeRegExp"] = QString::fromStdString(*regExp);
//        }

//        auto timeMatch
//            = timeMessage.get().get_optional<std::string>("timeMatch");
//        if (timeMatch)
//        {
//            m_options["timeMatch"] = QString::fromStdString(*timeMatch);
//        }

//        auto inputFormat = timeMessage.get().get_optional<std::string>("input");
//        if (inputFormat)
//        {
//            m_options["input"] = QString::fromStdString(*inputFormat);
//        }

//        auto outputFormat
//            = timeMessage.get().get_optional<std::string>("output");
//        if (outputFormat)
//        {
//            m_options["output"] = QString::fromStdString(*outputFormat);
//        }
//    }
//}

//ReportTable ConfiguredParser::parseTable(Table& table) {}

//std::map<QString, QString> ConfiguredParser::parseMessage(std::vector<QString>&)
//{
//    return {};
//}

//std::map<QString, QString>
//ConfiguredParser::parseMessage(const QString& message)
//{
//    // auto regExp = "CODE \\( ([0-9]) \\)";

//    auto deviceResult = QString{};
//    auto stateResult = QString{};
//    auto time = QString{};

//    auto parseToInt
//        = [](const QString& matchedGroup) { return matchedGroup.toInt(); };

//    if (optionExists(m_options, "regExp"))
//    {
//        auto messageStd = message.toStdString();

//        auto stateMatch = 0;
//        auto deviceMatch = 0;

//        std::smatch match;
//        auto found = std::regex_search(
//            messageStd,
//            match,
//            std::regex(m_options.at("regExp").toStdString()));

//        auto isDeviceParsed = false;
//        if (optionExists(m_options, "deviceMatch"))
//        {
//            isDeviceParsed = true;
//            deviceMatch = parseToInt(m_options.at("deviceMatch"));
//        }

//        auto isStateParsed = false;
//        if (optionExists(m_options, "stateMatch"))
//        {
//            isStateParsed = true;
//            stateMatch = parseToInt(m_options.at("deviceMatch"));
//        }

//        auto name = std::string();
//        auto state = std::string();
//        if (found)
//        {
//            if (isDeviceParsed)
//            {
//                name = match[static_cast<size_t>(deviceMatch)].str();
//                deviceResult = QString::fromStdString(name);
//            }

//            if (isStateParsed)
//            {
//                state = match[static_cast<size_t>(stateMatch)].str();
//                if (!m_states.empty() && !state.empty())
//                {
//                    auto find = m_states.find(QString::fromStdString(state));
//                    if (find != m_states.end())
//                    {
//                        state = find->second.toStdString();
//                    }
//                }
//                stateResult = QString::fromStdString(state);
//            }
//        }
//    }

//    // auto deviceMatched = "1";
//    // auto stateMatcher = "1";
//    // auto deviceMatch = parseToInt(deviceMatched);
//    // auto stateMatch = parseToInt(stateMatcher);

//    auto statesConfig = true;
//    auto defaultState = "Неизвестно";

//    auto dateRegExp = "\\[c\\] \\'(.*)\' \\'";
//    std::smatch dateMatch;
//    auto foundDate
//        = std::regex_search(messageStd, dateMatch, std::regex(dateRegExp));
//    auto time = parseDate(
//        QString::fromStdString(dateMatch[1].str()),
//        INPUT_DATE_FORMAT,
//        OUTPUT_DATE_FORMAT);

//    auto data = std::map<QString, QString>{ { "name", QObject::tr("RPDU") },
//                                            { "state",
//                                              QString::fromStdString(state) },
//                                            { "time", time } };

//    return data;
//}

//} // namespace mantis
