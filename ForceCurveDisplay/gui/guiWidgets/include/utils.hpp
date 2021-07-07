#pragma once
#include <QGuiApplication>
#include <QObject>
#include <QWidget>
#include <QCursor>
#include <QIcon>

class CursorPosProvider : public QObject {
    Q_OBJECT
    QWidget* baseCoordsWidget;
public:
    CursorPosProvider(QWidget* baseCoordsWidget, QObject *parent = nullptr) : QObject(parent), baseCoordsWidget(baseCoordsWidget) {}
    Q_INVOKABLE QPointF cursorPos() {
        return baseCoordsWidget->mapFromGlobal(QCursor::pos());
    }
};

inline void setIcon() noexcept {
    QIcon icon(":/../../resources/img/wave.ico");
    QGuiApplication::setWindowIcon(icon);
}

class PositionUpdater : public QObject {
    Q_OBJECT
    QWidget* widget;
public:
    PositionUpdater(QWidget* widget) : widget(widget) {}
    Q_INVOKABLE void updatePosition(double const x, double y) {
        widget->move(x, y);
    }
};
