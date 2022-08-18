# include modules
include(${CMAKE_CURRENT_LIST_DIR}/core.cmake)

macro(sanitize_flag)
  list_append(CFLAGS ${ARGN})
  list_append(CXXFLAGS ${ARGN})
endmacro()

if(
  "${CMAKE_C_COMPILER_ID}" MATCHES "GNU" OR
  "${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR
  "${CMAKE_C_COMPILER_ID}" MATCHES "IntelLLVM" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "IntelLLVM"
)
  sanitize_flag(-fsanitize=address)
  check_flag_cx(-fsanitize=undefined)
  check_flag_cx(-fno-omit-frame-pointer)
  check_flag_cx(-fsanitize-recover=address)

  if(NOT(
    "${CMAKE_C_COMPILER_ID}" MATCHES "Apple[Cc]lang" OR
    "${CMAKE_CXX_COMPILER_ID}" MATCHES "Apple[Cc]lang"
    ))
    check_flag_cx(-fsanitize=leak)
  endif()
elseif(
  "${CMAKE_C_COMPILER_ID}" MATCHES "MSVC" OR
  "${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC"
)
  check_flag_cx(/fsanitize=address)
endif()
