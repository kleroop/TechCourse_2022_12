find_package(Poco COMPONENTS Util JWT REQUIRED)

add_library(common STATIC models/auth_model.cpp models/categories_model.cpp)
target_link_libraries(common PUBLIC Poco::Util Poco::JWT nlohmann_json::nlohmann_json)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
