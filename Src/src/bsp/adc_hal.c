/**
 * @file adc_hal.c
 * @author Product application department
 * @brief  ADC 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "adc_hal.h"

// 函数定义

/**
 * @brief ADC 模块初始化函数
 *
 * @param adc ADC模块初始化参数
 */
void hal_adc_init(adc_init_t *adc)
{

    drv_adc_init(adc);
    drv_adc_channel_select(adc->channel);

    if (adc->int_kind != 0)
    {
        NVIC_Init(3, 3, QADC_IRQn, 2);
        drv_adc_irqinit(adc->int_kind);
    }
    drv_adc_trigger_mode(adc->trigger_mode);
    drv_adc_trigger_select(adc->trigger_source);
}

/**
 * @brief ADC 模块功能开启函数
 *
 * @param en 是否使能
 */
void hal_adc_moduleen(BOOL en)
{
    if (en == TRUE)
    {
        drv_adc_module_enable();
    }
    else if (en == FALSE)
    {
        drv_adc_module_disable();
    }
}

/**
 * @brief ADC 模块采样函数函数
 *
 * @return uint16_t ADC采样值
 */
uint16_t hal_adc_getconversionvalue(void)
{
    uint32_t tmp;
    uint8_t i;

    for (i = 0; i < 9; i++)
    {
        drv_adc_conversion_start();

        while (drv_adc_check_endflag() != ADC_END_SEQUENCE_FLAG)
            ;
        drv_adc_clr_endflag();
        drv_adc_conversion_stop();

        // 丢掉第一个采样值
        if (i == 0)
        {
            tmp = drv_adc_get_data();
            tmp = 0;
            continue;
        }

        tmp += drv_adc_get_data();
    }

    return ((tmp >> 3) & 0xFFFF);
}

/**
 * @brief ADC 模块停止采样函数
 *
 */
void hal_adc_stop(void)
{
    drv_adc_conversion_stop();
}

/**
 * @brief ADC 模块启动采样函数
 *
 */
void hal_adc_start(void)
{
    drv_adc_conversion_start();
}