add_library(client_api api.cpp)
target_include_directories(client_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(client_api PRIVATE common Qt5::Core Qt5::Network nlohmann_json::nlohmann_json)
add_library(client::api ALIAS client_api)
