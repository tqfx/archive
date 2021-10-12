/*!
 @file           a_pid.h
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

/* Define to prevent recursive inclusion */
#ifndef __A_PID_H__
#define __A_PID_H__

#include "liba.h"

/*!
 @ingroup        LIBA
 @defgroup       LIBA_PID Proportional Integral Derivative
 @{
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
*/

/*!
 @brief          Instance enumeration for PID Control Mode
*/
typedef enum a_pid_mode_t
{
    A_PID_POS,  //!< Position pid control
    A_PID_INC,  //!< Incremental pid control
} a_pid_mode_t;

/*!< @} */

#undef __A_PID_T
#define __A_PID_T(id, type)                               \
    typedef struct a_pid_##id##_t                         \
    {                                                     \
        a_pid_mode_t mode; /* Mode for PID Control     */ \
                                                          \
        type kp; /* Proportional constant    */           \
        type ki; /* Integral constant        */           \
        type kd; /* Derivative constant      */           \
                                                          \
        type omin;  /* Minimum output           */        \
        type omax;  /* Maximum output           */        \
        type omaxi; /* Maximum intergral output */        \
                                                          \
        type a[3]; /* Derived gain             */         \
                   /* - A_PID_POS              */         \
                   /*   - a[0] = Kp + Kd       */         \
                   /*   - a[1] = - Kd          */         \
                   /*   - a[2] = Ki            */         \
                   /* - A_PID_INC              */         \
                   /*   - a[0] = Kp + Ki + Kd  */         \
                   /*   - a[1] = -Kp - 2 * Kd  */         \
                   /*   - a[2] = Kd            */         \
                                                          \
        type x[2]; /* State array                  */     \
                   /* - x[0] (The last error)      */     \
                   /* - x[1] (The last last error) */     \
                                                          \
        type y; /* Cache variable              */         \
                /* - A_PID_POS integral output */         \
                /* - A_PID_INC all output      */         \
    } a_pid_##id##_t
__A_PID_T(f32, float32_t);
__A_PID_T(f64, float64_t);
#undef __A_PID_T

__BEGIN_DECLS

#undef __A_PID_INIT
#define __A_PID_INIT(id, type, func)   \
    void func(a_pid_##id##_t *ctx,     \
              const a_pid_mode_t mode, \
              const type kpid[3],      \
              const type omin,         \
              const type omax,         \
              const type omaxi)
extern __A_PID_INIT(f32, float32_t, a_pid_f32_init);
extern __A_PID_INIT(f64, float64_t, a_pid_f64_init);
#undef __A_PID_INIT

#undef __A_PID
#define __A_PID(id, type, func) \
    type func(a_pid_##id##_t *ctx, const type ref, const type set)
extern __A_PID(f32, float32_t, a_pid_f32);
extern __A_PID(f64, float64_t, a_pid_f64);
#undef __A_PID

__END_DECLS

#undef __A_PID_RESET
#define __A_PID_RESET(id, func)             \
    __STATIC_INLINE                         \
    void func(a_pid_##id##_t *ctx)          \
    {                                       \
        ctx->x[0] = ctx->x[1] = ctx->y = 0; \
    }
__A_PID_RESET(f32, a_pid_f32_reset)
__A_PID_RESET(f64, a_pid_f64_reset)
#undef __A_PID_RESET

#undef __A_PID_POS
#define __A_PID_POS(id, type, init, func)              \
    __STATIC_INLINE                                    \
    void func(a_pid_##id##_t *ctx,                     \
              const type kpid[3],                      \
              const type omin,                         \
              const type omax,                         \
              const type omaxi)                        \
    {                                                  \
        init(ctx, A_PID_POS, kpid, omin, omax, omaxi); \
    }
__A_PID_POS(f32, float32_t, a_pid_f32_init, a_pid_f32_pos)
__A_PID_POS(f64, float64_t, a_pid_f64_init, a_pid_f64_pos)
#undef __A_PID_POS

#undef __A_PID_INC
#define __A_PID_INC(id, type, init, func)          \
    __STATIC_INLINE                                \
    void func(a_pid_##id##_t *ctx,                 \
              const type kpid[3],                  \
              const type omin,                     \
              const type omax)                     \
    {                                              \
        init(ctx, A_PID_INC, kpid, omin, omax, 0); \
    }
__A_PID_INC(f32, float32_t, a_pid_f32_init, a_pid_f32_inc)
__A_PID_INC(f64, float64_t, a_pid_f64_init, a_pid_f64_inc)
#undef __A_PID_INC

/*!
 @ingroup        LIBA_PID
 @{
*/

#ifndef a_pid_t
/*!
 @brief          Instance structure for the floating-point PID Control
 @param[in]      id: id for the type of the data
*/
#define a_pid_t(id) a_pid_##id##_t
#endif /* a_pid_t */

#ifndef a_pid_init
/*!
 @brief          Initialize function for the floating-point PID Control
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      mode: the mode for PID Control
  @arg @ref      A_PID_POS position pid control
  @arg @ref      A_PID_INC incremental pid control
 @param[in]      kpid: constant array
  @arg           0 Proportional
  @arg           1 Integral
  @arg           2 Derivative
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
#define a_pid_init(id, ctx, mode, kpid, omin, omax, omaxi) \
    a_pid_##id##_init(ctx, mode, kpid, omin, omax, omaxi)
#endif /* a_pid_init */

#ifndef a_pid
/*!
 @brief          Process function for the floating-point PID Control
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      ref: reference point
 @param[in]      set: set point
 @return         Output
*/
#define a_pid(id, ctx, ref, set) a_pid_##id(ctx, ref, set)
#endif /* a_pid */

#ifndef a_pid_reset
/*!
 @brief          Reset function for the floating-point PID Control
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
*/
#define a_pid_reset(id, ctx) a_pid_##id##_reset(ctx)
#endif /* a_pid_reset */

#ifndef a_pid_pos
/*!
 @brief          Initialize function for the floating-point position PID Control
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      kpid: constant array
  @arg           0 Proportional
  @arg           1 Integral
  @arg           2 Derivative
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
#define a_pid_pos(id, ctx, kpid, omin, omax, omaxi) \
    a_pid_##id##_pos(ctx, kpid, omin, omax, omaxi)
#endif /* a_pid_pos */

#ifndef a_pid_inc
/*!
 @brief          Initialize function for the floating-point incremental PID Control
 @param[in]      id: id for the type of the data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      kpid: constant array
  @arg           0 Proportional
  @arg           1 Integral
  @arg           2 Derivative
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
*/
#define a_pid_inc(id, ctx, kpid, omin, omax) \
    a_pid_##id##_inc(ctx, kpid, omin, omax)
#endif /* a_pid_inc */

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_PID_H__ */

/* END OF FILE */
