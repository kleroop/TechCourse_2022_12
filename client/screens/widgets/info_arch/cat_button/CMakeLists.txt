add_library(cat_button cat_button.cpp cat_button.ui CustomButton.h)

target_link_libraries(cat_button info_arch_dropdown)

target_include_directories(cat_button PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
