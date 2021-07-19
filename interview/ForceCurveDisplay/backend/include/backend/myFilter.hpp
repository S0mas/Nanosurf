#pragma once
#include "filter.hpp"

template <typename DataType>
class MyFilter : public Filter<DataType> {
public:
    QVector<DataType> filterData(QVector<DataType> const& data) const noexcept override {
        DLOG_F(INFO, "MyFilter::%s", __func__);
        QVector<DataType> result;
        //TODO: IMPLEMENT
        return result;
    }
};
