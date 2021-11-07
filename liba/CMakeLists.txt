cmake_minimum_required(VERSION 3.10)

project(a VERSION 0.2.1)

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
add_library(${PROJECT_NAME} ${SOURCES})
unset(SOURCES)

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/poly>
  $<INSTALL_INTERFACE:include/poly>
)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/hash>
  $<INSTALL_INTERFACE:include/hash>
)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_link_libraries(${PROJECT_NAME} m)
endif()

foreach(_prefix ${CMAKE_CURRENT_LIST_DIR})
  foreach(_suffix "*.h" ".hh" "*.hxx" "*.hpp")
    file(GLOB_RECURSE _include ${_prefix}/${_suffix})
    install(FILES ${_include} DESTINATION include)
  endforeach()
endforeach()
install(EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-config.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
if(DOXYGEN_FOUND)
  # Project related configuration options
  set(DOXYGEN_PROJECT_BRIEF "The algorithm library based on C language.")
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  # Build related configuration options
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_EXTRACT_PRIVATE YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  # Configuration options related to warning and progress messages
  # Configuration options related to the input files
  set(DOXYGEN_RECURSIVE YES)
  # Configuration options related to source browsing
  set(DOXYGEN_INLINE_SOURCES YES)
  # Configuration options related to the alphabetical class index
  # Configuration options related to the HTML output
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_USE_MATHJAX YES)
  # Configuration options related to the LaTeX output
  # Configuration options related to the RTF output
  # Configuration options related to the man page output
  # Configuration options related to the XML output
  # Configuration options related to the DOCBOOK output
  # Configuration options for the AutoGen Definitions output
  # Configuration options related to Sqlite3 output
  # Configuration options related to the Perl module output
  # Configuration options related to the preprocessor
  set(DOXYGEN_MACRO_EXPANSION YES)
  set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
  set(DOXYGEN_PREDEFINED
    "__cplusplus"
    "__BEGIN_DECLS:="
    "__END_DECLS:="
    "__NONNULL():="
    "__NONNULL_ALL:="
    "__RESULT_USE_CHECK:="
    "__ALWAYS_INLINE:="
    "__WEAK:="
    "__USED:="
    "__UNUSED:="
    "__ALIGNED():="
    "__PACKED:="
    "__PACKED_STRUCT:="
    "__PACKED_UNION:="
    "__ASM:="
    "__INLINE:="
    "__RESTRICT:="
    "__STATIC_INLINE:="
    "__ATTR_PRINTF():="
  )
  # Configuration options related to external references
  # Configuration options related to the dot tool
  if(Doxygen_dot_FOUND)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_INTERACTIVE_SVG YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  endif()
  doxygen_add_docs(docs_${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR})
endif()
