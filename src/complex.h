#ifndef COMPLEX_H
#define COMPLEX_H

#include "a/complex.h"
#include <math.h>

#if defined(__cplusplus)
#include <complex>
#define A_COMPLEX_T std::complex<A_REAL_T>
#else /* !__cplusplus */
#if defined(__GNUC__)
#include <complex.h>
#define A_COMPLEX_T _Complex A_REAL_T
#elif defined(_MSC_VER)
#include <complex.h>
#if A_REAL_BITS > 64
#define A_COMPLEX_T _Lcomplex
#elif A_REAL_BITS == 64
#define A_COMPLEX_T _Dcomplex
#elif A_REAL_BITS == 32
#define A_COMPLEX_T _Fcomplex
#endif /* A_REAL_BITS */
#endif /* A_COMPLEX_T */
#endif /* __cplusplus */

#if defined(A_COMPLEX_T)

/* compiler built-in complex number type */
#define a_complex_t A_COMPLEX_T

typedef union
{
    a_complex_s s;
    a_complex_t z;
} a_complex_u;

#endif /* A_COMPLEX_T */

#endif /* COMPLEX_H */
