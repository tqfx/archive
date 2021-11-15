# include modules
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

# unset
unset(FLAG_CHECKS)
unset(FLAG_CHECK_CC)
unset(FLAG_CHECK_CXX)

# common
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
  "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  list(APPEND FLAG_CHECKS -Wall -Wextra -Wpedantic)
  list(APPEND FLAG_CHECKS -Wdouble-promotion)
  list(APPEND FLAG_CHECKS -Wnull-dereference)
  list(APPEND FLAG_CHECKS -Wmissing-include-dirs)
  list(APPEND FLAG_CHECKS -Wswitch-default -Wswitch-enum)
  list(APPEND FLAG_CHECKS -Walloca)
  list(APPEND FLAG_CHECKS -Wattributes)
  list(APPEND FLAG_CHECKS -Wfloat-equal)
  list(APPEND FLAG_CHECKS -Wshadow)
  list(APPEND FLAG_CHECKS -Wundef)
  list(APPEND FLAG_CHECKS -Wunused -Wunused-macros)
  list(APPEND FLAG_CHECKS -Wcast-qual -Wcast-align)
  list(APPEND FLAG_CHECKS -Wconversion)
  list(APPEND FLAG_CHECKS -Wdate-time)
  list(APPEND FLAG_CHECKS -Waggregate-return)
  list(APPEND FLAG_CHECKS -Wmissing-declarations)
  list(APPEND FLAG_CHECKS -Wpacked -Wpadded)
  list(APPEND FLAG_CHECKS -Wredundant-decls)
  list(APPEND FLAG_CHECKS -Winline)
  list(APPEND FLAG_CHECKS -Winvalid-pch)
  list(APPEND FLAG_CHECKS -Wdisabled-optimization)
  list(APPEND FLAG_CHECKS -Wstack-protector)
  list(APPEND FLAG_CHECK_CC -Winit-self)
  list(APPEND FLAG_CHECK_CC -Wbad-function-cast)
  list(APPEND FLAG_CHECK_CC -Wc++-compat)
  list(APPEND FLAG_CHECK_CC -Wstrict-prototypes)
  list(APPEND FLAG_CHECK_CC -Wold-style-definition)
  list(APPEND FLAG_CHECK_CC -Wmissing-prototypes)
  list(APPEND FLAG_CHECK_CC -Wnested-externs)
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_link_options(/nologo)
  add_compile_options(/nologo)
  add_definitions(/D_CRT_SECURE_NO_WARNINGS)
  list(APPEND FLAG_CHECKS /W4)
  list(APPEND FLAG_CHECKS /sdl)
  list(APPEND FLAG_CHECKS /utf-8)
endif()
# GNU
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  list(APPEND FLAG_CHECKS -Wstringop-overflow -Wstringop-truncation)
  list(APPEND FLAG_CHECKS -Walloc-zero)
  list(APPEND FLAG_CHECKS -Wduplicated-branches -Wduplicated-cond)
  list(APPEND FLAG_CHECKS -Wzero-length-bounds)
  list(APPEND FLAG_CHECKS -Wtrampolines)
  list(APPEND FLAG_CHECKS -Wunsafe-loop-optimizations)
  list(APPEND FLAG_CHECKS -Wno-pedantic-ms-format)
  list(APPEND FLAG_CHECKS -Wlogical-op)
endif()
# Clang
if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  list(APPEND FLAG_CHECKS -Wzero-length-array)
  list(APPEND FLAG_CHECKS -Wshadow-all)
endif()

# C and C++
foreach(flag ${FLAG_CHECKS})
  if(NOT ${flag} IN_LIST FLAG_CHECKED_CC)
    list(APPEND FLAG_CHECKED_CC ${flag})
    check_c_compiler_flag(${flag} CC${flag})
    if(CC${flag})
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
    endif()
  endif()
  if(NOT ${flag} IN_LIST FLAG_CHECKED_CXX)
    list(APPEND FLAG_CHECKED_CXX ${flag})
    check_cxx_compiler_flag(${flag} CXX${flag})
    if(CXX${flag})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
    endif()
  endif()
endforeach()
# C
foreach(flag ${FLAG_CHECK_CC})
  if(NOT ${flag} IN_LIST FLAG_CHECKED_CC)
    list(APPEND FLAG_CHECKED_CC ${flag})
    check_c_compiler_flag(${flag} CC${flag})
    if(CC${flag})
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
    endif()
  endif()
endforeach()
# C++
foreach(flag ${FLAG_CHECK_CXX})
  if(NOT ${flag} IN_LIST FLAG_CHECKED_CXX)
    list(APPEND FLAG_CHECKED_CXX ${flag})
    check_cxx_compiler_flag(${flag} CXX${flag})
    if(CXX${flag})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
    endif()
  endif()
endforeach()

# unset
unset(FLAG_CHECKS)
unset(FLAG_CHECK_CC)
unset(FLAG_CHECK_CXX)
