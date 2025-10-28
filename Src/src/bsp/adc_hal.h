/**
 * @file adc_hal.h
 * @author Product application department
 * @brief  ADC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef _ADC_HAL_H
#define _ADC_HAL_H
#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "adc_drv.h"
#include "interrupt.h"
#include "system_NVIC.h"
#include "pwmt_hal.h"

// 全局变量定义
typedef void (*adc_callback_t)(void *);

/**
 * @brief  ADC 模块时钟分频枚举定义
 * 
 */
typedef enum
{
    ADC_CLK_DIV_1 = 0,
    ADC_CLK_DIV_2,
    ADC_CLK_DIV_3,
    ADC_CLK_DIV_4,
    ADC_CLK_DIV_5,
    ADC_CLK_DIV_6,
    ADC_CLK_DIV_7,
    ADC_CLK_DIV_8,
    ADC_CLK_DIV_9,
    ADC_CLK_DIV_10,
    ADC_CLK_DIV_11,
    ADC_CLK_DIV_12,
    ADC_CLK_DIV_13,
    ADC_CLK_DIV_14,
    ADC_CLK_DIV_15,
    ADC_CLK_DIV_16
} adc_clkdiv_t;

/**
 * @brief ADC 模块句柄结构体定义
 * 
 */
typedef struct
{
    reg_adc_t *instance;     /*!< ADC实例指针 */
    adc_init_t init;         /*!< ADC初始化结构体 */
    adc_callback_t callback; /*!< 回调函数 */
} adc_handle_t;

/**
 * @brief ADC 模块中断类型枚举定义
 * 
 */
typedef enum
{
    HAL_ADC_NULL_INT = 0,
    HAL_ADC_ANALOG_WD_INT = ADC_ANALOG_WD_INT_EN,
    HAL_ADC_OVER_RUN_INT = ADC_OVER_RUN_INT_EN,
    HAL_ADC_END_SEQUENCE_INT = ADC_END_SEQUENCE_INT_EN,
    HAL_ADC_END_CONVERSION_INT = ADC_END_CONVERSION_INT_EN,
    HAL_ADC_END_SAMPLING_INT = ADC_END_SAMPLING_INT_EN,
    HAL_ADC_READY_INT = ADC_READY_INT_EN,
} adc_interrupt_t;

/**
 * @brief ADC 模块触发模式枚举定义
 * 
 */
typedef enum
{
    HAL_ADC_TRIGGER_SOFT = 0,
    HAL_ADC_TRIGGER_RISING_EDGE,
    HAL_ADC_TRIGGER_FALLING_EDGE,
    HAL_ADC_TRIGGER_RISING_FALLING_EDGE,
    HAL_ADC_TRIGGER_HIGH_LEVEL,
    HAL_ADC_TRIGGER_LOW_LEVEL,
    HAL_ADC_TRIGGER_SINGLE_LEVEL,
} adc_triggermode_t;

/**
 * @brief ADC 模块触发源枚举定义
 * 
 */
typedef enum
{
    HAL_ADC_TRIGGER_PIT1 = 0,
    HAL_ADC_TRIGGER_PIT2 = 1,
    HAL_ADC_TRIGGER_PWMT1 = 4,
    HAL_ADC_TRIGGER_PWMT2 = 5,
    HAL_ADC_TRIGGER_PWMT3 = 6,
} adc_triggersource_t;

// 函数声明
void hal_adc_init(adc_init_t *adc);
void hal_adc_moduleen(BOOL en);
uint16_t hal_adc_getconversionvalue(void);
void hal_adc_stop(void);
void hal_adc_start(void);

#ifdef __cplusplus
}
#endif

#endif