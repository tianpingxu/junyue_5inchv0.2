/**
 * @file rtc_test.c
 * @author Product application department
 * @brief  RTC 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-13
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

// 头文件包含
#include "rtc_test.h"

//全局变量定义
unsigned char week_table[7] = {6, 0, 1, 2, 3, 4, 5}; // START_YEARS=1973
int8_t week[7] = {1, 2, 3, 4, 5, 6, 7};

// 函数定义

/**
 * @brief 时间转换函数，转换成小时分钟秒
 * 
 * @param init_stamp_time 传入的时间
 * @param rtc_times 转换后的时间
 */
void set_time(t_ctimes init_stamp_time, rtc_time_t *rtc_times)
{
    unsigned char nonleap_years;
    unsigned char leap_years;
    unsigned char full_years;
    unsigned int months_table[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 367};

    if ((init_stamp_time.years <= START_YEARS) || (init_stamp_time.years >= END_YEARS))
    {
        init_stamp_time.years = START_YEARS;
    }

    full_years = (init_stamp_time.years - START_YEARS);

    leap_years = full_years / 4;

    nonleap_years = full_years - leap_years;

    rtc_times->days = (leap_years * 366 + nonleap_years * 365);

    rtc_times->days += months_table[init_stamp_time.months - 1];

    rtc_times->days += init_stamp_time.days;

    if ((0 == init_stamp_time.years % 4) && (2 < init_stamp_time.months))
    {
        rtc_times->days += 1;
    }

    rtc_times->hours = init_stamp_time.hours;
    rtc_times->minutes = init_stamp_time.minutes;
    rtc_times->seconds = init_stamp_time.seconds;
}

/**
 * @brief 获取转换后的时间
 * 
 * @param current_stamp_time 转换后的时间
 * @param rtc_times 转换前的时间
 */
void get_time(t_ctimes *current_stamp_time, rtc_time_t rtc_times)
{
    unsigned short days;
    unsigned char leap_year_num;
    //	unsigned char year_num;
    unsigned char i;
    unsigned int months_table[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 367};

    //	RTC_GetTime(&rtc_times);

    current_stamp_time->seconds = rtc_times.seconds;
    current_stamp_time->minutes = rtc_times.minutes;
    current_stamp_time->hours = rtc_times.hours;

    current_stamp_time->weeks = week_table[rtc_times.days % 7];

    leap_year_num = (rtc_times.days) / 1461;

    days = (rtc_times.days % 1461); //

    if (0 == days)
    {
        current_stamp_time->years = 3 + (leap_year_num - 1) * 4 + START_YEARS;
        current_stamp_time->months = 12;
        current_stamp_time->days = 31;
    }
    else
    {
        if (1155 <= days) // 365*3+31+29=1155
        {
            current_stamp_time->years = 3 + leap_year_num * 4 + START_YEARS;
            days = (days - 365 * 3) % 366;
            months_table[2] = 60;
            months_table[3] = 91;
            months_table[4] = 121;
            months_table[5] = 152;
            months_table[6] = 182;
            months_table[7] = 213;
            months_table[8] = 244;
            months_table[9] = 274;
            months_table[10] = 305;
            months_table[11] = 335;
        }
        else
        {
            current_stamp_time->years = (rtc_times.days % 1461 - 1) / 365 + leap_year_num * 4 + START_YEARS;
            days = days % 365;
        }

        i = 0;

        while (months_table[i] < days)
        {
            i++;
        }

        if (i == 0)
        {
            current_stamp_time->months = 12;
            current_stamp_time->days = 31;
        }
        else
        {
            current_stamp_time->months = i;
            current_stamp_time->days = (days - months_table[i - 1]);
        }
    }
}
/**
 *  @brief  RTC 模块设置 RTC 当前时间和时间信息函数
 *
 *  @param dt 输入 RTC 日期结构体
 *  @param tim 输入 RTC 时间结构体
 */
void dev_set_rtc_time(rtc_time_t *tim)
{
    uint8_t i = 0;
    rtc_init_t rtc_init;
    rtc_init.set_time.days = tim->days;
    rtc_init.set_time.hours = tim->hours;
    rtc_init.set_time.minutes = tim->minutes;
    rtc_init.set_time.seconds = tim->seconds;

    rtc_init.sys_clk = g_sys_clk; // 系统时钟
    rtc_init.rtc_it_type = RTC_INT_NULL;
    rtc_init.rtc_clk_sel = RTC_EXTERNAL_CLK_SEL;
    hal_rtc_init(&rtc_init);
    delayms(1000);
    hal_rtc_set_time(&(rtc_init.set_time));

    return;
}

/**
 * @brief RTC 模块测试示例函数
 *
 */
void rtc_demo(void)
{
    uint32_t tick = 0;
    uint8_t second = 0;
    t_ctimes gt;
    t_ctimes st = {2024, 01, 02, 0, 23, 59, 58};
    rtc_time_t tim;
    set_time(st, &tim);
    dev_set_rtc_time(&tim);
    hal_rtc_get_time(&tim);
    printf("RTC test ...\r\n");
    while (1)
    {
        delayms(1000);
        hal_rtc_get_time(&tim); // 获取芯片RTC时间
        get_time(&gt, tim);     // 获取时间戳
        printf("Data: %04d年%02d月%02d日 星期%d %02d:%02d:%02d\r\n", gt.years, gt.months, gt.days, week[(gt.weeks)], gt.hours, gt.minutes, gt.seconds);
    }
}

/** @} */ // 结束 RTC 模块分组
/** @} */ // 结束外设模块分组
