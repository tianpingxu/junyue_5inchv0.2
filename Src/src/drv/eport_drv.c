/**
 * @file eport_drv.c
 * @author Product Application Department
 * @brief  EPORT 模块驱动层.
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "eport_drv.h"

// 函数定义

/**
 * @brief EPORT 模块中断服务函数
 *
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 */
void drv_eport_irqhandler(reg_eport_t *pEport, uint8_t Pinx)
{
    uint8_t status;

    status = _eport_epfr_pins_flag_get(pEport, Pinx);

    if (status)
    {
        _eport_epfr_pins_flag_clr(pEport, Pinx); // clear flag by writing 1 to it.
        if (EPORT0 == pEport)
        {
            printf("Enter EPORT%d interrupt.PIN = %d\r\n", 1, PIN_NUM_IS(Pinx));
        }
        if (EPORT1 == pEport)
        {
            printf("Enter EPORT%d interrupt.PIN = %d\r\n", 2, PIN_NUM_IS(Pinx));
        }
        if (EPORT2 == pEport)
        {
            printf("Enter EPORT%d interrupt.PIN = %d\r\n", 3, PIN_NUM_IS(Pinx));
        }
        if (EPORT3 == pEport)
        {
            printf("Enter EPORT%d interrupt.PIN = %d\r\n", 4, PIN_NUM_IS(Pinx));
        }
        if (EPORT4 == pEport)
        {
            printf("Enter EPORT%d interrupt.PIN = %d\r\n", 5, PIN_NUM_IS(Pinx));
        }
    }
    else
    {
        printf("interrupt.PIN = %d\r\n", PIN_NUM_IS(Pinx));
    }
}

/**
 * @brief EPORT 模块设置引脚中断触发模式函数
 *
 * @param pEport EPORT实例化
 * @param Pins EPORT引脚
 * @param TriggerMode 中断触发模式
 */
void drv_eport_settriggermode(reg_eport_t *pEport, uint8_t Pins, eport_intmode_t TriggerMode)
{
    uint8_t i;
    //    uint16_t ports_val;

    for (i = 0; i < 8; i++)
    {
        if (Pins & (0x01 << i))
        {
            switch (TriggerMode)
            {
            case EPORT_HIGH_LEVEL_TRIGGER:
                _eport_eppar_trigger_level_set(pEport, i);
                _eport_eplpr_pins_high_level_set(pEport, Pins);
                break;
            case EPORT_LOW_LEVEL_TRIGGER:
                _eport_eppar_trigger_level_set(pEport, i);
                _eport_eplpr_pins_low_level_set(pEport, Pins);
                break;
            case EPORT_RISING_TRIGGER:
                _eport_eppar_trigger_rising_set(pEport, i);
                break;
            case EPORT_FALLING_TRIGGER:
                _eport_eppar_trigger_falling_set(pEport, i);
                break;
            case EPORT_RISINGFALLING_TRIGGER:
                _eport_eppar_trigger_falling_rising_set(pEport, i);
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief EPORT 模块设置引脚输入输出函数
 *
 * @param pEport EPORT实例化
 * @param Pins EPORT引脚
 * @param Dir 方向配置
 */
void drv_eport_setdirection(reg_eport_t *pEport, uint8_t Pins, eport_dir_t Dir)
{
    switch (Dir)
    {
    case GPIO_DIR_IN:
        _eport_epddr_pins_input_set(pEport, Pins);
        break;
    case GPIO_DIR_OUT:
        _eport_epddr_pins_output_set(pEport, Pins);
        break;
    default:
        break;
    }
}

/**
 * @brief EPORT 模块设置中断函数
 *
 * @param pEport EPORT实例化
 * @param Pins  EPORT引脚
 * @param Status 是否使能中断
 */
void drv_eport_setit(reg_eport_t *pEport, uint8_t Pins, functionalstate_t Status)
{
    switch (Status)
    {
    case ENABLE:
        _eport_epier_pins_it_en(pEport, Pins);
        break;
    case DISABLE:
        _eport_epier_pins_it_dis(pEport, Pins);
        break;
    default:
        break;
    }
}

/**
 * @brief EPORT 模块清除中断表示函数
 *
 * @param pEport EPORT实例化
 * @param Pinx EPORT引脚
 */
void drv_eport_clearitflag(reg_eport_t *pEport, uint8_t Pinx)
{
    _eport_epfr_pins_flag_clr(pEport, Pinx);
}

/**
 * @brief EPORT 模块设置引脚电平函数
 *
 * @param pEport EPORT实例化
 * @param Pins EPORT引脚
 * @param Level 输出电平
 */
void drv_eport_writepinslevel(reg_eport_t *pEport, uint8_t Pins, gpio_pinstate_t Level)
{
    switch (Level)
    {
    case GPIO_HIGH:
        _eport_epdr_pins_load_set(pEport, Pins);
        break;
    case GPIO_LOW:
        _eport_epdr_pins_load_clr(pEport, Pins);
        break;
    default:
        break;
    }
}

/**
 * @brief EPORT 模块读取引脚电平函数
 *
 * @param pEport EPORT实例化
 * @param pins EPORT引脚
 * @return uint8_t 引脚状态
 */
uint8_t drv_eport_readpinslevel(reg_eport_t *pEport, uint8_t pins)
{
    return _eport_eppdr_pins_data_get(pEport, pins);
}

/**
 * @brief EPORT 模块读取引脚中断标志函数
 *
 * @param pEport EPORT实例化
 * @param pins  EPORT引脚
 * @return uint8_t 返回边沿触发的状态
 */
uint8_t drv_eport_readitflag(reg_eport_t *pEport, uint8_t pins)
{
    return _eport_epfr_pins_flag_get(pEport, pins);
}

/**
 * @brief EPORT 模块配置引脚上下拉使能函数
 *
 * @param pEport EPORT实例化
 * @param Pins EPORT引脚
 * @param Status 是否使能
 */
void drv_eport_setpullup(reg_eport_t *pEport, uint8_t Pins, functionalstate_t Status)
{
    switch (Status)
    {
    case ENABLE:
        _eport_eppuer_pins_pull_up_en(pEport, Pins);
        break;
    case DISABLE:
        _eport_eppuer_pins_pull_up_dis(pEport, Pins);
        break;
    default:
        break;
    }
}

/**
 * @brief EPORT 模块配置引脚输出属性函数
 *
 * @param pEport EPORT实例化
 * @param Pins EPORT引脚
 * @param Mode 推挽/开漏输出
 */
void drv_eport_setopendrain(reg_eport_t *pEport, uint8_t Pins, eport_outputmode_t Mode)
{
    switch (Mode)
    {
    case EPORT_OUTPUT_MODE_CMOS:
        _eport_epoder_pins_output_cmos_set(pEport, Pins);
        break;
    case EPORT_OUTPUT_MODE_OPEN_DRAIN:
        _eport_epoder_pins_output_od_set(pEport, Pins);
        break;
    default:
        break;
    }
}
