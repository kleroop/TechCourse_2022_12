find_package(OpenSSL COMPONENTS Crypto REQUIRED)

add_library(utils STATIC phash.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(utils PRIVATE nlohmann_json::nlohmann_json OpenSSL::Crypto)
