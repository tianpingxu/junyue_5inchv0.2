/**
 * @file WDT_drv.h
 * @author Product application department
 * @brief  WDT 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __WDT_DRV_H
#define __WDT_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "wdt_reg.h"
#include "cpm_drv.h"

// 全局变量定义
#define _wdt_en _bit_set(WDT->WCR, WDT_EN)
#define _wdt_dis _bit_clr(WDT->WCR, WDT_EN)
#define _wdt_set_debug_run _bit_clr(WDT->WCR, WDT_DEBUG)
#define _wdt_set_debug_stop _bit_set(WDT->WCR, WDT_DEBUG)
#define _wdt_set_doze_run _bit_clr(WDT->WCR, WDT_DOZE)
#define _wdt_set_doze_stop _bit_set(WDT->WCR, WDT_DOZE)
#define _wdt_set_wait_run _bit_clr(WDT->WCR, WDT_WAIT)
#define _wdt_set_wait_stop _bit_set(WDT->WCR, WDT_WAIT)
#define _wdt_get_count _reg_read(WDT->WCNTR)
#define _wdt_set_wsr(value) _reg_write(WDT->WSR, value)
#define _wdt_set_mr(value) _reg_write(WDT->WMR, value)

// 函数声明
void drv_wdt_init(uint16_t value);
void drv_wdt_feed_watchdog(void);
void drv_wdt_open(void);
void drv_wdt_close(void);
uint16_t drv_wdt_get_counter(void);

#ifdef __cplusplus
}
#endif

#endif
