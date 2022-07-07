cmake_minimum_required(VERSION 3.15)
project(QTWorld)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(client)
add_subdirectory(server)