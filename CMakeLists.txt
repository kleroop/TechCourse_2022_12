cmake_minimum_required(VERSION 3.15)
project(QTWorld)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

find_package(nlohmann_json CONFIG REQUIRED)

include(client/client.cmake)
include(server/server.cmake)
