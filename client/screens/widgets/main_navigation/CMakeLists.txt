add_subdirectory(main_button)

add_library(main_navigation main_navigation.cpp main_navigation.ui)

target_link_libraries(main_navigation main_button)

target_include_directories(main_navigation PUBLIC .)