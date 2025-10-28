/**
 * @file wdt_hal.h
 * @author Product application department
 * @brief  WDT 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __WDT_HAL_H
#define __WDT_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "wdt_drv.h"

// 函数声明
void hal_wdt_init(uint16_t counter);
void hal_wdt_cmd(uint8_t status);
void hal_wdt_feed_watchdog(void);
uint32_t hal_wdt_get_counter(void);

#ifdef __cplusplus
}
#endif

#endif
