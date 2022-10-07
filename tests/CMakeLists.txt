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

add_executable(dal_test dal.cc)
target_link_libraries(dal_test PRIVATE utils DAL GTest::gtest_main)
add_custom_command(TARGET dal_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:DAL>
        $<TARGET_FILE_DIR:dal_test>)

include(GoogleTest)
gtest_discover_tests(categories)
gtest_discover_tests(login_test)
gtest_discover_tests(dal_test)


windeployqt(login_test)
