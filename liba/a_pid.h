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

#undef __A_PID_T
/*!
 @brief          Instance structure for the floating-point PID Control
*/
#define __A_PID_T(def, type)                              \
    typedef struct def##_t                                \
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
    } def##_t
__A_PID_T(a_pid, double);
__A_PID_T(a_pidf, float);
#undef __A_PID_T

__BEGIN_DECLS

/*!
 @brief          Initialize function for the floating-point PID Control
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
extern void a_pid_init(a_pid_t *ctx, a_pid_mode_t mode, const double kpid[3], double omin, double omax, double omaxi);
extern void a_pidf_init(a_pidf_t *ctx, a_pid_mode_t mode, const float kpid[3], float omin, float omax, float omaxi);

/*!
 @brief          Process function for the floating-point PID Control
 @param[in,out]  ctx: points to an instance of the floating-point PID Control structure
 @param[in]      ref: reference point
 @param[in]      set: set point
 @return         Output
*/
extern double a_pid_process(a_pid_t *ctx, double ref, double set);
extern float a_pidf_process(a_pidf_t *ctx, float ref, float set);

__END_DECLS

#undef __A_PID_RESET
/*!
 @brief          Reset function for the floating-point PID Control
*/
#define __A_PID_RESET(def, func)            \
    __STATIC_INLINE                         \
    void func(def##_t *ctx)                 \
    {                                       \
        ctx->x[0] = ctx->x[1] = ctx->y = 0; \
    }
__A_PID_RESET(a_pid, a_pid_reset)
__A_PID_RESET(a_pidf, a_pidf_reset)
#undef __A_PID_RESET

#undef __A_PID_POS
/*!
 @brief          Initialize function for the floating-point position PID Control
*/
#define __A_PID_POS(def, type, init, func)                                        \
    __STATIC_INLINE                                                               \
    void func(def##_t *ctx, const type kpid[3], type omin, type omax, type omaxi) \
    {                                                                             \
        init(ctx, A_PID_POS, kpid, omin, omax, omaxi);                            \
    }
__A_PID_POS(a_pid, double, a_pid_init, a_pid_pos)
__A_PID_POS(a_pidf, float, a_pidf_init, a_pidf_pos)
#undef __A_PID_POS

#undef __A_PID_INC
/*!
 @brief          Initialize function for the floating-point incremental PID Control
*/
#define __A_PID_INC(def, type, init, func)                            \
    __STATIC_INLINE                                                   \
    void func(def##_t *ctx, const type kpid[3], type omin, type omax) \
    {                                                                 \
        init(ctx, A_PID_INC, kpid, omin, omax, 0);                    \
    }
__A_PID_INC(a_pid, double, a_pid_init, a_pid_inc)
__A_PID_INC(a_pidf, float, a_pidf_init, a_pidf_inc)
#undef __A_PID_INC

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_PID_H__ */

/* END OF FILE */
