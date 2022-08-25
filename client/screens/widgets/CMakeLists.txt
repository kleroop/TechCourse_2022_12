link_libraries(Qt5::Widgets Qt5::Core)

add_subdirectory(user_profile)
add_subdirectory(user_login)
add_subdirectory(header)
add_subdirectory(navigation)
add_subdirectory(main_navigation)
add_subdirectory(info_arch)

add_library(client_widgets INTERFACE)
add_library(client::widgets ALIAS client_widgets)
target_link_libraries(client_widgets INTERFACE header user_profile user_login navigation main_navigation info_arch)
