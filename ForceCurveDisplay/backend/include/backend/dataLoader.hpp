#pragma once
#include <QVector>

template <typename DataType>
class DataLoader {
protected:
    QVector<DataType> data_;
public:
    virtual void loadData() = 0;
    auto data() const noexcept {
        return data_;
    }
};
