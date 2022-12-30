cmake_minimum_required(VERSION 3.15)

if(POLICY CMP0057) # 3.3
  cmake_policy(SET CMP0057 NEW)
endif() # if(IN_LIST)

if(POLICY CMP0063) # 3.3
  cmake_policy(SET CMP0063 NEW)
endif() # <LANG>_VISIBILITY_PRESET

if(POLICY CMP0091) # 3.15
  cmake_policy(SET CMP0091 NEW)
endif() # CMAKE_MSVC_RUNTIME_LIBRARY

option(WITH_CXX "Enable or disable C++" 1)

if(NOT CXX IN_LIST LANGUAGES AND WITH_CXX)
  list(PREPEND LANGUAGES CXX)
endif()

if(NOT C IN_LIST LANGUAGES)
  list(PREPEND LANGUAGES C)
endif()

project(liba VERSION 0.1.1 LANGUAGES ${LANGUAGES} # 3.12
  DESCRIPTION "An algorithm library based on C/C++ language"
  HOMEPAGE_URL "https://github.com/tqfx/liba.git"
)

include(GNUInstallDirs)
include(cmake/core.cmake)
include(cmake/target.cmake)
include(cmake/package.cmake)
include(cmake/standard.cmake)

option(LIBA_STATIC "Enable or disable static" 0)

if(LIBA_STATIC)
  include(cmake/static.cmake)
endif()

option(LIBA_WARNINGS "Enable or disable warnings" 0)

if(LIBA_WARNINGS)
  include(cmake/warnings.cmake)
endif()

option(LIBA_SANITIZE "Enable or disable sanitize" 0)

if(LIBA_SANITIZE)
  include(cmake/sanitize.cmake)
endif()

include(cmake/check.cmake)

option(LIBA_PYTHON "Enable or disable python" 0)

# https://cmake.org/cmake/help/latest/module/FindPython.html
if(LIBA_PYTHON AND CMAKE_VERSION VERSION_GREATER 3.12)
  find_package(Python COMPONENTS Interpreter)
  set(PYTHONINTERP_FOUND ${Python_Interpreter_FOUND})
  set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
elseif(LIBA_PYTHON) # cmake < 3.12
  find_package(PythonInterp)
endif()

option(LIBA_DOXYGEN "Enable or disable doxygen" 0)

# https://cmake.org/cmake/help/latest/module/FindDoxygen.html
if(LIBA_DOXYGEN AND CMAKE_VERSION VERSION_GREATER 3.9)
  find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
elseif(LIBA_DOXYGEN) # cmake < 3.9
  find_package(Doxygen)
endif()

option(LIBA_IPO "Enable or disable interprocedural optimization" 0)

# https://cmake.org/cmake/help/latest/module/CheckIPOSupported.html
if(LIBA_IPO AND CMAKE_VERSION VERSION_GREATER 3.9)
  cmake_policy(SET CMP0069 NEW)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT LIBA_IPO)
elseif(LIBA_IPO) # cmake < 3.9
  set(LIBA_IPO 0)
endif()

function(target_library_setting target)
  if(LIBA_TALLOC AND TALLOC_FOUND)
    target_link_libraries(${target} PUBLIC Talloc::talloc)
  endif()

  add_library(${PROJECT_NAME}::${target} ALIAS ${target})
  set_target_properties(${target} PROPERTIES
    POSITION_INDEPENDENT_CODE ON DEFINE_SYMBOL A_EXPORTS
  )
  target_compile_definitions(${target} PRIVATE A_EXPORTS)
  target_compile_definitions(${target} PUBLIC A_HAVE_H)
  target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_link_libraries(${target} PUBLIC ${LIBA_MATH})
  target_library_options(${target})
endfunction()

if(CXX IN_LIST ENABLED_LANGUAGES)
  file(GLOB_RECURSE SOURCES include/*.h* src/*.[chm]*)
else()
  file(GLOB_RECURSE SOURCES include/*.h src/*.[ch])
endif()

configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.h
  ${CMAKE_CURRENT_BINARY_DIR}/a.config.h
)

set(A_LIBRARIES a)
add_library(a ${SOURCES})
target_library_setting(a)

if(TARGET_SUPPORTS_SHARED_LIBS)
  if(NOT BUILD_SHARED_LIBS)
    set(module SHARED)
    set(shared liba)
  else()
    set(module STATIC)
    set(shared a)
  endif()

  list(APPEND A_LIBRARIES liba)
  add_library(liba ${module} $<TARGET_OBJECTS:a>)
  set_target_properties(liba PROPERTIES OUTPUT_NAME a)
  target_compile_definitions(${shared} INTERFACE A_IMPORTS)
  target_library_setting(liba)

  if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
    set_target_properties(${shared}
      PROPERTIES OUTPUT_NAME liba
    )
  endif()
endif()

if(LIBA_SANITIZE)
  add_library(asan ${SOURCES})
  target_library_setting(asan)
  target_compile_sanitize(asan)
  set_target_properties(asan
    PROPERTIES OUTPUT_NAME a.san
  )

  if(TARGET_SUPPORTS_SHARED_LIBS)
    if(NOT BUILD_SHARED_LIBS)
      set(shared libasan)
      set(module SHARED)
    else()
      set(module STATIC)
      set(shared asan)
    endif()

    add_library(libasan ${module} $<TARGET_OBJECTS:asan>)
    set_target_properties(libasan PROPERTIES OUTPUT_NAME a.san)
    target_compile_definitions(${shared} INTERFACE A_IMPORTS)
    target_library_setting(libasan)

    if(CMAKE_STATIC_LIBRARY_SUFFIX STREQUAL .lib)
      set_target_properties(${shared}
        PROPERTIES OUTPUT_NAME liba.san
      )
    endif()
  endif()
endif()

get_property(prop TARGET a PROPERTY INTERFACE_COMPILE_DEFINITIONS)
set(PROJECT_CFLAGS "$<$<BOOL:${prop}>:-D$<JOIN:${prop}, -D>>")
get_property(prop TARGET a PROPERTY INTERFACE_LINK_LIBRARIES)
set(PROJECT_LIBS "-l$<JOIN:a;${prop}, -l>")

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

option(LIBA_PKGCONFIG "Enable or disable pkgconfig" 0)

if(LIBA_PKGCONFIG)
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

option(LIBA_VCPKG "Enable or disable vcpkg" 0)

if(LIBA_VCPKG AND GIT_COMMIT)
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

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/ffi)
  add_subdirectory(ffi)
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/test AND PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
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
endif()

if(PYTHONINTERP_FOUND)
  file(GLOB BYPRODUCT ${PROJECT_NAME}.*)
  file(GLOB_RECURSE SOURCES ffi/python/src/*.[ch]*)
  add_custom_target(a-py ALL # https://cython.readthedocs.io/en/stable
    ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/setup.py --quiet build_ext --inplace
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
    "A_EXTERN:="
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
