#pragma once
#include <QObject>
#include <QRegExp>
#include <QString>

class log_filter_qt final : public QObject {
  Q_OBJECT
  std::vector<bool> severity_levels_states_;
public:
  explicit log_filter_qt(int const severity_levels_count, QObject* parent = nullptr)
    : QObject(parent)
    , severity_levels_states_(severity_levels_count, false)
  {
  }
  QRegExp regExp() const noexcept
  {
    QString str = "[";
    for(int severity_level = 0; severity_level < severity_levels_states_.size(); ++severity_level) {
        if(severity_levels_states_[severity_level])
            str += QString("%1,").arg(severity_level);
    }
    if(str.size() != 1)
        str.chop(1);
    str += "]";
    return QRegExp(str);
  }
public slots:
  void set(int const severity_level, bool const state) noexcept
  {
    severity_levels_states_.at(severity_level) = state;
    emit filterUpdated();
  }
signals:
  void filterUpdated() const;
};
