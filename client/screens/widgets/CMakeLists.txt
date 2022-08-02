link_libraries(Qt5::Widgets Qt5::Core)

add_subdirectory(header EXCLUDE_FROM_ALL)
add_subdirectory(user_profile EXCLUDE_FROM_ALL)
add_subdirectory(user_login)

add_library(client_widgets INTERFACE)
add_library(client::widgets ALIAS client_widgets)
target_link_libraries(client_widgets INTERFACE header user_profile user_login)
