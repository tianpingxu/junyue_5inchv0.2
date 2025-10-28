/**
 * @file common.h
 * @author Product application department
 * @brief
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif
    
// 头文件包含
#include "type.h"

// 全局变量定义
#define writel(addr, value) (*(volatile unsigned long *)(addr)) = ((unsigned long)(value))
#define writew(addr, value) (*(volatile unsigned short *)(addr)) = ((unsigned short)(value))
#define writeb(addr, value) (*(volatile unsigned char *)(addr)) = ((unsigned char)(value))
#define readl(addr) (*(volatile unsigned long *)(addr))
#define readw(addr) (*(volatile unsigned short *)(addr))
#define readb(addr) (*(volatile unsigned char *)(addr))

#define W32 writel
#define R32 readl
#define Disable_Interrupts     __asm("CPSID I")
#define Enable_Interrupts     __asm("CPSIE I")

// 函数声明
uint32_t enter_critical_sr_save(void);
void exit_critical_sr_restore(uint32_t primask);
uint32_t Read_VEC(void);

#ifdef __cplusplus
}
#endif

#endif
