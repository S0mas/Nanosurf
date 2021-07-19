project(backend LANGUAGES CXX)

#BUILD FLAGS ####################################################################
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#FINDING QT PACKAGE #######################
find_package(Qt5 COMPONENTS Core Quick Concurrent Charts REQUIRED)

#PREPARING HEADER FILES ################################
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_library(${PROJECT_NAME} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Concurrent
    Qt5::Charts
    Qt5::Quick
    loguru
)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
