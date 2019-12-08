/** @file
 * @brief     UiController implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "UiController.h"

#include "ReportManager.h"

#include <QDesktopServices>
#include <cstdlib>
#include <QProcess>
#include <QUrl>

namespace mantis
{

void UiController::setConfiguration(QVariantList map)
{
    m_map = map;
}

void UiController::buttonClicked(int index)
{
    switchedIndex = index;
    emit reportSwitched();
    emit indexSwitched(index);
}

void UiController::openReportFile()
{

    qDebug() << m_reportPath;

    QDesktopServices::openUrl(m_reportPath);
}

void UiController::reportPathChanged(QString path)
{
    m_reportPath = path;
}

int UiController::getIndex()
{
    return switchedIndex;
}

} // namespace mantis
