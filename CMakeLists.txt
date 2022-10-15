cmake_minimum_required(VERSION 3.15) # CheckPIESupported

if(POLICY CMP0057) # 3.3
  cmake_policy(SET CMP0057 NEW)
endif() # IN_LIST if()

if(POLICY CMP0063) # 3.3
  cmake_policy(SET CMP0063 NEW)
endif() # <LANG>_VISIBILITY_PRESET

if("${VCPKG_TARGET_TRIPLET}" MATCHES "x86-mingw(.*)")
  include(cmake/mingw32.cmake)
elseif("${VCPKG_TARGET_TRIPLET}" MATCHES "x64-mingw(.*)")
  include(cmake/mingw64.cmake)
endif()

set(PROJECT_LICENSE "MPL-2.0")
project(liba VERSION 0.1.1 LANGUAGES C CXX
  HOMEPAGE_URL "https://github.com/tqfx/liba.git"
  DESCRIPTION "An algorithm library based on C/C++ language"
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Specifies the build type on single-configuration generators." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(NOT "${CMAKE_SYSTEM_NAME}" MATCHES "Generic" AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

include(TestBigEndian)
include(GNUInstallDirs)
include(cmake/core.cmake)
include(cmake/target.cmake)
include(cmake/package.cmake)
include(cmake/standard.cmake)

option(ENABLE_VCPKG "Enable vcpkg" OFF)
option(ENABLE_PYTHON "Enable python" OFF)
option(ENABLE_DOXYGEN "Enable doxygen" OFF)
option(ENABLE_WARNINGS "Enable warnings" OFF)
option(ENABLE_SANITIZE "Enable sanitize" OFF)
option(ENABLE_CPPCHECK "Enable cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_IYWU "Enable include-what-you-use" OFF)
option(ENABLE_PIC "Enable position independent code" OFF)
option(ENABLE_IPO "Enable interprocedural optimization" OFF)

if(ENABLE_WARNINGS)
  include(cmake/warnings.cmake)
endif()

if(ENABLE_SANITIZE)
  include(cmake/sanitize.cmake)
endif()

include(cmake/git.cmake)

if(ENABLE_PYTHON AND CMAKE_VERSION VERSION_GREATER 3.11)
  find_package(Python COMPONENTS Interpreter)
  set(PYTHONINTERP_FOUND ${Python_Interpreter_FOUND})
  set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
elseif(ENABLE_PYTHON) # cmake < 3.12
  find_package(PythonInterp)
endif()

if(ENABLE_DOXYGEN AND CMAKE_VERSION VERSION_GREATER 3.8)
  find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
elseif(ENABLE_DOXYGEN) # cmake < 3.9
  find_package(Doxygen)
endif()

if(ENABLE_IPO AND CMAKE_VERSION VERSION_GREATER 3.8)
  cmake_policy(SET CMP0069 NEW)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ENABLE_IPO)
elseif(ENABLE_IPO) # cmake < 3.9
  set(ENABLE_IPO NO)
endif()

set(A_VERSION ${PROJECT_VERSION})
set(A_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(A_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(A_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(A_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
set(A_SIZEOF_P ${CMAKE_SIZEOF_VOID_P})
find_library(MATH_LIBRARY NAMES m)
test_big_endian(A_BIG_ENDIAN)

if(NOT MATH_LIBRARY AND ANDROID)
  set(MATH_LIBRARY m CACHE STRING "math library" FORCE)
endif()

function(target_library_setting target)
  add_library(${PROJECT_NAME}::${target} ALIAS ${target})
  get_target_property(A_SHARED ${target} POSITION_INDEPENDENT_CODE)
  set_target_properties(${target} PROPERTIES OUTPUT_NAME a
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL A_EXPORTS
  )
  target_compile_definitions(${target} PUBLIC A_CONFIG
    INTERFACE $<$<BOOL:${A_SHARED}>:A_SHARED>
  )
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${target} PUBLIC
    $<$<BOOL:${MATH_LIBRARY}>:${MATH_LIBRARY}>
  )
  set(A_SHARED ${A_SHARED} PARENT_SCOPE)
  target_library_options(${target})
endfunction()

configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.h
  ${CMAKE_CURRENT_BINARY_DIR}/a.config.h
)

file(GLOB_RECURSE SOURCES include/*.h* src/*.[chm]*)
add_library(a ${SOURCES})
target_library_setting(a)
unset(SOURCES)

if(A_SHARED)
  set(SHARED_LIBS a)
  set(A_LIBRARIES a a-static)
  add_library(a-shared ALIAS a)
  add_library(a-static STATIC $<TARGET_OBJECTS:a>)
  target_library_setting(a-static)
else()
  set(SHARED_LIBS a-shared)
  set(A_LIBRARIES a a-shared)
  add_library(a-static ALIAS a)
  add_library(a-shared SHARED $<TARGET_OBJECTS:a>)
  target_library_setting(a-shared)
endif()

if("${CMAKE_STATIC_LIBRARY_SUFFIX}" MATCHES ".lib")
  set_target_properties(${SHARED_LIBS} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
  )
  unset(SHARED_LIBS)
endif()

set(prop "$<TARGET_PROPERTY:a,INTERFACE_COMPILE_DEFINITIONS>")
set(PROJECT_CFLAGS "$<$<BOOL:${prop}>:-D$<JOIN:${prop}, -D>>")
set(PROJECT_LIBRARIES -la)
unset(prop)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/a.config.h DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION include FILES_MATCHING
  REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
)
install(TARGETS ${A_LIBRARIES} EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT ${PROJECT_NAME}-targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
file(GENERATE
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  INPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.pc
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  @ONLY
)

if(ENABLE_VCPKG AND GIT_COMMIT)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcpkg DESTINATION ${CMAKE_INSTALL_DATADIR})
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
  file(GLOB_RECURSE SOURCES ffi/*.[chm]* include/*.h* src/*.[chm]* test/*.[chm]*)
  list(FILTER SOURCES INCLUDE REGEX ".+(c|h|cc|hh|cxx|hxx|cpp|hpp|mpp)$")
  list(FILTER SOURCES EXCLUDE REGEX ".+python.+")
  add_custom_target(a-format # https://clang.llvm.org/docs/ClangFormat.html
    ${CLANG_FORMAT} --style=file -i ${SOURCES} --verbose
    COMMENT "Formatting code using ClangFormat"
  )
  unset(SOURCES)
endif()

if(PYTHONINTERP_FOUND)
  file(GLOB BYPRODUCT ${PROJECT_NAME}.*py*)
  file(GLOB_RECURSE SOURCES ffi/python/src/*.[ch]*)
  add_custom_target(a-py-build ALL # https://cython.readthedocs.io/en/stable
    ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py build_ext --inplace
    COMMENT "setup.py build_ext --inplace"
    BYPRODUCTS ${BYPRODUCT} ${SOURCES}
  )
  add_custom_target(a-py-setup # https://pip.readthedocs.io/en/stable
    ${PYTHON_EXECUTABLE} -m pip install -r ${CMAKE_CURRENT_LIST_DIR}/requirements.txt
    COMMENT "pip install -r requirements.txt"
  )
  add_custom_target(a-black # https://black.readthedocs.io/en/stable
    ${PYTHON_EXECUTABLE} -m black -S ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Formatting code using black"
  )
  unset(BYPRODUCT)
  unset(SOURCES)
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
    "__cplusplus=201103L"
    "__STDC_HOSTED__=1"
    "A_STATIC:=static"
    "A_INTERN:="
    "A_PUBLIC:="
    "A_HIDDEN:="
  )

  # Configuration options related to external references
  # Configuration options related to the dot tool
  if(Doxygen_dot_FOUND)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_INTERACTIVE_SVG YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  endif()

  if(CMAKE_VERSION VERSION_LESS 3.9)
    include(cmake/doxygen.cmake)
  endif()

  # https://www.doxygen.nl/manual/config.html
  doxygen_add_docs(a-doxygen
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
  )
endif()
