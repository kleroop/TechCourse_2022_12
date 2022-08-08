add_subdirectory(button_decorator)

add_library(navigation navigation.cpp navigation.ui)

target_link_libraries(navigation button_decorator)

target_include_directories(navigation PUBLIC .)
