/**
 * @file uart_reg.h
 * @author Product application department
 * @brief  UART 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __REG_UART_H
#define __REG_UART_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define UART1_BASE_ADDR (0x40013000)
#define UART2_BASE_ADDR (0x40014000)
#define UART3_BASE_ADDR (0x4001D000)
#define UART4_BASE_ADDR (0x4001E000)
#define UART5_BASE_ADDR (0x4002B000)
#define UART6_BASE_ADDR (0x4002C000)
#define UART1 ((uart_typedef_t *)UART1_BASE_ADDR)
#define UART2 ((uart_typedef_t *)UART2_BASE_ADDR)
#define UART3 ((uart_typedef_t *)UART3_BASE_ADDR)
#define UART4 ((uart_typedef_t *)UART4_BASE_ADDR)
#define UART5 ((uart_typedef_t *)UART5_BASE_ADDR)
#define UART6 ((uart_typedef_t *)UART6_BASE_ADDR)

// UARTCR1
#define UART_WOMS_SHIFT_MASK (6)
#define UART_PARITY_ODD ((uint8_t)(1 << 0))
#define UART_PARITY_EVEN ((uint8_t)(0xFE))
#define UART_PARITY_ENABLE ((uint8_t)(1 << 1))
#define UART_PARITY_DISABLE ((uint8_t)(0xFD))
#define UART_IDLE_LINE_AFTER_STOP ((uint8_t)(1 << 2))
#define UART_IDLE_LINE_AFTER_START ((uint8_t)(0xFB))
#define UART_WAKEUP_MODE_ADDRESS ((uint8_t)(1 << 3))
#define UART_WAKEUP_IDLE_LINE ((uint8_t)(0xF7))
#define UART_DATA_BITS_LENGTH_8 ((uint8_t)(1 << 4))
#define UART_DATA_BITS_LENGTH_7 ((uint8_t)(0xEF))
#define UART_STOP_BITS_LENGTH_2 ((uint8_t)(1 << 7))
#define UART_STOP_BITS_LENGTH_1 ((uint8_t)(0x7F))
#define UART_RSCR_TO_TXD ((uint8_t)(1 << 5))
#define UART_RSCR_TRANSMITTER_OUTPUT ((uint8_t)(0xDF))
#define UART_OPEN_DRAIN_MODE ((uint8_t)(1 << 6))
#define UART_CMOS_MODE ((uint8_t)(0xBF))
#define UART_LOOPS_MODE ((uint8_t)(1 << 7))
#define UART_LOOPS_NORMAL_MODE ((uint8_t)(0x7F))

// UARTCR2
#define UART_SBK ((uint8_t)(1 << 0))
#define UART_IT_RWU_ASLEEP ((uint8_t)(1 << 1))
#define UART_RE ((uint8_t)(1 << 2))
#define UART_TE ((uint8_t)(1 << 3))
#define UART_IT_IDLE ((uint8_t)(1 << 4))
#define UART_IT_RIE ((uint8_t)(1 << 5))
#define UART_IT_TCIE ((uint8_t)(1 << 6))
#define UART_IT_TIE ((uint8_t)(1 << 7))

// UARTSR1
#define UART_IT_FLAG_PF ((uint8_t)(1 << 0))
#define UART_IT_FLAG_FE ((uint8_t)(1 << 1))
#define UART_IT_FLAG_NF ((uint8_t)(1 << 2))
#define UART_IT_FLAG_OR ((uint8_t)(1 << 3))
#define UART_IT_FLAG_IDLE ((uint8_t)(1 << 4))
#define UART_IT_FLAG_RDRF ((uint8_t)(1 << 5))
#define UART_IT_FLAG_TC ((uint8_t)(1 << 6))
#define UART_IT_FLAG_TDRE ((uint8_t)(1 << 7))

// UARTSR2
#define UART_IT_FLAG_RAF ((uint8_t)(1 << 0))

// UARTPUD
#define UART_PU_SHIFT_MASK (0)
#define UART_PULLUP_EN ((uint8_t)(1 << 0))
#define UART_PULLUP_DIS ((uint8_t)(0xFE))
#define UART_REDUCE_DRIVE ((uint8_t)(1 << 4))
#define UART_FULL_DRIVE ((uint8_t)(0xEF))
#define UART_DOZE_MODE_DIS ((uint8_t)(1 << 7))
#define UART_DOZE_MODE_EN ((uint8_t)(0x7F))

// UARTDDR
#define UART_RXD_OUT ((uint8_t)(1 << 0))
#define UART_TXD_OUT ((uint8_t)(1 << 1))

// UARTIRCR
#define UART_IR_EN ((uint8_t)(1 << 0))
#define UART_IRSC_SYS_CLK ((uint8_t)(1 << 1))
#define UART_RINV_ACTIVE_HIGH ((uint8_t)(1 << 2))
#define UART_TINV_ACTIVE_HIGH ((uint8_t)(1 << 3))
#define UART_RNUM_MASK ((uint8_t)(0xCF))
#define UART_RNUM_SHIFT_MASK ((uint8_t)(4))
#define UART_RNUM_BITS_MASK ((uint8_t)(0x30))
#define UART_TNUM_MASK ((uint8_t)(0x3F))
#define UART_TNUM_SHIFT_MASK ((uint8_t)(6))
#define UART_TNUM_BITS_MASK ((uint8_t)(0xC0))

// UARTFCR
#define UART_TF_EN ((uint8_t)(1 << 6))
#define UART_RF_EN ((uint8_t)(1 << 7))
#define UART_RX_FLSEL_MASK ((uint8_t)(0x38))
#define UART_RX_FLSEL_SHIFT_MASK ((uint8_t)(3))
#define UART_RX_FLSEL_BITS_MASK ((uint8_t)(0xC7))
#define UART_TX_FLSEL_MASK ((uint8_t)(0x07))
#define UART_TX_FLSEL_SHIFT_MASK ((uint8_t)(0))
#define UART_TX_FLSEL_BITS_MASK ((uint8_t)(0xF8))

// UARTFSR
#define UART_FIFO_FLAG_R_EMPTY ((uint8_t)(1 << 0))
#define UART_FIFO_FLAG_R_FULL ((uint8_t)(1 << 1))
#define UART_FIFO_FLAG_T_EMPTY ((uint8_t)(1 << 2))
#define UART_FIFO_FLAG_T_FULL ((uint8_t)(1 << 3))
#define UART_FIFO_FLAG_RTOS ((uint8_t)(1 << 4))
#define UART_FIFO_FLAG_RFTS ((uint8_t)(1 << 5))
#define UART_FIFO_FLAG_FTC ((uint8_t)(1 << 6))
#define UART_FIFO_FLAG_TFTS ((uint8_t)(1 << 7))

// UARTDCR
#define UART_RX_DMA_EN ((uint8_t)(1 << 0))
#define UART_TX_DMA_EN ((uint8_t)(1 << 1))

// UARTFCR2
#define UART_FIFO_RXF_CLR ((uint8_t)(1 << 0))
#define UART_FIFO_TXF_CLR ((uint8_t)(1 << 1))
#define UART_FIFO_RXF_TO_EN ((uint8_t)(1 << 2))
#define UART_FIFO_RXFTO_IE ((uint8_t)(1 << 3))
#define UART_FIFO_RXFOR_IE ((uint8_t)(1 << 4))
#define UART_FIFO_RXF_IE ((uint8_t)(1 << 5))
#define UART_FIFO_TXFC_IE ((uint8_t)(1 << 6))
#define UART_FIFO_TXF_IE ((uint8_t)(1 << 7))

// UARTFSR2
#define UART_FXPF ((uint8_t)(1 << 0))
#define UART_FXFE ((uint8_t)(1 << 1))
#define UART_FXNF ((uint8_t)(1 << 2))
#define UART_FXOR ((uint8_t)(1 << 3))

/**
 * @brief UART 模块寄存器结构体定义
 */
typedef struct
{
    __IO uint8_t BDL;     // 0x00
    __IO uint8_t BDH;     // 0x01
    __IO uint8_t CR2;     // 0x02
    __IO uint8_t CR1;     // 0x03
    __IO uint8_t SR2;     // 0x04
    __IO uint8_t SR1;     // 0x05
    __IO uint8_t DRL;     // 0x06
    __IO uint8_t DRH;     // 0x07
    __IO uint8_t PORT;    // 0x08
    __IO uint8_t PURD;    // 0x09
    __IO uint8_t BRDF;    // 0x0a
    __IO uint8_t DDR;     // 0x0b
    __IO uint8_t IRCR;    // 0x0c
    __IO uint8_t TR;      // 0x0d
    __IO uint8_t FCR;     // 0x0e
    __IO uint8_t IRDR;    // 0x0f
    __IO uint8_t DCR;     // 0x10
    __IO uint8_t FSR;     // 0x11
    __IO uint8_t RXTOCTR; // 0x12
    __IO uint8_t FCR2;    // 0x13
    __IO uint8_t FCTRL;   // 0x14
    __IO uint8_t FSR2;    // 0x15
    __IO uint8_t CR3;	  // 0x16
} uart_typedef_t;

#ifdef __cplusplus
}
#endif


#endif