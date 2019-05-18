/** @file
 * @brief     AppName implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "AppName.h"

namespace mantis
{

QString getAppName(AppName name)
{
    switch (name)
    {
    case AppName::ICS:
        return "ics";
    case AppName::PCS:
        return "PCS";
    }
    return {};
}

} // namespace mantis
