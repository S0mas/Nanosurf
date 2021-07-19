cmake_minimum_required(VERSION 3.5)

project(LogsFiltering LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
  main.cpp
  filter.h
  logger.h
  log_item.h
  proxy_model.h
)


add_executable(LogsFiltering
  ${PROJECT_SOURCES}
)

target_link_libraries(LogsFiltering PRIVATE Qt5::Widgets)
