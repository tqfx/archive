/*!
 @file fuzzy.h
 @brief Fuzzy operator
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_FUZZY_H__
#define __A_FUZZY_H__

#include "../def.h"
#include "../real.h"

#include <math.h>

/*!
 @brief Instance enumeration for fuzzy operator
*/
typedef enum a_fuzzy_e
{
    A_FUZZY_ALGEBRA = 1, //!< algebra operator
    A_FUZZY_BOUNDED = 2, //!< bounded operator
} a_fuzzy_e;

/*!
 @brief Union operator
 @param[in] t The type of operator
  @arg 0 fuzzy union
  @arg 1 algebraic sum
  @arg 2 bounded sum
 @param[in] a The first operand
 @param[in] b The second operand
 @return Result of operation
*/
A_INLINE a_real_t a_fuzzy_or(unsigned int t, a_real_t a, a_real_t b)
{
    switch (t)
    {
    case A_FUZZY_ALGEBRA:
        return a + b - a * b;
    case A_FUZZY_BOUNDED:
        return A_REAL_F(fmin, 1, a + b);
    default:
        return A_REAL_F(fmax, a, b);
    }
}

/*!
 @brief Intersection operator
 @param[in] t The type of operator
  @arg 0 fuzzy intersection
  @arg 1 algebraic product
  @arg 2 bounded product
 @param[in] a The first operand
 @param[in] b The second operand
 @return Result of operation
*/
A_INLINE a_real_t a_fuzzy_and(unsigned int t, a_real_t a, a_real_t b)
{
    switch (t)
    {
    case A_FUZZY_ALGEBRA:
        return a * b;
    case A_FUZZY_BOUNDED:
        return A_REAL_F(fmax, 0, a + b - 1);
    default:
        return A_REAL_F(fmin, a, b);
    }
}

/*!
 @brief Equilibrium operator
 @param[in] gamma gamma operator
 @param[in] a The first operand
 @param[in] b The second operand
 @return Result of operation
*/
A_INLINE a_real_t a_fuzzy_equ(a_real_t gamma, a_real_t a, a_real_t b)
{
    return A_REAL_F(pow, a * b, 1 - gamma) *
           A_REAL_F(pow, 1 - (1 - a) * (1 - b), gamma);
}

#endif /* __A_FUZZY_H__ */
