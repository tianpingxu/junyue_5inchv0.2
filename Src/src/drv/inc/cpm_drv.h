/**
 * @file cpm_drv.h
 * @author Product application department
 * @brief  CPM 模块驱动层头文件
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __DRV_CPM_H
#define __DRV_CPM_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "delay.h"
#include "ccm_drv.h"
#include "libccm4211.h"
#include "cpm_reg.h"
                                                                                                                       
// 全局变量定义
#define DRV_SYS_OSC_CLK_500M     (500 * 1000 * 1000)
#define DRV_SYS_OSC_CLK_480M     (480 * 1000 * 1000)
#define DRV_SYS_OSC_CLK_400M     (400 * 1000 * 1000)
#define DRV_SYS_OSC_CLK_320M     (320 * 1000 * 1000)
#define DRV_SYS_OSC_CLK_240M     (120 * 1000 * 1000)
#define DRV_SYS_OSC_CLK_12M      (12 * 1000 * 1000)
#define DRV_SYS_OSC_CLK_8M       (8 * 1000 * 1000)
#define TRIM_500M_VALUE (*(volatile unsigned int *)(0x480000E8) & 0x0001FFFF)
#define TRIM_400M_VALUE (*(volatile unsigned int *)(0x48000700) & 0x0001FFFF)

#define _cpm_get_osc400mhz_trim_value (_reg_read(CPM->O400MTRIMR)& 0x0001FFFF) 
// sleep config:SLPCFGR
#define _cpm_sleep_mode_sel(mode) _reg_modify(CPM->SLPCFGR, 0x10FFFFFF, ((uint32_t)mode) << 24)
#define _cpm_eport4_module_clock_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_EPORT4_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport4_module_clock_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_EPORT4_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport3_module_clock_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_EPORT3_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport3_module_clock_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_EPORT3_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport2_module_clock_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_EPORT2_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport2_module_clock_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_EPORT2_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport1_module_clock_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_EPORT1_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport1_module_clock_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_EPORT1_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport0_module_clock_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_EPORT0_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport0_module_clock_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_EPORT0_MODULE_CLOCK_SLEEP_EN)
#define _cpm_eport_all_module_clk_sleep_en _bit_set(CPM->SLPCFGR, 0x1C600000)
#define _cpm_eport_all_module_clk_sleep_dis _bit_clr(CPM->SLPCFGR, 0x1C600000)
#define _cpm_oscext_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_OSCEXT_SLEEP_EN)
#define _cpm_oscext_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_OSCEXT_SLEEP_EN)
#define _cpm_pmu128k_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_PMU128K_SLEEP_EN)
#define _cpm_pmu128k_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_PMU128K_SLEEP_EN)
#define _cpm_rtc32k_sleep_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_RTC32K_SLEEP_EN)
#define _cpm_rtc32k_sleep_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_RTC32K_SLEEP_EN)
#define _cpm_vdd33_ldo_enter_lowpower_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_VDD33_LDO_ENTER_LOWPOWER_EN)
#define _cpm_vdd33_ldo_enter_lowpower_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_VDD33_LDO_ENTER_LOWPOWER_EN)
#define _cpm_flash_ldo_enter_lowpower_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_FLASH_LDO_ENTER_LOWPOWER_EN)
#define _cpm_flash_ldo_enter_lowpower_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_FLASH_LDO_ENTER_LOWPOWER_EN)
#define _cpm_card0_ldo_poweron _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_CARD0_LDO_POWEROFF)
#define _cpm_card0_ldo_poweroff _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_CARD0_LDO_POWEROFF)
#define _cpm_card0_ldo_votage_out_config(conf) _reg_modify(CPM->SLPCFGR, 0xFFFFFCFF, (conf))
#define _cpm_flash_ldo_enter_lowpower_poweroff _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_FLASH_LDO_ENTER_LOWPOWER_POWEROFF)
#define _cpm_flash_ldo_enter_lowpower_poweron _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_FLASH_LDO_ENTER_LOWPOWER_POWEROFF)
#define _cpm_flash_ip_enter_lowpower_en _bit_set(CPM->SLPCFGR, CPM_SLPCFGR_FLASH_IP_ENTER_LOWPOWER_EN)
#define _cpm_flash_ip_enter_lowpower_dis _bit_clr(CPM->SLPCFGR, CPM_SLPCFGR_FLASH_IP_ENTER_LOWPOWER_EN)
#define _cpm_set_sleep_conf(cnt) _reg_write(CPM->SLPCFGR, (cnt))
#define _cpm_get_sleep_conf _reg_read(CPM->SLPCFGR)

// sleep control:SLPCR
#define _cpm_set_sleep_conf_key(val) _reg_write(CPM->SLPCR, (val) & 0x3FFFFFFF)
#define _cpm_set_sleep_conf_mode _bit_set(CPM->SLPCR, CPM_SLPCR_SLEEP_CONF_MODE)

// system clock divider:SCDIVR
#define _cpm_set_core_clk_div(div) _reg_modify(CPM->SCDIVR, CPM_SCDIVR_CORE_DIV_MASK, (div) << CPM_SCDIVR_CORE_DIV_SHIFT_MASK)
#define _cpm_set_clkout_clk_div(div) _reg_modify(CPM->SCDIVR, CPM_SCDIVR_CLKOUT_DIV_MASK, (div) << CPM_SCDIVR_CLKOUT_DIV_SHIFT_MASK)
#define _cpm_set_trace_clk_div(div) _reg_modify(CPM->SCDIVR, CPM_SCDIVR_TRACE_DIV_MASK, (div) << CPM_SCDIVR_TRACE_DIV_SHIFT_MASK)
#define _cpm_set_sys_clk_div(div) _reg_modify(CPM->SCDIVR, CPM_SCDIVR_SYS_DIV_MASK, (div) << CPM_SCDIVR_SYS_DIV_SHIFT_MASK)
#define _cpm_get_sys_clk_value _reg_read(CPM->SCDIVR)

// peripheral clock divider register 1:PCDIVR1
#define _cpm_set_peripheral_sdram2lcd_clk_div(div) _reg_modify(CPM->PCDIVR1, CPM_PCDIVR_SDRAM2LCD_DIV_MASK, (div) << CPM_PCDIVR_SDRAM2LCD_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_arith_clk_div(div) _reg_modify(CPM->PCDIVR1, CPM_PCDIVR_ARITH_DIV_MASK, (div) << CPM_PCDIVR_ARITH_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_ahb3_clk_div(div) _reg_modify(CPM->PCDIVR1, CPM_PCDIVR_AHB3_DIV_MASK, (div) << CPM_PCDIVR_AHB3_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_ips_clk_div(div) _reg_modify(CPM->PCDIVR1, CPM_PCDIVR_IPS_DIV_MASK, (div) << CPM_PCDIVR_IPS_DIV_SHIFT_MASK)
#define _cpm_get_peripheral1_clk_div_value _reg_read(CPM->PCDIVR1)

// peripheral clock divider register 2:PCDIVR2
#define _cpm_set_peripheral_tc_clk_div(div) _reg_modify(CPM->PCDIVR2, CPM_PCDIVR_TC_DIV_MASK, (div) << CPM_PCDIVR_TC_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_mesh_clk_div(div) _reg_modify(CPM->PCDIVR2, CPM_PCDIVR_MESH_DIV_MASK, (div) << CPM_PCDIVR_MESH_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_adc_clk_div(div) _reg_modify(CPM->PCDIVR2, CPM_PCDIVR_ADC_DIV_MASK, (div) << CPM_PCDIVR_ADC_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_mcc_adr_clk_div(div) _reg_modify(CPM->PCDIVR2, CPM_PCDIVR_MCC_ADR_DIV_MASK, (div) << CPM_PCDIVR_MCC_ADR_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_mcc_clk_div(div) _reg_modify(CPM->PCDIVR2, CPM_PCDIVR_MCC_DIV_MASK, (div) << CPM_PCDIVR_MCC_DIV_SHIFT_MASK)
#define _cpm_set_peripheral_clcd_clk_div(div) _reg_modify(CPM->PCDIVR2, CPM_PCDIVR_CLCD_DIV_MASK, (div) << CPM_PCDIVR_CLCD_DIV_SHIFT_MASK)

// clock divider update register:CDIVUPDR
#define _cpm_update_sys_clk_div _bit_set(CPM->CDIVUPDR, CPM_CDIVUPDR_SYS_DIV_UPDATE)
#define _cpm_update_peripheral_clk_div _bit_set(CPM->CDIVUPDR, CPM_CDIVUPDR_PERIPHERAL_DIV_UPDATE)

// clock divider enable register:CDIVENR
#define _cpm_set_clkout_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_CLKOUT_CLK_DIV_EN)
#define _cpm_set_clkout_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_CLKOUT_CLK_DIV_EN)
#define _cpm_set_trace_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_TRACE_CLK_DIV_EN)
#define _cpm_set_trace_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_TRACE_CLK_DIV_EN)
#define _cpm_set_tc_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_TC_CLK_DIV_EN)
#define _cpm_set_tc_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_TC_CLK_DIV_EN)
#define _cpm_set_mesh_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_MESH_CLK_DIV_EN)
#define _cpm_set_mesh_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_MESH_CLK_DIV_EN)
#define _cpm_set_adc_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_ADC_CLK_DIV_EN)
#define _cpm_set_adc_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_ADC_CLK_DIV_EN)
#define _cpm_set_mcc_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_MCC_CLK_DIV_EN)
#define _cpm_set_mcc_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_MCC_CLK_DIV_EN)
#define _cpm_set_arith_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_TRACE_CLK_DIV_EN)
#define _cpm_set_arith_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_TRACE_CLK_DIV_EN)
#define _cpm_set_ahb3_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_AHB3_CLK_DIV_EN)
#define _cpm_set_ahb3_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_AHB3_CLK_DIV_EN)
#define _cpm_set_ips_clk_div_en _bit_set(CPM->CDIVENR, CPM_CDIVENR_IPS_CLK_DIV_EN)
#define _cpm_set_ips_clk_div_dis _bit_clr(CPM->CDIVENR, CPM_CDIVENR_IPS_CLK_DIV_EN)
#define _cpm_chk_ips_clk_div_en _reg_chk(CPM->CDIVENR, CPM_CDIVENR_IPS_CLK_DIV_EN)

// oscillator control and status register:OCSR
#define _cpm_set_trng_oscen_cnt(cnt) _reg_modify(CPM->OCSR, 0xF0FFFFFF, (cnt))
#define _cpm_set_pllnfc_clk_en _bit_set(CPM->OCSR, CPM_OCSR_PLLNFC_EN)
#define _cpm_set_pllnfc_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_PLLNFC_EN)
#define _cpm_set_pmu2k_clk_en _bit_set(CPM->OCSR, CPM_OCSR_PMU2K_CLK_EN)
#define _cpm_set_pmu2k_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_PMU2K_CLK_EN)
#define _cpm_set_rtc32k_clk_en _bit_set(CPM->OCSR, CPM_OCSR_RTC32K_CLK_EN)
#define _cpm_set_rtc32k_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_RTC32K_CLK_EN)
#define _cpm_set_oscext_clk_en _bit_set(CPM->OCSR, CPM_OCSR_OSCEXT_CLK_EN)
#define _cpm_set_oscext_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_OSCEXT_CLK_EN)
#define _cpm_set_osc400m_clk_en _bit_set(CPM->OCSR, CPM_OCSR_OSC400M_CLK_EN)
#define _cpm_set_osc400m_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_OSC400M_CLK_EN)
#define _cpm_set_usbphy240m_clk_en _bit_set(CPM->OCSR, CPM_OCSR_USBPHY240M_CLK_EN)
#define _cpm_set_usbphy240m_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_USBPHY240M_CLK_EN)
#define _cpm_set_pmu128k_clk_en _bit_set(CPM->OCSR, CPM_OCSR_PMU128K_CLK_EN)
#define _cpm_set_pmu128k_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_PMU128K_CLK_EN)
#define _cpm_set_osc8m_clk_en _bit_set(CPM->OCSR, CPM_OCSR_OSC8M_CLK_EN)
#define _cpm_set_osc8m_clk_dis _bit_clr(CPM->OCSR, CPM_OCSR_OSC8M_CLK_EN)
#define _cpm_get_pmu2k_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_PMU2K_STABLE)
#define _cpm_get_rtc32k_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_RTC32K_STABLE)
#define _cpm_get_oscext_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_OSCEXT_STABLE)
#define _cpm_get_osc400m_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_OSC400M_STABLE)
#define _cpm_get_usbphy240m_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_USBPHY240M_STABLE)
#define _cpm_get_pmu128k_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_OSC128K_STABLE)
#define _cpm_get_osc8m_stable_flag _reg_chk(CPM->OCSR, CPM_OCSR_OSC8M_STABLE)

// clock switch config register:CSWCFGR
#define _cpm_get_clkout_select_flag _reg_read(CPM->CSWCFGR)
#define _cpm_get_osc8m_select_flag _reg_chk(CPM->CSWCFGR, CPM_CSWCFGR_OSC8M_SELECT)
#define _cpm_get_osc400m_select_flag _reg_chk(CPM->CSWCFGR, CPM_CSWCFGR_OSC400M_SELECT)
#define _cpm_get_usbphy240m_select_flag _reg_chk(CPM->CSWCFGR, CPM_CSWCFGR_USBPHY240M_SELECT)
#define _cpm_get_oscext_select_flag _reg_chk(CPM->CSWCFGR, CPM_CSWCFGR_OSCEXT_SELECT)
#define _cpm_set_soc_clk_osc8m_en _reg_modify(CPM->CSWCFGR, CPM_CSWCFGR_SOC_CLK_SOURCE_MASK, 0)
#define _cpm_set_soc_clk_osc400m_en _reg_modify(CPM->CSWCFGR, CPM_CSWCFGR_SOC_CLK_SOURCE_MASK, 1)
#define _cpm_set_soc_clk_usbphy240m_en _reg_modify(CPM->CSWCFGR, CPM_CSWCFGR_SOC_CLK_SOURCE_MASK, 2)
#define _cpm_set_soc_clk_oscext_en _reg_modify(CPM->CSWCFGR, CPM_CSWCFGR_SOC_CLK_SOURCE_MASK, 3)
#define _cpm_set_clkout_source_sys_clk _reg_modify(CPM->CSWCFGR, 0xFCFFFFFF, CPM_CSWCFGR_CLKOUT_SOURCE_SYS)
#define _cpm_set_clkout_source_arith_clk _reg_modify(CPM->CSWCFGR, 0xFCFFFFFF, CPM_CSWCFGR_CLKOUT_SOURCE_ARITH)
#define _cpm_set_clkout_source_rtc32k_clk _reg_modify(CPM->CSWCFGR, 0xFCFFFFFF, CPM_CSWCFGR_CLKOUT_SOURCE_RTC32K)
#define _cpm_set_clkout_source_pllnfc_clk _reg_modify(CPM->CSWCFGR, 0xFCFFFFFF, CPM_CSWCFGR_CLKOUT_SOURCE_PLLNFC)
#define _cpm_set_clkout_source(source) _reg_modify(CPM->CSWCFGR, 0xFCFFFFFF, source << 24)
#define _cpm_chk_sys_clk_src(index) _reg_chk(CPM->CSWCFGR, (index))

// core tick timer register:CTICKR
#define _cpm_select_core_clk_reference_clk _bit_set(CPM->CTICKR, CPM_CTICKR_REFERENCE_CLK_SELECT_MASK)
#define _cpm_select_rtc32k_reference_clk _bit_clr(CPM->CTICKR, CPM_CTICKR_REFERENCE_CLK_SELECT_MASK)
#define _cpm_set_skew_en _bit_set(CPM->CTICKR, CPM_CTICKR_SKEW_EN)
#define _cpm_set_skew_dis _bit_clr(CPM->CTICKR, CPM_CTICKR_SKEW_EN)
#define _cpm_set_calibration_val(val) _reg_modify(CPM->CTICKR, 0xFF000000, (val) & 0x00FFFFFF)

// chip config register:CHIPCFGR
#define _cpm_select_usbphy_osc_mode(mode) _reg_modify(CPM->CHIPCFGR, 0x3FFFFFFF, (mode << 30))
#define _cpm_set_usbphy_conf_software_reset_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_CONF_SOFTWARE_MASK)
#define _cpm_set_usbphy_conf_software_reset_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_CONF_SOFTWARE_MASK)
#define _cpm_set_usbphy_pll_software_reset_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_PLL_SOFTWARE_MASK)
#define _cpm_set_usbphy_pll_software_reset_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_PLL_SOFTWARE_MASK)
#define _cpm_set_usbphy_ip_software_reset_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_IP_SOFTWARE_MASK)
#define _cpm_set_usbphy_ip_software_reset_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_IP_SOFTWARE_MASK)
#define _cpm_set_usbphy_input_isolation_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_INPUT_ISOLATION_EN)
#define _cpm_set_usbphy_input_isolation_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_INPUT_ISOLATION_EN)
// #define _cpm_set_usbphy_output_isolation_en       _bit_set(CPM->CHIPCFGR,CPM_CHIPCFGR_USBPHY_OUTPUT_ISOLATION_EN)
// #define _cpm_set_usbphy_output_isolation_dis      _bit_clr(CPM->CHIPCFGR,CPM_CHIPCFGR_USBPHY_OUTPUT_ISOLATION_EN)
#define _cpm_set_usbphy_reset_signal_mask_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_RESET_SIGNAL_MASK)
#define _cpm_set_usbphy_reset_signal_mask_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_RESET_SIGNAL_MASK)
#define _cpm_set_usbphy_power_switch_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_POWER_SWITCH_EN)
#define _cpm_set_usbphy_power_switch_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_USBPHY_POWER_SWITCH_EN)
#define _cpm_set_main_to_sub_system_int_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_MAIN_TO_SUB_SYSTEM_INT_EN)
#define _cpm_set_main_to_sub_system_int_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_MAIN_TO_SUB_SYSTEM_INT_EN)
#define _cpm_get_sub_to_main_system_int_flag _reg_chk(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_INT_FLAG)
#define _cpm_set_sub_to_main_system_int_flag_clr _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_INT_FLAG_CLR)
#define _cpm_set_sub_to_main_system_int_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_INT_EN)
#define _cpm_set_sub_to_main_system_int_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_INT_EN)
#define _cpm_set_sub_to_main_system_output_isolation_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_OUTPUT_ISOLATION_EN)
#define _cpm_set_sub_to_main_system_output_isolation_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_OUTPUT_ISOLATION_EN)
#define _cpm_set_sub_to_main_system_power_status_isolation_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_POWER_STATUS_ISOLATION_EN)
#define _cpm_set_sub_to_main_system_power_status_isolation_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_SUB_TO_MAIN_SYSTEM_POWER_STATUS_ISOLATION_EN)
#define _cpm_set_pci_h2l_isolation_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_PCI_H2L_ISOLATION_EN)
#define _cpm_set_pci_h2l_isolation_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_PCI_H2L_ISOLATION_EN)
#define _cpm_select_pci_h2l_isolation_cpm_module _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_PCI_H2L_ISOLATION_SEL_MASK)
#define _cpm_select_pci_h2l_isolation_pci_module _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_PCI_H2L_ISOLATION_SEL_MASK)
#define _cpm_set_rtc1s_clk_gate_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC1S_CLK_GATE_EN)
#define _cpm_set_rtc1s_clk_gate_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC1S_CLK_GATE_EN)
#define _cpm_set_rtc1k_clk_gate_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC1K_CLK_GATE_EN)
#define _cpm_set_rtc1k_clk_gate_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC1K_CLK_GATE_EN)
#define _cpm_set_rtc32k_clk_gate_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC32K_CLK_GATE_EN)
#define _cpm_set_rtc32k_clk_gate_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC32K_CLK_GATE_EN)
#define _cpm_set_rtc32k_isolation_en _bit_set(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC32K_ISOLATION_EN)
#define _cpm_set_rtc32k_isolation_dis _bit_clr(CPM->CHIPCFGR, CPM_CHIPCFGR_RTC32K_ISOLATION_EN)

// power control register:PWRCR
#define _cpm_set_vcc_io_latch_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_IO_LATCH_SET_MASK)
#define _cpm_set_vcc_io_latch_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_IO_LATCH_SET_MASK)
#define _cpm_clr_vcc_io_latch_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_IO_LATCH_CLR_MASK)
#define _cpm_clr_vcc_io_latch_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_IO_LATCH_CLR_MASK)
#define _cpm_set_vcc_3v3_lv_detect_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_3V3_LV_DETECT_EN)
#define _cpm_set_vcc_3v3_lv_detect_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_3V3_LV_DETECT_EN)
// #define _cpm_set_vcc_1v8_lv_detect_en             _bit_set(CPM->PWRCR,CPM_PWRCR_VCC_1V8_LV_DETECT_EN)
// #define _cpm_set_vcc_1v8_lv_detect_dis            _bit_clr(CPM->PWRCR,CPM_PWRCR_VCC_1V8_LV_DETECT_EN)
#define _cpm_set_card0_lv_detect_en _bit_set(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_EN)
#define _cpm_set_card0_lv_detect_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_EN)
#define _cpm_set_vcc_5v_lv_detect_output_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_5V_LV_DETECT_OUTPUT_EN)
#define _cpm_set_vcc_5v_lv_detect_output_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_5V_LV_DETECT_OUTPUT_EN)
#define _cpm_set_vcc_1v8_lv_detect_output_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_1V8_LV_DETECT_OUTPUT_EN)
#define _cpm_set_vcc_1v8_lv_detect_output_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_1V8_LV_DETECT_OUTPUT_EN)
#define _cpm_set_card0_lv_detect_output_en _bit_set(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_OUTPUT_EN)
#define _cpm_set_card0_lv_detect_output_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_OUTPUT_EN)
#define _cpm_set_vcc_5v_lv_detect_reset_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_5V_LV_DETECT_RESET_EN)
#define _cpm_set_vcc_5v_lv_detect_reset_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_5V_LV_DETECT_RESET_EN)
#define _cpm_set_vcc_1v8_lv_detect_reset_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_1V8_LV_DETECT_RESET_EN)
#define _cpm_set_vcc_1v8_lv_detect_reset_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_1V8_LV_DETECT_RESET_EN)
#define _cpm_set_card0_lv_detect_reset_en _bit_set(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_RESET_EN)
#define _cpm_set_card0_lv_detect_reset_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_RESET_EN)
#define _cpm_set_vcc_5v_lv_detect_int_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_5V_LV_DETECT_INT_EN)
#define _cpm_set_vcc_5v_lv_detect_int_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_5V_LV_DETECT_INT_EN)
#define _cpm_set_vcc_1v8_lv_detect_int_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_1V8_LV_DETECT_INT_EN)
#define _cpm_set_vcc_1v8_lv_detect_int_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_1V8_LV_DETECT_INT_EN)
#define _cpm_set_card0_lv_detect_int_en _bit_set(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_INT_EN)
#define _cpm_set_card0_lv_detect_int_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_CARD0_LV_DETECT_INT_EN)

#define _cpm_set_vcard0_interface_isolation_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCARD0_INTERFACE_ISOLATION_EN)
#define _cpm_set_vcard0_interface_isolation_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCARD0_INTERFACE_ISOLATION_EN)
#define _cpm_set_vcc_5v_ld_powerdown_en _bit_set(CPM->PWRCR, CPM_PWRCR_VCC_5V_LVD_POWERDOWN_MASK)
#define _cpm_set_vcc_5v_ld_powerdown_dis _bit_clr(CPM->PWRCR, CPM_PWRCR_VCC_5V_LVD_POWERDOWN_MASK)

// sleep counter register:SLPCNTR
#define _cpm_set_sleep_counter_0_cnt(cnt) _reg_modify(CPM->SLPCNTR, 0x00FFFFFF, ((cnt) & 0xFF) << 24)
#define _cpm_set_sleep_counter_1_cnt(cnt) _reg_modify(CPM->SLPCNTR, 0xFF00FFFF, ((cnt) & 0xFF) << 16)
#define _cpm_set_sleep_counter_2_cnt(cnt) _reg_modify(CPM->SLPCNTR, 0xFFFF00FF, ((cnt) & 0xFF) << 8)
#define _cpm_set_sleep_counter_3_cnt(cnt) _reg_modify(CPM->SLPCNTR, 0xFFFFFF00, (cnt) & 0xFF)
#define _cpm_set_sleep_counter_val(val) _reg_write(CPM->SLPCNTR, (val))

// wake up counter register:WKPCNTR
#define _cpm_set_wakeup_counter_0_cnt(cnt) _reg_modify(CPM->WKPCNTR, 0x00FFFFFF, ((cnt) & 0xFF) << 24)
#define _cpm_set_wakeup_counter_1_cnt(cnt) _reg_modify(CPM->WKPCNTR, 0xFF00FFFF, ((cnt) & 0xFF) << 16)
#define _cpm_set_wakeup_counter_2_cnt(cnt) _reg_modify(CPM->WKPCNTR, 0xFFFF00FF, ((cnt) & 0xFF) << 8)
#define _cpm_set_wakeup_counter_3_cnt(cnt) _reg_modify(CPM->WKPCNTR, 0xFFFFFF00, (cnt) & 0xFF)
#define _cpm_set_wakeup_counter_val(val) _reg_write(CPM->WKPCNTR, (val))

// multiple clock gate control register:MULTICGTCR
#define _cpm_set_multicgtcr_clk_on(index) _bit_set(CPM->MULTICGTCR, 1 << (index))
#define _cpm_set_multicgtcr_clk_off(index) _bit_clr(CPM->MULTICGTCR, 1 << (index))
#define _cpm_set_multicgtcr_val(val) _reg_write(CPM->MULTICGTCR, (val))
#define _cpm_chk_multicgtcr_clk_on(index) _reg_chk(CPM->MULTICGTCR, 1 << (index))

// system clock gate control register:SYSCGTCR
#define _cpm_set_syscgtcr_clk_on(index) _bit_set(CPM->SYSCGTCR, 1 << (index))
#define _cpm_set_syscgtcr_clk_off(index) _bit_clr(CPM->SYSCGTCR, 1 << (index))
#define _cpm_set_syscgtcr_val(val) _reg_write(CPM->SYSCGTCR, (val))
#define _cpm_chk_syscgtcr_clk_on(index) _reg_chk(CPM->SYSCGTCR, 1 << (index))

// ahb3 clock gate control registe:AHB3CGTCR
#define _cpm_set_ahb3cgtcr_clk_on(index) _bit_set(CPM->AHB3CGTCR, 1 << (index))
#define _cpm_set_ahb3cgtcr_clk_off(index) _bit_clr(CPM->AHB3CGTCR, 1 << (index))
#define _cpm_set_ahb3cgtcr_val(val) _reg_write(CPM->AHB3CGTCR, (val))
#define _cpm_chk_ahb3cgtcr_clk_on(index) _reg_chk(CPM->AHB3CGTCR, 1 << (index))

// arith clock gate control register:ARITHCGTCR
#define _cpm_get_arith_clk_state _reg_read(CPM->ARITHCGTCR)
#define _cpm_set_arithcgtcr_clk_on(index) _bit_set(CPM->ARITHCGTCR, 1 << (index))
#define _cpm_set_arithcgtcr_clk_off(index) _bit_clr(CPM->ARITHCGTCR, 1 << (index))
#define _cpm_set_arithcgtcr_val(val) _reg_write(CPM->ARITHCGTCR, (val))
#define _cpm_chk_arithcgtcr_clk_on(val) _reg_chk(CPM->ARITHCGTCR, 1 << (index))

// ips clock gate control register:IPSCGTCR
#define _cpm_set_ipscgtcr_clk_on(index) _bit_set(CPM->IPSCGTCR, 1 << (index))
#define _cpm_set_ipscgtcr_clk_off(index) _bit_clr(CPM->IPSCGTCR, 1 << (index))
#define _cpm_set_ipscgtcr_val(val) _reg_write(CPM->IPSCGTCR, (val))
#define _cpm_chk_ipscgtcr_clk_on(val) _reg_chk(CPM->IPSCGTCR, 1 << (index))

// vcc general trim register:VCCGTRIMR
#define _cpm_v33_sw_en _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_V33_SW_ENB)
#define _cpm_v33_sw_dis _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_V33_SW_ENB)
#define _cpm_v33_discharge_en _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_DISCHARGE_EN)
#define _cpm_v33_discharge_dis _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_DISCHARGE_EN)
#define _cpm_set_128khz_trim_value(val) _reg_modify(CPM->VCCGTRIMR, 0xE0FFFFFF, ((val) & 0x1F) << 24)
#define _cpm_set_2khz_trim_value(val) _reg_modify(CPM->VCCGTRIMR, 0xFFE0FFFF, ((val) & 0x1F) << 16)
#define _cpm_set_2khz_clk_gate_en _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_2KHZ_CLK_GATE_EN)
#define _cpm_set_2khz_clk_gate_dis _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_2KHZ_CLK_GATE_EN)
#define _cpm_set_core_voltage_0V9_on _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_CORE_VOLTAGE_MASK)
#define _cpm_set_core_voltage_0V9_off _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_CORE_VOLTAGE_MASK)
#define _cpm_set_vcc_latch_auto_set_on _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_VCC_LATCH_AUTO_SET_MASK)
#define _cpm_set_vcc_latch_auto_set_off _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_VCC_LATCH_AUTO_SET_MASK)
#define _cpm_set_vcc_latch_auto_clr_on _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_VCC_LATCH_AUTO_CLR_MASK)
#define _cpm_set_vcc_latch_auto_clr_off _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_VCC_LATCH_AUTO_CLR_MASK)
#define _cpm_set_sample_div(val) _reg_modify(CPM->VCCGTRIMR, 0xFFFFFCFF, ((val) & 0x03) << 8)
#define _cpm_set_bias1_res_trim_value(val) _reg_modify(CPM->VCCGTRIMR, 0xFFFFFF8F, ((val) & 0x07) << 4)
#define _cpm_set_ldo_trim_value(val) _reg_modify(CPM->VCCGTRIMR, 0xFFFFFFF3, ((val) & 0x03) << 2)
#define _cpm_set_bias2_res_trim_value(val) _reg_modify(CPM->VCCGTRIMR, 0xFFFFFFFC, (val) & 0x03)
#define _cpm_test_bias_current_en _bit_set(CPM->VCCGTRIMR, CPM_VCCGTRIMR_TEST_BIAS_CURRENT_EN)
#define _cpm_test_bias_current_dis _bit_clr(CPM->VCCGTRIMR, CPM_VCCGTRIMR_TEST_BIAS_CURRENT_EN)
#define _cpm_get_vcc_trim_value _reg_read(CPM->VCCGTRIMR)

// vcc lv detect trim register:VCCLTRIMR
#define _cpm_set_vcc_lvd_msb_value(val) _reg_modify(CPM->VCCLTRIMR, 0x3FFFFFFF, ((val) & 0x03) << 30)
#define _cpm_set_vcc5v_lvd_step_voltage(val) _reg_modify(CPM->VCCLTRIMR, 0xFFFFCFFF, ((val) & 0x03) << 12)
#define _cpm_set_vcc1v8_lvd_step_voltage(val) _reg_modify(CPM->VCCLTRIMR, 0xFFFFFFCF, ((val) & 0x03) << 4)
#define _cpm_set_vcc5v_lvd_trig_voltage(val) _reg_modify(CPM->VCCLTRIMR, 0xFFFFF8FF, ((val) & 0x07) << 8)
#define _cpm_set_vcc1v8_lvd_trig_voltage(val) _reg_modify(CPM->VCCLTRIMR, 0xFFFFFFF8, (val) & 0x07)
#define _cpm_set_vcc_coarse_lvd_module_en _bit_set(CPM->VCCLTRIMR, CPM_VCCLTRIMR_COARSE_LVD_MODULE_EN)
#define _cpm_set_vcc_coarse_lvd_module_dis _bit_clr(CPM->VCCLTRIMR, CPM_VCCLTRIMR_COARSE_LVD_MODULE_EN)

// vcc vref trim register:VCCVTRIMR
#define _cpm_set_sleep_conf_reg_protect_en _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_SLEEP_CONF_REG_PROTECT_EN)
#define _cpm_set_sleep_conf_reg_protect_dis _bit_clr(CPM->VCCVTRIMR, CPM_VCCVTRIMR_SLEEP_CONF_REG_PROTECT_EN)
#define _cpm_set_poff2_wakeup_source(src) _reg_modify(CPM->VCCVTRIMR, 0xFFF8FFFF, ((src) & 0x07) << 24)
#define _cpm_dis_sub_vdd_sram_power_signal _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_SUB_VDD_SRAM_POWER_MASK)
#define _cpm_dis_poff2_wakeup_source_usbdet _bit_clr(CPM->VCCVTRIMR, CPM_VCCVTRIMR_POFF2_WAKEUP_SOURCE_USBDET)
#define _cpm_dis_sub_vdd_power_signal _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_SUB_VDD_POWER_MASK)
#define _cpm_set_vref_stable _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_VREF_STABLE_MASK)
#define _cpm_set_vref_trim_en _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_VREF_TRIM_EN)
#define _cpm_set_vref_trim_dis _bit_clr(CPM->VCCVTRIMR, CPM_VCCVTRIMR_VREF_TRIM_EN)
#define _cpm_load_vref_trim_value _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_VREF_TRIM_VALUE_LOAD_BIT)
#define _cpm_store_vref_voltage_value_en _bit_set(CPM->VCCVTRIMR, CPM_VCCVTRIMR_STORE_VREF_VOLTAGE_VALUE_EN)
#define _cpm_store_vref_voltage_value_dis _bit_clr(CPM->VCCVTRIMR, CPM_VCCVTRIMR_STORE_VREF_VOLTAGE_VALUE_EN)
#define _cpm_set_vref_trim_value(val) _reg_modify(CPM->VCCVTRIMR, 0xFFFFFFF0, (val) & 0x0F)
#define _cpm_get_vcctrim_register_value _reg_read(CPM->VCCVTRIMR)
#define _cpm_set_vcctrim_register_value(val) _reg_write(CPM->VCCVTRIMR, val)

// vcc core test mode register:VCCCTMR
// #define _cpm_write_core_test_mode_key(key)        _reg_modify(CPM->VCCCTMR,0x3FFFFFFF,((key)&0x03)<<30)
#define _cpm_get_core_test_mode_value _reg_read(CPM->VCCCTMR)
#define _cpm_write_core_test_mode_value(val) _reg_write(CPM->VCCCTMR, (val))
#define _cpm_set_core_test_mode_value(val) _bit_set(CPM->VCCCTMR, (val))
#define _cpm_clr_core_test_mode_value(val) _bit_clr(CPM->VCCCTMR, (val))
#define _cpm_soft_por_reset _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_SOFT_POR)
#define _cpm_set_overwrite_cswcfgr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_CSWCFGR_TRIM_EN)
#define _cpm_set_overwrite_cswcfgr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_CSWCFGR_TRIM_EN)
#define _cpm_set_overwrite_cswcfgr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_CSWCFGR_TRIM_EN)
#define _cpm_set_overwrite_rtctrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_RTCTRIMR_TRIM_EN)
#define _cpm_set_overwrite_rtctrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_RTCTRIMR_TRIM_EN)
#define _cpm_set_overwrite_rtcstimer_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_RTCSTIMER_TRIM_EN)
#define _cpm_set_overwrite_rtcstimer_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_RTCSTIMER_TRIM_EN)
#define _cpm_set_overwrite_cardtrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_CARDTRIMR_TRIM_EN)
#define _cpm_set_overwrite_cardtrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_CARDTRIMR_TRIM_EN)
#define _cpm_set_overwrite_vccgtrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_VCCGTRIMR_TRIM_EN)
#define _cpm_set_overwrite_vccgtrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_VCCGTRIMR_TRIM_EN)
#define _cpm_set_overwrite_vccltrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_VCCLTRIMR_TRIM_EN)
#define _cpm_set_overwrite_vccltrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_VCCLTRIMR_TRIM_EN)
#define _cpm_set_overwrite_vccvtrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_VCCVTRIMR_TRIM_EN)
#define _cpm_set_overwrite_vccvtrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_VCCVTRIMR_TRIM_EN)
#define _cpm_set_overwrite_o8mtrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_O8MTRIMR_TRIM_EN)
#define _cpm_set_overwrite_o8mtrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_O8MTRIMR_TRIM_EN)
#define _cpm_set_overwrite_o320mtrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_O320MTRIMR_TRIM_EN)
#define _cpm_set_overwrite_o320mtrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_O320MTRIMR_TRIM_EN)
#define _cpm_set_overwrite_osclstrimr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OSCLSTIMER_TRIM_EN)
#define _cpm_set_overwrite_osclstrimr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OSCLSTIMER_TRIM_EN)
#define _cpm_set_overwrite_oschstimer_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OSCHSTIMER_TRIM_EN)
#define _cpm_set_overwrite_oschstimer_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OSCHSTIMER_TRIM_EN)
#define _cpm_set_overwrite_oscestimer_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OSCESTIMER_TRIM_EN)
#define _cpm_set_overwrite_oscestimer_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OSCESTIMER_TRIM_EN)
#define _cpm_set_overwrite_arithcgtcr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_ARITHCGTCR_TRIM_EN)
#define _cpm_set_overwrite_arithcgtcr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_ARITHCGTCR_TRIM_EN)
#define _cpm_set_overwrite_scdivr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_SCDIVR_TRIM_EN)
#define _cpm_set_overwrite_scdivr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_SCDIVR_TRIM_EN)
#define _cpm_set_overwrite_pcdivr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_PCDIVR_TRIM_EN)
#define _cpm_set_overwrite_pcdivr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_PCDIVR_TRIM_EN)
#define _cpm_set_overwrite_ocsr_trim_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OCSR_TRIM_EN)
#define _cpm_set_overwrite_ocsr_trim_dis _bit_clr(CPM->VCCCTMR, CPM_VCCCTMR_OVERWRITE_OCSR_TRIM_EN)
#define _cpm_set_cpu_core_test_mode_en _bit_set(CPM->VCCCTMR, CPM_VCCCTMR_CPU_CORE_TEST_MODE_EN)

// osc8mhz trim register:O8MTRIMR
#define _cpm_set_osc8mhz_trim_value(val) _reg_modify(CPM->O8MTRIMR, 0xFFFE0000, (val) & 0x0001FFFF)

// osc8mhz trim register:O320MTRIMR
#define _cpm_set_osc400mhz_trim_value(val) _reg_modify(CPM->O400MTRIMR, 0xFFFE0000, (val) & 0x0001FFFF)

// card ldo trim trgister:CARDTRIMR
#define _cpm_wakeup_filter_en _bit_set(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_FILTER_EN)
#define _cpm_wakeup_filter_dis _bit_clr(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_FILTER_EN)
#define _cpm_wakeup_filter_bypass_en _bit_set(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_FILTER_BYPASS_EN)
#define _cpm_wakeup_filter_bypass_dis _bit_clr(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_FILTER_BYPASS_EN)
#define _cpm_wakeup_filter_clk_gate_en _bit_set(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_FILTER_CLK_GATE_EN)
#define _cpm_wakeup_filter_clk_gate_dis _bit_clr(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_FILTER_CLK_GATE_EN)
#define _cpm_wakeup_analog_filter_bypass_en _bit_set(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_ANALOG_FILTER_BYPASS_EN)
#define _cpm_wakeup_analog_filter_bypass_dis _bit_clr(CPM->CARDTRIMR, CPM_CARDTRIMR_WAKEUP_ANALOG_FILTER_BYPASS_EN)
#define _cpm_wakeup_analog_filter_trim_value(val)       _reg_modify((CPM->CARDTRIMR,0xFFFFF0FF,((val)&0x0F)<<8)
#define _cpm_set_card0_sensor_resistance_reduce _bit_set(CPM->CARDTRIMR, CPM_CARDTRIMR_CARD0_SENSOR_RESISTANCE_REDUCE)

// oscl stable time register:OSCLSTIMER
#define _cpm_set_pmu128k_clk_stable_time_value(val) _reg_modify(CPM->OSCLSTIMER, 0xF000FFFF, ((val) & 0xFFF) << 16)
#define _cpm_set_osc8m_clk_stable_time_value(val) _reg_modify(CPM->OSCLSTIMER, 0xFFFFF000, (val) & 0xFFF)
#define _cpm_set_oscl_stable_time_value(val) _reg_write(CPM->OSCLSTIMER, (val))

// osch stable time register:OSCHSTIMER
#define _cpm_set_osc320m_clk_stable_time_value(val) _reg_modify(CPM->OSCHSTIMER, 0xF000FFFF, ((val) & 0xFFF) << 16)
#define _cpm_set_usb240m_clk_stable_time_value(val) _reg_modify(CPM->OSCHSTIMER, 0xFFFFF000, (val) & 0xFFF)
#define _cpm_set_osch_stable_time_value(val) _reg_write(CPM->OSCHSTIMER, (val))

// osce stable time register:OSCESTIMER
#define _cpm_set_oscext_clk_stable_time_value(val) _reg_modify(CPM->OSCESTIMER, 0xFFF00000, (val) & 0xFFFFF)

// power status register:PWRSR
#define _cpm_get_vcard_isolation_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_VCARD_ISOLATION_FLAG)
#define _cpm_get_vcc5v_lvd_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_VCC5V_LVD_FLAG)
#define _cpm_clr_vcc5v_lvd_flag _bit_set(CPM->PWRSR, CPM_PWRSR_VCC5V_LVD_FLAG)
#define _cpm_get_vcc1v8_lvd_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_VCC1V8_LVD_FLAG)
#define _cpm_clr_vcc1v8_lvd_flag _bit_set(CPM->PWRSR, CPM_PWRSR_VCC1V8_LVD_FLAG)
#define _cpm_get_card0_lvd_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_CARD0_LVD_FLAG)
#define _cpm_clr_card0_lvd_flag _bit_set(CPM->PWRSR, CPM_PWRSR_CARD0_LVD_FLAG)
#define _cpm_get_vcc5v_lvd_real_time_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_VCC5V_LVD_REAL_TIME_FLAG)
#define _cpm_get_vcc1v8_lvd_real_time_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_VCC1V8_LVD_REAL_TIME_FLAG)
#define _cpm_get_card0_lvd_real_time_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_CARD0_LVD_REAL_TIME_FLAG)
#define _cpm_get_card0_ldo_fail_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_CARD0_LVD_FAIL_FLAG)
#define _cpm_clr_card0_ldo_fail_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_CARD0_LVD_FAIL_FLAG)
#define _cpm_get_vcc_high_power_ready_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_VCC_HIGH_POWER_READY_FLAG)
#define _cpm_get_vcc_card0_ready_flag _reg_chk(CPM->PWRSR, CPM_PWRSR_CARD0_READY_FLAG)
// #define _cpm_get_main_to_sub_sys_rst_release_flag     _reg_chk(CPM->PWRSR,CPM_PWRSR_M2S_SYS_RST_RELEASE_FLAG)
// #define _cpm_get_main_to_sub_sys_bus_ready_flag       _reg_chk(CPM->PWRSR,CPM_PWRSR_M2S_SYS_BUS_READY_FLAG)
// #define _cpm_get_sub_sys_power_ready_flag             _reg_chk(CPM->PWRSR,CPM_PWRSR_SUB_POWER_READY_FLAG)
// #define _cpm_get_sub_sys_sram_status                  _reg_read(CPM->PWRSR)

// rtc trim register:RTCTRIMR
#define _cpm_set_rtc_trim_en _bit_set(CPM->RTCTRIMR, CPM_RTCTRIMR_RTC_TRIM_EN)
#define _cpm_set_rtc_trim_load_en _bit_set(CPM->RTCTRIMR, CPM_RTCTRIMR_RTC_TRIM_LOAD_EN)
#define _cpm_set_rtc_trim_value(val) _reg_modify(CPM->RTCTRIMR, 0xFFFFFF00, (val) & 0xFF)

// pad wakeup interrupt control register:PADWKINTCR
#define _cpm_get_s2m_wakeup_src_status _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_S2M_WAKEUP_SRC_STATUS)
#define _cpm_set_s2m_wakeup_src_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_S2M_WAKEUP_SRC_EN)
#define _cpm_set_s2m_wakeup_src_int_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_S2M_WAKEUP_SRC_INT_EN)
#define _cpm_get_s2m_wakeup_src_int_flag _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_S2M_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_s2m_wakeup_src_int_flag _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_S2M_WAKEUP_SRC_INT_FLAG)
#define _cpm_get_pad_ss3_wakeup_src_status _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_PAD_SS3_WAKEUP_SRC_STATUS)
#define _cpm_set_pad_ss3_wakeup_src_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PAD_SS3_WAKEUP_SRC_EN)
#define _cpm_set_pad_ss3_wakeup_src_int_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PAD_SS3_WAKEUP_SRC_INT_EN)
#define _cpm_get_pad_ss3_wakeup_src_int_flag _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_PAD_SS3_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_pad_ss3_wakeup_src_int_flag _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PAD_SS3_WAKEUP_SRC_INT_FLAG)
#define _cpm_get_pci_atimer_wakeup_src_status _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_STATUS)
#define _cpm_set_pci_atimer_wakeup_src_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_EN)
#define _cpm_set_pci_atimer_wakeup_src_int_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_INT_EN)
#define _cpm_get_pci_atimer_wakeup_src_int_flag _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_pci_atimer_wakeup_src_int_flag _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_INT_FLAG)
#define _cpm_get_pci_det_wakeup_src_status _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_STATUS)
#define _cpm_set_pci_det_wakeup_src_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_EN)
#define _cpm_set_pci_det_wakeup_src_int_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_INT_EN)
#define _cpm_get_pci_det_wakeup_src_int_flag _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_pci_det_wakeup_src_int_flag _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_INT_FLAG)
#define _cpm_get_wake_wakeup_src_status _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_WAKE_WAKEUP_SRC_STATUS)
#define _cpm_set_wake_wakeup_src_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_WAKE_WAKEUP_SRC_EN)
#define _cpm_set_wake_wakeup_src_int_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_WAKE_WAKEUP_SRC_INT_EN)
#define _cpm_get_wake_wakeup_src_int_flag _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_WAKE_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_wake_wakeup_src_int_flag _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_WAKE_WAKEUP_SRC_INT_FLAG)
#define _cpm_get_usb_det_wakeup_src_status _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_STATUS)
#define _cpm_set_usb_det_wakeup_src_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_EN)
#define _cpm_set_usb_det_wakeup_src_int_en _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_INT_EN)
#define _cpm_get_usb_det_wakeup_src_int_flag _reg_chk(CPM->PADWKINTCR, CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_usb_det_wakeup_src_int_flag _bit_set(CPM->PADWKINTCR, CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_INT_FLAG)
#define _cpm_clr_wakeup_src _reg_write(CPM->PADWKINTCR, 0)
#define _cpm_write_wakeup_src(val) _reg_write(CPM->PADWKINTCR, (val))
#define _cpm_get_wakeup_src _reg_read(CPM->PADWKINTCR)

// wakeup filter counter register:WKPFILTCNTR
#define _cpm_set_wakeup_filter_count0(cnt) _reg_modify(CPM->WKPFILTCNTR, 0x00FFFFFF, ((cnt) & 0xFF) << 24)
#define _cpm_set_wakeup_filter_count1(cnt) _reg_modify(CPM->WKPFILTCNTR, 0xFF00FFFF, ((cnt) & 0xFF) << 16)
#define _cpm_set_wakeup_filter_count2(cnt) _reg_modify(CPM->WKPFILTCNTR, 0xFFFF00FF, ((cnt) & 0xFF) << 8)
#define _cpm_set_wakeup_filter_count3(cnt) _reg_modify(CPM->WKPFILTCNTR, 0xFFFFFF00, (cnt) & 0xFF)
#define _cpm_set_wakeup_filter_val(val) _reg_write(CPM->WKPFILTCNTR, (val))

// card power on counter register:CARDPOCR
#define _cpm_set_card_poweron_wait_count(cnt) _reg_modify(CPM->CARDPOCR, 0xFFF00000, (cnt) & 0xFFFFF)

// rtc 32k stable time register:RTCSTIMER
#define _cpm_set_rtc32k_clk_stable_wait_count(cnt) _reg_modify(CPM->RTCSTIMER, 0xFFF00000, (cnt) & 0xFFFFF)

// memory power down sleep control register:MPDSLPCR
#define _cpm_enter_power_saving_mode_en(index) _bit_set(CPM->MPDSLPCR, 1 << (index))
#define _cpm_enter_power_saving_mode_dis(index) _bit_clr(CPM->MPDSLPCR, 1 << (index))

#define _cpm_write_power_saving_mode_register(val) _reg_write(CPM->MPDSLPCR, (val))

// multiple reset control register:MULTIRSTCR
#define _cpm_set_multi_module_reset_en(index) _bit_set(CPM->MULTIRSTCR, 1 << (index))
#define _cpm_set_multi_module_reset_dis(index) _bit_clr(CPM->MULTIRSTCR, 1 << (index))

// system reset control register:SYSRSTCR
#define _cpm_set_sys_module_reset_en(index) _bit_set(CPM->SYSRSTCR, 1 << (index))
#define _cpm_set_sys_module_reset_dis(index) _bit_clr(CPM->SYSRSTCR, 1 << (index))

// ahb3 reset control register:AHB3RSTCR
#define _cpm_set_ahb3_module_reset_en(index) _bit_set(CPM->AHB3RSTCR, 1 << (index))
#define _cpm_set_ahb3_module_reset_dis(index) _bit_clr(CPM->AHB3RSTCR, 1 << (index))

// arith reset control register:ARITHRSTTCR
#define _cpm_set_arith_module_reset_en(index) _bit_set(CPM->ARITHRSTTCR, 1 << (index))
#define _cpm_set_arith_module_reset_dis(index) _bit_clr(CPM->ARITHRSTTCR, 1 << (index))

// ips reset control register:IPRSTCR
#define _cpm_set_ips_module_reset_en(index) _bit_set(CPM->IPRSTCR, 1 << (index))
#define _cpm_set_ips_module_reset_dis(index) _bit_clr(CPM->IPRSTCR, 1 << (index))

// sleep config register 2:SLPCFGR2
#define _cpm_set_s2m_wakeup_src_sgl_int_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_S2M_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_s2m_wakeup_src_sgl_int_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_S2M_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_pad_ss3_wakeup_src_sgl_int_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_PAD_SS3_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_pad_ss3_wakeup_src_sgl_int_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_PAD_SS3_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_pci_atimer_wakeup_src_sgl_int_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_PCI_ATIMER_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_pci_atimer_wakeup_src_sgl_int_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_PCI_ATIMER_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_pci_det_wakeup_src_sgl_int_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_PCI_DET_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_pci_det_wakeup_src_sgl_int_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_PCI_DET_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_wake_wakeup_src_sgl_int_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_WAKE_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_wake_wakeup_src_sgl_int_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_WAKE_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_usb_det_wakeup_src_sgl_int_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_USB_DET_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_usb_det_wakeup_src_sgl_int_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_USB_DET_WAKEUP_SRC_SGL_INT_EN)
#define _cpm_set_core_f_clk_sleep_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_CORE_F_CLK_SLEEP_EN)
#define _cpm_set_core_f_clk_sleep_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_CORE_F_CLK_SLEEP_EN)
#define _cpm_set_clkout_clk_sleep_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_CLKOUT_CLK_SLEEP_EN)
#define _cpm_set_clkout_clk_sleep_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_CLKOUT_CLK_SLEEP_EN)
#define _cpm_set_cpm_ips_clk_sleep_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_CPM_IPS_CLK_SLEEP_EN)
#define _cpm_set_cpm_ips_clk_sleep_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_CPM_IPS_CLK_SLEEP_EN)
#define _cpm_set_tc_clk_sleep_en _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_TC_CLK_SLEEP_EN)
#define _cpm_set_tc_clk_sleep_dis _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_TC_CLK_SLEEP_EN)
#define _cpm_set_vddwk_power_domain_switch_on _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_VDDWK_POWER_DOMAIN_SWITCH_MASK)
#define _cpm_set_vddwk_power_domain_switch_off _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_VDDWK_POWER_DOMAIN_SWITCH_MASK)
#define _cpm_set_vddpd_power_domain_retention_on _bit_set(CPM->SLPCFGR2, CPM_SLPCFGR2_VDDPD_POWER_DOMAIN_RETENTION_MASK)
#define _cpm_set_vddpd_power_domain_retention_off _bit_clr(CPM->SLPCFGR2, CPM_SLPCFGR2_VDDPD_POWER_DOMAIN_RETENTION_MASK)

// power down counter register:PDNCNTR
#define _cpm_set_power_down_delay_count0(cnt) _reg_modify(CPM->PDNCNTR, 0x00FFFFFF, ((cnt) & 0xFF) << 24)
#define _cpm_set_power_down_delay_count1(cnt) _reg_modify(CPM->PDNCNTR, 0xFF00FFFF, ((cnt) & 0xFF) << 16)
#define _cpm_set_power_down_delay_count2(cnt) _reg_modify(CPM->PDNCNTR, 0xFFFF00FF, ((cnt) & 0xFF) << 8)
#define _cpm_set_power_down_delay_count3(cnt) _reg_modify(CPM->PDNCNTR, 0xFFFFFF00, (cnt) & 0xFF)

// power down counter register:PONCNTR
#define _cpm_set_power_on_delay_count0(cnt) _reg_modify(CPM->PONCNTR, 0x00FFFFFF, ((cnt) & 0xFF) << 24)
#define _cpm_set_power_on_delay_count1(cnt) _reg_modify(CPM->PONCNTR, 0xFF00FFFF, ((cnt) & 0xFF) << 16)
#define _cpm_set_power_on_delay_count2(cnt) _reg_modify(CPM->PONCNTR, 0xFFFF00FF, ((cnt) & 0xFF) << 8)
#define _cpm_set_power_on_delay_count3(cnt) _reg_modify(CPM->PONCNTR, 0xFFFFFF00, (cnt) & 0xFF)

// pad ss3 control register:PADSS3CR
#define _cpm_set_pad_ss3_control_en _bit_set(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_CONTROL_EN)
#define _cpm_set_pad_ss3_control_dis _bit_clr(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_CONTROL_EN)
#define _cpm_set_pad_ss3_wakeup_src_mask_en _bit_set(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_WAKEUP_SRC_MASK_EN)
#define _cpm_set_pad_ss3_wakeup_src_mask_dis _bit_clr(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_WAKEUP_SRC_MASK_EN)
#define _cpm_set_pad_ss3_output_high _bit_set(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_OUTPUT_HIGH_MASK)
#define _cpm_set_pad_ss3_output_low _bit_clr(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_OUTPUT_HIGH_MASK)
#define _cpm_set_pad_ss3_output_en _bit_set(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_OUTPUT_EN)
#define _cpm_set_pad_ss3_output_dis _bit_clr(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_OUTPUT_EN)
#define _cpm_set_pad_ss3_pull_en _bit_set(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_PULL_EN)
#define _cpm_set_pad_ss3_pull_dis _bit_clr(CPM_PADSS3CR, CPM_PADSS3CR_PAD_SS3_PULL_EN)

// wake up source control register:WKPSCR
#define _cpm_set_wakeup_src_en(index) _bit_set(CPM->WKPSCR, 1 << (index))
#define _cpm_set_wakeup_src_dis(index) _bit_clr(CPM->WKPSCR, 1 << (index))

#define _cpm_porset(value)      _reg_modify(CPM->LOCKUPRSTMASK, 0xFFFFFFF0, (value) & 0xFF) 
/**
 * @brief  CPM 模块选择枚举定义
 * 
 */
typedef enum
{
    SDRAM2LCD_MODULE = 0,
    LCDC_MODULE,
    DMA2D_MODULE,
    SDHOST_MODULE,
    MAC_MODULE,
    CRC1_MODULE,
    CRC0_MODULE,
    I2S_SLAVE_MODULE,
    I2S_MASTER_MODULE,
    TC_MODULE,
    PSRAM_MODULE,
    AXIDMA_MODULE,
    JEPG_MODULE,
    SSI6_MODULE,
    SSI5_MODULE,
    SSI4_MODULE,
    SD_EMMC_HOST,
    DMAC2_MODULE,
    DMAC1_MODULE,
    I2S2_MODULE,
    I2S1_MODULE,
    USBC_MODULE,
    AES_MODULE,
    SM4_MODULE,
    TRNG_MODULE,
    PWMT3_MODULE,
    PWMT2_PWMT3_MODULE,
    UART1_MODULE,
    UART2_MODULE,
    UART3_MODULE,
    UART4_MODULE,
    UART5_MODULE,
    UART6_MODULE,
    DAC_MODULE,
    ADC_MODULE,
    CAN1_MODULE,
    CAN2_MODULE,
    I2C1_MODULE,
    I2C2_MODULE,
    SPI1_MODULE,
    SPI2_MODULE,
    SPI3_MODULE,
    PIT1_MODULE,
    PIT2_MODULE,
    WDT_MODULE,
} cpm_module_t;

/**
 * @brief CPM 模块时钟trim选择枚举定义
 * 
 */
typedef enum
{
    OSC_320M_HZ = 0,
    OSC_400M_HZ,
    OSC_480M_HZ,
    OSC_500M_HZ
} cpm_sysclktrim_t;

/**
 * @brief CPM 模块USBPHY时钟源枚举定义
 * 
 */
typedef enum
{
    CPM_USBPHY_AUTO_DET = 0x00,
    CPM_USBPHY_INTER_OSC = 0x02,
    CPM_USBPHY_EXTER_OSC = 0x03
} cpm_usbphysrc_t;

/**
 * @brief CPM 模块系统电压Trim值枚举定义
 * 
 */
typedef enum
{
    CPM_VREF_TRIM_090 = 0x10,
    CPM_VREF_TRIM_105 = 0x00,
    CPM_VREF_TRIM_110 = 0x01,
    CPM_VREF_TRIM_115 = 0x02,
    CPM_VREF_TRIM_121 = 0x03
} cpm_vreftrimvalue_t;

/**
 * @brief CPM 模块系统时钟选择枚举定义
 * 
 */
typedef enum
{
    CPM_SYSCLK_OSC8M = 0,
    CPM_SYSCLK_OSC400M,
    CPM_SYSCLK_USBPHY240M,
    CPM_SYSCLK_OSCEXT
} cpm_sysclksel_t;

/**
 * @brief CPM 模块系统时钟分频枚举定义
 * 
 */
typedef enum
{
    CLK_DIV_1 = 0,
    CLK_DIV_2,
    CLK_DIV_3,
    CLK_DIV_4,
    CLK_DIV_5,
    CLK_DIV_6,
    CLK_DIV_7,
    CLK_DIV_8,
    CLK_DIV_9,
    CLK_DIV_10,
    CLK_DIV_11,
    CLK_DIV_12,
    CLK_DIV_13,
    CLK_DIV_14,
    CLK_DIV_15,
    CLK_DIV_16,
    CLK_DIV_17,
    CLK_DIV_18,
    CLK_DIV_19,
    CLK_DIV_20
} cpm_sysclkdiv_t,
    cpm_ipsclkdiv_t;

/**
 * @brief CPM时钟源索引定义
 * 
 */
typedef enum
{
    PAD_WAKEUP_INDEX_USBDET = 0x01,
    PAD_WAKEUP_INDEX_WAKE = 0x02,
} cpm_padwakeupindex_t;
extern __IO uint32_t g_core_clk;
extern __IO uint32_t g_sys_clk;
extern __IO uint32_t g_ips_clk;
extern __IO uint32_t g_ahb3_clk;
extern __IO uint32_t g_trim_clk;

// 函数声明
void drv_cpm_systemclk_osc8mselect(void);
void drv_cpm_systemclk_osc400mselect(void);
void drv_cpm_systemclk_osc240mselect(void);
void drv_cpm_systemclk_oscextselect(void);
void drv_cpm_vcccore_testmodekeyset(void);
void drv_cpm_vcccore_testmodeset(uint32_t val);
void drv_cpm_systemclkvreftrim(uint32_t trim_value);
void drv_cpm_moduleclkoff(uint8_t module_index);
void drv_cpm_moduleclkon(uint8_t module_index);
uint32_t drv_cpm_getcoreclk(void);
uint32_t drv_cpm_getsysclk(void);
uint32_t drv_cpm_getipsclk(void);
uint32_t drv_cpm_getahbclk(void);
void drv_cpm_setsysclkdiv(uint8_t core_div, uint8_t sys_div);
void drv_cpm_setclkoutsource(uint8_t source);
void drv_cpm_setclkoutdiv(uint8_t div);
void drv_cpm_setarithclkdiv(uint8_t div);
void drv_cpm_setahb3clkdiv(uint8_t div);
void drv_cpm_setipsclkdiv(uint8_t div);
void drv_cpm_settcclkdiv(uint8_t div);
void drv_cpm_setadcclkdiv(uint8_t div);
void drv_cpm_usbphyinit(uint8_t src_type);
void drv_cpm_usbphydeinit(void);
void drv_cpm_porreset(void);
void drv_cpm_lowpower(void);
void drv_cpm_poweroff(void);
void sys_standby(void);
void drv_cpm_irqhandler(void);
void drv_cpm_wakeupinit(cpm_padwakeupindex_t Src, functionalstate_t NewState);
void drv_cpm_module_reset(cpm_module_t module);
void drv_cpm_clktrim(uint32_t value);
void drv_cpm_setclcddiv(uint8_t clcd_dir);
void drv_cpm_sdram2lcd_module_set_div(uint8_t div);
void drv_cpm_porset(void);
uint32_t drv_cpm_gettrimclk(void);
#ifdef __cplusplus
}
#endif

#endif