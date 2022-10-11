# include modules
include(${PROJECT_SOURCE_DIR}/cmake/core.cmake)

if(
  "${CMAKE_C_COMPILER_ID}" MATCHES "(ARM|Apple)?[Cc]lang" OR
  "${CMAKE_C_COMPILER_ID}" MATCHES "IntelLLVM" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "(ARM|Apple)?[Cc]lang" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "IntelLLVM"
)
  warnings_flag_cx(-Wno-documentation)
  warnings_flag_cx(-Wno-documentation-unknown-command)
endif()
