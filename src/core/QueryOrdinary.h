///** @file
// * @brief     Ordinary Query declaration
// *
// * @ingroup   MANTIS
// *
// * @copyright (C) 2019
// */

//#pragma once

//#include "Query.h"

//#include <QString>
//#include <QStringList>

//namespace mantis
//{
///**
// * Class using for implement query for ordinary devices
// */
//class QueryOrdinary: public Query
//{
//public:
//    QueryOrdinary(
//        AppName appName,
//        QStringList deviceList,
//        QString beginDate,
//        QString endDate);

//    /**
//     * Reimplemented from Query
//     */
//    virtual void init() override;

//    /**
//     * Reimplemented from Query
//     */
//    virtual QString get() override;

//    QueryConfiguration& config();

//private:
//    AppName m_appName;
//    QStringList m_deviceList;
//    QString m_beginDate;
//    QString m_endDate;
//    QString m_query;
//};

//} // namespace mantis
