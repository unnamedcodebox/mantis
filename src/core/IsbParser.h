/** @file
 * @brief     Isb devices parser declaration
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

class IsbParser: public Parser
{

public:

    IsbParser();

    /**
     * Reimplemented from Parser
     */
    virtual ReportTable parseTable(Table& table) override;

    /**
     * Reimplemented from Parser
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) override;

private:
    std::map<QString, QString> m_placement;
    std::map<QString, QString> m_equipmentType;
};

} // namespace mantis
