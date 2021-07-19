project(guiQml LANGUAGES CXX)

#SETTING ICON FOR WINDOWS #######################################################
set(APP_ICON_RESOURCE_WINDOWS "../commonResources/img/icon.rc")

#BUILD FLAGS ####################################################################
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#QT PACKAGE #######################
find_package(Qt5 COMPONENTS Core Quick Concurrent REQUIRED)

#INCLUDE ################################
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

#ADDING SOURCE FILES ############################################################
set(SOURCES
    src/main.cpp
    ${HEADERS}
    resourcesQml.qrc
    ../resources.qrc)

#CREATING EXEC AND LINK IT WITH LIBS AND MANUALLY CREATED SOURCES ###############
add_executable(${PROJECT_NAME} ${SOURCES} ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Quick
    Qt5::Concurrent
    backend
)

target_compile_definitions(${PROJECT_NAME} PUBLIC LOGURU_DEBUG_LOGGING)
