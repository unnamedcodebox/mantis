#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <memory>

namespace
{

QStringList readDeviceListFromFile(const std::string& fileName, const std::string& reportName)
{
    boost::property_tree::ptree config;
    boost::property_tree::read_json(fileName, config);
    auto deviceTree = config.get_child(reportName);
    auto deviceList = QStringList{};
    for (auto& it: deviceTree)
    {
        deviceList.push_back(
            QString::fromStdString(it.second.get_value<std::string>()));
    }

    return deviceList;
}
} // anonymous

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    auto data = readDeviceListFromFile("device_list.json", "state_tech");
    engine.rootContext()->setContextProperty("reportData", data);

    return app.exec();
}
