/**
 * @file ssislv_reg.h 
 * @author Product application department 
 * @brief  SSI SLAVE 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */
#ifndef __SSISLV_REG_H
#define __SSISLV_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
// 全局变量定义
/**
 *  @brief  SSISLAVE 模块寄存器结构体定义
 * 
 */
typedef struct
{
    __IO uint32_t CTRLR0;       // 0x00
    __IO uint32_t CTRLR1;       // 0x04
    __IO uint32_t SSIENR;       // 0x08
    __IO uint32_t MWCR;         // 0x0c
    __IO uint32_t RESERVE0;     // 0x10
    __IO uint32_t RESERVE1;     // 0x14
    __IO uint32_t TXFTLR;       // 0x18
    __IO uint32_t RXFTLR;       // 0x1c
    __IO uint32_t TXFLR;        // 0x20
    __IO uint32_t RXFLR;        // 0x24
    __IO uint32_t SR;           // 0x28
    __IO uint32_t IMR;          // 0x2c
    __IO uint32_t ISR;          // 0x30
    __IO uint32_t RISR;         // 0x34
    __IO uint32_t TXOICR;       // 0x38
    __IO uint32_t RXOICR;       // 0x3c
    __IO uint32_t RXUICR;       // 0x40
    __IO uint32_t RESERVE2;     // 0x44
    __IO uint32_t ICR;          // 0x48
    __IO uint32_t DMACR;        // 0x4c
    __IO uint32_t DMATDLR;      // 0x50
    __IO uint32_t DMARDLR;      // 0x54
    __IO uint32_t RESERVE3[2];  // 0x58
    __IO uint32_t DR;           // 0x60
} reg_ssislv_t;
  
#ifdef __cplusplus
}
#endif

#endif 