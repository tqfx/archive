# include(cmake/arm_none_eabi.cmake)
cmake_minimum_required(VERSION 3.10)

project(TEST_LIBA VERSION 1.0.0)

message(STATUS ${CMAKE_SYSTEM})

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

include(cmake/CheckFlag.cmake)

add_subdirectory (liba)
add_subdirectory (test)
