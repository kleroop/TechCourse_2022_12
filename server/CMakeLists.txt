cmake_minimum_required(VERSION 3.15)
project(server)
find_package(Poco COMPONENTS Net Util JSON REQUIRED)

add_executable(server main.cpp server.cpp handlers/handlers_factory.cpp handlers/handlers_factory.h handlers/root.cpp handlers/root.h handlers/shutdown.cpp handlers/shutdown.h ../common/utils/poco_response.cpp ../common/utils/poco_response.h)
target_link_libraries(server PRIVATE Poco::Net Poco::Util nlohmann_json::nlohmann_json)
