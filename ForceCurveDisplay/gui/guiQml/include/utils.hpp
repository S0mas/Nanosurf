#pragma once
#include <QGuiApplication>
#include <QObject>
#include <QCursor>
#include <QIcon>

class CursorPosProvider : public QObject {
    Q_OBJECT
public:
    CursorPosProvider(QObject *parent = nullptr) : QObject(parent){}
    Q_INVOKABLE QPointF cursorPos() {
        return QCursor::pos();
    }
};

inline void setIcon() noexcept {
    QIcon icon(":/../../resources/img/wave.ico");
    QGuiApplication::setWindowIcon(icon);
}
