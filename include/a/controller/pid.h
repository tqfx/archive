/*!
 @file pid.h
 @brief Proportional Integral Derivative Algorithm
 @details
 A proportional integral derivative controller (PID controller or three-term controller) is
 a control loop mechanism employing feedback that is widely used in industrial control systems
 and a variety of other applications requiring continuously modulated control.
 @f[
  u(t) = K_p\left[e(t)+\frac{1}{T_i}\int{e(t)}\text{dt}+T_d\frac{\text{d}e(t)}{\text{d}t}\right]
 @f]
 @f[
  u(t) = K_p\left[e(t)+\frac{T}{T_i}\sum^k_{i=0}e(i)+\frac{T_d}{T}[e(k)-e(k-1)]\right]
 @f]
 - Positional PID control
 @f{aligned}{
  u(k) &= K_p e(k) + q\sum^k_{i=0} K_i e(i) + K_d [e(k)-e(k-1)] \\
       &= (K_p+K_d) e(k) + q\sum^k_{i=0}K_i e(i) + (-K_d) e(k-1) \\
       &\begin{cases}q=0&|\sum\limits^{k-1}_{i=0}K_ie(i)|>E,[\sum\limits^{k-1}_{i=0}K_ie(i)]K_ke(k)>0 \\
                     q=1\end{cases}
 @f}
 - Incremental PID control
 @f{aligned}{
  \Delta u(k) &= K_p [e(k)-e(k-1)]
               + K_i e(k)
               + K_d [e(k)+e(k-2)-2e(k-1)] \\
              &= (K_p+K_i+K_d) e(k)
               + (-K_p-2K_i) e(k-1)
               + K_d e(k-2)
 @f}
 https://en.wikipedia.org/wiki/PID_controller
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_PID_H__
#define __A_PID_H__

#include "../def.h"

/*!
 @brief Instance enumeration for PID control mode
*/
typedef enum a_pid_e
{
    A_PID_OFF, //!< Turn off PID control
    A_PID_POS, //!< Positional PID control
    A_PID_INC, //!< Incremental PID control
} a_pid_e;

#pragma pack(push)
#pragma pack(4)
/*!
 @brief Instance structure for PID control
*/
typedef struct a_pid_s
{
    a_real_t kp;  //!< Proportional constant
    a_real_t ki;  //!< Integral constant
    a_real_t kd;  //!< Derivative constant
    a_real_t ts;  //!< Sample time unit(s)
    a_real_t min; //!< Minimum output
    a_real_t max; //!< Maximum output
    a_real_t imx; //!< Maximum intergral output
    a_real_t sum; //!< Sum output item
    a_real_t ref; //!< Cache feedback
    a_real_t out; //!< Cache output
    a_real_t ec;  //!< Error change
    a_real_t e;   //!< Error input
    uint32_t mode;
} a_pid_s;
#pragma pack(pop)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief Set sampling period for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] ts Sample time unit(s)
*/
A_PUBLIC void a_pid_time(a_pid_s *ctx, a_real_t ts);

/*!
 @brief Set Proportional Integral Derivative constant for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] kp Proportional constant
 @param[in] ki Integral constant
 @param[in] kd Derivative constant
*/
A_PUBLIC void a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd);

/*!
 @brief Initialize function for PID control, default setting is off
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] ts Sample time unit(s)
 @param[in] min Minimum output
 @param[in] max Maximum output
*/
A_PUBLIC void a_pid_init(a_pid_s *ctx, a_real_t ts, a_real_t min, a_real_t max);

/*!
 @brief Process function for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] set Setpoint
 @param[in] ref Feedback
 @return Output
  @retval set When PID is off
*/
A_PUBLIC a_real_t a_pid_proc(a_pid_s *ctx, a_real_t set, a_real_t ref);

/*!
 @brief Terminate function for PID control
 @param[in,out] ctx points to an instance of PID control structure
*/
A_PUBLIC void a_pid_done(a_pid_s *ctx);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*!
 @brief Set mode for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] mode Mode for PID control
  @arg @ref A_PID_OFF Turn off PID control
  @arg @ref A_PID_POS Positional PID control
  @arg @ref A_PID_INC Incremental PID control
*/
A_INLINE void a_pid_mode(a_pid_s *ctx, unsigned int mode) { ctx->mode = mode; }

/*!
 @brief Positional PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] imx Maximum intergral output
*/
A_INLINE void a_pid_pos(a_pid_s *ctx, a_real_t imx)
{
    ctx->imx = (imx > 0) ? imx : -imx;
    if (ctx->max < ctx->imx)
    {
        ctx->imx = ctx->max;
    }
    ctx->mode = A_PID_POS;
}

/*!
 @brief Incremental PID control
 @param[in,out] ctx points to an instance of PID control structure
*/
A_INLINE void a_pid_inc(a_pid_s *ctx) { ctx->mode = A_PID_INC; }

/*!
 @brief Turn off PID control
 @param[in,out] ctx points to an instance of PID control structure
*/
A_INLINE void a_pid_off(a_pid_s *ctx) { ctx->mode = A_PID_OFF; }

#endif /* __A_PID_H__ */
