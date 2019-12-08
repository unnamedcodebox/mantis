/** @file
 * @brief     Ordinary Query implementation
 *
 * @ingroup   MANTIS
 *
 * @copyright (C) 2019
 */

#include "OrdinaryQuery.h"
#include <QDebug>
#include <QObject>

namespace  {

const auto QUERY_TEMPLATE
    = "SELECT xx_FIELDS_xx FROM xx_TABLE_NAME_xx WHERE xx_STATEMENT_xx AND "
      "xx_TIMESTAMP_xx>='xx_BEGIN_DATE_xx' AND "
      "xx_TIMESTAMP_xx<='xx_END_DATE_xx' ORDER BY xx_TIMESTAMP_xx;";

const auto FIELDS = "xx_FIELDS_xx";
const auto TABLE_NAME = "xx_TABLE_NAME_xx";
const auto STATEMENT = "xx_STATEMENT_xx";
const auto TIME_STAMP = "xx_TIMESTAMP_xx";
const auto BEGIN_DATE = "xx_BEGIN_DATE_xx";
const auto END_DATE = "xx_END_DATE_xx";
const auto DEVICE_LIST = "xx_DEVICE_LIST_xx";

const auto MESSAGE_FIELD = "message";
const auto TIME_STAMP_FIELD = "timestamp";
}

namespace mantis
{

OrdinaryQuery::OrdinaryQuery(QStringList deviceList, QString beginDate, QString endDate, QueryConfiguration configuration)
    : m_deviceList(std::move(deviceList))
    , m_beginDate(std::move(beginDate))
    , m_endDate(std::move(endDate)),
      m_conf(std::move(configuration))
{
    init();
}

void OrdinaryQuery::init()
{
    if(m_conf.useRawString)
    {
        m_query = m_conf.useRawString;
    }
    else
    {
        auto devices = m_deviceList.join("|");

        auto query = QString(QUERY_TEMPLATE);
        query.replace(TABLE_NAME, QString::fromStdString(*m_conf.tableName));
        query.replace(BEGIN_DATE, m_beginDate);
        query.replace(END_DATE, m_endDate);
        query.replace(STATEMENT, QString::fromStdString(*m_conf.whereStatement));

        auto timestamp = m_conf.fields->at(TIME_STAMP_FIELD);
        auto message = m_conf.fields->at(MESSAGE_FIELD);
        query.replace(DEVICE_LIST, devices);

        query.replace(TIME_STAMP, QString::fromStdString(timestamp));
        //query.replace()

        auto fields = QStringList{};

        for(const auto& field : *m_conf.fields)
        {
        fields.push_back(QString::fromStdString(field.second));
        }
        query.replace(FIELDS, fields.join(","));

        m_query = query;

    }

    qDebug() << m_query;
}

QString OrdinaryQuery::get()
{
    return m_query;
}

QueryConfiguration &OrdinaryQuery::config()
{
    return m_conf;
}

}; // namespace mantis
