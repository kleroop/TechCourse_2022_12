find_package(Qt5 COMPONENTS Widgets Core Network REQUIRED)

add_library(utilsClient STATIC nlohmanQt.cpp)

target_include_directories(utilsClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(utilsClient PRIVATE Qt5::Core Qt5::Widgets Qt5::Network nlohmann_json::nlohmann_json) # todo: delete widget