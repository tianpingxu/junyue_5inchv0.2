/**
 *  @file ssi_reg.h
 *  @author Product application department
 *  @brief  SSI 模块寄存器配置文件
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __SSI_REG_H
#define __SSI_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define SPIM1_BASE_ADDR (0xC1000000)
#define SPIM2_BASE_ADDR (0xC2000000)
#define SPIM3_BASE_ADDR (0xC3000000)
#define SSI1 ((reg_ssi_t *)SPIM1_BASE_ADDR)
#define SSI2 ((reg_ssi_t *)SPIM2_BASE_ADDR)
#define SSI3 ((reg_ssi_t *)SPIM3_BASE_ADDR)
// SSI_CTRLR0
#define CTRLR0_DFS_VALUE(x) (x << 0)
#define CTRLR0_FRF_MOT (0x00 << 6)
#define CTRLR0_TMOD_VALUE(x) (x << 10)
#define CTRLR0_TMOD_TX_AND_RX (0x00 << 10)
#define CTRLR0_TMOD_TX_ONLY (0x01 << 10)
#define CTRLR0_TMOD_RX_ONLY (0x02 << 10)
#define CTRLR0_TMOD_EEPROM_READ (0x03 << 10)
#define CTRLR0_CFS_VALUE(x) (x << 16)
#define CTRLR0_SCPH_MASK (1 << 8)
#define CTRLR0_SCPOL_MASK (1 << 9)
#define CTRLR0_SRL_MASK (1 << 13)
#define CTRLR0_SSTE_MASK (1 << 14)
#define CTRLR0_SPI_FRF_STD (0x00 << 22)
#define CTRLR0_SPI_FRF_DUAL (0x01 << 22)
#define CTRLR0_SPI_FRF_QUAD (0x02 << 22)

// SPI_CTRLR0
#define CTRLR0_TRANS_TYPE_TT0 (0x00 << 0)
#define CTRLR0_TRANS_TYPE_TT1 (0x01 << 0)
#define CTRLR0_TRANS_TYPE_TT2 (0x02 << 0)
#define CTRLR0_ADDR_L_VALUE(x) (x << 2)
#define CTRLR0_INST_L_VALUE(x) (x << 8)
#define CTRLR0_WAIT_CYCLES_VALUE(x) (x << 11)
#define CTRLR0_CLK_STRETCH_EN_MASK (1 << 30)

/**
 * @brief SSI 模块寄存器结构体定义
 * 
 */
typedef struct
{
    __IO uint32_t CTRLR0;         // 0x00
    __IO uint32_t CTRLR1;         // 0x04
    __IO uint32_t SSIENR;         // 0x08
    __IO uint32_t MWCR;           // 0x0c
    __IO uint32_t SER;            // 0x10
    __IO uint32_t BAUDR;          // 0x14
    __IO uint32_t TXFTLR;         // 0x18
    __IO uint32_t RXFTLR;         // 0x1c
    __IO uint32_t TXFLR;          // 0x20
    __IO uint32_t RXFLR;          // 0x24
    __IO uint32_t SR;             // 0x28
    __IO uint32_t IMR;            // 0x2c
    __IO uint32_t ISR;            // 0x30
    __IO uint32_t RISR;           // 0x34
    __IO uint32_t TXOICR;         // 0x38
    __IO uint32_t RXOICR;         // 0x3c
    __IO uint32_t RXUICR;         // 0x40
    __IO uint32_t reserve_44;     // 0x44
    __IO uint32_t ICR;            // 0x48
    __IO uint32_t DMACR;          // 0x4c
    __IO uint32_t DMATDLR;        // 0x50
    __IO uint32_t DMARDLR;        // 0x54
    __IO uint32_t reserve_58;     // 0x58
    __IO uint32_t reserve_5c;     // 0x5c
    __IO uint32_t DR;             // 0x60
    __IO uint32_t RESERVERED[35]; // 0x64~0xec
    __IO uint32_t RXSDR;          // 0xf0
    __IO uint32_t SPICTRLR0;      // 0xf4
    __IO uint32_t reserve_f8;     // 0xf8
    __IO uint32_t XIPMBR;         // 0xfc
    __IO uint32_t XIPIIR;         // 0x100
    __IO uint32_t XIPWIR;         // 0x104
    __IO uint32_t XIPCR;          // 0x108
    __IO uint32_t XIPSER;         // 0x10C
    __IO uint32_t XRXIOCR;        // 0x110
    __IO uint32_t reserve_114;    // 0x114
} reg_ssi_t;

#ifdef __cplusplus
}
#endif

#endif
