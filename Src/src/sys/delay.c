/**
 * @file delay.c
 * @author Product application department
 * @brief  DELAY 延迟配置文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "cpm_drv.h"
#include "delay.h"
// 函数定义

/**
 * @brief 延迟MS函数
 *
 * @param delayms 延迟时间
 */
 void delayms(__IO uint32_t delayms)
{
     __IO uint32_t k = 0;
     __IO uint32_t counter_ms = 0;

    counter_ms = g_sys_clk / 3000;

    while (delayms--)
    {
        while (k < counter_ms)
            k++;

        k = 0;
    }

}

/**
 * @brief 延迟时间函数
 *
 * @param time 延迟时间
 */

void delay(__IO uint32_t time)
{
    while (time--)
        ;
}

/**
 * @brief 延迟US函数
 *
 * @param delayus 延迟时间
 */
void delayus(__IO uint32_t delayus)
{
    uint32_t k = 0;
    __IO uint32_t counter_us;

    counter_us = g_sys_clk / 36000000;

    while (delayus--)
    {
        while (k < delayus)
            k++;
        k = 0;
    }
}
