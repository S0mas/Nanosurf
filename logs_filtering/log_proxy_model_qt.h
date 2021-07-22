#pragma once
#include "log_filter_qt.h"

#include <QSortFilterProxyModel>
#include <QDebug>
class log_proxy_model_qt : public QSortFilterProxyModel {
  Q_OBJECT
  log_filter_qt* filter_;
protected:
  auto filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const -> bool override
  {
    auto const& index = sourceModel()->index(sourceRow, 0, sourceParent);
    if(index.row() < 0)
        return false;
    auto const& severity_level = sourceModel()->data(index, Qt::UserRole).toUInt();
    return QString::number(severity_level).contains(filterRegExp());
  }
public:
  explicit log_proxy_model_qt(QObject* parent = nullptr) : QSortFilterProxyModel(parent)
  {
  }
  auto setFilter(log_filter_qt* filter) noexcept -> void
  {
    filter_ = filter;
    setFilterRegExp(filter_->regExp());
    connect(filter_, &log_filter_qt::filterUpdated, this, [this]() { setFilterRegExp(filter_->regExp()); });
    connect(sourceModel(), &QAbstractItemModel::dataChanged, this, [this]() { setFilterRegExp(filter_->regExp()); });
  }
};
