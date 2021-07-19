#pragma once
#include <QObject>
#include <QString>
#include <QFuture>
#include <QFutureWatcher>
#include <QtCharts>

#include <loguru/loguru.hpp>
#include <QtConcurrent>
#include <utility>
#include <QVector>
#include <memory>
#include "fileDataLoader.hpp"
#include "filter.hpp"
#include "sample.hpp"
#include "chartData.hpp"

class Backend : public QObject {
    Q_OBJECT
    std::unique_ptr<DataLoader<Sample>> dataLoader_;
    std::unique_ptr<Filter<Sample>> filter_;
    QVector<Sample> filteredData_;
public:
    Backend(std::unique_ptr<DataLoader<Sample>>&& dataLoader, std::unique_ptr<Filter<Sample>>&& filter) : dataLoader_(std::move(dataLoader)), filter_(std::move(filter)) {}

    void loadData() {
        DLOG_F(INFO, "Backend::%s", __func__);
        dataLoader_->loadData();
    }
    void filterData() noexcept {
        DLOG_F(INFO, "Backend::%s", __func__);
        filteredData_ = filter_->filterData(dataLoader_->data());
    }
    QVector<Sample> data() const noexcept {
        return dataLoader_->data();
    }
    QVector<Sample> filteredData() const noexcept {
        return filteredData_;
    }
    void updateFileName(QString const& fileName) const noexcept {
        if(auto castPtr = dynamic_cast<FileDataLoader<Sample>*>(dataLoader_.get()); castPtr)
            castPtr->setFileName(fileName);
    }
};

class BackendController : public QObject {
    Q_OBJECT
    std::unique_ptr<Backend> backend_;
    template<typename ReturnType, typename CallbackFunction>
    void call(QFuture<ReturnType> future, CallbackFunction const& callback) noexcept {
        auto *watcher = new QFutureWatcher<ReturnType>(this);
        QObject::connect(watcher, &QFutureWatcher<ReturnType>::finished,
                         this, [watcher, callback]() {
            callback(watcher->result());
            watcher->deleteLater();
        });
        watcher->setFuture(future);
    }
    template<typename CallbackFunction>
    void call(QFuture<void> future, CallbackFunction const& callback) noexcept {
        auto *watcher = new QFutureWatcher<void>(this);
        QObject::connect(watcher, &QFutureWatcher<void>::finished,
                         this, [watcher, callback]() {
            callback();
            watcher->deleteLater();
        });
        watcher->setFuture(future);
    }
public:
    ChartData chartData_;
    BackendController(std::unique_ptr<DataLoader<Sample>>&& dataLoader, std::unique_ptr<Filter<Sample>>&& filter) : backend_(std::make_unique<Backend>(std::move(dataLoader), std::move(filter))) {}

    Q_INVOKABLE void loadData() {
        call(QtConcurrent::run(backend_.get(), &Backend::loadData), [this]() {
            chartData_.updateMinAndMax(backend_->data());
            chartData_.updateSeries(backend_->data());
        });
    }
    Q_INVOKABLE void filterData() {
        call(QtConcurrent::run(backend_.get(), &Backend::filterData), [this](){
            chartData_.updateMinAndMax(backend_->data());
            chartData_.updateSeries(backend_->filteredData());
        });
    }
    Q_INVOKABLE void updateFileName(QString const& fileName) {
        call(QtConcurrent::run(backend_.get(), &Backend::updateFileName, fileName), [](){});
    }
};
