/*!
 @file           ca_pid.h
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

/* Define to prevent recursive inclusion */
#ifndef __CA_PID_H__
#define __CA_PID_H__

#include "ca.h"

#include <stdint.h>

/*!
 @ingroup        CA
 @defgroup       CA_PID Proportional Integral Derivative
 @{
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
*/

/*!
 @enum           ca_pid_mode_t
 @brief          Instance enumeration for PID Control Mode
*/
typedef enum
{
    CA_PID_POS,  //!< Position pid control
    CA_PID_INC,  //!< Incremental pid control
} ca_pid_mode_t;

/*!
 @struct         ca_pid_f32_t
 @brief          Instance structure for the floating-point PID Control
*/
typedef struct
{
    ca_pid_mode_t mode;  //!< Mode of PID Control

    float omin;   //!< Minimum output
    float omax;   //!< Maximum output
    float omaxi;  //!< Maximum intergral output

    float a[3];  //!< Derived gain
    /*!<
     - @ref CA_PID_POS
        - a[0] = Kp + Kd
        - a[1] = - Kd
        - a[2] = Ki
     - @ref CA_PID_INC
        - a[0] = Kp + Ki + Kd
        - a[1] = -Kp - 2 * Kd
        - a[2] = Kd
    */
    float x[2];  //!< State array
    /*!<
     - x[0] (The last error)
     - x[1] (The error before the last time)
    */
    float y;  //!< Cache variable
    /*!<
        - @ref CA_PID_POS integral output
        - @ref CA_PID_INC all output
    */
} ca_pid_f32_t;

/*!
 @struct         ca_pid_f64_t
 @brief          Instance structure for the double floating-point PID Control
*/
typedef struct
{
    ca_pid_mode_t mode;  //!< Mode of PID Control

    double omin;   //!< Minimum output
    double omax;   //!< Maximum output
    double omaxi;  //!< Maximum intergral output

    double a[3];  //!< Derived gain
    /*!<
     - @ref CA_PID_POS
        - a[0] = Kp + Kd
        - a[1] = - Kd
        - a[2] = Ki
     - @ref CA_PID_INC
        - a[0] = Kp + Ki + Kd
        - a[1] = -Kp - 2 * Kd
        - a[2] = Kd
    */
    double x[2];  //!< State array
    /*!<
     - x[0] (The last error)
     - x[1] (The error before the last time)
    */
    double y;  //!< Cache variable
    /*!<
        - @ref CA_PID_POS integral output
        - @ref CA_PID_INC all output
    */
} ca_pid_f64_t;

__BEGIN_DECLS

/*!
 @brief          Initialization function for the floating-point PID Control
 @param[in,out]  pid: An instance of the floating-point PID Control structure
 @param[in]      mode: The mode of PID Control
  @arg @ref      CA_PID_POS position pid control
  @arg @ref      CA_PID_INC incremental pid control
 @param[in]      k: constant array
  @arg           k[0] (Proportional constant)
  @arg           k[1] (Integral constant)
  @arg           k[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
extern void ca_pid_f32_init(ca_pid_f32_t *pid,
                            ca_pid_mode_t mode,
                            const float k[3],
                            const float omin,
                            const float omax,
                            const float omaxi);

/*!
 @brief          Initialization function for the double floating-point PID Control
 @param[in,out]  pid: An instance of the double floating-point PID Control structure
 @param[in]      mode: The mode of PID Control
  @arg @ref      CA_PID_POS position pid control
  @arg @ref      CA_PID_INC incremental pid control
 @param[in]      k: constant array
  @arg           k[0] (Proportional constant)
  @arg           k[1] (Integral constant)
  @arg           k[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      ...: Maximum intergral output
*/
extern void ca_pid_f64_init(ca_pid_f64_t *pid,
                            ca_pid_mode_t mode,
                            const double k[3],
                            const double omin,
                            const double omax,
                            ...);

/*!
 @brief          Process function for the floating-point PID Control
 @param[in,out]  pid: An instance of the floating-point PID Control structure
 @param[in]      ref: Reference point
 @param[in]      set: Set point
 @return         Output
*/
extern float ca_pid_f32(ca_pid_f32_t *pid,
                        const float ref,
                        const float set);

/*!
 @brief          Process function for the double floating-point PID Control
 @param[in,out]  pid: An instance of the double floating-point PID Control structure
 @param[in]      ref: Reference point
 @param[in]      set: Set point
 @return         Output
*/
extern double ca_pid_f64(ca_pid_f64_t *pid,
                         const double ref,
                         const double set);

__END_DECLS

__STATIC_INLINE
/*!
 @brief          Reset function for the floating-point PID Control
 @param[in,out]  pid: An instance of the floating-point PID Control structure
*/
void ca_pid_f32_reset(ca_pid_f32_t *pid)
{
    /* Reset buffer */
    pid->x[0] = pid->x[1] = pid->y = 0;
}

__STATIC_INLINE
/*!
 @brief          Reset function for the double floating-point PID Control
 @param[in,out]  pid: An instance of the double floating-point PID Control structure
*/
void ca_pid_f64_reset(ca_pid_f64_t *pid)
{
    /* Reset buffer */
    pid->x[0] = pid->x[1] = pid->y = 0;
}

__STATIC_INLINE
/*!
 @brief          Initialization function for the floating-point position PID Control
 @param[in,out]  pid: An instance of the floating-point PID Control structure
 @param[in]      k: constant array
  @arg           k[0] (Proportional constant)
  @arg           k[1] (Integral constant)
  @arg           k[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
void ca_pid_f32_pos(ca_pid_f32_t *pid,
                    const float k[3],
                    float omin,
                    float omax,
                    float omaxi)
{
    ca_pid_f32_init(pid, CA_PID_POS, k, omin, omax, omaxi);
}

__STATIC_INLINE
/*!
 @brief          Initialization function for the floating-point incremental PID Control
 @param[in,out]  pid: An instance of the floating-point PID Control structure
 @param[in]      k: constant array
  @arg           k[0] (Proportional constant)
  @arg           k[1] (Integral constant)
  @arg           k[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
*/
void ca_pid_f32_inc(ca_pid_f32_t *pid,
                    const float k[3],
                    float omin,
                    float omax)
{
    ca_pid_f32_init(pid, CA_PID_INC, k, omin, omax, 0);
}

__STATIC_INLINE
/*!
 @brief          Initialization function for the double floating-point position PID Control
 @param[in,out]  pid: An instance of the double floating-point PID Control structure
 @param[in]      k: constant array
  @arg           k[0] (Proportional constant)
  @arg           k[1] (Integral constant)
  @arg           k[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
 @param[in]      omaxi: Maximum intergral output
*/
void ca_pid_f64_pos(ca_pid_f64_t *pid,
                    const double k[3],
                    const double omin,
                    const double omax,
                    const double omaxi)
{
    ca_pid_f64_init(pid, CA_PID_POS, k, omin, omax, omaxi);
}

__STATIC_INLINE
/*!
 @brief          Initialization function for the double floating-point incremental PID Control
 @param[in,out]  pid: An instance of the double floating-point PID Control structure
 @param[in]      k: constant array
  @arg           k[0] (Proportional constant)
  @arg           k[1] (Integral constant)
  @arg           k[2] (Derivative constant)
 @param[in]      omin: Minimum output
 @param[in]      omax: Maximum output
*/
void ca_pid_f64_inc(ca_pid_f64_t *pid,
                    const double k[3],
                    const double omin,
                    const double omax)
{
    ca_pid_f64_init(pid, CA_PID_INC, k, omin, omax);
}

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __CA_PID_H__ */

/* END OF FILE */
