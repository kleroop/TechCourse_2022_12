cmake_minimum_required(VERSION 3.20)
project(QTWorld)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

include(cmake/utils.cmake)

find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
