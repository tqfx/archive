/*!
 @file a_pid.c
 @brief Proportional Integral Derivative Algorithm
 @details
 A proportional integral derivative controller (PID controller or three-term controller) is
 a control loop mechanism employing feedback that is widely used in industrial control systems
 and a variety of other applications requiring continuously modulated control.
 - Position pid control
 \f{aligned}{
  u(k) &= K_p e(k) + K_i \sum^k_{i=0} q e(i) + K_d [e(k) - e(k-1)] \\
       &= (K_p + K_d) e(k) + (-K_d)e(k - 1) + K_i \sum^k_{i=0} q e(i) \\
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
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_pid.h"

#include <stdarg.h>

/*!
 @cond
*/

#ifndef A_LIMIT
#define A_LIMIT(x, min, max) \
    ((min) < (x)             \
         ? ((x) < (max)      \
                ? (x)        \
                : (max))     \
         : (min))
#endif /* A_LIMIT */

/*!
 @endcond
*/

#undef a_pid_init
#undef A_PID_INIT
#define A_PID_INIT(def, type, func)                  \
    void func(def##_s *ctx, a_pid_e mode,            \
              const type kpid[3],                    \
              type omin, type omax,                  \
              type omaxi)                            \
    {                                                \
        AASSERT(ctx);                                \
                                                     \
        ctx->mode = mode;                            \
        ctx->kp = kpid[0];                           \
        ctx->ki = kpid[1];                           \
        ctx->kd = kpid[2];                           \
        ctx->omin = omin;                            \
        ctx->omax = omax;                            \
                                                     \
        switch (ctx->mode)                           \
        {                                            \
        case A_PID_POS:                              \
        {                                            \
            ctx->omaxi = omaxi;                      \
            if (ctx->omaxi < 0)                      \
            {                                        \
                ctx->omaxi = -ctx->omaxi;            \
            }                                        \
                                                     \
            ctx->a[0] = ctx->kp + ctx->kd;           \
            ctx->a[1] = -ctx->kd;                    \
            ctx->a[2] = ctx->ki;                     \
        }                                            \
        break;                                       \
                                                     \
        case A_PID_INC:                              \
        {                                            \
            ctx->omaxi = 0;                          \
                                                     \
            ctx->a[0] = ctx->kp + ctx->ki + ctx->kd; \
            ctx->a[1] = -ctx->kp - 2 * ctx->kd;      \
            ctx->a[2] = ctx->kd;                     \
        }                                            \
        break;                                       \
                                                     \
        default:                                     \
            break;                                   \
        }                                            \
    }
A_PID_INIT(a_pid, double, a_pid_init)
A_PID_INIT(a_pidf, float, a_pidf_init)
#undef A_PID_INIT

#undef a_pid_process
#undef A_PID_PROCESS
#define A_PID_PROCESS(def, type, func)                                  \
    type func(def##_s *ctx, type ref, type set)                         \
    {                                                                   \
        AASSERT(ctx);                                                   \
                                                                        \
        type out = 0;                                                   \
        type in = set - ref;                                            \
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
            ctx->y = A_LIMIT(ctx->y, ctx->omin, ctx->omax);             \
            out = ctx->y;                                               \
        }                                                               \
        break;                                                          \
                                                                        \
        default:                                                        \
            break;                                                      \
        }                                                               \
                                                                        \
        ctx->x[1] = ctx->x[0];                                          \
        ctx->x[0] = in;                                                 \
                                                                        \
        return out;                                                     \
    }
A_PID_PROCESS(a_pid, double, a_pid_process)
A_PID_PROCESS(a_pidf, float, a_pidf_process)
#undef A_PID_PROCESS
