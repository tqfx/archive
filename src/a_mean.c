/*!
 @file a_mean.c
 @brief mean calculation
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_mean.h"

#include <math.h>

#undef A_SQ
#define A_SQ(x) ((x) * (x))

#undef a_mean_init
#undef __A_MEAN_INIT
#define __A_MEAN_INIT(def, func)           \
    void func(def##_s *ctx, a_mean_e mode) \
    {                                      \
        AASSERT(ctx);                      \
        AASSERT(mode < A_MEAN_ALL);        \
                                           \
        ctx->num = 0;                      \
        ctx->mode = mode;                  \
                                           \
        switch (ctx->mode)                 \
        {                                  \
        case A_MEAN_GEOMETRIC:             \
        {                                  \
            ctx->out = 1;                  \
        }                                  \
        break;                             \
                                           \
        case A_MEAN_ARITHMETIC:            \
        case A_MEAN_HARMONIC:              \
        case A_MEAN_SQUARE:                \
        case A_MEAN_ALL:                   \
        default:                           \
        {                                  \
            ctx->out = 0;                  \
        }                                  \
        break;                             \
        }                                  \
    }
__A_MEAN_INIT(a_mean, a_mean_init)
__A_MEAN_INIT(a_meanf, a_meanf_init)
#undef __A_MEAN_INIT

#undef a_mean_process
#undef __A_MEAN_PROCESS
#define __A_MEAN_PROCESS(def, type, func)                \
    void func(def##_s *ctx, const type *dat, size_t num) \
    {                                                    \
        AASSERT(ctx);                                    \
        AASSERT(!num || dat);                            \
                                                         \
        const type *p = dat + num;                       \
                                                         \
        switch (ctx->mode)                               \
        {                                                \
        case A_MEAN_ARITHMETIC:                          \
        {                                                \
            for (; dat != p; ++dat)                      \
            {                                            \
                ctx->out += *dat;                        \
            }                                            \
        }                                                \
        break;                                           \
                                                         \
        case A_MEAN_GEOMETRIC:                           \
        {                                                \
            for (; dat != p; ++dat)                      \
            {                                            \
                ctx->out *= *dat;                        \
            }                                            \
        }                                                \
        break;                                           \
                                                         \
        case A_MEAN_HARMONIC:                            \
        {                                                \
            for (; dat != p; ++dat)                      \
            {                                            \
                ctx->out += 1 / *dat;                    \
            }                                            \
        }                                                \
        break;                                           \
                                                         \
        case A_MEAN_SQUARE:                              \
        {                                                \
            for (; dat != p; ++dat)                      \
            {                                            \
                ctx->out += A_SQ(*dat);                  \
            }                                            \
        }                                                \
        break;                                           \
                                                         \
        case A_MEAN_ALL:                                 \
        default:                                         \
            break;                                       \
        }                                                \
                                                         \
        ctx->num += num;                                 \
    }
__A_MEAN_PROCESS(a_mean, double, a_mean_process)
__A_MEAN_PROCESS(a_meanf, float, a_meanf_process)
#undef __A_MEAN_PROCESS

#undef a_mean_done
#undef __A_MEAN_DONE
#define __A_MEAN_DONE(def, type, func, sqrt, pow)         \
    type func(def##_s *ctx)                               \
    {                                                     \
        AASSERT(ctx);                                     \
                                                          \
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
        case A_MEAN_ALL:                                  \
        default:                                          \
            break;                                        \
        }                                                 \
                                                          \
        return ctx->out;                                  \
    }
__A_MEAN_DONE(a_mean, double, a_mean_done, sqrt, pow)
__A_MEAN_DONE(a_meanf, float, a_meanf_done, sqrtf, powf)
#undef __A_MEAN_DONE
