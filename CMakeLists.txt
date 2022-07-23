cmake_minimum_required(VERSION 3.15)

set(PROJECT_LICENSE "MPL-2.0")
project(liba VERSION 0.1.0 LANGUAGES C CXX
  DESCRIPTION "An algorithm library based on C/C++ language"
  HOMEPAGE_URL "https://github.com/tqfx/liba.git"
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Specifies the build type on single-configuration generators." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND NOT "${CMAKE_SYSTEM_NAME}" MATCHES "Generic")
  include(CTest)
endif()

include(cmake/core.cmake)
include(cmake/target.cmake)
include(cmake/package.cmake)
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

if(ENABLE_WARNINGS)
  include(cmake/warnings.cmake)
endif()

if(ENABLE_SANITIZE)
  include(cmake/sanitize.cmake)
endif()

find_package(Git)

if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE GIT_REF
    ERROR_QUIET
  )
endif()

if(ENABLE_PYTHON)
  find_package(Python)
endif()

if(ENABLE_DOXYGEN)
  find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
endif()

if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ENABLE_IPO)
endif()

find_library(MATH_LIBRARY NAMES m)

set(A_VERSION ${PROJECT_VERSION})
set(A_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(A_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(A_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(A_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})

function(target_library_setting target)
  add_library(${PROJECT_NAME}::${target} ALIAS ${target})
  set_target_properties(${target} PROPERTIES DEFINE_SYMBOL A_EXPORTS)
  get_target_property(A_SHARED ${target} POSITION_INDEPENDENT_CODE)
  set(A_SHARED ${A_SHARED} PARENT_SCOPE)
  target_compile_definitions(${target}
    PRIVATE $<$<BOOL:${A_VERSION}>:A_CONFIG>
    INTERFACE $<$<BOOL:${A_SHARED}>:A_SHARED>
  )
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${target} PUBLIC
    $<$<OR:$<BOOL:${MATH_LIBRARY}>,$<BOOL:${ANDROID}>>:m>
  )
  target_library_options(${target})
endfunction()

configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.h
  ${CMAKE_CURRENT_LIST_DIR}/src/config.h
)
file(GLOB_RECURSE SOURCES include/*.h src/*.[ch])

add_library(a ${SOURCES})
target_library_setting(a)

if(A_SHARED)
  add_library(a-static STATIC EXCLUDE_FROM_ALL ${SOURCES})
  set_target_properties(a-static PROPERTIES OUTPUT_NAME a)
  target_library_setting(a-static)
else()
  add_library(a-shared SHARED EXCLUDE_FROM_ALL ${SOURCES})
  set_target_properties(a-shared PROPERTIES OUTPUT_NAME a)
  target_library_setting(a-shared)
endif()

configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.hpp
  ${CMAKE_CURRENT_LIST_DIR}/src/config.hpp
)
file(GLOB_RECURSE SOURCES include/*.hpp src/*.[chm]pp)

add_library(aa ${SOURCES})
target_library_setting(aa)

if(A_SHARED)
  add_library(aa-static STATIC EXCLUDE_FROM_ALL ${SOURCES})
  set_target_properties(aa-static PROPERTIES OUTPUT_NAME aa)
  target_library_setting(aa-static)
else()
  add_library(aa-shared SHARED EXCLUDE_FROM_ALL ${SOURCES})
  set_target_properties(aa-shared PROPERTIES OUTPUT_NAME aa)
  target_library_setting(aa-shared)
endif()

set_target_properties(a aa PROPERTIES
  VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION include FILES_MATCHING
  REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
)
install(TARGETS a aa EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(EXPORT ${PROJECT_NAME}-targets
  DESTINATION lib/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
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

if(ENABLE_VCPKG AND GIT_REF)
  if(DEFINED ENV{VCPKG_INSTALLATION_ROOT})
    get_filename_component(VCPKG_INSTALLATION_ROOT "$ENV{VCPKG_INSTALLATION_ROOT}/." DIRECTORY)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/ DESTINATION ${VCPKG_INSTALLATION_ROOT})
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

if(EXISTS ffi)
  add_subdirectory(ffi)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(test)
endif()

package_cpack(${CMAKE_CURRENT_LIST_DIR})

if(CLANG_FORMAT)
  file(GLOB_RECURSE SOURCES include/*.h* src/*.[chm]* test/*.[chm]*)
  add_custom_target(a-format # https://clang.llvm.org/docs/ClangFormat.html
    COMMAND ${CLANG_FORMAT} --style=file -i ${SOURCES} --verbose
    COMMENT "Formatting code using ClangFormat"
  )
endif()

if(Python_Interpreter_FOUND)
  add_custom_target(a-black # https://black.readthedocs.io/en/stable
    COMMAND ${Python_EXECUTABLE} -m black -S ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Formatting code using black"
  )
  add_custom_target(a-wheel # https://setuptools.readthedocs.io/en/stable
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py bdist_wheel --universal
    COMMENT "setup.py bdist_wheel --universal"
  )
  add_custom_target(a-cython # https://cython.readthedocs.io/en/stable
    COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py build_ext --inplace
    COMMENT "setup.py build_ext --inplace"
  )
endif()

if(DOXYGEN_FOUND)
  # Project related configuration options
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)

  # Build related configuration options
  # Configuration options related to warning and progress messages
  set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
  set(DOXYGEN_WARN_NO_PARAMDOC YES)
  set(DOXYGEN_WARN_LOGFILE doc.log)

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
    "__STDC_HOSTED__=1"
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
  doxygen_add_docs(a-doxygen
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
  )
endif()
