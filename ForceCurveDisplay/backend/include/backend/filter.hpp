#pragma once
#include <QVector>

template <typename DataType>
class Filter {
public:
    virtual QVector<DataType> filterData(QVector<DataType> const& data) const noexcept = 0;
};
