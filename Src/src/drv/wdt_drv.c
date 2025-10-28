/**
 * @file wdt_drv.c
 * @author Product application department
 * @brief  WDT 模块驱动层
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "wdt_drv.h"

// 函数定义
/**
 *  @brief  WDT 模块设置 MR 寄存器的数值函数
 *
 *  @param value WDT MR寄存器设置的数值
 */
void drv_wdt_init(uint16_t value)
{
    _wdt_set_mr(value);
    _wdt_en;
}

/**
 *  @brief  WDT 模块喂狗函数
 *
 */
void drv_wdt_feed_watchdog(void)
{
    _wdt_set_wsr(0x5555);
    _wdt_set_wsr(0xAAAA);
}

/**
 *  @brief  WDT 模块启动函数
 *
 */
void drv_wdt_open(void)
{
    _cpm_set_ipscgtcr_clk_on(1);
    _wdt_en;
}

/**
 *  @brief  WDT 模块禁用函数
 *
 */
void drv_wdt_close(void)
{
    _cpm_set_ipscgtcr_clk_off(1);
    _wdt_dis;
}

/**
 *  @brief  WDT 模块获取当前计数值函数
 *
 *  @return uint16_t  返回当前计数值
 */
uint16_t drv_wdt_get_counter(void)
{
    return _wdt_get_count;
}
