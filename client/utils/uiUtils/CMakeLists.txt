add_library(uiUtils uiUtils.h)
target_link_libraries(uiUtils PRIVATE Qt5::Core Qt5::Widgets)
target_include_directories(uiUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
