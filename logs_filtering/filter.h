#pragma once
#include <QObject>
#include <QRegExp>
#include <QString>

class filter : public QObject {
    Q_OBJECT

    bool debug_ = false;
    bool info_ = false;
    bool error_ = false;
public:
    QRegExp regExp() const noexcept {
        QString str = "[";
        if(debug_)
            str += "0,";
        if(info_)
            str += "1,";
        if(error_)
            str += "2,";
        if(debug_ || info_ || error_)
            str.chop(1);
        str += "]";
        return QRegExp(str);
    }
public slots:
    void setDebug(bool const state) noexcept {
        debug_ = state;
        emit filterUpdated();
    }
    void setInfo(bool const state) noexcept {
        info_ = state;
        emit filterUpdated();
    }
    void setError(bool const state) noexcept {
        error_ = state;
        emit filterUpdated();
    }
signals:
    void filterUpdated() const;
};
