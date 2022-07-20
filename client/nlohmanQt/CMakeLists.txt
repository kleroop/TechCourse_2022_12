find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_library(nlohmanQt STATIC nlohmanQt.cpp)

target_link_libraries(nlohmanQt PRIVATE Qt5::Core Qt5::Network nlohmann_json::nlohmann_json)

target_include_directories(nlohmanQt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
