/**
 * @file dac_reg.h
 * @author Product application department
 * @brief  DAC 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DAC_REG_H_
#define __DAC_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define DAC_BASE_ADDR (0x40021000)
#define DAC ((reg_dac_t *)DAC_BASE_ADDR)

// DAC_CR
#define DAC_DACEN (((uint32_t)1 << 0))
#define DAC_BUFDIS (((uint32_t)1 << 1))
#define DAC_ALIGN (((uint32_t)1 << 2))
#define DAC_RES (((uint32_t)1 << 3))
#define DAC_DMATH (((uint32_t)1 << 16))
#define DAC_DMAEN (((uint32_t)1 << 23))
#define DAC_STH (((uint32_t)1 << 24))
#define DAC_STHIE (((uint32_t)1 << 28))
#define DAC_UDFIE (((uint32_t)1 << 29))
#define DAC_OVFIE (((uint32_t)1 << 30))
#define DAC_FCLR (((uint32_t)1 << 31))
#define DAC_TSEL_MASK (0x00000600)
#define DAC_TSEL_SHIFT (9)
#define DAC_EXT_TMOD_MASK (0x00007000)
#define DAC_EXT_TMOD_SHIFT (12)

// DAC_SWTR
#define DAC_SW_TRIG (((uint32_t)1 << 0))

// DAC_FSR
#define DAC_SER (((uint32_t)1 << 29))
#define DAC_OVF (((uint32_t)1 << 30))
#define DAC_LD_DONE ((uint32_t)1 << 31)

/**
 * @brief DAC 模块寄存器结构体定义
 */
typedef struct
{
    __IO uint32_t DAC_CR;    // 0x00
    __IO uint32_t DAC_DR;    // 0x04
    __IO uint32_t DAC_SWTR;  // 0x08
    __IO uint32_t DAC_DOR;   // 0x0c
    __IO uint32_t DAC_FSR;   // 0x10
    __IO uint32_t DAC_TRIMR; // 0x14
} reg_dac_t;

#ifdef __cplusplus
}
#endif

#endif
