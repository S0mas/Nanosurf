#pragma once
#include "log_item.h"
#include <QStandardItemModel>

class logger {
    QStandardItemModel model_;
public:
    logger() {}
    void log(int const severity_level, const char* msg) {
        model_.appendRow(new log_item(severity_level, msg));
    }
    auto logs() noexcept {
        return &model_;
    }
};
