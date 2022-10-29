include(CheckSymbolExists)

find_library(MATH_LIBRARY NAMES m
  PATHS /system/lib64 /system/lib
)

list(APPEND CMAKE_REQUIRED_LIBRARIES ${MATH_LIBRARY})

# math.h
check_symbol_exists(hypot "math.h" A_HAVE_HYPOT)
check_symbol_exists(log1p "math.h" A_HAVE_LOG1P)
check_symbol_exists(fabs "math.h" A_HAVE_FABS)
check_symbol_exists(pow "math.h" A_HAVE_POW)
check_symbol_exists(exp "math.h" A_HAVE_EXP)
check_symbol_exists(log "math.h" A_HAVE_LOG)
check_symbol_exists(sin "math.h" A_HAVE_SIN)
check_symbol_exists(cos "math.h" A_HAVE_COS)
check_symbol_exists(tan "math.h" A_HAVE_TAN)
check_symbol_exists(asin "math.h" A_HAVE_ASIN)
check_symbol_exists(acos "math.h" A_HAVE_ACOS)
check_symbol_exists(atan "math.h" A_HAVE_ATAN)
check_symbol_exists(atan2 "math.h" A_HAVE_ATAN2)

# complex.h
check_symbol_exists(csqrt "complex.h" A_HAVE_CSQRT)
check_symbol_exists(cpow "complex.h" A_HAVE_CPOW)
check_symbol_exists(cexp "complex.h" A_HAVE_CEXP)
check_symbol_exists(clog "complex.h" A_HAVE_CLOG)
check_symbol_exists(csin "complex.h" A_HAVE_CSIN)
check_symbol_exists(ccos "complex.h" A_HAVE_CCOS)
check_symbol_exists(ctan "complex.h" A_HAVE_CTAN)
check_symbol_exists(casin "complex.h" A_HAVE_CASIN)
check_symbol_exists(cacos "complex.h" A_HAVE_CACOS)
check_symbol_exists(catan "complex.h" A_HAVE_CATAN)
check_symbol_exists(csinh "complex.h" A_HAVE_CSINH)
check_symbol_exists(ccosh "complex.h" A_HAVE_CCOSH)
check_symbol_exists(ctanh "complex.h" A_HAVE_CTANH)
check_symbol_exists(casinh "complex.h" A_HAVE_CASINH)
check_symbol_exists(cacosh "complex.h" A_HAVE_CACOSH)
check_symbol_exists(catanh "complex.h" A_HAVE_CATANH)
