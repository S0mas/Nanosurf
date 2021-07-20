#pragma once
#include "log_item_qt.h"
#include "log_target_interface.h"

#include <QAbstractListModel>
#include <QContiguousCache>

class log_circular_list_model_qt final : public QAbstractListModel, public log_target_interface
{
  Q_OBJECT
  QContiguousCache<log_item_qt> buffer_;
  auto push(log_item_qt&& item)
  {
    buffer_.append(item);
  }
public:
  explicit log_circular_list_model_qt(int const capacity = 5000, QObject* parent = nullptr)
    : QAbstractListModel(parent)
    , buffer_{capacity}
  {
  }
  auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override
  {
    return buffer_.count();
  }
  auto data(const QModelIndex &index, int role = Qt::UserRole) const -> QVariant override
  {
    return buffer_.at(index.row()).data(role);
  }
  auto push_log(int const severity_level, const char* message) -> void override
  {
      push({severity_level, message});
  }
};
