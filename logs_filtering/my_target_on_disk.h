#pragma once
#include "log_target_interface.h"

#include <QDebug>

class my_target_on_disk : public log_target_interface {
    auto push_log_impl(int const severity_level, const char* message) -> void override {
       ////
       //// write log into the file
       qDebug() << "writing log to file...";
    }
};
