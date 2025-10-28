/**
 * @file systick_drv.c
 * @author Product application department
 * @brief  SYSTICK 模块驱动层
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "systick_drv.h"

#ifdef LVGL_OS
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#endif

// 函数定义
/**
 * @brief SYSTICK 模块配置函数
 *
 * @param ticks 心跳时间
 * @return uint32_t
 */
uint32_t drv_systick_config(uint32_t ticks)
{
    return SysTick_Config(ticks);
}

/**
 * @brief SysTick 模块中断服务函数
 *
 */
void drv_systick_handler(void)
{

#ifdef LVGL_OS

    extern void xPortSysTickHandler(void);
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
    {
        uint32_t ulReturn;
        ulReturn = taskENTER_CRITICAL_FROM_ISR();
        xPortSysTickHandler();
        taskEXIT_CRITICAL_FROM_ISR(ulReturn);
    }
#endif

#ifdef LVGL_MCU

    extern void LVGL_SYSTIC_Handler(void);
    LVGL_SYSTIC_Handler();
#endif
}

/**
 * @brief SYSTICK 模块使能/失能函数
 *
 * @param flag
 */
void drv_systick_enable(uint8_t flag)
{
    if (flag == TRUE)
    {
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    }
    else
    {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }
}
