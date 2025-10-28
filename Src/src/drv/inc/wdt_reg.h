/**
 * @file wdt_reg.h
 * @author Product application department
 * @brief  WDT 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __WDT_REG_H
#define __WDT_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
#define WDT_BASE_ADDR (0x40005000)
#define WDT ((reg_wdt_t *)WDT_BASE_ADDR)
#define WDT_EN (1 << 0)
#define WDT_DEBUG (1 << 1)
#define WDT_DOZE (1 << 2)
#define WDT_WAIT (1 << 3)

/**
 *  @brief  WDT 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint16_t WCR;   // 0x00
    __IO uint16_t WMR;   // 0x02
    __IO uint16_t WCNTR; // 0x04
    __IO uint16_t WSR;   // 0x06
} reg_wdt_t;

#ifdef __cplusplus
}
#endif

#endif
