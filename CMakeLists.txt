cmake_minimum_required(VERSION 3.15)

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
include(cmake/core.cmake)

set(LIBRARY_NAME a)
set(PROJECT_LICENSE "MPL-2.0")
project(lib${LIBRARY_NAME} VERSION 0.1.0 LANGUAGES C
  DESCRIPTION "An algorithm library based on C language"
  HOMEPAGE_URL "https://github.com/tqfx/lib${LIBRARY_NAME}.git"
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

option(ENABLE_VCPKG "Enable vcpkg" OFF)
option(ENABLE_PYTHON "Enable python" ON)
option(ENABLE_DOXYGEN "Enable doxygen" ON)
option(ENABLE_WARNINGS "Enable warnings" OFF)
option(ENABLE_SANITIZE "Enable sanitize" OFF)
option(ENABLE_CPPCHECK "Enable cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_IYWU "Enable include-what-you-use" OFF)
option(ENABLE_IPO "Enable interprocedural optimization" OFF)

find_package(Git)

if(ENABLE_PYTHON)
  find_package(Python)
endif()

if(ENABLE_DOXYGEN)
  find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
endif()

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

if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE GIT_REF
    ERROR_QUIET
  )
endif()

set(${LIBRARY_NAME}_VERSION ${PROJECT_VERSION})
find_library(MATH_LIBRARIES NAMES m)
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.h
  ${CMAKE_CURRENT_LIST_DIR}/src/config.h
)
file(GLOB_RECURSE SOURCES include/*.h src/*.h src/*.c)

add_library(${LIBRARY_NAME} ${SOURCES})
add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})
set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIBRARY_NAME} PROPERTIES C_VISIBILITY_PRESET hidden)
target_compile_options(${LIBRARY_NAME} PRIVATE
  $<$<C_COMPILER_ID:GNU,Clang,AppleClang,IntelLLVM>:-Wall -Wextra -Wpedantic>
  $<$<C_COMPILER_ID:MSVC>:/W4 /sdl> $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>
)
target_compile_definitions(${LIBRARY_NAME}
  PRIVATE $<$<BOOL:${${LIBRARY_NAME}_VERSION}>:${LIBRARY_NAME}_CONFIGS>
  PUBLIC $<$<BOOL:${BUILD_SHARED_LIBS}>:${LIBRARY_NAME}_SHARED>
)
target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(MATH_LIBRARIES OR ANDROID)
  target_link_libraries(${LIBRARY_NAME} PUBLIC m)
endif()

if(ENABLE_IYWU AND INCLUDE_WHAT_YOU_USE)
  set_target_properties(${LIBRARY_NAME} PROPERTIES C_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
endif()

if(ENABLE_CLANG_TIDY AND CLANG_TIDY)
  set_target_properties(${LIBRARY_NAME} PROPERTIES C_CLANG_TIDY "${CLANG_TIDY};--fix")
endif()

if(ENABLE_CPPCHECK AND CPPCHECK)
  set_target_properties(${LIBRARY_NAME} PROPERTIES C_CPPCHECK "${CPPCHECK};--enable=warning,performance")
endif()

if(ENABLE_IPO)
  set_target_properties(${LIBRARY_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION include FILES_MATCHING
  REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
)
install(TARGETS ${LIBRARY_NAME}
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
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION lib/pkgconfig
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.pc
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  @ONLY
)

if(ENABLE_VCPKG)
  if(DEFINED ENV{VCPKG_INSTALLATION_ROOT})
    install(
      DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/
      DESTINATION $ENV{VCPKG_INSTALLATION_ROOT}
    )
  else()
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcpkg DESTINATION share)
  endif()

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/vcpkg/portfile.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/ports/${PROJECT_NAME}/portfile.cmake
    @ONLY
  )
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/vcpkg/vcpkg.json
    ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/ports/${PROJECT_NAME}/vcpkg.json
    @ONLY
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

if(CLANG_FORMAT)
  file(GLOB_RECURSE SOURCES include/*.h src/*.[ch] tests/*.[ch]*)
  add_custom_target(${LIBRARY_NAME}-format # https://clang.llvm.org/docs/ClangFormat.html
    COMMAND ${CLANG_FORMAT} --style=file -i ${SOURCES} --verbose
    COMMENT "Formatting code using ClangFormat"
  )
endif()

if(Python_Interpreter_FOUND)
  add_custom_target(${LIBRARY_NAME}-black # https://black.readthedocs.io/en/stable
    COMMAND ${Python_EXECUTABLE} -m black -S ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Formatting code using black"
  )
  add_custom_target(${LIBRARY_NAME}-wheel # https://setuptools.readthedocs.io/en/stable
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py bdist_wheel --universal
    COMMENT "setup.py bdist_wheel --universal"
  )
  add_custom_target(${LIBRARY_NAME}-cython # https://cython.readthedocs.io/en/stable
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py build_ext --inplace
    COMMENT "setup.py build_ext --inplace"
  )
endif()

if(DOXYGEN_FOUND)
  # Project related configuration options
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)

  # Build related configuration options
  # Configuration options related to warning and progress messages
  set(DOXYGEN_WARN_LOGFILE doxygen.log)

  # Configuration options related to the input files
  set(DOXYGEN_RECURSIVE YES)
  set(DOXYGEN_EXCLUDE_SYMBOLS "__*")

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

  # https://www.doxygen.nl/manual/config.html
  doxygen_add_docs(${LIBRARY_NAME}-doc
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
  )
endif()
