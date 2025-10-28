/**
 * @file axidma_hal.c
 * @author Product application department
 * @brief  AXIDMA 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "axidma_hal.h"

// 全局变量定义
axidma_handle_t *g_axidma_handle;

// 函数定义

/**
 * @brief AXIDMA 模块初始化函数
 *
 * @param initpara axidma配置参数
 * @return Status_TypeDef 函数执行状态
 */
status_t hal_axidma_init(axidma_handle_t *initpara)
{
    // reset axidma
    drv_axidma_reset(initpara);
    g_axidma_handle = initpara;
    // config axidma
    return (drv_axidma_config(initpara));
}

/**
 * @brief  AXIDMA 模块启动传输函数
 *
 * @param initpara axidma配置参数
 */
void hal_axidma_start(axidma_handle_t *initpara)
{
    if (initpara->irq_en)
    {
        // enable dma irq
        drv_axidma_enable_ioblk_done(initpara);
        drv_axidma_enable_int(initpara);
        // NVIC init
        NVIC_Init(3, 3, AXIDMA_IRQn, 2);
        AXIDMA_IRQHandler_Callback = hal_axidma_irq_handler;
    }else
    {
        NVIC_Clear(AXIDMA_IRQn);
    }
    // set irq
    drv_axidma_set_int_tfr(initpara);
    if (initpara->blk_tfr_en)
        drv_axidma_set_intblk_tfr(initpara);    
    // enbale dma channel
    drv_axidma_enable_channel(initpara);
}

/**
 * @brief AXIDMA 模块停止传输函数
 *
 * @param initpara
 */
void hal_axidma_disable(axidma_handle_t *initpara)
{
    drv_axidma_disable(initpara);
}

/**
 * @brief AXIDMA 模块轮询传输函数
 *
 * @param initpara
 */
void hal_axidma_transfer_polling(axidma_handle_t *initpara)
{
    volatile uint32_t intstat, reg;
    intstat = drv_axidma_get_intstatus(initpara);

    while (!(intstat & (1 << initpara->channel_num)))
        intstat = drv_axidma_get_intstatus(initpara);

    reg = drv_axidma_chx_get_intstatus(initpara);
    if (reg & AXI_DMAC_INTBIT_DMA_TFR_DONE)
        drv_axidma_chx_clr_intstatus_l(initpara, reg);

    // invalidate dcache
    if(initpara->transfer_type == AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA || 
       initpara->transfer_type == AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA ||
       initpara->transfer_type == AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL)
    {
        if(initpara->dst_multblk_type == AXI_DMAC_MULTIBLK_DST_CONTIGUOUS)
        {
            dcache_invalidate_range((uint32_t*)initpara->dst_addr, (initpara->nBlocks + 1) * (1 << initpara->dst_tr_width));
        }
        else
        {
            SCB_InvalidateDCache();
        }
    }



    return;
}

/**
 * @brief AXIDMA 模块获取通道控制寄存器值函数
 *
 * @param initpara
 * @return uint32_t
 */
uint32_t hal_axidma_get_chx_ctl(axidma_handle_t *initpara)
{
    return (drv_axidma_chx_ctl(initpara));
}

/**
 * @brief AXIDMA 模块配置llp链表函数
 *
 * @param initpara axidma配置参数
 * @param llp_addr llp链表首地址
 * @return Status_TypeDef 函数执行状态
 */
status_t hal_axidma_config_llp(axidma_handle_t *initpara, uint32_t llp_addr)
{
    return drv_axidma_llp_config(initpara, llp_addr);
}

/**
 * @brief axidma中断处理函数
 * 
 */
void hal_axidma_irq_handler(void)
{
    volatile uint32_t intstat, reg;
    reg = drv_axidma_getcommonintstatus(g_axidma_handle);
    drv_axidma_clrcommonintstatus(g_axidma_handle, reg);
    intstat = drv_axidma_get_intstatus(g_axidma_handle);
    if (intstat & (1 << g_axidma_handle->channel_num))
    {
        reg = drv_axidma_chx_get_intstatus(g_axidma_handle);
        if (reg & AXI_DMAC_INTBIT_DMA_TFR_DONE)
        {
            drv_axidma_chx_clr_intstatus_l(g_axidma_handle, reg);

            // invalidate dcache
            if(g_axidma_handle->transfer_type == AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA || 
               g_axidma_handle->transfer_type == AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA ||
               g_axidma_handle->transfer_type == AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL)
            {
                if(g_axidma_handle->dst_multblk_type == AXI_DMAC_MULTIBLK_DST_CONTIGUOUS)
                {
                    dcache_invalidate_range((uint32_t*)g_axidma_handle->dst_addr, (g_axidma_handle->nBlocks + 1) * (1 << g_axidma_handle->dst_tr_width));
                }
                else
                {
                    SCB_InvalidateDCache();
                }
            }

            if(g_axidma_handle->axidma_cb)
                g_axidma_handle->axidma_cb();
            return ;
        }
        else if (g_axidma_handle->blk_tfr_en)
        {
            if (reg & AXI_DMAC_INTBIT_BLOCK_TFR_DONE)
            {
                drv_axidma_chx_clr_intstatus_l(g_axidma_handle, reg);
                return ;
            }
        }
    }
    return;
}
