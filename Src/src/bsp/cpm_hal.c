/**
 * @file cpm_hal.c
 * @author Product application department
 * @brief  CPM 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright  Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "cpm_hal.h"

// 函数定义

/**
 * @brief CPM 模块使能/失能模块时钟函数
 *
 * @param ModuleClkIdex 使能/失能的IP模块
 * @param NewState 模块时钟的新状态
 */
void hal_cpm_moduleclkcmd(cpm_moduleclkindex_t ModuleClkIdex, functionalstate_t NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the selected  Module clock*/
        drv_cpm_moduleclkon(ModuleClkIdex);
    }
    else
    {
        /* Disable the selected IP Module clock*/
        drv_cpm_moduleclkoff(ModuleClkIdex);
    }
}

/**
 * @brief CPM 模块唤醒中断源初始化函数
 *
 * @param Src CPM唤醒源选择
 * @param NewState 是否使能中断
 */
void hal_cpm_wakeupinit(cpm_padwakeupindex_t Src, functionalstate_t NewState)
{
    drv_cpm_wakeupinit(Src, NewState);
}

/**
 * @brief CPM 模块POR复位函数
 *
 */
void hal_cpm_porreset(void)
{
    drv_cpm_porreset();
}

void hal_cpm_poweroff(void)
{
    drv_cpm_poweroff();
}

void hal_cpm_lowpower(void)
{
    drv_cpm_lowpower();
}


/**
 * @brief CPM 模块获取IP、EFM、SYSTEM的时钟函数
 * @param ClkSourceFlg 时钟源标志
 * @return
 */
uint32_t hal_cpm_getclockfreq(uint8_t ClkSourceFlg)
{
    int32_t clock_freq = 0;

    switch (ClkSourceFlg)
    {
    case HAL_SYSCLKSOURCE_FLAG:
    {
        clock_freq = drv_cpm_getsysclk();
        break;
    }
    case HAL_IPSCLKSOURCE_FLAG:
    {
        clock_freq = drv_cpm_getipsclk();
        break;
    }
    default:
    {
        clock_freq = drv_cpm_getsysclk();
        break;
    }
    }
    return (clock_freq);
}
 /**
 * @brief CPM 模块 外设复位函数
 * @param  
 */
void hal_cpm_module_reset(cpm_module_t module)
{
     drv_cpm_module_reset(module);
}
/**
 * @brief CPM 模块设置SDRAM2LCD时钟分频函数
 * 
 * @param div 分频系数
 */
void hal_cpm_sdram2lcd_module_set_div(uint8_t div)
{
    drv_cpm_sdram2lcd_module_set_div(div);
}
