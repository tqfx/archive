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

/* Includes ------------------------------------------------------------------*/
#include "ca_pid.h"

/* Private includes ----------------------------------------------------------*/
#include <stdarg.h>

/* Private macro -------------------------------------------------------------*/

#undef LIMIT
#define LIMIT(x, min, max) ((x) > (max)        \
                                ? (max)        \
                                : ((x) < (min) \
                                       ? (min) \
                                       : (x)))

/* Private user code ---------------------------------------------------------*/

void ca_pid_f32_init(ca_pid_f32_t *pid,
                     ca_pid_mode_e mode,
                     const float   k[3],
                     float         omin,
                     float         omax,
                     ...)
{
    va_list ap;

    /* Set mode of PID Control */
    pid->mode = mode;
    /* Set minimum output */
    pid->omin = omin;
    /* Set maximum output */
    pid->omax = omax;

    switch (pid->mode)
    {
    /**
     * y[n] = Kp * x[0] + Kd * (x[0]-x[1])
     *      + (|ei| < max || ei * x[0] < 0) ? Ki * x[0] : 0
     * y[n] = a[0] * x[0] + a[1] * x[1]
     *      + (|ei| < max || ei * x[0] < 0) ? a[2] * x[0] : 0
     * a[0] = Kp + Kd
     * a[1] = - Kd
     * a[2] = Ki
    */
    case CA_PID_POSITION:
    {
        /* Set maximum intergral output */
        va_start(ap, omax);
        pid->omaxi = (float)va_arg(ap, double);
        if (pid->omaxi < 0)
        {
            pid->omaxi = -pid->omaxi;
        }
        va_end(ap);

        /* Set derived gain */
        pid->a[0] = k[0] + k[2];
        pid->a[1] = -k[2];
        pid->a[2] = k[1];

        break;
    }
    /**
     * y[n] = y[n-1] + Kp * (x[0]-x[1]) + Ki * x[1] + Kd * (x[0]-2*x[1]+x[2])
     * y[n] = y[n-1] + a[0] * x[0] + a[1] * x[1] + a[2] * x[2]
     * a[0] = Kp + Ki + Kd
     * a[1] = -Kp - 2 * Kd
     * a[2] = Kd
    */
    case CA_PID_DELTA:
    {
        /* Reset maximum intergral output */
        pid->omaxi = 0;

        /* Set derived gain */
        pid->a[0] = k[0] + k[1] + k[2];
        pid->a[1] = -k[0] - 2 * k[2];
        pid->a[2] = k[2];

        break;
    }

    default:
        break;
    }
}

float ca_pid_f32(ca_pid_f32_t *pid,
                 float         ref,
                 float         set)
{
    /* Output */
    float out = 0;
    /* Input */
    float in = set - ref;

    switch (pid->mode)
    {
    case CA_PID_POSITION:
    {
        /**
         * When the limit of integration is exceeded and
         * the direction of integration is the same,
         * the integration stops
        */
        if ((-pid->omaxi < pid->x[2] &&
             pid->x[2] < pid->omaxi) ||
            pid->x[2] * in < 0)
        {
            pid->x[2] += pid->a[2] * in;
        }

        /* y[n] = a[0] * x[0] + a[1] * x[1] + a[2] * x[0] */
        out = pid->a[0] * in;
        out += pid->a[1] * pid->x[0];
        out += pid->x[2];

        /* Restrict the output of the PID */
        out = LIMIT(out, pid->omin, pid->omax);

        break;
    }

    case CA_PID_DELTA:
    {
        /* y[n] = y[n-1] + a[0] * x[0] + a[1] * x[1] + a[2] * x[2] */
        pid->x[2] = pid->a[0] * in;
        pid->x[2] += pid->a[1] * pid->x[0];
        pid->x[2] += pid->a[2] * pid->x[1];

        /* Restrict the output of the PID */
        pid->x[2] = LIMIT(pid->x[2], pid->omin, pid->omax);
        /* Export output */
        out = pid->x[2];

        break;
    }

    default:
        break;
    }

    /* Cache data */
    pid->x[1] = pid->x[0];
    pid->x[0] = in;

    return out;
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
