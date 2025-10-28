/**
 * @file pwmt_drv.c
 * @author Product Application Department
 * @brief  PWMT 模块驱动层
 * @version V1.0
 * @date 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "pwmt_drv.h"

// 函数定义

/**
 * @brief PMWT1 模块引脚复用使能函数
 *
 * @param ch 引脚通道定义
 */
void drv_pwmt1_swapenable(uint8_t ch)
{
    switch (ch)
    {
    case PWMT_0:
        _pwmt1_ch0_enable;
        break;
    case PWMT_0_N:
        _pwmt1_ch0n_enable;
        break;
    case PWMT_1:
        _pwmt1_ch1_enable;
        break;
    case PWMT_1_N:
        _pwmt1_ch1n_enable;
        break;
    case PWMT_2:
        _pwmt1_ch2_enable;
        break;
    case PWMT_2_N:
        _pwmt1_ch2n_enable;
        break;
    case PWMT_3:
        _pwmt1_ch3_enable;
        break;
    case PWMT_3_N:
        _pwmt1_ch3n_enable;
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT2 模块引脚复用使能函数
 *
 * @param ch 引脚通道定义
 */
void drv_pwmt2_swapenable(uint8_t ch)
{
    switch (ch)
    {
    case PWMT_0:
        _pwmt2_ch0_enable;
        break;
    case PWMT_0_N:
        _pwmt2_ch0n_enable;
        break;
    case PWMT_1:
        _pwmt2_ch1_enable;
        break;
    case PWMT_1_N:
        _pwmt2_ch1n_enable;
        break;
    case PWMT_2:
        _pwmt2_ch2_enable;
        break;
    case PWMT_2_N:
        _pwmt2_ch2n_enable;
        break;
    case PWMT_3:
        _pwmt2_ch3_enable;
        break;
    case PWMT_3_N:
        _pwmt2_ch3n_enable;
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT3 模块引脚复用使能函数
 *
 * @param ch 引脚通道定义
 */
void drv_pwmt3_swapenable(uint8_t ch)
{
    switch (ch)
    {
    case PWMT_0:
        _pwmt3_ch0_enable;
        break;
    case PWMT_0_N:
        _pwmt3_ch0n_enable;
        break;
    case PWMT_1:
        _pwmt3_ch1_enable;
        break;
    case PWMT_1_N:
        _pwmt3_ch1n_enable;
        break;
    case PWMT_2:
        _pwmt3_ch2_enable;
        break;
    case PWMT_2_N:
        _pwmt3_ch2n_enable;
        break;
    case PWMT_3:
        _pwmt3_ch3_enable;
        break;
    case PWMT_3_N:
        _pwmt3_ch3n_enable;
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块计数使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param status 功能状态定义
 */
void drv_pwmt_counterenable(reg_pwmt_t *ppwmt, functionalstate_t status)
{
    if (status == ENABLE)
    {
        _pwmt_cr1_counter_en(ppwmt);
    }
    else
    {
        _pwmt_cr1_counter_dis(ppwmt);
    }
}

/**
 * @brief PWMT 模块捕获比较1选择函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口号定义
 */
void drv_pwmt_capturecompare1selection(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    pwmt_dir_channel_t dir;

    switch (dir)
    {
    case CC1_CHANNEL_OUTPUT:
        break;
    case CC1_CHANNEL_INPUT_IC1_MAP_TI1:
        break;
    case CC1_CHANNEL_INPUT_IC1_MAP_TI2:
        break;
    case CC1_CHANNEL_INPUT_IC1_MAP_TRC:
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块通道0输出比较模式函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param mode 模式定义
 */
void drv_pwmt_ch0outputcomparemode(reg_pwmt_t *ppwmt, pwmt_outcmp_mode_t mode)
{
    switch (mode)
    {
    case FROZEN:
        break;
    case CH1_ACTIVE_LEVEL_MATCH:
        break;
    case CH1_INACTIVE_LEVEL_MATCH:
        break;
    case TOGGLE:
        _pwmt_ccmr1_ch0_oc1ref_toggle(ppwmt);
        break;
    case OC1REF_FORCE_LOW:
        break;
    case OC1REF_FORCE_HIGH:
        break;
    case PWM_MODE1:
        _pwmt_ccmr1_ch0_pwm_mode1_high_level_valid(ppwmt);
        break;
    case PWM_MODE2:
        _pwmt_ccmr1_ch0_pwm_mode2_low_level_valid(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块通道1输出比较模式函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param mode 模式定义
 */
void drv_pwmt_ch1outputcomparemode(reg_pwmt_t *ppwmt, pwmt_outcmp_mode_t mode)
{
    switch (mode)
    {
    case FROZEN:
        break;
    case CH1_ACTIVE_LEVEL_MATCH:
        break;
    case CH1_INACTIVE_LEVEL_MATCH:
        break;
    case TOGGLE:
        _pwmt_ccmr1_ch1_oc2ref_toggle(ppwmt);
        break;
    case OC1REF_FORCE_LOW:
        break;
    case OC1REF_FORCE_HIGH:
        break;
    case PWM_MODE1:
        _pwmt_ccmr1_ch1_pwm_mode1_high_level_valid(ppwmt);
        break;
    case PWM_MODE2:
        _pwmt_ccmr1_ch1_pwm_mode2_low_level_valid(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块通道2输出比较模式函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param mode 模式定义
 */
void drv_pwmt_ch2outputcomparemode(reg_pwmt_t *ppwmt, pwmt_outcmp_mode_t mode)
{
    switch (mode)
    {
    case FROZEN:
        break;
    case CH1_ACTIVE_LEVEL_MATCH:
        break;
    case CH1_INACTIVE_LEVEL_MATCH:
        break;
    case TOGGLE:
        _pwmt_ccmr2_ch2_oc3ref_toggle(ppwmt);
        break;
    case OC1REF_FORCE_LOW:
        break;
    case OC1REF_FORCE_HIGH:
        break;
    case PWM_MODE1:
        _pwmt_ccmr2_ch2_pwm_mode1_high_level_valid(ppwmt);
        break;
    case PWM_MODE2:
        _pwmt_ccmr2_ch2_pwm_mode2_low_level_valid(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块通道3输出比较模式函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param mode 模式定义
 */
void drv_pwmt_ch3outputcomparemode(reg_pwmt_t *ppwmt, pwmt_outcmp_mode_t mode)
{
    switch (mode)
    {
    case FROZEN:
        break;
    case CH1_ACTIVE_LEVEL_MATCH:
        break;
    case CH1_INACTIVE_LEVEL_MATCH:
        break;
    case TOGGLE:
        _pwmt_ccmr2_ch3_oc4ref_toggle(ppwmt);
        break;
    case OC1REF_FORCE_LOW:
        break;
    case OC1REF_FORCE_HIGH:
        break;
    case PWM_MODE1:
        _pwmt_ccmr2_ch3_pwm_mode1_high_level_valid(ppwmt);
        break;
    case PWM_MODE2:
        _pwmt_ccmr2_ch3_pwm_mode2_low_level_valid(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块输出比较模式函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param mode 模式定义
 */
void drv_pwmt_outputcomparemode(reg_pwmt_t *ppwmt, uint8_t portnum, pwmt_outcmp_mode_t mode)
{
    switch (portnum)
    {
    case 0:
        drv_pwmt_ch0outputcomparemode(ppwmt, mode);
        break;
    case 1:
        drv_pwmt_ch1outputcomparemode(ppwmt, mode);
        break;
    case 2:
        drv_pwmt_ch2outputcomparemode(ppwmt, mode);
        break;
    case 3:
        drv_pwmt_ch3outputcomparemode(ppwmt, mode);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块输出比较预装载使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 */
void drv_pwmt_outputcomparepreloadenable(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    switch (portnum)
    {
    case 0:
        _pwmt_ccmr1_ch0_output_compare_preload_en(ppwmt);
        break;
    case 1:
        _pwmt_ccmr1_ch1_output_compare_preload_en(ppwmt);
        break;
    case 2:
        _pwmt_ccmr2_ch2_output_compare_preload_en(ppwmt);
        break;
    case 3:
        _pwmt_ccmr2_ch3_output_compare_preload_en(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块通道输出函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 */
void drv_pwmt_channeloutput(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    switch (portnum)
    {
    case 0:
        _pwmt_ccmr1_ch0_cfg_output(ppwmt);
        break;
    case 1:
        _pwmt_ccmr1_ch1_cfg_output(ppwmt);
        break;
    case 2:
        _pwmt_ccmr2_ch2_cfg_output(ppwmt);
        break;
    case 3:
        _pwmt_ccmr2_ch3_cfg_output(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PWMT 模块捕获比较输出优先级函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param high 比特动作定义
 */
void drv_pwmt_capturecompareoutputpolarity(reg_pwmt_t *ppwmt, uint8_t portnum, BitActionTypeDef high)
{
    if (high == BIT_SET)
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_ch0_high_level_valid(ppwmt);
            break;
        case 1:
            _pwmt_ccer_ch1_high_level_valid(ppwmt);
            break;
        case 2:
            _pwmt_ccer_ch2_high_level_valid(ppwmt);
            break;
        case 3:
            _pwmt_ccer_ch3_high_level_valid(ppwmt);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_ch0_low_level_valid(ppwmt);
            break;
        case 1:
            _pwmt_ccer_ch1_low_level_valid(ppwmt);
            break;
        case 2:
            _pwmt_ccer_ch2_low_level_valid(ppwmt);
            break;
        case 3:
            _pwmt_ccer_ch3_low_level_valid(ppwmt);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief PWMT 模块通道输出使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param en 功能状态定义
 */
void drv_pwmt_channeloutputenable(reg_pwmt_t *ppwmt, uint8_t portnum, functionalstate_t en)
{
    if (en == ENABLE)
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_ch0_output_en(ppwmt);
            _pwmt_ccer_ch0n_output_en(ppwmt);
            break;
        case 1:
            _pwmt_ccer_ch1_output_en(ppwmt);
            _pwmt_ccer_ch1n_output_en(ppwmt);
            break;
        case 2:
            _pwmt_ccer_ch2_output_en(ppwmt);
            _pwmt_ccer_ch2n_output_en(ppwmt);
            break;
        case 3:
            _pwmt_ccer_ch3_output_en(ppwmt);
            _pwmt_ccer_ch3n_output_en(ppwmt);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_ch0_output_dis(ppwmt);
            break;
        case 1:
            _pwmt_ccer_ch1_output_dis(ppwmt);
            break;
        case 2:
            _pwmt_ccer_ch2_output_dis(ppwmt);
            break;
        case 3:
            _pwmt_ccer_ch3_output_dis(ppwmt);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief PMWT 模块捕获比较预装载值函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param width 预装载值定义
 */
void drv_pwmt_setdutyfactor(reg_pwmt_t *ppwmt, uint8_t portnum, uint16_t width)
{
    switch (portnum)
    {
    case 0:
        _pwmt_ccr1_ch0_dutyfactor(ppwmt, width);
        break;
    case 1:
        _pwmt_ccr2_ch1_dutyfactor(ppwmt, width);
        break;
    case 2:
        _pwmt_ccr3_ch2_dutyfactor(ppwmt, width);
        break;
    case 3:
        _pwmt_ccr4_ch3_dutyfactor(ppwmt, width);
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT 模块设置死区函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param deadzone 死区值定义
 */
void drv_pwmt_setdeadzone(reg_pwmt_t *ppwmt, uint8_t portnum, uint16_t deadzone)
{
    switch (portnum)
    {
    case 0:
    {
        _pwmt_ccer_ch0_deadzone_polarity(ppwmt);
        _pwmt_ccer_ch0_deadzone_en(ppwmt);
    }
    break;

    case 1:
    {
        _pwmt_ccer_ch1_deadzone_polarity(ppwmt);
        _pwmt_ccer_ch1_deadzone_en(ppwmt);
    }
    break;

    case 2:
    {
        _pwmt_ccer_ch2_deadzone_polarity(ppwmt);
        _pwmt_ccer_ch2_deadzone_en(ppwmt);
    }
    break;

    case 3:
    {
        _pwmt_ccer_ch3_deadzone_polarity(ppwmt);
        _pwmt_ccer_ch3_deadzone_en(ppwmt);
    }
    break;

    default:
        break;
    }

    _pwmt_bdtr_deadzone_time(ppwmt, deadzone);
}

/**
 * @brief PMWT 模块设置预分频函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param pre 预分频定义
 */
void drv_pwmt_setprescaler(reg_pwmt_t *ppwmt, uint16_t pre)
{
    _pwmt_psc_prescaler_value(ppwmt, pre);
}

/**
 * @brief PMWT 模块设置周期函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param period 周期值定义
 */
void drv_pwmt_setperiod(reg_pwmt_t *ppwmt, uint16_t period)
{
    _pwmt_arr_auto_reload_value(ppwmt, period);
}

/**
 * @brief PMWT 模块设置计数方向函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param dir 方向定义
 */
void drv_pwmt_setcounterdir(reg_pwmt_t *ppwmt, pwmt_count_dir_t dir)
{
    if (dir == UP_COUNTER)
    {
        _pwmt_cr1_counter_increase(ppwmt);
    }
    else
    {
        _pwmt_cr1_counter_decrease(ppwmt);
    }
}

/**
 * @brief PMWT 模块设置对齐函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param mode 对齐模式定义函数
 */
void drv_pwmt_centeralignmode(reg_pwmt_t *ppwmt, pwmt_center_alignmode_t mode)
{
    switch (mode)
    {
    case EDGE_ALIGN:
        _pwmt_cr1_edge_aligned_mode(ppwmt);
        break;
    case CENTER_ALIGN_MODE1:
        _pwmt_cr1_center_aligned_mode1(ppwmt);
        break;
    case CENTER_ALIGN_MODE2:
        _pwmt_cr1_center_aligned_mode2(ppwmt);
        break;
    case CENTER_ALIGN_MODE3:
        _pwmt_cr1_center_aligned_mode3(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT 模块更新事件函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_updtgeneration(reg_pwmt_t *ppwmt)
{
    _pwmt_egr_update_generation(ppwmt);
}

/**
 * @brief PMWT 模块自动重载使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_autoreloaden(reg_pwmt_t *ppwmt)
{
    _pwmt_cr1_auto_reload_preload_en(ppwmt);
}

/**
 * @brief PMWT 模块主要输出使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_mainoutputen(reg_pwmt_t *ppwmt)
{
    _pwmt_bdtr_main_output_en(ppwmt);
}

/**
 * @brief PMWT 模块通道上拉使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param ch 通道定义
 * @param status 功能状态定义
 */
void drv_pwmt_pullenable(reg_pwmt_t *ppwmt, uint8_t ch, functionalstate_t status)
{
    if (status == ENABLE)
    {
        _pwmt_ch_pull_en(ppwmt, (ch & 0x3));
    }
    else
    {
        _pwmt_ch_pull_dis(ppwmt, (ch & 0x3));
    }
}

/**
 * @brief PMWT 模块通道输入配置函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 */
void drv_pwmt_channelinput(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    switch (portnum)
    {
    case 0:
        _pwmt_ccmr1_ch0_cfg_input_map_ti1(ppwmt);
        //_pwmt_ccmr1_ch0_cfg_input_map_ti2(ppwmt);
        //_pwmt_ccmr1_ch0_cfg_input_map_trc(ppwmt);
        break;
    case 1:
        //_pwmt_ccmr1_ch1_cfg_input_map_ti1(ppwmt);
        _pwmt_ccmr1_ch1_cfg_input_map_ti2(ppwmt);
        //_pwmt_ccmr1_ch1_cfg_input_map_trc(ppwmt);
        break;
    case 2:
        _pwmt_ccmr2_ch2_cfg_input_map_ti3(ppwmt);
        //_pwmt_ccmr2_ch2_cfg_input_map_ti4(ppwmt);
        //_pwmt_ccmr2_ch2_cfg_input_map_trc(ppwmt);
        break;
    case 3:
        //_pwmt_ccmr2_ch3_cfg_input_map_ti3(ppwmt);
        _pwmt_ccmr2_ch3_cfg_input_map_ti4(ppwmt);
        //_pwmt_ccmr2_ch3_cfg_input_map_trc(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT 模块通道捕获使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param en 功能状态定义
 */
void drv_pwmt_channelcaptureenable(reg_pwmt_t *ppwmt, uint8_t portnum, functionalstate_t en)
{
    if (en == ENABLE)
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_ch0_capture_en(ppwmt);
            break;
        case 1:
            _pwmt_ccer_ch1_capture_en(ppwmt);
            break;
        case 2:
            _pwmt_ccer_ch2_capture_en(ppwmt);
            break;
        case 3:
            _pwmt_ccer_ch3_capture_en(ppwmt);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_ch0_capture_dis(ppwmt);
            break;
        case 1:
            _pwmt_ccer_ch1_capture_dis(ppwmt);
            break;
        case 2:
            _pwmt_ccer_ch2_capture_dis(ppwmt);
            break;
        case 3:
            _pwmt_ccer_ch3_capture_dis(ppwmt);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief PWMT 模块更新DMA请求使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_updatedmarequestenable(reg_pwmt_t *ppwmt)
{
    _pwmt_dier_update_dma_request_en(ppwmt);
}

/**
 * @brief PWMT 模块捕获比较1 DMA请求使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_cc1dmarequestenable(reg_pwmt_t *ppwmt)
{
    _pwmt_dier_cc1_dma_request_en(ppwmt);
}

/**
 * @brief PWMT 模块捕获比较2 DMA请求使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_cc2dmarequestenable(reg_pwmt_t *ppwmt)
{
    _pwmt_dier_cc2_dma_request_en(ppwmt);
}

/**
 * @brief PWMT 模块捕获比较3 DMA请求使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_cc3dmarequestenable(reg_pwmt_t *ppwmt)
{
    _pwmt_dier_cc3_dma_request_en(ppwmt);
}

/**
 * @brief PWMT 模块捕获比较4 DMA请求使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_cc4dmarequestenable(reg_pwmt_t *ppwmt)
{
    _pwmt_dier_cc4_dma_request_en(ppwmt);
}

/**
 * @brief PMWT 模块设置触发方式函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @param way 触发方式定义
 */
void drv_pwmt_settriggerway(reg_pwmt_t *ppwmt, uint8_t portnum, pwmt_triggerway_t way)
{
    if (way == RISING_EDGE)
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_cc1p_low(ppwmt);
            _pwmt_ccer_cc1np_low(ppwmt);
            break;
        case 1:
            _pwmt_ccer_cc2p_low(ppwmt);
            _pwmt_ccer_cc2np_low(ppwmt);
            break;
        case 2:
            _pwmt_ccer_cc3p_low(ppwmt);
            _pwmt_ccer_cc3np_low(ppwmt);
            break;
        case 3:
            _pwmt_ccer_cc4p_low(ppwmt);
            _pwmt_ccer_cc4np_low(ppwmt);
            break;
        default:
            break;
        }
    }
    else if (way == FALLING_EDGE)
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_cc1p_high(ppwmt);
            _pwmt_ccer_cc1np_low(ppwmt);
            break;
        case 1:
            _pwmt_ccer_cc2p_high(ppwmt);
            _pwmt_ccer_cc2np_low(ppwmt);
            break;
        case 2:
            _pwmt_ccer_cc3p_high(ppwmt);
            _pwmt_ccer_cc3np_low(ppwmt);
            break;
        case 3:
            _pwmt_ccer_cc4p_high(ppwmt);
            _pwmt_ccer_cc4np_low(ppwmt);
            break;
        default:
            break;
        }
    }
    else if (way == BOTH_EDGE)
    {
        switch (portnum)
        {
        case 0:
            _pwmt_ccer_cc1p_high(ppwmt);
            _pwmt_ccer_cc1np_high(ppwmt);
            break;
        case 1:
            _pwmt_ccer_cc2p_high(ppwmt);
            _pwmt_ccer_cc2np_high(ppwmt);
            break;
        case 2:
            _pwmt_ccer_cc3p_high(ppwmt);
            _pwmt_ccer_cc3np_high(ppwmt);
            break;
        case 3:
            _pwmt_ccer_cc4p_high(ppwmt);
            _pwmt_ccer_cc4np_high(ppwmt);
            break;
        default:
            break;
        }
    }
    else
    {
        ;
    }
}

/**
 * @brief PMWT 模块中断使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param int_type 中断类型定义
 */
void drv_pwmt_interruptenable(reg_pwmt_t *ppwmt, pwmt_int_t int_type)
{
    if (int_type != ALL_PWMT_INT_DIS)
    {
        //        capintflag = 0;

        if (ppwmt == PWMT1)
        {
            NVIC_Init(3, 3, PWMT1_IRQn, 2);
        }
        else if (ppwmt == PWMT2)
        {
            NVIC_Init(3, 3, PWMT2_IRQn, 2);
        }
        else
        {
            NVIC_Init(3, 3, PWMT3_IRQn, 2);
        }

        _pwmt_dier_interrupt_en(ppwmt, int_type);
    }
    else
    {
        NVIC_Clear(PWMT1_IRQn);
        NVIC_Clear(PWMT2_IRQn);
        NVIC_Clear(PWMT3_IRQn);

        _pwmt_dier_interrupt_all_dis(ppwmt);
    }
}

/**
 * @brief PMWT 模块中断禁止函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param int_type 中断类型定义
 */
void drv_pwmt_interruptdisable(reg_pwmt_t *ppwmt, pwmt_int_t int_type)
{
    if (int_type != ALL_PWMT_INT_DIS)
    {
        if (ppwmt == PWMT1)
        {
            NVIC_Clear(PWMT1_IRQn);
        }
        else if (ppwmt == PWMT2)
        {
            NVIC_Clear(PWMT2_IRQn);
        }
        else
        {
            NVIC_Clear(PWMT3_IRQn);
        }

        _pwmt_dier_interrupt_dis(ppwmt, int_type);
    }
    else
    {
        NVIC_Clear(PWMT1_IRQn);
        NVIC_Clear(PWMT2_IRQn);
        NVIC_Clear(PWMT3_IRQn);

        _pwmt_dier_interrupt_all_dis(ppwmt);
    }
}

/**
 * @brief PMWT 模块获取寄存器状态函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @return uint16_t
 */
uint16_t drv_pwmt_getstatusreg(reg_pwmt_t *ppwmt)
{
    return (_pwmt_get_status_reg(ppwmt));
}

/**
 * @brief PMWT 模块获取寄存器中断状态函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @return uint8_t
 */
uint8_t drv_pwmt_getinterruptstatus(reg_pwmt_t *ppwmt)
{
    return (_pwmt_get_int_flag(ppwmt));
}

/**
 * @brief PMWT 模块获取捕获比较值函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口定义
 * @return uint16_t
 */
uint16_t drv_pwmt_getccr(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    uint16_t ccr_tmp = 0;

    switch (portnum)
    {
    case 0:
        ccr_tmp = _pwmt_get_ccr1(ppwmt);
        break;
    case 1:
        ccr_tmp = _pwmt_get_ccr2(ppwmt);
        break;
    case 2:
        ccr_tmp = _pwmt_get_ccr3(ppwmt);
        break;
    case 3:
        ccr_tmp = _pwmt_get_ccr4(ppwmt);
        break;
    default:
        break;
    }

    return ccr_tmp;
}

/**
 * @brief PMWT 模块清除中断状态函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param flag 中断方式定义
 */
void drv_pwmt_clearinterruptstatus(reg_pwmt_t *ppwmt, pwmt_int_t flag)
{
    _pwmt_sr_clr_int_flag(ppwmt, flag);
}

/**
 * @brief PMWT 模块获取过采样标志函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param flag 中断方式定义
 * @return flagstatus_t
 */
flagstatus_t drv_pwmt_getovercaptureflag(reg_pwmt_t *ppwmt, pwmt_int_t flag)
{
    if (_pwmt_get_overcapture_flag(ppwmt, (flag << 8)))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
 * @brief PMWT 模块清除过采样标志函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param flag 中断方式定义
 */
void drv_pwmt_clearovercaptureflag(reg_pwmt_t *ppwmt, pwmt_int_t flag)
{
    _pwmt_sr_clr_int_flag(ppwmt, (flag + 8));
}

/**
 * @brief PMWT 模块获取通道配置方向函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param portnum 端口号定义
 * @return pwmt_dir_t
 */
pwmt_dir_t drv_pwmt_getdir(reg_pwmt_t *ppwmt, uint8_t portnum)
{
    pwmt_dir_t dir = PWMT_INPUT;

    switch (portnum)
    {
    case 0:
        if (_pwmt_ccmr1_ch0_cfg_dir(ppwmt) == PWMT_CCMR1_CC1S_OUT)
        {
            dir = PWMT_OUTPUT;
        }
        break;
    case 1:
        if (_pwmt_ccmr1_ch1_cfg_dir(ppwmt) == PWMT_CCMR1_CC2S_OUT)
        {
            dir = PWMT_OUTPUT;
        }
        break;
    case 2:
        if (_pwmt_ccmr2_ch2_cfg_dir(ppwmt) == PWMT_CCMR2_CC3S_OUT)
        {
            dir = PWMT_OUTPUT;
        }
        break;
    case 3:
        if (_pwmt_ccmr2_ch3_cfg_dir(ppwmt) == PWMT_CCMR2_CC4S_OUT)
        {
            dir = PWMT_OUTPUT;
        }
        break;
    default:
        break;
    }

    return dir;
}

/**
 * @brief PMWT 模块主模式选择函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param sel PWMT主模式选择定义
 */
void drv_pwmt_mastermodeselect(reg_pwmt_t *ppwmt, pwmt_mastermode_sel_t sel)
{
    switch (sel)
    {
    case MMS_RESET:
        _pwmt_cr2_reset_as_trgo(ppwmt);
        break;
    case MMS_ENABLE:
        _pwmt_cr2_counter_en_as_trgo(ppwmt);
        break;
    case MMS_UPDATE:
        _pwmt_cr2_update_event_as_trgo(ppwmt);
        break;
    case MMS_COMPARE_PULSE:
        _pwmt_cr2_compare_pulse_as_trgo(ppwmt);
        break;
    case MMS_COMPARE_OC1REF:
        _pwmt_cr2_compare_oc1ref_as_trgo(ppwmt);
        break;
    case MMS_COMPARE_OC2REF:
        _pwmt_cr2_compare_oc2ref_as_trgo(ppwmt);
        break;
    case MMS_COMPARE_OC3REF:
        _pwmt_cr2_compare_oc3ref_as_trgo(ppwmt);
        break;
    case MMS_COMPARE_OC4REF:
        _pwmt_cr2_compare_oc4ref_as_trgo(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT 模块从模式控制函数
 *
 * @param ppwmt PWMT模块寄存器定义
 */
void drv_pwmt_masterslavemode(reg_pwmt_t *ppwmt)
{
    _pwmt_smcr_master_slave_mode(ppwmt);
}

/**
 * @brief PMWT 模块从模式选择函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param sel 从模式选择定义
 */
void drv_pwmt_slavemodeselect(reg_pwmt_t *ppwmt, pwmt_slavemode_sel_t sel)
{
    switch (sel)
    {
    case SMS_DISABLE:
        _pwmt_smcr_slave_mode_disable(ppwmt);
        break;
    case SMS_ENCODE_MODE1:
        _pwmt_smcr_encoder_mode1(ppwmt);
        break;
    case SMS_ENCODE_MODE2:
        _pwmt_smcr_encoder_mode2(ppwmt);
        break;
    case SMS_ENCODE_MODE3:
        _pwmt_smcr_encoder_mode3(ppwmt);
        break;
    case SMS_RESET:
        _pwmt_smcr_reset_mode(ppwmt);
        break;
    case SMS_GATED:
        _pwmt_smcr_gated_mode(ppwmt);
        break;
    case SMS_TRIGGER:
        _pwmt_smcr_trigger_mode(ppwmt);
        break;
    case SMS_EXTCLK_MODE1:
        _pwmt_smcr_extclk_mode1(ppwmt);
        break;
    default:
        break;
    }
}

/**
 * @brief PMWT 模块刹车使能函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param sel 刹车模式选择定义
 */
void drv_pwmt_breaken(reg_pwmt_t *ppwmt, pwmt_breakmode_sel_t sel)
{
    if (sel == BRK_ENABLE)
    {
        ppwmt->BDTR = (1 << 13); // high level break
        ppwmt->BDTR |= (1 << 10);
        ppwmt->BDTR |= (1 << 11);
        // ppwmt->BDTR|= (1<<16);//ACMP1 OUT
        __asm("nop");
        __asm("nop");
        __asm("nop");
        ppwmt->BDTR |= (1 << 12);
        __asm("nop");
        __asm("nop");
        __asm("nop");
        ppwmt->BDTR |= (1 << 14);
    }
}

/**
 * @brief PMWT 模块触发模式选择函数
 *
 * @param ppwmt PWMT模块寄存器定义
 * @param trgo_mode 触发模式定义
 */
void drv_pwmt_trgomodesel(reg_pwmt_t *ppwmt, pwmt_trgomode_sel_t trgo_mode)
{
    ppwmt->CR1 &= ~(PWMT_CR1_OPM);
    ppwmt->SMCR |= (1 << 7);
    ppwmt->CR2 &= ~(7 << 4);
    switch (trgo_mode)
    {
    case MODE_1:
        ppwmt->CR2 |= (2 << 4);
        break;
    case MODE_2:
        ppwmt->CR2 |= (3 << 4);
        break;
    case MODE_3:
        ppwmt->CR2 |= (4 << 4);
        break;
    default:
        break;
    }
}
