/*!
 @file           ca_pid.c
 @brief          Proportional Integral Derivative Algorithm
 @details        A proportional–integral–derivative controller
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
    \Delta u(k) &= K_p [e(k) − e(k - 1)]
                 + K_i e(k)
                 + K_d [e(k) + e(k - 2) − 2 e(k - 1)] \\
                &= (K_p + K_i + K_d) e(k)
                 + (-K_p - 2 K_i) e(k - 1)
                 + K_d e(k - 2)
 \f}
                 https://en.wikipedia.org/wiki/PID_controller
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-22
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 \n \n
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 \n \n
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "ca_pid.h"

#include <stdarg.h>

/*!
 @cond
*/

#undef LIMIT
#define LIMIT(x, min, max) ((x) > (max)        \
                                ? (max)        \
                                : ((x) < (min) \
                                       ? (min) \
                                       : (x)))

/*!
 @endcond
*/

void ca_pid_f32_init(ca_pid_f32_t *pid,
                     ca_pid_mode_t mode,
                     const float k[3],
                     const float omin,
                     const float omax,
                     const float omaxi)
{
    /* Set mode of PID Control */
    pid->mode = mode;
    /* Set minimum output */
    pid->omin = omin;
    /* Set maximum output */
    pid->omax = omax;

    switch (pid->mode)
    {
    case CA_PID_POS:
    {
        /* Set maximum intergral output */
        pid->omaxi = omaxi;
        if (pid->omaxi < 0)
        {
            pid->omaxi = -pid->omaxi;
        }

        /* Set derived gain */
        pid->a[0] = k[0] + k[2];
        pid->a[1] = -k[2];
        pid->a[2] = k[1];
    }
    break;

    case CA_PID_INC:
    {
        /* Reset maximum intergral output */
        pid->omaxi = 0;

        /* Set derived gain */
        pid->a[0] = k[0] + k[1] + k[2];
        pid->a[1] = -k[0] - 2 * k[2];
        pid->a[2] = k[2];
    }
    break;

    default:
    {
    }
    break;
    }
}

void ca_pid_f64_init(ca_pid_f64_t *pid,
                     ca_pid_mode_t mode,
                     const double k[3],
                     const double omin,
                     const double omax,
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
    case CA_PID_POS:
    {
        /* Set maximum intergral output */
        va_start(ap, omax);
        pid->omaxi = va_arg(ap, double);
        if (pid->omaxi < 0)
        {
            pid->omaxi = -pid->omaxi;
        }
        va_end(ap);

        /* Set derived gain */
        pid->a[0] = k[0] + k[2];
        pid->a[1] = -k[2];
        pid->a[2] = k[1];
    }
    break;

    case CA_PID_INC:
    {
        /* Reset maximum intergral output */
        pid->omaxi = 0;

        /* Set derived gain */
        pid->a[0] = k[0] + k[1] + k[2];
        pid->a[1] = -k[0] - 2 * k[2];
        pid->a[2] = k[2];
    }
    break;

    default:
    {
    }
    break;
    }
}

float ca_pid_f32(ca_pid_f32_t *pid,
                 const float ref,
                 const float set)
{
    /* Output */
    float out = 0;
    /* Input */
    float in = set - ref;

    switch (pid->mode)
    {
    case CA_PID_POS:
    {
        /*
         When the limit of integration is exceeded and
         the direction of integration is the same,
         the integration stops
        */
        if ((-pid->omaxi < pid->y &&
             pid->y < pid->omaxi) ||
            pid->y * in < 0)
        {
            /* y = a[2] * (\sum in) */
            pid->y += pid->a[2] * in;
        }

        /* out = a[0] * in + a[1] * x[0] + y */
        out = pid->a[0] * in;
        out += pid->a[1] * pid->x[0];
        out += pid->y;

        /* Restrict the output of the PID */
        out = LIMIT(out, pid->omin, pid->omax);
    }
    break;

    case CA_PID_INC:
    {
        /* y[n] = y[n-1] + a[0] * in + a[1] * x[0] + a[2] * x[1] */
        pid->y += pid->a[0] * in;
        pid->y += pid->a[1] * pid->x[0];
        pid->y += pid->a[2] * pid->x[1];

        /* Restrict the output of the PID */
        pid->y = LIMIT(pid->y, pid->omin, pid->omax);
        /* Export output */
        out = pid->y;
    }
    break;

    default:
    {
    }
    break;
    }

    /* Cache data */
    pid->x[1] = pid->x[0];
    pid->x[0] = in;

    return out;
}

double ca_pid_f64(ca_pid_f64_t *pid,
                  const double ref,
                  const double set)
{
    /* Output */
    double out = 0;
    /* Input */
    double in = set - ref;

    switch (pid->mode)
    {
    case CA_PID_POS:
    {
        /*
         When the limit of integration is exceeded and
         the direction of integration is the same,
         the integration stops
        */
        if ((-pid->omaxi < pid->y &&
             pid->y < pid->omaxi) ||
            pid->y * in < 0)
        {
            /* y = a[2] * (\sum in) */
            pid->y += pid->a[2] * in;
        }

        /* out = a[0] * in + a[1] * x[0] + y */
        out = pid->a[0] * in;
        out += pid->a[1] * pid->x[0];
        out += pid->y;

        /* Restrict the output of the PID */
        out = LIMIT(out, pid->omin, pid->omax);
    }
    break;

    case CA_PID_INC:
    {
        /* y[n] = y[n-1] + a[0] * in + a[1] * x[0] + a[2] * x[1] */
        pid->y += pid->a[0] * in;
        pid->y += pid->a[1] * pid->x[0];
        pid->y += pid->a[2] * pid->x[1];

        /* Restrict the output of the PID */
        pid->y = LIMIT(pid->y, pid->omin, pid->omax);
        /* Export output */
        out = pid->y;
    }
    break;

    default:
    {
    }
    break;
    }

    /* Cache data */
    pid->x[1] = pid->x[0];
    pid->x[0] = in;

    return out;
}

/* END OF FILE */
