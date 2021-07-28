# include(cmake/arm_none_eabi.cmake)
cmake_minimum_required(VERSION 3.10)

project(TEST_LIBA VERSION 0)

set(CMAKE_VERBOSE_MAKEFILE OFF)

include(cmake/check_flag.cmake)

add_subdirectory (liba)
add_subdirectory (test)
