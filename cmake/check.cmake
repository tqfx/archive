# include modules
include(CheckIncludeFile)
include(CheckLibraryExists)

if(CMAKE_VERSION VERSION_GREATER 3.20 AND CMAKE_C_BYTE_ORDER EQUAL LITTLE_ENDIAN)
  set(PROJECT_BYTE_ORDER 1234)
elseif(CMAKE_VERSION VERSION_GREATER 3.20 AND CMAKE_C_BYTE_ORDER EQUAL BIG_ENDIAN)
  set(PROJECT_BYTE_ORDER 4321)
else()
  include(TestBigEndian)
  test_big_endian(var)

  if(var)
    set(PROJECT_BYTE_ORDER 4321)
  else()
    set(PROJECT_BYTE_ORDER 1234)
  endif()
endif()

set(A_SIZE_REAL 8 CACHE INTERNAL "real number bytes")
find_library(MATH_LIBRARY NAMES m DOC "math library")
mark_as_advanced(MATH_LIBRARY)

# https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013
# https://learn.microsoft.com/cpp/overview/visual-cpp-language-conformance
if(NOT MATH_LIBRARY AND CMAKE_C_COMPILER_ID MATCHES "TinyCC" AND WIN32)
  find_file(MATH_LIBRARY NAMES ucrtbase.dll msvcrt.dll)
endif()

function(check_math VARIABLE FUNCTION)
  get_filename_component(LOCATION "${MATH_LIBRARY}" DIRECTORY)
  list(APPEND CMAKE_REQUIRED_LIBRARIES ${MATH_LIBRARY})

  if(A_SIZE_REAL GREATER 8)
    set(FUNCTION "${FUNCTION}l")
  elseif(A_SIZE_REAL EQUAL 4)
    set(FUNCTION "${FUNCTION}f")
  endif()

  if(NOT MATH_LIBRARY AND WIN32)
    set(MATH_LIBRARY msvcrt)
  elseif(NOT MATH_LIBRARY)
    set(MATH_LIBRARY m)
  endif()

  check_library_exists("${MATH_LIBRARY}"
    ${FUNCTION} "${LOCATION}" ${VARIABLE}
  )
endfunction()

if(NOT MATH_LIBRARY AND WIN32)
  unset(MATH_LIBRARY CACHE)
elseif(NOT MATH_LIBRARY)
  set(MATH_LIBRARY m)
endif()

check_include_file(stdint.h A_HAVE_STDINT_H)
check_math(A_HAVE_HYPOT hypot)
check_math(A_HAVE_LOG1P log1p)
check_math(A_HAVE_ATAN2 atan2)
check_include_file(complex.h A_HAVE_COMPLEX_H)
check_math(A_HAVE_CSQRT csqrt)
check_math(A_HAVE_CPOW cpow)
check_math(A_HAVE_CEXP cexp)
check_math(A_HAVE_CLOG clog)
check_math(A_HAVE_CSIN csin)
check_math(A_HAVE_CCOS ccos)
check_math(A_HAVE_CTAN ctan)
check_math(A_HAVE_CSINH csinh)
check_math(A_HAVE_CCOSH ccosh)
check_math(A_HAVE_CTANH ctanh)
check_math(A_HAVE_CASIN casin)
check_math(A_HAVE_CACOS cacos)
check_math(A_HAVE_CATAN catan)
check_math(A_HAVE_CASINH casinh)
check_math(A_HAVE_CACOSH cacosh)
check_math(A_HAVE_CATANH catanh)

option(LIBA_TALLOC "Enable or disable talloc" 0)

if(LIBA_TALLOC)
  find_path(TALLOC_INCLUDE_DIR talloc.h)
  find_library(TALLOC_LIBRARY talloc)
  mark_as_advanced(
    TALLOC_INCLUDE_DIR TALLOC_LIBRARY
  )

  if(TALLOC_INCLUDE_DIR AND TALLOC_LIBRARY)
    set(A_HAVE_TALLOC_H 1)
    set(TALLOC_FOUND 1)
  endif()
endif()
