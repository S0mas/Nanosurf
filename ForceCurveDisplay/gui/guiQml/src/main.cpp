#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include <backend/backend.hpp>
#include <backend/myFilter.hpp>
#include <backend/fileDataLoader.hpp>
#include <backend/sampleParser.hpp>
#include "../include/utils.hpp"

int main(int argc, char *argv[]) {
    /// APPLICATION INITIALIZATION ////////////////////////////////////////////////////////////////////////////////////////////////
    loguru::init(argc, argv);
    loguru::add_file("qml_everything.log", loguru::Append, loguru::Verbosity_MAX);
    loguru::add_file("qml_latest_readable.log", loguru::Truncate, loguru::Verbosity_INFO);

    QApplication app(argc, argv);
    app.setOrganizationName("Nanosurf");
    app.setOrganizationDomain("Nanosurf");
    app.setApplicationName("Nanosurf Force Curve Display");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// ADDITIONAL APP INIT ///////////////////////////////////////////////////////////////////////////////////////////////////////
    setIcon();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QQmlApplicationEngine engine;

    /// ROOTCONTEXT INIT ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    BackendController backendController(std::make_unique<FileDataLoader<Sample>>("", std::make_unique<SampleParser>()), std::make_unique<MyFilter<Sample>>());
    engine.rootContext()->setContextProperty("backendController", &backendController);
    engine.rootContext()->setContextProperty("chartData", &backendController.chartData_);

    CursorPosProvider mousePosProvider;
    engine.rootContext()->setContextProperty("mousePosition", &mousePosProvider);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// STARTING THE GUI APP //////////////////////////////////////////////////////////////////////////////////////////////////////////
    const QUrl url(QString("qrc:/resources/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    auto result = app.exec();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AFTER GUI APP EXIT CODE ///////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return result;
}

