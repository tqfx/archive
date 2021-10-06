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

#define a_pid_t(bit)                                            \
    typedef struct a_pid_f##bit##_t                             \
    {                                                           \
        a_pid_mode_t mode; /* Mode of PID Control      */       \
                                                                \
        float##bit##_t kp; /* Proportional constant    */       \
        float##bit##_t ki; /* Integral constant        */       \
        float##bit##_t kd; /* Derivative constant      */       \
                                                                \
        float##bit##_t omin;  /* Minimum output           */    \
        float##bit##_t omax;  /* Maximum output           */    \
        float##bit##_t omaxi; /* Maximum intergral output */    \
                                                                \
        float##bit##_t a[3]; /* Derived gain             */     \
                             /* - A_PID_POS              */     \
                             /*   - a[0] = Kp + Kd       */     \
                             /*   - a[1] = - Kd          */     \
                             /*   - a[2] = Ki            */     \
                             /* - A_PID_INC              */     \
                             /*   - a[0] = Kp + Ki + Kd  */     \
                             /*   - a[1] = -Kp - 2 * Kd  */     \
                             /*   - a[2] = Kd            */     \
                                                                \
        float##bit##_t x[2]; /* State array                  */ \
                             /* - x[0] (The last error)      */ \
                             /* - x[1] (The last last error) */ \
                                                                \
        float##bit##_t y; /* Cache variable              */     \
                          /* - A_PID_POS integral output */     \
                          /* - A_PID_INC all output      */     \
    } a_pid_f##bit##_t
a_pid_t(32);
a_pid_t(64);
#undef a_pid_t

__BEGIN_DECLS

#define a_pid_init(bit, ctx, mode, kpid, omin, omax, omaxi)       \
    extern void a_pid_f##bit##_init(a_pid_f##bit##_t *ctx,        \
                                    const a_pid_mode_t mode,      \
                                    const float##bit##_t kpid[3], \
                                    const float##bit##_t omin,    \
                                    const float##bit##_t omax,    \
                                    const float##bit##_t omaxi)
a_pid_init(32, ctx, mode, kpid, omin, omax, omaxi);
a_pid_init(64, ctx, mode, kpid, omin, omax, omaxi);
#undef a_pid_init

#define a_pid(bit, ctx, ref, set)                                \
    extern float##bit##_t a_pid_f##bit(a_pid_f##bit##_t *ctx,    \
                                       const float##bit##_t ref, \
                                       const float##bit##_t set)
a_pid(32, ctx, ref, set);
a_pid(64, ctx, ref, set);
#undef a_pid

__END_DECLS

#define __A_PID_RESET(bit, ctx)                      \
    __STATIC_INLINE                                  \
    void a_pid_f##bit##_reset(a_pid_f##bit##_t *ctx) \
    {                                                \
        /* Reset buffer */                           \
        ctx->x[0] = ctx->x[1] = ctx->y = 0;          \
    }
__A_PID_RESET(32, ctx)
__A_PID_RESET(64, ctx)
#undef __A_PID_RESET

#define __A_PID_POS(bit, ctx, kpid, omin, omax, omaxi)                \
    __STATIC_INLINE                                                   \
    void a_pid_f##bit##_pos(a_pid_f##bit##_t *ctx,                    \
                            const float##bit##_t kpid[3],             \
                            const float##bit##_t omin,                \
                            const float##bit##_t omax,                \
                            const float##bit##_t omaxi)               \
    {                                                                 \
        a_pid_f##bit##_init(ctx, A_PID_POS, kpid, omin, omax, omaxi); \
    }
__A_PID_POS(32, ctx, kpid, omin, omax, omaxi)
__A_PID_POS(64, ctx, kpid, omin, omax, omaxi)
#undef __A_PID_POS

#define __A_PID_INC(bit, ctx, kpid, omin, omax)                   \
    __STATIC_INLINE                                               \
    void a_pid_f##bit##_inc(a_pid_f##bit##_t *ctx,                \
                            const float##bit##_t kpid[3],         \
                            const float##bit##_t omin,            \
                            const float##bit##_t omax)            \
    {                                                             \
        a_pid_f##bit##_init(ctx, A_PID_INC, kpid, omin, omax, 0); \
    }
__A_PID_INC(32, ctx, kpid, omin, omax)
__A_PID_INC(64, ctx, kpid, omin, omax)
#undef __A_PID_INC

/*!
 @ingroup        LIBA_PID
 @{
*/

/*!
 @brief          Instance structure for the floating-point PID Control
 @param[in]      bit: bits for the floating-point data
*/
#define a_pid_t(bit) a_pid_f##bit##_t

/*!
 @brief          Initialization function for the floating-point PID Control
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      mode: The mode of PID Control
  @arg @ref      A_PID_POS position pid control
  @arg @ref      A_PID_INC incremental pid control
 @param[in]      kpid: constant array
  @arg           kpid[0] (Proportional constant)
  @arg           kpid[1] (Integral constant)
  @arg           kpid[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
#define a_pid_init(bit, ctx, mode, kpid, omin, omax, omaxi) \
    a_pid_f##bit##_init(ctx, mode, kpid, omin, omax, omaxi)

/*!
 @brief          Process function for the floating-point PID Control
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      ref: Reference point
 @param[in]      set: Set point
 @return         Output
*/
#define a_pid(bit, ctx, ref, set) a_pid_f##bit(ctx, ref, set)

/*!
 @brief          Reset function for the floating-point PID Control
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
*/
#define a_pid_reset(bit, ctx) a_pid_f##bit##_reset(ctx)

/*!
 @brief          Initialization function for the floating-point position PID Control
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      kpid: constant array
  @arg           kpid[0] (Proportional constant)
  @arg           kpid[1] (Integral constant)
  @arg           kpid[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
#define a_pid_pos(bit, ctx, kpid, omin, omax, omaxi) \
    a_pid_f##bit##_pos(ctx, kpid, omin, omax, omaxi)

/*!
 @brief          Initialization function for the floating-point incremental PID Control
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      kpid: constant array
  @arg           kpid[0] (Proportional constant)
  @arg           kpid[1] (Integral constant)
  @arg           kpid[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
*/
#define a_pid_inc(bit, ctx, kpid, omin, omax) \
    a_pid_f##bit##_inc(ctx, kpid, omin, omax)

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_PID_H__ */

/* END OF FILE */
