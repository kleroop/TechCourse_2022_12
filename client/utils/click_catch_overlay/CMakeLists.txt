add_library(click_catch_overlay click_catch_overlay.cpp click_catch_overlay.ui)
target_link_libraries(click_catch_overlay PRIVATE Qt5::Core Qt5::Widgets)
target_include_directories(click_catch_overlay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
