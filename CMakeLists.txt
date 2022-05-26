cmake_minimum_required(VERSION 3.10)

if("${VCPKG_TARGET_TRIPLET}" MATCHES "x86-mingw(.*)")
  include(cmake/mingw32.cmake)
elseif("${VCPKG_TARGET_TRIPLET}" MATCHES "x64-mingw(.*)")
  include(cmake/mingw64.cmake)
endif()
find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
find_program(CLANG_FORMAT clang-format)
find_program(CLANG_TIDY clang-tidy)
find_program(CPPCHECK cppcheck)
find_program(CPPLINT cpplint)
find_program(BLACK black)
include(cmake/core.cmake)
set(DEFAULT_NAME a)

project(lib${DEFAULT_NAME} VERSION 0.1.0 LANGUAGES C
  DESCRIPTION "An algorithm library based on C language."
  HOMEPAGE_URL "https://github.com/tqfx/lib${DEFAULT_NAME}.git"
  )

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Specifies the build type on single-configuration generators." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND NOT "${CMAKE_SYSTEM_NAME}" MATCHES "Generic")
  include(CTest)
endif()
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  enable_language(CXX OPTIONAL)
endif()
include(cmake/standard.cmake)

option(ENABLE_WARNINGS "Enable warnings" OFF)
option(ENABLE_SANITIZE "Enable sanitize" OFF)
option(ENABLE_CPPCHECK "Enable cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_IYWU "Enable include-what-you-use" OFF)
option(ENABLE_IPO "Enable interprocedural optimization" OFF)

if(ENABLE_WARNINGS)
  include(cmake/warnings.cmake)
endif()
if(ENABLE_SANITIZE)
  include(cmake/sanitize.cmake)
endif()
if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ENABLE_IPO)
endif()

set(${DEFAULT_NAME}_VERSION ${PROJECT_VERSION})
find_library(MATH_LIBRARIES NAMES m)
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.h.in
  ${CMAKE_CURRENT_LIST_DIR}/src/config.h
  )
file(GLOB_RECURSE SOURCES include/*.h src/*.h src/*.c)

add_library(${DEFAULT_NAME} ${SOURCES})
add_library(${PROJECT_NAME}::${DEFAULT_NAME} ALIAS ${DEFAULT_NAME})
set_target_properties(${DEFAULT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${DEFAULT_NAME} PROPERTIES C_VISIBILITY_PRESET hidden)
if(ENABLE_IYWU AND INCLUDE_WHAT_YOU_USE)
  set_target_properties(${DEFAULT_NAME} PROPERTIES C_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
endif()
if(ENABLE_CLANG_TIDY AND CLANG_TIDY)
  set_target_properties(${DEFAULT_NAME} PROPERTIES C_CLANG_TIDY "${CLANG_TIDY};--fix")
endif()
if(ENABLE_CPPCHECK AND CPPCHECK)
  set_target_properties(${DEFAULT_NAME} PROPERTIES C_CPPCHECK "${CPPCHECK};--enable=warning,performance")
endif()
if(ENABLE_IPO)
  set_target_properties(${DEFAULT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
endif()
target_compile_options(${DEFAULT_NAME} PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang,IntelLLVM>:-Wall -Wextra -Wpedantic>
  $<$<C_COMPILER_ID:MSVC>:/W4 /sdl> $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
  )
target_compile_definitions(${DEFAULT_NAME}
  PRIVATE $<$<BOOL:${${DEFAULT_NAME}_VERSION}>:${DEFAULT_NAME}_CONFIGS>
  PUBLIC $<$<BOOL:${BUILD_SHARED_LIBS}>:${DEFAULT_NAME}_SHARED>
  )
target_include_directories(${DEFAULT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )
if(MATH_LIBRARIES OR ANDROID)
  target_link_libraries(${DEFAULT_NAME} PUBLIC m)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

if(CLANG_FORMAT)
  file(GLOB_RECURSE SOURCE include/*.h src/*.[ch] tests/*.[ch]*)
  # https://clang.llvm.org/docs/ClangFormat.html
  add_custom_target(${DEFAULT_NAME}-format
    COMMAND ${CLANG_FORMAT} -style=file -i ${SOURCE} --verbose
    )
endif()
if(BLACK)
  # https://black.readthedocs.io/en/stable
  add_custom_target(${DEFAULT_NAME}-black
    COMMAND ${BLACK} -S ${CMAKE_CURRENT_LIST_DIR}
    )
endif()

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION include FILES_MATCHING
  REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
  )
install(TARGETS ${DEFAULT_NAME}
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
  )
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
  )
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION lib/pkgconfig
  )
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  )
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  @ONLY
  )

# https://www.doxygen.nl/manual/config.html
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if(DOXYGEN_FOUND)
  # Project related configuration options
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  # Build related configuration options
  # Configuration options related to warning and progress messages
  # Configuration options related to the input files
  set(DOXYGEN_RECURSIVE YES)
  # Configuration options related to source browsing
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
    "__STDC_VERSION__=201112L"
    "__cplusplus=201703L"
    "A_RESTRICT:="
    "A_INLINE:="
    "A_PUBLIC:="
    "A_HIDDEN:="
    "A_ASM:="
    )
  # Configuration options related to external references
  # Configuration options related to the dot tool
  if(Doxygen_dot_FOUND)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_INTERACTIVE_SVG YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  endif()
  doxygen_add_docs(${DEFAULT_NAME}-doc
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
    )
endif()

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_LIST_DIR}/LICENSE.txt)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_LIST_DIR}/README.md)
set(CPACK_SOURCE_IGNORE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/.git
  ${CMAKE_CURRENT_LIST_DIR}/.vscode
  ${CMAKE_CURRENT_LIST_DIR}/.github
  ${CMAKE_CURRENT_LIST_DIR}/.gitignore
  ${CMAKE_CURRENT_LIST_DIR}/.gitmodules
  ${CMAKE_CURRENT_LIST_DIR}/.gitattributes
  ${CMAKE_CURRENT_LIST_DIR}/build
  ${CMAKE_CURRENT_LIST_DIR}/html
  )
include(CPack)
