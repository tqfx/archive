/*!
 @file a_pid.h
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

/* Define to prevent recursive inclusion */
#ifndef __A_PID_H__
#define __A_PID_H__

#include "liba.h"

/*!
 @brief Instance enumeration for PID Control Mode
*/
typedef enum a_pid_e
{
    A_PID_POS, //!< Position pid control
    A_PID_INC, //!< Incremental pid control
} a_pid_e;

#undef __A_PID_T
/*!
 @brief Instance structure for the floating-point PID Control
*/
#define __A_PID_T(def, type)                          \
    typedef struct def##_s                            \
    {                                                 \
        a_pid_e mode; /* Mode for PID Control */      \
                                                      \
        type kp; /* Proportional constant    */       \
        type ki; /* Integral constant        */       \
        type kd; /* Derivative constant      */       \
                                                      \
        type omin;  /* Minimum output           */    \
        type omax;  /* Maximum output           */    \
        type omaxi; /* Maximum intergral output */    \
                                                      \
        type a[3]; /* Derived gain             */     \
                   /* - A_PID_POS              */     \
                   /*   - a[0] = Kp + Kd       */     \
                   /*   - a[1] = - Kd          */     \
                   /*   - a[2] = Ki            */     \
                   /* - A_PID_INC              */     \
                   /*   - a[0] = Kp + Ki + Kd  */     \
                   /*   - a[1] = -Kp - 2 * Kd  */     \
                   /*   - a[2] = Kd            */     \
                                                      \
        type x[2]; /* State array                  */ \
                   /* - x[0] (The last error)      */ \
                   /* - x[1] (The last last error) */ \
                                                      \
        type y; /* Cache variable              */     \
                /* - A_PID_POS integral output */     \
                /* - A_PID_INC all output      */     \
    } def##_s
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
__A_PID_T(a_pid, double);
__A_PID_T(a_pidf, float);
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */
#undef __A_PID_T

__BEGIN_DECLS

/*!
 @brief Initialize function for the floating-point PID Control
 @param[in,out] ctx: points to an instance of the floating-point PID Control structure
 @param[in] mode: the mode for PID Control
  @arg @ref A_PID_POS position pid control
  @arg @ref A_PID_INC incremental pid control
 @param[in] kpid: constant array
  @arg 0 Proportional
  @arg 1 Integral
  @arg 2 Derivative
 @param[in] omin: Minimum output
 @param[in] omax: Maximum output
 @param[in] omaxi: Maximum intergral output
*/
void a_pid_init(a_pid_s *ctx, a_pid_e mode,
                const double kpid[3],
                double omin, double omax,
                double omaxi) __NONNULL((1, 3));
void a_pidf_init(a_pidf_s *ctx, a_pid_e mode,
                 const float kpid[3],
                 float omin, float omax,
                 float omaxi) __NONNULL((1, 3));

/*!
 @brief Process function for the floating-point PID Control
 @param[in,out] ctx: points to an instance of the floating-point PID Control structure
 @param[in] ref: reference point
 @param[in] set: set point
 @return Output
*/
double a_pid_process(a_pid_s *ctx, double ref, double set) __NONNULL((1));
float a_pidf_process(a_pidf_s *ctx, float ref, float set) __NONNULL((1));

__END_DECLS

#undef __A_PID_POS
#define __A_PID_POS(def, type, init, func)             \
    __STATIC_INLINE                                    \
    __NONNULL((1, 2))                                  \
    void func(def##_s *ctx,                            \
              const type kpid[3],                      \
              type omin, type omax,                    \
              type omaxi)                              \
    {                                                  \
        init(ctx, A_PID_POS, kpid, omin, omax, omaxi); \
    }
__A_PID_POS(a_pid, double, a_pid_init, a_pid_pos)
__A_PID_POS(a_pidf, float, a_pidf_init, a_pidf_pos)
#undef __A_PID_POS

#undef __A_PID_INC
#define __A_PID_INC(def, type, init, func)         \
    __STATIC_INLINE                                \
    __NONNULL((1, 2))                              \
    void func(def##_s *ctx,                        \
              const type kpid[3],                  \
              type omin, type omax)                \
    {                                              \
        init(ctx, A_PID_INC, kpid, omin, omax, 0); \
    }
__A_PID_INC(a_pid, double, a_pid_init, a_pid_inc)
__A_PID_INC(a_pidf, float, a_pidf_init, a_pidf_inc)
#undef __A_PID_INC

#undef __A_PID_RESET
#define __A_PID_RESET(def, func)            \
    __NONNULL_ALL                           \
    __STATIC_INLINE                         \
    void func(def##_s *ctx)                 \
    {                                       \
        AASSERT(ctx);                       \
        ctx->x[0] = ctx->x[1] = ctx->y = 0; \
    }
__A_PID_RESET(a_pid, a_pid_reset)
__A_PID_RESET(a_pidf, a_pidf_reset)
#undef __A_PID_RESET

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/*!
 @brief Initialize function for the floating-point position PID Control
*/
#define a_pid_pos(ctx, kpid, omin, omax, omaxi) \
    _Generic((ctx),                             \
             default                            \
             : a_pid_pos,                       \
               a_pidf_s *                       \
             : a_pidf_pos)(ctx, kpid, omin, omax, omaxi)
/*!
 @brief Initialize function for the floating-point incremental PID Control
*/
#define a_pid_inc(ctx, kpid, omin, omax) \
    _Generic((ctx),                      \
             default                     \
             : a_pid_inc,                \
               a_pidf_s *                \
             : a_pidf_inc)(ctx, kpid, omin, omax)
#define a_pid_init(ctx, mode, kpid, omin, omax, omaxi) \
    _Generic((ctx),                                    \
             default                                   \
             : a_pid_init,                             \
               a_pidf_s *                              \
             : a_pidf_init)(ctx, mode, kpid, omin, omax, omaxi)
#define a_pid_process(ctx, ref, set) \
    _Generic((ctx),                  \
             default                 \
             : a_pid_process,        \
               a_pidf_s *            \
             : a_pidf_process)(ctx, ref, set)
/*!
 @brief Reset function for the floating-point PID Control
*/
#define a_pid_reset(ctx)    \
    _Generic((ctx),         \
             default        \
             : a_pid_reset, \
               a_pidf_s *   \
             : a_pidf_reset)(ctx)
#endif /* __STDC_VERSION__ */

/* Enddef to prevent recursive inclusion */
#endif /* __A_PID_H__ */
