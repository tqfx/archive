cmake_minimum_required(VERSION 3.15) # CheckPIESupported

if(POLICY CMP0057) # 3.3
  cmake_policy(SET CMP0057 NEW)
endif() # IN_LIST if()

if(POLICY CMP0063) # 3.3
  cmake_policy(SET CMP0063 NEW)
endif() # <LANG>_VISIBILITY_PRESET

if(POLICY CMP0091) # 3.15
  cmake_policy(SET CMP0091 NEW)
endif() # CMAKE_MSVC_RUNTIME_LIBRARY

if(VCPKG_TARGET_TRIPLET MATCHES "x86-mingw(.*)")
  include(cmake/mingw32.cmake)
elseif(VCPKG_TARGET_TRIPLET MATCHES "x64-mingw(.*)")
  include(cmake/mingw64.cmake)
endif()

project(liba VERSION 0.1.1 LANGUAGES C # 3.12
  DESCRIPTION "An algorithm library based on C/C++ language"
  HOMEPAGE_URL "https://github.com/tqfx/liba.git"
)

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
option(ENABLE_PKGCONFIG "Enable pkgconfig" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_IYWU "Enable include-what-you-use" OFF)
option(ENABLE_PIC "Enable position independent code" OFF)
option(ENABLE_IPO "Enable interprocedural optimization" OFF)

if(TARGET_SUPPORTS_SHARED_LIBS AND PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif()

if(ENABLE_WARNINGS)
  include(cmake/warnings.cmake)
endif()

if(ENABLE_SANITIZE)
  include(cmake/sanitize.cmake)
endif()

include(cmake/check.cmake)
include(cmake/git.cmake)

# https://cmake.org/cmake/help/latest/module/FindPython.html
if(ENABLE_PYTHON AND CMAKE_VERSION VERSION_GREATER 3.12)
  find_package(Python COMPONENTS Interpreter)
  set(PYTHONINTERP_FOUND ${Python_Interpreter_FOUND})
  set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
elseif(ENABLE_PYTHON) # cmake < 3.12
  find_package(PythonInterp)
endif()

# https://cmake.org/cmake/help/latest/module/FindDoxygen.html
if(ENABLE_DOXYGEN AND CMAKE_VERSION VERSION_GREATER 3.9)
  find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
elseif(ENABLE_DOXYGEN) # cmake < 3.9
  find_package(Doxygen)
endif()

# https://cmake.org/cmake/help/latest/module/CheckIPOSupported.html
if(ENABLE_IPO AND CMAKE_VERSION VERSION_GREATER 3.9)
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

function(target_library_setting target)
  add_library(${PROJECT_NAME}::${target} ALIAS ${target})
  set_target_properties(${target} PROPERTIES
    POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL A_EXPORTS
  )
  target_compile_definitions(${target} PRIVATE A_EXPORTS)
  target_compile_definitions(${target} PUBLIC A_CONFIG)
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${target} PUBLIC
    $<$<BOOL:${MATH_LIBRARY}>:${MATH_LIBRARY}>
  )
  target_library_options(${target})
endfunction()

configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.h
  ${CMAKE_CURRENT_BINARY_DIR}/a.config.h
)

if(CXX IN_LIST ENABLED_LANGUAGES)
  file(GLOB_RECURSE SOURCES include/*.h* src/*.[chm]*)
else()
  file(GLOB_RECURSE SOURCES include/*.h src/*.[ch])
endif()

if(ENABLE_SANITIZE)
  add_library(a-san STATIC ${SOURCES})
  target_compile_sanitize(a-san)
  target_library_setting(a-san)
endif()

add_library(a ${SOURCES})
target_library_setting(a)
set(A_LIBRARIES a)
unset(SOURCES)

if(TARGET_SUPPORTS_SHARED_LIBS)
  if(NOT BUILD_SHARED_LIBS)
    set(A_SHARED_LIB liba)
    set(A_STATIC_LIB a)
    set(module SHARED)
  else()
    set(A_STATIC_LIB liba)
    set(A_SHARED_LIB a)
    set(module STATIC)
  endif()

  list(APPEND A_LIBRARIES liba)
  add_library(liba ${module} $<TARGET_OBJECTS:a>)
  set_target_properties(${A_LIBRARIES} PROPERTIES OUTPUT_NAME a)
  target_compile_definitions(${A_SHARED_LIB} INTERFACE A_IMPORTS)
  target_library_setting(liba)
  unset(module)

  if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
    set_target_properties(${A_SHARED_LIB} PROPERTIES
      OUTPUT_NAME ${PROJECT_NAME}
    )
  endif()
endif()

get_target_property(prop a INTERFACE_COMPILE_DEFINITIONS)
set(PROJECT_CFLAGS "$<$<BOOL:${prop}>:-D$<JOIN:${prop}, -D>>")
get_target_property(prop a INTERFACE_LINK_LIBRARIES)
set(PROJECT_LIBRARIES "-l$<JOIN:a;${prop}, -l>")
set(PROJECT_LICENSE MPL-2.0)
unset(prop)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/a.config.h DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION include FILES_MATCHING REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
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

if(ENABLE_PKGCONFIG)
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
endif()

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

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/ffi AND TARGET_SUPPORTS_SHARED_LIBS)
  add_subdirectory(ffi)
endif()

if(TARGET_SUPPORTS_SHARED_LIBS AND PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
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
  file(GLOB BYPRODUCT ${PROJECT_NAME}.*)
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

if(DOXYGEN_FOUND AND CMAKE_VERSION VERSION_GREATER 3.9)
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
  set(DOXYGEN_MATHJAX_VERSION MathJax_3)

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

  # https://www.doxygen.nl/manual/config.html
  doxygen_add_docs(a-doxygen WORKING_DIRECTORY
    ${CMAKE_CURRENT_LIST_DIR}/include/a
    ${CMAKE_CURRENT_LIST_DIR}/include/a
    ${CMAKE_CURRENT_LIST_DIR}/README.md
  )
endif()
