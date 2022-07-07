/*!
 @file math.h
 @brief internal mathematical algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __A_SRC_MATH_H__
#define __A_SRC_MATH_H__

#include "a/math.h"

#undef P_E
#undef P_LOG2E
#undef P_LOG10E
#undef P_LN2
#undef P_LN10
#undef P_PI
#undef P_PI_2
#undef P_PI_4
#undef P_1_PI
#undef P_2_PI
#undef P_2_SQRTPI
#undef P_SQRT2
#undef P_SQRT1_2
#define P_E A_E
#define P_LOG2E A_LOG2E
#define P_LOG10E A_LOG10E
#define P_LN2 A_LN2
#define P_LN10 A_LN10
#define P_PI A_PI
#define P_PI_2 A_PI_2
#define P_PI_4 A_PI_4
#define P_1_PI A_1_PI
#define P_2_PI A_2_PI
#define P_2_SQRTPI A_2_SQRTPI
#define P_SQRT2 A_SQRT2
#define P_SQRT1_2 A_SQRT1_2

#undef DBL_C
#undef FLT_C
#undef LDBL_C
#define DBL_C(X) A_DBL_C(X)
#define FLT_C(X) A_FLT_C(X)
#define LDBL_C(X) A_LDBL_C(X)

#undef DBL_F
#undef FLT_F
#undef LDBL_F
#define DBL_F(F, ...) A_DBL_F(F, __VA_ARGS__)
#define FLT_F(F, ...) A_FLT_F(F, __VA_ARGS__)
#define LDBL_F(F, ...) A_LDBL_F(F, __VA_ARGS__)

#undef SQ
#undef ABS
#undef SGN
#define SQ(x) A_SQ(x)
#define ABS(x) A_ABS(x)
#define SGN(x) A_SGN(x)

#endif /* __A_SRC_MATH_H__ */
