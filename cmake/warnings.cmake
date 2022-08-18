# include modules
include(${CMAKE_CURRENT_LIST_DIR}/core.cmake)

if(
  "${CMAKE_C_COMPILER_ID}" MATCHES "GNU" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU"
)
  check_flag_cc(-Winit-self)
  check_flag_cc(-Wc++-compat)
  check_flag_cc(-Wbad-function-cast)
  check_flag_cc(-Wstrict-prototypes)
  check_flag_cc(-Wold-style-definition)
  check_flag_cc(-Wmissing-prototypes)
  check_flag_cc(-Wnested-externs)
  check_flag_cx(-Wdouble-promotion)
  check_flag_cx(-Wnull-dereference)
  check_flag_cx(-Wmissing-include-dirs)
  check_flag_cx(-Wswitch-default)
  check_flag_cx(-Wswitch-enum)
  check_flag_cx(-Walloca)
  check_flag_cx(-Wattributes)
  check_flag_cx(-Wfloat-equal)
  check_flag_cx(-Wshadow)
  check_flag_cx(-Wundef)
  check_flag_cx(-Wunused)
  check_flag_cx(-Wunused-macros)
  check_flag_cx(-Wcast-qual)
  check_flag_cx(-Wcast-align)
  check_flag_cx(-Wconversion)
  check_flag_cx(-Wdate-time)
  check_flag_cx(-Waggregate-return)
  check_flag_cx(-Wmissing-declarations)
  check_flag_cx(-Wpacked)
  check_flag_cx(-Wpadded)
  check_flag_cx(-Wredundant-decls)
  check_flag_cx(-Winline)
  check_flag_cx(-Winvalid-pch)
  check_flag_cx(-Wdisabled-optimization)
  check_flag_cx(-Wstack-protector)
  check_flag_cx(-Wstringop-overflow)
  check_flag_cx(-Wstringop-truncation)
  check_flag_cx(-Walloc-zero)
  check_flag_cx(-Wduplicated-branches)
  check_flag_cx(-Wduplicated-cond)
  check_flag_cx(-Wzero-length-bounds)
  check_flag_cx(-Wtrampolines)
  check_flag_cx(-Wunsafe-loop-optimizations)
  check_flag_cx(-Wno-pedantic-ms-format)
  check_flag_cx(-Wlogical-op)
elseif(
  "${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR
  "${CMAKE_C_COMPILER_ID}" MATCHES "IntelLLVM" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "IntelLLVM"
)
  check_flag_cx(-Weverything)
  check_flag_cx(-Wno-reserved-id-macro)
  check_flag_cx(-Wno-reserved-identifier)
  check_flag_cx(-Wno-used-but-marked-unused)
  check_flag_cc(-Wno-declaration-after-statement)
  check_flag_xx(-Wno-c++98-compat-pedantic)
elseif(
  "${CMAKE_C_COMPILER_ID}" MATCHES "MSVC" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC"
)
  check_flag_cx(/Wall)
  check_flag_cx(/wd4464)
  check_flag_cx(/wd4514)
  check_flag_cx(/wd4710)
  check_flag_cx(/wd5039)
  check_flag_cx(/wd5045)
endif()
