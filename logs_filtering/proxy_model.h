#pragma once
#include "filter.h"
#include <QSortFilterProxyModel>

class proxy_model : public QSortFilterProxyModel {
    Q_OBJECT
    filter* filter_;
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        auto const& index = sourceModel()->index(sourceRow, 0, sourceParent);
        auto const& severity_level = sourceModel()->data(index, Qt::UserRole).toUInt();
        return QString::number(severity_level).contains(filterRegExp());
    }
public:
    proxy_model(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}
    void setFilter(filter* filter) noexcept {
        filter_ = filter;
        setFilterRegExp(filter_->regExp());
        connect(filter_, &filter::filterUpdated, this, [this]() { setFilterRegExp(filter_->regExp()); });
    }
};
