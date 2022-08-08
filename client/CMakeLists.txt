cmake_minimum_required(VERSION 3.15)
project(client)
# Auto compile ui design files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

add_subdirectory(utils)
add_subdirectory(api)
add_subdirectory(screens/widgets)


add_executable(client WIN32 main.cpp main_window.cpp main_window.ui
        QResources.qrc
        screens/login.cpp screens/login.ui
        screens/home.cpp screens/home.ui)
target_link_libraries(client PRIVATE
        Qt5::Widgets Qt5::Core Qt5::Network
        nlohmann_json::nlohmann_json
        common
        client::utils client::api client::widgets)

windeployqt(client)
