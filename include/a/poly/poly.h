/*!
 @file poly.h
 @brief polynomial
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_POLY_H__
#define __A_POLY_H__

#include "../def.h"
#include "../real.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief horner function for polynomial
 @f[
  \left\{\begin{array}{l}
  S_0 = a_0\\
  S_i = xS_{i-1} + a_i,\quad(i=1,2,\cdots,n-1,n)\\
  P(x) = S_n
  \end{array}\right.
 @f]
*/
A_PUBLIC a_real_t a_horner(const a_real_t *a, size_t n, a_real_t x);

/*!
 @brief horner function for polynomial reserved
 @f[
  \left\{\begin{array}{l}
  S_n = a_n\\
  S_i = xS_{i+1} + a_i,\quad(i=n-1,n-2,\cdots,1,0)\\
  P(x) = S_0
  \end{array}\right.
 @f]
*/
A_PUBLIC a_real_t a_hornerr(const a_real_t *a, size_t n, a_real_t x);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_POLY_H__ */
