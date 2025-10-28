/**
 * @file tc_hal.h
 * @author Product application department
 * @brief  TC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __TC_HAL_H
#define __TC_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "tc_drv.h"
#include "system_NVIC.h"
#include "interrupt.h"

// 全局变量定义

/**
 * @brief TC 模块回调函数定义
 * 
 */
typedef void (*tc_callback_t)(void *);

/**
 * @brief TC 模块初始化结构体定义
 * 
 */
typedef struct
{
    reg_tc_t *instance;
    uint8_t wait_mode;              // 等待模式位
    uint8_t doze_mode;              // 休眠模式位
    uint8_t stop_mode;              // 停止模式位
    uint8_t debug_mode;             // 停止模式位
    uint8_t reset_enable;           // 复位使能
    uint8_t interrupt_enable;       // 中断使能
    tc_timer_prescaler_t prescaler; // 分频系数
    uint16_t tcmr;                  // 寄存器模数
    tc_callback_t callback;         // 回调函数
} tc_init_t;

// 函数声明
void hal_tc_init(tc_init_t *tcit);
void hal_tc_feed_watchdog(tc_init_t *tcit);
void hal_tc_callback(void *tcit);
void tc_irq_handler(void);
uint16_t hal_tc_get_counter(tc_init_t *tcit);
void hal_tc_porset(void);
#ifdef __cplusplus
}
#endif

#endif
