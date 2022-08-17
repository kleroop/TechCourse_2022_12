add_library(add_cat_window add_cat_window.cpp add_cat_window.ui)
target_include_directories(add_cat_window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(add_cat_window PUBLIC client::utils)