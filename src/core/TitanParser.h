/** @file
 * @brief     Titan device parser declaration
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

namespace  {

std::map<int, QString> initStates
    = { { 0, "Исправно" },          { 1, "Авария охлаждения" },
        { 2, "Авария накала" },     { 3, "Перегрев" },
        { 4, "Авария пневматики" }, { 5, "Авария сеть" } };

} // anonymous

class TitanParser: public Parser
{

public:
    explicit TitanParser(std::map<int, QString> states = initStates);

    /**
     * Reimplemented from Parser
     */
    virtual ReportTable parseTable(Table& table) override;

    /**
     * Reimplemented from Parser
     */
    virtual std::map<QString,QString> parseMessage(std::vector<QString>& message) override;

private:
    std::map<int, QString> m_states;
};

} // namespace mantis
