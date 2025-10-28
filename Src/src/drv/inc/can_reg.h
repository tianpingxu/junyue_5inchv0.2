/**
 * @file can_reg.h
 * @author Product application department
 * @brief  CAN 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __CAN_REG_H
#define __CAN_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define CAN1_BASE_ADDR (0x4000C000)
#define CAN2_BASE_ADDR (0x4000D000)
#define CAN1 ((reg_can_t *)CAN1_BASE_ADDR)
#define CAN2 ((reg_can_t *)CAN2_BASE_ADDR)

// MCR
#define SPI_FRAME_FORMAT_TI ((uint8_t)(1 << 4))
#define CAN_MCR_MAXMB (0x0000003f)
#define CAN_MCR_MDIS (0x01u << 31)
#define CAN_MCR_FRZ (0x01u << 30)
#define CAN_MCR_WRN_EN (0x01u << 21)
#define CAN_MCR_SOFT_RST (0x01u << 25)
#define CAN_MCR_FEN (0x01u << 29)
#define CAN_MCR_HALT (0x01u << 28)
#define CAN_MCR_NOT_RDY (0x01u << 27)
#define CAN_MCR_FRZ_ACK (0x01u << 24)
#define CAN_MCR_SLF_WAK (0x01u << 22)
#define CAN_MCR_LPM_ACK (0x01u << 20)
#define CAN_MCR_LPRIO_EN (0x00002000)
#define CAN_MCR_SRX_DIS (0X00020000)
#define CAN_MCR_BCC (0x00010000)
#define CAN_MCR_AEN (0x00001000)
#define CAN_MCR_IDAM_A (0x00000000)
#define CAN_MCR_IDAM_B (0x00000100)
#define CAN_MCR_IDAM_C (0x00000200)

// CR
#define CAN_TIMING_MASK (0x00C0FFF8)
#define CAN_CR_RJW_2 (0x00800000)
#define CAN_CR_BOFF_MSK (0x00008000)
#define CAN_CR_ERR_MSK (0x00004000)
#define CAN_CR_CLK_SRC (0x00002000)
#define CAN_CR_LPB (0x00001000)
#define CAN_CR_TWRN_MSK (0x00000800)
#define CAN_CR_RWRN_MSK (0x00000400)
#define CAN_CR_BUFF_REC (0x00000040)
#define CAN_CR_TSYN (0x00000020)
#define CAN_CR_LBUF (0x00000010)
#define CAN_CR_LOM (0x00000008)

// SR
#define CAN_ESR_TWRN_INT (0x00020000)
#define CAN_ESR_RWRN_INT (0x00010000)
#define CAN_ESR_BIT0_ERROR (0x1 << 14)
#define CAN_ESR_Error_Passive (0x1 << 4)
#define CAN_ESR_BOFF_INT (0x00000004)
#define CAN_ESR_ERR_INT (0x00000002)

// IM1R
#define CAN_IM1R_RX_FIFO_INT_MASK (0xffffff1f)
#define CAN_IM1R_RX_FIFO_INT (0xe0)

// IF1R
#define CAN_IF1R_RX_FIFO_OVERRUN_FLAG (0x1 << 7)
#define CAN_IF1R_RX_FIFO_ALMOST_OVERRUN_FLAG (0x1 << 6)
#define CAN_IF1R_RX_FIFO_FLAG (0x1 << 5)

// MB
#define CAN_RXCODE_INACT (0x00000000)
#define CAN_RXCODE_EMPTY (0x04000000)
#define CAN_TXCODE_INACT (0x08000000)
#define CAN_TXCODE_ABORT (0x09000000)
#define CAN_TXCODE_ONCE (0x0c000000)
#define CAN_TXCODE_REMOTE (0x0a000000)
#define CAN_MBS_RTR (0x00100000)
#define CAN_MBS_IDE (0x00200000)
#define CAN_MBS_SRR (0x00400000)
#define CAN_FIFO_EXT_MSK (0x40000000)
#define CAN_DLC_8BYTE (0x00080000)

/**
 * @brief CAN 模块消息缓存区结构体定义
 */
typedef struct
{
    __IO uint32_t MB_CS;
    __IO uint32_t MB_ID;
    union
    {
        struct
        {
            __IO uint32_t MB_WORD0;
            __IO uint32_t MB_WORD1;
        };
        __IO uint8_t MB_DATA[8];
    };
} can_messagebuffer_t;

/**
 * @brief CAN 模块rx individual mask寄存器结构定义
 */
typedef struct
{
    __IO uint32_t CAN_RXIMR[64];
} can_rxindividualmask_t;

/**
 * @brief CAN rx fifo寄存器枚举定义
 */
typedef struct
{
    __IO uint32_t ID_TABLE[8];
} can_rxfifoidtable_t;

/**
 * @brief CAN 模块寄存器定义
 */
typedef struct
{
    __IO uint32_t CAN_MCR;
    __IO uint32_t CAN_CR;
    __IO uint32_t CAN_FRT;
    __IO uint32_t RESERVED0;
    __IO uint32_t CAN_RXGM;
    __IO uint32_t CAN_RX14M;
    __IO uint32_t CAN_RX15M;
    __IO uint32_t CAN_ECR;
    __IO uint32_t CAN_ESR;
    __IO uint32_t CAN_IM2R;
    __IO uint32_t CAN_IM1R;
    __IO uint32_t CAN_IF2R;
    __IO uint32_t CAN_IF1R;
    __IO uint32_t RESERVED1[19];
    can_messagebuffer_t CAN_MB[64];

} reg_can_t;


#ifdef __cplusplus
}
#endif

#endif
