/**
 * @file pwmt_drv.h
 * @author Product Application Department
 * @brief  PWMT 模块驱动头文件
 * @version V1.0
 * @date 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __PWMT_DRV_H__
#define __PWMT_DRV_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "pwmt_reg.h"
#include "ioctrl_drv.h"
#include "interrupt.h"
	
// 全局变量定义
#define _pwmt1_etr_enable _ioctrl_swapcr3_swap2_set
#define _pwmt1_brk_enable _ioctrl_swapcr3_swap3_set
#define _pwmt1_ch0_enable _ioctrl_swapcr3_swap8_set
#define _pwmt1_ch0n_enable _ioctrl_swapcr3_swap9_set
#define _pwmt1_ch1_enable _ioctrl_swapcr3_swap10_set
#define _pwmt1_ch1n_enable _ioctrl_swapcr3_swap11_set
#define _pwmt1_ch2_enable _ioctrl_swapcr3_swap12_set
#define _pwmt1_ch2n_enable _ioctrl_swapcr3_swap13_set
#define _pwmt1_ch3_enable _ioctrl_swapcr3_swap14_set
#define _pwmt1_ch3n_enable _ioctrl_swapcr3_swap15_set

#define _pwmt2_etr_enable _ioctrl_swapcr3_swap4_set
#define _pwmt2_brk_enable _ioctrl_swapcr3_swap5_set
#define _pwmt2_ch0_enable _ioctrl_swapcr3_swap16_set
#define _pwmt2_ch0n_enable _ioctrl_swapcr3_swap17_set
#define _pwmt2_ch1_enable _ioctrl_swapcr3_swap18_set
#define _pwmt2_ch1n_enable _ioctrl_swapcr3_swap19_set
#define _pwmt2_ch2_enable _ioctrl_swapcr3_swap20_set
#define _pwmt2_ch2n_enable _ioctrl_swapcr3_swap21_set
#define _pwmt2_ch3_enable _ioctrl_swapcr3_swap22_set
#define _pwmt2_ch3n_enable _ioctrl_swapcr3_swap23_set

#define _pwmt3_etr_enable _ioctrl_swapcr3_swap6_set
#define _pwmt3_brk_enable _ioctrl_swapcr3_swap7_set
#define _pwmt3_ch0_enable _ioctrl_swapcr3_swap24_set
#define _pwmt3_ch0n_enable _ioctrl_swapcr3_swap25_set
#define _pwmt3_ch1_enable _ioctrl_swapcr3_swap26_set
#define _pwmt3_ch1n_enable _ioctrl_swapcr3_swap27_set
#define _pwmt3_ch2_enable _ioctrl_swapcr3_swap28_set
#define _pwmt3_ch2n_enable _ioctrl_swapcr3_swap29_set
#define _pwmt3_ch3_enable _ioctrl_swapcr3_swap30_set
#define _pwmt3_ch3n_enable _ioctrl_swapcr3_swap31_set

// CR1
#define _pwmt_cr1_counter_increase(pwmt) _bit_clr(pwmt->CR1, PWMT_CR1_DIR_DOWN)
#define _pwmt_cr1_counter_decrease(pwmt) _bit_set(pwmt->CR1, PWMT_CR1_DIR_DOWN)
#define _pwmt_cr1_edge_aligned_mode(pwmt) _reg_modify(pwmt->CR1, (~PWMT_CR1_CMS_CALIGN3), PWMT_CR1_CMS_EALIGN)
#define _pwmt_cr1_center_aligned_mode1(pwmt) _reg_modify(pwmt->CR1, (~PWMT_CR1_CMS_CALIGN3), PWMT_CR1_CMS_CALIGN1)
#define _pwmt_cr1_center_aligned_mode2(pwmt) _reg_modify(pwmt->CR1, (~PWMT_CR1_CMS_CALIGN3), PWMT_CR1_CMS_CALIGN2)
#define _pwmt_cr1_center_aligned_mode3(pwmt) _reg_modify(pwmt->CR1, (~PWMT_CR1_CMS_CALIGN3), PWMT_CR1_CMS_CALIGN3)
#define _pwmt_cr1_auto_reload_preload_en(pwmt) _bit_set(pwmt->CR1, PWMT_CR1_ARPE)
#define _pwmt_cr1_counter_en(pwmt) _bit_set(pwmt->CR1, PWMT_CR1_CEN)
#define _pwmt_cr1_counter_dis(pwmt) _bit_clr(pwmt->CR1, PWMT_CR1_CEN)

// CR2
#define _pwmt_cr2_updatae_selection_en(pwmt) _bit_set(pwmt->CR2, PWMT_CR2_CCDS);
#define _pwmt_cr2_updatae_selection_dis(pwmt) _bit_clr(pwmt->CR2, PWMT_CR2_CCDS);
#define _pwmt_cr2_reset_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_RESET)
#define _pwmt_cr2_counter_en_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_ENABLE)
#define _pwmt_cr2_update_event_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_UPDATE)
#define _pwmt_cr2_compare_pulse_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_COMPP)
#define _pwmt_cr2_compare_oc1ref_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_COMP1TRGO)
#define _pwmt_cr2_compare_oc2ref_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_COMP2TRGO)
#define _pwmt_cr2_compare_oc3ref_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_COMP3TRGO)
#define _pwmt_cr2_compare_oc4ref_as_trgo(pwmt) _reg_modify(pwmt->CR2, (~PWMT_CR2_MMS_COMP4TRGO), PWMT_CR2_MMS_COMP4TRGO)

// SMCR
#define _pwmt_smcr_master_slave_mode(pwmt) _bit_set(pwmt->SMCR, PWMT_SMCR_MSM)
#define _pwmt_smcr_slave_mode_disable(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_SLV_DIS)
#define _pwmt_smcr_encoder_mode1(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_ENC_MODE1)
#define _pwmt_smcr_encoder_mode2(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_ENC_MODE2)
#define _pwmt_smcr_encoder_mode3(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_ENC_MODE3)
#define _pwmt_smcr_reset_mode(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_RESET)
#define _pwmt_smcr_gated_mode(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_GATED)
#define _pwmt_smcr_trigger_mode(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_TRIGGER)
#define _pwmt_smcr_extclk_mode1(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_SMS_EXTCLK), PWMT_SMCR_SMS_EXTCLK)
#define _pwmt_smcr_ts_etrf(pwmt) _reg_modify(pwmt->SMCR, (~PWMT_SMCR_TS_ETRF), PWMT_SMCR_TS_ETRF)

// DIER
#define _pwmt_dier_interrupt_en(pwmt, int_bit) _bit_set(pwmt->DIER, (1 << int_bit))
#define _pwmt_dier_interrupt_dis(pwmt, int_bit) _bit_clr(pwmt->DIER, (1 << int_bit))
#define _pwmt_dier_interrupt_all_dis(pwmt) _bit_clr(pwmt->DIER, 0xff)
#define _pwmt_dier_update_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_UDE)
#define _pwmt_dier_update_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_UDE)
#define _pwmt_dier_cc1_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_CC1DE)
#define _pwmt_dier_cc1_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_CC1DE)
#define _pwmt_dier_cc2_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_CC2DE)
#define _pwmt_dier_cc2_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_CC2DE)
#define _pwmt_dier_cc3_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_CC3DE)
#define _pwmt_dier_cc3_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_CC3DE)
#define _pwmt_dier_cc4_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_CC4DE)
#define _pwmt_dier_cc4_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_CC4DE)
#define _pwmt_dier_com_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_COMDE)
#define _pwmt_dier_com_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_COMDE)
#define _pwmt_dier_trigger_dma_request_en(pwmt) _bit_set(pwmt->DIER, PWMT_DIER_TDE)
#define _pwmt_dier_trigger_dma_request_dis(pwmt) _bit_clr(pwmt->DIER, PWMT_DIER_TDE)
// SR
#define _pwmt_get_status_reg(pwmt) _bit_get(pwmt->SR, 0x1EFF)
#define _pwmt_sr_clr_int_flag(pwmt, clr_bit) _bit_clr(pwmt->SR, (1 << clr_bit))
#define _pwmt_get_int_flag(pwmt) _bit_get(pwmt->SR, 0xFF)
#define _pwmt_get_overcapture_flag(pwmt, cap_bit) _bit_get(pwmt->SR, cap_bit)

// EGR
#define _pwmt_egr_update_generation(pwmt) _bit_set(pwmt->EGR, PWMT_EGR_UG)

// CCMR1
#define _pwmt_ccmr1_ch0_cfg_output(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC1S_IN_IC1_TRC), PWMT_CCMR1_CC1S_OUT)
#define _pwmt_ccmr1_ch0_cfg_input_map_ti1(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC1S_IN_IC1_TRC), PWMT_CCMR1_CC1S_IN_IC1_TI1)
#define _pwmt_ccmr1_ch0_cfg_input_map_ti2(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC1S_IN_IC1_TRC), PWMT_CCMR1_CC1S_IN_IC1_TI2)
#define _pwmt_ccmr1_ch0_cfg_input_map_trc(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC1S_IN_IC1_TRC), PWMT_CCMR1_CC1S_IN_IC1_TRC)
#define _pwmt_ccmr1_ch0_pwm_mode1_high_level_valid(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_OC1M_PWM_MODE2), PWMT_CCMR1_OC1M_PWM_MODE1)
#define _pwmt_ccmr1_ch0_pwm_mode2_low_level_valid(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_OC1M_PWM_MODE2), PWMT_CCMR1_OC1M_PWM_MODE2)
#define _pwmt_ccmr1_ch0_oc1ref_toggle(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_OC1M_PWM_MODE2), PWMT_CCMR1_OC1M_TOGGLE)
#define _pwmt_ccmr1_ch0_output_compare_preload_en(pwmt) _bit_set(pwmt->CCMR1, PWMT_CCMR1_OC1PE)
#define _pwmt_ccmr1_ch0_cfg_dir(pwmt) _bit_get(pwmt->CCMR1, PWMT_CCMR1_CC1S_IN_IC1_TRC)

#define _pwmt_ccmr1_ch1_cfg_output(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC2S_IN_IC2_TRC), PWMT_CCMR1_CC2S_OUT)
#define _pwmt_ccmr1_ch1_cfg_input_map_ti1(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC2S_IN_IC2_TRC), PWMT_CCMR1_CC2S_IN_IC2_TI1)
#define _pwmt_ccmr1_ch1_cfg_input_map_ti2(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC2S_IN_IC2_TRC), PWMT_CCMR1_CC2S_IN_IC2_TI2)
#define _pwmt_ccmr1_ch1_cfg_input_map_trc(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_CC2S_IN_IC2_TRC), PWMT_CCMR1_CC2S_IN_IC2_TRC)
#define _pwmt_ccmr1_ch1_pwm_mode1_high_level_valid(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_OC2M_PWM_MODE2), PWMT_CCMR1_OC2M_PWM_MODE1)
#define _pwmt_ccmr1_ch1_pwm_mode2_low_level_valid(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_OC2M_PWM_MODE2), PWMT_CCMR1_OC2M_PWM_MODE2)
#define _pwmt_ccmr1_ch1_oc2ref_toggle(pwmt) _reg_modify(pwmt->CCMR1, (~PWMT_CCMR1_OC2M_PWM_MODE2), PWMT_CCMR1_OC2M_TOGGLE)
#define _pwmt_ccmr1_ch1_output_compare_preload_en(pwmt) _bit_set(pwmt->CCMR1, PWMT_CCMR1_OC2PE)
#define _pwmt_ccmr1_ch1_cfg_dir(pwmt) _bit_get(pwmt->CCMR1, PWMT_CCMR1_CC2S_IN_IC2_TRC)

// CCMR2
#define _pwmt_ccmr2_ch2_cfg_output(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC3S_IN_IC3_TRC), PWMT_CCMR2_CC3S_OUT)
#define _pwmt_ccmr2_ch2_cfg_input_map_ti3(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC3S_IN_IC3_TRC), PWMT_CCMR2_CC3S_IN_IC3_TI3)
#define _pwmt_ccmr2_ch2_cfg_input_map_ti4(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC3S_IN_IC3_TRC), PWMT_CCMR2_CC3S_IN_IC3_TI4)
#define _pwmt_ccmr2_ch2_cfg_input_map_trc(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC3S_IN_IC3_TRC), PWMT_CCMR2_CC3S_IN_IC3_TRC)
#define _pwmt_ccmr2_ch2_pwm_mode1_high_level_valid(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_OC3M_PWM_MODE2), PWMT_CCMR2_OC3M_PWM_MODE1)
#define _pwmt_ccmr2_ch2_pwm_mode2_low_level_valid(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_OC3M_PWM_MODE2), PWMT_CCMR2_OC3M_PWM_MODE2)
#define _pwmt_ccmr2_ch2_oc3ref_toggle(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_OC3M_PWM_MODE2), PWMT_CCMR2_OC3M_TOGGLE)
#define _pwmt_ccmr2_ch2_output_compare_preload_en(pwmt) _bit_set(pwmt->CCMR2, PWMT_CCMR2_OC3PE)
#define _pwmt_ccmr2_ch2_cfg_dir(pwmt) _bit_get(pwmt->CCMR2, PWMT_CCMR2_CC3S_IN_IC3_TRC)

#define _pwmt_ccmr2_ch3_cfg_output(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC4S_IN_IC4_TRC), PWMT_CCMR2_CC4S_OUT)
#define _pwmt_ccmr2_ch3_cfg_input_map_ti3(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC4S_IN_IC4_TRC), PWMT_CCMR2_CC4S_IN_IC4_TI3)
#define _pwmt_ccmr2_ch3_cfg_input_map_ti4(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC4S_IN_IC4_TRC), PWMT_CCMR2_CC4S_IN_IC4_TI4)
#define _pwmt_ccmr2_ch3_cfg_input_map_trc(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_CC4S_IN_IC4_TRC), PWMT_CCMR2_CC4S_IN_IC4_TRC)
#define _pwmt_ccmr2_ch3_pwm_mode1_high_level_valid(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_OC4M_PWM_MODE2), PWMT_CCMR2_OC4M_PWM_MODE1)
#define _pwmt_ccmr2_ch3_pwm_mode2_low_level_valid(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_OC4M_PWM_MODE2), PWMT_CCMR2_OC4M_PWM_MODE2)
#define _pwmt_ccmr2_ch3_oc4ref_toggle(pwmt) _reg_modify(pwmt->CCMR2, (~PWMT_CCMR2_OC4M_PWM_MODE2), PWMT_CCMR2_OC4M_TOGGLE)
#define _pwmt_ccmr2_ch3_output_compare_preload_en(pwmt) _bit_set(pwmt->CCMR2, PWMT_CCMR2_OC4PE)
#define _pwmt_ccmr2_ch3_cfg_dir(pwmt) _bit_get(pwmt->CCMR2, PWMT_CCMR2_CC4S_IN_IC4_TRC)

// CCER
#define _pwmt_ccer_ch0_high_level_valid(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC1P)
#define _pwmt_ccer_ch0_low_level_valid(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1P)
#define _pwmt_ccer_cc1p_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC1P)
#define _pwmt_ccer_cc1p_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1P)
#define _pwmt_ccer_ch0_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1E)
#define _pwmt_ccer_ch0n_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1NE)
#define _pwmt_ccer_ch0_output_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC1E)
#define _pwmt_ccer_ch0_capture_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1E)
#define _pwmt_ccer_ch0_capture_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC1E)
#define _pwmt_ccer_ch0_deadzone_polarity(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1NP)
#define _pwmt_ccer_cc1np_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC1NP)
#define _pwmt_ccer_cc1np_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1NP)
#define _pwmt_ccer_ch0_deadzone_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC1NE)

#define _pwmt_ccer_ch1_high_level_valid(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC2P)
#define _pwmt_ccer_ch1_low_level_valid(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2P)
#define _pwmt_ccer_cc2p_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC2P)
#define _pwmt_ccer_cc2p_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2P)
#define _pwmt_ccer_ch1_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2E)
#define _pwmt_ccer_ch1n_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2NE)
#define _pwmt_ccer_ch1_output_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC2E)
#define _pwmt_ccer_ch1_capture_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2E)
#define _pwmt_ccer_ch1_capture_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC2E)
#define _pwmt_ccer_ch1_deadzone_polarity(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2NP)
#define _pwmt_ccer_cc2np_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC2NP)
#define _pwmt_ccer_cc2np_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2NP)
#define _pwmt_ccer_ch1_deadzone_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC2NE)

#define _pwmt_ccer_ch2_high_level_valid(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC3P)
#define _pwmt_ccer_ch2_low_level_valid(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3P)
#define _pwmt_ccer_cc3p_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC3P)
#define _pwmt_ccer_cc3p_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3P)
#define _pwmt_ccer_ch2_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3E)
#define _pwmt_ccer_ch2n_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3NE)
#define _pwmt_ccer_ch2_output_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC3E)
#define _pwmt_ccer_ch2_capture_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3E)
#define _pwmt_ccer_ch2_capture_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC3E)
#define _pwmt_ccer_ch2_deadzone_polarity(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3NP)
#define _pwmt_ccer_cc3np_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC3NP)
#define _pwmt_ccer_cc3np_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3NP)
#define _pwmt_ccer_ch2_deadzone_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC3NE)

#define _pwmt_ccer_ch3_high_level_valid(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC4P)
#define _pwmt_ccer_ch3_low_level_valid(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4P)
#define _pwmt_ccer_cc4p_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC4P)
#define _pwmt_ccer_cc4p_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4P)
#define _pwmt_ccer_ch3_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4E)
#define _pwmt_ccer_ch3n_output_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4NE)
#define _pwmt_ccer_ch3_output_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC4E)
#define _pwmt_ccer_ch3_capture_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4E)
#define _pwmt_ccer_ch3_capture_dis(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC4E)
#define _pwmt_ccer_ch3_deadzone_polarity(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4NP)
#define _pwmt_ccer_cc4np_low(pwmt) _bit_clr(pwmt->CCER, PWMT_CCER_CC4NP)
#define _pwmt_ccer_cc4np_high(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4NP)
#define _pwmt_ccer_ch3_deadzone_en(pwmt) _bit_set(pwmt->CCER, PWMT_CCER_CC4NE)

// CNT
// PSC
#define _pwmt_psc_prescaler_value(pwmt, val) _reg_write(pwmt->PSC, val)

// ARR
#define _pwmt_arr_auto_reload_value(pwmt, val) _reg_write(pwmt->ARR, val)

// RCR

// CCR1
#define _pwmt_ccr1_ch0_dutyfactor(pwmt, val) _reg_write(pwmt->CCR1, val)
#define _pwmt_get_ccr1(pwmt) (_reg_read(pwmt->CCR1) & 0xffff)

// CCR2
#define _pwmt_ccr2_ch1_dutyfactor(pwmt, val) _reg_write(pwmt->CCR2, val)
#define _pwmt_get_ccr2(pwmt) (_reg_read(pwmt->CCR2) & 0xffff)

// CCR3
#define _pwmt_ccr3_ch2_dutyfactor(pwmt, val) _reg_write(pwmt->CCR3, val)
#define _pwmt_get_ccr3(pwmt) (_reg_read(pwmt->CCR3) & 0xffff)

// CCR4
#define _pwmt_ccr4_ch3_dutyfactor(pwmt, val) _reg_write(pwmt->CCR4, val)
#define _pwmt_get_ccr4(pwmt) (_reg_read(pwmt->CCR4) & 0xffff)

// BDTR
#define _pwmt_bdtr_deadzone_time(pwmt, val) _reg_modify(pwmt->BDTR, 0xffffff00, (val & 0x000000ff))
#define _pwmt_bdtr_main_output_en(pwmt) _bit_set(pwmt->BDTR, PWMT_BDTR_MOE)

// DCR
// DMAR
// PMCR1
// PMCR2
// PMCR3
// PMCR4
// PMCREN
// PUE
#define _pwmt_ch_pull_en(pwmt, ch) _bit_set(pwmt->PUE, (1 << ch))
#define _pwmt_ch_pull_dis(pwmt, ch) _bit_clr(pwmt->PUE, (1 << ch))

typedef void (*pwmt_callback_t)(void *);
/**
 * @brief PWMT 模块引脚功能枚举定义
 *
 */
typedef enum
{
    PWMT_0 = 0,
    PWMT_0_N,
    PWMT_1,
    PWMT_1_N,
    PWMT_2,
    PWMT_2_N,
    PWMT_3,
    PWMT_3_N,
    PWMT_ALL,
} pwmt_pin_func_t;
/**
 * @brief PWMT 模块通道枚举定义
 *
 */
typedef enum
{
    CHANNEL0 = 0,
    CHANNEL1,
    CHANNEL2,
    CHANNEL3,
} pwmt_ch_t;
/**
 * @brief PWMT 模块功能方向枚举定义
 *
 */
typedef enum
{
    PWMT_INPUT = 0,
    PWMT_OUTPUT,
} pwmt_dir_t;
/**
 * @brief PWMT 模块分频枚举定义
 *
 */
typedef enum
{
    CKINT_MUT1 = 0,
    CKINT_MUT2,
    CKINT_MUT4,
} pwmt_clk_div_t;
/**
 * @brief PWMT 模块中断方式枚举定义
 *
 */
typedef enum
{
    UPDATE_INTERRUPT = 0,
    CAPTURE_COMPARE1 = 1,
    CAPTURE_COMPARE2 = 2,
    CAPTURE_COMPARE3 = 3,
    CAPTURE_COMPARE4 = 4,
    COM_INTERRUPT = 5,
    TRIGGER_INTERRUPT = 6,
    BREAK_INTERRUPT = 7,
    ALL_PWMT_INT_DIS,
} pwmt_int_t;
/**
 * @brief PWMT 模块触发方式枚举定义
 *
 */
typedef enum
{
    RISING_EDGE = 0,
    FALLING_EDGE,
    RESERVED_WAY,
    BOTH_EDGE,
} pwmt_triggerway_t;
/**
 * @brief PWMT 模块输出配置结构体定义
 *
 */
typedef struct
{
    uint8_t deadzone;
    uint8_t prescaler;
    uint16_t period;
    uint16_t width;
    pwmt_clk_div_t clkdiv;
    functionalstate_t autoload;
} pwmt_output_t;
/**
 * @brief PWMT 模块输入配置结构体定义
 *
 */
typedef struct
{
    uint8_t deadzone;
    uint8_t prescaler;
    uint8_t clkdiv;
    uint16_t period;
    uint32_t edgeinterrupt;
    functionalstate_t autoload;
    pwmt_triggerway_t trigger;
} pwmt_input_t;
/**
 * @brief PWMT 模块刹车模式选择枚举定义
 *
 */
typedef enum
{
    BRK_DISABLE = 1,
    BRK_ENABLE,
} pwmt_breakmode_sel_t;
/**
 * @brief PWMT 模块触发模式选择枚举定义
 *
 */
typedef enum
{
    MODE_1 = 0,
    MODE_2,
    MODE_3,
} pwmt_trgomode_sel_t;
/**
 * @brief PWMT 模块功能配置结构体定义
 *
 */
typedef struct
{
    uint8_t channel;
    pwmt_pin_func_t function;
    pwmt_dir_t direction;
    pwmt_int_t interrupr_type;
    pwmt_breakmode_sel_t brk;
    pwmt_trgomode_sel_t trgo_mode;
    union
    {
        pwmt_input_t in;
        pwmt_output_t out;
    };
} pwmt_init_t;
/**
 * @brief PWMT 模块配置句柄结构体定义
 *
 */
typedef struct
{
    reg_pwmt_t *instance;
    pwmt_init_t init;
    pwmt_callback_t RisingCallback;
    pwmt_callback_t FallingCallback;
    pwmt_callback_t CaptureCallback;
} pwmt_handle_t;
/**
 * @brief PWMT 模块方向通道方向枚举定义
 *
 */
typedef enum
{
    CC1_CHANNEL_OUTPUT = 0,
    CC1_CHANNEL_INPUT_IC1_MAP_TI1,
    CC1_CHANNEL_INPUT_IC1_MAP_TI2,
    CC1_CHANNEL_INPUT_IC1_MAP_TRC,
} pwmt_dir_channel_t;
/**
 * @brief PWMT 模块输出比较模式枚举定义
 *
 */
typedef enum
{
    FROZEN = 0,
    CH1_ACTIVE_LEVEL_MATCH = 1,
    CH1_INACTIVE_LEVEL_MATCH = 2,
    TOGGLE = 3,
    OC1REF_FORCE_LOW = 4,
    OC1REF_FORCE_HIGH = 5,
    PWM_MODE1 = 6,
    PWM_MODE2 = 7,
} pwmt_outcmp_mode_t;
/**
 * @brief PWMT 模块计数方向枚举定义
 *
 */
typedef enum
{
    UP_COUNTER = 0,
    DOWN_COUNTER,
} pwmt_count_dir_t;
/**
 * @brief PWMT 模块中心对齐模式枚举定义
 *
 */
typedef enum
{
    EDGE_ALIGN = 0,
    CENTER_ALIGN_MODE1,
    CENTER_ALIGN_MODE2,
    CENTER_ALIGN_MODE3,
} pwmt_center_alignmode_t;
/**
 * @brief PWMT 模块主模式选择枚举定义
 *
 */
typedef enum
{
    MMS_RESET = 0,
    MMS_ENABLE = 1,
    MMS_UPDATE = 2,
    MMS_COMPARE_PULSE = 3,
    MMS_COMPARE_OC1REF = 4,
    MMS_COMPARE_OC2REF = 5,
    MMS_COMPARE_OC3REF = 6,
    MMS_COMPARE_OC4REF = 7,
} pwmt_mastermode_sel_t;
/**
 * @brief PWMT 模块从模式选择枚举定义
 *
 */
typedef enum
{
    SMS_DISABLE = 0,
    SMS_ENCODE_MODE1 = 1,
    SMS_ENCODE_MODE2 = 2,
    SMS_ENCODE_MODE3 = 3,
    SMS_RESET = 4,
    SMS_GATED = 5,
    SMS_TRIGGER = 6,
    SMS_EXTCLK_MODE1 = 7,
} pwmt_slavemode_sel_t;
// 函数声明
void drv_pwmt1_swapenable(uint8_t ch);
void drv_pwmt2_swapenable(uint8_t ch);
void drv_pwmt3_swapenable(uint8_t ch);
void drv_pwmt_counterenable(reg_pwmt_t *ppwmt, functionalstate_t status);
void drv_pwmt_capturecompare1selection(reg_pwmt_t *ppwmt, uint8_t portnum);
void drv_pwmt_outputcomparemode(reg_pwmt_t *ppwmt, uint8_t portnum, pwmt_outcmp_mode_t mode);
void drv_pwmt_outputcomparepreloadenable(reg_pwmt_t *ppwmt, uint8_t portnum);
void drv_pwmt_channeloutput(reg_pwmt_t *ppwmt, uint8_t portnum);
void drv_pwmt_capturecompareoutputpolarity(reg_pwmt_t *ppwmt, uint8_t portnum, BitActionTypeDef high);
void drv_pwmt_channeloutputenable(reg_pwmt_t *ppwmt, uint8_t portnum, functionalstate_t en);
void drv_pwmt_setdutyfactor(reg_pwmt_t *ppwmt, uint8_t portnum, uint16_t width);
void drv_pwmt_setdeadzone(reg_pwmt_t *ppwmt, uint8_t portnum, uint16_t deadzone);
void drv_pwmt_setprescaler(reg_pwmt_t *ppwmt, uint16_t pre);
void drv_pwmt_setperiod(reg_pwmt_t *ppwmt, uint16_t period);
void drv_pwmt_setcounterdir(reg_pwmt_t *ppwmt, pwmt_count_dir_t dir);
void drv_pwmt_centeralignmode(reg_pwmt_t *ppwmt, pwmt_center_alignmode_t mode);
void drv_pwmt_updtgeneration(reg_pwmt_t *ppwmt);
void drv_pwmt_autoreloaden(reg_pwmt_t *ppwmt);
void drv_pwmt_mainoutputen(reg_pwmt_t *ppwmt);
void drv_pwmt_pullenable(reg_pwmt_t *ppwmt, uint8_t ch, functionalstate_t status);
void drv_pwmt_channelinput(reg_pwmt_t *ppwmt, uint8_t portnum);
void drv_pwmt_channelcaptureenable(reg_pwmt_t *ppwmt, uint8_t portnum, functionalstate_t en);
void drv_pwmt_updatedmarequestenable(reg_pwmt_t *ppwmt);
void drv_pwmt_cc1dmarequestenable(reg_pwmt_t *ppwmt);
void drv_pwmt_cc2dmarequestenable(reg_pwmt_t *ppwmt);
void drv_pwmt_cc3dmarequestenable(reg_pwmt_t *ppwmt);
void drv_pwmt_cc4dmarequestenable(reg_pwmt_t *ppwmt);
void drv_pwmt_settriggerway(reg_pwmt_t *ppwmt, uint8_t portnum, pwmt_triggerway_t way);
void drv_pwmt_interruptenable(reg_pwmt_t *ppwmt, pwmt_int_t int_type);
void drv_pwmt_interruptdisable(reg_pwmt_t *ppwmt, pwmt_int_t int_type);

uint8_t drv_pwmt_getinterruptstatus(reg_pwmt_t *ppwmt);
flagstatus_t drv_pwmt_getovercaptureflag(reg_pwmt_t *ppwmt, pwmt_int_t flag);
void drv_pwmt_clearinterruptstatus(reg_pwmt_t *ppwmt, pwmt_int_t flag);
void drv_pwmt_clearovercaptureflag(reg_pwmt_t *ppwmt, pwmt_int_t flag);
uint16_t drv_pwmt_getstatusreg(reg_pwmt_t *ppwmt);
void drv_pwmt_mastermodeselect(reg_pwmt_t *ppwmt, pwmt_mastermode_sel_t sel);
void drv_pwmt_masterslavemode(reg_pwmt_t *ppwmt);
void drv_pwmt_slavemodeselect(reg_pwmt_t *ppwmt, pwmt_slavemode_sel_t sel);
uint16_t drv_pwmt_getccr(reg_pwmt_t *ppwmt, uint8_t portnum);
pwmt_dir_t drv_pwmt_getdir(reg_pwmt_t *ppwmt, uint8_t port_num);
void drv_pwmt_breaken(reg_pwmt_t *ppwmt, pwmt_breakmode_sel_t sel);
void drv_pwmt_trgomodesel(reg_pwmt_t *ppwmt, pwmt_trgomode_sel_t trgo_mode);

#ifdef __cplusplus
}
#endif

#endif
