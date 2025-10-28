/**
 * @file adc_drv.c
 * @author Product application department
 * @brief  ADC 模块驱动层
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "adc_drv.h"
#include "eport_drv.h"
#include "uart_drv.h"
// 函数定义

/**
 * @brief ADC 模块使能函数
 *
 */
void drv_adc_module_enable(void)
{
    _adc_set_enable_cmd;
    while (!_adc_chk_ready_flag)
        ;
}

/**
 * @brief ADC 模块禁用函数
 *
 */
void drv_adc_module_disable(void)
{
    _adc_set_disable_cmd;
    while (_adc_chk_cr_disable != 0)
        ;
}

/**
 * @brief ADC 模块转换启动函数
 *
 */
void drv_adc_conversion_start(void)
{
    _adc_set_start_conversion_cmd;
}

/**
 * @brief ADC 模块转换停止函数
 *
 */
void drv_adc_conversion_stop(void)
{
    volatile uint32_t tmp;
    _adc_set_stop_conversion_cmd;
    do
    {
        tmp = _adc_chk_cr_disable;
    } while (tmp & ADC_STOP_CONVERSION_CMD_EN);
}

/**
 * @brief ADC 模块通道选择函数
 *
 * @param channel ADC通道
 */
void drv_adc_channel_select(uint32_t channel)
{
    if(channel == ADC_IN1)
        _uart_dis_rx_it(UART1);
    else if(channel == ADC_IN2)
        _uart_dis_rx_it(UART5);

    _adc_set_channel_sel_value(1 << channel);
}

/**
 * @brief ADC 模块通道失能函数
 *
 * @param channel ADC通道
 */
void drv_adc_channel_disselect(uint32_t channel)
{
    if(channel == ADC_IN1)
        _uart_dis_rx_it(UART1);
    else if(channel == ADC_IN2)
        _uart_dis_rx_it(UART5);

    _adc_clr_channel_sel_value(1 << channel);
}

/**
 * @brief ADC 模块触发模式设置函数
 *
 * @param trigger_mode 触发模式
 */
void drv_adc_trigger_mode(uint8_t trigger_mode)
{
    _adc_set_trig_mode(trigger_mode);
}

/**
 * @brief ADC 模块触发源选择函数
 *
 * @param source 触发源
 */
void drv_adc_trigger_select(uint8_t source)
{
    _adc_set_trigger_source_sel_value(source);
}

/**
 * @brief ADC 模块清除采集完成标志位函数
 *
 */
void drv_adc_clr_endflag(void)
{
    _adc_clr_end_sequence_flag;
}

/**
 * @brief ADC 模块等待清除采集完成标志位函数
 *
 */
uint32_t drv_adc_check_endflag()
{
    return _adc_chk_end_sequence_flag;
}

/**
 * @brief ADC 模块中断处理函数
 *
 */
void drv_adc_irq_handler(void)
{
    _adc_clr_all_int_flag;
}

/**
 * @brief ADC 模块中断初始化函数
 * 
 * @param value ADC中断号
 */
void drv_adc_irqinit(uint8_t value)
{
    _adc_set_int_en(value);
}

/**
 * @brief ADC 模块获取数值函数
 *
 * @return ADC 电压
 */
uint16_t drv_adc_get_data(void)
{
    return _adc_get_convert_data;
}

/**
 * @brief ADC 模块初始化函数
 *
 * @param adc ADC 模块初始化参数
 */
void drv_adc_init(adc_init_t *adc)
{
    _adc_set_prescaler_clk_div(adc->clk_div);
    _adc_set_startup_counter(adc->stab_time);
    _adc_set_sampling_time(adc->smp_time);
    _adc_set_data_resolution(adc->resolution);

    // ADC转换队列设置
    _adc_set_sequence_length(0);
    _adc_set_number0_channel_name(adc->channel);

    if (adc->vref == ADC_EXTERNAL_VREF)
    {
        _adc_sel_external_vref;
    }
    else
    {
        _adc_sel_internal_vref;
    }

    if (adc->conv == ADC_CONTINUOUS_CONV_MODE)
    {
        _adc_set_continuous_conversion;
    }
    else
    {
        _adc_set_single_conversion;
    }

    if (adc->overrun == ADC_OVERRUN_MODE_LAST)
    {
        _adc_set_overrun_mode_last;
    }
    else
    {
        _adc_set_overrun_mode_old;
    }

    if (adc->align == ADC_RIGHT_ALIGN)
    {
        _adc_set_data_right_alignment;
    }
    else
    {
        _adc_set_data_left_alignment;
    }
}
