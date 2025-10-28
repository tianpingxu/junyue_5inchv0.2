/**
 * @file rtc_drv.h
 * @author Product application department
 * @brief  RTC 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __RTC_DRV_H
#define __RTC_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "rtc_reg.h"
#include "debug.h"
    
// 全局变量定义
#define RTC_WCLK_MAX 10000000 // 10MHz
// PRT1R
#define _rtc_prt1r_counter_days_set(val) _reg_write(RTC->PRT1R, (uint16_t)val)

// PRT2R
#define _rtc_prt2r_counter_set(h, m, s) _reg_write(RTC->PRT2R, ((h << RTC_PRT2R_HOURS_COUNTER) | (m << RTC_PRT2R_MINUTES_COUNTER) | (s)))

// PRA1R
#define _rtc_pra1r_alarm_day_en _bit_set(RTC->PRA1R, RTC_PRA1R_ALARM_DAYS_EN)
#define _rtc_pra1r_alarm_day_dis _bit_clr(RTC->PRA1R, RTC_PRA1R_ALARM_DAYS_EN)
#define _rtc_pra1r_alarm_day_counter_set(val) _reg_modify(RTC->PRA1R, ~RTC_PRA1R_ALARM_DAYS_MASK, val)

// PRA2R
#define _rtc_pra2r_alarm_hour_en _bit_set(RTC->PRA2R, RTC_PRA2R_ALARM_HOURS_EN)
#define _rtc_pra2r_alarm_hour_dis _bit_clr(RTC->PRA2R, RTC_PRA2R_ALARM_HOURS_EN)
#define _rtc_pra2r_alarm_min_en _bit_set(RTC->PRA2R, RTC_PRA2R_ALARM_MINUTES_EN)
#define _rtc_pra2r_alarm_min_dis _bit_clr(RTC->PRA2R, RTC_PRA2R_ALARM_MINUTES_EN)
#define _rtc_pra2r_alarm_sec_en _bit_set(RTC->PRA2R, RTC_PRA2R_ALARM_SECONDS_EN)
#define _rtc_pra2r_alarm_sec_dis _bit_clr(RTC->PRA2R, RTC_PRA2R_ALARM_SECONDS_EN)
#define _rtc_pra2r_alarm_hour_counter_set(val) _reg_modify(RTC->PRA2R, ~RTC_PRA2R_ALARM_HOURS_MASK, val << RTC_PRA2R_ALARM_HOURS)
#define _rtc_pra2r_alarm_min_counter_set(val) _reg_modify(RTC->PRA2R, ~RTC_PRA2R_ALARM_MINUTES_MASK, val << RTC_PRA2R_ALARM_MINUTES)
#define _rtc_pra2r_alarm_sec_counter_set(val) _reg_modify(RTC->PRA2R, ~RTC_PRA2R_ALARM_SECONDS_MASK, val)

// PRTCR
#define _rtc_prtcr_days_counter_get ((_reg_read(RTC->PRTCR) & RTC_PRTCR_DAYS_COUNTER_MASK) >> RTC_PRTCR_DAYS_COUNTER)
#define _rtc_prtcr_hours_counter_get ((_reg_read(RTC->PRTCR) & RTC_PRTCR_HOURS_COUNTER_MASK) >> RTC_PRTCR_HOURS_COUNTER)
#define _rtc_prtcr_mins_counter_get ((_reg_read(RTC->PRTCR) & RTC_PRTCR_MINUTES_COUNTER_MASK) >> RTC_PRTCR_MINUTES_COUNTER)
#define _rtc_prtcr_secs_counter_get ((_reg_read(RTC->PRTCR) & RTC_PRTCR_SECONDS_COUNTER_MASK) >> RTC_PRTCR_SECONDS_COUNTER)

// PRCSR
#define _rtc_prcsr_get_val _reg_read(RTC->PRCSR)
#define _rtc_prcsr_day_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_DAY_IEN)
#define _rtc_prcsr_day_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_DAY_IEN)
#define _rtc_prcsr_hour_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_HOUR_IEN)
#define _rtc_prcsr_hour_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_HOUR_IEN)
#define _rtc_prcsr_min_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_MINUTE_IEN)
#define _rtc_prcsr_min_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_MINUTE_IEN)
#define _rtc_prcsr_sec_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_SECOND_IEN)
#define _rtc_prcsr_sec_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_SECOND_IEN)
#define _rtc_prcsr_alarm_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_ALARM_IEN)
#define _rtc_prcsr_alarm_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_ALARM_IEN)
#define _rtc_prcsr_1khz_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_1KHZ_IEN)
#define _rtc_prcsr_1khz_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_1KHZ_IEN)
#define _rtc_prcsr_32khz_pulse_ie_en _bit_set(RTC->PRCSR, RTC_PRCSR_32KHZ_IEN)
#define _rtc_prcsr_32khz_pulse_ie_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_32KHZ_IEN)
#define _rtc_prcsr_day_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_DAY_INTF)
#define _rtc_prcsr_hour_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_HOUR_INTF)
#define _rtc_prcsr_min_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_MINUTE_INTF)
#define _rtc_prcsr_sec_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_SECOND_INTF)
#define _rtc_prcsr_alarm_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_ALARM_INTF)
#define _rtc_prcsr_day_pulse_clr_flag _bit_set(RTC->PRCSR, RTC_PRCSR_DAY_INTF)
#define _rtc_prcsr_hour_pulse_clr_flag _bit_set(RTC->PRCSR, RTC_PRCSR_HOUR_INTF)
#define _rtc_prcsr_min_pulse_clr_flag _bit_set(RTC->PRCSR, RTC_PRCSR_MINUTE_INTF)
#define _rtc_prcsr_sec_pulse_clr_flag _bit_set(RTC->PRCSR, RTC_PRCSR_SECOND_INTF)
#define _rtc_prcsr_alarm_pulse_clr_flag _bit_set(RTC->PRCSR, RTC_PRCSR_ALARM_INTF)
#define _rtc_prcsr_1khz_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_1KHZ_INTF)
#define _rtc_prcsr_32khz_pulse_ie_flag _bit_get(RTC->PRCSR, RTC_PRCSR_32KHZ_INTF)
#define _rtc_prcsr_ie_type_low_level _reg_modify(RTC->PRCSR, ~RTC_PRCSR_INT_TYPE_MASK, RTC_PRCSR_LOW_LEVEL_INT)
#define _rtc_prcsr_ie_type_rise_edge _reg_modify(RTC->PRCSR, ~RTC_PRCSR_INT_TYPE_MASK, RTC_PRCSR_RISEING_EDGE_INT)
#define _rtc_prcsr_ie_type_fall_edge _reg_modify(RTC->PRCSR, ~RTC_PRCSR_INT_TYPE_MASK, RTC_PRCSR_FALLING_EDGE_INT)
#define _rtc_prcsr_ie_type_rise_fall_edge _reg_modify(RTC->PRCSR, ~RTC_PRCSR_INT_TYPE_MASK, RTC_PRCSR_RISING_FALLING_EDGE_INT)
#define _rtc_prcsr_wclk_div(div) _reg_modify(RTC->PRCSR, ~RTC_PRCSR_WCLK_DIV_MASK, div << 3)
#define _rtc_prcsr_rcnt_wen_en _bit_set(RTC->PRCSR, RTC_PRCSR_RCNT_WEN)
#define _rtc_prcsr_rcnt_wen_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_RCNT_WEN)
#define _rtc_prcsr_direct_control_en _bit_set(RTC->PRCSR, RTC_PRCSR_DIR_EN)
#define _rtc_prcsr_direct_control_dis _bit_clr(RTC->PRCSR, RTC_PRCSR_DIR_EN)

// PRENR
#define _rtc_prenr_rtc_en _bit_set(RTC->PRENR, RTC_PRENR_RTC_EN)
#define _rtc_prenr_rtc_dis _bit_clr(RTC->PRENR, RTC_PRENR_RTC_EN)
#define _rtc_prenr_direct_control_en _bit_set(RTC->PRENR, RTC_PRENR_RTC_EN_DIR)
#define _rtc_prenr_direct_control_dis _bit_clr(RTC->PRENR, RTC_PRENR_RTC_EN_DIR)
#define _rtc_prenr_rtc_en_rcnt_wen_en _bit_set(RTC->PRENR, RTC_PRENR_RTC_EN_RCNT_WEN)
#define _rtc_prenr_rtc_en_rcnt_wen_dis _bit_clr(RTC->PRENR, RTC_PRENR_RTC_EN_RCNT_WEN)
#define _rtc_prenr_cntupdate_en_get _bit_get(RTC->PRENR, RTC_PRENR_RTC_EN_CNTUPDATE_EN)

// PRKEYR
#define _rtc_prkeyr_key_set _reg_write(RTC->PRKEYR, RTC_PRKEYR_KEY)

/**
 *  @brief  RTC 模块时间结构体定义
 *
 */
typedef struct
{
    __IO uint16_t days;
    __IO uint8_t hours;
    __IO uint8_t minutes;
    __IO uint8_t seconds;
} rtc_time_t;
/**
 *  @brief  RTC 模块时钟源选择枚举定义
 *
 */
typedef enum
{
    RTC_INTERNAL_CLK_SEL = 0,
    RTC_EXTERNAL_CLK_SEL
} rtc_src_t;
// 函数声明
void drv_rtc_irq_handler(void);
void drv_rtc_set_time_counter(rtc_time_t *time);
void drv_rtc_set_alarm_time_counter(rtc_time_t *time);
void drv_rtc_get_time_counter(rtc_time_t *time);
void drv_rtc_clock_exchange(rtc_src_t clk_src);
void drv_rtc_clock_set(uint32_t sys_clk);
#ifdef __cplusplus
}
#endif

#endif
