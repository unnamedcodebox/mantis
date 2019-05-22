#include "Watcher.h"

void mantis::Watcher::setConfiguration(QVariantList map){m_map = map;}

void mantis::Watcher::buttonClicked(int index)
{
    qDebug() << index << m_map.value(index).toMap()["device_list"].toStringList();
    qDebug() << index << m_map.value(index).toMap()["title"].toString();
    qDebug() << index << m_map.value(index).toMap()["id"].toString();
}
