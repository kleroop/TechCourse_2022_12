add_library(header header.cpp header.ui)
target_include_directories(header PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(header PRIVATE user_profile)
