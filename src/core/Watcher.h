#pragma once
#include <QObject>
#include <QVariantList>
#include <QDebug>
namespace mantis
{
class Watcher: public QObject
{
    Q_OBJECT
public:
    void setConfiguration(QVariantList map);
public slots:
    void buttonClicked(int index);

private:
    QVariantList m_map;
};

}
