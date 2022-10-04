include_directories(${client_SOURCE_DIR})
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)
set(ALL_SRCS ${ALL_SRCS} CACHE INTERNAL "description")

enable_testing()

add_executable(categories categories.cc)
target_link_libraries(categories PRIVATE GTest::gtest_main Qt5::Core Qt5::Network
        nlohmann_json::nlohmann_json
        common
        client::api)

add_executable(login_test login.cc)
target_link_libraries(login_test PRIVATE GTest::gtest_main Qt5::Core Qt5::Network
        nlohmann_json::nlohmann_json
        common
        client::api)

include(GoogleTest)
gtest_discover_tests(categories)
gtest_discover_tests(login_test)

windeployqt(login_test)
