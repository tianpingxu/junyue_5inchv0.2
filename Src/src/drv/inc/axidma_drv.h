/**
 * @file axidma_drv.h
 * @author Product application department
 * @brief  AXIDMA 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __AXIDMA_DRV_H
#define __AXIDMA_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "status.h"
#include "axidma_reg.h"

/**
 * @brief AXIDMA 模块中断状态结构体定义
 * 
 */
typedef enum
{
    DRV_AXIDMA_TFR_IRQ = 0x00,
    DRV_AXIDMA_BLK_IRQ = 0x01,
    DRV_AXIDMA_ERROR_IRQ = 0x02
} axidma_irq_status_t;

/**
 * @brief  AXIDMA 模块传输信息结构体定义
 * 
 */
typedef struct
{
    axi_dma_t *instance;
    uint32_t irq_en;                           /**< irq en*/
    uint32_t dma_tfr_en;                       /**< dma tfr irq en*/
    uint32_t blk_tfr_en;                       /**< llp blk tfr irq en*/
    axi_dma_chx_t channel_num;                 /**< DMA channel number, should be in
                                                    *  range from 0 to 7.
                                                    *  Note: DMA channel 0 has the highest priority
                                                    *  and DMA channel 7 the lowest priority.    //TODO check axi_dmac priority
                                                    */
    axi_dma_mize_t src_msize;                  /**< SRC burst Transaction length @ref AXI_DMAC_MSIZE_Typedef */
    axi_dma_mize_t dst_msize;                  /**< DST burst Transaction length @ref AXI_DMAC_MSIZE_Typedef */
    axi_dma_transwidth_t src_tr_width;         /**< SRC Transfer width, @ref AXI_DMAC_TransWidth_Typedef */
    axi_dma_transwidth_t dst_tr_width;         /**< DST Transfer width, @ref AXI_DMAC_TransWidth_Typedef */
    axi_dma_inc_option_t src_inc;              /*!< Specifies whether the Source address register should be incremented or not.
                                                  This parameter can be a value of @ref AXI_DAMC_INC_OPTION */
    axi_dma_inc_option_t dst_inc;              /*!< Specifies whether the Destination address register should be incremented or not.
                                                  This parameter can be a value of @ref AXI_DAMC_INC_OPTION */
    axi_dma_mutiblk_option_t src_multblk_type; /**< SRC MulitBlock Type, should be a value of @ref AXI_DMAC_MULTIBLK_OPTION */
    axi_dma_mutiblk_option_t dst_multblk_type; /**< DST MulitBlock Type, should be a value of @ref AXI_DMAC_MULTIBLK_OPTION */
    axi_dma_fc_option_t transfer_type;         /**< Transfer Type, should be a value of @ref AXI_DMAC_FC_OPTION */
    axi_dma1_peri_t src_peri_type;         /**< Transfer Type, should be one of the following:
                                                   AXI_DMAC_PeriTypeDef/AXI_DMAC2_PeriTypeDef */
    uint32_t dst_peri_type;                    /**< Transfer Type, should be one of the following:
                                                              AXI_DMAC_PeriTypeDef/AXI_DMAC2_PeriTypeDef */
    uint32_t src_addr;                         /**< Physical Source Address */
    uint32_t dst_addr;                         /**< Physical Destination Address */
    uint32_t nBlocks;                          /**< Number of the transfer blocks */
    axidma_callback_t axidma_cb;
} axidma_handle_t;

// 函数声明
void drv_axidma_reset(axidma_handle_t *initpara);
status_t drv_axidma_config(axidma_handle_t *initpara);
void drv_axidma_enable_ioblk_done(axidma_handle_t *initpara);
void drv_axidma_enable_int(axidma_handle_t *initpara);
void drv_axidma_set_int_tfr(axidma_handle_t *initpara);
void drv_axidma_set_intblk_tfr(axidma_handle_t *initpara);
void drv_axidma_enable_channel(axidma_handle_t *initpara);
void drv_axidma_disable(axidma_handle_t *initpara);
uint32_t drv_axidma_get_intstatus(axidma_handle_t *initpara);
uint32_t drv_axidma_chx_get_intstatus(axidma_handle_t *initpara);
void drv_axidma_chx_clr_intstatus_l(axidma_handle_t *initpara, uint32_t int_mask);
uint32_t drv_axidma_chx_ctl(axidma_handle_t *initpara);
status_t drv_axidma_llp_config(axidma_handle_t *initpara, uint32_t llp_addr);
uint32_t drv_axidma_getcommonintstatus(axidma_handle_t *initpara);
void drv_axidma_clrcommonintstatus(axidma_handle_t *initpara, uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif
