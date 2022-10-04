cmake_minimum_required(VERSION 3.20)
project(QTWorld)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#[[ todo: use cppunit
include(FetchContent)
FetchContent_Declare(
        cunit
        GIT_REPOSITORY https://gitlab.com/cunity/cunit.git
)

FetchContent_MakeAvailable(cunit)
]]

# Global compilation options
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    add_compile_options(-W3 -WX)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()

include(cmake/utils.cmake)

find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
