/**
 * @file axidma_drv.c
 * @author Product application department
 * @brief  AXIDMA 模块驱动层
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "axidma_drv.h"

// 函数定义

/**
 * @brief AXIDMA 模块复位函数
 *
 * @param initpara
 */
void drv_axidma_reset(axidma_handle_t *initpara)
{
    _reg_set(initpara->instance->RESET_L, AXI_DMA_RESET);
    while (_reg_chk(initpara->instance->RESET_L, AXI_DMA_RESET))
        ;
}
/**
 * @brief AXIDMA 模块寄存器配置函数
 *
 * @param initpara axidma配置参数
 * @return Status_TypeDef 函数执行状态
 */
status_t drv_axidma_config(axidma_handle_t *initpara)
{
    uint32_t src_addr_h = 0;
    uint32_t dst_addr_h = 0;
    uint32_t cfg_l_val = 0;
    uint32_t cfg_h_val = 0;
    uint32_t sms = 0;
    uint32_t dms = 0;
    uint32_t ctl_l_val = 0;

    if (initpara->channel_num > DRV_AXI_DMAC_CH_MAX)
        return STATUS_ERROR;

    //*使能AXI DMA模块
    _reg_set(initpara->instance->CFG_L, AXI_DMA_CFG_EN);

    //*AXI DMAC 参数配置 : CHANNEL寄存器配置
    _reg_write(initpara->instance->CH[initpara->channel_num].SAR_L, (uint32_t)(initpara->src_addr));
    _reg_write(initpara->instance->CH[initpara->channel_num].SAR_H, src_addr_h);
    _reg_write(initpara->instance->CH[initpara->channel_num].DAR_L, (uint32_t)(initpara->dst_addr));
    _reg_write(initpara->instance->CH[initpara->channel_num].DAR_H, dst_addr_h);

    //*配置MultiBlock传输类型
    cfg_l_val = _reg_read(initpara->instance->CH[initpara->channel_num].CFG_L);
    cfg_l_val &= (~(AXI_DMAC_SRC_MULTBLK_MASK | AXI_DMAC_DST_MULTBLK_MASK));

    cfg_l_val |= (((initpara->src_multblk_type << AXI_DMAC_SRC_MULTBLK_SHIFT_MASK) & (AXI_DMAC_SRC_MULTBLK_MASK)) |
                  ((initpara->dst_multblk_type << AXI_DMAC_DST_MULTBLK_SHIFT_MASK) & (AXI_DMAC_DST_MULTBLK_MASK)));

    _reg_write(initpara->instance->CH[initpara->channel_num].CFG_L, cfg_l_val);

    //*配置设备类型、握手类型
    cfg_h_val = _reg_read(initpara->instance->CH[initpara->channel_num].CFG_H);
    cfg_h_val &= (~(AXI_DMAC_TT_FC_MASK | AXI_DMAC_DST_PER_MASK | AXI_DMAC_SRC_PER_MASK |
                    AXI_DMAC_SRC_HS_SEL_MASK | AXI_DMAC_DST_HS_SEL_MASK));

    switch (initpara->transfer_type)
    {
    case AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA:
    {
        cfg_h_val |= ((initpara->transfer_type << AXI_DMAC_TT_FC_SHIFT_MASK) & (AXI_DMAC_TT_FC_MASK));
        break;
    }

    case AXI_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA:
    case AXI_DMAC_TRANSFERTYPE_M2P_CONTROLLER_PERIPHERAL:
    {
        cfg_h_val |= (((initpara->transfer_type << AXI_DMAC_TT_FC_SHIFT_MASK) & (AXI_DMAC_TT_FC_MASK)) |
                      (AXI_DMA_CHx_CFG_HS_SEL_DST_HARDWARE) |
                      ((initpara->dst_peri_type << AXI_DMAC_DST_PER_SHIFT_MASK) & (AXI_DMAC_DST_PER_MASK)));
        break;
    }

    case AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA:
    case AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_PERIPHERAL:
    {
        cfg_h_val |= (((initpara->transfer_type << AXI_DMAC_TT_FC_SHIFT_MASK) & (AXI_DMAC_TT_FC_MASK)) |
                      (AXI_DMA_CHx_CFG_HS_SEL_SRC_HARDWARE) |
                      ((initpara->src_peri_type << AXI_DMAC_SRC_PER_SHIFT_MASK) & (AXI_DMAC_SRC_PER_MASK)));
        break;
    }

    case AXI_DMAC_TRANSFERTYPE_P2P_CONTROLLER_DMA:
    case AXI_DMAC_TRANSFERTYPE_P2P_CONTROLLER_SRCPERIPHERAL:
    case AXI_DMAC_TRANSFERTYPE_P2P_CONTROLLER_DSTPERIPHERAL:
    {
        cfg_h_val |= (((initpara->transfer_type << AXI_DMAC_TT_FC_SHIFT_MASK) & (AXI_DMAC_TT_FC_MASK)) |
                      (AXI_DMA_CHx_CFG_HS_SEL_SRC_HARDWARE) |
                      (AXI_DMA_CHx_CFG_HS_SEL_DST_HARDWARE) |
                      ((initpara->src_peri_type << AXI_DMAC_SRC_PER_SHIFT_MASK) & (AXI_DMAC_SRC_PER_MASK)) |
                      ((initpara->dst_peri_type << AXI_DMAC_DST_PER_SHIFT_MASK) & (AXI_DMAC_DST_PER_MASK)));
        break;
    }

    default:
        return STATUS_TYPE_ERR;
    }

    _reg_write(initpara->instance->CH[initpara->channel_num].CFG_H, cfg_h_val);

    //*AXI DMAC 参数配置 : CTL寄存器配置
    ctl_l_val = _reg_read(initpara->instance->CH[initpara->channel_num].CTL_L);
    ctl_l_val &= (~(AXI_DMAC_SINC_INC_MASK | AXI_DMAC_DINC_INC_MASK | AXI_DMAC_SRC_TR_WIDTH_MASK |
                    AXI_DMAC_DST_TR_WIDTH_MASK | AXI_DMAC_SRC_MSIZE_MASK | AXI_DMAC_DST_MSIZE_MASK));

    ctl_l_val = ((sms << 0) |
                 (dms << 2) |
                 ((initpara->src_inc << AXI_DMAC_SINC_INC_SHIFT_MASK) & (AXI_DMAC_SINC_INC_MASK)) |
                 ((initpara->dst_inc << AXI_DMAC_DINC_INC_SHIFT_MASK) & (AXI_DMAC_DINC_INC_MASK)) |
                 ((initpara->src_tr_width << AXI_DMAC_SRC_TR_WIDTH_SHIFT_MASK) & (AXI_DMAC_SRC_TR_WIDTH_MASK)) |
                 ((initpara->dst_tr_width << AXI_DMAC_DST_TR_WIDTH_SHIFT_MASK) & (AXI_DMAC_DST_TR_WIDTH_MASK)) |
                 ((initpara->src_msize << AXI_DMAC_SRC_MSIZE_SHIFT_MASK) & (AXI_DMAC_SRC_MSIZE_MASK)) |
                 ((initpara->dst_msize << AXI_DMAC_DST_MSIZE_SHIFT_MASK) & (AXI_DMAC_DST_MSIZE_MASK)));

    _reg_write(initpara->instance->CH[initpara->channel_num].CTL_L, ctl_l_val);

    //*配置BLOCK数量
    _reg_write(initpara->instance->CH[initpara->channel_num].BLOCK_TS_L, initpara->nBlocks);

    return STATUS_OK;
}
/**
 * @brief AXIDMA 模块使能完成中断函数
 *
 * @param initpara axidma配置参数
 */
void drv_axidma_enable_ioblk_done(axidma_handle_t *initpara)
{
    _reg_set(initpara->instance->CH[initpara->channel_num].CTL_H, AXI_DMA_CHx_CTL_IOC_BLKTFR);
}
/**
 * @brief AXIDMA 模块打开中断使能函数
 *
 * @param initpara axidma配置参数
 */
void drv_axidma_enable_int(axidma_handle_t *initpara)
{
    _reg_set(initpara->instance->CFG_L, AXI_DMA_CFG_INT_EN);
}
/**
 * @brief AXIDMA 模块配置tfr完成中断函数
 *
 * @param initpara axidma配置参数
 */
void drv_axidma_set_int_tfr(axidma_handle_t *initpara)
{
    _reg_write(initpara->instance->CH[initpara->channel_num].INT_STATUS_ENABLE_L, AXI_DMAC_INTBIT_DMA_TFR_DONE);
}
/**
 * @brief AXIDMA 模块配置block和tfr完成中断函数
 *
 * @param initpara axidma配置参数
 */
void drv_axidma_set_intblk_tfr(axidma_handle_t *initpara)
{
    _reg_write(initpara->instance->CH[initpara->channel_num].INT_STATUS_ENABLE_L, AXI_DMAC_INTBIT_BLOCK_TFR_DONE | AXI_DMAC_INTBIT_DMA_TFR_DONE);
}
/**
 * @brief AXIDMA 模块开启通道使能函数
 *
 * @param initpara axidma配置参数
 */
void drv_axidma_enable_channel(axidma_handle_t *initpara)
{
    _reg_set(initpara->instance->CH_EN_L, AXI_DMA_CH_EN_WE(initpara->channel_num) | AXI_DMA_CH_EN(initpara->channel_num));
}
/**
 * @brief AXIDMA 模块关闭使能函数
 *
 * @param initpara axidma配置参数
 */
void drv_axidma_disable(axidma_handle_t *initpara)
{
    _reg_clr(initpara->instance->CFG_L, AXI_DMA_CFG_EN);
}
/**
 * @brief AXIDMA 模块获取中断状态函数
 *
 * @param initpara axidma配置参数
 * @return uint32_t axidma中断状态寄存器值
 */
uint32_t drv_axidma_get_intstatus(axidma_handle_t *initpara)
{
    return _reg_read(initpara->instance->INT_STATUS_L);
}
/**
 * @brief AXIDMA 模块获取通道中断状态函数
 *
 * @param initpara axidma配置参数
 * @return uint32_t 返回通道中断状态寄存器值
 */
uint32_t drv_axidma_chx_get_intstatus(axidma_handle_t *initpara)
{
    return _reg_read(initpara->instance->CH[initpara->channel_num].INT_STATUS_L);
}
/**
 * @brief AXIDMA 模块清除通道中断状态函数
 *
 * @param initpara axidma配置参数
 * @param int_mask 清除中断掩码
 */
void drv_axidma_chx_clr_intstatus_l(axidma_handle_t *initpara, uint32_t int_mask)
{
    _reg_write(initpara->instance->CH[initpara->channel_num].INT_CLEAR_L, int_mask);
}
/**
 * @brief AXIDMA 模块获取通道控制寄存器值函数
 *
 * @param initpara axidma配置参数
 * @return uint32_t 返回axidma通道控制寄存器值
 */
uint32_t drv_axidma_chx_ctl(axidma_handle_t *initpara)
{
    return (initpara->instance->CH[initpara->channel_num].CTL_L);
}
/**
 * @brief AXIDMA 模块配置llp链表函数
 *
 * @param initpara axidma配置参数
 * @param llp_addr axidma llp链表首地址
 * @return Status_TypeDef 函数执行状态
 */
status_t drv_axidma_llp_config(axidma_handle_t *initpara, uint32_t llp_addr)
{
    if (llp_addr & 0x3F) // 低6bit必须为零
        return STATUS_ERROR;
    initpara->instance->CH[initpara->channel_num].LLP_L = llp_addr;
    initpara->instance->CH[initpara->channel_num].LLP_H = 0;

    return STATUS_OK;
}
/**
 * @brief AXIDMA 模块获取普通错误中断状态函数
 *
 * @param initpara axidma配置参数
 * @return uint32_t 返回普通错误中断状态寄存器值
 */
uint32_t drv_axidma_getcommonintstatus(axidma_handle_t *initpara)
{
    return _reg_read(initpara->instance->COMMONREG_INTSTATUS_L);
}
/**
 * @brief AXIDMA 模块清除普通错误中断状态函数
 *
 * @param initpara axidma配置参数
 * @param mask 清除中断掩码
 */
void drv_axidma_clrcommonintstatus(axidma_handle_t *initpara, uint32_t mask)
{
    _reg_write(initpara->instance->COMMONREG_INTCLEAR_L, mask);
}
