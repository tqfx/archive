/*!
 @file gmath.h
 @brief Generic math
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_GMATH_H__
#define __A_GMATH_H__

#include "../def.h"
#include "../complex.h"

#if defined(_MSC_VER)
#include <math.h>
#else /* !_MSC_VER */
#include <tgmath.h>
#endif /* _MSC_VER */

#if defined(_MSC_VER) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/* clang-format off */

#undef fabs
#define fabs(x)         \
    _Generic((x),       \
    float: fabsf,       \
    double: fabs,       \
    long double: fabsl, \
    a_complex_f: cabsf, \
    a_complex_d: cabs,  \
    a_complex_l: cabsl, \
    default: fabs       \
    )(x)

#undef exp
#define exp(x)          \
    _Generic((x),       \
    float: expf,        \
    double: exp,        \
    long double: expl,  \
    a_complex_f: cexpf, \
    a_complex_d: cexp,  \
    a_complex_l: cexpl, \
    default: exp        \
    )(x)

#undef log
#define log(x)          \
    _Generic((x),       \
    float: logf,        \
    double: log,        \
    long double: logl,  \
    a_complex_f: clogf, \
    a_complex_d: clog,  \
    a_complex_l: clogl, \
    default: log        \
    )(x)

#undef pow
#define pow(x, y)       \
    _Generic((x),       \
    float: powf,        \
    double: pow,        \
    long double: powl,  \
    a_complex_f: cpowf, \
    a_complex_d: cpow,  \
    a_complex_l: cpowl, \
    default: pow        \
    )(x, y)

#undef sqrt
#define sqrt(x)          \
    _Generic((x),        \
    float: sqrtf,        \
    double: sqrt,        \
    long double: sqrtl,  \
    a_complex_f: csqrtf, \
    a_complex_d: csqrt,  \
    a_complex_l: csqrtl, \
    default: sqrt        \
    )(x)

#undef sin
#define sin(x)          \
    _Generic((x),       \
    float: sinf,        \
    double: sin,        \
    long double: sinl,  \
    a_complex_f: csinf, \
    a_complex_d: csin,  \
    a_complex_l: csinl, \
    default: sin        \
    )(x)

#undef cos
#define cos(x)          \
    _Generic((x),       \
    float: cosf,        \
    double: cos,        \
    long double: cosl,  \
    a_complex_f: ccosf, \
    a_complex_d: ccos,  \
    a_complex_l: ccosl, \
    default: cos        \
    )(x)

#undef tan
#define tan(x)          \
    _Generic((x),       \
    float: tanf,        \
    double: tan,        \
    long double: tanl,  \
    a_complex_f: ctanf, \
    a_complex_d: ctan,  \
    a_complex_l: ctanl, \
    default: tan        \
    )(x)

#undef asin
#define asin(x)          \
    _Generic((x),        \
    float: asinf,        \
    double: asin,        \
    long double: asinl,  \
    a_complex_f: casinf, \
    a_complex_d: casin,  \
    a_complex_l: casinl, \
    default: asin        \
    )(x)

#undef acos
#define acos(x)          \
    _Generic((x),        \
    float: acosf,        \
    double: acos,        \
    long double: acosl,  \
    a_complex_f: cacosf, \
    a_complex_d: cacos,  \
    a_complex_l: cacosl, \
    default: acos        \
    )(x)

#undef atan
#define atan(x)          \
    _Generic((x),        \
    float: atanf,        \
    double: atan,        \
    long double: atanl,  \
    a_complex_f: catanf, \
    a_complex_d: catan,  \
    a_complex_l: catanl, \
    default: atan        \
    )(x)

#undef sinh
#define sinh(x)          \
    _Generic((x),        \
    float: sinhf,        \
    double: sinh,        \
    long double: sinhl,  \
    a_complex_f: csinhf, \
    a_complex_d: csinh,  \
    a_complex_l: csinhl, \
    default: sinh        \
    )(x)

#undef cosh
#define cosh(x)          \
    _Generic((x),        \
    float: coshf,        \
    double: cosh,        \
    long double: coshl,  \
    a_complex_f: ccoshf, \
    a_complex_d: ccosh,  \
    a_complex_l: ccoshl, \
    default: cosh        \
    )(x)

#undef tanh
#define tanh(x)          \
    _Generic((x),        \
    float: tanhf,        \
    double: tanh,        \
    long double: tanhl,  \
    a_complex_f: ctanhf, \
    a_complex_d: ctanh,  \
    a_complex_l: ctanhl, \
    default: tanh        \
    )(x)

#undef asinh
#define asinh(x)          \
    _Generic((x),         \
    float: asinhf,        \
    double: asinh,        \
    long double: asinhl,  \
    a_complex_f: casinhf, \
    a_complex_d: casinh,  \
    a_complex_l: casinhl, \
    default: asinh        \
    )(x)

#undef acosh
#define acosh(x)          \
    _Generic((x),         \
    float: acoshf,        \
    double: acosh,        \
    long double: acoshl,  \
    a_complex_f: cacoshf, \
    a_complex_d: cacosh,  \
    a_complex_l: cacoshl, \
    default: acosh        \
    )(x)

#undef atanh
#define atanh(x)          \
    _Generic((x),         \
    float: atanhf,        \
    double: atanh,        \
    long double: atanhl,  \
    a_complex_f: catanhf, \
    a_complex_d: catanh,  \
    a_complex_l: catanhl, \
    default: atanh        \
    )(x)

#undef atan2
#define atan2(y, x)      \
    _Generic((y),        \
    float: atan2f,       \
    double: atan2,       \
    long double: atan2l, \
    default: atan2       \
    )(y, x)

#undef cbrt
#define cbrt(x)         \
    _Generic((x),       \
    float: cbrtf,       \
    double: cbrt,       \
    long double: cbrtl, \
    default: cbrt       \
    )(x)

#undef ceil
#define ceil(x)         \
    _Generic((x),       \
    float: ceilf,       \
    double: ceil,       \
    long double: ceill, \
    default: ceil       \
    )(x)

#undef copysign
#define copysign(x, y)      \
    _Generic((x),           \
    float: copysignf,       \
    double: copysign,       \
    long double: copysignl, \
    default: copysign       \
    )(x, y)

#undef erf
#define erf(x)         \
    _Generic((x),      \
    float: erff,       \
    double: erf,       \
    long double: erfl, \
    default: erf       \
    )(x)

#undef erfc
#define erfc(x)         \
    _Generic((x),       \
    float: erfcf,       \
    double: erfc,       \
    long double: erfcl, \
    default: erfc       \
    )(x)

#undef exp2
#define exp2(x)         \
    _Generic((x),       \
    float: exp2f,       \
    double: exp2,       \
    long double: exp2l, \
    default: exp2       \
    )(x)

#undef expm1
#define expm1(x)         \
    _Generic((x),        \
    float: expm1f,       \
    double: expm1,       \
    long double: expm1l, \
    default: expm1       \
    )(x)

#undef fdim
#define fdim(x, y)      \
    _Generic((x),       \
    float: fdimf,       \
    double: fdim,       \
    long double: fdiml, \
    default: fdim       \
    )(x, y)

#undef floor
#define floor(x)         \
    _Generic((x),        \
    float: floorf,       \
    double: floor,       \
    long double: floorl, \
    default: floor       \
    )(x)

#undef fma
#define fma(x, y, z)   \
    _Generic((x),      \
    float: fmaf,       \
    double: fma,       \
    long double: fmal, \
    default: fma       \
    )(x, y, z)

#undef fmax
#define fmax(x, y)      \
    _Generic((x),       \
    float: fmaxf,       \
    double: fmax,       \
    long double: fmaxl, \
    default: fmax       \
    )(x, y)

#undef fmin
#define fmin(x, y)      \
    _Generic((x),       \
    float: fminf,       \
    double: fmin,       \
    long double: fminl, \
    default: fmin       \
    )(x, y)

#undef fmod
#define fmod(x, y)      \
    _Generic((x),       \
    float: fmodf,       \
    double: fmod,       \
    long double: fmodl, \
    default: fmod       \
    )(x, y)

#undef frexp
#define frexp(x, e)      \
    _Generic((x),        \
    float: frexpf,       \
    double: frexp,       \
    long double: frexpl, \
    default: frexp       \
    )(x, e)

#undef hypot
#define hypot(x, y)      \
    _Generic((x),        \
    float: hypotf,       \
    double: hypot,       \
    long double: hypotl, \
    default: hypot       \
    )(x, y)

#undef ilogb
#define ilogb(x)         \
    _Generic((x),        \
    float: ilogbf,       \
    double: ilogb,       \
    long double: ilogbl, \
    default: ilogb       \
    )(x)

#undef ldexp
#define ldexp(x, e)      \
    _Generic((x),        \
    float: ldexpf,       \
    double: ldexp,       \
    long double: ldexpl, \
    default: ldexp       \
    )(x, e)

#undef lgamma
#define lgamma(x)         \
    _Generic((x),         \
    float: lgammaf,       \
    double: lgamma,       \
    long double: lgammal, \
    default: lgamma       \
    )(x)

#undef llrint
#define llrint(x)         \
    _Generic((x),         \
    float: llrintf,       \
    double: llrint,       \
    long double: llrintl, \
    default: llrint       \
    )(x)

#undef llround
#define llround(x)         \
    _Generic((x),          \
    float: llroundf,       \
    double: llround,       \
    long double: llroundl, \
    default: llround       \
    )(x)

#undef log10
#define log10(x)         \
    _Generic((x),        \
    float: log10f,       \
    double: log10,       \
    long double: log10l, \
    default: log10       \
    )(x)

#undef log1p
#define log1p(x)         \
    _Generic((x),        \
    float: log1pf,       \
    double: log1p,       \
    long double: log1pl, \
    default: log1p       \
    )(x)

#undef log2
#define log2(x)         \
    _Generic((x),       \
    float: log2f,       \
    double: log2,       \
    long double: log2l, \
    default: log2       \
    )(x)

#undef logb
#define logb(x)         \
    _Generic((x),       \
    float: logbf,       \
    double: logb,       \
    long double: logbl, \
    default: logb       \
    )(x)

#undef lrint
#define lrint(x)         \
    _Generic((x),        \
    float: lrintf,       \
    double: lrint,       \
    long double: lrintl, \
    default: lrint       \
    )(x)

#undef lround
#define lround(x)         \
    _Generic((x),         \
    float: lroundf,       \
    double: lround,       \
    long double: lroundl, \
    default: lround       \
    )(x)

#undef nearbyint
#define nearbyint(x)         \
    _Generic((x),            \
    float: nearbyintf,       \
    double: nearbyint,       \
    long double: nearbyintl, \
    default: nearbyint       \
    )(x)

#undef nextafter
#define nextafter(from, to)  \
    _Generic((from),         \
    float: nextafterf,       \
    double: nextafter,       \
    long double: nextafterl, \
    default: nextafter       \
    )(from, to)

#undef nexttoward
#define nexttoward(from, to)  \
    _Generic((from, to),      \
    float: nexttowardf,       \
    double: nexttoward,       \
    long double: nexttowardl, \
    default: nexttoward       \
    )(x)

#undef remainder
#define remainder(x, y)      \
    _Generic((x),            \
    float: remainderf,       \
    double: remainder,       \
    long double: remainderl, \
    default: remainder       \
    )(x, y)

#undef remquo
#define remquo(x, y, q)   \
    _Generic((x),         \
    float: remquof,       \
    double: remquo,       \
    long double: remquol, \
    default: remquo       \
    )(x, y, q)

#undef rint
#define rint(x)         \
    _Generic((x),       \
    float: rintf,       \
    double: rint,       \
    long double: rintl, \
    default: rint       \
    )(x)

#undef round
#define round(x)         \
    _Generic((x),        \
    float: roundf,       \
    double: round,       \
    long double: roundl, \
    default: round       \
    )(x)

#undef scalbln
#define scalbln(x, e)      \
    _Generic((x),          \
    float: scalblnf,       \
    double: scalbln,       \
    long double: scalblnl, \
    default: scalbln       \
    )(x, e)

#undef scalbn
#define scalbn(x, e)      \
    _Generic((x),         \
    float: scalbnf,       \
    double: scalbn,       \
    long double: scalbnl, \
    default: scalbn       \
    )(x, e)

#undef tgamma
#define tgamma(x)         \
    _Generic((x),         \
    float: tgammaf,       \
    double: tgamma,       \
    long double: tgammal, \
    default: tgamma       \
    )(x)

#undef trunc
#define trunc(x)         \
    _Generic((x),        \
    float: truncf,       \
    double: trunc,       \
    long double: truncl, \
    default: trunc       \
    )(x)

/* clang-format on */
#endif /* _MSC_VER && __STDC_VERSION__ */

#endif /* __A_GMATH_H__ */
