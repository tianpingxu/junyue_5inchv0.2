/**
 * @file lcdc_reg.h
 * @author Product application department
 * @brief  LCDC 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __LCDC_REG_H
#define __LCDC_REG_H

// 头文件包含
#include <stdint.h>
#include "type.h"

#define LCDC_BASE_ADDR         (0x400b0000)                  
#define LCDC_GLOBAL_BASE     (LCDC_BASE_ADDR)                    
#define LCDC_LAYER1_BASE      (LCDC_BASE_ADDR + 0x100)        
#define LCDC_LAYER2_BASE    (LCDC_BASE_ADDR + 0x200)        


#define LCDC_G     ((reg_lcdc_g_t *)LCDC_BASE_ADDR)
#define LCDC_L1 ((reg_lcdc_l_t *)LCDC_LAYER1_BASE)
#define LCDC_L2 ((reg_lcdc_l_t *)LCDC_LAYER2_BASE)

// 全局变量定义
/**
 *  @brief  LCDC 模块全局寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t HW_VERSION;                     // 0x00
    __IO uint32_t LAYER_COUNT;                    // 0x04
    __IO uint32_t SYNC_SIZE;                      // 0x08
    __IO uint32_t BACK_PORCH;                     // 0x0C
    __IO uint32_t ACTIVE_WIDTH;                   // 0x10
    __IO uint32_t TOTAL_WIDTH;                    // 0x14
    __IO uint32_t GLOBAL_CONTROL;                 // 0x18
    __IO uint32_t CONFIGURATION_1;                // 0x1C
    __IO uint32_t CONFIGURATION_2;                // 0x20
    __IO uint32_t SHADOW_RELOAD_CONTROL;          // 0x24
    __IO uint32_t GAMMA_CORRECTION;               // 0x28
    __IO uint32_t BACKGROUND_COLOR;               // 0x2C
    __IO uint32_t RESERVED_1;                     // 0x30
    __IO uint32_t IRQ_ENABLE;                     // 0x34
    __IO uint32_t IRQ_STATUS;                     // 0x38
    __IO uint32_t IRQ_CLEAR;                      // 0x3C
    __IO uint32_t LINE_IRQ_POS_CONTROL;           // 0x40
    __IO uint32_t POSITION_STATUS;                // 0x44
    __IO uint32_t SYNC_BLANK_STATUS;              // 0x48
    __IO uint32_t BACKGROUND_LAYER_BASE;          // 0x4C
    __IO uint32_t BACKGROUND_LAYER_INCS;          // 0x50
    __IO uint32_t BACKGROUND_LAYER_RAM_ADDR;      // 0x54
    __IO uint32_t BACKGROUND_LAYER_DATA;          // 0x58
    __IO uint32_t SLAVE_TIMING_MODE_STATUS;       // 0x5C
    __IO uint32_t EXTERNAL_DISPLAY_CONTROL;       // 0x60
    __IO uint32_t SECONDARY_IRQ_ENABLE;           // 0x64
    __IO uint32_t SECONDARY_IRQ_STATUS;           // 0x68
    __IO uint32_t SECONDARY_IRQ_CLEAR;            // 0x6C
    __IO uint32_t SECONDARY_LINE_IRQ_POS_CONTROL; // 0x70
    __IO uint32_t RESERVED_2;                     // 0x74
    __IO uint32_t CRC_REFERENCE;                  // 0x78
    __IO uint32_t CRC_RESULT;                     // 0x7C
    __IO uint32_t ROT_BUF0_START;                 // 0x80
    __IO uint32_t ROT_BUF1_START;                 // 0x84
    __IO uint32_t ROT_BUF_PITCH;                  // 0x88
    __IO uint32_t BLEND_COLOR;                    // 0x8C
    __IO uint32_t UNDERRUN_THRESHOLD;             // 0x90
} reg_lcdc_g_t;

/**
 *  @brief  LCDC 模块 Layer 层寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t CONFIGURATION1;          // 0x00
    __IO uint32_t CONFIGURATION2;          // 0x04
    __IO uint32_t CONTROL_RELOAD;          // 0x08
    __IO uint32_t CONTROL;                 // 0x0C
    __IO uint32_t WINDOW_H_POS;            // 0x10
    __IO uint32_t WINDOW_V_POS;            // 0x14
    __IO uint32_t COLOR_KEY;               // 0x18
    __IO uint32_t PIXEL_FORMAT;            // 0x1C
    __IO uint32_t CONSTANT_ALPHA;          // 0x20
    __IO uint32_t DEFAULT_COLOR;           // 0x24
    __IO uint32_t BLENDING_FACTORS;        // 0x28
    __IO uint32_t FB_BUS_CONTROL;          // 0x2C
    __IO uint32_t AUX_FB_CONTROL;          // 0x30
    __IO uint32_t COLOR_FB_ADDRESS;        // 0x34
    __IO uint32_t COLOR_FB_LENGTH;         // 0x38
    __IO uint32_t COLOR_FB_LINES;          // 0x3C
    __IO uint32_t AUX0_FB_ADDRESS;         // 0x40
    __IO uint32_t AUX1_FB_ADDRESS;         // 0x44
    __IO uint32_t AUX_FB_LENGTH;           // 0x48
    __IO uint32_t AUX_FB_LINES;            // 0x4C
    __IO uint32_t CLUT_WRITE_ACCESS;       // 0x50
    __IO uint32_t SCALER_INPUT_SIZE;       // 0x54
    __IO uint32_t SCALER_OUTPUT_SIZE;      // 0x58
    __IO uint32_t SCALER_V_SCALING_FACTOR; // 0x5C
    __IO uint32_t SCALER_V_SCALING_PHASE;  // 0x60
    __IO uint32_t SCALER_H_SCALING_FACTOR; // 0x64
    __IO uint32_t SCALER_H_SCALING_PHASE;  // 0x68
    __IO uint32_t YCBCR_SCALE1;            // 0x6C
    __IO uint32_t YCBCR_SCALE2;            // 0x70
    __IO uint32_t FLEXI_FORMAT1;           // 0x74
    __IO uint32_t FLEXI_FORMAT2;           // 0x78
} reg_lcdc_l_t;

/**
 *  @brief LCDC 模块寄存器操作方式枚举定义
 *
 */
typedef enum
{
    READ_REG = 0,
    WRITE_REG = 1
} reg_ops_t;

#endif
