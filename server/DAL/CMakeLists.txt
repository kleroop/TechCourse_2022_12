cmake_minimum_required(VERSION 3.15)
project(server)
find_package(Poco COMPONENTS DataPostgreSQL REQUIRED)
find_package(PostgreSQL REQUIRED)
# fixme: this is a temporary solution
add_library(PostgreSQL::client ALIAS PostgreSQL::PostgreSQL)

add_library(DAL SHARED DAL.cpp)
include(GenerateExportHeader)
generate_export_header(DAL)

target_include_directories(DAL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(DAL PRIVATE Poco::DataPostgreSQL)
add_library(server::DAL ALIAS DAL)

add_executable(DAL_populate DAL_populate.cpp)
target_link_libraries(DAL_populate PRIVATE utils DAL)
