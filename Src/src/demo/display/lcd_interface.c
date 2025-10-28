/**
 * @file lcd_interface.c
 * @author Product Application Department
 * @brief  LCD 硬件抽象层，供应用层调用，仅供参考
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

// 头文件定义
#include "lcd_interface.h"
#include "rgb_lcd.h"

// 全局变量定义
lcd_handle_t lcd_dev;

// 函数定义
/**
 * @brief 屏幕初始化接口函数
 *
 * @param itf 屏幕配置参数
 * @return lcd_status_t 配置返回值
 */
lcd_status_t lcd_init(lcd_handle_t *itf)
{
    switch (itf->lcd_itf_type)
    {
    case LCD_SPI:

        break;
    case LCD_QSPI:

        break;
    case LCD_I8080_16:

        break;
    case LCD_RGB:
        itf->init = RGBLCD_Init;
        itf->writedots = LCD_RGB_Color_Fill;
        break;
    default:
        LCDLOG_DEBUG("Nothing init.\n");
        break;
    }
    return itf->init(itf->lcd_ic);
}

/** 
 * @brief 屏幕刷新接口函数
 * @param itf 屏幕配置参数
 * @param x0 X轴起始地址
 * @param y0 Y轴起始地址
 * @param x1 X轴结束地址
 * @param y1 Y轴结束地址
 * @param DataBase 刷图数据
 * @return
 */
lcd_status_t lcd_write_dots(lcd_handle_t *itf, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t *DataBase)
{
    lcd_status_t res = LCD_OK;
    if (itf->writedots == NULL)
    {
        res = LCD_ERR;
        return res;
    }
    itf->writedots(x0, y0, x1, y1, DataBase);
    return res;
}

/**
 * @brief 屏幕读点接口函数
 * @param itf 屏幕配置参数
 * @param x0 X轴起始地址
 * @param y0 Y轴起始地址
 * @param x1 X轴结束地址
 * @param y1 Y轴结束地址
 * @param DataBase 刷图数据
 * @return
 */
lcd_status_t lcd_read_dots(lcd_handle_t *itf, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint16_t *DataBase)
{
    lcd_status_t res = LCD_OK;
    if (itf->readdots == NULL)
    {
        res = LCD_ERR;
        return res;
    }
    itf->readdots(x0, y0, x1, y1, DataBase);
    return res;
}

/** @} */  // 结束 DISPLAY 模块分组
/** @} */  // 结束外设模块分组
