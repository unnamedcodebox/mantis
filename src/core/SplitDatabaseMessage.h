/** @file
 * @brief     Split database message declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include "AppName.h"

#include <vector>

class QString;

namespace mantis
{

/**
 * Split database message depends on application
 */
std::vector<QString> splitDatabaseMessage(QString message, AppName appName = AppName::ICS);

} // namespace mantis
