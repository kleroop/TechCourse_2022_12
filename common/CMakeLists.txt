find_package(Poco COMPONENTS Util JWT REQUIRED)

add_library(common STATIC models/api/auth_model.cpp)
target_link_libraries(common PRIVATE Poco::Util Poco::JWT)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
