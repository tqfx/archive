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
 - positional PID controller
 \f{aligned}{
  u(k) &= K_p e(k) + q\sum^k_{i=0} K_i e(i) + K_d [e(k)-e(k-1)] \\
       &= (K_p+K_d) e(k) + q\sum^k_{i=0}K_i e(i) + (-K_d) e(k-1) \\
       &\begin{cases}q=0&|\sum\limits^{k-1}_{i=0}K_ie(i)|>E \bigvee
       [\sum\limits^{k-1}_{i=0}K_ie(i)]K_ke(k)>0 \\ q=1\end{cases}
 \f}
 - incremental PID controller
 \f{aligned}{
  \Delta u(k) &= K_p [e(k)-e(k-1)] + K_i e(k) + K_d [e(k)+e(k-2)-2e(k-1)] \\
              &= (K_p+K_i+K_d) e(k) + (-K_p-2K_i) e(k-1) + K_d e(k-2)
 \f}
 https://en.wikipedia.org/wiki/PID_controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_PID_H
#define A_PID_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_PID proportional integral derivative controller
 @{
*/

#define A_PID_NUM_BITS 8
#define A_PID_NUM_MASK ((1U << A_PID_NUM_BITS) - 1U)
#define A_PID_REG_BITS 8
#define A_PID_REG_MASK ((1U << A_PID_REG_BITS) - 1U)
#define A_PID_MODE_BITS 2
#define A_PID_MODE_MASK ((1U << A_PID_MODE_BITS) - 1U)

/*!
 @brief instance enumeration for PID controller mode
*/
typedef enum a_pid_e
{
    A_PID_OFF, //!< turn off PID controller
    A_PID_POS, //!< positional PID controller
    A_PID_INC, //!< incremental PID controller
} a_pid_e;

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* diagnostic */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */

/*!
 @brief instance structure for PID controller
*/
typedef struct a_pid_s
{
    a_real_t dt; //!< sampling time unit(s)
    a_real_t kp; //!< proportional constant
    a_real_t ki; //!< integral constant
    a_real_t kd; //!< derivative constant
    a_real_u out; //!< controller output
    a_real_u sum; //!< (integral) output item sum
    a_real_u fdb; //!< cache feedback
    a_real_u ec; //!< error change
    a_real_u e; //!< error input
    a_real_t outmin; //!< minimum final output
    a_real_t outmax; //!< maximum final output
    a_real_t summax; //!< maximum integral output
    a_uint_t num; //!< number register
    a_uint_t reg; //!< status register
} a_pid_s;

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC a_void_t a_pid_set_dt(a_pid_s *ctx, a_real_t dt);
A_PUBLIC a_real_t a_pid_dt(const a_pid_s *ctx);
A_PUBLIC a_void_t a_pid_set_kp(a_pid_s *ctx, a_real_t ki);
A_PUBLIC a_real_t a_pid_kp(const a_pid_s *ctx);
A_PUBLIC a_void_t a_pid_set_ki(a_pid_s *ctx, a_real_t ki);
A_PUBLIC a_real_t a_pid_ki(const a_pid_s *ctx);
A_PUBLIC a_void_t a_pid_set_kd(a_pid_s *ctx, a_real_t kd);
A_PUBLIC a_real_t a_pid_kd(const a_pid_s *ctx);
A_PUBLIC a_void_t a_pid_set_num(a_pid_s *ctx, a_uint_t num);
A_PUBLIC a_uint_t a_pid_num(const a_pid_s *ctx);
A_PUBLIC a_void_t a_pid_set_reg(a_pid_s *ctx, a_uint_t reg);
A_PUBLIC a_uint_t a_pid_reg(const a_pid_s *ctx);
A_PUBLIC a_void_t a_pid_set_mode(a_pid_s *ctx, a_uint_t mode);
A_PUBLIC a_uint_t a_pid_mode(const a_pid_s *mode);

/*!
 @brief turn off PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_PUBLIC a_pid_s *a_pid_off(a_pid_s *ctx);

/*!
 @brief incremental PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_PUBLIC a_pid_s *a_pid_inc(a_pid_s *ctx);

/*!
 @brief positional PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] max maximum intergral output
*/
A_PUBLIC a_pid_s *a_pid_pos(a_pid_s *ctx, a_real_t max);

/*!
 @brief set proportional integral derivative constant for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] kp proportional constant
 @param[in] ki integral constant
 @param[in] kd derivative constant
*/
A_PUBLIC a_pid_s *a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd);

/*!
 @brief set buffer for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] num number of controllers output
 @param[in] out points to controllers output
 @param[in] fdb points to cache feedback buffer
 @param[in] sum points to (integral) output buffer
 @param[in] ec points to error change buffer
 @param[in] e points to error input buffer
*/
A_PUBLIC a_pid_s *a_pid_setp(a_pid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e);

/*!
 @brief initialize function for PID controller, default is turn off
 @param[in,out] ctx points to an instance of PID controller
 @param[in] dt sampling time unit(s)
 @param[in] min minimum output
 @param[in] max maximum output
*/
A_PUBLIC a_pid_s *a_pid_init(a_pid_s *ctx, a_real_t dt, a_real_t min, a_real_t max);

/*!
 @brief calculate function for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set setpoint
 @param[in] fdb feedback
 @return output
  @retval set when PID controller is off
*/
A_PUBLIC a_real_t a_pid_outv(a_pid_s *ctx, a_real_t set, a_real_t fdb);

/*!
 @brief calculate function for PID controller
 @param[in,out] ctx points to an instance of PID controller
 @param[in] set points to setpoint
 @param[in] fdb points to feedback
 @return points to output
  @retval set when PID controller is off
*/
A_PUBLIC a_real_t *a_pid_outp(a_pid_s *ctx, a_real_t *set, a_real_t *fdb);

/*!
 @brief terminate function for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_PUBLIC a_pid_s *a_pid_exit(a_pid_s *ctx);

/*!
 @brief zero function for PID controller
 @param[in,out] ctx points to an instance of PID controller
*/
A_PUBLIC a_pid_s *a_pid_zero(a_pid_s *ctx);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#define a_pid_dt(ctx) ((ctx)->dt)
#define a_pid_set_kp(ctx, val) ((ctx)->kp = (val))
#define a_pid_kp(ctx) ((ctx)->kp)
#define a_pid_set_ki(ctx, val) ((ctx)->ki = (val) * (ctx)->dt)
#define a_pid_ki(ctx) ((ctx)->ki / (ctx)->dt)
#define a_pid_set_kd(ctx, val) ((ctx)->kd = (val) / (ctx)->dt)
#define a_pid_kd(ctx) ((ctx)->kd * (ctx)->dt)
#define a_pid_set_num(ctx, val) ((void)((ctx)->num &= ~A_PID_NUM_MASK), (ctx)->num |= (val)&A_PID_NUM_MASK)
#define a_pid_num(ctx) ((ctx)->num & A_PID_NUM_MASK)
#define a_pid_set_reg(ctx, val) ((void)((ctx)->reg &= ~A_PID_REG_MASK), (ctx)->reg |= (val)&A_PID_REG_MASK)
#define a_pid_reg(ctx) ((ctx)->reg & A_PID_REG_MASK)
#define a_pid_set_mode(ctx, val) ((void)((ctx)->reg &= ~A_PID_MODE_MASK), (ctx)->reg |= (val)&A_PID_MODE_MASK)
#define a_pid_mode(ctx) ((ctx)->reg & A_PID_MODE_MASK)

/*! @} A_PID */

#endif /* A_PID_H */
