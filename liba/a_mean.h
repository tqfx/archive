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
#define __A_MEAN_T(_def, _type) \
    typedef struct _def##_s     \
    {                           \
        _type out;              \
        size_t num;             \
        a_mean_e mode;          \
    } _def##_s
#pragma pack(push, 4)
__A_MEAN_T(a_mean, double);
__A_MEAN_T(a_meanf, float);
#pragma pack(pop)
#undef __A_MEAN_T

__BEGIN_DECLS

#undef __A_MEAN
/*!
 @brief function for the mean calculation
*/
#define __A_MEAN(_def, _type)                                                    \
    void _def##_init(_def##_s *ctx, a_mean_e mode) __NONNULL((1));               \
    void _def##_process(_def##_s *ctx, const _type *p, size_t n) __NONNULL((1)); \
    _type _def##_done(_def##_s *ctx) __NONNULL_ALL;
__A_MEAN(a_mean, double)
__A_MEAN(a_meanf, float)
#undef __A_MEAN

__END_DECLS

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define a_mean_init(_ctx, _mode) \
    _Generic((_ctx),             \
             default             \
             : a_mean_init,      \
               a_meanf_s *       \
             : a_meanf_init)(_ctx, _mode)
#define a_mean_process(_ctx, _p, _n) \
    _Generic((_ctx),                 \
             default                 \
             : a_mean_process,       \
               a_meanf_s *           \
             : a_meanf_process)(_ctx, _p, _n)
#define a_mean_done(_ctx)   \
    _Generic((_ctx),        \
             default        \
             : a_mean_done, \
               a_meanf_s *  \
             : a_meanf_done)(_ctx)
#endif /* __STDC_VERSION__ */

/* Enddef to prevent recursive inclusion */
#endif /* __A_MEAN_H__ */

/* END OF FILE */
