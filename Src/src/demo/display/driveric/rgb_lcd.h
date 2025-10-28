/**
 * @file rgb_lcd.h
 * @author Product Application Department
 * @brief  RGB LCD 硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

 
 /**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup RGB RGB模块
 * @ingroup Peripherals
 * @{
 */

 
#ifndef _RGB_LCD_H
#define _RGB_LCD_H

// 头文件定义

#include "type.h"
#include "lcdc_hal.h"
#include "lcd_interface.h"
#include "image_decoder_test.h"
#include "dma2d_test.h"
#include "libaxiflow.h"
#include "lv_ccore_conf.h"

// 函数声明
lcd_status_t RGBLCD_Init(lcd_driveric_t ic);
void LCD_RGB_Color_Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint8_t *color);
void lvgl_decode(image_type_t img_type,image_output_type_t output_type,uint32_t img_addr,uint32_t image_len,uint32_t out_addr);
#endif


/** @} */  // 结束 RGB 模块分组
/** @} */  // 结束外设模块分组