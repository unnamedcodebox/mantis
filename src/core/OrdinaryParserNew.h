/** @file
 * @brief     Ordinary devices parser declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Parser.h"
#include "Configuration.h"

#include <map>
#include <vector>
#include <QString>

namespace mantis
{
/**
 * @brief The OrdinaryParserNew class using for parsing for Ordinary device group
 */
class OrdinaryParserNew: public Parser
{

public:

    explicit OrdinaryParserNew(ParserConfiguration configuration = ParserConfiguration());

    /**
     * Reimplemented from Parser
     */
    virtual ReportTable parseTable(Table& table) override;

    /**
     * Reimplemented from Parser
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) override;

    std::map<QString, QString> parseMessage(const QString &message);

    ParserConfiguration& config();
private:
    ParserConfiguration m_conf;
};

} // namespace mantis
