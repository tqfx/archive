# include modules
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)
include(CheckLanguage)
check_language(CXX)

if(CMAKE_CXX_COMPILER)
  enable_language(CXX)
endif()

function(check_compile_feature)
  foreach(feature ${ARGN})
    string(TOUPPER ${feature} var)
    string(CONCAT var "A_HAVE_" ${var})
    set(${var} 1 CACHE INTERNAL "Have feature ${feature}")
  endforeach()
endfunction()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
get_cmake_property(TARGET_SUPPORTS_SHARED_LIBS TARGET_SUPPORTS_SHARED_LIBS)
check_compile_feature(${CMAKE_C_COMPILE_FEATURES} ${CMAKE_CXX_COMPILE_FEATURES})

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Specifies the build type on single-configuration generators." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_VERSION VERSION_LESS 3.21)
  if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(PROJECT_IS_TOP_LEVEL ON)
  else()
    set(PROJECT_IS_TOP_LEVEL NO)
  endif()
endif()

function(string_prefix variable)
  foreach(var ${ARGN})
    string(FIND "${${variable}}" "${var}" out)

    if(${out} EQUAL -1)
      string(STRIP "${var} ${${variable}}" ${variable})
    endif()
  endforeach()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()

function(string_append variable)
  foreach(var ${ARGN})
    string(FIND "${${variable}}" "${var}" out)

    if(${out} EQUAL -1)
      string(STRIP "${${variable}} ${var}" ${variable})
    endif()
  endforeach()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()

function(string_remove variable)
  foreach(var ${ARGN})
    string(REPLACE "${var} " "" ${variable} "${${variable}}")
    string(REPLACE "${var}" "" ${variable} "${${variable}}")
  endforeach()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()

function(list_append variable)
  foreach(var ${ARGN})
    if(NOT ${var} IN_LIST ${variable})
      list(APPEND ${variable} ${var})
    endif()
  endforeach()

  set(${variable} ${${variable}} PARENT_SCOPE)
endfunction()

function(list_remove variable)
  foreach(var ${ARGN})
    if(${var} IN_LIST ${variable})
      list(REMOVE_ITEM ${variable} ${var})
    endif()
  endforeach()

  set(${variable} ${${variable}} PARENT_SCOPE)
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
