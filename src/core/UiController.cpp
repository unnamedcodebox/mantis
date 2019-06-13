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
//    QProcess q1;
//    q1.start("sh", QStringList() << "-c" << "libreoffice --calc " + m_reportPath);
    qDebug() << m_reportPath;

//    std::system(QString{"LD_LIBRARY_PATH=\"$LD_LIBRARY_PATH:/usr/lib/libreoffice/program/\" libreoffice --calc " +m_reportPath}.toStdString().c_str());
    //QDesktopServices::openUrl("file://"+m_reportPath);
    //QDesktopServices::openUrl(QString("/home/amyasnikov/Documents/Reports/commutation_station/06_11_2019_01_48.xlsx"));
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
