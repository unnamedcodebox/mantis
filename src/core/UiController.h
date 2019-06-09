/** @file
 * @brief     UiController declaration
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#pragma once

#include <QObject>
#include <QVariantList>
#include <QDebug>

/**
 * Class using for connect ui & ReportManager
 */
namespace mantis
{
class UiController : public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(int switchedIndex READ getIndex NOTIFY indexChanged)
public:
    void setConfiguration(QVariantList map);
    int getIndex();
public slots:
    void buttonClicked(int index);

    /**
     * Open created report file
     */
    void openReportFile();

    /**
     * Report path changed
     */
    void reportPathChanged(QString path);
signals:
    void reportSwitched();
    void indexChanged();
    void indexSwitched(int index);
    void sendReportInfo(QVariantMap reportInfo);
    void reportCreated(QString message);

private:
    QVariantList m_map;
    int switchedIndex;
    QString m_reportPath;
};

} // namespace mantis
