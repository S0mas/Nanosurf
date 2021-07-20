#include "logger.h"
#include "log_circular_list_model_qt.h"
#include "log_delegate_qt.h"
#include "log_proxy_model_qt.h"
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

    auto model = new log_circular_list_model_qt(5000);
    logger.addTarget(model);

    logger.log(3, "Log severity 3");
    logger.log(1, "Log severity 1");
    logger.log(2, "Log severity 2");
    logger.log(3, "Log severity 3");
    logger.log(2, "Log severity 2");
    logger.log(1, "Log severity 1");
    logger.log(4, "Log severity 4");
    logger.log(3, "Log severity 3");
    logger.log(1, "Log severity 1");
    logger.log(2, "Log severity 2");
    logger.log(3, "Log severity 3");
    logger.log(2, "Log severity 2");
    logger.log(1, "Log severity 1");
    logger.log(3, "Log severity 3");
    logger.log(4, "Log severity 4");
/////////////////////////////

    log_filter_qt filter(5);

    log_proxy_model_qt proxy_model;
    proxy_model.setFilter(&filter);
    proxy_model.setSourceModel(model);

    auto list_view = new QListView;
    auto delegate = new log_delegate_qt;

    list_view->setModel(&proxy_model);
    auto oldDelegate = list_view->itemDelegate();
    delete oldDelegate;
    list_view->setItemDelegate(delegate);

/////////////////////////////
/// Presentation
    auto debugCheckBox = new QCheckBox("Debug");
    QObject::connect(debugCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(1, state); });

    auto infoCheckBox = new QCheckBox("Info");
    QObject::connect(infoCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(2, state); });

    auto warningCheckBox = new QCheckBox("Warning");
    QObject::connect(warningCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(3, state); });

    auto errorCheckBox = new QCheckBox("Error");
    QObject::connect(errorCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(4, state); });

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(debugCheckBox);
    hlayout->addWidget(infoCheckBox);
    hlayout->addWidget(warningCheckBox);
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
