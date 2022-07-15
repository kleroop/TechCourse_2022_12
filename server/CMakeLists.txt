cmake_minimum_required(VERSION 3.15)
project(server)
find_package(Poco COMPONENTS Net Util JWT REQUIRED)

add_executable(server main.cpp server.cpp handlers/handlers_factory.cpp handlers/handlers_factory.h handlers/root.cpp handlers/root.h handlers/shutdown.cpp handlers/shutdown.h utils/poco_response.cpp utils/poco_response.h handlers/not_found.cpp handlers/not_found.h handlers/handler_includes.h handlers/auth.cpp handlers/auth.h ../common/models/serializable.cpp ../common/models/serializable.h ../common/models/api/auth_model.cpp ../common/models/api/auth_model.h ../common/models/serializable.cpp utils/poco_request.cpp utils/poco_request.h)
target_link_libraries(server PRIVATE Poco::Net Poco::Util Poco::JWT nlohmann_json::nlohmann_json)
