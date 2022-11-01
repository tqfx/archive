# include modules
include(${CMAKE_CURRENT_LIST_DIR}/core.cmake)

if(CMAKE_C_COMPILER_ID MATCHES "(ARM|Apple)?[Cc]lang" OR CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
  CMAKE_CXX_COMPILER_ID MATCHES "(ARM|Apple)?[Cc]lang" OR CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM")
  # https://clang.llvm.org/docs/DiagnosticsReference.html
  # https://releases.llvm.org/4.0.1/tools/clang/docs/DiagnosticsReference.html
  warnings_flag_cx(-Weverything)
  warnings_flag_cx(-Wno-documentation)
  warnings_flag_cx(-Wno-used-but-marked-unused)
  warnings_flag_cx(-Wno-documentation-unknown-command)
  warnings_flag_cc(-Wno-declaration-after-statement)
  warnings_flag_xx(-Wno-c++98-compat-pedantic)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR
  CMAKE_C_COMPILER_ID MATCHES "TinyCC" OR CMAKE_CXX_COMPILER_ID MATCHES "TinyCC")
  # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  # https://gcc.gnu.org/onlinedocs/gcc-3.0.3/gcc/Warning-Options.html
  warnings_flag_cx(-Wextra) # 3.4+
  warnings_flag_cc(-Winit-self) # 3.4+
  warnings_flag_cc(-Wc++-compat) # 4.1+
  warnings_flag_cc(-Wbad-function-cast) # 2.95+
  warnings_flag_cc(-Wstrict-prototypes) # 2.95+
  warnings_flag_cc(-Wold-style-definition) # 3.4+
  warnings_flag_cc(-Wmissing-prototypes) # 2.95+
  warnings_flag_cc(-Wnested-externs) # 2.95+
  warnings_flag_cx(-Wdouble-promotion) # 4.6+
  warnings_flag_cx(-Wnull-dereference) # 6.1+
  warnings_flag_cx(-Wmissing-include-dirs) # 4.0+
  warnings_flag_cx(-Wswitch-default) # 3.3+
  warnings_flag_cx(-Wswitch-enum) # 3.3+
  warnings_flag_cx(-Walloca) # 7.1+
  warnings_flag_cx(-Wattributes) # 4.1+
  warnings_flag_cx(-Wfloat-equal) # 3.0+
  warnings_flag_cx(-Wshadow) # 2.95+
  warnings_flag_cx(-Wundef) # 2.95+
  warnings_flag_cx(-Wunused) # 2.95+
  warnings_flag_cx(-Wunused-macros) # 7.1+
  warnings_flag_cx(-Wcast-qual) # 2.95+
  warnings_flag_cx(-Wcast-align) # 2.95+
  warnings_flag_cx(-Wconversion) # 2.95+
  warnings_flag_cx(-Wdate-time) # 4.9+
  warnings_flag_cx(-Waggregate-return) # 2.95+
  warnings_flag_cx(-Wmissing-declarations) # 2.95+
  warnings_flag_cx(-Wpacked) # 3.0+
  warnings_flag_cx(-Wpadded) # 3.0+
  warnings_flag_cx(-Wredundant-decls) # 2.95+
  warnings_flag_cx(-Winline) # 2.95+
  warnings_flag_cx(-Winvalid-pch) # 3.4+
  warnings_flag_cx(-Wdisabled-optimization) # 3.0+
  warnings_flag_cx(-Wstack-protector) # 4.1+
  warnings_flag_cx(-Wstringop-overflow) # 7.1+
  warnings_flag_cx(-Wstringop-truncation) # 8.1+
  warnings_flag_cx(-Walloc-zero) # 7.1+
  warnings_flag_cx(-Wduplicated-branches) # 7.1+
  warnings_flag_cx(-Wduplicated-cond) # 6.1+
  warnings_flag_cx(-Wzero-length-bounds) # 10.1+
  warnings_flag_cx(-Wtrampolines) # 4.6+
  warnings_flag_cx(-Wunsafe-loop-optimizations) # 4.1+
  warnings_flag_cx(-Wno-pedantic-ms-format) # 4.4+
  warnings_flag_cx(-Wlogical-op) # 4.3+
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC" OR CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # https://learn.microsoft.com/en-us/cpp/error-messages
  warnings_flag_cx(/Wall)
  warnings_flag_cx(/wd4464)
  warnings_flag_cx(/wd4514)
  warnings_flag_cx(/wd4710)
  warnings_flag_cx(/wd5039)
  warnings_flag_cx(/wd5045)
endif()
