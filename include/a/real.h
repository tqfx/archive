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

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief = @f$ \boldsymbol{a} + \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_real_nadd(size_t n, a_real_t *p, a_real_t *l, a_real_t *r);
/*!
 @brief = @f$ \boldsymbol{a} - \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_real_nsub(size_t n, a_real_t *p, a_real_t *l, a_real_t *r);
/*!
 @brief = @f$ \boldsymbol{a} \times \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_real_nmul(size_t n, a_real_t *p, a_real_t *l, a_real_t *r);
/*!
 @brief = @f$ \boldsymbol{a} \div \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_real_ndiv(size_t n, a_real_t *p, a_real_t *l, a_real_t *r);

/*!
 @brief = @f$ \boldsymbol{a} + b @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r right-hand operand
*/
A_PUBLIC void a_real_nadd1(size_t n, a_real_t *p, a_real_t *l, a_real_t r);
/*!
 @brief = @f$ a - \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_real_nsubl(size_t n, a_real_t *p, a_real_t l, a_real_t *r);
/*!
 @brief = @f$ \boldsymbol{a} - b @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r right-hand operand
*/
A_PUBLIC void a_real_nsubr(size_t n, a_real_t *p, a_real_t *l, a_real_t r);
/*!
 @brief = @f$ \boldsymbol{a} \times b @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r right-hand operand
*/
A_PUBLIC void a_real_nmul1(size_t n, a_real_t *p, a_real_t *l, a_real_t r);
/*!
 @brief = @f$ a \div \boldsymbol{b} @f$
 @param n number of operaneds
 @param p points to the result
 @param l left-hand operand
 @param r points to the right-hand operand
*/
A_PUBLIC void a_real_ndivl(size_t n, a_real_t *p, a_real_t l, a_real_t *r);
/*!
 @brief = @f$ \boldsymbol{a} \div b @f$
 @param n number of operaneds
 @param p points to the result
 @param l points to the left-hand operand
 @param r right-hand operand
*/
A_PUBLIC void a_real_ndivr(size_t n, a_real_t *p, a_real_t *l, a_real_t r);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __A_REAL_H__ */
