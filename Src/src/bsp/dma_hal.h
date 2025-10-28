/**
 * @file dma_hal.h
 * @author Product application department
 * @brief  DMA 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef _DMAC_HAL_H
#define _DMAC_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "dma_drv.h"

// 全局变量定义
#define HAL_DMAC_SINC_INC 0       /* DMAC Source Address Increment */
#define HAL_DMAC_SINC_DEC 1       /* DMAC Source Address Decrement */
#define HAL_DMAC_SINC_NO_CHANGE 2 /* DMAC Source Address No Change */

#define HAL_DMAC_DINC_INC 0       /* DMAC Destination Address Increment */
#define HAL_DMAC_DINC_DEC 1       /* DMAC Destination Address Decrement */
#define HAL_DMAC_DINC_NO_CHANGE 2 /* DMAC Destination Address No Change */

#define HAL_DMAC_LLP_DIS 0        /* 源端和目的端都不使用LLP */
#define HAL_DMAC_LLP_SRC_EN 1     /* 源端使用LLP */
#define HAL_DMAC_LLP_DST_EN 2     /* 目的端使用LLP */
#define HAL_DMAC_LLP_SRC_DST_EN 3 /* 源端和目的端都使用LLP */
#define hal_dmac_set_LLI(pdmac, ch, value) _reg_write(pdmac->CH[ch].LLI, value)
typedef void (*dmac_callback_t)(void);

/**
 * @brief DMA 模块Init结构体定义
 * 
 */
typedef struct
{
    uint32_t channel_num;
    uint32_t transfer_lli; /**< 源端和目的端LLP标识，
                                * should be one of the following:
                                * - HAL_DMAC_LLP_DIS
                                * - HAL_DMAC_LLP_SRC_EN
                                * - HAL_DMAC_LLP_DST_EN
                                * - HAL_DMAC_LLP_SRC_DST_EN */
    uint32_t src_msize;
    uint32_t dst_msize;
    uint32_t src_tr_width; /**< Transfer width - used for TransferType is DMAC_TRANSFERTYPE_M2M only */
    uint32_t dst_tr_width;
    uint32_t src_inc;
    uint32_t dst_inc;
    uint32_t transfer_type;   /**< Transfer Type, should be one of the following:
                                   * - DMAC_TRANSFERTYPE_M2M: Memory to memory - DMA control
                                   * - DMAC_TRANSFERTYPE_M2P: Memory to peripheral - DMA control
                                   * - DMAC_TRANSFERTYPE_P2M: Peripheral to memory - DMA control
                                   * - DMAC_TRANSFERTYPE_P2P: Source peripheral to destination peripheral - DMA control*/
    uint32_t peripheral_type; /*Transfer Type, should be one of the following: DMAC_PeripheralTypeDef */
    uint32_t src_addr;
    uint32_t dst_addr;
    uint32_t transfer_size; /**< Length/Size of transfer */
} dmac_int_t;

/**
 * @brief DMAC 模块设备枚举定义
 * 
 */
typedef enum
{
    HAL_DMAC_PERIPHERAL_SPI1_TX = 0X00,
    HAL_DMAC_PERIPHERAL_SPI2_TX = 0X01,
    HAL_DMAC_PERIPHERAL_I2S1_RX = 0X02,
    HAL_DMAC_PERIPHERAL_I2S1_TX = 0X03,
    HAL_DMAC_PERIPHERAL_SPI1_RX = 0X04,
    HAL_DMAC_PERIPHERAL_SPI2_RX = 0X05,
    HAL_DMAC_PER3PHERAL_QADC = 0x06,
    HAL_DMAC_PER3PHERAL_UART6_RX = 0x07,
    HAL_DMAC_PERIPHERAL_UART6_TX = 0x08,
    HAL_DMAC_PERIPHERAL_UART5_RX = 0x09,
    HAL_DMAC_PERIPHERAL_UART1_TX = 0x0A,
    HAL_DMAC_PERIPHERAL_UART1_RX = 0x0B,
    HAL_DMAC_PERIPHERAL_UART3_TX = 0x0C,
    HAL_DMAC_PERIPHERAL_UART3_RX = 0x0D,
    HAL_DMAC_PERIPHERAL_PWMT2_TX = 0x0E,
    HAL_DMAC_PERIPHERAL_PWMT3_TX = 0x0F,
} dmac_periperal_t;

typedef enum
{
    HAL_DMAC2_PERIPHERAL_UART2_RX = 0X00,
    HAL_DMAC2_PERIPHERAL_UART2_TX = 0X01,
    HAL_DMAC2_PERIPHERAL_SSISLV_RX = 0X02,
    HAL_DMAC2_PERIPHERAL_SSISLV_TX = 0X03,
    HAL_DMAC2_PERIPHERAL_SPI3_RX = 0X04,
    HAL_DMAC2_PERIPHERAL_SPI3_TX = 0X05,
    HAL_DMAC2_PERIPHERAL_I2S2_RX = 0X06,
    HAL_DMAC2_PERIPHERAL_I2S2_TX = 0X07,
    HAL_DMAC2_PERIPHERAL_UART5_TX = 0X08,
    HAL_DMAC2_PERIPHERAL_PWMT1_TX = 0X09,
    HAL_DMAC2_PERIPHERAL_DAC = 0X0B,
    HAL_DMAC2_PERIPHERAL_ALG_TX = 0X0C,
    HAL_DMAC2_PERIPHERAL_ALG_RX = 0X0D,
    HAL_DMAC2_PERIPHERAL_UART4_RX = 0X0E,
    HAL_DMAC2_PERIPHERAL_UART4_TX = 0X0F,
} dmac2_periperal_t;

/**
 * @brief DMAC 模块handler 结构体定义
 * 
 */
typedef struct
{
    reg_dmac_t *instance;               /**< register base address       */
    dmac_int_t init;                    /**< init required parameters      */
    dmac_callback_t dma_raw_callback;   /**< DMA raw callback            */
    dmac_callback_t dma_block_callback; /**< DMA block callback          */
    dmac_callback_t dma_err_callback;   /**< DMA error callback          */
    dmac_callback_t dma_min_callback;   /**< DMA min callback            */
} dmac_hdle_t;

/**
 * @brief DNAC 模块通信宽度枚举定义
 * 
 */
typedef enum
{
    HAL_DMAC_TR_WIDTH_8BITS = 0x00,
    HAL_DMAC_TR_WIDTH_16BITS,
    HAL_DMAC_TR_WIDTH_32BITS,
    HAL_DMAC_TR_WIDTH_64BITS,
    HAL_DMAC_TR_WIDTH_128BITS,
    HAL_DMAC_TR_WIDTH_256BITS,
} dmac_transwidth_t;

/**
 * @brief DMA 模块传输长度枚举定义
 * 
 */
typedef enum
{
    HAL_DMAC_MSIZE_1 = 0x00,
    HAL_DMAC_MSIZE_4,
    HAL_DMAC_MSIZE_8,
    HAL_DMAC_MSIZE_16,
    HAL_DMAC_MSIZE_32,
    HAL_DMAC_MSIZE_64,
    HAL_DMAC_MSIZE_128,
    HAL_DMAC_MSIZE_256,
} dmac_bursttranslength_t;

/**
 * @brief DMA 模块传输类型枚举定义
 * 
 */
typedef enum
{
    HAL_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA = ((0UL)),           /**< Memory to memory - DMA control */
    HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA = ((1UL)),           /**< Memory to peripheral - DMA control */
    HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA = ((2UL)),           /**< Peripheral to memory - DMA control */
    HAL_DMAC_TRANSFERTYPE_P2P_CONTROLLER_DMA = ((3UL)),           /**< Source peripheral to destination peripheral - DMA control */
    HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL = ((4UL)),    /**< Source peripheral to destination peripheral - destination peripheral control */
    HAL_DMAC_TRANSFERTYPE_P2P_CONTROLLER_SRCPERIPHERAL = ((5UL)), /**< Memory to peripheral - peripheral control */
    HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_PERIPHERAL = ((6UL)),    /**< Peripheral to memory - peripheral control */
    HAL_DMAC_TRANSFERTYPE_P2P_CONTROLLER_DSTPERIPHERAL = ((7UL))  /**< Source peripheral to destination peripheral - source peripheral control */
} dmac_flowcontrol_t;

/**
 * @brief DMA 模块通道枚举定义
 * 
 */
typedef enum
{
    HAL_DMAC_CHANNEL_0 = 0x00,
    HAL_DMAC_CHANNEL_1,
    HAL_DMAC_CHANNEL_2,
    HAL_DMAC_CHANNEL_3,
    HAL_DMAC_CHANNEL_4,
    HAL_DMAC_CHANNEL_5,
    HAL_DMAC_CHANNEL_6,
    HAL_DMAC_CHANNEL_7,
} dmac_channelindex_t;

// 函数声明
status_t hal_dmac_deinit(dmac_hdle_t *hdma);
static void hal_dmac_setconfig(dmac_hdle_t *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
status_t hal_dmac_init(dmac_hdle_t *hdma);
status_t hal_dmac_startpolling(dmac_hdle_t *hdma);
status_t hal_dmac_pollfortransfer(dmac_hdle_t *hdma, uint32_t CompleteLevel, uint32_t Timeout);
static uint32_t hal_dmac_gettick(void);
status_t hal_dmac_pollfortransfer_it(dmac_hdle_t *hdma, uint32_t CompleteLevel, uint32_t Timeout);
void hal_dmac_clearrawstatus(dmac_hdle_t *hdma, uint32_t ch);
void hal_dmac_enable(dmac_hdle_t *hdma);
void hal_dmac_irqhandler(void);
status_t hal_dmac_start_it(dmac_hdle_t *hdma);

#ifdef __cplusplus
}
#endif

#endif
