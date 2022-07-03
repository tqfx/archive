/*!
 @file real.h
 @brief real number
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __A_REAL_H__
#define __A_REAL_H__

#include "def.h"

/*!
 @ingroup A
 @addtogroup A_REAL real number
 @{
*/

#if A_DEF_FLT == 0

/*! @brief real number stored using `float` */
typedef float a_real_t;

/*!
 @brief expands to a floating-point constant expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_C(X) X##F
/*!
 @brief expands to a floating-point function expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_F(F, ...) F##f(__VA_ARGS__)

/*! @brief Format constants for the fprintf family of functions */
#define A_REAL_PRI(F, ...) "%" F __VA_ARGS__
/*! @brief Format constants for the fscanf family of functions */
#define A_REAL_SCN(F, ...) "%" F __VA_ARGS__

#elif A_DEF_FLT == 1

/*! @brief real number stored using `double` */
typedef double a_real_t;

/*!
 @brief expands to a floating-point constant expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_C(X) X
/*!
 @brief expands to a floating-point function expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_F(F, ...) F(__VA_ARGS__)

/*! @brief Format constants for the fprintf family of functions */
#define A_REAL_PRI(F, ...) "%" F __VA_ARGS__
/*! @brief Format constants for the fscanf family of functions */
#define A_REAL_SCN(F, ...) "%" F "l" __VA_ARGS__

#elif A_DEF_FLT == 2

/*! @brief real number stored using `long double` */
typedef long double a_real_t;

/*!
 @brief expands to a floating-point constant expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_C(X) X##L
/*!
 @brief expands to a floating-point function expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_F(F, ...) F##l(__VA_ARGS__)

/*! @brief Format constants for the fprintf family of functions */
#define A_REAL_PRI(F, ...) "%" F "L" __VA_ARGS__
/*! @brief Format constants for the fscanf family of functions */
#define A_REAL_SCN(F, ...) "%" F "L" __VA_ARGS__

#endif /* A_DEF_FLT */

#define a_real_add(lhs, rhs) ((lhs) + (rhs)) //!< \f$ \texttt{lhs} + \texttt{rhs} \f$
#define a_real_sub(lhs, rhs) ((lhs) - (rhs)) //!< \f$ \texttt{lhs} - \texttt{rhs} \f$
#define a_real_mul(lhs, rhs) ((lhs) * (rhs)) //!< \f$ \texttt{lhs} \times \texttt{rhs} \f$
#define a_real_div(lhs, rhs) ((lhs) / (rhs)) //!< \f$ \texttt{lhs} \div   \texttt{rhs} \f$

/*!
 @} A_REAL
*/

#endif /* __A_REAL_H__ */
