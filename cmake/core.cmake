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

get_property(enabled_languages GLOBAL PROPERTY ENABLED_LANGUAGES)

macro(check_flag_cx)
  foreach(v ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" r ${v})

    if(C IN_LIST enabled_languages)
      check_c_compiler_flag(${v} C${r})

      if(C${r} AND NOT ${v} IN_LIST CFLAGS)
        list(APPEND CFLAGS ${v})
      endif()
    endif()

    if(CXX IN_LIST enabled_languages)
      check_cxx_compiler_flag(${v} CXX${r})

      if(CXX${r} AND NOT ${v} IN_LIST CXXFLAGS)
        list(APPEND CXXFLAGS ${v})
      endif()
    endif()
  endforeach()
endmacro()

macro(check_flag_cc)
  foreach(v ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" r ${v})

    if(C IN_LIST enabled_languages)
      check_c_compiler_flag(${v} C${r})

      if(C${r} AND NOT ${v} IN_LIST CFLAGS)
        list(APPEND CFLAGS ${v})
      endif()
    endif()
  endforeach()
endmacro()

macro(check_flag_xx)
  foreach(v ${ARGN})
    string(REGEX REPLACE "[^A-Za-z0-9_+-]+" "-" r ${v})

    if(CXX IN_LIST enabled_languages)
      check_cxx_compiler_flag(${v} CXX${r})

      if(CXX${r} AND NOT ${v} IN_LIST CXXFLAGS)
        list(APPEND CXXFLAGS ${v})
      endif()
    endif()
  endforeach()
endmacro()
