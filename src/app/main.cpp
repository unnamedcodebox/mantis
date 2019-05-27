#include "../config/ConfigReader.h"

#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"
#include "../core/ReportManager.h"
#include "../core/Watcher.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariantList>
#include <QObject>

#include <QQmlContext>

#include <memory>

int main(int argc, char* argv[])
{
    using namespace mantis;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto data = readDeviceListFromFile("device_list.json", "state_tech");
    auto components = readReportsConfiguration("device_list.json");

    auto databaseConfig = config::fromFile("config.json");
    auto database = std::make_shared<Database>(databaseConfig);

    auto reportManager = std::make_shared<ReportManager>(database);
    auto watcher = std::make_shared<Watcher>();
    watcher->setConfiguration(components);

    engine.rootContext()->setContextProperty("components", components);
    engine.rootContext()->setContextProperty("watcher", watcher.get());
    engine.rootContext()->setContextProperty("reportManager", reportManager.get());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
