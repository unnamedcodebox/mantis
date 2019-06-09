#include "../config/ConfigReader.h"

#include "../core/Database.h"
#include "../core/OrdinaryParser.h"
#include "../core/TitanParser.h"
#include "../core/IsbParser.h"
#include "../core/ReportManager.h"
#include "../core/UiController.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariantList>
#include <QObject>
#include <QThread>
#include <QTranslator>

#include <QQmlContext>
#include <memory>

namespace
{

const auto APP_TR_PATH = "mantis_ru.qm";
const auto CORE_TR_PATH = "../core/core_ru.qm";

void installTranslators(
    QGuiApplication& app,
    QTranslator& appTranslator,
    QTranslator& coreTranslator)
{
    appTranslator.load(APP_TR_PATH);
    coreTranslator.load(CORE_TR_PATH);

    app.installTranslator(&appTranslator);
    app.installTranslator(&coreTranslator);
}

} // namespace

int main(int argc, char* argv[])
{
    using namespace mantis;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QTranslator appTranslator;
    QTranslator coreTranslator;

    installTranslators(app, appTranslator, coreTranslator);

    QQmlApplicationEngine engine;

    auto components = readReportsConfiguration("device_list.json");
    auto databaseConfig = config::fromFile("config.json");

    QThread* thread = new QThread();
    auto reportManager = std::make_shared<ReportManager>(databaseConfig);
    reportManager->moveToThread(thread);
    auto controller = std::make_shared<UiController>();
    controller->setConfiguration(components);

    QObject::connect(
        thread,
        &QThread::started,
        reportManager.get(),
        &ReportManager::start,
        Qt::QueuedConnection);
    QObject::connect(
        controller.get(),
        &UiController::sendReportInfo,
        reportManager.get(),
        &ReportManager::createReport,
        Qt::QueuedConnection);
    QObject::connect(
        reportManager.get(),
        &ReportManager::reportCreated,
        controller.get(),
        &UiController::reportCreated);
    QObject::connect(
        reportManager.get(),
        &ReportManager::sendReportPath,
        controller.get(),
        &UiController::reportPathChanged);

    thread->start();

    engine.rootContext()->setContextProperty("components", components);
    engine.rootContext()->setContextProperty("uiController", controller.get());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
