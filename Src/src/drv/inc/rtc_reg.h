/**
 *  @file rtc_reg.h
 *  @author Product application department
 *  @brief  RTC 模块寄存器配置文件
 *  @version V1.0
 *  @date 2025-02-13
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __RTC_REG_H_
#define __RTC_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define RTC_BASE_ADDR (0x40035000)
#define RTC ((reg_rtc_t *)(RTC_BASE_ADDR))

// PRT1R
#define RTC_PRT1R_DAYS_COUNTER (0)
#define RTC_PRT1R_DAYS_COUNTER_MASK ((uint32_t)0x00007FFF)

// PRT2R
#define RTC_PRT2R_SECONDS_COUNTER (0)
#define RTC_PRT2R_SECONDS_COUNTER_MASK ((uint32_t)0x0000003F)
#define RTC_PRT2R_MINUTES_COUNTER (8)
#define RTC_PRT2R_MINUTES_COUNTER_MASK ((uint32_t)0x00003F00)
#define RTC_PRT2R_HOURS_COUNTER (16)
#define RTC_PRT2R_HOURS_COUNTER_MASK ((uint32_t)0x001F0000)

// PRA1R
#define RTC_PRA1R_ALARM_DAYS_EN ((uint32_t)1 << 15)
#define RTC_PRA1R_ALARM_DAYS (0)
#define RTC_PRA1R_ALARM_DAYS_MASK ((uint32_t)0x00007FFF)

// PRA2R
#define RTC_PRA2R_ALARM_HOURS_MASK ((uint32_t)0x001F0000)
#define RTC_PRA2R_ALARM_MINUTES_MASK ((uint32_t)0x00003F00)
#define RTC_PRA2R_ALARM_SECONDS_MASK ((uint32_t)0x0000003F)
#define RTC_PRA2R_ALARM_HOURS (16)
#define RTC_PRA2R_ALARM_HOURS_EN ((uint32_t)1 << 23)
#define RTC_PRA2R_ALARM_MINUTES (8)
#define RTC_PRA2R_ALARM_MINUTES_EN ((uint32_t)1 << 15)
#define RTC_PRA2R_ALARM_SECONDS (0)
#define RTC_PRA2R_ALARM_SECONDS_EN ((uint32_t)1 << 7)

// PRTCR
#define RTC_PRTCR_DAYS_COUNTER_MASK ((uint32_t)0xFFFE0000)
#define RTC_PRTCR_DAYS_COUNTER (17)
#define RTC_PRTCR_HOURS_COUNTER_MASK ((uint32_t)0x0001F000)
#define RTC_PRTCR_HOURS_COUNTER (12)
#define RTC_PRTCR_MINUTES_COUNTER_MASK ((uint32_t)0x00000FC0)
#define RTC_PRTCR_MINUTES_COUNTER (6)
#define RTC_PRTCR_SECONDS_COUNTER_MASK ((uint32_t)0x0000003F)
#define RTC_PRTCR_SECONDS_COUNTER (0)

// PRCSR
#define RTC_PRCSR_DAY_IEN ((uint32_t)1 << 30)
#define RTC_PRCSR_HOUR_IEN ((uint32_t)1 << 29)
#define RTC_PRCSR_MINUTE_IEN ((uint32_t)1 << 28)
#define RTC_PRCSR_SECOND_IEN ((uint32_t)1 << 27)
#define RTC_PRCSR_ALARM_IEN ((uint32_t)1 << 26)
#define RTC_PRCSR_1KHZ_IEN ((uint32_t)1 << 25)
#define RTC_PRCSR_32KHZ_IEN ((uint32_t)1 << 24)
#define RTC_PRCSR_DAY_INTF ((uint32_t)1 << 22)
#define RTC_PRCSR_HOUR_INTF ((uint32_t)1 << 21)
#define RTC_PRCSR_MINUTE_INTF ((uint32_t)1 << 20)
#define RTC_PRCSR_SECOND_INTF ((uint32_t)1 << 19)
#define RTC_PRCSR_ALARM_INTF ((uint32_t)1 << 18)
#define RTC_PRCSR_1KHZ_INTF ((uint32_t)1 << 17)
#define RTC_PRCSR_32KHZ_INTF ((uint32_t)1 << 16)
#define RTC_PRCSR_INT_TYPE_MASK ((uint32_t)0x00000300)
#define RTC_PRCSR_LOW_LEVEL_INT (0x00 << 8)           /**< RTC中断产生类型为低电压    */
#define RTC_PRCSR_RISEING_EDGE_INT ((uint32_t)1 << 8) /**< RTC中断产生类型为上升沿    */
#define RTC_PRCSR_FALLING_EDGE_INT (0x02 << 8)        /**< RTC中断产生类型为下降沿    */
#define RTC_PRCSR_RISING_FALLING_EDGE_INT (0x03 << 8) /**< RTC中断产生类型为上升沿或下降沿    */
#define RTC_PRCSR_WCLK_DIV_MASK ((uint32_t)0x000000F8)
#define RTC_PRCSR_CNTUPDATE_EN ((uint32_t)1 << 2)
#define RTC_PRCSR_RCNT_WEN ((uint32_t)1 << 1)
#define RTC_PRCSR_DIR_EN ((uint32_t)1 << 0)

// PRENR
#define RTC_PRENR_RTC_EN_CNTUPDATE_EN ((uint32_t)1 << 10)
#define RTC_PRENR_RTC_EN_RCNT_WEN ((uint32_t)1 << 9)
#define RTC_PRENR_RTC_EN_DIR ((uint32_t)1 << 8)
#define RTC_PRENR_RTC_EN ((uint32_t)1 << 0)

// PRKEYR
#define RTC_PRKEYR_KEY (0x5AA55AA5)

/**
 *  @brief  RTC 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t PRT1R; // 0x00
    __IO uint32_t PRT2R; // 0x04
    __IO uint32_t PRA1R; // 0x08
    __IO uint32_t PRA2R; // 0x0c

    __IO uint32_t PRTCR;  // 0x10
    __IO uint32_t PRCSR;  // 0x14
    __IO uint32_t PRENR;  // 0x18
    __IO uint32_t PRKEYR; // 0x1c
} reg_rtc_t;

#ifdef __cplusplus
}
#endif

#endif // RTC_REG_H
