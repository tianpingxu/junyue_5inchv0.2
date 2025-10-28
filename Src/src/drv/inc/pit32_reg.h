/**
 * @file pit32_reg.h
 * @author Product application department
 * @brief  PIT32 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __PIT32_REG_H
#define __PIT32_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define PIT1_BASE_ADDR (0x40007000)
#define PIT2_BASE_ADDR (0x40008000)
#define PIT1 ((reg_pit32_t *)PIT1_BASE_ADDR)
#define PIT2 ((reg_pit32_t *)PIT2_BASE_ADDR)

#define PIT_PCSR_EN (1 << 0) // PIT使能
#define PIT_PCSR_RLD (1 << 1)
#define PIT_PCSR_PIF (1 << 2) // PIT计数达到了0,并且产生了中断信号
#define PIT_PCSR_PIE (1 << 3) // PIT中断请求使能
#define PIT_PCSR_OVW (1 << 4)
#define PIT_PCSR_PDBG (1 << 5)
#define PIT_PCSR_PDOZE (1 << 6)
#define PIT_PCSR_PRESCALER_1 (0x00 << 8)     // PIT模块分频数值: 1分频
#define PIT_PCSR_PRESCALER_2 (0x01 << 8)     // PIT模块分频数值: 2分频
#define PIT_PCSR_PRESCALER_4 (0x02 << 8)     // PIT模块分频数值: 4分频
#define PIT_PCSR_PRESCALER_8 (0x03 << 8)     // PIT模块分频数值: 8分频
#define PIT_PCSR_PRESCALER_16 (0x04 << 8)    // PIT模块分频数值: 16分频
#define PIT_PCSR_PRESCALER_32 (0x05 << 8)    // PIT模块分频数值: 32分频
#define PIT_PCSR_PRESCALER_64 (0x06 << 8)    // PIT模块分频数值: 64分频
#define PIT_PCSR_PRESCALER_128 (0x07 << 8)   // PIT模块分频数值: 128分频
#define PIT_PCSR_PRESCALER_256 (0x08 << 8)   // PIT模块分频数值: 256分频
#define PIT_PCSR_PRESCALER_512 (0x09 << 8)   // PIT模块分频数值: 512分频
#define PIT_PCSR_PRESCALER_1024 (0x0a << 8)  // PIT模块分频数值: 1024分频
#define PIT_PCSR_PRESCALER_2048 (0x0b << 8)  // PIT模块分频数值: 2048分频
#define PIT_PCSR_PRESCALER_4096 (0x0c << 8)  // PIT模块分频数值: 4096分频
#define PIT_PCSR_PRESCALER_8192 (0x0d << 8)  // PIT模块分频数值: 8192分频
#define PIT_PCSR_PRESCALER_16384 (0x0e << 8) // PIT模块分频数值: 16384分频
#define PIT_PCSR_PRESCALER_32768 (0x0f << 8) // PIT模块分频数值: 32768分频

/**
 *  @brief  PIT 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t PCSR;  // PIT32控制和状态寄存器, 偏移地址: 0x0000
    __IO uint32_t PMR;   // PIT32计数load寄存器, 偏移地址: 0x0004
    __IO uint32_t PCNTR; // PIT32当前计数寄存器, 偏移地址: 0x0008
} reg_pit32_t;

#ifdef __cplusplus
}
#endif

#endif
