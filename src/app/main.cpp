#include "../config/ConfigReader.h"

#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"
#include "../core/Watcher.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariantList>
#include <QObject>

#include <QQmlContext>

#include <memory>

int main(int argc, char *argv[])
{
    using namespace mantis;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto data = readDeviceListFromFile("device_list.json", "state_tech");
    auto components = readReportsConfiguration("device_list.json");

    auto watcher = new Watcher();
    watcher->setConfiguration(components);
    engine.rootContext()->setContextProperty("components", components);
    engine.rootContext()->setContextProperty("watcher", watcher);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
