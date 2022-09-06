/*!
 @file pid.h
 @brief proportional integral derivative controller
 @details
 A proportional integral derivative controller (PID controller or three-term controller) is
 a control loop mechanism employing feedback that is widely used in industrial control systems
 and a variety of other applications requiring continuously modulated control.
 \f[
  u(t) = K_p\left[e(t)+\frac{1}{T_i}\int{e(t)}\text{dt}+T_d\frac{\text{d}e(t)}{\text{d}t}\right]
 \f]
 \f[
  u(t) = K_p\left[e(t)+\frac{T}{T_i}\sum^k_{i=0}e(i)+\frac{T_d}{T}[e(k)-e(k-1)]\right]
 \f]
 - positional PID control
 \f{aligned}{
  u(k) &= K_p e(k) + q\sum^k_{i=0} K_i e(i) + K_d [e(k)-e(k-1)] \\
       &= (K_p+K_d) e(k) + q\sum^k_{i=0}K_i e(i) + (-K_d) e(k-1) \\
       &\begin{cases}q=0&|\sum\limits^{k-1}_{i=0}K_ie(i)|>E \bigvee
       [\sum\limits^{k-1}_{i=0}K_ie(i)]K_ke(k)>0 \\ q=1\end{cases}
 \f}
 - incremental PID control
 \f{aligned}{
  \Delta u(k) &= K_p [e(k)-e(k-1)] + K_i e(k) + K_d [e(k)+e(k-2)-2e(k-1)] \\
              &= (K_p+K_i+K_d) e(k) + (-K_p-2K_i) e(k-1) + K_d e(k-2)
 \f}
 https://en.wikipedia.org/wiki/PID_controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_PID_H__
#define __A_PID_H__

#include "a.h"

/*!
 @brief instance enumeration for PID control mode
*/
typedef enum a_pid_e
{
    A_PID_OFF, //!< turn off PID control
    A_PID_POS, //!< positional PID control
    A_PID_INC, //!< incremental PID control
} a_pid_e;

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */

/*!
 @brief instance structure for PID control
*/
typedef struct a_pid_s
{
    a_real_t ts; //!< sampling time unit(s)
    a_real_t kp; //!< proportional constant
    a_real_t ki; //!< integral constant
    a_real_t kd; //!< derivative constant
    a_real_t outmin; //!< minimum output
    a_real_t outmax; //!< maximum output
    a_real_t summax; //!< maximum integral output
    a_real_t sum; //!< (integral) output item sum
    a_real_t ref; //!< cache feedback
    a_real_t out; //!< cache output
    a_real_t ec; //!< error change
    a_real_t e; //!< error input
    a_uint_t mode;
} a_pid_s;

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief set sampling period for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] ts sampling time unit(s)
*/
A_PUBLIC void a_pid_time(a_pid_s *ctx, a_real_t ts);

/*!
 @brief set proportional integral derivative constant for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_PUBLIC void a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd);

/*!
 @brief initialize function for PID control, default setting is off
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] ts sampling time unit(s)
 @param[in] min minimum output
 @param[in] max maximum output
*/
A_PUBLIC void a_pid_init(a_pid_s *ctx, a_real_t ts, a_real_t min, a_real_t max);

/*!
 @brief process function for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] set setpoint
 @param[in] ref feedback
 @return output
  @retval set When PID is off
*/
A_PUBLIC a_real_t a_pid_proc(a_pid_s *ctx, a_real_t set, a_real_t ref);

/*!
 @brief terminate function for PID control
 @param[in,out] ctx points to an instance of PID control structure
*/
A_PUBLIC void a_pid_done(a_pid_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*!
 @brief set mode for PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] mode Mode for PID control
  @arg @ref A_PID_OFF turn off PID control
  @arg @ref A_PID_POS positional PID control
  @arg @ref A_PID_INC incremental PID control
*/
A_INLINE void a_pid_mode(a_pid_s *ctx, a_uint_t mode) { ctx->mode = mode; }

/*!
 @brief positional PID control
 @param[in,out] ctx points to an instance of PID control structure
 @param[in] max maximum intergral output
*/
A_INLINE void a_pid_pos(a_pid_s *ctx, a_real_t max)
{
    ctx->summax = (max > 0) ? max : -max;
    if (ctx->outmax < ctx->summax)
    {
        ctx->summax = ctx->outmax;
    }
    ctx->mode = A_PID_POS;
}

/*!
 @brief incremental PID control
 @param[in,out] ctx points to an instance of PID control structure
*/
A_INLINE void a_pid_inc(a_pid_s *ctx) { ctx->mode = A_PID_INC; }

/*!
 @brief turn off PID control
 @param[in,out] ctx points to an instance of PID control structure
*/
A_INLINE void a_pid_off(a_pid_s *ctx) { ctx->mode = A_PID_OFF; }

#endif /* __A_PID_H__ */
