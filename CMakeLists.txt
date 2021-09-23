# include(cmake/arm-none-eabi.cmake)
cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0.0)

message(STATUS ${CMAKE_SYSTEM})

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

include(cmake/check-flag.cmake OPTIONAL)

add_subdirectory(liba)
add_subdirectory(test)
