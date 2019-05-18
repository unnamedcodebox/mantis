/** @file
 * @brief     AppName declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include <QString>

namespace mantis
{

enum class AppName
{
    ICS,
    PCS
};

QString getAppName(AppName name);

} // namespace mantis
