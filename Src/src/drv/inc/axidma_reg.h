/**
 * @file axidma_reg.h
 * @author Product application department
 * @brief  AXIDMA 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __AXIDMA_REG_H
#define __AXIDMA_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define AXI_DMAC1_BASE_ADDR (0x40049000)
#define AXI_DMAC1 ((axi_dma_t *)AXI_DMAC1_BASE_ADDR)

#define _bit_ex(mask, x) (mask << (x))
#define _bit_set_ex(x, mask, n) ((x & mask) << n)
#define _reg_set(reg, mask) ((reg) |= (mask))
#define _reg_clr(reg, mask) ((reg) &= (~mask))

// AXI_DMAC_CTRLn_L
#define AXI_DMAC_SINC_INC_MASK ((uint32_t)(0x00000010))
#define AXI_DMAC_SINC_INC_SHIFT_MASK ((uint32_t)(4))
#define AXI_DMAC_SINC_INC_BITS_MASK ((uint32_t)(0xFFFFFFEF))

#define AXI_DMAC_DINC_INC_MASK ((uint32_t)(0x00000040))
#define AXI_DMAC_DINC_INC_SHIFT_MASK ((uint32_t)(6))
#define AXI_DMAC_DINC_INC_BITS_MASK ((uint32_t)(0xFFFFFFBF))

#define AXI_DMAC_SRC_TR_WIDTH_MASK ((uint32_t)(0x00000700))
#define AXI_DMAC_SRC_TR_WIDTH_SHIFT_MASK ((uint32_t)(8))
#define AXI_DMAC_SRC_TR_WIDTH_BITS_MASK ((uint32_t)(0xFFFFF8FF))

#define AXI_DMAC_DST_TR_WIDTH_MASK ((uint32_t)(0x00003800))
#define AXI_DMAC_DST_TR_WIDTH_SHIFT_MASK ((uint32_t)(11))
#define AXI_DMAC_DST_TR_WIDTH_BITS_MASK ((uint32_t)(0xFFFFC7FF))

#define AXI_DMAC_SRC_MSIZE_MASK ((uint32_t)(0x0003C000))
#define AXI_DMAC_SRC_MSIZE_SHIFT_MASK ((uint32_t)(14))
#define AXI_DMAC_SRC_MSIZE_BITS_MASK ((uint32_t)(0xFFFC3FFF))

#define AXI_DMAC_DST_MSIZE_MASK ((uint32_t)(0x003C0000))
#define AXI_DMAC_DST_MSIZE_SHIFT_MASK ((uint32_t)(18))
#define AXI_DMAC_DST_MSIZE_BITS_MASK ((uint32_t)(0xFFC3FFFF))

// AXI_DMAC_CTRLn_H
#define AXI_DMAC_LLI_VALID_MASK ((uint32_t)(0x80000000))
#define AXI_DMAC_LLI_VALID_SHIFT_MASK ((uint32_t)(31))
#define AXI_DMAC_LLI_VALID_BITS_MASK ((uint32_t)(0x7FFFFFFF))

#define AXI_DMAC_LLI_LAST_MASK ((uint32_t)(0x40000000))
#define AXI_DMAC_LLI_LAST_SHIFT_MASK ((uint32_t)(30))
#define AXI_DMAC_LLI_LAST_BITS_MASK ((uint32_t)(0xBFFFFFFF))

#define AXI_DMAC_LLI_IOC_BLK_MASK ((uint32_t)(0x04000000))
#define AXI_DMAC_LLI_IOC_BLK_SHIFT_MASK ((uint32_t)(26))
#define AXI_DMAC_LLI_IOC_BLK_BITS_MASK ((uint32_t)(0xFBFFFFFF))

// AXI_DMAC_CFGLn_L
#define AXI_DMAC_SRC_MULTBLK_MASK ((uint32_t)(0x00000003))
#define AXI_DMAC_SRC_MULTBLK_SHIFT_MASK ((uint32_t)(0))
#define AXI_DMAC_SRC_MULTBLK_BITS_MASK ((uint32_t)(0xFFFFFFFC))

#define AXI_DMAC_DST_MULTBLK_MASK ((uint32_t)(0x0000000C))
#define AXI_DMAC_DST_MULTBLK_SHIFT_MASK ((uint32_t)(2))
#define AXI_DMAC_DST_MULTBLK_BITS_MASK ((uint32_t)(0xFFFFFFF3))

// AXI_DMAC_CFGLn_H
#define AXI_DMAC_TT_FC_MASK ((uint32_t)(0x00000007))
#define AXI_DMAC_TT_FC_SHIFT_MASK ((uint32_t)(0))
#define AXI_DMAC_TT_FC_BITS_MASK ((uint32_t)(0xFFFFFFF8))

#define AXI_DMAC_SRC_HS_SEL_MASK ((uint32_t)(0x00000008))
#define AXI_DMAC_SRC_HS_SEL_SHIFT_MASK ((uint32_t)(3))
#define AXI_DMAC_SRC_HS_SEL_BITS_MASK ((uint32_t)(0xFFFFFFF7))

#define AXI_DMAC_DST_HS_SEL_MASK ((uint32_t)(0x00000010))
#define AXI_DMAC_DST_HS_SEL_SHIFT_MASK ((uint32_t)(4))
#define AXI_DMAC_DST_HS_SEL_BITS_MASK ((uint32_t)(0xFFFFFFEF))

#define AXI_DMAC_SRC_PER_MASK ((uint32_t)(0x00000780))
#define AXI_DMAC_SRC_PER_SHIFT_MASK ((uint32_t)(7))
#define AXI_DMAC_SRC_PER_BITS_MASK ((uint32_t)(0xFFFFF87F))

#define AXI_DMAC_DST_PER_MASK ((uint32_t)(0x0000F000))
#define AXI_DMAC_DST_PER_SHIFT_MASK ((uint32_t)(12))
#define AXI_DMAC_DST_PER_BITS_MASK ((uint32_t)(0xFFFF0FFF))

#define DRV_AXI_DMAC_CH_MAX (8) // 0~7

// AXI_DMA寄存器描述
#define AXI_DMA_CFG_INT_EN _bit(1)
#define AXI_DMA_CFG_EN _bit(0)

// RESET
#define AXI_DMA_RESET _bit(0)

// ChEn
#define AXI_DMA_CH_ABORT_WE(n) _bit_ex(1, n + 8)
#define AXI_DMA_CH_ABORT(n) _bit_ex(1, n)
#define AXI_DMA_CH_SUSP_WE(n) _bit_ex(1, (n + 24))
#define AXI_DMA_CH_SUSP(n) _bit_ex(1, (n + 16))
#define AXI_DMA_CH_EN_WE(n) _bit_ex(1, (n + 8))
#define AXI_DMA_CH_EN(n) _bit_ex(1, n)

// DMAC_IntStatusReg
#define AXI_DMA_COMMONREG_INT_STATE _bit(16)
#define AXI_DMA_CHx_INITSTAT(n) _bit_ex(1, n)

//*IntClearReg*IntStatusEnable*IntSignalEnableReg*IntSignalStatus
#define AXI_DMA_EN_INT_SLVIF_UNDEFINE_DEC_MASK _bit(8)
#define AXI_DMA_EN_INT_SLVIF_WRON_HOLD_MASK _bit(3)
#define AXI_DMA_EN_INT_SLVIF_RD2WO_MASK _bit(2)
#define AXI_DMA_EN_INT_SLVIF_WR2WO_MASK _bit(1)
#define AXI_DMA_EN_INT_SLVIF_DEC_MASK _bit(0)

// reset reg
#define AXI_DMA_RESET _bit(0)

// CHx_CTL
#define AXI_DMA_CHx_CTL_SHADOW_OR_LLI_VALID _bit(31)
#define AXI_DMA_CHx_CTL_SHADOW_OR_LLILAST _bit(30)
#define AXI_DMA_CHx_CTL_IOC_BLKTFR _bit(26)
#define AXI_DMA_CHx_CTL_DST_STAT_EN _bit(25)
#define AXI_DMA_CHx_CTL_SRC_STAT_EN _bit(24)
#define AXI_DMA_CHx_CTL_AWLEN_MASK _bit_ex(0xFF, 16)
#define AXI_DMA_CHx_CTL_AWLEN_EN _bit(15)
#define AXI_DMA_CHx_CTL_ARLEN _bit_ex(0xFF, 7)
#define AXI_DMA_CHx_CTL_ARLEN_EN _bit(6)

// MSIZE
#define AXI_DMA_CHx_CTL_DST_MSIZE_1 _bit_ex(0, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_4 _bit_ex(1, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_8 _bit_ex(2, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_16 _bit_ex(3, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_32 _bit_ex(4, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_64 _bit_ex(5, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_128 _bit_ex(6, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_256 _bit_ex(7, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_512 _bit_ex(8, 18)
#define AXI_DMA_CHx_CTL_DST_MSIZE_1024 _bit_ex(9, 18)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_1 _bit_ex(0, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_4 _bit_ex(1, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_8 _bit_ex(2, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_16 _bit_ex(3, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_32 _bit_ex(4, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_64 _bit_ex(5, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_128 _bit_ex(6, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_256 _bit_ex(7, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_512 _bit_ex(8, 14)
#define AXI_DMA_CHx_CTL_SRC_MSIZE_1024 _bit_ex(9, 14)

#define AXI_DMA_CHx_CTL_DST_TR_WITH_8 _bit_ex(0, 11)
#define AXI_DMA_CHx_CTL_DST_TR_WITH_16 _bit_ex(1, 11)
#define AXI_DMA_CHx_CTL_DST_TR_WITH_32 _bit_ex(2, 11)
#define AXI_DMA_CHx_CTL_DST_TR_WITH_64 _bit_ex(3, 11)
#define AXI_DMA_CHx_CTL_DST_TR_WITH_128 _bit_ex(4, 11)
#define AXI_DMA_CHx_CTL_DST_TR_WITH_256 _bit_ex(5, 11)
#define AXI_DMA_CHx_CTL_DST_TR_WITH_512 _bit_ex(6, 11)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_8 _bit_ex(0, 8)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_16 _bit_ex(1, 8)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_32 _bit_ex(2, 8)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_64 _bit_ex(3, 8)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_128 _bit_ex(4, 8)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_256 _bit_ex(5, 8)
#define AXI_DMA_CHx_CTL_SRC_TR_WITH_512 _bit_ex(6, 8)

#define AXI_DMA_CHx_CTL_DINC 0            //*目标地址递增
#define AXI_DMA_CHx_CTL_DNOCHANGE _bit(6) //*目标不变,reload模式
#define AXI_DMA_CHx_CTL_SINC 0            //*目标地址递增
#define AXI_DMA_CHx_CTL_SNOCHANGE _bit(4) //*目标不变,reload模式

#define AXI_DMA_CHx_CTL_DMS_1 _bit_ex(0, 2)
#define AXI_DMA_CHx_CTL_DMS_2 _bit_ex(1, 2)
#define AXI_DMA_CHx_CTL_SMS_1 _bit_ex(0, 0)
#define AXI_DMA_CHx_CTL_SMS_2 _bit_ex(1, 0)
// CHx_CFG
#define AXI_DMA_CHx_CFG_DST_OSR_LMT(n) _bit_ex((n & 0x0F), 27)
#define AXI_DMA_CHx_CFG_SRC_OSR_LMT(n) _bit_ex((n & 0x0F), 23)
#define AXI_DMA_CHx_CFG_LOCK_CH_L_00 _bit_ex(0x00, 21)
#define AXI_DMA_CHx_CFG_LOCK_CH_L_01 _bit_ex(0x01, 21)
#define AXI_DMA_CHx_CFG_LOCK_CH _bit(20)
#define AXI_DMA_CHx_CFG_CH_PRIOR(n) _bit_ex((n & 0x07), 17)
#define AXI_DMA_CHx_CFG_DST_PER(n) _bit_ex((n & 0x0F), 12)
#define AXI_DMA_CHx_CFG_SRC_PER(n) _bit_ex((n & 0x0F), 7)
#define AXI_DMA_CHx_CFG_DST_HWHS_POL_HIGH _bit_ex(0, 6)
#define AXI_DMA_CHx_CFG_DST_HWHS_POL_LOW _bit(6)
#define AXI_DMA_CHx_CFG_SRC_HWHS_POL_HIGH _bit_ex(0, 5)
#define AXI_DMA_CHx_CFG_SRC_HWHS_POL_LOW _bit(5)
#define AXI_DMA_CHx_CFG_HS_SEL_DST_HARDWARE _bit_ex(0, 4)
#define AXI_DMA_CHx_CFG_HS_SEL_DST_SOFTWARE _bit(4)
#define AXI_DMA_CHx_CFG_HS_SEL_SRC_HARDWARE _bit_ex(0, 3)
#define AXI_DMA_CHx_CFG_HS_SEL_SRC_SOFTWARE _bit(3)

#define AXI_DMA_CHx_CFG_TT_FC_MEM_TO_MEM_DMAC _bit_ex(0, 0)
#define AXI_DMA_CHx_CFG_TT_FC_MEM_TO_PER_DMAC _bit_ex(1, 0)
#define AXI_DMA_CHx_CFG_TT_FC_PER_TO_MEM_DMAC _bit_ex(2, 0)
#define AXI_DMA_CHx_CFG_TT_FC_PER_TO_PER_DMAC _bit_ex(3, 0)
#define AXI_DMA_CHx_CFG_TT_FC_PER_TO_MEM_PSRC _bit_ex(4, 0)
#define AXI_DMA_CHx_CFG_TT_FC_PER_TO_PER_PSRC _bit_ex(5, 0)
#define AXI_DMA_CHx_CFG_TT_FC_MEM_TO_PER_PDST _bit_ex(6, 0)
#define AXI_DMA_CHx_CFG_TT_FC_PER_TO_PER_PDST _bit_ex(7, 0)

#define AXI_DMA_CHx_CFG_DST_MULTBLK_TYPE_CON _bit_ex(0, 2)
#define AXI_DMA_CHx_CFG_DST_MULTBLK_TYPE_RELOAD _bit_ex(1, 2)
#define AXI_DMA_CHx_CFG_DST_MULTBLK_TYPE_SHADOW _bit_ex(2, 2)
#define AXI_DMA_CHx_CFG_DST_MULTBLK_TYPE_LINKEDLIST _bit_ex(3, 2)

#define AXI_DMA_CHx_CFG_SRC_MULTBLK_TYPE_CON _bit_ex(0, 0)
#define AXI_DMA_CHx_CFG_SRC_MULTBLK_TYPE_RELOAD _bit_ex(1, 0)
#define AXI_DMA_CHx_CFG_SRC_MULTBLK_TYPE_SHADOW _bit_ex(2, 0)
#define AXI_DMA_CHx_CFG_SRC_MULTBLK_TYPE_LINKEDLIST _bit_ex(3, 0)

// CHxINTSTATUS_ENABLE/CHxIntSTATUS/CHxINTSIGNAL_ENABLE/CHxONTCLEAR
#define AXI_DMA_CHx_INI_MASK_DMA_DST_TRANS_FINISH _bit(4)
#define AXI_DMA_CHx_INI_MASK_DMA_SRC_TRANS_FINISH _bit(3)
#define AXI_DMA_CHx_INI_MASK_DMA_BLOCK_TF _bit(1)
#define AXI_DMA_CHx_INI_MASK_BLOCK_TF _bit(0)

#define AXI_DMAC_INTBIT_CH_ABORTED (0x1 << 31) /**< Channel Aborted. */

typedef void (*axidma_callback_t)(void);

/**
 * @brief AXIDMA 模块通道枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_CH0 = 0,
    AXI_DMAC_CH1 = 1,
    AXI_DMAC_CH2 = 2,
    AXI_DMAC_CH3 = 3,
    AXI_DMAC_CH4 = 4,
    AXI_DMAC_CH5 = 5,
    AXI_DMAC_CH6 = 6,
    AXI_DMAC_CH7 = 7,
} axi_dma_chx_t;

/**
 * @brief AXIDMAC 模块源/目的地址配置枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_SINC_INC = 0,       /*DMAC Source Address Increment*/
    AXI_DMAC_SINC_NO_CHANGE = 1, /*DMAC Source Address No Change*/

    AXI_DMAC_DINC_NO_CHANGE = 1, /*DMAC Destination Address No Change*/
    AXI_DMAC_DINC_INC = 0,       /*DMAC Destination Address Increment*/
} axi_dma_inc_option_t;

/**
 * @brief AXIDMAC 模块传输方式枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA = ((0UL)),           /**< Memory to memory - DMA control */
    AXI_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA = ((1UL)),           /**< Memory to peripheral - DMA control */
    AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA = ((2UL)),           /**< Peripheral to memory - DMA control */
    AXI_DMAC_TRANSFERTYPE_P2P_CONTROLLER_DMA = ((3UL)),           /**< Source peripheral to destination peripheral - DMA control */
    AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL = ((4UL)),    /**< Source peripheral to destination peripheral - destination peripheral control */
    AXI_DMAC_TRANSFERTYPE_P2P_CONTROLLER_SRCPERIPHERAL = ((5UL)), /**< Memory to peripheral - peripheral control */
    AXI_DMAC_TRANSFERTYPE_M2P_CONTROLLER_PERIPHERAL = ((6UL)),    /**< Peripheral to memory - peripheral control */
    AXI_DMAC_TRANSFERTYPE_P2P_CONTROLLER_DSTPERIPHERAL = ((7UL))  /**< Source peripheral to destination peripheral - source peripheral control */
} axi_dma_fc_option_t;

/**
 * @brief AXIDMAC 模块MULTIBLK控制类型枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_MULTIBLK_SRC_CONTIGUOUS = 0x0,
    AXI_DMAC_MULTIBLK_SRC_RELOAD = 0x1,
    AXI_DMAC_MULTIBLK_SRC_SHADOWREG = 0x2,
    AXI_DMAC_MULTIBLK_SRC_LINKEDLIST = 0x3,

    AXI_DMAC_MULTIBLK_DST_CONTIGUOUS = 0x0,
    AXI_DMAC_MULTIBLK_DST_RELOAD = 0x1,
    AXI_DMAC_MULTIBLK_DST_SHADOWREG = 0x2,
    AXI_DMAC_MULTIBLK_DST_LINKEDLIST = 0x3,
} axi_dma_mutiblk_option_t;

/**
 * @brief AXIDMAC 模块设备枚举定义
 *
 */
typedef enum
{
    AXI_DMAC1_PERIPHERAL_SSI1_RX = 0X00,
    AXI_DMAC1_PERIPHERAL_SSI1_TX = 0X01,
    AXI_DMAC1_PERIPHERAL_SSI2_RX = 0X02,
    AXI_DMAC1_PERIPHERAL_SSI2_TX = 0X03,
    AXI_DMAC1_PERIPHERAL_SSI3_RX = 0X04,
    AXI_DMAC1_PERIPHERAL_SSI3_TX = 0X05,
} axi_dma1_peri_t;

/**
 * @brief AXIDMAC 模块传输宽度枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_TRANSWIDTH_8_BITS = 0x0,
    AXI_DMAC_TRANSWIDTH_16_BITS = 0x1,
    AXI_DMAC_TRANSWIDTH_32_BITS = 0x2,
    AXI_DMAC_TRANSWIDTH_64_BITS = 0x3,
    AXI_DMAC_TRANSWIDTH_128_BITS = 0x4,
    AXI_DMAC_TRANSWIDTH_256_BITS = 0x5,
    AXI_DMAC_TRANSWIDTH_512_BITS = 0x6,
} axi_dma_transwidth_t;

/**
 * @brief AXIDMAC 模块burst传输长度枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_MIZE_1 = 0x0,
    AXI_DMAC_MIZE_4 = 0x1,
    AXI_DMAC_MIZE_8 = 0x2,
    AXI_DMAC_MIZE_16 = 0x3,
    AXI_DMAC_MIZE_32 = 0x4,
    AXI_DMAC_MIZE_64 = 0x5,
    AXI_DMAC_MIZE_128 = 0x6,
    AXI_DMAC_MIZE_256 = 0x7,
    AXI_DMAC_MIZE_512 = 0x8,
    AXI_DMAC_MIZE_1024 = 0x9,
} axi_dma_mize_t;

/**
 * @brief AXIDMAC 模块中断标志通道枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_INTSTAT_CH0 = (0x1 << 0),
    AXI_DMAC_INTSTAT_CH1 = (0x1 << 1),
    AXI_DMAC_INTSTAT_CH2 = (0x1 << 2),
    AXI_DMAC_INTSTAT_CH3 = (0x1 << 3),
    AXI_DMAC_INTSTAT_CH4 = (0x1 << 4),
    AXI_DMAC_INTSTAT_CH5 = (0x1 << 5),
    AXI_DMAC_INTSTAT_CH6 = (0x1 << 6),
    AXI_DMAC_INTSTAT_CH7 = (0x1 << 7),
    AXI_DMAC_INTSTAT_COMMONREG = (0x1 << 16),
} axi_dma_intrstat_t;

/**
 * @brief AXIDMA 通道中断比特枚举定义
 *
 */
typedef enum
{
    AXI_DMAC_INTBIT_BLOCK_TFR_DONE = (0x1 << 0), /**< Block Transfer Done. */
    AXI_DMAC_INTBIT_DMA_TFR_DONE = (0x1 << 1),   /**< DMA Transfer Done. */

    AXI_DMAC_INTBIT_SRC_TRANSCOMP = (0x1 << 3),                 /**< Source Transaction Completed. */
    AXI_DMAC_INTBIT_DST_TRANSCOMP = (0x1 << 4),                 /**< Destination Transaction Completed. */
    AXI_DMAC_INTBIT_SRC_DEC_ERR = (0x1 << 5),                   /**< Source Decode Error. */
    AXI_DMAC_INTBIT_DST_DEC_ERR = (0x1 << 6),                   /**< Destination Decode Error. */
    AXI_DMAC_INTBIT_SRC_SLV_ERR = (0x1 << 7),                   /**< Source Slave Error. */
    AXI_DMAC_INTBIT_DST_SLV_ERR = (0x1 << 8),                   /**< Destination Slave Error. */
    AXI_DMAC_INTBIT_LLI_RD_DEC_ERR = (0x1 << 9),                /**< LLI Read Decode Error. */
    AXI_DMAC_INTBIT_LLI_WR_DEC_ERR = (0x1 << 10),               /**< LLI WRITE Decode Error. */
    AXI_DMAC_INTBIT_LLI_RD_SLV_ERR = (0x1 << 11),               /**< LLI Read Slave Error. */
    AXI_DMAC_INTBIT_LLI_WR_SLV_ERR = (0x1 << 12),               /**< LLI WRITE Slave Error. */
    AXI_DMAC_INTBIT_SHADOWREG_OR_LLI_INVALID_ERR = (0x1 << 13), /**< Shadow register or LLI Invalid Error. */
    AXI_DMAC_INTBIT_SLVIF_MULTIBLKTYPE_ERR = (0x1 << 14),       /**< Slave Interface MultiBlock type Error. */

    AXI_DMAC_INTBIT_SLVIF_DEC_ERR = (0x1 << 16),                  /**< Slave Interface Decode Error. */
    AXI_DMAC_INTBIT_SLVIF_WR2RO_ERR = (0x1 << 17),                /**< Slave Interface Write to Read Only Error. */
    AXI_DMAC_INTBIT_SLVIF_RD2RWO_ERR = (0x1 << 18),               /**< Slave Interface Read to write Only Error. */
    AXI_DMAC_INTBIT_SLVIF_WRONCHEN_ERR = (0x1 << 19),             /**< Slave Interface Write On Channel Enabled Error. */
    AXI_DMAC_INTBIT_SLVIF_SHADOWREG_WRON_VALID_ERR = (0x1 << 20), /**< Shadow Register Write On Valid Error. */
    AXI_DMAC_INTBIT_SLVIF_WRONHOLD_ERR = (0x1 << 21),             /**< Slave Interface Write On Hold Error. */

    AXI_DMAC_INTBIT_CH_LOCK_CLEARED = (0x1 << 27),  /**< Channel Lock Cleared. */
    AXI_DMAC_INTBIT_CH_SRC_SUSPENDED = (0x1 << 28), /**< Channel Source Suspended. */
    AXI_DMAC_INTBIT_CH_SUSPENDED = (0x1 << 29),     /**< Channel Suspended. */
    AXI_DMAC_INTBIT_CH_DISABLED = (0x1 << 30),      /**< Channel Disabled. */
    //    AXI_DMAC_INTBIT_CH_ABORTED                        = (0x1 << 31),    /**< Channel Aborted. */
} axi_dma_chx_intrbit_t;

/**
 * @brief AXIDMA 模块通道寄存器结构体定义
 *
 */
typedef struct
{
    volatile uint32_t SAR_L;               // 100
    volatile uint32_t SAR_H;               // 104
    volatile uint32_t DAR_L;               // 108
    volatile uint32_t DAR_H;               // 10C
    volatile uint32_t BLOCK_TS_L;          // 110
    volatile uint32_t BLOCK_TS_H;          // 114
    volatile uint32_t CTL_L;               // 118
    volatile uint32_t CTL_H;               // 11C
    volatile uint32_t CFG_L;               // 120
    volatile uint32_t CFG_H;               // 124
    volatile uint32_t LLP_L;               // 128
    volatile uint32_t LLP_H;               // 12C
    volatile uint32_t STATUS_L;            // 130
    volatile uint32_t STATUS_H;            // 134
    volatile uint32_t SWHSSRC_L;           // 138
    volatile uint32_t SWHSSRC_H;           // 13C
    volatile uint32_t SWHSDST_L;           // 140
    volatile uint32_t SWHSDST_H;           // 144
    volatile uint32_t BLK_TFR_RESUMEREQ_L; // 148
    volatile uint32_t BLK_TFR_RESUMEREQ_H; // 14C
    volatile uint32_t AXI_ID_L;            // 150
    volatile uint32_t AXI_ID_H;            // 154
    volatile uint32_t AXI_QoS_L;           // 158
    volatile uint32_t AXI_QoS_H;           // 15C
    volatile uint32_t SSTAT_L;             // 160
    volatile uint32_t SSTAT_H;             // 164
    volatile uint32_t DSTAT_L;             // 168
    volatile uint32_t DSTAT_H;             // 16C
    volatile uint32_t SSTATAR_L;           // 170
    volatile uint32_t SSTATAR_H;           // 174
    volatile uint32_t SDTATAR_L;           // 178
    volatile uint32_t SDTATAR_H;           // 17C
    volatile uint32_t INT_STATUS_ENABLE_L; // 180
    volatile uint32_t INT_STATUS_ENABLE_H; // 184
    volatile uint32_t INT_STATUS_L;        // 188
    volatile uint32_t INT_STATUS_H;        // 18C
    volatile uint32_t INT_SIGNAL_ENABLE_L; // 190
    volatile uint32_t INT_SIGNAL_ENABLE_H; // 194
    volatile uint32_t INT_CLEAR_L;         // 198
    volatile uint32_t INT_CLEAR_H;         // 19C
    volatile uint32_t RSVD[24];            // offset to 200
} reg_dma_axi_dma_chx;

/**
 * @brief AXIDMA 模块寄存器结构体定义
 *
 */
typedef struct
{
    volatile uint32_t ID_L;                     // 000
    volatile uint32_t ID_H;                     // 004
    volatile uint32_t COMP_VER_L;               // 008
    volatile uint32_t COMP_VER_H;               // 00C
    volatile uint32_t CFG_L;                    // 010
    volatile uint32_t CFG_H;                    // 014
    volatile uint32_t CH_EN_L;                  // 018
    volatile uint32_t CH_EN_H;                  // 01C
    volatile uint32_t rfu[4];                   // 020
    volatile uint32_t INT_STATUS_L;             // 030
    volatile uint32_t INT_STATUS_H;             // 034
    volatile uint32_t COMMONREG_INTCLEAR_L;     // 038
    volatile uint32_t COMMONREG_INTCLEAR_H;     // 03C
    volatile uint32_t COMMONREG_INTENA_L;       // 040
    volatile uint32_t COMMONREG_INTENA_H;       // 044
    volatile uint32_t COMMONREG_INTSIGNAL_EN_L; // 048
    volatile uint32_t COMMONREG_INTSIGNAL_EN_H; // 04C
    volatile uint32_t COMMONREG_INTSTATUS_L;    // 050
    volatile uint32_t COMMONREG_INTSTATUS_H;    // 054
    volatile uint32_t RESET_L;                  // 058
    volatile uint32_t RESET_H;                  // 05C

    volatile uint32_t RSVD[40]; // offset to channel register

    reg_dma_axi_dma_chx CH[8]; // 8 channel
} axi_dma_t;

/**
 * @brief AXIDMA 模块链表结构体定义
 *
 */
typedef struct
{
    volatile uint32_t SRC_ADDR_L;
    volatile uint32_t SRC_ADDR_H;
    volatile uint32_t DST_ADDR_L;
    volatile uint32_t DST_ADDR_H;
    volatile uint32_t BLOCK_TS; // block number
    volatile uint32_t RSVD;
    volatile uint32_t NEXT_LLI_L; // bit[5:63] used
    volatile uint32_t NEXT_LLI_H;
    volatile uint32_t CHx_CTL_L;
    volatile uint32_t CHx_CTL_H;
    volatile uint32_t WRB_CHX_SSTAT; // Write back for CHx_SSTAT
    volatile uint32_t WRB_CHX_DSTAT; // Write back for CHx_DSTAT
    volatile uint32_t CHx_LLP_STATUS_L;
    volatile uint32_t CHx_LLP_STATUS_H;
    volatile uint32_t RSV[2];
} axi_dma_llp_t;

#ifdef __cplusplus
}
#endif

#endif
