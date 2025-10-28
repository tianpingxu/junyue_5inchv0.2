/**
 * @file tc_drv.h
 * @author Product application department
 * @brief  TC 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __TC_DRV_H
#define __TC_DRV_H

#ifdef __cplusplus
"C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "tc_reg.h"

// 全局变量定义
#define _tc_set_debug_run(tc) _bit_clr(tc->CR, TC_DEBUG)
#define _tc_set_debug_stop(tc) _bit_set(tc->CR, TC_DEBUG)
#define _tc_set_doze_run(tc) _bit_clr(tc->CR, TC_DOZE)
#define _tc_set_doze_stop(tc) _bit_set(tc->CR, TC_DOZE)
#define _tc_set_wait_run(tc) _bit_clr(tc->CR, TC_WAIT)
#define _tc_set_wait_stop(tc) _bit_set(tc->CR, TC_WAIT)
#define _tc_set_stop_run(tc) _bit_clr(tc->CR, TC_STOP)
#define _tc_set_stop_stop(tc) _bit_set(tc->CR, TC_STOP)
#define _tc_set_reset_enable(tc) _bit_set(tc->CR, TC_RN_MODE_MASK)
#define _tc_set_reset_disable(tc) _bit_clr(tc->CR, TC_RN_MODE_MASK)
#define _tc_get_count(tc) _reg_read(tc->CNTR)
#define _tc_set_wsr(tc, value) _reg_write(tc->SR, value)
#define _tc_set_mr(tc, value) _reg_write(tc->MR, value)
#define _tc_set_prescaler(tc, value) _reg_write(tc->CR, (tc->CR & 0xFF8F) | (value << 4))
#define _tc_enable_int(tc) _bit_set(tc->CR, TC_IE_MODE_MASK)
#define _tc_disable_int(tc) _bit_clr(tc->CR, TC_IE_MODE_MASK)
#define _tc_update_wdp(tc) _bit_set(tc->CR, TC_CU_MODE_MASK)
#define _tc_clear_int_flag(tc) _bit_set(tc->CR, TC_IF_MODE_MASK)

/**
 *@brief TC 模块预分频值枚举定义
 *
 */
typedef enum
{
    TC_WDP_2048 = 0x00,
    TC_WDP_1024 = 0x01,
    TC_WDP_512 = 0x02,
    TC_WDP_256 = 0x03,
    TC_WDP_128 = 0x04,
    TC_WDP_64 = 0x05,
    TC_WDP_32 = 0x06,
    TC_WDP_16 = 0x07
} tc_timer_prescaler_t;
// 函数声明
void drv_tc_wait_cmd(reg_tc_t * tctd, uint8_t status);
void drv_tc_doze_cmd(reg_tc_t * tctd, uint8_t status);
void drv_tc_stop_cmd(reg_tc_t * tctd, uint8_t status);
void drv_tc_debug_cmd(reg_tc_t * tctd, uint8_t status);
void drv_tc_reset_cmd(reg_tc_t * tctd, uint8_t status);
void drv_tc_interrupt_cmd(reg_tc_t * tctd, uint8_t status);
void drv_tc_feed_watch(reg_tc_t * tctd);
void drv_tc_clear_intr_flag(reg_tc_t * tctd);
void drv_tc_set_mr(reg_tc_t * tctd, uint16_t value);
void drv_tc_set_prescaler(reg_tc_t * tctd, tc_timer_prescaler_t value);
void drv_tc_update_wdp(reg_tc_t * tctd);
uint16_t drv_tc_get_counter(reg_tc_t * tctd);
#ifdef __cplusplus
}
#endif

#endif
