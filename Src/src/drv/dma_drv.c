/**
 * @file dma_drv.c
 * @author Product application department
 * @brief  DMA 模块DRV层驱动.
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "dma_drv.h"

// 全局变量定义
dmac_controlreg_t *m_dma_control;
dmac_channel_t *m_dma_channel[DMAC_CHNUM] = {(dmac_channel_t *)(DMAC1_BASE_ADDR), (dmac_channel_t *)(DMAC1_BASE_ADDR + 0x58),
                                             (dmac_channel_t *)(DMAC1_BASE_ADDR + 0xB0), (dmac_channel_t *)(DMAC1_BASE_ADDR + 0x108)}; // global struct variable for for Channel registers

// 函数定义

/**
 * @brief DMA 模块设置控制寄存器函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @param[in] tt_fc 传送类型和流控制
 * @param[in] src_msize 源传输数据长度
 * @param[in] dest_msize 目标传输数据长度
 * @param[in] sinc  源地址增量
 * @param[in] dinc  目标地址增量
 * @param[in] src_tr_wideh 源数据传输大小
 * @param[in] dst_tr_width 目标数据传输大小
 * @return @ref NONE
 */
void drv_dmac_ctrlregconfig(reg_dmac_t *pdmac,
                            uint32_t ch,
                            uint32_t tt_fc,
                            uint32_t src_msize,
                            uint32_t dest_msize,
                            uint32_t sinc,
                            uint32_t dinc,
                            uint32_t src_tr_wideh,
                            uint32_t dst_tr_width)
{
    uint32_t tmp = 0;

    if (ch > (DRV_DMAC_CH_MAX - 1))
        return;

    /* Prepare the DMA Channel configuration */
    tmp |= (((tt_fc << DMAC_TT_FC_SHIFT_MASK) & (DMAC_TT_FC_MASK)) |
            ((src_msize << DMAC_SRC_MSIZE_SHIFT_MASK) & (DMAC_SRC_MSIZE_MASK)) |
            ((dest_msize << DMAC_DEST_MSIZE_SHIFT_MASK) & (DMAC_DEST_MSIZE_MASK)) |
            ((sinc << DMAC_SINC_INC_SHIFT_MASK) & (DMAC_SINC_INC_MASK)) |
            ((dinc << DMAC_DINC_INC_SHIFT_MASK) & (DMAC_DINC_INC_MASK)) |
            ((src_tr_wideh << DMAC_SRC_TR_WIDTH_SHIFT_MASK) & (DMAC_SRC_TR_WIDTH_MASK)) |
            ((dst_tr_width << DMAC_DST_TR_WIDTH_SHIFT_MASK) & (DMAC_DST_TR_WIDTH_MASK)));

    _dmac_set_dmac_ctrln(pdmac, ch, tmp);
}

/**
 * @brief DMA 模块初始化LLI寄存器函数.
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @param[in] pdma_lli dma的LLI结构体
 *
 * @return @ref NONE
 */
void drv_dmac_llireginit(reg_dmac_t *pdmac, uint32_t ch, dmac_lli_t *pdma_lli)
{
    if (ch > (DRV_DMAC_CH_MAX - 1))
        return;

    pdmac->CH[ch].SRCADDR = pdma_lli->src_addr;
    pdmac->CH[ch].DSTADDR = pdma_lli->dst_addr;
    pdmac->CH[ch].LLI = (uint32_t)pdma_lli;
    //    pdmac->CH[ch].CTRL = pdma_lli->control;
    pdmac->CH[ch].CTRL_HIGH = pdma_lli->len;
}

/**
 * @brief DMA 模块寄存器初始化函数
 *
 * @param dmac_base_addr DAM 地址
 */
void drv_dmac_reg_init(uint32_t dmac_base_addr)
{
    m_dma_control = (dmac_controlreg_t *)(dmac_base_addr + 0x2c0);
    m_dma_channel[0] = (dmac_channel_t *)(dmac_base_addr);
    m_dma_channel[1] = (dmac_channel_t *)(dmac_base_addr + 0x58);
    m_dma_channel[2] = (dmac_channel_t *)(dmac_base_addr + 0xB0);
    m_dma_channel[3] = (dmac_channel_t *)(dmac_base_addr + 0x108);
    m_dma_control->DMA_CONFIG = 0x01;
}

/**
 * @brief DMA 模块使能函数
 * @param pdmac DMAC指针;
 */
void drv_dmac_en(reg_dmac_t *pdmac)
{
    _dmac_en(pdmac);
}

/**
 * @brief DMA 模块失能函数
 * @param pdmac DMAC指针;
 */
void drv_dma_dis(reg_dmac_t *pdmac)
{
    _dmac_dis(pdmac);
}

/**
 * @brief DMA 模块通道禁止函数
 *
 * @param n dma通道号，取指【0~3】
 */

void drv_dmac_dis(uint8_t n)
{
    m_dma_channel[n]->CONFIG |= 1 << 8;
    m_dma_control->DMA_CHEN |= CHANNEL_WRITE_ENABLE(n);
    m_dma_control->DMA_CHEN &= ~CHANNEL_ENABLE(n);
    m_dma_channel[n]->CONFIG &= ~(1 << 8);
    m_dma_control->DMA_CONFIG = ~1;
}
/**
 * @brief DMA 模块禁止TRF中断函数.
 *
 * @param[in] pdmac DMAC指针;
 * @param[in] ch dma通道号;
 *
 * @return @ref NONE
 */
void drv_dmac_distfrit(reg_dmac_t *pdmac, uint32_t ch)
{
    pdmac->MASKTFR &= ~(((1 << ch) << 8 | (1 << ch)));
}
/**
 * @brief DMA 模块清队TRF中断标志函数.
 *
 * @param[in] pdmac DMAC指针;
 * @param[in] ch dma通道号;
 *
 * @return @ref NONE
 */
void drv_dmac_clrtrflag(reg_dmac_t *pdmac, uint32_t ch)
{
    pdmac->CLRTFR = (1 << ch);
}

/**
 * @brief DMA 模块获取RAW中断使能标志函数
 * @param pdmac dma 实例
 * @param ch dma 通道号
 * @return
 */
BitActionTypeDef drv_dmac_getrawirq_en(reg_dmac_t *pdmac, uint32_t ch)
{
    if (_dmac_get_raw_interrupt_en(pdmac, ch))
        return BIT_SET;

    return BIT_RESET;
}

/**
 * @brief DMA 模块获取DMA的RAW状态函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @return @ref
 *  - BIT_RESET
 *  - BIT_SET
 */
BitActionTypeDef drv_dmac_getrawstatus(reg_dmac_t *pdmac, uint32_t ch)
{
    if (_dmac_get_raw_interrupt_status(pdmac, ch))
        return BIT_SET;

    return BIT_RESET;
}

/**
 * @brief DMA 模块清除DMA的RAW状态函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @return @ref NONE
 */
void drv_dmac_clearrawstatus(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_clr_raw_interrupt_status(pdmac, ch);
}

/**
 * @brief DMA 模块获取BLOCK中断使能标志函数
 * @param pdmac dma 实例
 * @param ch dma 通道号
 * @return
 */
BitActionTypeDef drv_dmac_getblockirq_en(reg_dmac_t *pdmac, uint32_t ch)
{
    if (_dmac_get_block_interrupt_en(pdmac, ch))
        return BIT_SET;

    return BIT_RESET;
}

/**
 * @brief DMA 模块获取DMA的block状态函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @return @ref
 *  - BIT_RESET
 *  - BIT_SET
 */
BitActionTypeDef drv_dmac_getblockstatus(reg_dmac_t *pdmac, uint32_t ch)
{
    if (_dmac_get_block_interrupt_status(pdmac, ch))
        return BIT_SET;

    return BIT_RESET;
}

/**
 * @brief DMA 模块清除DMA的block状态函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @return @ref NONE
 */
void drv_dmac_clearblocktatus(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_clr_block_interrupt_status(pdmac, ch);
}

/**
 * @brief DMA 模块获取MIN中断使能标志函数
 * @param pdmac dma 实例
 * @param ch dma 通道号
 * @return
 */
BitActionTypeDef drv_dmac_getminirq_en(reg_dmac_t *pdmac, uint32_t ch)
{
    if (_dmac_get_min_interrupt_en(pdmac, ch))
        return BIT_SET;

    return BIT_RESET;
}

/**
 * @brief DMA 模块获取DMA的min状态函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @return @ref
 *  - BIT_RESET
 *  - BIT_SET
 */
BitActionTypeDef drv_dmac_getminstatus(reg_dmac_t *pdmac, uint32_t ch)
{
    if (_dmac_get_min_interrupt_status(pdmac, ch))
        return BIT_SET;

    return BIT_RESET;
}

/**
 * @brief DMA 模块清除DMA的min状态函数
 *
 * @param[in] ch dma通道号，取指【0~3】
 * @return @ref NONE
 */
void drv_dmac_clearmintatus(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_clr_min_interrupt_status(pdmac, ch);
}

/**
 * @brief  DMA 模块通道使能函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_ch_enable(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_ch_en(pdmac, ch);
}

/**
 * @brief  DMA 模块通道失能函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_ch_disable(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_ch_dis(pdmac, ch);
}

/**
 * @brief  DMA 模块通道复位控制器函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_ch_reset(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_clr_dmac_ctrln(pdmac, ch);
}

/**
 * @brief  DMA 模块通道传输长度设置函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_transfer_length(reg_dmac_t *pdmac, uint32_t ch, int32_t length)
{
    _dmac_set_transfer_length(pdmac, ch, length);
}

/**
 * @brief DMA 模块通道传输起始地址设置函数
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 * @param addr 地址
 */
void drv_dmac_set_transfer_srcaddr(reg_dmac_t *pdmac, uint32_t ch, int32_t addr)
{
    _dmac_set_source_address(pdmac, ch, addr);
}

/**
 * @brief DMA 模块通道传输目标地址设置函数
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 * @param addr 地址
 */
void drv_dmac_set_transfer_dstaddr(reg_dmac_t *pdmac, uint32_t ch, int32_t addr)
{
    _dmac_set_destination_address(pdmac, ch, addr);
}

/**
 * @brief DMA 模块通道通源地址软件握手函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_src_soft(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_src_hs_soft(pdmac, ch);
}

/**
 * @brief DMA 模块通道源地址硬件握手函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_src_hard(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_src_hs_hard(pdmac, ch);
}
/**
 * @brief DMA 模块通道地址软件握手函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_dst_soft(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_dst_hs_soft(pdmac, ch);
}

/**
 * @brief DMA 模块通道目标地址软件握手函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_dst_hard(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_dst_hs_hard(pdmac, ch);
}

/**
 * @brief  DMA 模块通道目标设备函数
 *
 * pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 * @param per_type 设备类型
 */
void drv_dmac_set_dst_peripheral(reg_dmac_t *pdmac, uint32_t ch, uint32_t per_type)
{
    _dmac_set_dst_peripheral(pdmac, ch, per_type);
}

/**
 * @brief  DMA 模块通道目标设备函数
 *
 * pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 * @param per_type 设备类型
 */
void drv_dmac_set_src_peripheral(reg_dmac_t *pdmac, uint32_t ch, uint32_t per_type)
{
    _dmac_set_src_peripheral(pdmac, ch, per_type);
}

/**
 * @brief DMA 模块通道RAW中断使能函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_raw_inten(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_raw_interrupt_en(pdmac, ch);
}

/**
 * @brief DMA 模块通道RAW中断失能函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_set_raw_intdis(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_raw_interrupt_dis(pdmac, ch);
}

/**
 * @brief DMA 模块中断使能函数
 *
 * @param pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 */
void drv_dmac_int_en(reg_dmac_t *pdmac, uint32_t ch)
{
    _dmac_int_en_en(pdmac, ch);
}

/**
 * @brief DMA 模块设置通道控制寄存器函数
 * @param pdmac  pdmac DMAC实例
 * @param ch dma通道号，取指【0~3】
 * @param tmp 控制器值
 */
void drv_damc_set_ch_ctrl(reg_dmac_t *pdmac, uint32_t ch, uint32_t tmp)
{
    _dmac_set_dmac_ctrln(pdmac, ch, tmp);
}
