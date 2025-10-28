/**
 * @file lcdc_drv.h
 * @author Product application department
 * @brief  LCDC 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __LCDC_DRV_H
#define __LCDC_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "lcdc_reg.h"
#include "ioctrl_drv.h"
#include "eport_drv.h"
#include "color_def.h"
#include "status.h"
    
// 全局变量定义

// lcdc sync size register
// lcdc hsync, actual (hsync - 1)
#define LCDC_G_HSYNC_MASK (0xFFFF << 16)
#define LCDC_G_HSYNC_UNMASK (~(0xFFFF << 16))
#define _lcdc_g_hsync_set(lcdc_g, value) _reg_modify(lcdc_g->SYNC_SIZE, LCDC_G_HSYNC_UNMASK, ((value - 1) << 16))
#define _lcdc_g_hsync_get(lcdc_g) ((_reg_read(lcdc_g->SYNC_SIZE) >> 16) + 1)
// lcdc vsync, actual (vsync - 1)
#define LCDC_G_VSYNC_MASK (0xFFFF << 0)
#define LCDC_G_VSYNC_UNMASK (~(0xFFFF << 0))
#define _lcdc_g_vsync_set(lcdc_g, value) _reg_modify(lcdc_g->SYNC_SIZE, LCDC_G_VSYNC_UNMASK, ((value - 1) << 0))
#define _lcdc_g_vsync_get(lcdc_g) ((_reg_read(lcdc_g->SYNC_SIZE) & LCDC_G_VSYNC_MASK) + 1)
// lcdc sync size set
#define LCDC_G_SYNC_SIZE_MASK (0xFFFFFFFF)
#define _lcdc_g_sync_size_set(lcdc_g, value_h, value_v) _reg_write(lcdc_g->SYNC_SIZE, ((value_h - 1) << 16) | (value_v - 1) << 0)
#define _lcdc_g_sync_size_get(lcdc_g) _reg_read(lcdc_g->SYNC_SIZE)

// lcdc back porch register
// lcdc hsync, actual (hsync + hbp - 1)
#define LCDC_G_HBP_MASK (0xFFFF << 16)
#define LCDC_G_HBP_UNMASK (~(0xFFFF << 16))
#define _lcdc_g_hbp_set(lcdc_g, value) _reg_modify(lcdc_g->BACK_PORCH, LCDC_G_HBP_UNMASK, ((value - 1) << 16))
#define _lcdc_g_hbp_get(lcdc_g) ((_reg_read(lcdc_g->BACK_PORCH) >> 16) + 1)
// lcdc vsync, actual (vsync + vbp - 1)
#define LCDC_G_VBP_MASK (0xFFFF << 0)
#define LCDC_G_VBP_UNMASK (~(0xFFFF << 0))
#define _lcdc_g_vbp_set(lcdc_g, value) _reg_modify(lcdc_g->BACK_PORCH, LCDC_G_VBP_UNMASK, ((value - 1) << 0))
#define _lcdc_g_vbp_get(lcdc_g) ((_reg_read(lcdc_g->BACK_PORCH) & LCDC_G_VBP_MASK) + 1)
// lcdc back porch set
#define LCDC_G_BACK_PORCH_MASK (0xFFFFFFFF)
#define _lcdc_g_back_porch_set(lcdc_g, value_h, value_v) _reg_write(lcdc_g->BACK_PORCH, ((value_h - 1) << 16) | (value_v - 1) << 0)
#define _lcdc_g_back_porch_get(lcdc_g) _reg_read(lcdc_g->BACK_PORCH)

// lcdc active width register
// lcdc width, actual (hsync + hbp + width - 1)
#define LCDC_G_WIDTH_MASK (0xFFFF << 16)
#define LCDC_G_WIDTH_UNMASK (~(0xFFFF << 16))
#define _lcdc_g_width_set(lcdc_g, value) _reg_modify(lcdc_g->ACTIVE_WIDTH, LCDC_G_WIDTH_MASK, ((value - 1) << 16))
#define _lcdc_g_width_get(lcdc_g) ((_reg_read(lcdc_g->ACTIVE_WIDTH) >> 16) + 1)
// lcdc height, actual (vsync + vbp + height - 1)
#define LCDC_G_HEIGHT_MASK (0xFFFF << 0)
#define LCDC_G_HEIGHT_UNMASK (~(0xFFFF << 0))
#define _lcdc_g_height_set(lcdc_g, value) _reg_modify(lcdc_g->ACTIVE_WIDTH, LCDC_G_HEIGHT_UNMASK, ((value - 1) << 0))
#define _lcdc_g_height_get(lcdc_g) ((_reg_read(lcdc_g->ACTIVE_WIDTH) & LCDC_G_HEIGHT_MASK) + 1)
// lcdc active width set
#define LCDC_G_ACTIVE_WIDTH_MASK (0xFFFFFFFF)
#define _lcdc_g_active_width_set(lcdc_g, value_w, value_h) _reg_write(lcdc_g->ACTIVE_WIDTH, ((value_w - 1) << 16) | (value_h - 1) << 0)
#define _lcdc_g_active_width_get(lcdc_g) _reg_read(lcdc_g->ACTIVE_WIDTH)

// lcdc total width register
// lcdc hfp, actual (hsync + hbp + width + hfp - 1)
#define LCDC_G_HFP_MASK (0xFFFF << 16)
#define LCDC_G_HFP_UNMASK (~(0xFFFF << 16))
#define _lcdc_g_hfp_set(lcdc_g, value) _reg_modify(lcdc_g->TOTAL_WIDTH, LCDC_G_HFP_UNMASK, ((value - 1) << 16))
#define _lcdc_g_hfp_get(lcdc_g) ((_reg_read(lcdc_g->TOTAL_WIDTH) >> 16) + 1)
// lcdc vfp, actual (vsync + vbp + height + vfp - 1)
#define LCDC_G_VFP_MASK (0xFFFF << 0)
#define LCDC_G_VFP_UNMASK (~(0xFFFF << 0))
#define _lcdc_g_vfp_set(lcdc_g, value) _reg_modify(lcdc_g->TOTAL_WIDTH, LCDC_G_VFP_UNMASK, ((value - 1) << 0))
#define _lcdc_g_vfp_get(lcdc_g) ((_reg_read(lcdc_g->TOTAL_WIDTH) & LCDC_G_VFP_MASK) + 1)
// lcdc active width set
#define LCDC_G_TOTAL_WIDTH_MASK (0xFFFFFFFF)
#define _lcdc_g_total_width_set(lcdc_g, value_h, value_v) _reg_write(lcdc_g->TOTAL_WIDTH, ((value_h - 1) << 16) | (value_v - 1) << 0)
#define _lcdc_g_total_width_get(lcdc_g) _reg_read(lcdc_g->TOTAL_WIDTH)

// lcdc global control register
// lcdc crc enable
#define LCDC_CRC_EN_MASK (0x1 << 19)
#define LCDC_CRC_EN_UNMASK (~(0x1 << 19))
#define _lcdc_g_crc_en_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_CRC_EN_UNMASK, ((value & 0x1) << 19))
#define _lcdc_g_crc_en_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_CRC_EN_MASK) >> 19)
// lcdc background layer on
#define LCDC_G_BACKGROUND_ON_MASK (0x1 << 17)
#define LCDC_G_BACKGROUND_ON_UNMASK (~(0x1 << 17))
#define _lcdc_g_background_on_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_BACKGROUND_ON_UNMASK, ((value & 0x1) << 17))
#define _lcdc_g_background_on_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_BACKGROUND_ON_MASK) >> 17)
// lcdc dithering enable
#define LCDC_G_DITHERING_ON_MASK (0x1 << 16)
#define LCDC_G_DITHERING_ON_UNMASK (~(0x1 << 16))
#define _lcdc_g_dither_en_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_DITHERING_ON_UNMASK, ((value & 0x1) << 16))
#define _lcdc_g_dither_en_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_DITHERING_ON_MASK) >> 16)
// lcdc dither bits width for red (0-4)
#define LCDC_G_DITHER_RED_ON_MASK (0x7 << 12)
#define LCDC_G_DITHER_RED_ON_UNMASK (~(0x7 << 12))
#define _lcdc_g_dither_red_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_DITHER_RED_ON_UNMASK, ((value & 0x7) << 12))
#define _lcdc_g_dither_red_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_DITHER_RED_ON_MASK) >> 12)
// lcdc dither bits width for green (0-4)
#define LCDC_G_DITHER_GREEN_ON_MASK (0x7 << 8)
#define LCDC_G_DITHER_GREEN_ON_UNMASK (~(0x7 << 8))
#define _lcdc_g_dither_green_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_DITHER_GREEN_ON_UNMASK, ((value & 0x7) << 8))
#define _lcdc_g_dither_green_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_DITHER_GREEN_ON_MASK) >> 12)
// lcdc dither bits width for blue (0-4)
#define LCDC_G_DITHER_BLUE_ON_MASK (0x7 << 4)
#define LCDC_G_DITHER_BLUE_ON_UNMASK (~(0x7 << 4))
#define _lcdc_g_dither_blue_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_DITHER_BLUE_ON_UNMASK, ((value & 0x7) << 4))
#define _lcdc_g_dither_blue_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_DITHER_BLUE_ON_MASK) >> 12)
// lcdc gamma correction enable
#define LCDC_G_GAMMA_CORRECTION_EN_MASK (0x1 << 1)
#define LCDC_G_GAMMA_CORRECTION_EN_UNMASK (~(0x1 << 1))
#define _lcdc_g_gamma_correction_en_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_GAMMA_CORRECTION_EN_UNMASK, ((value & 0x1) << 1))
#define _lcdc_g_gamma_correction_en_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_GAMMA_CORRECTION_EN_MASK) >> 1)
// lcdc global enable
#define LCDC_G_GLOBAL_EN_MASK (0x1 << 0)
#define LCDC_G_GLOBAL_EN_UNMASK (~(0x1 << 0))
#define _lcdc_g_global_en_set(lcdc_g, value) _reg_modify(lcdc_g->GLOBAL_CONTROL, LCDC_G_GLOBAL_EN_UNMASK, ((value & 0x1) << 0))
#define _lcdc_g_global_en_get(lcdc_g) ((_reg_read(lcdc_g->GLOBAL_CONTROL) & LCDC_G_GLOBAL_EN_MASK) >> 0)
// lcdc global control set
#define LCDC_G_GLOBAL_CONTROL_MASK (0xB7773)
#define _lcdc_g_global_control_set(lcdc_g, value) _reg_write(lcdc_g->GLOBAL_CONTROL, value &LCDC_G_GLOBAL_CONTROL_MASK)
#define _lcdc_g_global_control_get(lcdc_g) _reg_read(lcdc_g->GLOBAL_CONTROL)

// lcdc shadow reload control register
// lcdc vertical blanking reload
#define LCDC_G_VERTICAL_RELOAD_MASK (0x1 << 1)
#define LCDC_G_VERTICAL_RELOAD_UNMASK (~(0x1 << 1))
#define _lcdc_g_vertical_reload_set(lcdc_g, value) _reg_modify(lcdc_g->SHADOW_RELOAD_CONTROL, LCDC_G_VERTICAL_RELOAD_UNMASK, ((value & 0x1) << 1))
#define _lcdc_g_vertical_reload_get(lcdc_g) ((_reg_read(lcdc_g->SHADOW_RELOAD_CONTROL) & LCDC_G_VERTICAL_RELOAD_MASK) >> 1)
// lcdc immediate reload
#define LCDC_G_IMMEDIATE_RELOAD_MASK (0x1 << 0)
#define LCDC_G_IMMEDIATE_RELOAD_UNMASK (~(0x1 << 0))
#define _lcdc_g_immediate_reload_set(lcdc_g, value) _reg_modify(lcdc_g->SHADOW_RELOAD_CONTROL, LCDC_G_IMMEDIATE_RELOAD_UNMASK, ((value & 0x1) << 0))
#define _lcdc_g_immediate_reload_get(lcdc_g) ((_reg_read(lcdc_g->SHADOW_RELOAD_CONTROL) & LCDC_G_IMMEDIATE_RELOAD_MASK) >> 0)
// lcdc shadow reload control set
#define LCDC_G_SHADOW_RELOAD_CONTROL_MASK (0x3)
#define _lcdc_g_shadow_reload_ctrl_set(lcdc_g, value) _reg_write(lcdc_g->SHADOW_RELOAD_CONTROL, (value & LCDC_G_SHADOW_RELOAD_CONTROL_MASK))
#define _lcdc_g_shadow_reload_ctrl_get(lcdc_g) _reg_read(lcdc_g->SHADOW_RELOAD_CONTROL)

// lcdc gamma correction register
// lcdc select red CLUT
#define LCDC_G_SELECT_RED_CLUT_MASK (0x1 << 18)
#define LCDC_G_SELECT_RED_CLUT_UNMASK (~(0x1 << 18))
#define _lcdc_g_select_red_set(lcdc_g, value) _reg_modify(lcdc_g->GAMMA_CORRECTION, LCDC_G_SELECT_RED_CLUT_UNMASK, ((value & 0x1) << 18))
#define _lcdc_g_select_red_get(lcdc_g) ((_reg_read(lcdc_g->GAMMA_CORRECTION) & LCDC_G_SELECT_RED_CLUT_MASK) >> 18)
// lcdc select green CLUT
#define LCDC_G_SELECT_GREEN_CLUT_MASK (0x1 << 17)
#define LCDC_G_SELECT_GREEN_CLUT_UNMASK (~(0x1 << 17))
#define _lcdc_g_select_green_set(lcdc_g, value) _reg_modify(lcdc_g->GAMMA_CORRECTION, LCDC_G_SELECT_GREEN_CLUT_UNMASK, ((value & 0x1) << 17))
#define _lcdc_g_select_green_get(lcdc_g) ((_reg_read(lcdc_g->GAMMA_CORRECTION) & LCDC_G_SELECT_GREEN_CLUT_MASK) >> 17)
// lcdc select blue CLUT
#define LCDC_G_SELECT_BLUE_CLUT_MASK (0x1 << 16)
#define LCDC_G_SELECT_BLUE_CLUT_UNMASK (~(0x1 << 16))
#define _lcdc_g_select_blue_set(lcdc_g, value) _reg_modify(lcdc_g->GAMMA_CORRECTION, LCDC_G_SELECT_BLUE_CLUT_UNMASK, ((value & 0x1) << 16))
#define _lcdc_g_select_blue_get(lcdc_g) ((_reg_read(lcdc_g->GAMMA_CORRECTION) & LCDC_G_SELECT_BLUE_CLUT_MASK) >> 16)
// lcdc mapped color (RGB)
#define LCDC_G_MAPPED_COLOR_MASK (0xFF << 8)
#define LCDC_G_MAPPED_COLOR_UNMASK (~(0xFF << 8))
#define _lcdc_g_mapped_color_set(lcdc_g, value) _reg_modify(lcdc_g->GAMMA_CORRECTION, LCDC_G_MAPPED_COLOR_UNMASK, ((value & 0xFF) << 8))
#define _lcdc_g_mapped_color_get(lcdc_g) ((_reg_read(lcdc_g->GAMMA_CORRECTION) & LCDC_G_MAPPED_COLOR_MASK) >> 8)
// lcdc addressed color
#define LCDC_G_ADDR_COLOR_MASK (0xFF << 0)
#define LCDC_G_ADDR_COLOR_UNMASK (~(0xFF << 0))
#define _lcdc_g_addr_color_set(lcdc_g, value) _reg_modify(lcdc_g->GAMMA_CORRECTION, LCDC_G_ADDR_COLOR_UNMASK, ((value & 0xFF) << 0))
#define _lcdc_g_addr_color_get(lcdc_g) ((_reg_read(lcdc_g->GAMMA_CORRECTION) & LCDC_G_ADDR_COLOR_MASK) >> 0)
// lcdc  gamma correction set
#define LCDC_G_GAMMA_CORRECTION_MASK (0x7FFFF)
#define _lcdc_g_gamma_correction_set(lcdc_g, value) _reg_write(lcdc_g->GAMMA_CORRECTION, (value & LCDC_G_GAMMA_CORRECTION_MASK))
#define _lcdc_g_gamma_correction_get(lcdc_g) _reg_read(lcdc_g->GAMMA_CORRECTION)

// lcdc background color register
// lcdc background color
#define LCDC_G_BACKGROUND_COLOR_MASK (0xFFFFFF << 0)
#define LCDC_G_BACKGROUND_COLOR_UNMASK (~(0xFFFFFF << 0))
#define _lcdc_g_background_color_set(lcdc_g, value) _reg_write(lcdc_g->BACKGROUND_COLOR, (value & LCDC_G_BACKGROUND_COLOR_MASK))
#define _lcdc_g_background_color_get(lcdc_g) _reg_read(lcdc_g->BACKGROUND_COLOR)

// lcdc irq enable register
// lcdc crc irq on
#define LCDC_G_CRC_IRQ_ON_MASK (0x1 << 7)
#define LCDC_G_CRC_IRQ_ON_UNMASK (~(0x1 << 7))
#define _lcdc_g_crc_irq_on_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_CRC_IRQ_ON_UNMASK, ((value & 0x1) << 7))
#define _lcdc_g_crc_irq_on_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_CRC_IRQ_ON_MASK) >> 7)
// lcdc fifo underrun killing irq on
#define LCDC_G_FIFO_UNDER_KILL_IRQ_ON_MASK (0x1 << 6)
#define LCDC_G_FIFO_UNDER_KILL_IRQ_ON_UNMASK (~(0x1 << 6))
#define _lcdc_g_fifo_under_kill_irq_on_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_FIFO_UNDER_KILL_IRQ_ON_UNMASK, ((value & 0x1) << 6))
#define _lcdc_g_fifo_under_kill_irq_on_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_FIFO_UNDER_KILL_IRQ_ON_MASK) >> 6)
// lcdc register reload irq on
#define LCDC_G_REG_RELOAD_IRQ_ON_MASK (0x1 << 3)
#define LCDC_G_REG_RELOAD_IRQ_ON_UNMASK (~(0x1 << 3))
#define _lcdc_g_reg_reload_irq_on_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_REG_RELOAD_IRQ_ON_UNMASK, ((value & 0x1) << 3))
#define _lcdc_g_reg_reload_irq_on_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_REG_RELOAD_IRQ_ON_MASK) >> 3)
// lcdc fifo underrun warning irq on
#define LCDC_G_FIFO_UNDER_WARN_IRQ_ON_MASK (0x1 << 1)
#define LCDC_G_FIFO_UNDER_WARN_IRQ_ON_UNMASK (~(0x1 << 1))
#define _lcdc_g_fifo_under_warn_irq_on_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_FIFO_UNDER_WARN_IRQ_ON_UNMASK, ((value & 0x1) << 1))
#define _lcdc_g_fifo_under_warn_irq_on_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_FIFO_UNDER_WARN_IRQ_ON_MASK) >> 1)
// lcdc line irq on
#define LCDC_G_LINE_IRQ_ON_MASK (0x1 << 0)
#define LCDC_G_LINE_IRQ_ON_UNMASK (~(0x1 << 0))
#define _lcdc_g_line_irq_on_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_LINE_IRQ_ON_UNMASK, ((value & 0x1) << 0))
#define _lcdc_g_line_irq_on_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_LINE_IRQ_ON_MASK) >> 0)
// lcdc irq enable set
#define LCDC_G_IRQ_EN_MASK (0xCB) // (0x1FF)
#define _lcdc_g_irq_en_set(lcdc_g, value) _reg_write(lcdc_g->IRQ_ENABLE, (value & LCDC_G_IRQ_EN_MASK))
#define _lcdc_g_irq_en_get(lcdc_g) _reg_read(lcdc_g->IRQ_ENABLE)

// lcdc irq status register
// lcdc crc irq status
#define LCDC_G_CRC_IRQ_STATUS_MASK (0x1 << 7)
#define LCDC_G_CRC_IRQ_STATUS_UNMASK (~(0x1 << 7))
#define _lcdc_g_crc_irq_status_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_CRC_IRQ_STATUS_MASK) >> 7)
// lcdc fifo underrun killing irq status
#define LCDC_G_FIFO_UNDER_KILL_IRQ_STATUS_MASK (0x1 << 6)
#define LCDC_G_FIFO_UNDER_KILL_IRQ_STATUS_UNMASK (~(0x1 << 6))
#define _lcdc_g_fifo_under_kill_irq_STATUS_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_FIFO_UNDER_KILL_IRQ_STATUS_MASK) >> 6)
// lcdc register reload irq status
#define LCDC_G_REG_RELOAD_IRQ_STATUS_MASK (0x1 << 3)
#define LCDC_G_REG_RELOAD_IRQ_STATUS_UNMASK (~(0x1 << 3))
#define _lcdc_g_reg_reload_irq_STATUS_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_REG_RELOAD_IRQ_STATUS_MASK) >> 3)
// lcdc fifo underrun warning irq status
#define LCDC_G_FIFO_UNDER_WARN_IRQ_STATUS_MASK (0x1 << 1)
#define LCDC_G_FIFO_UNDER_WARN_IRQ_STATUS_UNMASK (~(0x1 << 1))
#define _lcdc_g_fifo_under_warn_irq_STATUS_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_FIFO_UNDER_WARN_IRQ_STATUS_MASK) >> 1)
// lcdc line irq status
#define LCDC_G_LINE_IRQ_STATUS_MASK (0x1 << 0)
#define LCDC_G_LINE_IRQ_STATUS_UNMASK (~(0x1 << 0))
#define _lcdc_g_line_irq_STATUS_get(lcdc_g) ((_reg_read(lcdc_g->IRQ_ENABLE) & LCDC_G_LINE_IRQ_STATUS_MASK) >> 0)



// lcdc irq clear register
// lcdc crc irq clear
#define LCDC_G_CRC_IRQ_CLEAR_MASK (0x1 << 7)
#define LCDC_G_CRC_IRQ_CLEAR_UNMASK (~(0x1 << 7))
#define _lcdc_g_crc_irq_clr_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_CRC_IRQ_CLEAR_UNMASK, ((value & 0x1) << 7))
// lcdc fifo underrun killing irq clear
#define LCDC_G_FIFO_UNDER_KILL_IRQ_CLEAR_MASK (0x1 << 6)
#define LCDC_G_FIFO_UNDER_KILL_IRQ_CLEAR_UNMASK (~(0x1 << 6))
#define _lcdc_g_fifo_under_kill_irq_clr_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_FIFO_UNDER_KILL_IRQ_CLEAR_UNMASK, ((value & 0x1) << 6))
// lcdc register reload irq clear
#define LCDC_G_REG_RELOAD_IRQ_CLEAR_MASK (0x1 << 3)
#define LCDC_G_REG_RELOAD_IRQ_CLEAR_UNMASK (~(0x1 << 3))
#define _lcdc_g_reg_reload_irq_clr_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_REG_RELOAD_IRQ_CLEAR_UNMASK, ((value & 0x1) << 3))
// lcdc fifo underrun warning irq clear
#define LCDC_G_FIFO_UNDER_WARN_IRQ_CLEAR_MASK (0x1 << 1)
#define LCDC_G_FIFO_UNDER_WARN_IRQ_CLEAR_UNMASK (~(0x1 << 1))
#define _lcdc_g_fifo_under_warn_irq_clr_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_FIFO_UNDER_WARN_IRQ_CLEAR_UNMASK, ((value & 0x1) << 1))
// lcdc line irq clear
#define LCDC_G_LINE_IRQ_CLEAR_MASK (0x1 << 0)
#define LCDC_G_LINE_IRQ_CLEAR_UNMASK (~(0x1 << 0))
#define _lcdc_g_line_irq_clr_set(lcdc_g, value) _reg_modify(lcdc_g->IRQ_ENABLE, LCDC_G_LINE_IRQ_CLEAR_UNMASK, ((value & 0x1) << 0))
// lcdc irq clear
#define LCDC_G_IRQ_CLEAR_MASK (0xCB) // (0x1FF)
#define _lcdc_g_irq_clr_set(lcdc_g, value) _reg_write(lcdc_g->IRQ_ENABLE, (value & LCDC_G_IRQ_CLEAR_MASK))

//lcdc irq status
#define LCDC_G_REG_IRQ_STAT (0x1 << 3)
#define _lcdc_g_irq_status_get(lcdc_g) _reg_read(lcdc_g->IRQ_STATUS)

//lcdc irq clear
#define LCDC_G_REG_IRQ_CLEAR_MASK (0xff)
#define LCDC_G_REG_RLIRQ_CLEAR_MASK (1<<3)
#define _lcdc_g_irq_status_clear(lcdc_g,value) _reg_write(lcdc_g->IRQ_CLEAR, (value & LCDC_G_REG_IRQ_CLEAR_MASK))

// lcdc line irq position control register
// lcdc line irq position control
#define LCDC_G_LINE_IRQ_POSITION_CTRL_MASK (0xFFFF)
#define LCDC_G_LINE_IRQ_POSITION_CTRL_UNMASK (~(0xFFFF << 0))
#define _lcdc_g_line_irq_position_ctrl_set(lcdc_g, value) _reg_write(lcdc_g->LINE_IRQ_POS_CONTROL, ((value - 1) & LCDC_G_LINE_IRQ_POSITION_CTRL_MASK))
#define _lcdc_g_line_irq_position_ctrl_get(lcdc_g) _reg_read(lcdc_g->LINE_IRQ_POS_CONTROL)

// Todo: l1 and l2 register
// lcdc layer control register
// lcdc default color blending enable
#define LCDC_L_COLOR_BLENDING_EN_MASK (0x1 << 9)
#define LCDC_L_COLOR_BLENDING_EN_UNMASK (~(0x1 << 9))
#define _lcdc_l_color_blend_en_set(lcdc_l, value) _reg_modify(lcdc_l->CONTROL, LCDC_L_COLOR_BLENDING_EN_UNMASK, ((value & 0x1) << 9))
#define _lcdc_l_color_blend_en_get(lcdc_l) ((_reg_read(lcdc_l->CONTROL) & LCDC_L_COLOR_BLENDING_EN_MASK) >> 9)
// lcdc horizontal mirroring enable
#define LCDC_L_HOR_MIRROR_EN_MASK (0x1 << 8)
#define LCDC_L_HOR_MIRROR_EN_UNMASK (~(0x1 << 8))
#define _lcdc_l_hor_mirror_en_set(lcdc_l, value) _reg_modify(lcdc_l->CONTROL, LCDC_L_HOR_MIRROR_EN_UNMASK, ((value & 0x1) << 8))
#define _lcdc_l_hor_mirror_en_get(lcdc_l) ((_reg_read(lcdc_l->CONTROL) & LCDC_L_HOR_MIRROR_EN_MASK) >> 8)
// lcdc color key replace On
#define LCDC_L_COLOR_KEY_REPLACE_ON_MASK (0x1 << 5)
#define LCDC_L_COLOR_KEY_REPLACE_ON_UNMASK (~(0x1 << 5))
#define _lcdc_l_color_key_replace_on_set(lcdc_l, value) _reg_modify(lcdc_l->CONTROL, LCDC_L_COLOR_KEY_REPLACE_ON_UNMASK, ((value & 0x1) << 5))
#define _lcdc_l_color_key_replace_on_get(lcdc_l) ((_reg_read(lcdc_l->CONTROL) & LCDC_L_COLOR_KEY_REPLACE_ON_MASK) >> 5)
// lcdc CLUT lookup on
#define LCDC_L_CLUT_LOOKUP_ON_MASK (0x1 << 4)
#define LCDC_L_CLUT_LOOKUP_ON_UNMASK (~(0x1 << 4))
#define _lcdc_l_clut_lookup_on_set(lcdc_l, value) _reg_modify(lcdc_l->CONTROL, LCDC_L_CLUT_LOOKUP_ON_UNMASK, ((value & 0x1) << 4))
#define _lcdc_l_clut_lookup_on_get(lcdc_l) ((_reg_read(lcdc_l->CONTROL) & LCDC_L_CLUT_LOOKUP_ON_MASK) >> 4)
// lcdc color key feature on
#define LCDC_L_COLOR_KEY_FEATURE_ON_MASK (0x1 << 1)
#define LCDC_L_COLOR_KEY_FEATURE_ON_UNMASK (~(0x1 << 1))
#define _lcdc_l_color_key_feature_on_set(lcdc_l, value) _reg_modify(lcdc_l->CONTROL, LCDC_L_COLOR_KEY_FEATURE_ON_UNMASK, ((value & 0x1) << 1))
#define _lcdc_l_color_key_feature_on_get(lcdc_l) ((_reg_read(lcdc_l->CONTROL) & LCDC_L_COLOR_KEY_FEATURE_ON_MASK) >> 1)
// lcdc laver on
#define LCDC_L_LAYER_ON_MASK (0x1 << 0)
#define LCDC_L_LAYER_ON_UNMASK (~(0x1 << 0))
#define _lcdc_l_layer_on_set(lcdc_l, value) _reg_modify(lcdc_l->CONTROL, LCDC_L_LAYER_ON_UNMASK, ((value & 0x1) << 0))
#define _lcdc_l_layer_on_get(lcdc_l) ((_reg_read(lcdc_l->CONTROL) & LCDC_L_LAYER_ON_MASK) >> 0)
// lcdc layer control set
#define LCDC_L_LAYER_CTRL_MASK (0x333)
#define _lcdc_l_layer_ctrl_set(lcdc_l, value) _reg_write(lcdc_l->CONTROL, (value & LCDC_L_LAYER_CTRL_MASK))
#define _lcdc_l_layer_ctrl_get(lcdc_l) _reg_read(lcdc_l->CONTROL)

// lcdc window horizontal position register
// lcdc horizontal stop position, actual (hsync + hbp + width - 1)
#define LCDC_L_HOR_STOP_POS_MASK (0xFFFF << 16)
#define LCDC_L_HOR_STOP_POS_UNMASK (~(0xFFFF << 16))
#define _lcdc_l_hor_stop_pos_set(lcdc_l, value) _reg_modify(lcdc_l->WINDOW_H_POS, LCDC_L_HOR_STOP_POS_UNMASK, (((value - 1) & 0xFFFF) << 16))
#define _lcdc_l_hor_stop_pos_get(lcdc_l) ((_reg_read(lcdc_l->WINDOW_H_POS) & LCDC_L_HOR_STOP_POS_MASK) >> 16)
// lcdc horizontal start position, actual (hsync + hbp - 1)
#define LCDC_L_HOR_START_POS_MASK (0xFFFF << 0)
#define LCDC_L_HOR_START_POS_UNMASK (~(0xFFFF << 0))
#define _lcdc_l_hor_start_pos_set(lcdc_l, value) _reg_modify(lcdc_l->WINDOW_H_POS, LCDC_L_HOR_START_POS_UNMASK, ((value & 0xFFFF) << 0))
#define _lcdc_l_hor_start_pos_get(lcdc_l) ((_reg_read(lcdc_l->WINDOW_H_POS) & LCDC_L_HOR_START_POS_MASK) >> 0)
// lcdc window horizontal position set
#define LCDC_L_WINDOW_HOR_POS_MASK (0xFFFFFFFF)
#define _lcdc_l_window_hor_pos_set(lcdc_l, value_p, value_t) _reg_write(lcdc_l->WINDOW_H_POS, ((value_p - 1) << 16) | value_t << 0)
#define _lcdc_l_window_hor_pos_get(lcdc_l) _reg_read(lcdc_l->WINDOW_H_POS)

// lcdc window vertical position register
// lcdc vertical stop position, actual (vsync + vbp + height - 1)
#define LCDC_L_VER_STOP_POS_MASK (0xFFFF << 16)
#define LCDC_L_VER_STOP_POS_UNMASK (~(0xFFFF << 16))
#define _lcdc_l_ver_stop_pos_set(lcdc_l, value) _reg_modify(lcdc_l->WINDOW_V_POS, LCDC_L_VER_STOP_POS_UNMASK, (((value - 1) & 0xFFFF) << 16))
#define _lcdc_l_ver_stop_pos_get(lcdc_l) ((_reg_read(lcdc_l->WINDOW_V_POS) & LCDC_L_VER_STOP_POS_MASK) >> 16)
// lcdc vertical start position, actual (vsync + vbp - 1)
#define LCDC_L_VER_START_POS_MASK (0xFFFF << 0)
#define LCDC_L_VER_START_POS_UNMASK (~(0xFFFF << 0))
#define _lcdc_l_ver_start_pos_set(lcdc_l, value) _reg_modify(lcdc_l->WINDOW_V_POS, LCDC_L_VER_START_POS_UNMASK, ((value & 0xFFFF) << 0))
#define _lcdc_l_ver_start_pos_get(lcdc_l) ((_reg_read(lcdc_l->WINDOW_V_POS) & LCDC_L_VER_START_POS_MASK) >> 0)
// lcdc window vertical position set
#define LCDC_L_WINDOW_VER_POS_MASK (0xFFFFFFFF)
#define _lcdc_l_window_ver_pos_set(lcdc_l, value_p, value_t) _reg_write(lcdc_l->WINDOW_V_POS, ((value_p - 1) << 16) | value_t << 0)
#define _lcdc_l_window_ver_pos_get(lcdc_l) _reg_read(lcdc_l->WINDOW_V_POS)

// lcdc color key register
// lcdc color key
#define LCDC_L_COLOR_KEY_MASK (0xFFFFFF)
#define _lcdc_l_color_key_set(lcdc_l, value) _reg_write(lcdc_l->COLOR_KEY, (value & LCDC_L_COLOR_KEY_MASK))
#define _lcdc_l_color_key_get(lcdc_l) _reg_read(lcdc_l->COLOR_KEY)

// lcdc pixel format register
// lcdc pixel format
#define LCDC_L_PIXEL_FORMAT_MASK (0xFF)
#define _lcdc_l_pixel_format_set(lcdc_l, value) _reg_write(lcdc_l->PIXEL_FORMAT, (value & LCDC_L_PIXEL_FORMAT_MASK))
#define _lcdc_l_pixel_format_get(lcdc_l) _reg_read(lcdc_l->PIXEL_FORMAT)

// lcdc constant alpha register
// lcdc constant alpha
#define LCDC_L_CONST_ALPHA_MASK (0xFF)
#define _lcdc_l_const_alpha_set(lcdc_l, value) _reg_write(lcdc_l->CONSTANT_ALPHA, (value & LCDC_L_CONST_ALPHA_MASK))
#define _lcdc_l_const_alpha_get(lcdc_l) _reg_read(lcdc_l->CONSTANT_ALPHA)

// lcdc default color register
// lcdc default color
#define LCDC_L_DEFAULT_COLOR_MASK (0xFFFFFFFF)
#define _lcdc_l_default_color_set(lcdc_l, value) _reg_write(lcdc_l->DEFAULT_COLOR, (value & LCDC_L_DEFAULT_COLOR_MASK))
#define _lcdc_l_default_color_get(lcdc_l) _reg_read(lcdc_l->DEFAULT_COLOR)

// lcdc blending configuration register
// lcdc layer blending order position
#define LCDC_L_BLEND_ORDER_MASK (0xF << 16)
#define LCDC_L_BLEND_ORDER_UNMASK (~(0xF << 16))
#define _lcdc_l_blend_order_set(lcdc_l, value) _reg_modify(lcdc_l->BLENDING_FACTORS, LCDC_L_BLEND_ORDER_UNMASK, ((value & 0xF) << 16))
#define _lcdc_l_blend_order_get(lcdc_l) ((_reg_read(lcdc_l->BLENDING_FACTORS) & LCDC_L_BLEND_ORDER_MASK) >> 16)
// lcdc selection of Factor F1
#define LCDC_L_FACTOR_F1_MASK (0x7 << 8)
#define LCDC_L_FACTOR_F1_UNMASK (~(0x7 << 8))
#define _lcdc_l_factor_f1_set(lcdc_l, value) _reg_modify(lcdc_l->BLENDING_FACTORS, LCDC_L_FACTOR_F1_UNMASK, ((value & 0x7) << 8))
#define _lcdc_l_factor_f1_get(lcdc_l) ((_reg_read(lcdc_l->BLENDING_FACTORS) & LCDC_L_FACTOR_F1_MASK) >> 8)
// lcdc selection of Factor F2
#define LCDC_L_FACTOR_F2_MASK (0x7 << 0)
#define LCDC_L_FACTOR_F2_UNMASK (~(0x7 << 0))
#define _lcdc_l_factor_f2_set(lcdc_l, value) _reg_modify(lcdc_l->BLENDING_FACTORS, LCDC_L_FACTOR_F2_UNMASK, ((value & 0x7) << 0))
#define _lcdc_l_factor_f2_get(lcdc_l) ((_reg_read(lcdc_l->BLENDING_FACTORS) & LCDC_L_FACTOR_F2_MASK) >> 0)
// lcdc blending configuration set
#define LCDC_L_BLEND_CONFIG_MASK (0xF0707)
#define _lcdc_l_blend_config_set(lcdc_l, value) _reg_write(lcdc_l->BLENDING_FACTORS, value &LCDC_L_BLEND_CONFIG_MASK)
#define _lcdc_l_blend_config_get(lcdc_l) _reg_read(lcdc_l->BLENDING_FACTORS)

// lcdc fb bus control register
// lcdc number of words per burst set
#define LCDC_L_FB_BUS_CTRL_MASK (0xFF)
#define _lcdc_l_fb_bus_ctrl_set(lcdc_l, value) _reg_write(lcdc_l->FB_BUS_CONTROL, (value & LCDC_L_FB_BUS_CTRL_MASK))
#define _lcdc_l_fb_bus_ctrl_get(lcdc_l) _reg_read(lcdc_l->FB_BUS_CONTROL)

// lcdc color fb address register
// lcdc color fb address set
#define LCDC_L_COLOR_FB_ADDR_MASK (0xFFFFFFFF)
#define _lcdc_l_color_fb_addr_set(lcdc_l, value) _reg_write(lcdc_l->COLOR_FB_ADDRESS, (value & LCDC_L_COLOR_FB_ADDR_MASK))
#define _lcdc_l_color_fb_addr_get(lcdc_l) _reg_read(lcdc_l->COLOR_FB_ADDRESS)

// lcdc color fb pitch and length register
// lcdc pitch of color fb in bytes
#define LCDC_L_COLOR_FB_PITCH_MASK (0xFFFF << 16)
#define LCDC_L_COLOR_FB_PITCH_UNMASK (~(0xFFFF << 16))
#define _lcdc_l_color_fb_pitch_set(lcdc_l, value) _reg_modify(lcdc_l->COLOR_FB_LENGTH, LCDC_L_COLOR_FB_PITCH_UNMASK, ((value & 0xFFFF) << 16))
#define _lcdc_l_color_fb_pitch_get(lcdc_l) ((_reg_read(lcdc_l->COLOR_FB_LENGTH) & LCDC_L_COLOR_FB_PITCH_MASK) >> 8)
// lcdc line length of color fb in bytes
#define LCDC_L_COLOR_FB_LENGTH_MASK (0xFFFF << 0)
#define LCDC_L_COLOR_FB_LENGTH_UNMASK (~(0xFFFF << 0))
#define _lcdc_l_color_fb_length_set(lcdc_l, value) _reg_modify(lcdc_l->COLOR_FB_LENGTH, LCDC_L_COLOR_FB_LENGTH_UNMASK, ((value & 0xFFFF) << 0))
#define _lcdc_l_color_fb_length_get(lcdc_l) ((_reg_read(lcdc_l->COLOR_FB_LENGTH) & LCDC_L_COLOR_FB_LENGTH_MASK) >> 0)
// lcdc color fb address set
#define LCDC_L_COLOR_FB_PITCH_LENGTH_MASK (0xFFFFFFFF)
#define _lcdc_l_color_fb_pitch_length_set(lcdc_l, fb_p) _reg_write(lcdc_l->COLOR_FB_LENGTH, (fb_p << 16) | (fb_p + 7) << 0)
#define _lcdc_l_color_fb_pitch_length_get(lcdc_l) _reg_read(lcdc_l->COLOR_FB_LENGTH)

// lcdc color fb Lines register
// lcdc color fb Lines set, width
#define LCDC_L_COLOR_FB_LINES_MASK (0xFFFF)
#define _lcdc_l_color_fb_lines_set(lcdc_l, value) _reg_write(lcdc_l->COLOR_FB_LINES, (value & LCDC_L_COLOR_FB_LINES_MASK))
#define _lcdc_l_color_fb_lines_get(lcdc_l) _reg_read(lcdc_l->COLOR_FB_LINES)

// lcdc CLUT write access register
// lcdc address of CLUT entry
#define LCDC_L_CLUT_ADDR_ENTRY_MASK (0xFF << 24)
#define LCDC_L_CLUT_ADDR_ENTRY_UNMASK (~(0xFF << 24))
#define _lcdc_l_clut_addr_entry_set(lcdc_l, value) _reg_modify(lcdc_l->CLUT_WRITE_ACCESS, LCDC_L_CLUT_ADDR_ENTRY_UNMASK, ((value & 0xFF) << 24))
// lcdc RGB888 value to be written
#define LCDC_L_RGB888_VALUE_MASK (0xFFFFFF << 0)
#define LCDC_L_RGB888_VALUE_UNMASK (~(0xFFFFFF << 0))
#define _lcdc_l_rgb888_value_set(lcdc_l, value) _reg_modify(lcdc_l->CLUT_WRITE_ACCESS, LCDC_L_RGB888_VALUE_UNMASK, ((value & 0xFFFFFF) << 0))
// lcdc color fb address set
#define LCDC_L_CLUT_WRITE_ACCESS_MASK (0xFFFFFFFF)
#define _lcdc_l_clut_write_access_set(lcdc_l, value) _reg_write(lcdc_l->CLUT_WRITE_ACCESS, (value & LCDC_L_CLUT_WRITE_ACCESS_MASK))
/**
 *  @brief  LCDC 模块输入数据的格式枚举定义
 *
 */
typedef enum
{
    LCDC_ARGB8888 = 0,
    LCDC_ABGR8888 = 1,
    LCDC_RGBA8888 = 2,
    LCDC_BGRA8888 = 3,
    LCDC_RGB565 = 4,
    LCDC_BGR565 = 5,
    LCDC_RGB888 = 6,
    LCDC_CUSTOM = 7
} lcdc_pixel_format_t;
/**
 *  @brief  LCDC FIFO 预取长度
 *  @note 预取长度默认为最大
 */
typedef enum
{
    FB_BUS_16 = 0,
    FB_BUS_1 = 1,
    FB_BUS_2 = 2,
    FB_BUS_3 = 3,
    FB_BUS_4 = 4,
    FB_BUS_5 = 5,
    FB_BUS_6 = 6,
    FB_BUS_7 = 7,
    FB_BUS_8 = 8,
    FB_BUS_9 = 9,
    FB_BUS_10 = 10,
    FB_BUS_11 = 11,
    FB_BUS_12 = 12,
    FB_BUS_13 = 13,
    FB_BUS_14 = 14,
    FB_BUS_15 = 15,
} lcdc_fb_bus_t;

/**
 *  @brief  LCDC 使能或禁能类型
 *
 */
typedef enum
{
    LCDC_DIS = 0,
    LCDC_EN = 1,
} lcdc_enble_t;
/**
 *  @brief  LCDC 模块IRQ 索引枚举定义
 *
 */
typedef enum
{
    CRC_IRQ = 0x80,
    FlFO_UNDER_KILL_IRQ = 0x40,
    REG_RELOAD_IRQ = 0x8,
    BUS_ERR_IRQ = 0x4,
    FlFO_UNDER_WARN_IRQ = 0x2,
    LINE_IRQ = 0x1
} lcdc_irq_t;
// 函数声明
void drv_lcdc_gpio_config(void);
void drv_lcdc_sync_size_set(reg_lcdc_g_t *p_lcdc_g, uint32_t hsync, uint32_t vsync);
void drv_lcdc_back_porch_set(reg_lcdc_g_t *p_lcdc_g, uint32_t hbp, uint32_t vbp);
void drv_lcdc_active_width_set(reg_lcdc_g_t *p_lcdc_g, uint32_t width, uint32_t height);
void drv_lcdc_total_width_set(reg_lcdc_g_t *p_lcdc_g, uint32_t hfp, uint32_t vfp);
void drv_lcdc_crc_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t crc_en);
void drv_lcdc_dither_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_en);
void drv_lcdc_dither_red_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_red);
void drv_lcdc_dither_green_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_green);
void drv_lcdc_dither_blue_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_blue);
void drv_lcdc_gamma_correction_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t gamma);
void drv_lcdc_global_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t global_en);
void drv_lcdc_global_control_set(reg_lcdc_g_t *p_lcdc_g, uint32_t value);
void drv_lcdc_immediate_reload_set(reg_lcdc_g_t *p_lcdc_g, uint32_t reload);
void drv_lcdc_shadow_reload_ctrl_set(reg_lcdc_g_t *p_lcdc_g, uint32_t value);
void drv_lcdc_background_color_set(reg_lcdc_g_t *p_lcdc_g, uint32_t background);
void drv_lcdc_irq_en_set(reg_lcdc_g_t *p_lcdc_g, lcdc_irq_t irq_en);
lcdc_irq_t drv_lcdc_irq_status_get(reg_lcdc_g_t *p_lcdc_g);
void drv_lcdc_irq_status_clear(reg_lcdc_g_t *p_lcdc_g,uint32_t value);
void drv_lcdc_irq_clr_set(reg_lcdc_g_t *p_lcdc_g, lcdc_irq_t irq_clr);
void drv_lcdc_line_irq_position_ctrl_set(reg_lcdc_g_t *p_lcdc_g, uint32_t line_pos);
// 以下函数需要配合 drv_lcdc_shadow_reload_ctrl_set 函数才立即生效
void drv_lcdc_color_blend_en_set(reg_lcdc_l_t *p_lcdc_l, uint32_t blend_en);
void drv_lcdc_hor_mirror_en_set(reg_lcdc_l_t *p_lcdc_l, uint32_t mirror_en);
void drv_lcdc_layer_on_set(reg_lcdc_l_t *p_lcdc_l, uint32_t layer_on);
void drv_lcdc_layer_ctrl_set(reg_lcdc_l_t *p_lcdc_l, uint32_t value);
void drv_lcdc_hor_stop_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t hor_stop);
void drv_lcdc_hor_start_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t hor_start);
void drv_lcdc_window_hor_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t hor_stop, uint32_t hor_start);
void drv_lcdc_ver_stop_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t ver_stop);
void drv_lcdc_ver_start_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t ver_start);
void drv_lcdc_window_ver_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t ver_stop, uint32_t ver_start);
void drv_lcdc_pixel_format_set(reg_lcdc_l_t *p_lcdc_l, lcdc_pixel_format_t pixel_format);
void drv_lcdc_const_alpha_set(reg_lcdc_l_t *p_lcdc_l, uint32_t const_alpha);
void drv_lcdc_default_color_set(reg_lcdc_l_t *p_lcdc_l, uint32_t def_color);
void drv_lcdc_l_factor_f1_select(reg_lcdc_l_t *p_lcdc_l, uint32_t f1_en);
void drv_lcdc_l_factor_f2_select(reg_lcdc_l_t *p_lcdc_l, uint32_t f2_en);
void drv_lcdc_l_factor_layer_select(reg_lcdc_l_t *p_lcdc_l, uint8_t layer_n);
void drv_lcdc_fb_bus_ctrl_set(reg_lcdc_l_t *p_lcdc_l, lcdc_fb_bus_t fb_bus);
void drv_lcdc_color_fb_addr_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_addr);
void drv_lcdc_color_fb_pitch_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_pitch);
void drv_lcdc_color_fb_length_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_length);
void drv_lcdc_color_fb_pitch_length_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_pitch);
void drv_lcdc_color_fb_lines_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_lines);

#ifdef __cplusplus
}
#endif

#endif
