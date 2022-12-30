# include modules
include(CheckIncludeFile)
include(CheckLibraryExists)

find_library(LIBA_MATH NAMES m DOC "math library")
find_library(LIBA_LIBM NAMES m DOC "math library" NO_CMAKE_PATH)

# https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013
# https://learn.microsoft.com/cpp/overview/visual-cpp-language-conformance
if(NOT LIBA_MATH AND WIN32 AND CMAKE_C_COMPILER_ID MATCHES "TinyCC")
  find_file(LIBA_MATH NAMES ucrtbase.dll msvcrt.dll)
endif()

if(LIBA_LIBM STREQUAL LIBA_MATH)
  mark_as_advanced(LIBA_LIBM LIBA_MATH)
  set(LIBA_MATH m CACHE STRING "math library" FORCE)
endif()

set(A_SIZE_REAL 8 CACHE INTERNAL "real number bytes")

function(check_math VARIABLE FUNCTION)
  get_filename_component(LOCATION "${LIBA_MATH}" DIRECTORY)
  list(APPEND CMAKE_REQUIRED_LIBRARIES ${LIBA_MATH})

  if(A_SIZE_REAL GREATER 8)
    set(FUNCTION "${FUNCTION}l")
  elseif(A_SIZE_REAL EQUAL 4)
    set(FUNCTION "${FUNCTION}f")
  endif()

  if(NOT LIBA_MATH AND WIN32)
    set(LIBA_MATH msvcrt)
  elseif(NOT LIBA_MATH)
    set(LIBA_MATH m)
  endif()

  check_library_exists("${LIBA_MATH}"
    ${FUNCTION} "${LOCATION}" ${VARIABLE}
  )
endfunction()

if(NOT LIBA_LIBM)
  unset(LIBA_LIBM CACHE)
endif()

if(NOT LIBA_MATH AND WIN32)
  unset(LIBA_MATH CACHE)
elseif(NOT LIBA_MATH)
  set(LIBA_MATH m)
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
