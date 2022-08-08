add_subdirectory(hover)

add_library(button_decorator buttondecorator.cpp buttondecorator.ui)

target_link_libraries(button_decorator hover)

target_include_directories(button_decorator PUBLIC .)
