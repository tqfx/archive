/*!
 @file           a_mean.c
 @brief          mean calculation
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_mean.h"

#include <math.h>

#undef __A_MEAN_INIT
#define __A_MEAN_INIT(def, func)                \
    void func(def##_t *ctx, a_mean_mode_t mode) \
    {                                           \
        ctx->num = 0;                           \
        ctx->mode = mode;                       \
        switch (mode)                           \
        {                                       \
        case A_MEAN_GEOMETRIC:                  \
        {                                       \
            ctx->out = 1;                       \
        }                                       \
        break;                                  \
        case A_MEAN_ARITHMETIC:                 \
        case A_MEAN_HARMONIC:                   \
        case A_MEAN_SQUARE:                     \
        default:                                \
        {                                       \
            ctx->out = 0;                       \
        }                                       \
        break;                                  \
        }                                       \
    }
__A_MEAN_INIT(a_mean, a_mean_init)
__A_MEAN_INIT(a_meanf, a_meanf_init)
#undef __A_MEAN_INIT

#undef __A_MEAN_PROCESS
#define __A_MEAN_PROCESS(def, type, func)            \
    void func(def##_t *ctx, const type *p, size_t n) \
    {                                                \
        const type *q = p + n;                       \
                                                     \
        switch (ctx->mode)                           \
        {                                            \
        case A_MEAN_ARITHMETIC:                      \
        {                                            \
            for (; p != q; ++p)                      \
            {                                        \
                ctx->out += *p;                      \
            }                                        \
        }                                            \
        break;                                       \
                                                     \
        case A_MEAN_GEOMETRIC:                       \
        {                                            \
            for (; p != q; ++p)                      \
            {                                        \
                ctx->out *= *p;                      \
            }                                        \
        }                                            \
        break;                                       \
                                                     \
        case A_MEAN_HARMONIC:                        \
        {                                            \
            for (; p != q; ++p)                      \
            {                                        \
                ctx->out += 1 / *p;                  \
            }                                        \
        }                                            \
        break;                                       \
                                                     \
        case A_MEAN_SQUARE:                          \
        {                                            \
            for (; p != q; ++p)                      \
            {                                        \
                ctx->out += (*p) * (*p);             \
            }                                        \
        }                                            \
        break;                                       \
                                                     \
        default:                                     \
            break;                                   \
        }                                            \
                                                     \
        ctx->num += n;                               \
    }
__A_MEAN_PROCESS(a_mean, double, a_mean_process)
__A_MEAN_PROCESS(a_meanf, float, a_meanf_process)
#undef __A_MEAN_PROCESS

#undef __A_MEAN_DONE
#define __A_MEAN_DONE(def, type, func, sqrt, pow)         \
    type func(def##_t *ctx)                               \
    {                                                     \
        switch (ctx->mode)                                \
        {                                                 \
        case A_MEAN_ARITHMETIC:                           \
        {                                                 \
            ctx->out /= (type)ctx->num;                   \
        }                                                 \
        break;                                            \
                                                          \
        case A_MEAN_GEOMETRIC:                            \
        {                                                 \
            ctx->out = pow(ctx->out, 1 / (type)ctx->num); \
        }                                                 \
        break;                                            \
                                                          \
        case A_MEAN_HARMONIC:                             \
        {                                                 \
            ctx->out = (type)ctx->num / ctx->out;         \
        }                                                 \
        break;                                            \
                                                          \
        case A_MEAN_SQUARE:                               \
        {                                                 \
            ctx->out /= (type)ctx->num;                   \
            ctx->out = sqrt(ctx->out);                    \
        }                                                 \
        break;                                            \
                                                          \
        default:                                          \
            break;                                        \
        }                                                 \
                                                          \
        return ctx->out;                                  \
    }
__A_MEAN_DONE(a_mean, double, a_mean_done, sqrt, pow)
__A_MEAN_DONE(a_meanf, float, a_meanf_done, sqrtf, powf)
#undef __A_MEAN_DONE

/* END OF FILE */
