/**
 *  @file rtc_hal.c
 *  @author Product application department
 *  @brief  RTC 模块硬件抽象层，供应用层调用，仅供参考
 *  @version V1.0
 *  @date 2025-02-13
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "rtc_hal.h"

// 函数定义

/**
 *  @brief  RTC 模块初始化函数
 *
 *  @param prtcinit RTC HAL 初始化结构体
 */
void hal_rtc_init(rtc_init_t *prtcinit)
{
    drv_rtc_clock_exchange(prtcinit->rtc_clk_sel);
    drv_rtc_clock_set(prtcinit->sys_clk);
}

/**
 *  @brief  RTC 模块中断服务函数
 *
 */
void hal_rtc_irq_handler(void)
{
    drv_rtc_irq_handler();
}

/**
 *  @brief  RTC 模块获取RTC时间函数
 *
 *  @param time RTC 时间结构体
 */
void hal_rtc_get_time(rtc_time_t *time)
{
    drv_rtc_get_time_counter(time);
}

/**
 *  @brief  RTC 模块设置RTC时间函数
 *
 *  @param time RTC 时间结构体
 */
void hal_rtc_set_time(rtc_time_t *time)
{
    drv_rtc_set_time_counter(time);
}
