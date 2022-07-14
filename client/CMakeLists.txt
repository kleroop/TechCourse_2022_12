cmake_minimum_required(VERSION 3.15)
project(client)
# Auto compile ui design files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

include(../cmake/utils.cmake)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(client WIN32 main.cpp main_window.cpp main_window.ui ../common/models/serializable.cpp ../common/models/serializable.h ../common/models/api/auth_model.cpp ../common/models/api/auth_model.h ../common/models/serializable.cpp)
target_link_libraries(client PRIVATE Qt5::Widgets Qt5::Core nlohmann_json::nlohmann_json)

windeployqt(client)
