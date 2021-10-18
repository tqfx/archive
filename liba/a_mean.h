/*!
 @file           a_mean.h
 @brief          mean calculation
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_MEAN_H__
#define __A_MEAN_H__

#include "liba.h"

/*!
 @brief          Instance enumeration for the mean calculation
*/
typedef enum a_mean_mode_t
{
    A_MEAN_ARITHMETIC,  //!< arithmetic mean
    A_MEAN_GEOMETRIC,   //!< geometric mean
    A_MEAN_HARMONIC,    //!< harmonic mean
    A_MEAN_SQUARE,      //!< square mean
} a_mean_mode_t;

#undef __A_MEAN_T
/*!
 @brief          Instance structure for the mean calculation
*/
#define __A_MEAN_T(def, type) \
    typedef struct def##_t    \
    {                         \
        a_mean_mode_t mode;   \
        size_t num;           \
        type out;             \
    } def##_t
__A_MEAN_T(a_mean, double);
__A_MEAN_T(a_meanf, float);
#undef __A_MEAN_T

__BEGIN_DECLS

#undef __A_MEAN
/*!
 @brief          function for the mean calculation
*/
#define __A_MEAN(def, type)                                           \
    extern void def##_init(def##_t *ctx, a_mean_mode_t mode);         \
    extern void def##_process(def##_t *ctx, const type *p, size_t n); \
    extern type def##_done(def##_t *ctx);
__A_MEAN(a_mean, double)
__A_MEAN(a_meanf, float)
#undef __A_MEAN

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_MEAN_H__ */

/* END OF FILE */
