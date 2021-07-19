#pragma once
#include <QString>
#include <QTextStream>
#include "parser.hpp"
#include "sample.hpp"
#include "loguru/loguru.hpp"

class SampleParser : public Parser<Sample> {
public:
    Sample parse(QString const& str) const noexcept override {
        auto const& values = str.split(";");
        if(values.size() != 2) {
            DLOG_F(ERROR, "SampleParser::%s parsing error, str:'%s'", __func__, str.toStdString().c_str());
            return Sample(0, 0);
        }

        long double movement = values.at(0).toDouble();
        long double force =  values.at(1).toDouble();
        Sample sample(movement, force);
        //DLOG_F(INFO, "SampleParser::%s parsing '%s' to movement: %1.5e force:%1.5e", __func__, str.toStdString().c_str(), sample.x(), sample.y());
        return sample;
    }
};
