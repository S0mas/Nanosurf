#pragma once
#include <QLineSeries>
#include <QVector>
#include "sample.hpp"
#include <loguru/loguru.hpp>

class ChartData : public QObject {
    Q_OBJECT
    QLineSeries* series_ = nullptr;
    double maxMovement_ = 0;
    double maxForce_ = 0;
    double minMovement_ = 0;
    double minForce_ = 0;
public:
    Q_PROPERTY(QLineSeries* series MEMBER series_)
    Q_PROPERTY(double maxMovement MEMBER maxMovement_ NOTIFY maxMovementChanged)
    Q_PROPERTY(double maxForce MEMBER maxForce_ NOTIFY maxForceChanged)
    Q_PROPERTY(double minMovement MEMBER minMovement_ NOTIFY minMovementChanged)
    Q_PROPERTY(double minForce MEMBER minForce_ NOTIFY minForceChanged)

    void updateMinAndMax(QVector<Sample> const& data) noexcept {
        for(auto const& sample : data) {
            if(sample.x() > maxMovement_)
                maxMovement_ = sample.x();
            if(sample.x() < minMovement_)
                minMovement_ = sample.x();
            if(sample.y() > maxForce_)
                maxForce_ = sample.y();
            if(sample.y() < minForce_)
                minForce_ = sample.y();
        }
        emit maxMovementChanged();
        emit maxForceChanged();
        emit minMovementChanged();
        emit minForceChanged();
    }
    void updateSeries(QVector<Sample> const& data) noexcept {
        if(!series_) {
            DLOG_F(ERROR, "ChartData::%s no series set", __func__);
            return;
        }
        DLOG_F(INFO, "ChartData::%s updating series", __func__);
        series_->replace(data);
    }
signals:
    void maxMovementChanged() const;
    void maxForceChanged() const;
    void minMovementChanged() const;
    void minForceChanged() const;
};
