# include modules
include(${CMAKE_CURRENT_LIST_DIR}/core.cmake)

macro(sanitize_flag)
  list_append(CFLAGS_SANITIZE ${ARGN})
  list_append(CXXFLAGS_SANITIZE ${ARGN})
endmacro()

macro(sanitize_link)
  check_flag_cc(LDFLAGS_SANITIZE ${ARGN})
endmacro()

if(
  CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
  CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
  CMAKE_C_COMPILER_ID MATCHES "GNU" OR
  CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
  CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM" OR
  CMAKE_CXX_COMPILER_ID MATCHES "GNU"
)
  sanitize_flag(-fsanitize=address)
  sanitize_flag_cx(-fsanitize=undefined)
  sanitize_flag_cx(-fno-omit-frame-pointer)
  sanitize_flag_cx(-fsanitize-recover=address)

  if(NOT(
    CMAKE_C_COMPILER_ID MATCHES "Apple[Cc]lang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "Apple[Cc]lang"
    ))
    sanitize_flag_cx(-fsanitize=leak)

    if(
      CMAKE_C_COMPILER_ID MATCHES "GNU" OR
      CMAKE_CXX_COMPILER_ID MATCHES "GNU"
    )
      sanitize_link(-static-liblsan)
    endif()
  endif()

  if(
    CMAKE_C_COMPILER_ID MATCHES "GNU" OR
    CMAKE_CXX_COMPILER_ID MATCHES "GNU"
  )
    sanitize_link(-static-libubsan)
    sanitize_link(-static-libasan)
  endif()

  if(
    CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
    CMAKE_C_COMPILER_ID MATCHES "IntelLLVM" OR
    CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "IntelLLVM"
  )
    sanitize_link(-static-libsan)
  endif()
elseif(
  CMAKE_C_COMPILER_ID MATCHES "MSVC" OR
  CMAKE_CXX_COMPILER_ID MATCHES "MSVC"
)
  sanitize_flag_cx(/fsanitize=address)
endif()
