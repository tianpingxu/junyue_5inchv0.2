/**
 * @file rtc_drv.c
 * @author Product application department
 * @brief  RTC 模块驱动层
 * @version V1.0
 * @date 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "rtc_drv.h"

// 全局变量定义
#define DRV_RTC_DEBUG printf

// 函数定义

/**
 *  @brief  RTC 模块中断服务函数
 *
 */
void drv_rtc_irq_handler(void)
{
    uint32_t prcsr = 0;
    uint8_t alarm_wakeup_flg = 1;

    prcsr = _rtc_prcsr_get_val;

    if (((prcsr & RTC_PRCSR_ALARM_INTF) == RTC_PRCSR_ALARM_INTF) && ((prcsr & RTC_PRCSR_ALARM_IEN) == RTC_PRCSR_ALARM_IEN)) // alarm interrupt
    {
        _rtc_prcsr_alarm_pulse_clr_flag;
        alarm_wakeup_flg = 0;
        DRV_RTC_DEBUG("rtc alarm\r\n");
    }

    if (((prcsr & RTC_PRCSR_DAY_INTF) == RTC_PRCSR_DAY_INTF) && ((prcsr & RTC_PRCSR_DAY_IEN) == RTC_PRCSR_DAY_IEN)) // day interrupt
    {
        _rtc_prcsr_day_pulse_clr_flag;
        alarm_wakeup_flg = 0;
        DRV_RTC_DEBUG("rtc day alarm\r\n");
    }

    if (((prcsr & RTC_PRCSR_HOUR_INTF) == RTC_PRCSR_HOUR_INTF) && ((prcsr & RTC_PRCSR_HOUR_IEN) == RTC_PRCSR_HOUR_IEN)) // hour interrupt
    {
        _rtc_prcsr_hour_pulse_clr_flag;
        alarm_wakeup_flg = 0;
        DRV_RTC_DEBUG("rtc hour alarm\r\n");
    }

    if (((prcsr & RTC_PRCSR_MINUTE_INTF) == RTC_PRCSR_MINUTE_INTF) && ((prcsr & RTC_PRCSR_MINUTE_IEN) == RTC_PRCSR_MINUTE_IEN)) // minute interrupt
    {
        _rtc_prcsr_min_pulse_clr_flag;
        alarm_wakeup_flg = 0;
        DRV_RTC_DEBUG("rtc minute alarm\r\n");
    }

    if (((prcsr & RTC_PRCSR_SECOND_INTF) == RTC_PRCSR_SECOND_INTF) && ((prcsr & RTC_PRCSR_SECOND_IEN) == RTC_PRCSR_SECOND_IEN)) // second interrupt
    {
        _rtc_prcsr_sec_pulse_clr_flag;
        alarm_wakeup_flg = 0;
        DRV_RTC_DEBUG("rtc second alarm\r\n");
    }

    if (alarm_wakeup_flg)
    {
        DRV_RTC_DEBUG("\r\nRTC alarm wakeup from sleep mode\r\n");
        _rtc_prkeyr_key_set; // 输入key
        _rtc_prcsr_alarm_pulse_ie_dis;
        _rtc_prcsr_direct_control_dis; // set dir = 0;
    }
}

/**
 *  @brief  RTC 模块设置时间计数函数
 *
 *  @param time RTC 时间结构体
 */
void drv_rtc_set_time_counter(rtc_time_t *time)
{
    _rtc_prt1r_counter_days_set(time->days);
    _rtc_prt2r_counter_set(time->hours, time->minutes, time->seconds);
}

/**
 *  @brief  RTC 模块设置报警时间计数函数
 *
 *  @param time RTC 时间结构体
 */
void drv_rtc_set_alarm_time_counter(rtc_time_t *time)
{
    _rtc_pra1r_alarm_day_counter_set(time->days);
    _rtc_pra2r_alarm_hour_counter_set(time->hours);
    _rtc_pra2r_alarm_min_counter_set(time->minutes);
    _rtc_pra2r_alarm_sec_counter_set(time->seconds);
}

/**
 *  @brief  RTC 模块获取时间计数函数
 *
 *  @param time RTC 时间结构体
 */
void drv_rtc_get_time_counter(rtc_time_t *time)
{
    time->days = _rtc_prtcr_days_counter_get;
    time->hours = _rtc_prtcr_hours_counter_get;
    time->minutes = _rtc_prtcr_mins_counter_get;
    time->seconds = _rtc_prtcr_secs_counter_get;
}

/**
 *  @brief  RTC 模块时钟源选择配置函数
 *
 *  @param clk_src RTC 时钟源切换
 */
void drv_rtc_clock_exchange(rtc_src_t clk_src)
{

    if (clk_src == RTC_INTERNAL_CLK_SEL)
    {
        // 切换到内部32K时钟
        printf("初始化 INTERNAL_32K_CLK_SEL\r\n");
        _rtc_prenr_direct_control_en; // disable PMU_RTC 5
        _rtc_prenr_rtc_en_rcnt_wen_en;
    }
    else
    {
        //
    }
}

/**
 *  @brief  RTC 模块时钟设置函数
 *
 *  @param sys_clk 系统时钟
 */
void drv_rtc_clock_set(uint32_t sys_clk)
{
    uint32_t rtc_wclk_div = 0;

    rtc_wclk_div = sys_clk / RTC_WCLK_MAX;
    if (rtc_wclk_div >= 1)
    {
        rtc_wclk_div--;
    }

    // 输入key
    _rtc_prkeyr_key_set;

    // 分频
    _rtc_prcsr_wclk_div(rtc_wclk_div);

    // set dir = 0
    _rtc_prcsr_direct_control_dis;
}
