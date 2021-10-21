# include(cmake/arm-none-eabi.cmake)
cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0.0)

message(STATUS ${CMAKE_SYSTEM})

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)

include(cmake/output.cmake OPTIONAL)
include(cmake/standard.cmake OPTIONAL)
include(cmake/extension.cmake OPTIONAL)
include(cmake/checkflag.cmake OPTIONAL)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
  include(cmake/sanitizer.cmake OPTIONAL)
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(liba)
add_subdirectory(test)
