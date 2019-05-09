/** @file
 * @brief     Parser declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Database.h"

#include <QString>

#include <map>
#include <vector>


namespace mantis
{

using ReportTable = std::vector<std::vector<QString>>;

/**
 * Interface for parser
 */
class Parser
{

public:
    /**
     * Parse table from Database to ReportTable
     */
    virtual ReportTable parseTable(Table& table) = 0;

    /**
     * Parse tokenized message
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) = 0;

    virtual ~Parser(){}
};
} // namespace mantis
