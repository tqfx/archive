/*!
 @file           a_pid.c
 @brief          Proportional Integral Derivative Algorithm
 @details        A proportional integral derivative controller
                 (PID controller or three-term controller) is a control loop
                 mechanism employing feedback that is widely used in industrial
                 control systems and a variety of other applications requiring
                 continuously modulated control.
                 - Position pid control
 \f{aligned}{
    u(k) &= K_p e(k) + K_i \sum^k_{i=0} q e(i) + K_d [e(k) - e(k-1)]\\
         &= (K_p + K_d) e(k) + (-K_d)e(k - 1) + K_i \sum^k_{i=0} q e(i)\\
         &\begin{cases}q = 0 & |K_i \sum\limits^{k-1}_{i=0} e(i)| > E, e(k)e(k - 1) < 0 \\
          q = 1\end{cases}
 \f}
                 - Incremental pid control
 \f{aligned}{
    \Delta u(k) &= K_p [e(k) - e(k - 1)]
                 + K_i e(k)
                 + K_d [e(k) + e(k - 2) - 2 e(k - 1)] \\
                &= (K_p + K_i + K_d) e(k)
                 + (-K_p - 2 K_i) e(k - 1)
                 + K_d e(k - 2)
 \f}
                 https://en.wikipedia.org/wiki/PID_controller
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_pid.h"

#include <stdarg.h>

/*!
 @cond
*/

#ifndef __A_MATH_H__
/* Limiting macro */
#define A_LIMIT(x, min, max) \
    ((min) < (x)             \
         ? ((x) < (max)      \
                ? (x)        \
                : (max))     \
         : (min))
#endif /* __A_MATH_H__ */

/*!
 @endcond
*/

#undef __A_PID_INIT
#define __A_PID_INIT(bit)                                  \
    void a_pid_f##bit##_init(a_pid_f##bit##_t *ctx,        \
                             const a_pid_mode_t mode,      \
                             const float##bit##_t kpid[3], \
                             const float##bit##_t omin,    \
                             const float##bit##_t omax,    \
                             const float##bit##_t omaxi)   \
    {                                                      \
        /* Set mode of PID Control */                      \
        ctx->mode = mode;                                  \
        /* Set Proportional constant */                    \
        ctx->kp = kpid[0];                                 \
        /* Set Integral constant */                        \
        ctx->ki = kpid[1];                                 \
        /* Set Derivative constant */                      \
        ctx->kd = kpid[2];                                 \
        /* Set minimum output */                           \
        ctx->omin = omin;                                  \
        /* Set maximum output */                           \
        ctx->omax = omax;                                  \
                                                           \
        switch (ctx->mode)                                 \
        {                                                  \
        case A_PID_POS:                                    \
        {                                                  \
            /* Set maximum intergral output */             \
            ctx->omaxi = omaxi;                            \
            if (ctx->omaxi < 0)                            \
            {                                              \
                ctx->omaxi = -ctx->omaxi;                  \
            }                                              \
                                                           \
            /* Set derived gain */                         \
            ctx->a[0] = ctx->kp + ctx->kd;                 \
            ctx->a[1] = -ctx->kd;                          \
            ctx->a[2] = ctx->ki;                           \
        }                                                  \
        break;                                             \
                                                           \
        case A_PID_INC:                                    \
        {                                                  \
            /* Reset maximum intergral output */           \
            ctx->omaxi = 0;                                \
                                                           \
            /* Set derived gain */                         \
            ctx->a[0] = ctx->kp + ctx->ki + ctx->kd;       \
            ctx->a[1] = -ctx->kp - 2 * ctx->kd;            \
            ctx->a[2] = ctx->kd;                           \
        }                                                  \
        break;                                             \
                                                           \
        default:                                           \
            break;                                         \
        }                                                  \
    }
__A_PID_INIT(32)
__A_PID_INIT(64)

#undef __A_PID
#define __A_PID(bit)                                                    \
    float##bit##_t a_pid_f##bit(a_pid_f##bit##_t *ctx,                  \
                                const float##bit##_t ref,               \
                                const float##bit##_t set)               \
    {                                                                   \
        /* Output */                                                    \
        float##bit##_t out = 0;                                         \
        /* Input */                                                     \
        float##bit##_t in = set - ref;                                  \
                                                                        \
        switch (ctx->mode)                                              \
        {                                                               \
        case A_PID_POS:                                                 \
        {                                                               \
            /* When the limit of integration is exceeded and */         \
            /* the direction of integration is the same,     */         \
            /* the integration stops                         */         \
            if ((-ctx->omaxi < ctx->y && ctx->y < ctx->omaxi) ||        \
                ctx->y * in < 0)                                        \
            {                                                           \
                /* y = a[2] * (\sum in) */                              \
                ctx->y += ctx->a[2] * in;                               \
            }                                                           \
                                                                        \
            /* out = a[0] * in + a[1] * x[0] + y */                     \
            out = ctx->a[0] * in;                                       \
            out += ctx->a[1] * ctx->x[0];                               \
            out += ctx->y;                                              \
                                                                        \
            /* Restrict the output of the PID */                        \
            out = A_LIMIT(out, ctx->omin, ctx->omax);                   \
        }                                                               \
        break;                                                          \
                                                                        \
        case A_PID_INC:                                                 \
        {                                                               \
            /* y[n] = y[n-1] + a[0] * in + a[1] * x[0] + a[2] * x[1] */ \
            ctx->y += ctx->a[0] * in;                                   \
            ctx->y += ctx->a[1] * ctx->x[0];                            \
            ctx->y += ctx->a[2] * ctx->x[1];                            \
                                                                        \
            /* Restrict the output of the PID */                        \
            ctx->y = A_LIMIT(ctx->y, ctx->omin, ctx->omax);             \
            /* Export output */                                         \
            out = ctx->y;                                               \
        }                                                               \
        break;                                                          \
                                                                        \
        default:                                                        \
            break;                                                      \
        }                                                               \
                                                                        \
        /* Cache data */                                                \
        ctx->x[1] = ctx->x[0];                                          \
        ctx->x[0] = in;                                                 \
                                                                        \
        return out;                                                     \
    }
__A_PID(32)
__A_PID(64)

/* END OF FILE */
