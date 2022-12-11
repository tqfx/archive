# include modules
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckCSourceCompiles)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
get_cmake_property(TARGET_SUPPORTS_SHARED_LIBS TARGET_SUPPORTS_SHARED_LIBS)

function(target_supports_executables)
  set(CMAKE_REQUIRED_QUIET 1)
  set(CMAKE_TRY_COMPILE_TARGET_TYPE EXECUTABLE)
  check_c_source_compiles("int main(void) { return 0; }" TARGET_SUPPORTS_EXECUTABLES)
endfunction()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Specifies the build type on single-configuration generators." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_VERSION VERSION_LESS 3.21)
  if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(PROJECT_IS_TOP_LEVEL 1)
  else()
    set(PROJECT_IS_TOP_LEVEL 0)
  endif()
endif()

target_supports_executables()

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif()

function(string_prefix VAR)
  foreach(var ${ARGN})
    string(FIND "${${VAR}}" "${var}" out)

    if(${out} EQUAL -1)
      string(STRIP "${var} ${${VAR}}" ${VAR})
    endif()
  endforeach()

  set(${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction()

function(string_append VAR)
  foreach(var ${ARGN})
    string(FIND "${${VAR}}" "${var}" out)

    if(${out} EQUAL -1)
      string(STRIP "${${VAR}} ${var}" ${VAR})
    endif()
  endforeach()

  set(${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction()

function(string_remove VAR)
  foreach(var ${ARGN})
    string(REPLACE "${var} " "" ${VAR} "${${VAR}}")
    string(REPLACE "${var}" "" ${VAR} "${${VAR}}")
  endforeach()

  set(${VAR} "${${VAR}}" PARENT_SCOPE)
endfunction()

function(list_append VAR)
  foreach(var ${ARGN})
    if(NOT ${var} IN_LIST ${VAR})
      list(APPEND ${VAR} ${var})
    endif()
  endforeach()

  set(${VAR} ${${VAR}} PARENT_SCOPE)
endfunction()

function(list_remove VAR)
  foreach(var ${ARGN})
    if(${var} IN_LIST ${VAR})
      list(REMOVE_ITEM ${VAR} ${var})
    endif()
  endforeach()

  set(${VAR} ${${VAR}} PARENT_SCOPE)
endfunction()

macro(check_flag_cc VAR)
  foreach(var ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" out ${var})

    if(C IN_LIST ENABLED_LANGUAGES)
      check_c_compiler_flag(${var} CC${out})

      if(NOT ${var} IN_LIST ${VAR} AND CC${out})
        list(APPEND ${VAR} ${var})
      endif()
    endif()
  endforeach()
endmacro()

macro(warnings_flag_cc)
  check_flag_cc(CFLAGS_WARNINGS ${ARGN})
endmacro()

macro(sanitize_flag_cc)
  check_flag_cc(CFLAGS_SANITIZE ${ARGN})
endmacro()

macro(check_flag_xx VAR)
  foreach(var ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" out ${var})

    if(CXX IN_LIST ENABLED_LANGUAGES)
      check_cxx_compiler_flag(${var} CXX${out})

      if(NOT ${var} IN_LIST ${VAR} AND CXX${out})
        list(APPEND ${VAR} ${var})
      endif()
    endif()
  endforeach()
endmacro()

macro(warnings_flag_xx)
  check_flag_xx(CXXFLAGS_WARNINGS ${ARGN})
endmacro()

macro(sanitize_flag_xx)
  check_flag_xx(CXXFLAGS_SANITIZE ${ARGN})
endmacro()

macro(check_flag_cx VARC VARX)
  foreach(var ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" out ${var})

    if(C IN_LIST ENABLED_LANGUAGES)
      check_c_compiler_flag(${var} CC${out})

      if(NOT ${var} IN_LIST ${VARC} AND CC${out})
        list(APPEND ${VARC} ${var})
      endif()
    endif()

    if(CXX IN_LIST ENABLED_LANGUAGES)
      check_cxx_compiler_flag(${var} CXX${out})

      if(NOT ${var} IN_LIST ${VARX} AND CXX${out})
        list(APPEND ${VARX} ${var})
      endif()
    endif()
  endforeach()
endmacro()

macro(warnings_flag_cx)
  check_flag_cx(CFLAGS_WARNINGS CXXFLAGS_WARNINGS ${ARGN})
endmacro()

macro(sanitize_flag_cx)
  check_flag_cx(CFLAGS_SANITIZE CXXFLAGS_SANITIZE ${ARGN})
endmacro()
