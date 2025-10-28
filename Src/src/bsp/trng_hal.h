/**
 * @file trng_hal.h
 * @author Product application department
 * @brief  TRNG 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __TRNG_HAL_H
#define __TRNG_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "trng_drv.h"

// 全局变量定义

/**
 * @brief TRNG 模块配置结构体定义
 * 
 */
typedef struct
{
    reg_trng_t *instance;
    uint8_t dividor;
} trng_handle_t;

// 函数声明
void hal_trng_init(trng_handle_t *htrng);
void hal_trng_deinit(trng_handle_t *htrng);
uint32_t hal_trng_getrandom(trng_handle_t *htrng);

#ifdef __cplusplus
}
#endif

#endif