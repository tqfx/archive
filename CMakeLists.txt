# include(cmake/cmake-arm-none-eabi.cmake)
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(TEST_CA VERSION 0)

set(CMAKE_VERBOSE_MAKEFILE OFF)

include(cmake/cmake-flags.cmake)

add_subdirectory (ca)
add_subdirectory (test)
