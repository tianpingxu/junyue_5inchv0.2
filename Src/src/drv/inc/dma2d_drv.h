/**
 *  @file dma2d_drv.h
 *  @author Product application department
 *  @brief  DMA2D 模块驱动层头文件
 *  @version v1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __DMA2D_DRV_H
#define __DMA2D_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "dma2d_reg.h"
#include "status.h"
#include "sys.h"
    
// 全局变量定义

/**
 * @brief DMA2D 模块工作模式类型枚举定义
 * 
 */
typedef enum
{
    MEM2MEM = 0,
    MEM2MEM_PFC = 1,
    MEM2MEM_BLEND = 2,
    REG2MEM = 3
} dma2d_work_mode_t;

/**
 * @brief DMA 模块alpha 使用模式枚举定义
 * 
 */
typedef enum
{
    NO_MODIFY = 0,
    REPLACE_BY_ALPHA = 1,
    REPLACE_BY_ALPHA_AND_CHN = 2
} dma2d_alpha_mode_t;

/**
 * @brief DMA 模块CLUT 颜色模式枚举定义
 * 
 */
typedef enum
{
    CLUT_ARGB8888 = 0,
    CLUT_RGB888 = 1
} dma2d_clut_color_mode_t;

/**
 * @brief DMA 模块支持颜色格式枚举定义
 * 
 */
typedef enum
{
    CM_ARGB8888 = 0,
    CM_RGB888 = 1,
    CM_RGB565 = 2,
    CM_ARGB1555 = 3,
    CM_ARGB4444 = 4,
    CM_L8 = 5,
    CM_AL44 = 6,
    CM_AL88 = 7,
    CM_L4 = 8,
    CM_A8 = 9,
    CM_A4 = 10,
    CM_ABGR8888 = 11,
    CM_RGBA8888 = 12,
    CM_BGRA8888 = 13,
    CM_XRGB8888 = 14,
    CM_XBGR8888 = 15,
    CM_RGBX8888 = 16,
    CM_BGRX8888 = 17,
    CM_BGR888 = 18,
    CM_BGR565 = 19,
    CM_GRAY = 20
} dma2d_color_mode_t;

/**
 * @brief DMA 模块像素空间位置变换模式枚举定义
 * 
 */
typedef enum
{
    ROT_ANT_HOR_MIRROR = 1,
    ROT_ANT_VER_MIRROR = 2,
    ROT_ANT_ROTATE_90 = 4,
    ROT_ANT_HOR_ROTATE_90 = 5,
    ROT_ANT_VER_ROTATE_90 = 6,
    ROT_ANT_ROTATE_180 = 8,
    ROT_ANT_HOR_ROTATE_180 = 9,
    ROT_ANT_VER_ROTATE_180 = 10,
    ROT_ANT_ROTATE_270 = 16,
    ROT_ANT_HOR_ROTATE_270 = 17,
    ROT_ANT_VER_ROTATE_270 = 18,
    ROT_ANT_ROTATE_ANY = 32,
    ROT_ANT_ROTATE_ANY_BILINEAR = 96
} dma2d_rot_ant_mode_t;

/**
 * @brief DMA2D 模块功能使能与禁能枚举定义
 * 
 */
typedef enum
{
    DMA2D_DIS = 0,
    DMA2D_EN = 1
} dma2d_en_t;

// dma2d control register
// dma2d mode
#define DMA2D_MODF_MASK (0x3 << 16)
#define DMA2D_MODF_UNMASK (~(0x3 << 16))
#define _dma2d_mode_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_MODF_UNMASK, (value << 16))
#define _dma2d_mode_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_MODF_MASK) >> 16)
// configuration error interrupt enable
#define DMA2D_CEIE_MASK (0x1 << 13)
#define DMA2D_CEIE_UNMASK (~(0x1 << 13))
#define _dma2d_ceie_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_CEIE_UNMASK, (value << 13))
#define _dma2d_ceie_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_CEIE_MASK) >> 13)
// CLUT transfer complete interrupt enable
#define DMA2D_CTCIE_MASK (0x1 << 12)
#define DMA2D_CTCIE_UNMASK (~(0x1 << 12))
#define _dma2d_ctcie_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_CTCIE_UNMASK, (value << 12))
#define _dma2d_ctcie_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_CTCIE_MASK) >> 12)
// CLUT access error interrupt enable
#define DMA2D_CAEIE_MASK (0x1 << 11)
#define DMA2D_CAEIE_UNMASK (~(0x1 << 11))
#define _dma2d_caeie_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_CAEIE_UNMASK, (value << 11))
#define _dma2d_caeie_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_CAEIE_MASK) >> 11)
// transfer watermark interrupt enable
#define DMA2D_TWIE_MASK (0x1 << 10)
#define DMA2D_TWIE_UNMASK (~(0x1 << 10))
#define _dma2d_twie_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_TWIE_UNMASK, (value << 10))
#define _dma2d_twie_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_TWIE_MASK) >> 10)
// transfer complete interrupt enable
#define DMA2D_TCIE_MASK (0x1 << 9)
#define DMA2D_TCIE_UNMASK (~(0x1 << 9))
#define _dma2d_tcie_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_TCIE_UNMASK, (value << 9))
#define _dma2d_tcie_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_TCIE_MASK) >> 9)
// transfer error interrupt enable
#define DMA2D_TEIE_MASK (0x1 << 8)
#define DMA2D_TEIE_UNMASK (~(0x1 << 8))
#define _dma2d_teie_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_TEIE_UNMASK, (value << 8))
#define _dma2d_teie_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_TEIE_MASK) >> 8)
// abort the current transfer
#define DMA2D_ABORT_MASK (0x1 << 2)
#define DMA2D_ABORT_UNMASK (~(0x1 << 2))
#define _dma2d_abort_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_ABORT_UNMASK, (value << 2))
#define _dma2d_abort_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_ABORT_MASK) >> 2)
// suspend the current transfer
#define DMA2D_SUSP_MASK (0x1 << 1)
#define DMA2D_SUSP_UNMASK (~(0x1 << 1))
#define _dma2d_susp_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_SUSP_UNMASK, (value << 1))
#define _dma2d_susp_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_SUSP_MASK) >> 1)
// start the current transfer
#define DMA2D_START_MASK (0x1 << 0)
#define DMA2D_START_UNMASK (~(0x1 << 0))
#define _dma2d_start_set(dma2d, value) _reg_modify(dma2d->CR, DMA2D_START_UNMASK, (value << 0))
#define _dma2d_start_get(dma2d) ((_reg_read(dma2d->CR) & DMA2D_START_MASK) >> 0)
// dma2d control set
#define DMA2D_CTRL_MASK (0x33F07)
#define _dma2d_ctrl_set(dma2d, value) _reg_write(dma2d->CR, (value) & DMA2D_CTRL_MASK)
#define _dma2d_ctrl_get(dma2d) (_reg_read(dma2d->CR) & DMA2D_CTRL_MASK)

// dma2d interrupt status register
// configuration error interrupt flag
#define DMA2D_CEIF_MASK (0x1 << 5)
#define DMA2D_CEIF_UNMASK (~(0x1 << 5))
#define _dma2d_ceif_get(dma2d) ((_reg_read(dma2d->ISR) & DMA2D_CEIF_MASK) >> 5)
// CLUT transfer complete interrupt flag
#define DMA2D_CTCIF_MASK (0x1 << 4)
#define DMA2D_CTCIF_UNMASK (~(0x1 << 4))
#define _dma2d_ctcif_get(dma2d) ((_reg_read(dma2d->ISR) & DMA2D_CTCIF_MASK) >> 4)
// CLUT access error interrupt flag
#define DMA2D_CAEIF_MASK (0x1 << 3)
#define DMA2D_CAEIF_UNMASK (~(0x1 << 3))
#define _dma2d_caeif_get(dma2d) ((_reg_read(dma2d->ISR) & DMA2D_CAEIF_MASK) >> 3)
// transfer watermark interrupt flag
#define DMA2D_TWIF_MASK (0x1 << 2)
#define DMA2D_TWIF_UNMASK (~(0x1 << 2))
#define _dma2d_twif_get(dma2d) ((_reg_read(dma2d->ISR) & DMA2D_TWIF_MASK) >> 2)
// transfer complete interrupt flag
#define DMA2D_TCIF_MASK (0x1 << 1)
#define DMA2D_TCIF_UNMASK (~(0x1 << 1))
#define _dma2d_tcif_get(dma2d) ((_reg_read(dma2d->ISR) & DMA2D_CTCIF_MASK) >> 1)
// transfer error interrupt flag
#define DMA2D_TEIF_MASK (0x1 << 0)
#define DMA2D_TEIF_UNMASK (~(0x1 << 0))
#define _dma2d_teif_get(dma2d) ((_reg_read(dma2d->ISR) & DMA2D_TEIF_MASK) >> 0)
// dma2d interrupt status get
#define DMA2D_INTR_STATUS_MASK (0x3F)
#define _dma2d_intr_status_get(dma2d) (_reg_read(dma2d->ISR) & DMA2D_INTR_STATUS_MASK)

// dma2d interrupt flag clear register
// clear configuration error interrupt flag
#define DMA2D_CCEIF_MASK (0x1 << 5)
#define DMA2D_CCEIF_UNMASK (~(0x1 << 5))
#define _dma2d_cceif_clr(dma2d, value) _reg_modify(dma2d->IFCR, DMA2D_CCEIF_UNMASK, DMA2D_CCEIF_MASK)
// clear CLUT transfer complete interrupt flag
#define DMA2D_CCTCIF_MASK (0x1 << 4)
#define DMA2D_CCTCIF_UNMASK (~(0x1 << 4))
#define _dma2d_cctcif_clr(dma2d, value) _reg_modify(dma2d->IFCR, DMA2D_CCTCIF_UNMASK, DMA2D_CCTCIF_MASK)
// clear CLUT access error interrupt flag
#define DMA2D_CCAEIF_MASK (0x1 << 3)
#define DMA2D_CCAEIF_UNMASK (~(0x1 << 3))
#define _dma2d_ccaeif_clr(dma2d, value) _reg_modify(dma2d->IFCR, DMA2D_CCAEIF_UNMASK, DMA2D_CCAEIF_MASK)
// clear transfer watermark interrupt flag
#define DMA2D_CTWIF_MASK (0x1 << 2)
#define DMA2D_CTWIF_UNMASK (~(0x1 << 2))
#define _dma2d_ctwif_clr(dma2d, value) _reg_modify(dma2d->IFCR, DMA2D_CTWIF_UNMASK, DMA2D_CTWIF_MASK)
// clear transfer complete interrupt flag
#define DMA2D_CTCIFF_MASK (0x1 << 1)
#define DMA2D_CTCIFF_UNMASK (~(0x1 << 1))
#define _dma2d_ctcif_clr(dma2d, value) _reg_modify(dma2d->IFCR, DMA2D_CTCIFF_UNMASK, DMA2D_CTCIFF_MASK)
// clear transfer error interrupt flag
#define DMA2D_CTEIF_MASK (0x1 << 0)
#define DMA2D_CTEIF_UNMASK (~(0x1 << 0))
#define _dma2d_cteif_clr(dma2d, value) _reg_modify(dma2d->IFCR, DMA2D_CTEIF_UNMASK, DMA2D_CTEIF_MASK)
// clear dma2d interrupt status get
#define DMA2D_INTR_STATUS_MASK (0x3F)
#define _dma2d_intr_status_clr(dma2d, value) (_reg_write(dma2d->IFCR, value & DMA2D_INTR_STATUS_MASK))

// dma2d foreground memory address register (or rotate A layer register)
// foreground or A layer memory address
#define DMA2D_FG_ROTA_ADDR_MASK (0xFFFFFFFFF)
#define _dma2d_fg_rota_addr_set(dma2d, value) (_reg_write(dma2d->FG_ROTA_LAYER, value))
#define _dma2d_fg_rota_addr_get(dma2d) (_reg_read(dma2d->FG_ROTA_LAYER))

// dma2d foreground offset register
// foreground line offset
#define DMA2D_FG_LINE_OFFSET_MASK (0x3FFF << 0)
#define DMA2D_FG_LINE_OFFSET_UNMASK (~(0x3FFF << 0))
#define _dma2d_fg_offset_set(dma2d, value) (_reg_write(dma2d->FGOR, value & DMA2D_FG_LINE_OFFSET_MASK))
#define _dma2d_fg_offset_get(dma2d) (_reg_read(dma2d->FGOR) & DMA2D_FG_LINE_OFFSET_MASK)

// dma2d background memory address register (or rotate B layer register)
// background or B layer memory address
#define DMA2D_BG_ROTB_ADDR_MASK (0xFFFFFFFFF)
#define _dma2d_bg_rotb_addr_set(dma2d, value) (_reg_write(dma2d->BG_ROTB_LAYER, value))
#define _dma2d_bg_rotb_addr_get(dma2d) (_reg_read(dma2d->BG_ROTB_LAYER))

// dma2d background offset register
// background line offset
#define DMA2D_BG_LINE_OFFSET_MASK (0x3FFF << 0)
#define DMA2D_BG_LINE_OFFSET_UNMASK (~(0x3FFF << 0))
#define _dma2d_bg_offset_set(dma2d, value) (_reg_write(dma2d->BGOR, value & DMA2D_FG_LINE_OFFSET_MASK))
#define _dma2d_bg_offset_get(dma2d) (_reg_read(dma2d->BGOR) & DMA2D_FG_LINE_OFFSET_MASK)

// dma2d foreground PFC control register (or rotate A PFC register)
// foreground alpha value
#define DMA2D_FG_ROTA_ALPHA_MASK (0xFF << 24)
#define DMA2D_FG_ROTA_ALPHA_UNMASK (~(0xFF << 24))
#define _dma2d_fg_rota_alpha_set(dma2d, value) _reg_modify(dma2d->FG_ROTA_CTRL, DMA2D_FG_ROTA_ALPHA_UNMASK, (value << 24))
#define _dma2d_fg_rota_alpha_get(dma2d) ((_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_ROTA_ALPHA_MASK) >> 24)
// foreground alpha mode
#define DMA2D_FG_ROTA_ALPHA_AM_MASK (0x3 << 16)
#define DMA2D_FG_ROTA_ALPHA_AM_UNMASK (~(0x3 << 16))
#define _dma2d_fg_rota_alpha_am_set(dma2d, value) _reg_modify(dma2d->FG_ROTA_CTRL, DMA2D_FG_ROTA_ALPHA_AM_UNMASK, (value << 16))
#define _dma2d_fg_rota_alpha_am_get(dma2d) ((_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_ROTA_ALPHA_AM_MASK) >> 16)
// foreground CLUT size
#define DMA2D_FG_CLUT_SIZE_MASK (0xFF << 8)
#define DMA2D_FG_CLUT_SIZE_UNMASK (~(0xFF << 8))
#define _dma2d_fg_clut_size_set(dma2d, value) _reg_modify(dma2d->FG_ROTA_CTRL, DMA2D_FG_CLUT_SIZE_UNMASK, ((value - 1) << 24))
#define _dma2d_fg_clut_size_get(dma2d) (((_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_CLUT_SIZE_MASK) >> 24) + 1)
// foreground CLUT load
#define DMA2D_FG_CLUT_LOAD_MASK (0x1 << 5)
#define DMA2D_FG_CLUT_LOAD_UNMASK (~(0x1 << 5))
#define _dma2d_fg_clut_load_set(dma2d, value) _reg_modify(dma2d->FG_ROTA_CTRL, DMA2D_FG_CLUT_LOAD_UNMASK, (value << 5))
#define _dma2d_fg_clut_load_get(dma2d) ((_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_CLUT_LOAD_MASK) >> 5)
// foreground CLUT color mode
#define DMA2D_FG_CLUT_CM_MASK (0x1 << 4)
#define DMA2D_FG_CLUT_CM_UNMASK (~(0x1 << 4))
#define _dma2d_fg_clut_cm_set(dma2d, value) _reg_modify(dma2d->FG_ROTA_CTRL, DMA2D_FG_CLUT_CM_UNMASK, (value << 4))
#define _dma2d_fg_clut_cm_get(dma2d) ((_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_CLUT_CM_MASK) >> 4)
// foreground color mode
#define DMA2D_FG_ROTA_CM_MASK (0xF << 0)
#define DMA2D_FG_ROTA_CM_UNMASK (~(0xF << 0))
#define _dma2d_fg_cm_set(dma2d, value) _reg_modify(dma2d->FG_ROTA_CTRL, DMA2D_FG_ROTA_CM_UNMASK, (value << 0))
#define _dma2d_fg_cm_get(dma2d) ((_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_ROTA_CM_MASK) >> 0)
// foreground PFC control set
#define DMA2D_FG_ROTA_PFC_CTRL_MASK (0xFF03FF3F)
#define _dma2d_fg_rota_pfc_ctrl_set(dma2d, value) (_reg_write(dma2d->FG_ROTA_CTRL, value & DMA2D_FG_ROTA_PFC_CTRL_MASK))
#define _dma2d_fg_rota_pfc_ctrl_get(dma2d) (_reg_read(dma2d->FG_ROTA_CTRL) & DMA2D_FG_ROTA_PFC_CTRL_MASK)

// dma2d foreground color register (A4 or A8 mode)
// foreground red value
#define DMA2D_FG_RVAL_MASK (0xFF << 16)
#define DMA2D_FG_RVAL_UNMASK (~(0xFF << 16))
#define _dma2d_fg_r_val_set(dma2d, value) _reg_modify(dma2d->FGCOLR, DMA2D_FG_RVAL_UNMASK, (value << 16))
#define _dma2d_fg_r_val_get(dma2d) ((_reg_read(dma2d->FGCOLR) & DMA2D_FG_RVAL_MASK) >> 16)
// foreground green value
#define DMA2D_FG_GVAL_MASK (0xFF << 8)
#define DMA2D_FG_GVAL_UNMASK (~(0xFF << 8))
#define _dma2d_fg_g_val_set(dma2d, value) _reg_modify(dma2d->FGCOLR, DMA2D_FG_GVAL_UNMASK, (value << 8))
#define _dma2d_fg_g_val_get(dma2d) ((_reg_read(dma2d->FGCOLR) & DMA2D_FG_GVAL_MASK) >> 8)
// foreground blue value
#define DMA2D_FG_BVAL_MASK (0xFF << 0)
#define DMA2D_FG_BVAL_UNMASK (~(0xFF << 0))
#define _dma2d_fg_b_val_set(dma2d, value) _reg_modify(dma2d->FGCOLR, DMA2D_FG_BVAL_UNMASK, (value << 0))
#define _dma2d_fg_b_val_get(dma2d) (((_reg_read(dma2d->FGCOLR) & DMA2D_FG_BVAL_MASK) >> 0)
// foreground foreground colorl set
#define DMA2D_FG_COLOR_MASK (0xFFFFFF)
#define _dma2d_fg_color_set(dma2d, value) (_reg_write(dma2d->FGCOLR, value & DMA2D_FG_COLOR_MASK))
#define _dma2d_fg_color_get(dma2d) (_reg_read(dma2d->FGCOLR) & DMA2D_FG_COLOR_MASK)

// dma2d background PFC control register (or rotate B PFC register)
// background alpha value
#define DMA2D_BG_ROTB_ALPHA_MASK (0xFF << 24)
#define DMA2D_BG_ROTB_ALPHA_UNMASK (~(0xFF << 24))
#define _dma2d_bg_rotb_alpha_set(dma2d, value) _reg_modify(dma2d->BG_ROTB_CTRL, DMA2D_BG_ROTB_ALPHA_UNMASK, (value << 24))
#define _dma2d_bg_rotb_alpha_get(dma2d) ((_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_ROTB_ALPHA_MASK) >> 24)
// background alpha mode
#define DMA2D_BG_ROTB_ALPHA_AM_MASK (0x3 << 16)
#define DMA2D_BG_ROTB_ALPHA_AM_UNMASK (~(0x3 << 16))
#define _dma2d_bg_rotb_alpha_am_set(dma2d, value) _reg_modify(dma2d->BG_ROTB_CTRL, DMA2D_BG_ROTB_ALPHA_AM_UNMASK, (value << 16))
#define _dma2d_bg_rotb_alpha_am_get(dma2d) ((_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_ROTB_ALPHA_AM_MASK) >> 16)
// background CLUT size
#define DMA2D_BG_CLUT_SIZE_MASK (0xFF << 8)
#define DMA2D_BG_CLUT_SIZE_UNMASK (~(0xFF << 8))
#define _dma2d_bg_clut_size_set(dma2d, value) _reg_modify(dma2d->BG_ROTB_CTRL, DMA2D_BG_CLUT_SIZE_UNMASK, ((value - 1) << 24))
#define _dma2d_bg_clut_size_get(dma2d) (((_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_CLUT_SIZE_MASK) >> 24) + 1)
// background CLUT load
#define DMA2D_BG_CLUT_LOAD_MASK (0x1 << 5)
#define DMA2D_BG_CLUT_LOAD_UNMASK (~(0x1 << 5))
#define _dma2d_bg_clut_load_set(dma2d, value) _reg_modify(dma2d->BG_ROTB_CTRL, DMA2D_BG_CLUT_LOAD_UNMASK, (value << 5))
#define _dma2d_bg_clut_load_get(dma2d) ((_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_CLUT_LOAD_MASK) >> 5)
// background CLUT color mode
#define DMA2D_BG_CLUT_CM_MASK (0x1 << 4)
#define DMA2D_BG_CLUT_CM_UNMASK (~(0x1 << 4))
#define _dma2d_bg_clut_cm_set(dma2d, value) _reg_modify(dma2d->BG_ROTB_CTRL, DMA2D_BG_CLUT_CM_UNMASK, (value << 4))
#define _dma2d_bg_clut_cm_get(dma2d) ((_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_CLUT_CM_MASK) >> 4)
// background color mode
#define DMA2D_BG_ROTB_CM_MASK (0xF << 0)
#define DMA2D_BG_ROTB_CM_UNMASK (~(0xF << 0))
#define _dma2d_bg_cm_set(dma2d, value) _reg_modify(dma2d->BG_ROTB_CTRL, DMA2D_BG_ROTB_CM_UNMASK, (value << 0))
#define _dma2d_bg_cm_get(dma2d) ((_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_ROTB_CM_MASK) >> 0)
// background PFC control set
#define DMA2D_BG_ROTB_PFC_CTRL_MASK (0xFF03FF3F)
#define _dma2d_bg_rotb_pfc_ctrl_set(dma2d, value) (_reg_write(dma2d->BG_ROTB_CTRL, value & DMA2D_BG_ROTB_PFC_CTRL_MASK))
#define _dma2d_bg_rotb_pfc_ctrl_get(dma2d) (_reg_read(dma2d->BG_ROTB_CTRL) & DMA2D_BG_ROTB_PFC_CTRL_MASK)

// dma2d background color register (A4 or A8 mode)
// background red value
#define DMA2D_BG_RVAL_MASK (0xFF << 16)
#define DMA2D_BG_RVAL_UNMASK (~(0xFF << 16))
#define _dma2d_bg_r_val_set(dma2d, value) _reg_modify(dma2d->BGCOLR, DMA2D_BG_RVAL_UNMASK, (value << 16))
#define _dma2d_bg_r_val_get(dma2d) ((_reg_read(dma2d->BGCOLR) & DMA2D_BG_RVAL_MASK) >> 16)
// background green value
#define DMA2D_BG_GVAL_MASK (0xFF << 8)
#define DMA2D_BG_GVAL_UNMASK (~(0xFF << 8))
#define _dma2d_bg_g_val_set(dma2d, value) _reg_modify(dma2d->BGCOLR, DMA2D_BG_GVAL_UNMASK, (value << 8))
#define _dma2d_bg_g_val_get(dma2d) ((_reg_read(dma2d->BGCOLR) & DMA2D_BG_GVAL_MASK) >> 8)
// background blue value
#define DMA2D_BG_BVAL_MASK (0xFF << 0)
#define DMA2D_BG_BVAL_UNMASK (~(0xFF << 0))
#define _dma2d_bg_b_val_set(dma2d, value) _reg_modify(dma2d->BGCOLR, DMA2D_BG_BVAL_UNMASK, (value << 0))
#define _dma2d_bg_b_val_get(dma2d) (((_reg_read(dma2d->BGCOLR) & DMA2D_BG_BVAL_MASK) >> 0)
// background background colorl set
#define DMA2D_BG_COLOR_MASK (0xFFFFFF)
#define _dma2d_bg_color_set(dma2d, value) (_reg_write(dma2d->BGCOLR, value & DMA2D_BG_COLOR_MASK))
#define _dma2d_bg_color_get(dma2d) (_reg_read(dma2d->BGCOLR) & DMA2D_BG_COLOR_MASK)

// dma2d foreground CLUT memory address register
// foreground CLUT memory address
#define DMA2D_FG_CLUT_ADDR_MASK (0xFFFFFFFFF)
#define _dma2d_fg_clut_addr_set(dma2d, value) (_reg_write(dma2d->FGCMAR, value))
#define _dma2d_fg_clut_addr_get(dma2d) (_reg_read(dma2d->FGCMAR))

// dma2d background CLUT memory address register
// background CLUT memory address
#define DMA2D_BG_CLUT_ADDR_MASK (0xFFFFFFFFF)
#define _dma2d_bg_clut_addr_set(dma2d, value) (_reg_write(dma2d->BGCMAR, value))
#define _dma2d_bg_clut_addr_get(dma2d) (_reg_read(dma2d->BGCMAR))

// dma2d output PFC control register (or rotate C PFC register)
// output color mode
#define DMA2D_OUT_ROTC_CM_MASK (0xF)
#define _dma2d_out_rotc_cm_ctrl_set(dma2d, value) (_reg_write(dma2d->OUT_ROTC_CTRL, value & DMA2D_OUT_ROTC_CM_MASK))
#define _dma2d_out_rotc_cm_ctrl_get(dma2d) (_reg_read(dma2d->OUT_ROTC_CTRL) & DMA2D_OUT_ROTC_CM_MASK)

// dma2d output color register
// output alpha channel calue
#define DMA2D_OUT_ALPHA_VAL_MASK (0xFF << 24)
#define DMA2D_OUT_ALPHA_VAL_UNMASK (~(0xFF << 24))
#define _dma2d_out_alpha_val_set(dma2d, value) _reg_modify(dma2d->OCOLR, DMA2D_OUT_ALPHA_VAL_UNMASK, (value << 24))
#define _dma2d_out_alpha_val_get(dma2d) ((_reg_read(dma2d->OCOLR) & DMA2D_OUT_ALPHA_VAL_MASK) >> 24)
// output red value
#define DMA2D_OUT_RVAL_MASK (0xFF << 16)
#define DMA2D_OUT_RVAL_UNMASK (~(0xFF << 16))
#define _dma2d_out_r_val_set(dma2d, value) _reg_modify(dma2d->OCOLR, DMA2D_OUT_RVAL_UNMASK, (value << 16))
#define _dma2d_out_r_val_get(dma2d) ((_reg_read(dma2d->OCOLR) & DMA2D_OUT_RVAL_MASK) >> 16)
// output green value
#define DMA2D_OUT_GVAL_MASK (0xFF << 8)
#define DMA2D_OUT_GVAL_UNMASK (~(0xFF << 8))
#define _dma2d_out_g_val_set(dma2d, value) _reg_modify(dma2d->OCOLR, DMA2D_OUT_GVAL_UNMASK, (value << 8))
#define _dma2d_out_g_val_get(dma2d) ((_reg_read(dma2d->OCOLR) & DMA2D_OUT_GVAL_MASK) >> 8)
// output blue value
#define DMA2D_OUT_BVAL_MASK (0xFF << 0)
#define DMA2D_OUT_BVAL_UNMASK (~(0xFF << 0))
#define _dma2d_out_b_val_set(dma2d, value) _reg_modify(dma2d->OCOLR, DMA2D_OUT_BVAL_UNMASK, (value << 0))
#define _dma2d_out_b_val_get(dma2d) (((_reg_read(dma2d->OCOLR) & DMA2D_OUT_BVAL_MASK) >> 0)
// output color set
#define DMA2D_OUT_COLOR_MASK (0xFFFFFFFF)
#define _dma2d_out_color_set(dma2d, value) (_reg_write(dma2d->OCOLR, value))
#define _dma2d_out_color_get(dma2d) _reg_read(dma2d->OCOLR)

// dma2d output memory address register (or rotate C layer register)
// output or C layer memory address
#define DMA2D_OUT_ROTC_ADDR_MASK (0xFFFFFFFFF)
#define _dma2d_out_rotc_addr_set(dma2d, value) (_reg_write(dma2d->OUT_ROTC_LAYER, value))
#define _dma2d_out_rotc_addr_get(dma2d) (_reg_read(dma2d->OUT_ROTC_LAYER))

// dma2d output offset register
// output line offset
#define DMA2D_OUT_LINE_OFFSET_MASK (0x3FFF << 0)
#define DMA2D_OUT_LINE_OFFSET_UNMASK (~(0x3FFF << 0))
#define _dma2d_out_offset_set(dma2d, value) (_reg_write(dma2d->OOR, value & DMA2D_OUT_LINE_OFFSET_MASK))
#define _dma2d_out_offset_get(dma2d) (_reg_read(dma2d->OOR) & DMA2D_OUT_LINE_OFFSET_MASK)

// dma2d number of line register (or rotate A register)
// pixel per lines
#define DMA2D_FBG_ROTA_PIXEL_LINES_MASK (0x3FFF << 16)
#define DMA2D_FBG_ROTA_PIXEL_LINES_UNMASK (~(0x3FFF << 16))
#define _dma2d_fbg_rota_pixel_lines_set(dma2d, value) _reg_modify(dma2d->NLR_ROTA_SIZE, DMA2D_FBG_ROTA_PIXEL_LINES_UNMASK, (value << 16))
#define _dma2d_fbg_rota_pixel_lines_get(dma2d) (((_reg_read(dma2d->NLR_ROTA_SIZE) & DMA2D_FBG_ROTA_PIXEL_LINES_MASK) >> 16)
// number of lines
#define DMA2D_FBG_ROTA_NUMBER_LINES_MASK (0x3FFF << 0)
#define DMA2D_FBG_ROTA_NUMBER_LINES_UNMASK (~(0x3FFF << 0))
#define _dma2d_fbg_rota_number_lines_set(dma2d, value) _reg_modify(dma2d->NLR_ROTA_SIZE, DMA2D_FBG_ROTA_NUMBER_LINES_UNMASK, (value << 0))
#define _dma2d_fbg_rota_number_lines_get(dma2d) (((_reg_read(dma2d->NLR_ROTA_SIZE) & DMA2D_FBG_ROTA_NUMBER_LINES_MASK) >> 0)
// dma2d number of line set
#define DMA2D_FBG_ROTA_NUMBER_LINE_MASK (0x3FFF3FFF << 0)
#define _dma2d_fbg_rota_number_line_set(dma2d, value) (_reg_write(dma2d->NLR_ROTA_SIZE, value & DMA2D_FBG_ROTA_NUMBER_LINE_MASK))
#define _dma2d_fbg_rota_number_line_get(dma2d) (_reg_read(dma2d->NLR_ROTA_SIZE) & DMA2D_FBG_ROTA_NUMBER_LINE_MASK)

// dma2d line watermark register
// line watermark
#define DMA2D_LINE_WATERMARK_MASK (0xFFFF << 0)
#define _dma2d_line_watermark_set(dma2d, value) (_reg_write(dma2d->LWR, value & DMA2D_LINE_WATERMARK_MASK))
#define _dma2d_line_watermark_get(dma2d) (_reg_read(dma2d->LWR) & DMA2D_LINE_WATERMARK_MASK)

// dma2d AHB master timer configuration register
// dead time value
#define DMA2D_AHB_DEAD_TIME_VAL_MASK (0xFF << 8)
#define DMA2D_AHB_DEAD_TIME_VAL_UNMASK (~(0xFF << 8))
#define _dma2d_ahb_dead_time_val_set(dma2d, value) _reg_modify(dma2d->AMTCR, DMA2D_AHB_DEAD_TIME_VAL_UNMASK, (value << 8))
#define _dma2d_ahb_dead_time_val_get(dma2d) (((_reg_read(dma2d->AMTCR) & DMA2D_AHB_DEAD_TIME_VAL_MASK) >> 8)
// dead time function enable
#define DMA2D_AHB_DEAD_TIME_EN_MASK (0x1 << 0)
#define DMA2D_AHB_DEAD_TIME_EN_UNMASK (~(0x1 << 0))
#define _dma2d_ahb_dead_time_en_set(dma2d, value) _reg_modify(dma2d->AMTCR, DMA2D_AHB_DEAD_TIME_EN_UNMASK, (value << 0))
#define _dma2d_ahb_dead_time_en_get(dma2d) (((_reg_read(dma2d->AMTCR) & DMA2D_AHB_DEAD_TIME_EN_MASK) >> 0)
// dma2d AHB master timer configuration set
#define DMA2D_AHB_DEAD_TIME_CONFIG_MASK (0xFF01 << 0)
#define _dma2d_ahb_dead_time_config_set(dma2d, value) (_reg_write(dma2d->AMTCR, value & DMA2D_AHB_DEAD_TIME_CONFIG_MASK))
#define _dma2d_ahb_dead_time_config_get(dma2d) (_reg_read(dma2d->AMTCR) & DMA2D_AHB_DEAD_TIME_CONFIG_MASK)

// dma2d color byte swap configuration register (rgb2bgr)
// color byte swap enable
#define DMA2D_BYTE_SWAP_EN_MASK (0x1 << 2)
#define DMA2D_BYTE_SWAP_EN_UNMASK (~(0x1 << 2))
#define _dma2d_byte_swap_en_set(dma2d, value) _reg_modify(dma2d->RGB2BGR, DMA2D_BYTE_SWAP_EN_UNMASK, (value << 2))
#define _dma2d_byte_swap_en_get(dma2d) (((_reg_read(dma2d->RGB2BGR) & DMA2D_BYTE_SWAP_EN_MASK) >> 2)
// color byte swap mode
#define DMA2D_BYTE_SWAP_MODE_MASK (0x3 << 0)
#define DMA2D_BYTE_SWAP_MODE_UNMASK (~(0x3 << 0))
#define _dma2d_byte_swap_mode_set(dma2d, value) _reg_modify(dma2d->RGB2BGR, DMA2D_BYTE_SWAP_MODE_UNMASK, (value << 0))
#define _dma2d_byte_swap_mode_get(dma2d) (((_reg_read(dma2d->RGB2BGR) & DMA2D_BYTE_SWAP_MODE_MASK) >> 0)
// dma2d color byte swap configuration set
#define DMA2D_BYTE_SWAP_CONFIG_MASK (0x7 << 0)
#define _dma2d_byte_swap_config_set(dma2d, value) (_reg_write(dma2d->RGB2BGR, value & DMA2D_BYTE_SWAP_CONFIG_MASK))
#define _dma2d_byte_swap_config_get(dma2d) (_reg_read(dma2d->RGB2BGR) & DMA2D_BYTE_SWAP_CONFIG_MASK)

// dma2d rotate ant configuration register
// rotate ant with bilinear
#define DMA2D_ROT_ANY_BILINEAR_EN_MASK (0x1 << 6)
#define DMA2D_ROT_ANY_BILINEAR_EN_UNMASK (~(0x1 << 6))
#define _dma2d_rot_any_bilinear_set(dma2d, value) _reg_modify(dma2d->ROT_ANT, DMA2D_ROT_ANY_BILINEAR_EN_UNMASK, (value << 6))
#define _dma2d_rot_any_bilinear_get(dma2d) (((_reg_read(dma2d->ROT_ANT) & DMA2D_ROT_ANY_BILINEAR_EN_MASK) >> 6)
// rotate ant mode
#define DMA2D_ROT_ANT_MODE_MASK (0x3F << 0)
#define DMA2D_ROT_ANT_MODE_UNMASK (~(0x3F << 0))
#define _dma2d_rot_ant_mode_set(dma2d, value) _reg_modify(dma2d->ROT_ANT, DMA2D_ROT_ANT_MODE_UNMASK, (value << 0))
#define _dma2d_rot_ant_mode_get(dma2d) (((_reg_read(dma2d->ROT_ANT) & DMA2D_ROT_ANT_MODE_MASK) >> 0)
// rotate ant configuration set
#define DMA2D_ROT_ANT_CONFIG_MASK (0x7F << 0)
#define _dma2d_rot_ant_config_set(dma2d, value) (_reg_write(dma2d->ROT_ANT, value & DMA2D_ROT_ANT_CONFIG_MASK))
#define _dma2d_rot_ant_status_get(dma2d) (_reg_read(dma2d->ROT_ANT) & DMA2D_ROT_ANT_CONFIG_MASK)

// dma2d rotate sin value register
// sin value 
#define _dma2d_rot_sin_val_set(dma2d, value) (_reg_write_f(dma2d->ROT_SIN, value))
#define _dma2d_rot_sin_val_get(dma2d) (_reg_read_f(dma2d->ROT_SIN))

// dma2d rotate cos value register
// cos value 
#define _dma2d_rot_cos_val_set(dma2d, value) (_reg_write_f(dma2d->ROT_COS, value))
#define _dma2d_rot_cos_val_get(dma2d) (_reg_read_f(dma2d->ROT_COS))

// dma2d rotate A center configuration register
// rotate center x (width)
#define DMA2D_ROTA_CENTER_WIDTH_MASK (0x3FFF << 16)
#define DMA2D_ROTA_CENTER_WIDTH_UNMASK (~(0x3FFF << 16))
#define _dma2d_rota_center_width_set(dma2d, value) _reg_modify(dma2d->ROTA_CENTER, DMA2D_ROTA_CENTER_WIDTH_UNMASK, (value << 16))
#define _dma2d_rota_center_width_get(dma2d) (((_reg_read(dma2d->ROTA_CENTER) & DMA2D_ROTA_CENTER_WIDTH_MASK) >> 16)
// rotate center y (height)
#define DMA2D_ROTA_CENTER_HEIGHT_MASK (0x3FFF << 0)
#define DMA2D_ROTA_CENTER_HEIGHT_UNMASK (~(0x3FFF << 0))
#define _dma2d_rota_center_height_set(dma2d, value) _reg_modify(dma2d->ROTA_CENTER, DMA2D_ROTA_CENTER_HEIGHT_UNMASK, (value << 16))
#define _dma2d_rota_center_height_get(dma2d) (((_reg_read(dma2d->ROTA_CENTER) & DMA2D_ROTA_CENTER_HEIGHT_MASK) >> 16)
// rotate A center configuration set
#define DMA2D_ROTA_CENTER_CONFIG_MASK (0x3FFF3FFF << 0)
#define _dma2d_rota_center_config_set(dma2d, value) (_reg_write(dma2d->ROTA_CENTER, value & DMA2D_ROTA_CENTER_CONFIG_MASK))
#define _dma2d_rota_center_config_get(dma2d) (_reg_read(dma2d->ROTA_CENTER) & DMA2D_ROTA_CENTER_CONFIG_MASK)

// dma2d rotate B center configuration register
// rotate center x (width)
#define DMA2D_ROTB_CENTER_WIDTH_MASK (0x3FFF << 16)
#define DMA2D_ROTB_CENTER_WIDTH_UNMASK (~(0x3FFF << 16))
#define _dma2d_rotb_center_width_set(dma2d, value) _reg_modify(dma2d->ROTB_CENTER, DMA2D_ROTB_CENTER_WIDTH_UNMASK, (value << 16))
#define _dma2d_rotb_center_width_get(dma2d) (((_reg_read(dma2d->ROTB_CENTER) & DMA2D_ROTB_CENTER_WIDTH_MASK) >> 16)
// rotate center y (height)
#define DMA2D_ROTB_CENTER_HEIGHT_MASK (0x3FFF << 0)
#define DMA2D_ROTB_CENTER_HEIGHT_UNMASK (~(0x3FFF << 0))
#define _dma2d_rotb_center_height_set(dma2d, value) _reg_modify(dma2d->ROTB_CENTER, DMA2D_ROTB_CENTER_HEIGHT_UNMASK, (value << 16))
#define _dma2d_rotb_center_height_get(dma2d) (((_reg_read(dma2d->ROTB_CENTER) & DMA2D_ROTB_CENTER_HEIGHT_MASK) >> 16)
// rotate A center configuration set
#define DMA2D_ROTB_CENTER_CONFIG_MASK (0x3FFF3FFF << 0)
#define _dma2d_rotb_center_config_set(dma2d, value) (_reg_write(dma2d->ROTB_CENTER, value & DMA2D_ROTB_CENTER_CONFIG_MASK))
#define _dma2d_rotb_center_config_get(dma2d) (_reg_read(dma2d->ROTB_CENTER) & DMA2D_ROTB_CENTER_CONFIG_MASK)

// dma2d rotate B number of line register
// pixel per lines
#define DMA2D_ROTB_PIXEL_LINES_MASK (0x3FFF << 16)
#define DMA2D_ROTB_PIXEL_LINES_UNMASK (~(0x3FFF << 16))
#define _dma2d_rotb_pixel_lines_set(dma2d, value) _reg_modify(dma2d->ROTB_SIZE, DMA2D_ROTB_PIXEL_LINES_UNMASK, (value << 16))
#define _dma2d_rotb_pixel_lines_get(dma2d) (((_reg_read(dma2d->ROTB_SIZE) & DMA2D_ROTB_PIXEL_LINES_MASK) >> 16)
// number of lines
#define DMA2D_ROTB_NUMBER_LINES_MASK (0x3FFF << 0)
#define DMA2D_ROTB_NUMBER_LINES_UNMASK (~(0x3FFF << 0))
#define _dma2d_rotb_number_lines_set(dma2d, value) _reg_modify(dma2d->ROTB_SIZE, DMA2D_ROTB_NUMBER_LINES_UNMASK, (value << 0))
#define _dma2d_rotb_number_lines_get(dma2d) (((_reg_read(dma2d->ROTB_SIZE) & DMA2D_ROTB_NUMBER_LINES_MASK) >> 0)
// dma2d number of line set
#define DMA2D_ROTB_NUMBER_LINE_MASK (0x3FFF3FFF << 0)
#define _dma2d_rotb_number_line_set(dma2d, value) (_reg_write(dma2d->ROTB_SIZE, value & DMA2D_ROTB_NUMBER_LINE_MASK))
#define _dma2d_rotb_number_line_get(dma2d) (_reg_read(dma2d->ROTB_SIZE) & DMA2D_ROTB_NUMBER_LINE_MASK)

// 函数声明
void drv_dma2d_mode_clear(void);
status_t drv_dma2d_mode_set(dma_reg_t *pdma2d, dma2d_work_mode_t mode);
dma2d_work_mode_t drv_dma2d_mode_get(dma_reg_t *pdma2d);
status_t drv_dma2d_abort_en(dma_reg_t *pdma2d, uint32_t en);
status_t drv_dma2d_susp_en(dma_reg_t *pdma2d, uint32_t en);
status_t drv_dma2d_start_en(dma_reg_t *pdma2d, uint32_t en);
uint32_t drv_dma2d_intr_status_get(dma_reg_t *pdma2d);
status_t drv_dma2d_intr_status_clr(dma_reg_t *pdma2d, uint32_t status);
status_t drv_dma2d_fg_addr_set(dma_reg_t *pdma2d, uint32_t addr);
status_t drv_dma2d_rota_addr_set(dma_reg_t *pdma2d, uint32_t addr);
status_t drv_dma2d_fg_line_offset_set(dma_reg_t *pdma2d, uint32_t offset);
status_t drv_dma2d_bg_addr_set(dma_reg_t *pdma2d, uint32_t addr);
status_t drv_dma2d_rotb_addr_set(dma_reg_t *pdma2d, uint32_t addr);
status_t drv_dma2d_bg_line_offset_set(dma_reg_t *pdma2d, uint32_t offset);
status_t drv_dma2d_fg_pfc_alpha_set(dma_reg_t *pdma2d, uint32_t alpha, uint32_t alpha_mode);
status_t drv_dma2d_fg_color_mode_set(dma_reg_t *pdma2d, dma2d_color_mode_t color_mode);
status_t drv_dma2d_rota_color_mode_set(dma_reg_t *pdma2d, dma2d_color_mode_t color_mode);
status_t drv_dma2d_fg_pfc_clut_set(dma_reg_t *pdma2d, uint32_t clut_size, uint32_t clut_color_mode, uint32_t clut_start);
status_t drv_dma2d_fg_color_set(dma_reg_t *pdma2d, uint8_t r_val, uint8_t g_val, uint8_t b_val);
status_t drv_dma2d_bg_pfc_alpha_set(dma_reg_t *pdma2d, uint32_t alpha, uint32_t alpha_mode);
status_t drv_dma2d_bg_color_mode_set(dma_reg_t *pdma2d, dma2d_color_mode_t color_mode);
status_t drv_dma2d_rotb_color_mode_set(dma_reg_t *pdma2d, uint32_t color_mode);
status_t drv_dma2d_bg_pfc_clut_set(dma_reg_t *pdma2d, uint32_t clut_size, uint32_t clut_color_mode, uint32_t clut_start);
status_t drv_dma2d_bg_color_set(dma_reg_t *pdma2d, uint8_t r_val, uint8_t g_val, uint8_t b_val);
status_t drv_dma2d_fg_clut_addr_set(dma_reg_t *pdma2d, uint32_t clut_addr);
status_t drv_dma2d_bg_clut_addr_set(dma_reg_t *pdma2d, uint32_t clut_addr);
status_t drv_dma2d_output_color_mode_set(dma_reg_t *pdma2d, uint32_t color_mode);
status_t drv_dma2d_rotc_color_mode_set(dma_reg_t *pdma2d, uint32_t color_mode);
status_t drv_dma2d_output_color_set(dma_reg_t *pdma2d, uint32_t out_color);
status_t drv_dma2d_output_color_addr_set(dma_reg_t *pdma2d, uint32_t out_addr);
status_t drv_dma2d_rotc_color_addr_set(dma_reg_t *pdma2d, uint32_t out_addr);
status_t drv_dma2d_out_line_offset_set(dma_reg_t *pdma2d, uint32_t offset);
status_t drv_dma2d_pixels_and_lines_set(dma_reg_t *pdma2d, uint32_t pixels, uint32_t lines);
status_t drv_dma2d_rota_pixels_and_lines_set(dma_reg_t *pdma2d, uint32_t pixels, uint32_t lines);
status_t drv_dma2d_line_watermark_set(dma_reg_t *pdma2d, uint32_t wline);
status_t drv_dma2d_ahb_dead_time_set(dma_reg_t *pdma2d, uint32_t time_cycle, uint32_t en);
status_t drv_dma2d_byte_swap_set(dma_reg_t *pdma2d, uint32_t swap_mode, uint32_t en);
status_t drv_dma2d_rot_ant_config_set(dma_reg_t *pdma2d, dma2d_rot_ant_mode_t rot_ant_mode);
dma2d_rot_ant_mode_t drv_dma2d_rot_ant_status_get(dma_reg_t *pdma2d);
status_t drv_dma2d_rot_sin_val_set(dma_reg_t *pdma2d, float sinv);
status_t drv_dma2d_rot_cos_val_set(dma_reg_t *pdma2d, float cosv);
status_t drv_dma2d_rota_center_config_set(dma_reg_t *pdma2d, uint32_t center_w, uint32_t center_h);
status_t drv_dma2d_rotb_center_config_set(dma_reg_t *pdma2d, uint32_t center_w, uint32_t center_h);
status_t drv_dma2d_rotb_pixels_and_lines_set(dma_reg_t *pdma2d, uint32_t pixels, uint32_t lines);

#ifdef __cplusplus
}
#endif

#endif
