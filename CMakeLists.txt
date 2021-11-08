cmake_minimum_required(VERSION 3.10)

project(liba VERSION 0.2.2)

message(STATUS ${CMAKE_SYSTEM})

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)

include(cmake/check.cmake OPTIONAL)
include(cmake/output.cmake OPTIONAL)
include(cmake/standard.cmake OPTIONAL)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
  include(cmake/sanitizer.cmake OPTIONAL)
endif()

add_subdirectory(liba)
add_subdirectory(test)
