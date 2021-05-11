/**
 * *****************************************************************************
 * @file         ca.c/h
 * @brief        Algorithm library
 * @author       tqfx
 * @date         20210430
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CA_H__
#define __CA_H__

/* Exported macro ------------------------------------------------------------*/

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/

/**
 * @defgroup       CA algorithm
 * @brief          computational algorithm
 *                 control algorithm
 *                 filtering algorithm
 *                 conversion algorithm
*/

/**
 * @brief          Computational algorithm
*/
#include "ca_math.h"

/**
 * @brief          Control algorithm
*/
#include "ca_pid.h"

/**
 * @brief          Filtering algorithm
*/
#include "ca_lpf.h"

/**
 * @brief          Conversion algorithm
*/
#include "ahrs.h"
#include "zyx.h"

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __CA_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
