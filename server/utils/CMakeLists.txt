find_package(OpenSSL COMPONENTS Crypto REQUIRED)
find_package(Poco COMPONENTS JWT)

add_library(utils STATIC poco_request.cpp poco_response.cpp phash.cpp auth_utils.cpp categories_utils.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(utils PRIVATE Poco::JWT nlohmann_json::nlohmann_json OpenSSL::Crypto server::DAL common)
