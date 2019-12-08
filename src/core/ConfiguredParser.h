/** @file
 * @brief     ConfiguredParserDeclaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Database.h"
#include "Parser.h"

#include <QString>

#include <map>
#include <vector>


namespace mantis
{

using ReportTable = std::vector<std::vector<QString>>;

/**
 * Interface for parser
 */
class ConfiguredParser: public Parser
{

public:
    explicit ConfiguredParser(const QString config);

    /**
     * Init parser from configuration file
     */
    void init();

    /**
     * Parse table from Database to ReportTable
     */
    virtual ReportTable parseTable(Table& table) override;

    /**
     * Parse tokenized message
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) override;

    /**
     * Parse string message
     */
    virtual std::map<QString,QString> parseMessage(const QString& message);

private:
    QString m_config;
    std::map<QString, QString> m_options;
    std::map<QString, QString> m_states;


};

} // namespace mantis
