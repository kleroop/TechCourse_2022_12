add_library(confirmation_modal confirmation_modal.cpp confirmation_modal.ui)

target_include_directories(confirmation_modal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(confirmation_modal PRIVATE client::utils)
