#pragma once
#include <QStandardItem>
#include <QString>

class log_item_qt final : public QStandardItem
{
  int severity_level_;
public:
  explicit log_item_qt(int const severity_level, QString const& message)
    : QStandardItem(message)
    , severity_level_(severity_level)
  {
  }
  auto data(int role = Qt::UserRole) const -> QVariant override
  {
    if(role != Qt::UserRole)
        return QStandardItem::data(role);
    return severity_level_;
  }
};
