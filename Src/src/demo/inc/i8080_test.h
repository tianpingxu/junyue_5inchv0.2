/**
 * @file i8080_demo.h
 * @author Product Application Department
 * @brief  I8080 模块测试文件，仅供参考
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup I8080 I8080模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __I8080_DEMO_H
#define __I8080_DEMO_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i8080_hal.h"
#include "color_def.h"
#include "delay.h"

// 全局变量定义
#define LCD_BASE ((uint32_t)(0xA4000000 | 0x01FFFFFE))
#define MCU_LCD ((lcd_t *)LCD_BASE)

#define L2R_U2D 0
#define L2R_D2U 1
#define R2L_U2D 2
#define R2L_D2U 3

#define U2D_L2R 4
#define U2D_R2L 5
#define D2U_L2R 6
#define D2U_R2L 7

#define DFT_SCAN_DIR L2R_U2D

/**
 * @brief LCD地址结构体定义
 *
 */
typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} lcd_t;
/**
 * @brief LCD重要参数集结构体定义
 *
 */
typedef struct
{
    uint16_t width;      // LCD 宽度
    uint16_t height;  // LCD 高度
    uint16_t id;      // LCD ID
    uint8_t dir;      // 横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd; // 开始写gram指令
    uint16_t setxcmd; // 设置x坐标指令
    uint16_t setycmd; // 设置y坐标指令
} lcd_dev_t;

// 函数声明
void i8080_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 I8080 模块分组
/** @} */  // 结束外设模块分组

#endif