#include "Watcher.h"

#include "ReportManager.h"

void mantis::Watcher::setConfiguration(QVariantList map){m_map = map;}

int mantis::Watcher::getIndex()
{
    return m_index;
}

void mantis::Watcher::buttonClicked(int index)
{
    qDebug() << index << m_map.value(index).toMap()["device_list"].toStringList();
    qDebug() << index << m_map.value(index).toMap()["title"].toString();
    qDebug() << index << m_map.value(index).toMap()["id"].toString();
    m_index = index;
    emit reportSwitched();
    emit indexSwitched(index);
}

void mantis::Watcher::reportPropertiesSetted(QString beginDate, QString endDate, QString reportId, QString subtype)
{
    qDebug() << beginDate;
    qDebug() << endDate;
    qDebug() << reportId;
    qDebug() << subtype;
}

void mantis::Watcher::takeVariantMap(QVariantMap map)
{
    qDebug() << "this is map" << map;
    auto deviceList = map["device_list"].toStringList();
    qDebug() << "this is my deviceList" << deviceList;
//    auto reportManager = std::make_unique<ReportManager>();
//    reportManager->createReport(map);
}
