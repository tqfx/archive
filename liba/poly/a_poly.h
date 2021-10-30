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
extern double a_horner(double *a, size_t n, double x);
extern float a_hornerf(float *a, size_t n, float x);
extern double a_hornerr(double *a, size_t n, double x);
extern float a_hornerrf(float *a, size_t n, float x);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_POLY_H__ */

/* END OF FILE */
