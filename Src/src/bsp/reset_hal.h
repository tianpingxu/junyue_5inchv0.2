/**
 * @file reset_hal.h
 * @author Product application department
 * @brief  RESET 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __RESET_HAL_H_
#define __RESET_HAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "reset_drv.h"

// 全局变量定义

/**
 * @brief RESET 模块状态枚举定义
 * 
 */
typedef enum
{
    HAL_RESET_TC2_TC3 = 0,
    HAL_RESET_CR,
    HAL_RESET_FD,
    HAL_RESET_POR,
    HAL_RESET_WDT,
    HAL_RESET_SOFT,
    HAL_RESET_VD,
    HAL_RESET_TC
} reset_status_t;

/**
 * @brief RESET 模块复位源枚举定义
 * 
 */
typedef enum
{
    HAL_RESET_SRC_HFD = 0,
    HAL_RESET_SRC_LFD,
    HAL_RESET_SRC_HVD,
    HAL_RESET_SRC_LVD
} reset_source_t;

// 函数声明
void hal_reset_softreset(void);
void hal_reset_getstatus(reset_status_t *reset);
void hal_reset_disable(reset_source_t source);

#ifdef __cplusplus
}
#endif

#endif
