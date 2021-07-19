#pragma once
#include <QStandardItem>
#include <QString>

class log_item : public QStandardItem {
    int severity_level_;
public:
    log_item(int const severity_level, QString const& message)
        : QStandardItem(message)
        , severity_level_(severity_level) {}
    QVariant data(int role = Qt::UserRole + 1) const override {
        if(role != Qt::UserRole)
            return QStandardItem::data(role);
        return severity_level_;
    }
};
