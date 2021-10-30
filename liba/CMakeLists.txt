cmake_minimum_required(VERSION 3.10)

project(a VERSION 1.0.0)
set(TARGET ${PROJECT_NAME})

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()
if(NOT CMAKE_C_STANDARD_REQUIRED)
  set(CMAKE_C_STANDARD_REQUIRED ON)
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

unset(SOURCES)
include_directories(${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCE)
list(APPEND SOURCES ${SOURCE})
include_directories(${CMAKE_CURRENT_LIST_DIR}/poly)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/poly SOURCE)
list(APPEND SOURCES ${SOURCE})
include_directories(${CMAKE_CURRENT_LIST_DIR}/hash)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/hash SOURCE)
list(APPEND SOURCES ${SOURCE})
add_library(${TARGET} ${SOURCES})
unset(SOURCES)

target_include_directories(${TARGET} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(${TARGET} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/poly>
  $<INSTALL_INTERFACE:include/poly>
)
target_include_directories(${TARGET} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/hash>
  $<INSTALL_INTERFACE:include/hash>
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_link_libraries(${TARGET} m)
endif()

foreach(_prefix ${CMAKE_CURRENT_LIST_DIR})
  foreach(_suffix "*.h" "*.hxx" "*.hpp")
    file(GLOB_RECURSE _include ${_prefix}/${_suffix})
    install(FILES ${_include} DESTINATION include)
  endforeach()
endforeach()
install(EXPORT ${TARGET}-targets
  FILE ${TARGET}-config.cmake
  DESTINATION lib/cmake/${TARGET}
)
install(TARGETS ${TARGET}
  EXPORT ${TARGET}-targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
