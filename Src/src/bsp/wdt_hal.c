/**
 * @file wdt_hal.c
 * @author Product application department
 * @brief  WDT 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "wdt_hal.h"

// 函数定义
/**
 *  @brief  WDT 模块初始化函数
 *
 *  @param counter WDT MR寄存器设置的数值
 */
void hal_wdt_init(uint16_t counter)
{
    drv_wdt_init(counter);
}

/**
 *  @brief WDT HAL 模块使能与禁能功能函数
 *
 *  @param status 使能与禁能输入
 *  @note 看门狗模块在上电之后,只能使能和禁能一次
 */
void hal_wdt_cmd(uint8_t status)
{
    if (status == 1)
    {
        drv_wdt_open();
    }
    else
    {
        drv_wdt_close();
    }
}

/**
 *  @brief  WDT 模块喂狗函数
 *
 */
void hal_wdt_feed_watchdog(void)
{
    drv_wdt_feed_watchdog();
}

/**
 *  @brief  WDT 模块获取当前计数值函数
 *
 *  @return uint32_t  返回当前计数值
 */
uint32_t hal_wdt_get_counter(void)
{
    return drv_wdt_get_counter();
}
