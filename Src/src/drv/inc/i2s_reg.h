/**
 * @file i2s_reg.h
 * @author Product Application Department
 * @brief  I2S 模块寄存器配置文件
 * @version V1.0
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I2S_REG_H
#define __I2S_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define I2S1_BASE_ADDR (0x40056000)
#define I2S2_BASE_ADDR (0x40057000)

#define I2S1 ((reg_i2s_t *)I2S1_BASE_ADDR)
#define I2S2 ((reg_i2s_t *)I2S2_BASE_ADDR)

// CR
#define I2S_CR_TXE (1 << 0)
#define I2S_CR_TXIE (1 << 1)
#define I2S_CR_RXE (1 << 2)
#define I2S_CR_RXIE (1 << 3)
#define I2S_CR_SCLKOBE (1 << 4)
#define I2S_CR_SDOBE (1 << 5)
#define I2S_CR_TXAUIE (1 << 6)
#define I2S_CR_TXFWL(x) ((x & 0x00000007) << 8)
#define I2S_CR_RXFWL(x) ((x & 0x00000007) << 12)
#define I2S_CR_FIFORST (1 << 16)
#define I2S_CR_ACRST (1 << 17)

// SR
#define I2S_SR_TXBA (1 << 0)
#define I2S_SR_RXBA (1 << 1)
#define I2S_SR_TXBE (1 << 2)
#define I2S_SR_TXBF (1 << 3)
#define I2S_SR_RXBE (1 << 4)
#define I2S_SR_RXBF (1 << 5)

// ESR
#define I2S_ESR_TXERR (1 << 0)
#define I2S_ESR_RXERR (1 << 1)
#define I2S_ESR_TXAU (1 << 2)

// DMACR
#define I2S_DMACR_RXEN (1 << 0)
#define I2S_DMACR_TXEN (1 << 1)
#define I2S_DMACR_RXCNT(x) ((x & 0x00000007) << 8)
#define I2S_DMACR_TXCNT(x) ((x & 0x00000007) << 16)

/**
 * @brief I2S 模块寄存器结构体定义
 * 
 */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t ESR;
    __IO uint32_t CDR;
    __IO uint32_t TXDR;
    __IO uint32_t RXDR;
    __IO uint32_t DMACR;
    __IO uint32_t ITCR;
    __IO uint32_t ITIR;
    __IO uint32_t ITOR;
} reg_i2s_t;

#ifdef __cplusplus
}
#endif

#endif
