/**
 * @file rtc_test.h
 * @author Product application department
 * @brief  RTC 模块测试用例头文件，仅供参考
 * @version v1.0
 * @rtc_data_t 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */


/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup RTC RTC模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __RTC_TEST_H
#define __RTC_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "rtc_hal.h"

// 全局变量定义
#define YEAR_BASE (2000)

/**
 *  @brief  RTC 时间结构体
 *
 */
typedef struct
{
    int8_t hour;
    int8_t min;
    int8_t sec;
} rtc_rtc_time_t;

#define START_YEARS			1973
#define END_YEARS				2053   //END_YEARS - START_YEARS <= 80

typedef struct _t_ctimes{
    unsigned short years;
    unsigned char  months;
    unsigned char  days;
    unsigned char  weeks;
    unsigned char  hours;
    unsigned char  minutes;
    unsigned char  seconds;
}t_ctimes;
// 函数声明

void dev_set_rtc_time(rtc_time_t *tim);
void rtc_demo(void);

void set_time(t_ctimes init_stamp_time, rtc_time_t *rtc_times);

void get_time(t_ctimes *current_stamp_time, rtc_time_t rtc_times);

#ifdef __cplusplus
}
#endif


/** @} */  // 结束 RTC 模块分组
/** @} */  // 结束外设模块分组

#endif
