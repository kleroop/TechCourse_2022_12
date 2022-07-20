cmake_minimum_required(VERSION 3.15)
project(server)

# moves subproject runtime outputs (shared libs, exes) into the same dir as server executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

find_package(Poco COMPONENTS Net Util JSON REQUIRED)

add_subdirectory(utils)
add_subdirectory(DAL)

add_executable(server main.cpp)
target_link_libraries(server PRIVATE Poco::Net Poco::Util nlohmann_json::nlohmann_json server::DAL)
