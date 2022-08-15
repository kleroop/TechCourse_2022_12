add_subdirectory(info_arch_dropdown)
add_subdirectory(cat_button)

add_library(info_arch info_arch.cpp info_arch.ui categories.h)

target_link_libraries(info_arch info_arch_dropdown cat_button)

target_include_directories(info_arch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})