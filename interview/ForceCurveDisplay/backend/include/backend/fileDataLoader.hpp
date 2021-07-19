#pragma once
#include "dataLoader.hpp"
#include "parser.hpp"
#include <QFile>
#include <QString>
#include "loguru/loguru.hpp"

template <typename DataType>
class FileDataLoader : public DataLoader<DataType> {
    QString fileName_;
    std::unique_ptr<Parser<DataType>> parser_;
public:
    FileDataLoader(QString const& fileName, std::unique_ptr<Parser<DataType>>&& parser) : fileName_(fileName), parser_(std::move(parser)) {}
    void setFileName(QString const& fileName) noexcept {
        fileName_ = fileName;
        fileName_.remove("file:///");
    }
    void loadData() override {
        DLOG_F(INFO, "FileDataLoader::%s", __func__);
        DataLoader<DataType>::data_.clear();
        QFile file(fileName_);
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            int lines = 0;
            QString line;
            while(stream.readLineInto(&line)) {
                ++lines;
            }
            DataLoader<DataType>::data_.reserve(lines);
            DLOG_F(INFO, "FileDataLoader::%s prepering data structure for %d", __func__, lines);
            stream.seek(0);
            while(stream.readLineInto(&line)) {
                DataLoader<DataType>::data_.push_back(parser_->parse(line));
            }
        }
        else
            DLOG_F(ERROR, "FileDataLoader::%s failed to open file, path: %s", __func__, fileName_.toStdString().c_str());
    }
};
