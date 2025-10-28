/**
 * @file lcdc_hal.h
 * @author Product application department
 * @brief  LCDC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __LCDC_HAL_H
#define __LCDC_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "lcdc_drv.h"

// 全局变量定义

/**
 * @brief RGB 模块输入时序参数结构体定义
 * 
 */
typedef struct
{
    uint16_t vsync;
    uint16_t vbp;
    uint16_t vfp;
    uint16_t height;
    uint16_t hsync;
    uint16_t hbp;
    uint16_t hfp;
    uint16_t width;
    uint32_t  clcdclk;
    uint32_t background_color;
    uint32_t l1_default_color;
    uint32_t l2_default_color;
    lcdc_fb_bus_t fb_bus1;
    lcdc_fb_bus_t fb_bus2;
} rgb_input_timing_para_t;

/**
 * @brief  RGB 模块layer切换控制方式
 * 
 */
typedef enum
{
    LAYER_OFF = 0,
    LAYER1_ON = 1,
    LAYER2_ON = 2,
    LAYER_ALL_ON = 3
} rgb_layer_switch_t;

// 函数声明
status_t hal_lcdc_init(rgb_input_timing_para_t *p_rgb_para);
status_t hal_lcdc_layer_switch(rgb_layer_switch_t ctrl);
status_t hal_lcdc_layer_on(uint8_t layern, uint8_t en);
status_t hal_lcdc_layer_burst_config(lcdc_fb_bus_t fb_bus1, lcdc_fb_bus_t fb_bus2);
status_t hal_layer_format_config(rgb_input_timing_para_t *p_rgb_para,uint8_t layern, lcdc_pixel_format_t l_format);
status_t hal_layer_addr_config(rgb_input_timing_para_t *p_rgb_para, uint8_t layern, uint32_t l_addr);
status_t hal_lcdc_format_and_addr_config(rgb_input_timing_para_t *p_rgb_para, lcdc_pixel_format_t l1_format, lcdc_pixel_format_t l2_format, uint32_t l1_addr, uint32_t l2_addr);
status_t hal_lcdc_mirror_config(rgb_input_timing_para_t *p_rgb_para, lcdc_pixel_format_t l1_format, lcdc_pixel_format_t l2_format, uint8_t l1_mirror, uint8_t l2_mirror, uint32_t l1_addr, uint32_t l2_addr);
status_t hal_lcdc_layer_blend_config(uint32_t l1_alpha, uint32_t l2_alpha, uint8_t l1_f1, uint8_t l1_f2, uint8_t l2_f1, uint8_t l2_f2);
status_t hal_lcdc_switch_address(uint8_t layern, uint32_t addr);
#ifdef __cplusplus
}
#endif

#endif
