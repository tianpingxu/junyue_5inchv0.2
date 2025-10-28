/**
 * @file pit32_drv.c
 * @author Product application department
 * @brief  PIT32 模块驱动层
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "pit32_drv.h"

// 函数定义

/**
 *  @brief  PIT32 模块功能使能函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param status 输入使能状态：0- 禁能， 1- 使能
 */
void drv_pit32_cmd(reg_pit32_t *ppit32, uint8_t status)
{
    if (status == ENABLE)
    {
        _pit32_start(ppit32);
    }
    else
    {
        _pit32_stop(ppit32);
    }
}

/**
 *  @brief  PIT32 模块中断功能使能函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param status 输入使能状态：0- 禁能， 1- 使能
 */
void drv_pit32_interrupt_cmd(reg_pit32_t *ppit32, uint8_t status)
{
    if (status == ENABLE)
    {
        _pit32_en_interrupt(ppit32);
    }
    else
    {
        _pit32_dis_interrupt(ppit32);
    }
}

/**
 *  @brief  PIT32 模块重载功能使能函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param status 输入使能状态：0- 禁能， 1- 使能
 */
void drv_pit32_reload_cmd(reg_pit32_t *ppit32, uint8_t status)
{
    if (status == ENABLE)
    {
        _pit32_en_reload(ppit32);
    }
    else
    {
        _pit32_dis_reload(ppit32);
    }
}

/**
 *  @brief  PIT32 模块立即更新计数器功能使能函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param status 输入使能状态：0- 禁能， 1- 使能
 */
void drv_pit32_immediately_update_cnt_cmd(reg_pit32_t *ppit32, uint8_t status)
{
    if (status == ENABLE)
    {
        _pit32_reload_mode_immediate(ppit32);
    }
    else
    {
        _pit32_reload_mode_cnt_zero(ppit32);
    }
}

/**
 *  @brief  PIT32 模块在DEBUG模式下功能使能函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param status 输入使能状态：0- 禁能， 1- 使能
 */
void drv_pit32_debug_cmd(reg_pit32_t *ppit32, uint8_t status)
{
    if (status == ENABLE)
    {
        _pit32_set_debug_run(ppit32);
    }
    else
    {
        _pit32_set_debug_stop(ppit32);
    }
}

/**
 *  @brief  PIT32 模块在DOZE模式下功能使能函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param status 输入使能状态：0- 禁能， 1- 使能
 */
void drv_pit32_doze_cmd(reg_pit32_t *ppit32, uint8_t status)
{
    if (status == ENABLE)
    {
        _pit32_set_doze_run(ppit32);
    }
    else
    {
        _pit32_set_doze_stop(ppit32);
    }
}

/**
 *  @brief  PIT32 模块设置分频系数函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param prescaler 设置 PIT32 分频系数
 */
void drv_pit32_set_prescaler(reg_pit32_t *ppit32, pit32_clkdiv_t prescaler)
{
    _pit32_set_prescaler(ppit32, prescaler);
}

/**
 *  @brief  PIT32 模块设置计数器数值函数
 *
 *  @param ppit32 PIT32 初始化结构体
 *  @param cnt 设置 PIT32 计数器数值
 */
void drv_pit32_set_counter(reg_pit32_t *ppit32, uint32_t cnt)
{
    _pit32_set_pmr_all(ppit32, cnt);
}

/**
 *  @brief  PIT32 模块获取当前计数器数值函数
 *
 *  @param ppit32  PIT32 初始化结构体
 *  @return uint32_t 获取当前 PIT32 计数器数值
 */
uint32_t drv_pit32_get_counter(reg_pit32_t *ppit32)
{
    return _pit32_get_pcntr_all(ppit32);
}

/**
 *  @brief  PIT32 模块清理中断标志位函数
 *
 *  @param ppit32 PIT32 初始化结构体
 */
void drv_pit32_clear_intr_flag(reg_pit32_t *ppit32)
{
    _pit32_clr_int_flag(ppit32);
}
