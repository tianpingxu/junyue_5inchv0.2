/**
 * @file dma_drv.h
 * @author Product application department
 * @brief  DMA 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DMA_DRV_H
#define __DMA_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "status.h"
#include "type.h"
#include "dma_reg.h"
#include "debug.h"

// 全局变量定义
#define DMAC_CHNUM (4)
#define DMA_IE (0x01)

#define SIEC (0x0 << 9)
#define SDEC (0x1 << 9)
#define SNOCHG (0x2 << 9)

#define DIEC (0x0 << 7)
#define DDEC (0x1 << 7)
#define DNOCHG (0x2 << 7)
#define INTEN 0x1
#define SRC_PER_SCI1_RX (0xb << 7)
#define SRC_PER_SCI3_TX (0xc << 7)
#define SRC_PER_SCI3_RX (0xd << 7)
#define SRC_PER_SCI2_RX (0x0 << 7)
#define SRC_PER_SCI4_RX (0xe << 7)
#define SRC_PER_SCI4_TX (0xf << 7)
#define SRC_PER_SCI5_RX (0x9 << 7)
#define SRC_PER_SCI5_TX (0x8 << 7)
#define SRC_PER_SCI6_RX (0x7 << 7)
#define SRC_PER_SCI6_TX (0x8 << 7)
#define DI (0x0) // increment
#define SI (0x0)
#define DST_SOFT (0x1 << 10)
#define DWIDTH_B (0x0 << 1)
#define DWIDTH_HW (0x1 << 1)
#define DWIDTH_W (0x2 << 1)
#define DWIDTH_DW (0x3 << 1)
#define SWIDTH_B (0x0 << 4)
#define SWIDTH_HW (0x1 << 4)
#define SWIDTH_W (0x2 << 4)
#define SWIDTH_DW (0x2 << 4)

#define LLP_SRC_EN (0x1 << 28)
#define LLP_DST_EN (0x1 << 27)

#define M2M_DMA (0x0 << 20)
#define M2P_DMA (0x1 << 20)
#define P2M_DMA (0x2 << 20)
#define P2P_DMA (0x3 << 20)
#define P2M_PER (0x4 << 20)
#define P2P_SRC (0x5 << 20)
#define M2P_PER (0x6 << 20)
#define P2P_DST (0x7 << 20)
#define DST_PER_DAC (0x0B << 11)
#define DRV_DMAC_CH_MAX (4)

#define DMACEN 0x1
#define CHANNEL_WRITE_ENABLE(n) ((1 << n) << 8)
#define CHANNEL_UMASK(n) (((1 << n) << 8) | (1 << n))
#define CHANNEL_ENABLE(n) (1 << n)

// DMA_CHEN
#define _dmac_ch_en(pdmac, ch) _reg_write(pdmac->CHEN, (((1 << ch) << DMAC_CH_WE_EN_SHIFT_MASK) | (1 << ch)))
#define _dmac_ch_dis(pdmac, ch) _reg_write(pdmac->CHEN, (((1 << ch) << DMAC_CH_WE_EN_SHIFT_MASK) & (~(1 << ch))))
#define _dmac_set_ch_en(pdmac, ch) _reg_modify(pdmac->CHEN, ~(1 << ch), (1 << ch) << DMAC_CH_WE_EN_SHIFT_MASK)
#define _damc_get_ch_en(pdmac, ch) _reg_chk(pdmac->CHEN, (1 << ch))
#define _dmac_set_transfer_length(pdmac, ch, len) _reg_write(pdmac->CH[ch].CTRL_HIGH, len)
#define _dmac_set_source_address(pdmac, ch, addr) _reg_write(pdmac->CH[ch].SRCADDR, addr)
#define _dmac_set_destination_address(pdmac, ch, addr) _reg_write(pdmac->CH[ch].DSTADDR, addr)
#define _dmac_raw_interrupt_en(pdmac, ch) _reg_write(pdmac->MASKTFR, ((1 << ch) << 8) | (1 << ch))
#define _dmac_raw_interrupt_dis(pdmac, ch) _reg_write(pdmac->MASKTFR, (((1 << ch) << DMAC_CH_WE_EN_SHIFT_MASK)) & (~(1 << ch))) //(pdmac->MASKTFR &= ~(((1<<ch)<<8 | (1<<ch))))
#define _dmac_get_raw_interrupt_en(pdmac, ch) (_reg_read(pdmac->MASKTFR) & (1 << ch))
#define _dmac_block_interrupt_en(pdmac, ch) (pdmac->MASKBLOCK |= (((1 << ch) << 8 | (1 << ch))))
#define _dmac_block_interrupt_dis(pdmac, ch) (pdmac->MASKBLOCK = (pdmac->MASKBLOCK | ((1 << ch) << DMAC_CH_WE_EN_SHIFT_MASK)) & (~(1 << ch))) //(pdmac->MASKTFR &= ~(((1<<ch)<<8 | (1<<ch))))
#define _dmac_get_block_interrupt_en(pdmac, ch) (_reg_read(pdmac->MASKBLOCK) & (1 << ch))
#define _dmac_min_interrupt_en(pdmac, ch) (pdmac->MASKMIN |= (((1 << ch) << 8 | (1 << ch))))
#define _dmac_min_interrupt_dis(pdmac, ch) (pdmac->MASKMIN = (pdmac->MASKMIN | ((1 << ch) << DMAC_CH_WE_EN_SHIFT_MASK)) & (~(1 << ch))) //(pdmac->MASKMIN &= ~(((1<<ch)<<8 | (1<<ch))))
#define _dmac_get_min_interrupt_en(pdmac, ch) (_reg_read(pdmac->MASKMIN) & (1 << ch))
// DMA_RAWTFR
#define _dmac_get_raw_interrupt_status(pdmac, ch) (_reg_read(pdmac->RAWTFR) & (1 << ch))
#define _dmac_get_block_interrupt_status(pdmac, ch) (_reg_read(pdmac->RAWBLOCK) & (1 << ch))
#define _dmac_get_min_interrupt_status(pdmac, ch) (_reg_read(pdmac->RAWMIN) & (1 << ch))
#define _dmac_clr_raw_interrupt_status(pdmac, ch) (_reg_write(pdmac->CLRTFR, 1 << ch))
#define _dmac_clr_block_interrupt_status(pdmac, ch) (_reg_write(pdmac->CLRBLOCK, 1 << ch))
#define _dmac_clr_min_interrupt_status(pdmac, ch) (_reg_write(pdmac->CLRMIN, 1 << ch))
#define _dmac_en(pdmac) _bit_set(pdmac->CONFIG, DMAC_EN)
#define _dmac_dis(pdmac) _bit_clr(pdmac->CONFIG, DMAC_EN)
// CFGn
#define _dmac_src_hs_soft(pdmac, ch) _bit_set(pdmac->CH[ch].CONFIG, DMAC_HS_SEL_SRC)
#define _dmac_src_hs_hard(pdmac, ch) _bit_clr(pdmac->CH[ch].CONFIG, DMAC_HS_SEL_SRC)
#define _dmac_dst_hs_soft(pdmac, ch) _bit_set(pdmac->CH[ch].CONFIG, DMAC_HS_SEL_DST)
#define _dmac_dst_hs_hard(pdmac, ch) _bit_clr(pdmac->CH[ch].CONFIG, DMAC_HS_SEL_DST)
#define _dmac_ch_set_suspend(pdmac, ch) _bit_set(pdmac->CH[ch].CONFIG, DMAC_CH_SUSP)
#define _dmac_ch_clr_suspend(pdmac, ch) _bit_clr(pdmac->CH[ch].CONFIG, DMAC_CH_SUSP)
#define _dmac_chk_fifo_empty_status(pdmac, ch) _reg_chk(pdmac->CH[ch].CONFIG, DMAC_FIFO_EMPTY)

// DMA_CTRLn
#define _dmac_int_en_en(pdmac, ch) _bit_set(pdmac->CH[ch].CTRL, DMAC_INT_EN)
#define _dmac_int_en_dis(pdmac, ch) _bit_clr(pdmac->CH[ch].CTRL, DMAC_INT_EN)
#define _dmac_int_min_en(pdmac, ch) _bit_set(pdmac->CH[ch].CTRL, DMAC_INT_MIN)
#define _dmac_int_min_dis(pdmac, ch) _bit_clr(pdmac->CH[ch].CTRL, DMAC_INT_MIN)
#define _dmac_set_dmac_ctrln(pdmac, ch, val) _reg_write(pdmac->CH[ch].CTRL, val)
#define _dmac_clr_dmac_ctrln(pdmac, ch) _reg_write(pdmac->CH[ch].CTRL, 0)
#define _dmac_set_tt_fc(pdmac, ch, tt_fc) _reg_modify(pdmac->CH[ch].CTRL, DMAC_TT_FC_BITS_MASK, tt_fc << DMAC_TT_FC_SHIFT_MASK)

// DMA_CONFIG
#define _dmac_set_src_peripheral(pdmac, ch, per) _reg_write(pdmac->CH[ch].CONFIG_HIGH, per << (DMAC_SRC_PER_SHIFT_MASK))
#define _dmac_set_dst_peripheral(pdmac, ch, per) _reg_write(pdmac->CH[ch].CONFIG_HIGH, per << (DMAC_DST_PER_SHIFT_MASK))

/**
 * @brief DMA 模块链表结构体定义
 * 
 */

typedef struct
{
    __IO uint32_t src_addr;
    __IO uint32_t dst_addr;
    __IO uint32_t next_lli;
    __IO uint32_t control;
    __IO uint32_t len;
} dmac_lli_t;

// 函数声明
void drv_dmac_ctrlregconfig(reg_dmac_t *pdmac,
    uint32_t ch,
    uint32_t tt_fc,
    uint32_t src_msize,
    uint32_t dest_msize,
    uint32_t sinc,
    uint32_t dinc,
    uint32_t src_tr_wideh,
    uint32_t dst_tr_width);
void drv_dmac_llireginit(reg_dmac_t *pdmac, uint32_t ch, dmac_lli_t *pdma_lli);
void drv_dmac_reg_init(uint32_t dmac_base_addr);
void drv_dmac_dis(uint8_t n);
void drv_dmac_distfrit(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_clrtrflag(reg_dmac_t *pdmac, uint32_t ch);
BitActionTypeDef drv_dmac_getrawirq_en(reg_dmac_t *pdmac, uint32_t ch);
BitActionTypeDef drv_dmac_getrawstatus(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_clearrawstatus(reg_dmac_t *pdmac, uint32_t ch);
BitActionTypeDef drv_dmac_getblockirq_en(reg_dmac_t *pdmac, uint32_t ch);
BitActionTypeDef drv_dmac_getblockstatus(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_clearblocktatus(reg_dmac_t *pdmac, uint32_t ch);
BitActionTypeDef drv_dmac_getminirq_en(reg_dmac_t *pdmac, uint32_t ch);
BitActionTypeDef drv_dmac_getminstatus(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_clearmintatus(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_ch_enable(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_ch_disable(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_ch_reset(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_set_transfer_length(reg_dmac_t *pdmac, uint32_t ch, int32_t length);
void drv_dmac_set_transfer_srcaddr(reg_dmac_t *pdmac, uint32_t ch, int32_t addr);
void drv_dmac_set_transfer_dstaddr(reg_dmac_t *pdmac, uint32_t ch, int32_t addr);
void drv_dmac_set_src_hard(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_set_src_soft(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_set_dst_hard(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_set_dst_soft(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_set_dst_peripheral(reg_dmac_t *pdmac, uint32_t ch, uint32_t per_type);
void drv_dmac_set_src_peripheral(reg_dmac_t *pdmac, uint32_t ch, uint32_t per_type);
void drv_dmac_en(reg_dmac_t *pdmac);
void drv_dma_dis(reg_dmac_t *pdmac);
void drv_dmac_set_raw_inten(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_set_raw_intdis(reg_dmac_t *pdmac, uint32_t ch);
void drv_dmac_int_en(reg_dmac_t *pdmac, uint32_t ch);
void drv_damc_set_ch_ctrl(reg_dmac_t *pdmac, uint32_t ch, uint32_t tmp);
#ifdef __cplusplus
}
#endif

#endif
