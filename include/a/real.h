/*!
 @file real.h
 @brief real number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_REAL_H__
#define __A_REAL_H__

#include "def.h"

#if A_DEF_FLOAT == 0

typedef float a_real_t;
#define A_REAL_P
#define A_REAL_C(X)      X##F
#define A_REAL_F(F, ...) F##f(__VA_ARGS__)

#elif A_DEF_FLOAT == 1

typedef double a_real_t;
#define A_REAL_P
#define A_REAL_C(X)      X
#define A_REAL_F(F, ...) F(__VA_ARGS__)

#elif A_DEF_FLOAT == 2

typedef long double a_real_t;
#define A_REAL_P         "L"
#define A_REAL_C(X)      X##L
#define A_REAL_F(F, ...) F##l(__VA_ARGS__)

#endif /* A_DEF_FLOAT */

#define a_real_add(l, r) ((l) + (r))
#define a_real_sub(l, r) ((l) - (r))
#define a_real_mul(l, r) ((l) * (r))
#define a_real_div(l, r) ((l) / (r))

#endif /* __A_REAL_H__ */
