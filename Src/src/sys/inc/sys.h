/**
 * @file sys.h
 * @author Product application department
 * @brief  系统时钟配置头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
#include "iomacros.h"
#include "delay.h"
#include "cpm_drv.h"
#include "ssi_drv.h"
#include "debug.h"

// 全局变量定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
#define STARTUP_ADDR 0x10000000

/**
 * @brief 芯片启动模式枚举定义
 *
 */
typedef enum
{
    Startup_From_ROM = 0,
    Startup_From_FLASH,
} startupmode_t;

/**
 * @brief 时钟初始化索引结构体定义
 *
 */
typedef struct
{
    cpm_sysclksel_t SysClkSource;
    cpm_sysclktrim_t SysClkTrim;
    cpm_sysclkdiv_t CoreClkDiv;
    cpm_sysclkdiv_t SysClkDiv;
    cpm_ipsclkdiv_t IpsClkDiv;
} sys_clkinit_t;

// 函数声明
void sys_startupconfig(startupmode_t Mode, functionalstate_t ResetEN);
void sys_sysclkconfig(sys_clkinit_t *pClkInit);
void Sys_FrequencyConversion(cpm_sysclkdiv_t sys_clk_div);
void sys_cacheinit(void);
void sys_uartdebuginit(uart_typedef_t *UARTx, uint32_t pclk, uint32_t bound);
void sys_soft_reset(void);
void sys_standby(void);
void sys_init(void);
void wfi_set(void);
void MSR_MSP(uint32_t addr);
void sys_cpm_getclk(void);

#ifdef __cplusplus
}
#endif

#endif
