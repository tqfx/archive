if(${CMAKE_TOOLCHAIN_FILE})
  include(${CMAKE_TOOLCHAIN_FILE})
endif()

cmake_minimum_required(VERSION 3.10)

project(a VERSION 0.2.6)

include(cmake/check.cmake OPTIONAL)
include(cmake/output.cmake OPTIONAL)
include(cmake/standard.cmake OPTIONAL)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
elseif("${CMAKE_BUILD_TYPE}" MATCHES "[Dd]ebug")
  if(UNIX)
    include(cmake/sanitizer.cmake OPTIONAL)
  endif()
endif()

unset(SOURCES CACHE)
aux_source_directory(src SOURCES)

# crc
aux_source_directory(src/crc SOURCES)

# poly
aux_source_directory(src/poly SOURCES)

# hash
aux_source_directory(src/hash SOURCES)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/src/crc
  ${CMAKE_CURRENT_LIST_DIR}/src/poly
  ${CMAKE_CURRENT_LIST_DIR}/src/hash
  )
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/crc>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/poly>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/hash>
  $<INSTALL_INTERFACE:include>
  $<INSTALL_INTERFACE:include/crc>
  $<INSTALL_INTERFACE:include/poly>
  $<INSTALL_INTERFACE:include/hash>
  )

if(${CMAKE_C_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_C_COMPILER_ID} MATCHES "(Apple)?[Cc]lang" OR
  ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "(Apple)?[Cc]lang")
  target_link_libraries(${PROJECT_NAME} m)
endif()

option(ENABLE_TEST_LIBA "Enable building tests" OFF)
if(ENABLE_TEST_LIBA)
  enable_testing()
  add_subdirectory(test)
endif()

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-target
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(EXPORT ${PROJECT_NAME}-target
  FILE ${PROJECT_NAME}-config.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
  )
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION include FILES_MATCHING
  REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
  )

# https://www.doxygen.nl/manual/config.html
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
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
  doxygen_add_docs(doc_${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
    )
endif()

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_LIST_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_LIST_DIR}/README.md)
set(CPACK_SOURCE_IGNORE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/.git
  ${CMAKE_CURRENT_LIST_DIR}/.vscode
  ${CMAKE_CURRENT_LIST_DIR}/.github
  ${CMAKE_CURRENT_LIST_DIR}/.gitignore
  ${CMAKE_CURRENT_LIST_DIR}/.gitmodules
  ${CMAKE_CURRENT_LIST_DIR}/.clang-format
  ${CMAKE_CURRENT_LIST_DIR}/.gitattributes
  ${CMAKE_CURRENT_LIST_DIR}/build
  )
include(CPack)
