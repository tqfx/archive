/*!
 @file a_mean.h
 @brief mean calculation
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MEAN_H__
#define __A_MEAN_H__

#include "liba.h"

/*!
 @brief Instance enumeration for the mean calculation
*/
typedef enum a_mean_e
{
    A_MEAN_ARITHMETIC, //!< arithmetic mean
    A_MEAN_GEOMETRIC,  //!< geometric mean
    A_MEAN_HARMONIC,   //!< harmonic mean
    A_MEAN_SQUARE,     //!< square mean
    A_MEAN_ALL,        //!< all mean
} a_mean_e;

#undef __A_MEAN_T
/*!
 @brief Instance structure for the mean calculation
*/
#define __A_MEAN_T(def, type) \
    typedef struct def##_s    \
    {                         \
        type out;             \
        size_t num;           \
        a_mean_e mode;        \
    } def##_s
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
__A_MEAN_T(a_mean, double);
__A_MEAN_T(a_meanf, float);
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */
#undef __A_MEAN_T

__BEGIN_DECLS

#undef __A_MEAN
/*!
 @brief function for the mean calculation
*/
#define __A_MEAN(def, type)                                                       \
    void def##_init(def##_s *ctx, a_mean_e mode) __NONNULL((1));                  \
    void def##_process(def##_s *ctx, const type *dat, size_t num) __NONNULL((1)); \
    type def##_done(def##_s *ctx) __NONNULL_ALL;
__A_MEAN(a_mean, double)
__A_MEAN(a_meanf, float)
#undef __A_MEAN

__END_DECLS

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define a_mean_init(ctx, mode) \
    _Generic((ctx),            \
             default           \
             : a_mean_init,    \
               a_meanf_s *     \
             : a_meanf_init)(ctx, mode)
#define a_mean_process(ctx, dat, num) \
    _Generic((ctx),                   \
             default                  \
             : a_mean_process,        \
               a_meanf_s *            \
             : a_meanf_process)(ctx, dat, num)
#define a_mean_done(ctx)    \
    _Generic((ctx),         \
             default        \
             : a_mean_done, \
               a_meanf_s *  \
             : a_meanf_done)(ctx)
#endif /* __STDC_VERSION__ */

/* Enddef to prevent recursive inclusion */
#endif /* __A_MEAN_H__ */
