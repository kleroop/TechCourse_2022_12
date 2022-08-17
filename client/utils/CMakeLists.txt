find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(click_catch_overlay)

add_library(client_utils INTERFACE)
add_library(client::utils ALIAS client_utils)

target_link_libraries(client_utils INTERFACE click_catch_overlay)

target_include_directories(client_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})