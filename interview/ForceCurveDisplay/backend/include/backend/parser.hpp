#pragma once
#include <QString>

template <typename DataType>
class Parser {
public:
    virtual DataType parse(QString const& str) const noexcept = 0;
};
