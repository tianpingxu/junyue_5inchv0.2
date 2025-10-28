/**
 * @file systick_drv.h
 * @author Product application department
 * @brief  SYSTICK 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __SYSTICK_DRV_H
#define __SYSTICK_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "drv.h"
#include "core_cm7.h"
#include "interrupt.h"

// 函数声明
uint32_t drv_systick_config(uint32_t ticks);
void drv_systick_handler(void);
void drv_systick_enable(uint8_t flag);
    
#ifdef __cplusplus
}
#endif

#endif
