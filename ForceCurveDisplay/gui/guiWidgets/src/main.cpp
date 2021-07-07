#include <QApplication>
#include <QWidget>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlEngine>

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

    /// QML WIDGET INIT ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    QQuickWidget *view = new QQuickWidget;
    view->setStyleSheet("background:transparent");
    view->setAttribute(Qt::WA_TranslucentBackground);
    view->setWindowFlags(Qt::FramelessWindowHint);

    BackendController backendController(std::make_unique<FileDataLoader<Sample>>("force_curve.csv", std::make_unique<SampleParser>()), std::make_unique<MyFilter<Sample>>());
    view->rootContext()->setContextProperty("backendController", &backendController);
    view->rootContext()->setContextProperty("chartData", &backendController.chartData_);

    CursorPosProvider mousePosProvider(view);
    view->rootContext()->setContextProperty("mousePosition", &mousePosProvider);

    QMainWindow mainWindow(nullptr, Qt::Window | Qt::FramelessWindowHint);

    PositionUpdater positionSetter(&mainWindow);
    view->rootContext()->setContextProperty("positionSetter", &positionSetter);
    view->setSource(QUrl(QString("qrc:/resources/qml/main.qml")));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    QObject::connect((QObject*)view->engine(), SIGNAL(quit()), &app, SLOT(quit()));

    mainWindow.setCentralWidget(view);
    mainWindow.setStyleSheet("background:transparent;");
    mainWindow.setAttribute(Qt::WA_TranslucentBackground);


    mainWindow.show();

    /// STARTING THE GUI APP //////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto result = app.exec();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AFTER GUI APP EXIT CODE ///////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return result;
}

