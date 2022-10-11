function(string_prefix variable)
  foreach(v ${ARGN})
    string(FIND "${${variable}}" "${v}" r)

    if(${r} EQUAL -1)
      string(STRIP "${v} ${${variable}}" ${variable})
    endif()
  endforeach()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()

function(string_append variable)
  foreach(v ${ARGN})
    string(FIND "${${variable}}" "${v}" r)

    if(${r} EQUAL -1)
      string(STRIP "${${variable}} ${v}" ${variable})
    endif()
  endforeach()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()

function(string_remove variable)
  foreach(v ${ARGN})
    string(REPLACE "${v} " "" ${variable} "${${variable}}")
    string(REPLACE "${v}" "" ${variable} "${${variable}}")
  endforeach()

  set(${variable} "${${variable}}" PARENT_SCOPE)
endfunction()

function(list_append variable)
  foreach(v ${ARGN})
    if(NOT ${v} IN_LIST ${variable})
      list(APPEND ${variable} ${v})
    endif()
  endforeach()

  set(${variable} ${${variable}} PARENT_SCOPE)
endfunction()

function(list_remove variable)
  foreach(v ${ARGN})
    if(${v} IN_LIST ${variable})
      list(REMOVE_ITEM ${variable} ${v})
    endif()
  endforeach()

  set(${variable} ${${variable}} PARENT_SCOPE)
endfunction()

# include modules
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)

macro(check_flag_cc VAR)
  foreach(v ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" r ${v})

    if(C IN_LIST ENABLED_LANGUAGES)
      check_c_compiler_flag(${v} CC${r})

      if(NOT ${v} IN_LIST ${VAR} AND CC${r})
        list(APPEND ${VAR} ${v})
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
  foreach(v ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" r ${v})

    if(CXX IN_LIST ENABLED_LANGUAGES)
      check_cxx_compiler_flag(${v} CXX${r})

      if(NOT ${v} IN_LIST ${VAR} AND CXX${r})
        list(APPEND ${VAR} ${v})
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
  foreach(v ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" r ${v})

    if(C IN_LIST ENABLED_LANGUAGES)
      check_c_compiler_flag(${v} CC${r})

      if(NOT ${v} IN_LIST ${VARC} AND CC${r})
        list(APPEND ${VARC} ${v})
      endif()
    endif()

    if(CXX IN_LIST ENABLED_LANGUAGES)
      check_cxx_compiler_flag(${v} CXX${r})

      if(NOT ${v} IN_LIST ${VARX} AND CXX${r})
        list(APPEND ${VARX} ${v})
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
