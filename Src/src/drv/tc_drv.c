/**
 * @file tc_drv.c
 * @author Product application department
 * @brief  TC 模块驱动层
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "tc_drv.h"

// 函数定义
/**
 *  @brief  TC 模块WAIT 模式下启动或停止函数
 *
 *  @param tctd TC 初始化结构体
 *  @param status 功能状态
 */
void drv_tc_wait_cmd(reg_tc_t *tctd, uint8_t status)
{
    if (status == ENABLE)
    {
        _tc_set_wait_run(tctd);
    }
    else if (status == DISABLE)
    {
        _tc_set_wait_run(tctd);
    }
}

/**
 *  @brief  TC 模块DOZE 模式下启动或停止函数
 *
 *  @param tctd TC 初始化结构体
 *  @param status 功能状态
 */
void drv_tc_doze_cmd(reg_tc_t *tctd, uint8_t status)
{
    if (status == ENABLE)
    {
        _tc_set_doze_run(tctd);
    }
    else
    {
        _tc_set_doze_stop(tctd);
    }
}

/**
 *  @brief  TC 模块STOP 模式下启动或停止函数
 *
 *  @param tctd TC 初始化结构体
 *  @param status 功能状态
 */
void drv_tc_stop_cmd(reg_tc_t *tctd, uint8_t status)
{
    if (status == ENABLE)
    {
        _tc_set_stop_run(tctd);
    }
    else
    {
        _tc_set_stop_stop(tctd);
    }
}

/**
 *  @brief  TC 模块DEBUG 模式下启动或停止函数
 *
 *  @param tctd TC 初始化结构体
 *  @param status 功能状态
 */
void drv_tc_debug_cmd(reg_tc_t *tctd, uint8_t status)
{
    if (status == ENABLE)
    {
        _tc_set_debug_run(tctd);
    }
    else
    {
        _tc_set_debug_stop(tctd);
    }
}

/**
 *  @brief  TC 模块数值减为零时，是否复位函数
 *
 *  @param tctd TC 初始化结构体
 *  @param status 功能状态
 */
void drv_tc_reset_cmd(reg_tc_t *tctd, uint8_t status)
{
    if (status == ENABLE)
    {
        _tc_set_reset_enable(tctd);
    }
    else
    {
        _tc_set_reset_disable(tctd);
    }
}

/**
 *  @brief  TC 模块数值减为零时，是否中断函数
 *
 *  @param tctd TC 初始化结构体
 *  @param status 功能状态
 */
void drv_tc_interrupt_cmd(reg_tc_t *tctd, uint8_t status)
{
    if (status == ENABLE)
    {
        _tc_enable_int(tctd);
    }
    else
    {
        _tc_disable_int(tctd);
    }
}

/**
 *  @brief  TC 模块看门狗喂狗函数
 *
 *  @param tctd TC 初始化结构体
 */
void drv_tc_feed_watch(reg_tc_t *tctd)
{
    _tc_set_wsr(tctd, 0x5555);
    _tc_set_wsr(tctd, 0xAAAA);
}

/**
 *  @brief  TC 模块清理中断标志位函数
 *
 *  @param tctd TC 初始化结构体
 */
void drv_tc_clear_intr_flag(reg_tc_t *tctd)
{
    _tc_clear_int_flag(tctd);
}

/**
 *  @brief  TC 模块设置 MR 寄存器的数值函数
 *
 *  @param tctd TC 初始化结构体
 *  @param value MR寄存器设置的数值
 */
void drv_tc_set_mr(reg_tc_t *tctd, uint16_t value)
{
    _tc_set_mr(tctd, value);
}

/**
 *  @brief  TC 模块计时器中的计数器的分频值函数
 *
 *  @param tctd TC 初始化结构体
 *  @param value TC 计时器的分频值
 */
void drv_tc_set_prescaler(reg_tc_t *tctd, tc_timer_prescaler_t value)
{
    _tc_set_prescaler(tctd, value);
}

/**
 *  @brief  TC 模块立即使能设置好的分频值函数
 *
 *  @param tctd TC 初始化结构体
 */
void drv_tc_update_wdp(reg_tc_t *tctd)
{
    _tc_update_wdp(tctd);
}

/**
 *  @brief  TC 模块获取当前计数值函数
 *
 *  @param tctd TC 初始化结构体
 *  @return uint16_t 返回当前计数值
 */
uint16_t drv_tc_get_counter(reg_tc_t *tctd)
{
    return _tc_get_count(tctd);
}
