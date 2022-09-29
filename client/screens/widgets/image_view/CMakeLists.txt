add_library(image_view image_view.cpp image_view.ui)

target_link_libraries(image_view common)

target_include_directories(image_view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
