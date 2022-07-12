cmake_minimum_required(VERSION 3.15)
project(client)
# Auto compile ui design files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(client WIN32 MACOSX_BUNDLE main.cpp main_window.cpp main_window.ui)
target_link_libraries(client PRIVATE Qt5::Widgets Qt5::Core nlohmann_json::nlohmann_json)

windeployqt(client)
