# include modules
include(${CMAKE_CURRENT_LIST_DIR}/core.cmake)

if(
  "${CMAKE_C_COMPILER_ID}" MATCHES "GNU" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU"
)
  # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc-4.9.4/gcc/Warning-Options.html
  warnings_flag_cc(-Winit-self)
  warnings_flag_cc(-Wc++-compat)
  warnings_flag_cc(-Wbad-function-cast)
  warnings_flag_cc(-Wstrict-prototypes)
  warnings_flag_cc(-Wold-style-definition)
  warnings_flag_cc(-Wmissing-prototypes)
  warnings_flag_cc(-Wnested-externs)
  warnings_flag_cx(-Wdouble-promotion)
  warnings_flag_cx(-Wnull-dereference)
  warnings_flag_cx(-Wmissing-include-dirs)
  warnings_flag_cx(-Wswitch-default)
  warnings_flag_cx(-Wswitch-enum)
  warnings_flag_cx(-Walloca)
  warnings_flag_cx(-Wattributes)
  warnings_flag_cx(-Wfloat-equal)
  warnings_flag_cx(-Wshadow)
  warnings_flag_cx(-Wundef)
  warnings_flag_cx(-Wunused)
  warnings_flag_cx(-Wunused-macros)
  warnings_flag_cx(-Wcast-qual)
  warnings_flag_cx(-Wcast-align)
  warnings_flag_cx(-Wconversion)
  warnings_flag_cx(-Wdate-time)
  warnings_flag_cx(-Waggregate-return)
  warnings_flag_cx(-Wmissing-declarations)
  warnings_flag_cx(-Wpacked)
  warnings_flag_cx(-Wpadded)
  warnings_flag_cx(-Wredundant-decls)
  warnings_flag_cx(-Winline)
  warnings_flag_cx(-Winvalid-pch)
  warnings_flag_cx(-Wdisabled-optimization)
  warnings_flag_cx(-Wstack-protector)
  warnings_flag_cx(-Wstringop-overflow)
  warnings_flag_cx(-Wstringop-truncation)
  warnings_flag_cx(-Walloc-zero)
  warnings_flag_cx(-Wduplicated-branches)
  warnings_flag_cx(-Wduplicated-cond)
  warnings_flag_cx(-Wzero-length-bounds)
  warnings_flag_cx(-Wtrampolines)
  warnings_flag_cx(-Wunsafe-loop-optimizations)
  warnings_flag_cx(-Wno-pedantic-ms-format)
  warnings_flag_cx(-Wlogical-op)
elseif(
  "${CMAKE_C_COMPILER_ID}" MATCHES "(ARM|Apple)?[Cc]lang" OR
  "${CMAKE_C_COMPILER_ID}" MATCHES "IntelLLVM" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "(ARM|Apple)?[Cc]lang" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "IntelLLVM"
)
  # https://clang.llvm.org/docs/DiagnosticsReference.html
  # https://releases.llvm.org/4.0.1/tools/clang/docs/DiagnosticsReference.html
  warnings_flag_cx(-Weverything)
  warnings_flag_cx(-Wno-documentation)
  warnings_flag_cx(-Wno-used-but-marked-unused)
  warnings_flag_cx(-Wno-documentation-unknown-command)
  warnings_flag_cc(-Wno-declaration-after-statement)
  warnings_flag_xx(-Wno-c++98-compat-pedantic)
elseif(
  "${CMAKE_C_COMPILER_ID}" MATCHES "MSVC" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC"
)
  # https://learn.microsoft.com/en-us/cpp/error-messages
  warnings_flag_cx(/Wall)
  warnings_flag_cx(/wd4464)
  warnings_flag_cx(/wd4514)
  warnings_flag_cx(/wd4710)
  warnings_flag_cx(/wd5039)
  warnings_flag_cx(/wd5045)
endif()
