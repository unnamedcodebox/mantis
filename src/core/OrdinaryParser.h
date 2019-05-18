/** @file
 * @brief     Ordinary devices parser declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "Parser.h"

#include <map>
#include <vector>
#include <QString>

namespace mantis
{
/**
 * @brief The OrdinaryParser class using for parsing "ordinary" device groups:
 * Commutation Station, SNMP, Loudspeaker
 */
class OrdinaryParser: public Parser
{

public:
    /**
     * Reimplemented from Parser
     */
    virtual ReportTable parseTable(Table& table) override;

    /**
     * Reimplemented from Parser
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) override;

};

} // namespace mantis
