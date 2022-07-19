add_library(utils STATIC poco_request.cpp poco_response.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
