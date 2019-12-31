/*!
 @file fpid.h
 @brief Fuzzy Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_FPID_H__
#define __A_FPID_H__

#include "mf.h"
#include "pid.h"

#pragma pack(push)
#pragma pack(4)
/*!
 @brief Instance structure for Fuzzy PID control
*/
typedef struct a_fpid_s
{
    a_pid_s pid[1]; //!< Instance structure for PID control

    uint32_t num; //!< Number of rulesbase rows and columns

    const a_real_t *tkp; //!< Pointer to Kp's rule base table, the rule base must be square
    const a_real_t *tki; //!< Pointer to Ki's rule base table, the rule base must be square
    const a_real_t *tkd; //!< Pointer to Kd's rule base table, the rule base must be square
    const a_real_t *tmf; //!< Pointer to membership function parameter table, an array terminated by @ref A_MF_NONE

    unsigned int *idx; //!< The memory cache for membership index
    /*!< The length must be greater than or equal to twice the maximum number triggered by the rule */
    a_real_t *ms; //!< The memory cache for membership
    /*!< The length must be greater than or equal to twice the maximum number triggered by the rule */
    a_real_t *mat; //!< The memory cache for matrix of the membership outer product of e and ec

    a_real_t (*opt)(a_real_t, a_real_t); //!< Fuzzy relational operator

    a_real_t sigma; //!< The coefficient of the input, ((num-1)>>1<<1)/(Vmax-Vmin)
    a_real_t alpha; //!< The coefficient of the output, (Umax-Umin)/((num-1)>>1<<1)

    a_real_t kp; //!< Base proportional constant
    a_real_t ki; //!< Base integral constant
    a_real_t kd; //!< Base derivative constant
} a_fpid_s;
#pragma pack(pop)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief Initialize function for Fuzzy PID control, default setting is off
 @param[in,out] ctx points to an instance of Fuzzy PID control structure
 @param[in] ts Sample time unit(s)
 @param[in] num Number of rulesbase rows and columns
 @param[in] tmf Pointer to membership function parameter table, an array terminated by @ref A_MF_NONE
 @param[in] tkp Pointer to Kp's rule base table, the rule base must be square
 @param[in] tki Pointer to Ki's rule base table, the rule base must be square
 @param[in] tkd Pointer to Kd's rule base table, the rule base must be square
 @param[in] vmin Mininum input
 @param[in] vmax Maxinum input
 @param[in] umin Mininum output
 @param[in] umax Maxinum output
*/
A_PUBLIC void a_fpid_init(a_fpid_s *ctx, a_real_t ts, unsigned int num, const a_real_t *tmf,
                          const a_real_t *tkp, const a_real_t *tki, const a_real_t *tkd,
                          a_real_t vmin, a_real_t vmax, a_real_t umin, a_real_t umax);

/*!
 @brief Process function for Fuzzy PID control
 @param[in,out] ctx points to an instance of Fuzzy PID control structure
 @param[in] set Setpoint
 @param[in] ref Feedback
 @return Output
  @retval set When PID is off
*/
A_PUBLIC a_real_t a_fpid_proc(a_fpid_s *ctx, a_real_t set, a_real_t ref);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*!
 @brief Set buffer for Fuzzy PID control
 @param[in,out] ctx points to an instance of Fuzzy PID control structure
 @param[in] ms The memory cache for membership
  The length must be greater than or equal to twice the maximum number triggered by the rule
 @param[in] idx The memory cache for membership index
  The length must be greater than or equal to twice the maximum number triggered by the rule
 @param[in] mat The memory cache for matrix of the membership outer product of e and ec
*/
A_INLINE void a_fpid_buff(a_fpid_s *ctx, a_real_t *ms, unsigned int *idx, a_real_t *mat)
{
    ctx->ms = ms;
    ctx->idx = idx;
    ctx->mat = mat;
}

/*!
 @brief Set Proportional Integral Derivative constant for Fuzzy PID control
 @param[in,out] ctx points to an instance of Fuzzy PID control structure
 @param[in] kp Proportional constant
 @param[in] ki Integral constant
 @param[in] kd Derivative constant
*/
A_INLINE void a_fpid_kpid(a_fpid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
{
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
}

/*!
 @brief Set sampling period for Fuzzy PID control
 @param[in,out] ctx points to an instance of Fuzzy PID control structure
 @param[in] ts Sample time unit(s)
*/
A_INLINE void a_fpid_time(a_fpid_s *ctx, a_real_t ts) { a_pid_time(ctx->pid, ts); }

/*!
 @brief Terminate function for Fuzzy PID control
 @param[in,out] ctx points to an instance of Fuzzy PID control structure
*/
A_INLINE void a_fpid_done(a_fpid_s *ctx) { a_pid_done(ctx->pid); }

#endif /* __A_FPID_H__ */
