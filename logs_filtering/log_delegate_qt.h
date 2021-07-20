#pragma once
#include <QApplication>
#include <QPainter>
#include <QStyledItemDelegate>

class log_delegate_qt final : public QStyledItemDelegate
{
  Q_OBJECT
public:
  explicit log_delegate_qt(QObject *parent = 0)
  : QStyledItemDelegate(parent)
  {
  }
  auto paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const -> void override
  {
    auto const& severity_level = index.data(Qt::UserRole).toInt();
    auto text_pen = painter->pen();
    auto background_brush = painter->brush();
    switch (severity_level)
    {
      case 0:
        background_brush.setColor(QColor("#121212"));
        text_pen.setColor(QColor("#828282"));
        break;
      case 1:
        background_brush.setColor(QColor("#121212"));
        text_pen.setColor(QColor("#828282"));
        break;
      case 2:
        background_brush.setColor(QColor("#BDE5F8"));
        text_pen.setColor(QColor("#00529B"));
        break;
      case 3:
        background_brush.setColor(QColor("#FEEFB3"));
        text_pen.setColor(QColor("#9F6000"));
        break;
      case 4:
        background_brush.setColor(QColor("#FFD2D2"));
        text_pen.setColor(QColor("#D8000C"));
        break;
      case 5:
        background_brush.setColor(QColor("#FFD2D2"));
        text_pen.setColor(QColor("#D8000C"));
        break;
      default:
        break;
    }
    painter->save();
    painter->setPen(text_pen);
    painter->fillRect(option.rect, background_brush.color());
    painter->drawText(option.rect, index.data().toString());
    painter->restore();
  }
};
