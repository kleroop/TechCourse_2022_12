add_library(teams teams.cpp teams.ui)

target_link_libraries(teams PUBLIC common client::api nlohmann_json::nlohmann_json client::utils image_view)

target_include_directories(teams PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})