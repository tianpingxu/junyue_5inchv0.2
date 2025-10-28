/**
 * @file eport_drv.h
 * @author Product application department
 * @brief  EPORT 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __EPORT_DRV_H__
#define __EPORT_DRV_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "drv_gpio_def.h"
#include "ioctrl_drv.h"
#include "interrupt.h"
#include "eport_reg.h"


// 全局变量定义
#define PIN_NUM_IS(pin) (pin & 0x01 ? 0 : (pin & 0x02 ? 1 : (pin & 0x04 ? 2 : (pin & 0x08 ? 3 : (pin & 0x10 ? 4 : (pin & 0x20 ? 5 : (pin & 0x40 ? 6 : 7)))))))
// EPPAR
#define _eport_eppar_trigger_level_set(eportx, pins) _bit_clr(eportx->EPPAR, (0x03 << pins * 2))
#define _eport_eppar_trigger_rising_set(eportx, pins) _reg_modify(eportx->EPPAR, ~(0x3 << pins * 2), (0x01 << pins * 2))
#define _eport_eppar_trigger_falling_set(eportx, pins) _reg_modify(eportx->EPPAR, ~(0x3 << pins * 2), (0x02 << pins * 2))
#define _eport_eppar_trigger_falling_rising_set(eportx, pins) _reg_modify(eportx->EPPAR, ~(0x3 << pins * 2), (0x03 << pins * 2))
#define _eport_eppar_pin0_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA0)
#define _eport_eppar_pin1_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA1)
#define _eport_eppar_pin2_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA2)
#define _eport_eppar_pin3_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA3)
#define _eport_eppar_pin4_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA4)
#define _eport_eppar_pin5_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA5)
#define _eport_eppar_pin6_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA6)
#define _eport_eppar_pin7_trigger_set(eportx, val) _reg_write(eportx->EPPAR, (uint16_t)val << EPORT_EPPAR_EPPA7)

// EPDDR
#define _eport_epddr_pins_output_set(eportx, pins) _bit_set(eportx->EPDDR, pins << EPORT_EPDDR_EPDD)
#define _eport_epddr_pins_input_set(eportx, pins) _bit_clr(eportx->EPDDR, pins << EPORT_EPDDR_EPDD)
#define _eport_epddr_pin0_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD0)
#define _eport_epddr_pin0_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD0)
#define _eport_epddr_pin1_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD1)
#define _eport_epddr_pin1_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD1)
#define _eport_epddr_pin2_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD2)
#define _eport_epddr_pin2_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD2)
#define _eport_epddr_pin3_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD3)
#define _eport_epddr_pin3_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD3)
#define _eport_epddr_pin4_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD4)
#define _eport_epddr_pin4_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD4)
#define _eport_epddr_pin5_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD5)
#define _eport_epddr_pin5_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD5)
#define _eport_epddr_pin6_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD6)
#define _eport_epddr_pin6_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD6)
#define _eport_epddr_pin7_output_set(eportx) _bit_set(eportx->EPDDR, EPORT_EPDDR_EPDD7)
#define _eport_epddr_pin7_input_set(eportx) _bit_clr(eportx->EPDDR, EPORT_EPDDR_EPDD7)

// EPIER
#define _eport_epier_pins_it_en(eportx, pins) _bit_set(eportx->EPIER, pins << EPORT_EPIER_EPIE)
#define _eport_epier_pins_it_dis(eportx, pins) _bit_clr(eportx->EPIER, pins << EPORT_EPIER_EPIE)
#define _eport_epier_pin0_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE0)
#define _eport_epier_pin0_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE0)
#define _eport_epier_pin1_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE1)
#define _eport_epier_pin1_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE1)
#define _eport_epier_pin2_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE2)
#define _eport_epier_pin2_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE2)
#define _eport_epier_pin3_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE3)
#define _eport_epier_pin3_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE3)
#define _eport_epier_pin4_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE4)
#define _eport_epier_pin4_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE4)
#define _eport_epier_pin5_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE5)
#define _eport_epier_pin5_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE5)
#define _eport_epier_pin6_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE6)
#define _eport_epier_pin6_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE6)
#define _eport_epier_pin7_it_en(eportx) _bit_set(eportx->EPIER, EPORT_EPIER_EPIE7)
#define _eport_epier_pin7_it_dis(eportx) _bit_clr(eportx->EPIER, EPORT_EPIER_EPIE7)

// EPDR
#define _eport_epdr_pins_load_set(eportx, pins) _bit_set(eportx->EPDR, pins << EPORT_EPDR_EPD)
#define _eport_epdr_pins_load_clr(eportx, pins) _bit_clr(eportx->EPDR, pins << EPORT_EPDR_EPD)
#define _eport_epdr_pin0_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD0)
#define _eport_epdr_pin0_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD0)
#define _eport_epdr_pin1_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD1)
#define _eport_epdr_pin1_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD1)
#define _eport_epdr_pin2_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD2)
#define _eport_epdr_pin2_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD2)
#define _eport_epdr_pin3_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD3)
#define _eport_epdr_pin3_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD3)
#define _eport_epdr_pin4_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD4)
#define _eport_epdr_pin4_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD4)
#define _eport_epdr_pin5_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD5)
#define _eport_epdr_pin5_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD5)
#define _eport_epdr_pin6_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD6)
#define _eport_epdr_pin6_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD6)
#define _eport_epdr_pin7_load_set(eportx) _bit_set(eportx->EPDR, EPORT_EPDR_EPD7)
#define _eport_epdr_pin7_load_clr(eportx) _bit_clr(eportx->EPDR, EPORT_EPDR_EPD7)

// EPPDR
#define _eport_eppdr_pins_data_get(eportx, pins) _bit_get(eportx->EPPDR, pins << EPORT_EPPDR_EPPD)
#define _eport_eppdr_pin_data_get(eportx, pins) _bit_get(eportx->EPPDR, pins)
#define _eport_eppdr_pin0_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD0)
#define _eport_eppdr_pin1_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD1)
#define _eport_eppdr_pin2_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD2)
#define _eport_eppdr_pin3_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD3)
#define _eport_eppdr_pin4_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD4)
#define _eport_eppdr_pin5_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD5)
#define _eport_eppdr_pin6_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD6)
#define _eport_eppdr_pin7_data_get(eportx) _bit_get(eportx->EPPDR, EPORT_EPPDR_EPPD7)

// EPFR
#define _eport_epfr_pins_flag_get(eportx, pin) _bit_get(eportx->EPFR, pin << EPORT_EPFR_EPF)
#define _eport_epfr_pins_flag_clr(eportx, pin) _bit_set(eportx->EPFR, pin << EPORT_EPFR_EPF)
#define _eport_epFr_pin0_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF0)
#define _eport_epFr_pin1_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF1)
#define _eport_epFr_pin2_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF2)
#define _eport_epFr_pin3_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF3)
#define _eport_epFr_pin4_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF4)
#define _eport_epFr_pin5_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF5)
#define _eport_epFr_pin6_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF6)
#define _eport_epFr_pin7_flag_get(eportx) _bit_get(eportx->EPFR, EPORT_EPFR_EPF7)

// EPPUER
#define _eport_eppuer_pins_pull_up_en(eportx, pins) _bit_set(eportx->EPPUER, pins << EPORT_EPPUER_EPPUE)
#define _eport_eppuer_pins_pull_up_dis(eportx, pins) _bit_clr(eportx->EPPUER, pins << EPORT_EPPUER_EPPUE)
#define _eport_eppuer_pin0_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE0)
#define _eport_eppuer_pin0_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE0)
#define _eport_eppuer_pin1_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE1)
#define _eport_eppuer_pin1_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE1)
#define _eport_eppuer_pin2_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE2)
#define _eport_eppuer_pin2_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE2)
#define _eport_eppuer_pin3_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE3)
#define _eport_eppuer_pin3_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE3)
#define _eport_eppuer_pin4_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE4)
#define _eport_eppuer_pin4_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE4)
#define _eport_eppuer_pin5_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE5)
#define _eport_eppuer_pin5_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE5)
#define _eport_eppuer_pin6_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE6)
#define _eport_eppuer_pin6_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE6)
#define _eport_eppuer_pin7_pull_up_en(eportx) _bit_set(eportx->EPPUER, EPORT_EPPUER_EPPUE7)
#define _eport_eppuer_pin7_pull_up_dis(eportx) _bit_clr(eportx->EPPUER, EPORT_EPPUER_EPPUE7)

// EPLPR
#define _eport_eplpr_pins_high_level_set(eportx, pins) _bit_set(eportx->EPLPR, pins << EPORT_EPLPR_EPLP)
#define _eport_eplpr_pins_low_level_set(eportx, pins) _bit_clr(eportx->EPLPR, pins << EPORT_EPLPR_EPLP)
#define _eport_eplpr_pin0_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP0)
#define _eport_eplpr_pin0_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP0)
#define _eport_eplpr_pin1_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP1)
#define _eport_eplpr_pin1_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP1)
#define _eport_eplpr_pin2_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP2)
#define _eport_eplpr_pin2_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP2)
#define _eport_eplpr_pin3_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP3)
#define _eport_eplpr_pin3_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP3)
#define _eport_eplpr_pin4_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP4)
#define _eport_eplpr_pin4_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP4)
#define _eport_eplpr_pin5_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP5)
#define _eport_eplpr_pin5_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP5)
#define _eport_eplpr_pin6_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP6)
#define _eport_eplpr_pin6_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP6)
#define _eport_eplpr_pin7_high_level_set(eportx) _bit_set(eportx->EPLPR, EPORT_EPLPR_EPLP7)
#define _eport_eplpr_pin7_low_level_set(eportx) _bit_clr(eportx->EPLPR, EPORT_EPLPR_EPLP7)

// EPODER
#define _eport_epoder_pins_output_od_set(eportx, pins) _bit_set(eportx->EPODER, pins << EPORT_EPODER_EPODE)
#define _eport_epoder_pins_output_cmos_set(eportx, pins) _bit_clr(eportx->EPODER, pins << EPORT_EPODER_EPODE)
#define _eport_epoder_pin0_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE0)
#define _eport_epoder_pin0_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE0)
#define _eport_epoder_pin1_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE1)
#define _eport_epoder_pin1_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE1)
#define _eport_epoder_pin2_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE2)
#define _eport_epoder_pin2_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE2)
#define _eport_epoder_pin3_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE3)
#define _eport_epoder_pin3_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE3)
#define _eport_epoder_pin4_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE4)
#define _eport_epoder_pin4_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE4)
#define _eport_epoder_pin5_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE5)
#define _eport_epoder_pin5_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE5)
#define _eport_epoder_pin6_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE6)
#define _eport_epoder_pin6_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE6)
#define _eport_epoder_pin7_high_level_set(eportx) _bit_set(eportx->EPODER, EPORT_EPODER_EPODE7)
#define _eport_epoder_pin7_low_level_set(eportx) _bit_clr(eportx->EPODER, EPORT_EPODER_EPODE7)

/**
 * @brief EORIT 模块中断触发类型枚举定义
 * 
 */
typedef enum
{
    EPORT_TRIGGER_NULL = 0,
    EPORT_HIGH_LEVEL_TRIGGER,
    EPORT_LOW_LEVEL_TRIGGER,
    EPORT_RISING_TRIGGER,
    EPORT_FALLING_TRIGGER,
    EPORT_RISINGFALLING_TRIGGER
} eport_intmode_t;

/**
 * @brief EPORT 模块输出类型枚举定义
 * 
 */
typedef enum
{
    EPORT_OUTPUT_MODE_CMOS = 0,
    EPORT_OUTPUT_MODE_OPEN_DRAIN
} eport_outputmode_t;

// 函数声明
void drv_eport_irqhandler(reg_eport_t *pEport, uint8_t Pinx);
void drv_eport_settriggermode(reg_eport_t *pEport, uint8_t Pins, eport_intmode_t TriggerMode);
void drv_eport_setdirection(reg_eport_t *pEport, uint8_t Pins, eport_dir_t Dir);
void drv_eport_setit(reg_eport_t *pEport, uint8_t Pins, functionalstate_t Status);
void drv_eport_writepinslevel(reg_eport_t *pEport, uint8_t Pins, gpio_pinstate_t Level);
uint8_t drv_eport_readpinslevel(reg_eport_t *pEport, uint8_t pins);
uint8_t drv_eport_readitflag(reg_eport_t *pEport, uint8_t pins);
void drv_eport_setpullup(reg_eport_t *pEport, uint8_t Pins, functionalstate_t Status);
void drv_eport_setopendrain(reg_eport_t *pEport, uint8_t Pins, eport_outputmode_t Mode);
void drv_eport_clearitflag(reg_eport_t *pEport, uint8_t Pinx);

#ifdef __cplusplus
}

#endif

#endif
