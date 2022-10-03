include_directories(${client_SOURCE_DIR})

find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)
set(ALL_SRCS ${ALL_SRCS} CACHE INTERNAL "description")

enable_testing()

add_executable(hello_test hello_test.cc)
target_link_libraries(hello_test GTest::gtest_main)

add_executable(login_test login.cc)
target_link_libraries(login_test PRIVATE GTest::gtest_main Qt5::Core Qt5::Network
        nlohmann_json::nlohmann_json
        common
        client::api)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(login_test)

windeployqt(login_test)
