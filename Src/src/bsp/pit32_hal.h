/**
 * @file pit32_hal.h
 * @author Product application department
 * @brief  PIT32 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __PIT32_HAL_H
#define __PIT32_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "pit32_drv.h"
#include "cpm_drv.h"
#include "interrupt.h"

// 全局变量定义

/**
 * @brief pit32_init_t 回调函数结构体定义
 * 
 */
typedef void (*hal_pit32_callback_t)(void);

/**
 *  @brief  PIT32 模块计数器数值计算定义
 *
 */
#define hal_pit32_calc_counter(clk, div, time) pit32_calc_counter(clk, div, time)

/**
 * @brief  PIT32 模块初始化结构体 定义
 * 
 */
typedef struct
{
    uint8_t reload;           // reload使能
    uint8_t enable_ie;        // 中断使能
    uint8_t update_cnt;       // 写入PMR寄存器的值后立即更新计数器
    uint8_t run_at_doze;      // 在doze模式下是否正常运行
    uint8_t run_at_debug;     // 在debug模式下是否正常运行
    pit32_clkdiv_t prescaler; // 分频系数
    uint32_t counter;         // 计数器数值：cnt = (Fsys/(prescaler *second))
} hal_pit32_t;

/**
 * @brief PIT32 模块句柄结构体定义
 * 
 */
typedef struct
{
    reg_pit32_t *instance;         // PIT32 模块寄存器结构体
    hal_pit32_t init;              // PIT32 初始化结构体
    hal_pit32_callback_t callback; // 回调函数
} hal_pit32_handler_t;

// 函数声明
void hal_pit32_1_irq_handler(void);
void hal_pit32_2_irq_handler(void);
uint8_t hal_pit32_init(hal_pit32_handler_t *hpit32);
uint32_t hal_pit32_get_counter(hal_pit32_handler_t *ppit32);

#ifdef __cplusplus
}
#endif

#endif
