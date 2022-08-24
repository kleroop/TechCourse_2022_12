cmake_minimum_required(VERSION 3.15)
project(server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(DAL)

add_subdirectory(utils)

find_package(Poco COMPONENTS Net Util JWT REQUIRED)

add_executable(server main.cpp server.cpp handlers/handlers_factory.cpp handlers/root.cpp handlers/shutdown.cpp handlers/not_found.cpp handlers/auth.cpp handlers/categories.cpp)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server PRIVATE Poco::Net Poco::Util Poco::JWT nlohmann_json::nlohmann_json common utils server::DAL)

