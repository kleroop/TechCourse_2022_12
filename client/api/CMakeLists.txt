find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_library(api STATIC api.cpp)

target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(api PRIVATE Qt5::Core Qt5::Network nlohmann_json::nlohmann_json common utilsClient)
