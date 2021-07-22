#include "my_target_on_disk.h"
#include "logger.h"
#include "log_circular_list_model_qt.h"
#include "log_delegate_qt.h"
#include "log_proxy_model_qt.h"
#include "log_target_interface_with_subscribers.h"

#include <QApplication>
#include <QCheckBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>

#include <memory>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

/////////////////////////////
/// Example logs
    logger logger;
    my_target_in_program_memory target_in_memory;
    my_target_on_disk target_on_disk;
    logger.addTarget(&target_in_memory);
    logger.addTarget(&target_on_disk);

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
/// View 1
    log_filter_qt filter(5);

    auto model1 = new log_circular_list_model_qt(target_in_memory);
    log_proxy_model_qt proxy_model;
    proxy_model.setFilter(&filter);
    proxy_model.setSourceModel(model1);

    auto list_view = new QListView;
    auto delegate = new log_delegate_qt;

    list_view->setModel(&proxy_model);
    auto oldDelegate = list_view->itemDelegate();
    delete oldDelegate;
    list_view->setItemDelegate(delegate);

/////////////////////////////

/////////////////////////////
/// View 2
    log_filter_qt filter2(5);

    auto model2 = new log_circular_list_model_qt(target_in_memory);
    log_proxy_model_qt proxy_model2;
    proxy_model2.setFilter(&filter2);
    proxy_model2.setSourceModel(model2);

    auto list_view2 = new QListView;
    auto delegate2 = new log_delegate_qt;

    list_view2->setModel(&proxy_model2);
    auto oldDelegate2 = list_view2->itemDelegate();
    delete oldDelegate2;
    list_view2->setItemDelegate(delegate2);

/////////////////////////////

/// Presentation
    auto traceCheckBox = new QCheckBox("Trace");
    QObject::connect(traceCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(0, state); });

    auto debugCheckBox = new QCheckBox("Debug");
    QObject::connect(debugCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(1, state); });

    auto infoCheckBox = new QCheckBox("Info");
    QObject::connect(infoCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(2, state); });

    auto warningCheckBox = new QCheckBox("Warning");
    QObject::connect(warningCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(3, state); });

    auto errorCheckBox = new QCheckBox("Error");
    QObject::connect(errorCheckBox, &QCheckBox::toggled, &filter, [&filter](auto const state) { filter.set(4, state); });

    auto hlayout = new QHBoxLayout;
    hlayout->addWidget(traceCheckBox);
    hlayout->addWidget(debugCheckBox);
    hlayout->addWidget(infoCheckBox);
    hlayout->addWidget(warningCheckBox);
    hlayout->addWidget(errorCheckBox);

    auto vlayout = new QVBoxLayout;
    vlayout->addWidget(list_view);
    vlayout->addLayout(hlayout);

    auto traceCheckBox2 = new QCheckBox("Trace");
    QObject::connect(traceCheckBox2, &QCheckBox::toggled, &filter2, [&filter2](auto const state) { filter2.set(0, state); });

    auto debugCheckBox2 = new QCheckBox("Debug");
    QObject::connect(debugCheckBox2, &QCheckBox::toggled, &filter2, [&filter2](auto const state) { filter2.set(1, state); });

    auto infoCheckBox2 = new QCheckBox("Info");
    QObject::connect(infoCheckBox2, &QCheckBox::toggled, &filter2, [&filter2](auto const state) { filter2.set(2, state); });

    auto warningCheckBox2 = new QCheckBox("Warning");
    QObject::connect(warningCheckBox2, &QCheckBox::toggled, &filter2, [&filter2](auto const state) { filter2.set(3, state); });

    auto errorCheckBox2 = new QCheckBox("Error");
    QObject::connect(errorCheckBox2, &QCheckBox::toggled, &filter2, [&filter2](auto const state) { filter2.set(4, state); });

    auto hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(traceCheckBox2);
    hlayout2->addWidget(debugCheckBox2);
    hlayout2->addWidget(infoCheckBox2);
    hlayout2->addWidget(warningCheckBox2);
    hlayout2->addWidget(errorCheckBox2);

    auto vlayout2 = new QVBoxLayout;
    vlayout2->addWidget(list_view2);
    vlayout2->addLayout(hlayout2);

    auto button = new QPushButton("add log");
    QObject::connect(button, &QPushButton::clicked, button, [&logger]() { static int id = 0; logger.log(QRandomGenerator::global()->generate() % 5, QString("new log id: %1").arg(id++).toStdString().c_str()); });

    auto hlayout3 = new QHBoxLayout;
    hlayout3->addLayout(vlayout);
    hlayout3->addLayout(vlayout2);

    auto vlayout3 = new QVBoxLayout;
    vlayout3->addLayout(hlayout3);
    vlayout3->addWidget(button);

    QWidget w;
    w.setLayout(vlayout3);
    w.show();
/////////////////////////////

    return a.exec();
}
