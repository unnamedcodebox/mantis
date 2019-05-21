#include "../config/ConfigReader.h"

#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include <memory>

namespace
{

} // anonymous

int main(int argc, char *argv[])
{
    using namespace mantis;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto data = readDeviceListFromFile("device_list.json", "state_tech");
    auto configuration = readReportsConfiguration("device_list.json");
    auto buttons = QStringList{};
    for(auto& it : configuration)
    {
        buttons.push_back(it.title);
    }
    engine.rootContext()->setContextProperty("titles",buttons);
    //engine.rootContext()->setContextProperty("reportData", data);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    return app.exec();
}
