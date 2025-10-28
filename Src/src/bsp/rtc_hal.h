/**
 * @file rtc_hal.h
 * @author Product application department
 * @brief  RTC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __RTC_HAL_H
#define __RTC_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "rtc_drv.h"
#include "cpm_drv.h"

/**
 * @brief RTC 模块时间中断类型枚举定义
 * 
 */
typedef enum
{
    RTC_INT_NULL = 0x00,
    RTC_INT_32KHZ = 0x01,
    RTC_INT_1KHZ = 0x02,
    RTC_INT_ALA = 0x04,
    RTC_INT_SEC = 0x08,
    RTC_INT_MIN = 0x10,
    RTC_INT_HOUR = 0x20,
    RTC_INT_DAY = 0x40
} rtc_it_t;

/**
 * @brief RTC 模块alarm类型枚举定义
 * 
 */
typedef enum
{
    ALARM_NULL = 0x00,
    ALARM_DAY = 0x01,
    ALARM_HOUR = 0x02,
    ALARM_MIN = 0x04,
    ALARM_SEC = 0x08
} rtc_alarmit_t;

/**
 * @brief RTC 模块alarm触发类型枚举定义
 * 
 */
typedef enum
{
    ALARM_LOW_LEVEL = 0,
    ALARM_RISE,
    ALARM_FALL,
    ALARM_RISE_FALL
} rtc_alarm_t;

/**
 * @brief RTC 模块初始化结构体定义
 * 
 */
typedef struct
{
    rtc_time_t set_time;
    rtc_time_t set_alarm_time;
    rtc_it_t rtc_it_type;
    rtc_alarmit_t alarm_it_type;
    rtc_alarm_t alarm_type;
    uint32_t sys_clk;
    rtc_src_t rtc_clk_sel;
} rtc_init_t;

// 函数声明
void hal_rtc_irq_handler(void);
void hal_rtc_init(rtc_init_t *prtcinit);
void hal_rtc_get_time(rtc_time_t *time);
void hal_rtc_set_time(rtc_time_t *time);

#ifdef __cplusplus
}
#endif

#endif
