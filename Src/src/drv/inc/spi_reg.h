/**
 * @file spi_reg.h
 * @author Product application department
 * @brief  SPI 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __SPI_REG_H
#define __SPI_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
#define SPI1_BASE_ADDR (0x40010000)
#define SPI2_BASE_ADDR (0x40011000)
#define SPI3_BASE_ADDR (0x40012000)
#define SPI1 ((reg_spi_t *)(SPI1_BASE_ADDR))
#define SPI2 ((reg_spi_t *)(SPI2_BASE_ADDR))
#define SPI3 ((reg_spi_t *)(SPI3_BASE_ADDR))

// SPI寄存器
// SPIFR
#define SPI_FRAME_FORMAT_TI ((uint8_t)(1 << 4))
#define SPI_FRAME_FORMAT_FREESCALE ((uint8_t)(~SPI_FRAME_FORMAT_TI))
#define SPI_LOOP_BACK_MODE ((uint8_t)(1 << 5))
#define SPI_LOOP_NORMAL_MODE ((uint8_t)(~SPI_LOOP_BACK_MODE))
#define SPI_EN_GUARD_TIME ((uint8_t)(1 << 6))
#define SPI_DIS_GUARD_TIME ((uint8_t)(~SPI_EN_GUARD_TIME))
#define SPI_EN_CONT_CS ((uint8_t)(1 << 7))
#define SPI_DIS_CONT_CS ((uint8_t)(~SPI_EN_CONT_CS))
#define SPI_FRAME_SIZE_MASK ((uint8_t)(0xF0))
#define SPI_FRAME_SIZE_SHIFT_MASK ((uint8_t)(0))
// CR1
#define SPI_FIRSTBIT_LSB ((uint8_t)(1 << 0))
#define SPI_FIRSTBIT_MSB ((uint8_t)(0xFE))
#define SPI_EN_SSOE ((uint8_t)(1 << 1))
#define SPI_DIS_SSOE ((uint8_t)(0xFD))
#define SPI_CPHA_1EDGE ((uint8_t)(0xFB))
#define SPI_CPHA_2EDGE ((uint8_t)(1 << 2))
#define SPI_CPOL_HIGH ((uint8_t)(1 << 3))
#define SPI_CPOL_LOW ((uint8_t)(0xF7))
#define SPI_MASTER ((uint8_t)(1 << 4))
#define SPI_SLAVE ((uint8_t)(0xEF))
#define SPI_WIRED_OR_MODE_OPEN_DRAIN ((uint8_t)(1 << 5))
#define SPI_WIRED_OR_MODE_CMOS ((uint8_t)(0xDF))
#define SPI_EN_SSOE ((uint8_t)(1 << 1))
#define SPI_EN ((uint8_t)(1 << 6))
#define SPI_DIS ((uint8_t)(0xBF))
#define SPI_EN_IT ((uint8_t)(1 << 7))
#define SPI_DIS_IT ((uint8_t)(~SPI_EN_IT))

// SPICR2
#define SPI_SPC0_BIDIR_MODE ((uint8_t)(1 << 0))
#define SPI_SPC0_NORMAL_MODE ((uint8_t)(0xFE))
#define SPI_DOZE_INACTIVE_MODE ((uint8_t)(1 << 1))
#define SPI_DOZE_ACTIVE_MODE ((uint8_t)(0xFD))
#define SPI_GUARD_TIME_MASK ((uint8_t)(0x03))
#define SPI_GUARD_TIME_SHIFT_MASK ((uint8_t)(2))

// SPITXFTOCTR TX FIFO timeout counter register
#define SPI_EN_TX_FIFO_TINEOUT ((uint8_t)(1 << 6))
#define SPI_DIS_TX_FIFO_TIMEOUT ((uint8_t)(~SPI_EN_TX_FIFO_TINEOUT))
#define SPI_EN_TX_FIFO_TINEOUT_IT ((uint8_t)(1 << 7))
#define SPI_DIS_TX_FIFO_TIMEOUT_IT ((uint8_t)(~SPI_EN_TX_FIFO_TINEOUT_IT))
#define SPI_TX_FIFO_TIMEOUT_CNT_MASK ((uint8_t)(0xC0))

// SPITXFTOCTR RX FIFO timeout counter register
#define SPI_EN_RX_FIFO_TINEOUT ((uint8_t)(1 << 6))
#define SPI_DIS_RX_FIFO_TIMEOUT ((uint8_t)(~SPI_EN_RX_FIFO_TINEOUT))
#define SPI_EN_RX_FIFO_TINEOUT_IT ((uint8_t)(1 << 7))
#define SPI_DIS_RX_FIFO_TIMEOUT_IT ((uint8_t)(~SPI_EN_RX_FIFO_TINEOUT_IT))
#define SPI_RX_FIFO_TIMEOUT_CNT_MASK ((uint8_t)(0xC0))

// SPI TX FIFO control register
#define SPI_EN_TX_FIFO_SERVICE_THRESHOLD_IT ((uint8_t)(1 << 4))
#define SPI_EN_TX_FIFO_UNDERFLOW_IT ((uint8_t)(1 << 5))
#define SPI_EN_TX_FIFO_OVERFLOW_IT ((uint8_t)(1 << 6))
#define SPI_TX_FIFO_CLEAR ((uint8_t)(1 << 7))
#define SPI_TX_FIFO_SERVICE_TRHESHOLD_MASK ((uint8_t)(0xF0))
#define SPI_TX_FIFO_SERVICE_TRHESHOLD_SHIFT_MASK ((uint8_t)(0))

// SPI RX FIFO control register
#define SPI_EN_RX_FIFO_SERVICE_THRESHOLD_IT ((uint8_t)(1 << 4))
#define SPI_EN_RX_FIFO_UNDERFLOW_IT ((uint8_t)(1 << 5))
#define SPI_EN_RX_FIFO_OVERFLOW_IT ((uint8_t)(1 << 6))
#define SPI_RX_FIFO_CLEAR ((uint8_t)(1 << 7))
#define SPI_RX_FIFO_SERVICE_TRHESHOLD_MASK ((uint8_t)(0xF0))
#define SPI_RX_FIFO_SERVICE_TRHESHOLD_SHIFT_MASK ((uint8_t)(0))
// SPIPURD Pullup and reduced driver register
#define SPI_EN_PULLUP_DEVICE ((uint8_t)(1 << 0))
#define SPI_EN_DOUBLE_TX_DATA_MODE ((uint8_t)(1 << 1))
#define SPI_DIS_DOUBLE_TX_DATA_MODE_DIS ((uint8_t)(~SPI_EN_DOUBLE_TX_DATA_MODE))
#define SPI_EN_MISO_MOSI_SWITCH ((uint8_t)(1 << 2))
#define SPI_DIS_MISO_MOSI_SWITCH ((uint8_t)(~SPI_EN_MISO_MOSI_SWITCH))
#define SPI_EN_HIGH_SPEED ((uint8_t)(1 << 7))
#define SPI_DIS_HIGH_SPEED ((uint8_t)(0x7F))
#define SPI_MASTER_SAMPLE_POINT_DELAY_MASK ((uint8_t)(0xF3))
#define SPI_MASTER_SAMPLE_POINT_DELAY_SHIFT_MASK ((uint8_t)(2))
#define SPI_REDUCE_CAP ((uint8_t)(1 << 4))
#define SPI_FULL_DRIVER ((uint8_t)(0xEF))
#define SPI_EN_PULLDOWN_DEVICE ((uint8_t)(1 << 1))
#define SPI_DIS_PULLDOWN_DEVICE ((uint8_t)(0xFD))
#define SPI_DIS_DIS_PULLUP_DEVICE ((uint8_t)(0xFE))
#define SPI_PPS_SHIFT_MASK (4)
#define SPI_DDRSP_SHIFT_MASK (0)

// IRSP interrupt register of SS
#define SPI_SS_PIN_ASSIGNMENT_SEL_MASK ((uint8_t)(0x03))
#define SPI_SS_PIN_ASSIGNMENT_SEL_SHIFT_MASK ((uint8_t)(0x03))
#define SPI_SS_PIN_DATA_BIT ((uint8_t)(1 << 2))
#define SPI_SS_LEVEL_HIGH ((uint8_t)(1 << 3))
#define SPI_SS_LEVEL_LOW ((uint8_t)(~SPI_SS_LEVEL_HIGH))
#define SPI_SS_PIN_FLAG ((uint8_t)(1 << 4))
#define SPI_EN_SS_IT ((uint8_t)(1 << 7))
#define SPI_DIS_SS_IT ((uint8_t)(~SPI_EN_SS_IT))

// TX FIFO status register
#define SPI_TX_FIFO_NEXT_POINTER_MASK ((uint8_t)(0x0F))
#define SPI_TX_FIFO_NEXT_POINTER_SHIFT_MASK ((uint8_t)(0x0F))
#define SPI_TX_FIFO_COUNTER_MASK ((uint8_t)(0xF0))
#define SPI_TX_FIFO_COUNTER_SHIFT_MASK ((uint8_t)(0x00))

// RX FIFO status register
#define SPI_RX_FIFO_NEXT_POINTER_MASK ((uint8_t)(0x0F))
#define SPI_RX_FIFO_NEXT_POINTER_SHIFT_MASK ((uint8_t)(0x0F))
#define SPI_RX_FIFO_COUNTER_MASK ((uint8_t)(0xF0))
#define SPI_RX_FIFO_COUNTER_SHIFT_MASK ((uint8_t)(0x00))

// SPI status register
#define SPI_FLAG_RX_FIFO_EMPTY ((uint8_t)(1 << 0))
#define SPI_FLAG_RX_FIFO_FULL ((uint8_t)(1 << 1))
#define SPI_FLAG_TX_FIFO_EMPTY ((uint8_t)(1 << 2))
#define SPI_FLAG_TX_FIFO_FULL ((uint8_t)(1 << 3))
#define SPI_FLAG_MODE_FAULT ((uint8_t)(1 << 4))
#define SPI_FLAG_TRANSMISSION_END ((uint8_t)(1 << 5))
#define SPI_FLAG_FRAME_LOST ((uint8_t)(1 << 6))
#define SPI_FLAG_FINISH ((uint8_t)(1 << 7))
#define SPI_FLAG_RX_FIFO_SERVICE ((uint8_t)(1 << 0))
#define SPI_FLAG_RX_FIFO_UNDEFLOW ((uint8_t)(1 << 1))
#define SPI_FLAG_RX_FIFO_OVERFLOW ((uint8_t)(1 << 2))
#define SPI_FLAG_RX_FIFO_TIMEOUT ((uint8_t)(1 << 3))
#define SPI_FLAG_TX_FIFO_SERVICE ((uint8_t)(1 << 4))
#define SPI_FLAG_TX_FIFO_UNDERFLOW ((uint8_t)(1 << 5))
#define SPI_FLAG_TX_FIFO_OVERFLOW ((uint8_t)(1 << 6))
#define SPI_FLAG_TX_FIFO_TIMEOUT ((uint8_t)(1 << 7))


// interrupt control register
#define SPI_EN_MODE_FAULT_IT ((uint8_t)(1 << 4))
#define SPI_DIS_MODE_FAULT_IT ((uint8_t)(~SPI_EN_MODE_FAULT_IT))
#define SPI_EN_FRAME_LOST_IT ((uint8_t)(1 << 5))
#define SPI_DIS_FRAME_LOST_IT ((uint8_t)(~SPI_EN_FRAME_LOST_IT))

// SPI DMA threshold register
#define SPI_TX_DMA_THRESHOLD_MASK ((uint8_t)(0x0F))
#define SPI_TX_DMA_THRESHOLD_SHIFT_MASK ((uint8_t)(0x04))
#define SPI_RX_DMA_THRESHOLD_MASK ((uint8_t)(0xF0))
#define SPI_RX_DMA_THRESHOLD_SHIFT_MASK ((uint8_t)(0x00))

// SPI DMA control register
#define SPI_EN_RX_DMA ((uint8_t)((uint32_t)1))
#define SPI_DIS_RX_DMA ((uint8_t)(~SPI_EN_RX_DMA))
#define SPI_EN_TX_DMA ((uint8_t)(0x02))
#define SPI_DIS_TX_DMA ((uint8_t)(~SPI_EN_TX_DMA))

/**
 * @brief SPI 模块寄存器结构体定义
 */
typedef struct
{
    __IO uint8_t BR;
    __IO uint8_t FR;
    __IO uint8_t CR1;
    __IO uint8_t CR2;
    __IO uint8_t RXFTOCTR;
    __IO uint8_t TXFTOCTR;
    __IO uint8_t RXFCR;
    __IO uint8_t TXFCR;
    __IO uint8_t ASCDR;
    __IO uint8_t BSCDR;
    __IO uint8_t DDR;
    __IO uint8_t PURD;
    __IO uint8_t TCNTM;
    __IO uint8_t TCNTH;
    __IO uint8_t PORT;
    __IO uint8_t TCNTL;
    __IO uint8_t IRSP;
    __IO uint8_t RESERVED0;
    __IO uint8_t DR;
    __IO uint8_t DRH;
    __IO uint8_t RXFSR;
    __IO uint8_t TXFSR;
    __IO uint8_t SR;
    __IO uint8_t SRH;
    __IO uint8_t FDCR;
    __IO uint8_t ICR;
    __IO uint8_t DMACR;
    __IO uint8_t DMATHR;
    __IO uint8_t RXFDBGR;
    __IO uint8_t RESERVED1;
    __IO uint8_t TXFDBGR;
} reg_spi_t;

#ifdef __cplusplus
}
#endif

#endif
