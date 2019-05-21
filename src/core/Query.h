/** @file
 * @brief     Query interface
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "AppName.h"

#include <QString>

namespace mantis
{
/**
 * Class describes Query interface
 */
class Query
{
public:
    /**
     * Method to init Query
     */
    virtual void init() = 0;

    /**
     * Get query string
     */
    virtual QString get() = 0;

    virtual ~Query() = default;
};

} // namespace mantis
