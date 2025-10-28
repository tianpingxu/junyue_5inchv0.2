/**
 * @file pit32_hal.c
 * @author Product application department
 * @brief  PIT32 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "pit32_hal.h"

// 全局变量定义
static hal_pit32_handler_t *g_hpit32_t1;
static hal_pit32_handler_t *g_hpit32_t2;

// 函数定义

/**
 *  @brief  PIT32_1 模块中断处理函数
 *
 */
void hal_pit32_1_irq_handler(void)
{
    drv_pit32_clear_intr_flag(g_hpit32_t1->instance);

    if (g_hpit32_t1->callback)
    {
        g_hpit32_t1->callback();
        return;
    }
}

/**
 *  @brief  PIT32_2 模块中断处理函数
 *
 */
void hal_pit32_2_irq_handler(void)
{
    drv_pit32_clear_intr_flag(g_hpit32_t2->instance);

    if (g_hpit32_t2->callback)
    {
        g_hpit32_t2->callback();
        return;
    }
}

/**
 *  @brief  PIT32 模块初始化函数
 *
 *  @param hpit32 PIT32 HAL 层句柄结构体定义
 *  @return uint8_t PIT32初始化结果：0- 成功，1- 失败
 */
uint8_t hal_pit32_init(hal_pit32_handler_t *hpit32)
{
    drv_pit32_cmd(hpit32->instance, 0);
    drv_pit32_set_prescaler(hpit32->instance, hpit32->init.prescaler);
    drv_pit32_reload_cmd(hpit32->instance, hpit32->init.reload);
    drv_pit32_immediately_update_cnt_cmd(hpit32->instance, hpit32->init.update_cnt);
    drv_pit32_doze_cmd(hpit32->instance, hpit32->init.run_at_doze);
    drv_pit32_debug_cmd(hpit32->instance, hpit32->init.run_at_debug);
    drv_pit32_set_counter(hpit32->instance, hpit32->init.counter);

    if (hpit32->init.enable_ie == 1)
    {
        if (hpit32->instance == PIT1)
        {
            NVIC_Init(3, 3, PIT1_IRQn, 2);
            PIT1_IRQHandler_Callback = hal_pit32_1_irq_handler;
        }
        else
        {
            NVIC_Init(3, 3, PIT2_IRQn, 2);
            PIT2_IRQHandler_Callback = hal_pit32_2_irq_handler;
        }
    }

    if (hpit32->instance == PIT1)
    {
        g_hpit32_t1 = hpit32;
    }
    else
    {
        g_hpit32_t2 = hpit32;
    }

    drv_pit32_interrupt_cmd(hpit32->instance, hpit32->init.enable_ie);
    drv_pit32_cmd(hpit32->instance, 1);

    return 0;
}

/**
 *  @brief  PIT32 模块获取当前计数器数值函数
 *
 *  @param ppit32 PIT32 HAL 层句柄结构体定义
 *  @return uint32_t 获取当前 PIT32 计数器数值
 */
uint32_t hal_pit32_get_counter(hal_pit32_handler_t *ppit32)
{
    return drv_pit32_get_counter(ppit32->instance);
}
