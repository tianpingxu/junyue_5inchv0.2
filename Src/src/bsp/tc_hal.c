/**
 * @file tc_hal.c
 * @author Product application department
 * @brief  TC 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 *  date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "tc_hal.h"
#include "cpm_drv.h"
// 全局变量定义
static uint32_t tc_tick = 0;
static tc_init_t *g_tcit;

// 函数定义

/**
 *  @brief  TC 模块注册寄存器的回调函数
 *
 *  @param tcit HAL 层 TC 初始化结构体
 *  @param callback TC HAL 层回调函数实例
 *  @param index HAL 层回调函数类别
 *  @return uint8_t 注册回调函数结果: 0- 成功, 1-失败
 */
static uint8_t hal_tc_config_callback_register(tc_init_t *tcit, tc_callback_t callback, uint8_t index)
{
    (void)index;
    tcit->callback = callback;
    return 0;
}

/**
 *  @brief  TC 模块中断处理函数
 *
 */
void hal_tc_irq_handler(void)
{
    drv_tc_clear_intr_flag(g_tcit->instance);
    tc_tick++;
    if (g_tcit->callback)
    {
        g_tcit->callback((void *)g_tcit);
        return;
    }
}

/**
 *  @brief  TC 模块回调函数
 *
 *  @param tcit TC HAL 层初始化结构体
 */
void hal_tc_callback(void *tcit)
{
}

/**
 *  @brief  TC 模块初始化函数
 *
 *  @param tcit TC HAL 层初始化结构体
 */
void hal_tc_init(tc_init_t *tcit)
{
    drv_tc_debug_cmd(tcit->instance, tcit->debug_mode);
    drv_tc_doze_cmd(tcit->instance, tcit->doze_mode);
    drv_tc_wait_cmd(tcit->instance, tcit->wait_mode);
    drv_tc_stop_cmd(tcit->instance, tcit->stop_mode);
    drv_tc_reset_cmd(tcit->instance, tcit->reset_enable);

    if (tcit->interrupt_enable == ENABLE)
    {
        TC1_IRQHandler_Callback = hal_tc_irq_handler;
        hal_tc_config_callback_register(tcit, hal_tc_callback, 0);
        NVIC_Init(3, 1, TC_IRQn, 2);
    }
    drv_cpm_porset();
    drv_tc_interrupt_cmd(tcit->instance, tcit->interrupt_enable);
    drv_tc_set_mr(tcit->instance, tcit->tcmr);
    drv_tc_set_prescaler(tcit->instance, tcit->prescaler);
    drv_tc_update_wdp(tcit->instance);

    g_tcit = tcit;
}

/**
 *  @brief  TC 模块获取当前计数值函数
 *
 *  @param tcit TC HAL 层初始化结构体
 *  @return uint16_t 返回当前计数值
 */
uint16_t hal_tc_get_counter(tc_init_t *tcit)
{
    return drv_tc_get_counter(tcit->instance);
}

/**
 *  @brief  TC 模块看门狗喂狗函数
 *
 *  @param tcit TC HAL 层初始化结构体
 */
void hal_tc_feed_watchdog(tc_init_t *tcit)
{
    drv_tc_feed_watch(tcit->instance);
}

/**
 * @brief TC 复位等级设置函数
 * @param  
 */
void hal_tc_porset(void)
{
    drv_cpm_porset();
}