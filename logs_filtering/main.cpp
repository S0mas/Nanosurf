#include "logger.h"
#include "proxy_model.h"
#include <QApplication>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

/////////////////////////////
/// Example logs
    logger logger;
    logger.log(0, "Log severity 0");
    logger.log(1, "Log severity 1");
    logger.log(2, "Log severity 2");
    logger.log(0, "Log severity 0");
    logger.log(2, "Log severity 2");
    logger.log(1, "Log severity 1");
    logger.log(0, "Log severity 0");
    logger.log(1, "Log severity 1");
    logger.log(2, "Log severity 2");
    logger.log(0, "Log severity 0");
    logger.log(2, "Log severity 2");
    logger.log(1, "Log severity 1");
    logger.log(0, "Log severity 0");
/////////////////////////////

    filter filter;

    proxy_model proxy_model;
    proxy_model.setFilter(&filter);
    proxy_model.setSourceModel(logger.logs());

    auto list_view = new QListView;
    list_view->setModel(&proxy_model);

/////////////////////////////
/// Presentation
    auto debugCheckBox = new QCheckBox("Debug");
    QObject::connect(debugCheckBox, &QCheckBox::toggled, &filter, &filter::setDebug);

    auto infoCheckBox = new QCheckBox("Info");
    QObject::connect(infoCheckBox, &QCheckBox::toggled, &filter, &filter::setInfo);

    auto errorCheckBox = new QCheckBox("Error");
    QObject::connect(errorCheckBox, &QCheckBox::toggled, &filter, &filter::setError);

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(debugCheckBox);
    hlayout->addWidget(infoCheckBox);
    hlayout->addWidget(errorCheckBox);

    auto vlayout = new QVBoxLayout;
    vlayout->addWidget(list_view);
    vlayout->addLayout(hlayout);

    QWidget w;
    w.setLayout(vlayout);
    w.show();
/////////////////////////////

    return a.exec();
}
