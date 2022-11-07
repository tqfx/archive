# include modules
include(CheckLibraryExists)

if(ANDROID AND UNIX)
  list(APPEND CMAKE_PREFIX_PATH /system)
endif()

if(DEFINED ENV{PREFIX})
  list(APPEND CMAKE_PREFIX_PATH $ENV{PREFIX})
endif()

set(A_REAL_BYTE 8 CACHE INTERNAL "real number bytes")
find_library(MATH_LIBRARY NAMES m DOC "math library")

# https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013/
# https://learn.microsoft.com/en-us/cpp/overview/visual-cpp-language-conformance
if(NOT MATH_LIBRARY AND CMAKE_C_COMPILER_ID MATCHES "TinyCC" AND WIN32)
  find_file(MATH_LIBRARY NAMES ucrtbase.dll msvcrt.dll)
endif()

function(check_m VARIABLE FUNCTION)
  get_filename_component(LOCATION "${MATH_LIBRARY}" DIRECTORY)
  list(APPEND CMAKE_REQUIRED_LIBRARIES ${MATH_LIBRARY})

  if(A_REAL_BYTE GREATER 8 OR A_REAL_BITS GREATER 64)
    set(FUNCTION "${FUNCTION}l")
  elseif(A_REAL_BYTE EQUAL 4 OR A_REAL_BITS EQUAL 32)
    set(FUNCTION "${FUNCTION}f")
  endif()

  if(NOT MATH_LIBRARY AND WIN32)
    set(MATH_LIBRARY ucrt msvcrt)
  elseif(NOT MATH_LIBRARY)
    set(MATH_LIBRARY m)
  endif()

  check_library_exists("${MATH_LIBRARY}"
    ${FUNCTION} "${LOCATION}" ${VARIABLE}
  )
endfunction()

# math.h
check_m(A_HAVE_HYPOT hypot)
check_m(A_HAVE_LOG1P log1p)
check_m(A_HAVE_ATAN2 atan2)

# complex.h
check_m(A_HAVE_CSQRT csqrt)
check_m(A_HAVE_CPOW cpow)
check_m(A_HAVE_CEXP cexp)
check_m(A_HAVE_CLOG clog)
check_m(A_HAVE_CSIN csin)
check_m(A_HAVE_CCOS ccos)
check_m(A_HAVE_CTAN ctan)
check_m(A_HAVE_CSINH csinh)
check_m(A_HAVE_CCOSH ccosh)
check_m(A_HAVE_CTANH ctanh)
check_m(A_HAVE_CASIN casin)
check_m(A_HAVE_CACOS cacos)
check_m(A_HAVE_CATAN catan)
check_m(A_HAVE_CASINH casinh)
check_m(A_HAVE_CACOSH cacosh)
check_m(A_HAVE_CATANH catanh)
