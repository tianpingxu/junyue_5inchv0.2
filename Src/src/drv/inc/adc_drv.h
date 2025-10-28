/**
 * @file adc_drv.h
 * @author Product application department
 * @brief  ADC 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DRV_ADC_H
#define __DRV_ADC_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "adc_reg.h"

// 全局变量定义
// ADC_ISR
#define _adc_chk_analog_wd_flag _reg_chk(ADC->ADC_ISR, ADC_ANALOG_WD_FLAG)
#define _adc_clr_analog_wd_flag _bit_set(ADC->ADC_ISR, ADC_ANALOG_WD_FLAG)
#define _adc_chk_fifo_empty_status _reg_chk(ADC->ADC_ISR, ADC_FIFO_EMPTY_STATUS)
#define _adc_chk_fifo_full_status _reg_chk(ADC->ADC_ISR, ADC_FIFO_FULL_STATUS)
#define _adc_chk_over_run_flag _reg_chk(ADC->ADC_ISR, ADC_OVER_RUN_FLAG)
#define _adc_clr_over_run_flag _bit_set(ADC->ADC_ISR, ADC_OVER_RUN_FLAG)
#define _adc_chk_end_sequence_flag _reg_chk(ADC->ADC_ISR, ADC_END_SEQUENCE_FLAG)
#define _adc_clr_end_sequence_flag _bit_set(ADC->ADC_ISR, ADC_END_SEQUENCE_FLAG)
#define _adc_chk_end_conversion_flag _reg_chk(ADC->ADC_ISR, ADC_END_CONVERSION_FLAG)
#define _adc_clr_end_conversion_flag _bit_set(ADC->ADC_ISR, ADC_END_CONVERSION_FLAG)
#define _adc_chk_end_sampling_flag _reg_chk(ADC->ADC_ISR, ADC_END_SAMPLING_FLAG)
#define _adc_clr_end_sampling_flag _bit_set(ADC->ADC_ISR, ADC_END_SAMPLING_FLAG)
#define _adc_chk_ready_flag _reg_chk(ADC->ADC_ISR, ADC_READY_FLAG)
#define _adc_clr_ready_flag _bit_set(ADC->ADC_ISR, ADC_READY_FLAG)
#define _adc_clr_all_int_flag _bit_set(ADC->ADC_ISR, 0x9F)

// ADC_IER
#define _adc_set_analog_wd_int_en _bit_set(ADC->ADC_IER, ADC_ANALOG_WD_INT_EN)
#define _adc_set_analog_wd_int_dis _bit_clr(ADC->ADC_IER, ADC_ANALOG_WD_INT_EN)
#define _adc_set_over_run_int_en _bit_set(ADC->ADC_IER, ADC_OVER_RUN_INT_EN)
#define _adc_set_over_run_int_dis _bit_clr(ADC->ADC_IER, ADC_OVER_RUN_INT_EN)
#define _adc_set_end_sequence_int_en _bit_set(ADC->ADC_IER, ADC_END_SEQUENCE_INT_EN)
#define _adc_set_end_sequence_int_dis _bit_clr(ADC->ADC_IER, ADC_END_SEQUENCE_INT_EN)
#define _adc_set_end_conversion_int_en _bit_set(ADC->ADC_IER, ADC_END_CONVERSION_INT_EN)
#define _adc_set_end_conversion_int_dis _bit_clr(ADC->ADC_IER, ADC_END_CONVERSION_INT_EN)
#define _adc_set_end_sampling_int_en _bit_set(ADC->ADC_IER, ADC_END_SAMPLING_INT_EN)
#define _adc_set_end_sampling_int_dis _bit_clr(ADC->ADC_IER, ADC_END_SAMPLING_INT_EN)
#define _adc_set_ready_int_en _bit_set(ADC->ADC_IER, ADC_READY_INT_EN)
#define _adc_set_ready_int_dis _bit_clr(ADC->ADC_IER, ADC_READY_INT_EN)
#define _adc_set_int_en(index) _reg_modify(ADC->ADC_IER, 0xFFFFFF60, (index) & 0x9F)

// ADC_CR
#define _adc_set_stop_conversion_cmd _bit_set(ADC->ADC_CR, ADC_STOP_CONVERSION_CMD_EN)
#define _adc_chk_stop_conversion_cmd _reg_chk(ADC->ADC_CR, ADC_STOP_CONVERSION_CMD_EN)
#define _adc_set_start_conversion_cmd _bit_set(ADC->ADC_CR, ADC_START_CONVERSION_CMD_EN)
#define _adc_chk_start_conversion_cmd _reg_chk(ADC->ADC_CR, ADC_START_CONVERSION_CMD_EN)
#define _adc_set_disable_cmd _bit_set(ADC->ADC_CR, ADC_DISABLE_CMD_EN)
#define _adc_chk_disable_cmd _reg_chk(ADC->ADC_CR, ADC_DISABLE_CMD_EN)
#define _adc_set_enable_cmd _bit_set(ADC->ADC_CR, ADC_ENABLE_CMD_EN)
#define _adc_chk_enable_cmd _reg_chk(ADC->ADC_CR, ADC_ENABLE_CMD_EN)

#define _adc_chk_cr_disable _reg_read(ADC->ADC_CR)
#define _adc_set_cr(val) _reg_write(ADC->ADC_CR, val)

// ADC_CFGR1
#define _adc_set_analog_input_diff _bit_set(ADC->ADC_CFGR1, ADC_ANALOG_INPUT_DIFF_MASK)
#define _adc_set_analog_input_single _bit_clr(ADC->ADC_CFGR1, ADC_ANALOG_INPUT_DIFF_MASK)
#define _adc_set_overrun_mode_last _bit_set(ADC->ADC_CFGR1, ADC_OVERRUN_MODE_MASK)
#define _adc_set_overrun_mode_old _bit_clr(ADC->ADC_CFGR1, ADC_OVERRUN_MODE_MASK)
#define _adc_set_qadc_clk_disable_en _bit_set(ADC->ADC_CFGR1, ADC_QADC_CLK_DISABLE_MASK)
#define _adc_set_qadc_clk_disable_dis _bit_clr(ADC->ADC_CFGR1, ADC_QADC_CLK_DISABLE_MASK)
#define _adc_set_sample_output_buffer_en _bit_set(ADC->ADC_CFGR1, ADC_SAMPLE_OUTPUT_BUFFER_EN)
#define _adc_set_sample_output_buffer_dis _bit_clr(ADC->ADC_CFGR1, ADC_SAMPLE_OUTPUT_BUFFER_EN)
#define _adc_set_sequence_length(len) _reg_modify(ADC->ADC_CFGR1, 0xF8FFFFFF, ((len) & 0x7) << 24)
#define _adc_set_discontinuous_en _bit_set(ADC->ADC_CFGR1, ADC_DISCONTINUOUS_EN)
#define _adc_set_discontinuous_dis _bit_clr(ADC->ADC_CFGR1, ADC_DISCONTINUOUS_EN)
#define _adc_set_auto_off_mode_en _bit_set(ADC->ADC_CFGR1, ADC_AUTO_OFF_MODE_EN)
#define _adc_set_auto_off_mode_dis _bit_clr(ADC->ADC_CFGR1, ADC_AUTO_OFF_MODE_EN)
#define _adc_set_wait_conversion_mode_on _bit_set(ADC->ADC_CFGR1, ADC_WAIT_CONVERSION_MODE_MASK)
#define _adc_set_wait_conversion_mode_off _bit_clr(ADC->ADC_CFGR1, ADC_WAIT_CONVERSION_MODE_MASK)
#define _adc_set_continuous_conversion _bit_set(ADC->ADC_CFGR1, ADC_CONTINUOUS_CONVERSION_MASK)
#define _adc_set_single_conversion _bit_clr(ADC->ADC_CFGR1, ADC_CONTINUOUS_CONVERSION_MASK)
#define _adc_sel_external_vref _bit_set(ADC->ADC_CFGR1, ADC_EXTERNAL_VREF_MASK)
#define _adc_sel_internal_vref _bit_clr(ADC->ADC_CFGR1, ADC_EXTERNAL_VREF_MASK)
#define _adc_set_trig_mode(val) _reg_modify(ADC->ADC_CFGR1, 0xFFFFC7FF, ((val) & 0x7) << 11)
#define _adc_set_data_left_alignment _bit_set(ADC->ADC_CFGR1, ADC_LEFT_ALIGNMENT_MASK)
#define _adc_set_data_right_alignment _bit_clr(ADC->ADC_CFGR1, ADC_LEFT_ALIGNMENT_MASK)
#define _adc_set_data_resolution(val) _reg_modify(ADC->ADC_CFGR1, 0xFFFFFCFF, ((val) & 0x3) << 8)
#define _adc_set_dma_access_threshlod(val) _reg_modify(ADC->ADC_CFGR1, 0xFFFFFF8F, ((val) & 0x7) << 4)
#define _adc_set_dma_access_en _bit_set(ADC->ADC_CFGR1, ADC_DMA_ACCESS_EN)
#define _adc_set_dma_access_dis _bit_clr(ADC->ADC_CFGR1, ADC_DMA_ACCESS_EN)
#define _adc_set_cfgr1(val) _reg_write(ADC->ADC_CFGR1, val)

// ADC_CFGR2
#define _adc_set_analog_input_bypass_en _bit_set(ADC->ADC_CFGR2, ADC_ANALOG_INPUT_BYPASS_EN)
#define _adc_set_analog_input_bypass_dis _bit_clr(ADC->ADC_CFGR2, ADC_ANALOG_INPUT_BYPASS_EN)
#define _adc_set_prescaler_clk_div(div) _reg_modify(ADC->ADC_CFGR2, 0xFFFFF0FF, ((div) & 0x0F) << 8)
#define _adc_set_startup_counter(cnt) _reg_modify(ADC->ADC_CFGR2, 0xFFFFFF00, (cnt) & 0xFF)
#define _adc_set_cfgr2(val) _reg_write(ADC->ADC_CFGR2, val)

// ADC_SMPR
#define _adc_set_sampling_time(val) _reg_modify(ADC->ADC_SMPR, 0xFFFFFF00, (val) & 0xFF)
#define _adc_set_smpr(val) _reg_write(ADC->ADC_SMPR, val)
#define _adc_sel_analog_channel_index(index) _reg_modify(ADC->ADC_SMPR, 0xFFFFFFE0, (index) & 0x1F)

// ADC_WDG
#define _adc_set_analog_watchdog_en _bit_set(ADC->ADC_WDG, ADC_ANALOG_WATCHDOG_EN)
#define _adc_set_analog_watchdog_dis _bit_clr(ADC->ADC_WDG, ADC_ANALOG_WATCHDOG_EN)
#define _adc_set_wd_single_channel _bit_set(ADC->ADC_WDG, ADC_WATCHDOG_CHANNEL_MASK)
#define _adc_set_wd_all_channel _bit_clr(ADC->ADC_WDG, ADC_WATCHDOG_CHANNEL_MASK)

// ADC_TR
#define _adc_clr_note_for_ht _bit_clr(ADC->ADC_TR, ADC_NOTE_FOR_HT_MASK)
#define _adc_set_wd_higher_threshold_val(val) _reg_modify(ADC->ADC_TR, 0xF000FFFF, ((val) & 0xFFF) << 16)
#define _adc_clr_note_for_lt _bit_clr(ADC->ADC_TR, ADC_NOTE_FOR_LT_MASK)
#define _adc_set_wd_lower_threshold_val(val) _reg_modify(ADC->ADC_TR, 0xFFFFF000, (val) & 0xFFF)

// ADC_CHSELR1
#define _adc_set_number0_channel_name(index) _reg_modify(ADC->ADC_CHSELR1, 0xFFFFFFE0, (index) & 0x1F)
#define _adc_set_number1_channel_name(index) _reg_modify(ADC->ADC_CHSELR1, 0xFFFFE0FF, ((index) & 0x1F) << 8)
#define _adc_set_number2_channel_name(index) _reg_modify(ADC->ADC_CHSELR1, 0xFFE0FFFF, ((index) & 0x1F) << 16)
#define _adc_set_number3_channel_name(index) _reg_modify(ADC->ADC_CHSELR1, 0xE0FFFFFF, ((index) & 0x1F) << 24)
#define _adc_set_chselr1(val) _reg_write(ADC->ADC_CHSELR1, val)

// ADC_CHSELR2
#define _adc_set_number4_channel_name(index) _reg_modify(ADC->ADC_CHSELR2, 0xFFFFFFE0, (index) & 0x1F)
#define _adc_set_number5_channel_name(index) _reg_modify(ADC->ADC_CHSELR2, 0xFFFFE0FF, ((index) & 0x1F) << 8)
#define _adc_set_number6_channel_name(index) _reg_modify(ADC->ADC_CHSELR2, 0xFFE0FFFF, ((index) & 0x1F) << 16)
#define _adc_set_number7_channel_name(index) _reg_modify(ADC->ADC_CHSELR2, 0xE0FFFFFF, ((index) & 0x1F) << 24)
#define _adc_set_chselr2(val) _reg_write(ADC->ADC_CHSELR2, val)

// ADC_FIFOR
#define _adc_get_convert_data _bit_get(ADC->ADC_FIFOR, 0xFFFF)

// ADC_ISR2
#define _adc_chk_fifo_timeout_flag _reg_chk(ADC->ADC_ISR2, ADC_FIFO_TIMEOUT_FLAG)
#define _adc_clr_fifo_timeout_flag _bit_set(ADC->ADC_ISR2, ADC_FIFO_TIMEOUT_FLAG)
#define _adc_chk_data_buffer_timeout_flag _reg_chk(ADC->ADC_ISR2, ADC_DATA_BUFFER_TIMEOUT_FLAG)
#define _adc_clr_data_buffer_timeout_flag _bit_set(ADC->ADC_ISR2, ADC_DATA_BUFFER_TIMEOUT_FLAG)
#define _adc_chk_data_buffer_ready_flag _reg_chk(ADC->ADC_ISR2, ADC_DATA_BUFFER_READY_FLAG)
#define _adc_clr_data_buffer_ready_flag _bit_set(ADC->ADC_ISR2, ADC_DATA_BUFFER_READY_FLAG)
#define _adc_get_fifo_counter _bit_get(ADC->ADC_ISR2, 0x0F000000)
#define _adc_get_wd_error_channel _bit_get(ADC->ADC_ISR2, 0x000F0000)
#define _adc_get_data_gather_read_cnt _bit_get(ADC->ADC_ISR2, 0x00000F00)
#define _adc_get_data_gather_write_cnt _bit_get(ADC->ADC_ISR2, 0x000000F0)

// ADC_DGATR
#define _adc_set_data_buffer_timeout_val(val) _reg_modify(ADC->ADC_DGATR, 0x0000FFFF, ((val) & 0xFFFF) << 16)
#define _adc_set_data_gather_read_threshold_val(val) _reg_modify(ADC->ADC_DGATR, 0xFFFFF0FF, ((val) & 0xF) << 8)
#define _adc_set_data_gather_write_threshold_val(val) _reg_modify(ADC->ADC_DGATR, 0xFFFFFF0F, ((val) & 0xF) << 4)
#define _adc_set_data_gather_read_size(val) _reg_modify(ADC->ADC_DGATR, 0xFFFFFFF3, ((val) & 0x3) << 2)
#define _adc_set_data_buffer_timeout_int_en _bit_set(ADC->ADC_DGATR, ADC_DATA_BUFFER_TIMEOUT_INT_EN)
#define _adc_set_data_buffer_timeout_int_dis _bit_clr(ADC->ADC_DGATR, ADC_DATA_BUFFER_TIMEOUT_INT_EN)
#define _adc_set_data_buffer_timeout_en _bit_set(ADC->ADC_DGATR, ADC_DATA_BUFFER_TIMEOUT_EN)
#define _adc_set_data_buffer_timeout_dis _bit_clr(ADC->ADC_DGATR, ADC_DATA_BUFFER_TIMEOUT_EN)
#define _adc_set_data_buffer_ready_int_en _bit_set(ADC->ADC_DGATR, ADC_DATA_BUFFER_READY_INT_EN)
#define _adc_set_data_buffer_ready_int_dis _bit_clr(ADC->ADC_DGATR, ADC_DATA_BUFFER_READY_INT_EN)
#define _adc_set_data_gather_function_en _bit_set(ADC->ADC_DGATR, ADC_DATA_GATHER_FUNCTION_EN)
#define _adc_set_data_gather_function_dis _bit_clr(ADC->ADC_DGATR, ADC_DATA_GATHER_FUNCTION_EN)

// ADC_DBUFR
#define _adc_get_data_buffer_value _reg_read(ADC->ADC_DBUFR)

// ADC_FIFOTOR
#define _adc_set_fifo_timeout_val(val) _reg_modify(ADC->ADC_FIFOTOR, 0x0000FFFF, ((val) & 0xFFFF) << 16)
#define _adc_set_fifo_timeout_int_en _bit_set(ADC->ADC_FIFOTOR, ADC_FIFO_TIMEOUT_INT_EN)
#define _adc_set_fifo_timeout_int_dis _bit_clr(ADC->ADC_FIFOTOR, ADC_FIFO_TIMEOUT_INT_EN)
#define _adc_set_fifo_timeout_en _bit_set(ADC->ADC_FIFOTOR, ADC_FIFO_TIMEOUT_EN)
#define _adc_set_fifo_timeout_dis _bit_clr(ADC->ADC_FIFOTOR, ADC_FIFO_TIMEOUT_EN)

// ADC_DFT3
#define _adc_get_channel6_value _bit_get(ADC->DET3.CHANEL6, 0xFFF)
#define _adc_get_channel7_value _bit_get(ADC->DET4.CHANEL7, 0xFFF)

// ADC_DFT2
#define _adc_get_channel4_value _bit_get(ADC->DET2.CHANEL4, 0xFFF)
#define _adc_get_channel5_value _bit_get(ADC->DET2.CHANEL5, 0xFFF)

// ADC_DFT1
#define _adc_get_channel2_value _bit_get(ADC->DET1.CHANEL2, 0xFFF)
#define _adc_get_channel3_value _bit_get(ADC->DET1.CHANEL3, 0xFFF)

// ADC_DFT0
#define _adc_get_channel0_value _bit_get(ADC->DET0.CHANEL0, 0xFFF)
#define _adc_get_channel1_value _bit_get(ADC->DET0.CHANEL1, 0xFFF)

// ADC_DFT7
#define _adc_get_channel14_value _bit_get(ADC->DET7.CHANEL14, 0xFFF)
#define _adc_get_channel15_value _bit_get(ADC->DET7.CHANEL15, 0xFFF)

// ADC_DFT6
#define _adc_get_channel12_value _bit_get(ADC->DET6.CHANEL12, 0xFFF)
#define _adc_get_channel13_value _bit_get(ADC->DET6.CHANEL13, 0xFFF)

// ADC_DFT5
#define _adc_get_channel10_value _bit_get(ADC->DET5.CHANEL10, 0xFFF)
#define _adc_get_channel11_value _bit_get(ADC->DET5.CHANEL11, 0xFFF)

// ADC_DFT4
#define _adc_get_channel8_value _bit_get(ADC->DET4.CHANEL8, 0xFFF)
#define _adc_get_channel9_value _bit_get(ADC->DET4.CHANEL9, 0xFFF)

// ADC_DFT8
#define _adc_get_channel16_value _bit_get(ADC->DET8.CHANEL16, 0xFFF)

// ADC_CHSELR3
#define _adc_set_channel_sel_value(val) _bit_set(ADC->ADC_CHSELR3, val)
#define _adc_clr_channel_sel_value(val) _bit_clr(ADC->ADC_CHSELR3, val)
// ADC_TRIGSEL
#define _adc_set_trigger_source_sel_value(val) _reg_write(ADC->ADC_TRIGSEL, (val) & 0xFFFFFFFF)

/**
 * @brief  ADC通道号定义
 *
 */
#define ADC_IN1 ((uint32_t)1)
#define ADC_IN2 ((uint32_t)2)
#define ADC_IN3 ((uint32_t)3)
#define ADC_IN4 ((uint32_t)4)
#define ADC_IN5 ((uint32_t)5)
#define ADC_IN6 ((uint32_t)6)
#define ADC_IN7 ((uint32_t)7)
#define ADC_IN8 ((uint32_t)8)
#define ADC_IN9 ((uint32_t)9)
#define ADC_IN10 ((uint32_t)10)
#define ADC_IN11 ((uint32_t)11)
#define ADC_IN12 ((uint32_t)12)
#define ADC_IN13 ((uint32_t)13)
#define ADC_IN14 ((uint32_t)14)
#define ADC_IN15 ((uint32_t)15)

/**
 * @brief ADC 模块初始化结构体定义
 * 
 */
typedef struct
{
    uint8_t channel;    /*< ADC通道，参考ADC_ChannelTypeDef定义 */
    uint8_t resolution; /*< ADC分辨率设置，参考ADC_ResTypeDef定义 */
    uint8_t clk_div;    /*< ADC时钟分频 - QCLK = SYS_CLK/clk_div */
    uint8_t stab_time;  /*< ADC稳定时间，单位为2us - 2*(10^-6)*(1/QCLK) */
    uint8_t smp_time;   /*< ADC采样时间 - (smp_time + 2)*QCLKs */
    uint8_t vref;           /*< ADC参考电压选择，参考ADC_VrefTypeDef定义 */
    uint8_t align;          /*< ADC数据对齐方式，参考ADC_AlignTypeDef定义 */
    uint8_t conv;           /*< ADC转换模式，参考ADC_ConvModeTypeDef定义 */
    uint8_t overrun;        /*< ADC溢出管理，参考ADC_OverrunManagTypeDef定义 */
    uint8_t int_kind;       /*< ADC中断类型使能 */
    uint8_t trigger_source; /*< ADC触发源选择 */
    uint8_t trigger_mode;   /*< ADC触发模式选择，0：禁用触发 */
} adc_init_t;

/**
 * @brief ADC 模块采样精度枚举定义
 * 
 */
typedef enum
{
    ADC_RESOLUTION_12BIT = 0,
    ADC_RESOLUTION_10BIT = 1,
    ADC_RESOLUTION_8BIT = 2,
    ADC_RESOLUTION_6BIT = 3
} adc_resolution_t;

/**
 * @brief ADC 模块采集数据对齐方式枚举定义
 * 
 */
typedef enum
{
    ADC_RIGHT_ALIGN = 0x00,
    ADC_LEFT_ALIGN = 0x01
} adc_alignment_t;

/**
 * @brief ADC 模块基准电压源选择枚举定义
 * 
 */
typedef enum
{
    ADC_SINGLE_CONV_MODE = 0x00,
    ADC_CONTINUOUS_CONV_MODE = 0x01
} adc_conversionmode_t;

/**
 * @brief ADC 模块转换模式选择枚举定义
 * 
 */
typedef enum
{
    ADC_INTERNAL_VREF = 0x00,
    ADC_EXTERNAL_VREF = 0x01
} adc_verfence_t;

/**
 * @brief ADC 模块转换溢出处理模式选择枚举定义
 * 
 */
typedef enum
{
    ADC_OVERRUN_MODE_OLD = 0x00,
    ADC_OVERRUN_MODE_LAST = 0x01
} adc_overrunmanagement_t;

// 函数声明
void drv_adc_module_enable(void);
void drv_adc_module_disable(void);
void drv_adc_conversion_start(void);
void drv_adc_conversion_stop(void);
void drv_adc_channel_select(uint32_t channel);
void drv_adc_channel_disselect(uint32_t channel);
void drv_adc_irq_handler(void);
void drv_adc_trigger_select(uint8_t source);
void drv_adc_trigger_mode(uint8_t trigger_mode);
void drv_adc_init(adc_init_t *adc);
void drv_adc_irqinit(uint8_t value);
uint16_t drv_adc_get_data(void);
void drv_adc_clr_endflag(void);
uint32_t drv_adc_check_endflag();

#ifdef __cplusplus
}
#endif

#endif
