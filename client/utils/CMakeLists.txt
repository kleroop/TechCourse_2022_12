find_package(Qt5 COMPONENTS Widgets Core Network REQUIRED)
add_library(client_utils)
target_include_directories(client_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(client::utils ALIAS client_utils)
