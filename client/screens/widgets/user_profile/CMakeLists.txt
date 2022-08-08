add_subdirectory(user_dropdown)

add_library(user_profile user_profile.cpp user_profile.ui)

target_link_libraries(user_profile user_dropdown)

target_include_directories(user_profile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
