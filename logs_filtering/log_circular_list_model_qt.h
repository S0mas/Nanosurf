#pragma once
#include "log_item.h"
#include "log_subscriber_interface.h"
#include "my_target_in_program_memory.h"
#include <boost/circular_buffer.hpp>
#include <QAbstractListModel>
#include <QDebug>

class log_circular_list_model_qt final : public QAbstractListModel, public log_subscriber_interface
{
  Q_OBJECT
  std::shared_ptr<boost::circular_buffer<log_item>> buffer_;

  auto beginPush() -> void override
  {
    beginInsertRows(QModelIndex(), buffer_->size(), buffer_->size() + 1);
  }
  auto endPush() -> void override
  {
    endInsertRows();
    if(buffer_->size()+1 > buffer_->capacity())
      emit dataChanged(index(0, 0), index(buffer_->size() - 1, 0));
  }
public:
  explicit log_circular_list_model_qt(my_target_in_program_memory& target, QObject* parent = nullptr)
    : QAbstractListModel(parent)
    , buffer_{target.buffer()}
  {
    target.addSubscriber(this);
  }
  auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override
  {
    return buffer_->size();
  }
  auto data(const QModelIndex &index, int role = Qt::UserRole) const -> QVariant override
  {
    auto const& item = buffer_->at(index.row());
    switch (role) {
      case Qt::DisplayRole:
        return QVariant(item.message().c_str());
      case Qt::UserRole:
        return item.severity_level();
      default:
        return QVariant();
    }
  }
};
