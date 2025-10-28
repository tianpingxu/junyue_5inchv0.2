/**
 * @file i8080_hal.h
 * @author Product Application Department
 * @brief  I8080 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I8080_HAL_H
#define __I8080_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i8080_drv.h"

// 函数声明
void hal_fmc_init(fmc_initstructure_t *initpara);

#ifdef __cplusplus
}
#endif

#endif
