#include "Watcher.h"

void mantis::Watcher::setConfiguration(QVariantList map){m_map = map;}

void mantis::Watcher::buttonClicked(int index)
{
    qDebug() << index << m_map.value(index).toMap()["deviceList"].toList().size();
    qDebug() << index << m_map.value(index).toMap()["title"].toString();
    qDebug() << index << m_map.value(index).toMap()["id"].toString();
}
