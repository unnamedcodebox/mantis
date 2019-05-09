/** @file
 * @brief     Split database message implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "SplitDatabaseMessage.h"

#include <QString>
#include <QStringList>
#include <QRegExp>

#include <map>

namespace mantis
{

std::vector<QString> splitDatabaseMessage(QString message, AppName appName)
{
    auto parts = std::vector<QString>{};
    auto list = QStringList{};

    switch (appName)
    {
    case AppName::ICS:
    list = message.split(QRegExp("[<>{}='\\[\\]]"), QString::SkipEmptyParts);
        break;
    case AppName::PCS:
        list = message.split(':', QString::SkipEmptyParts);
        break;
    }

    for (const auto& it : list)
    {
        parts.push_back(it);
    }

    return parts;
}

} // namespace mantis
