cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14)

project(interpreter)

option(BUILD_UNIT_TESTS "Build unit tests" OFF)

add_subdirectory(src)
if (BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif ()