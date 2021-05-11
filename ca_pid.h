/**
 * *****************************************************************************
 * @file         ca_pid.c/h
 * @brief        Proportional Integral Derivative Algorithm
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CA_PID_H__
#define __CA_PID_H__

/* Includes ------------------------------------------------------------------*/
#include "ca.h"

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/

/**
 * @ingroup        CA
 * @defgroup       CA_PID Proportional Integral Derivative Group
 * @addtogroup     CA_PID
 * @{
*/

/**
 * @enum           ca_pid_mode_e
 * @brief          Instance enumeration for the PID Control Mode
*/
typedef enum
{
    CA_PID_POSITION, /* Position pid control    */
    CA_PID_DELTA,    /* Incremental pid control */

} ca_pid_mode_e;

/**
 * @struct         ca_pid_f32_t
 * @brief          Instance structure for the floating-point PID Control
*/
typedef struct
{
    ca_pid_mode_e mode; /* Mode of PID Control */

    float omin;  /* Minimum output           */
    float omax;  /* Maximum output           */
    float omaxi; /* Maximum intergral output */

    /**
     * @ref CA_PID_POSITION
     * y[n] = Kp * x[0] + Kd * (x[0]-x[1])
     *      + (|ei| < max || ei * x[0] < 0) ? Ki * x[0] : 0
     * y[n] = a[0] * x[0] + a[1] * x[1]
     *      + (|ei| < max || ei * x[0] < 0) ? a[2] * x[0] : 0
     * a[0] = Kp + Kd
     * a[1] = - Kd
     * a[2] = Ki
     * @ref CA_PID_DELTA
     * y[n] = y[n-1] + Kp * (x[0]-x[1]) + Ki * x[1] + Kd * (x[0]-2*x[1]+x[2])
     * y[n] = y[n-1] + a[0] * x[0] + a[1] * x[1] + a[2] * x[2]
     * a[0] = Kp + Ki + Kd
     * a[1] = -Kp - 2 * Kd
     * a[2] = Kd
    */
    float a[3]; /* Derived gain */

    /**
     * 0 (last) 1 (previous last)
     * @ref CA_PID_POSITION
     * 2 integral output
     * @ref CA_PID_DELTA
     * 2 all output
    */
    float x[3]; /* State array */

} ca_pid_f32_t;

/**
 * @}              End of CA_PID group
*/

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief          Initialization function for the floating-point PID Control
 * @param[in,out]  pid: An instance of the floating-point PID Control structure
 * @param[in]      mode: CA_PID_POSITION: position pid control \n
 *                       CA_PID_DELTA: incremental pid control
 * @param[in]      k: 0 (Proportional constant)
 *                    1 (Integral constant)
 *                    2 (Derivative constant)
 * @param[in]      omin: Minimum output
 * @param[in]      omax: Maximum output
 * @param[in]      ...: Maximum intergral output
*/
extern void ca_pid_f32_init(ca_pid_f32_t *pid,
                            ca_pid_mode_e mode,
                            const float   k[3],
                            float         omin,
                            float         omax,
                            ...);

/**
 * @brief          Process function for the floating-point PID Control
 * @param[in,out]  pid: An instance of the floating-point PID Control structure
 * @param[in]      ref: Reference point
 * @param[in]      set: Set point
 * @return         float Output
*/
extern float ca_pid_f32(ca_pid_f32_t *pid,
                        float         ref,
                        float         set);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

/**
 * @addtogroup     CA_PID
 * @{
*/

/**
 * @brief          Reset function for the floating-point PID Control
 * @param[in,out]  pid: An instance of the floating-point PID Control structure
*/
static inline void ca_pid_f32_reset(ca_pid_f32_t *pid)
{
    /* Reset buffer */
    pid->x[0] = pid->x[1] = pid->x[2] = 0;
}

/**
 * @brief          Initialization function for the position PID Control
 * @param[in,out]  pid: An instance of the floating-point PID Control structure
 * @param[in]      k: 0 (Proportional constant)
 *                    1 (Integral constant)
 *                    2 (Derivative constant)
 * @param[in]      omin: Minimum output
 * @param[in]      omax: Maximum output
 * @param[in]      omaxi: Maximum intergral output
*/
static inline void ca_pid_f32_position(ca_pid_f32_t *pid,
                                       const float   k[3],
                                       float         omin,
                                       float         omax,
                                       float         omaxi)
{
    ca_pid_f32_init(pid, CA_PID_POSITION, k, omin, omax, omaxi);
}

/**
 * @brief          Initialization function for the incremental PID Control
 * @param[in,out]  pid: An instance of the floating-point PID Control structure
 * @param[in]      k: 0 (Proportional constant)
 *                    1 (Integral constant)
 *                    2 (Derivative constant)
 * @param[in]      omin: Minimum output
 * @param[in]      omax: Maximum output
*/
static inline void ca_pid_f32_delta(ca_pid_f32_t *pid,
                                    const float   k[3],
                                    float         omin,
                                    float         omax)
{
    ca_pid_f32_init(pid, CA_PID_DELTA, k, omin, omax);
}

/**
 * @}              End of CA_PID group
*/

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __CA_PID_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
