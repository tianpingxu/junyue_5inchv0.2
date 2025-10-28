/**
 *  @file dma2d_reg.h
 *  @author Product application department
 *  @brief  DMA2D 模块寄存器配置文件
 *  @version v1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __DMA2D_REG_H
#define __DMA2D_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "type.h"

// 全局变量定义

#define DMA2D_BASE_ADDR (0x40080000)
#define DMA2D ((dma_reg_t *)DMA2D_BASE_ADDR)


/**
 *  @brief  DMA2D 模块寄存器结构体
 *
 */
typedef struct
{
    __IO uint32_t CR;             // Control Register, 0x00
    __IO uint32_t ISR;            // Interrupt Status Register, 0x04
    __IO uint32_t IFCR;           // Interrupt Flag Clear Register, 0x08
    __IO uint32_t FG_ROTA_LAYER;  // Foreground Memory Address Register or Rotate A Layer Register, 0x0C
    __IO uint32_t FGOR;           // Foreground Offset Register, 0x10
    __IO uint32_t BG_ROTB_LAYER;  // Background Memory Address Register or Rotate B Layer Register, 0x14
    __IO uint32_t BGOR;           // Background Offset Register, 0x18
    __IO uint32_t FG_ROTA_CTRL;   // Foreground PFC Control Register or Rotate A Pixel Format Register, 0x1C
    __IO uint32_t FGCOLR;         // Foreground Color Register, 0x20
    __IO uint32_t BG_ROTB_CTRL;   // Background PFC Control Register or Rotate B Pixel Format Register, 0x24
    __IO uint32_t BGCOLR;         // Background Color Register, 0x28
    __IO uint32_t FGCMAR;         // Foreground CLUT Memory Address Register, 0x2C
    __IO uint32_t BGCMAR;         // Background CLUT Memory Address Register, 0x30
    __IO uint32_t OUT_ROTC_CTRL;  // Output PFC Control Register or Rotate C Pixel Format Register, 0x34
    __IO uint32_t OCOLR;          // Output Color Register, 0x38
    __IO uint32_t OUT_ROTC_LAYER; // Output Memory Address Register or Rotate C Layer Register, 0x3C
    __IO uint32_t OOR;            // Output Offset Register, 0x40
    __IO uint32_t NLR_ROTA_SIZE;  // Number of Line Register or Rotate A Size Register, 0x44
    __IO uint32_t LWR;            // Line Watermark Register, 0x48
    __IO uint32_t AMTCR;          // AHB Master Timer Configuration Register, 0x4C
    __IO uint32_t RESERVED0[6];   // Reserved0, 0x50 - 0x64
    __IO uint32_t RGB2BGR;        // RGB2BGR Register, 0x68
    __IO uint32_t RESERVED1[2];   // Reserved1 Register, 0x6C - 0x70
    __IO uint32_t ROT_ANT;        // Rotate Ant Register, 0x74
    __IO uint32_t ROT_SIN;        // Rotate Sin Register, 0x78
    __IO uint32_t ROT_COS;        // Rotate Cos Register, 0x7C
    __IO uint32_t ROTA_CENTER;    // Rotate A Center Register, 0x80
    __IO uint32_t ROTB_CENTER;    // Rotate B Center Register, 0x84
    __IO uint32_t ROTB_SIZE;      // Rotate B Size Register, 0x88
    __IO uint32_t RESERVED[222];  // Reserved, 0x8C-0x3FF
    __IO uint32_t FGCLUT[256];    // Foreground CLUT, 0x400-0x7FF
    __IO uint32_t BGCLUT[256];    // Background CLUT, 0x800-0xBFF
} dma_reg_t;

// 浮点数寄存器操作
#define _reg_read_f(addr) (*((volatile float *)(addr)))
#define _reg_write_f(addr, val) (*((volatile float *)(addr)) = ((float)(val)))

#ifdef __cplusplus
}
#endif

#endif
