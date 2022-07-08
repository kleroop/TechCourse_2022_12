cmake_minimum_required(VERSION 3.15)
project(client)
# Auto compile ui design files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_OPTIO)
include(../cmake/utils.cmake)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Network)

add_executable(client WIN32 main.cpp main_window.cpp main_window.ui LoginBackgroundImg.qrc)
target_link_libraries(client PRIVATE Qt5::Widgets)
target_link_libraries(client PRIVATE Qt5::Core)
#target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE Qt5::Network)

windeployqt(client)
