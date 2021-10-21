cmake_minimum_required(VERSION 3.10)

project(a VERSION 1.0.0)
set(TARGET_NAME ${PROJECT_NAME})

include(filelist.cmake)
list(APPEND SOURCES ${SOURCE_LIBA})

add_library(${TARGET_NAME} ${SOURCES})
target_include_directories(${TARGET_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(${TARGET_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/poly>
  $<INSTALL_INTERFACE:include/poly>
)
target_include_directories(${TARGET_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hash>
  $<INSTALL_INTERFACE:include/hash>
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  target_link_libraries(${TARGET_NAME} m)

endif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

foreach(_prefix ${CMAKE_CURRENT_SOURCE_DIR})
  foreach(_suffix "*.h" "*.hxx" "*.hpp")
    file(GLOB_RECURSE _include ${_prefix}/${_suffix})
    install(FILES ${_include} DESTINATION include)
  endforeach(_suffix "*.h" "*.hxx" "*.hpp")
endforeach(_prefix ${CMAKE_CURRENT_SOURCE_DIR})
install(EXPORT ${TARGET_NAME}-targets
  FILE ${TARGET_NAME}-config.cmake
  DESTINATION lib/cmake/${TARGET_NAME}
)
install(TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
