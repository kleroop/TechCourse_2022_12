add_library(teams teams.cpp teams.ui)

target_link_libraries(teams PRIVATE common client::api nlohmann_json::nlohmann_json client::utils confirmation_modal)

target_include_directories(teams PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
