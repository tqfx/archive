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
#define A_LIMIT(_x, _min, _max) \
    ((_min) < (_x)              \
         ? ((_x) < (_max)       \
                ? (_x)          \
                : (_max))       \
         : (_min))
#endif /* A_LIMIT */

/*!
 @endcond
*/

#undef __A_PID_INIT
#define __A_PID_INIT(_def, _type, _func)                 \
    void _func(_def##_s *_ctx,                           \
               a_pid_e _mode,                            \
               const _type _kpid[3],                     \
               _type _omin,                              \
               _type _omax,                              \
               _type _omaxi)                             \
    {                                                    \
        aassert(_ctx);                                   \
                                                         \
        _ctx->mode = _mode;                              \
        _ctx->kp = _kpid[0];                             \
        _ctx->ki = _kpid[1];                             \
        _ctx->kd = _kpid[2];                             \
        _ctx->omin = _omin;                              \
        _ctx->omax = _omax;                              \
                                                         \
        switch (_ctx->mode)                              \
        {                                                \
        case A_PID_POS:                                  \
        {                                                \
            _ctx->omaxi = _omaxi;                        \
            if (_ctx->omaxi < 0)                         \
            {                                            \
                _ctx->omaxi = -_ctx->omaxi;              \
            }                                            \
                                                         \
            _ctx->a[0] = _ctx->kp + _ctx->kd;            \
            _ctx->a[1] = -_ctx->kd;                      \
            _ctx->a[2] = _ctx->ki;                       \
        }                                                \
        break;                                           \
                                                         \
        case A_PID_INC:                                  \
        {                                                \
            _ctx->omaxi = 0;                             \
                                                         \
            _ctx->a[0] = _ctx->kp + _ctx->ki + _ctx->kd; \
            _ctx->a[1] = -_ctx->kp - 2 * _ctx->kd;       \
            _ctx->a[2] = _ctx->kd;                       \
        }                                                \
        break;                                           \
                                                         \
        default:                                         \
            break;                                       \
        }                                                \
    }
__A_PID_INIT(a_pid, double, a_pid_init)
__A_PID_INIT(a_pidf, float, a_pidf_init)
#undef __A_PID_INIT

#undef __A_PID_PROCESS
#define __A_PID_PROCESS(_def, _type, _func)                             \
    _type _func(_def##_s *_ctx, _type _ref, _type _set)                 \
    {                                                                   \
        aassert(_ctx);                                                  \
                                                                        \
        _type out = 0;                                                  \
        _type in = _set - _ref;                                         \
                                                                        \
        switch (_ctx->mode)                                             \
        {                                                               \
        case A_PID_POS:                                                 \
        {                                                               \
            /* When the limit of integration is exceeded and */         \
            /* the direction of integration is the same,     */         \
            /* the integration stops                         */         \
            if ((-_ctx->omaxi < _ctx->y && _ctx->y < _ctx->omaxi) ||    \
                _ctx->y * in < 0)                                       \
            {                                                           \
                /* y = a[2] * (\sum in) */                              \
                _ctx->y += _ctx->a[2] * in;                             \
            }                                                           \
                                                                        \
            /* out = a[0] * in + a[1] * x[0] + y */                     \
            out = _ctx->a[0] * in;                                      \
            out += _ctx->a[1] * _ctx->x[0];                             \
            out += _ctx->y;                                             \
                                                                        \
            out = A_LIMIT(out, _ctx->omin, _ctx->omax);                 \
        }                                                               \
        break;                                                          \
                                                                        \
        case A_PID_INC:                                                 \
        {                                                               \
            /* y[n] = y[n-1] + a[0] * in + a[1] * x[0] + a[2] * x[1] */ \
            _ctx->y += _ctx->a[0] * in;                                 \
            _ctx->y += _ctx->a[1] * _ctx->x[0];                         \
            _ctx->y += _ctx->a[2] * _ctx->x[1];                         \
                                                                        \
            _ctx->y = A_LIMIT(_ctx->y, _ctx->omin, _ctx->omax);         \
            out = _ctx->y;                                              \
        }                                                               \
        break;                                                          \
                                                                        \
        default:                                                        \
            break;                                                      \
        }                                                               \
                                                                        \
        _ctx->x[1] = _ctx->x[0];                                        \
        _ctx->x[0] = in;                                                \
                                                                        \
        return out;                                                     \
    }
__A_PID_PROCESS(a_pid, double, a_pid_process)
__A_PID_PROCESS(a_pidf, float, a_pidf_process)
#undef __A_PID_PROCESS

/* END OF FILE */
