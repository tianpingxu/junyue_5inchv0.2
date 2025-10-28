/**
 * @file lcd_interface.h
 * @author Product Application Department
 * @brief  LCD 硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup DISPLAY DISPLAY模块
 * @ingroup Peripherals
 * @{
 */

#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "eport_hal.h"
#include "spi_hal.h"

// 全局变量定义
#define LCDLOG_DEBUG(...) printf(__VA_ARGS__)
#define LCD_DISP_HOR_RES 480
#define LCD_DISP_VER_RES 854

/**
 * @brief LCD 状态给返回枚举定义
 *
 */
typedef enum
{
    LCD_OK = 0,
    LCD_ERR = 1,
    LCD_WARN = 2
} lcd_status_t;

/**
 * @brief LCD 接口类型枚举定义
 *
 */
typedef enum
{
    LCD_SPI = 0,
    LCD_QSPI = 1,
    LCD_I8080_16 = 2,
    LCD_I8080_8 = 3,
    LCD_RGB = 4,
} lcd_interface_t;

/**
 * @brief LCD 驱动芯片枚举定义
 *
 */
typedef enum
{
    ST7789_ST7796 = 0,
    NV3041 = 1,
    ST77903,
    RGB_480272,
    RGB_480854,
    RGB_1024600,
} lcd_driveric_t;

/**
 * @brief LCD xy轴结构体定义
 *
 */
typedef struct
{
    int x;
    int y;
} lcd_dispsize_t;

/**
 * @brief LCD 配置结构体定义
 *
 */
typedef struct
{
    lcd_interface_t lcd_itf_type;
    lcd_driveric_t lcd_ic;
    lcd_dispsize_t lcd_size;
    lcd_status_t (*init)(lcd_driveric_t ic);
    void (*writedots)(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t *DataBase);
    void (*readdots)(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint16_t *DataBase);

} lcd_handle_t;

// 函数声明
lcd_status_t lcd_init(lcd_handle_t *itf);
lcd_status_t lcd_write_dots(lcd_handle_t *itf, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t *DataBase);
lcd_status_t lcd_read_dots(lcd_handle_t *itf, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint16_t *DataBase);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 DISPLAY 模块分组
/** @} */  // 结束外设模块分组

#endif
