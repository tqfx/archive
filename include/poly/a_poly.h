/*!
 @file a_poly.h
 @brief polynomial
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_POLY_H__
#define __A_POLY_H__

#include "liba.h"

__BEGIN_DECLS

/*!
 @brief horner function for polynomial
 \f[
  \left\{\begin{array}{l}
  S_n = a_n\\
  S_i = xS_{i+1} + a_i,\quad(i=n-1,n-2,\cdots,1,0)\\
  P(x) = S_0
  \end{array}\right.
 \f]
*/
double a_horner(const double *a, size_t n, double x);
float a_hornerf(const float *a, size_t n, float x);
double a_hornerr(const double *a, size_t n, double x);
float a_hornerrf(const float *a, size_t n, float x);

__END_DECLS

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define a_horner(a, n, x) \
    _Generic((x),         \
             default      \
             : a_horner,  \
               float      \
             : a_hornerf)(a, n, x)
#define a_hornerr(a, n, x) \
    _Generic((x),          \
             default       \
             : a_hornerr,  \
               float       \
             : a_hornerrf)(a, n, x)
#endif /* __STDC_VERSION__ */

/* Enddef to prevent recursive inclusion */
#endif /* __A_POLY_H__ */
