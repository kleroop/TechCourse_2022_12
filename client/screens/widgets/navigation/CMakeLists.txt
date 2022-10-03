add_subdirectory(button_decorator)

add_library(navigation navigation.cpp navigation.ui)

target_link_libraries(navigation button_decorator common client::api nlohmann_json::nlohmann_json)

target_include_directories(navigation PUBLIC .)
