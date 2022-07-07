cmake_minimum_required(VERSION 3.15)
project(server)
find_package(Poco COMPONENTS Net Util JSON REQUIRED)

add_executable(server main.cpp)
target_link_libraries(server PRIVATE Poco::Net Poco::Util nlohmann_json::nlohmann_json)
