#pragma once
#include <QObject>
#include <QVariantList>
#include <QDebug>
namespace mantis
{
class Watcher: public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(int m_index READ getIndex)
public:
    void setConfiguration(QVariantList map);
    int getIndex();
public slots:
    void buttonClicked(int index);
    void reportPropertiesSetted(QString beginDate, QString endDate, QString reportId, QString subtype);
    void takeVariantMap(QVariantMap map);
signals:
    void reportSwitched();
    void indexSwitched(int index);

private:
    QVariantList m_map;
    int m_index;
};

}
