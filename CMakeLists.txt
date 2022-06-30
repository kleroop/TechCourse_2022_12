cmake_minimum_required(VERSION 3.15)
project(QTWorld)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

# Auto compile ui design files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

include(cmake/utils.cmake)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(QTWorld WIN32 main.cpp main_window.cpp main_window.ui)
target_link_libraries(QTWorld PRIVATE Qt5::Widgets)

windeployqt(QTWorld)
