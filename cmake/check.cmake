# include modules
include(CheckLibraryExists)
set(A_VERSION ${PROJECT_VERSION})
set(A_SIZE_PTR ${CMAKE_SIZEOF_VOID_P})
set(A_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(A_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(A_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(A_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})

if(CMAKE_VERSION VERSION_GREATER 3.20 AND CMAKE_C_BYTE_ORDER EQUAL LITTLE_ENDIAN)
  set(A_BYTE_ORDER 1234)
elseif(CMAKE_VERSION VERSION_GREATER 3.20 AND CMAKE_C_BYTE_ORDER EQUAL BIG_ENDIAN)
  set(A_BYTE_ORDER 4321)
else()
  include(TestBigEndian)
  test_big_endian(var)

  if(var)
    set(A_BYTE_ORDER 4321)
  else()
    set(A_BYTE_ORDER 1234)
  endif()
endif()

if(DEFINED ENV{PREFIX})
  list(APPEND CMAKE_PREFIX_PATH $ENV{PREFIX})
endif()

if(DEFINED ENV{ANDROID_ROOT})
  list(APPEND CMAKE_PREFIX_PATH $ENV{ANDROID_ROOT})
endif()

set(A_REAL_BYTE 8 CACHE INTERNAL "real number bytes")
find_library(MATH_LIBRARY NAMES m DOC "math library")

# https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013
# https://learn.microsoft.com/cpp/overview/visual-cpp-language-conformance
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
    set(MATH_LIBRARY msvcrt)
  elseif(NOT MATH_LIBRARY)
    set(MATH_LIBRARY m)
  endif()

  check_library_exists("${MATH_LIBRARY}"
    ${FUNCTION} "${LOCATION}" ${VARIABLE}
  )
endfunction()

if(NOT MATH_LIBRARY)
  unset(MATH_LIBRARY CACHE)
endif()

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
