/**
 *  @file cpm_reg.h
 *  @author Product application department
 *  @brief  CPM 模块寄存器配置文件
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __CPM_REG_H_
#define __CPM_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define CPM_BASE_ADDR (0x40004000)
#define CPM ((reg_cpm_t *)CPM_BASE_ADDR)

#define CPM_SLPCFGR_LOW_POWER_MODE ((uint32_t)(0 << 30))
#define CPM_SLPCFGR_RETENTION_MODE (((uint32_t)1 << 30))
#define CPM_SLPCFGR_DEEP_SLEEP_MODE (((uint32_t)1 << 30))
#define CPM_SLPCFGR_HIBERNATION_MODE (((uint32_t)1 << 31))
#define CPM_SLPCFGR_EPORT4_MODULE_CLOCK_SLEEP_EN (((uint32_t)1 << 28))
#define CPM_SLPCFGR_EPORT3_MODULE_CLOCK_SLEEP_EN (((uint32_t)1 << 27))
#define CPM_SLPCFGR_EPORT2_MODULE_CLOCK_SLEEP_EN (((uint32_t)1 << 26))
#define CPM_SLPCFGR_EPORT1_MODULE_CLOCK_SLEEP_EN (((uint32_t)1 << 22))
#define CPM_SLPCFGR_EPORT0_MODULE_CLOCK_SLEEP_EN (((uint32_t)1 << 21))
#define CPM_SLPCFGR_OSCEXT_SLEEP_EN (((uint32_t)1 << 20))
#define CPM_SLPCFGR_PMU128K_SLEEP_EN (((uint32_t)1 << 19))
#define CPM_SLPCFGR_RTC32K_SLEEP_EN (((uint32_t)1 << 16))
#define CPM_SLPCFGR_VDD33_LDO_ENTER_LOWPOWER_EN (((uint32_t)1 << 18))
#define CPM_SLPCFGR_FLASH_LDO_ENTER_LOWPOWER_EN (((uint32_t)1 << 17))
#define CPM_SLPCFGR_FLASH_LDO_ENTER_LOWPOWER_POWEROFF (((uint32_t)1 << 7))
#define CPM_SLPCFGR_FLASH_IP_ENTER_LOWPOWER_EN (((uint32_t)1 << 4))

#define CPM_SLPCR_SLEEP_CONF_MODE (((uint32_t)1 << 29))

// system clock divider register:SCDIVR 0x0008 ~ 0x000B
#define CPM_SCDIVR_CORE_DIV_SHIFT_MASK (((uint32_t)28))
#define CPM_SCDIVR_CORE_DIV_MASK ((uint32_t)(0x00FFFFFF))
#define CPM_SCDIVR_CLKOUT_DIV_MASK ((uint32_t)(0xFF00FFFF))
#define CPM_SCDIVR_CLKOUT_DIV_SHIFT_MASK (((uint32_t)16))
#define CPM_SCDIVR_TRACE_DIV_MASK ((uint32_t)(0xFFFF00FF))
#define CPM_SCDIVR_TRACE_DIV_SHIFT_MASK ((uint32_t)(8))
#define CPM_SCDIVR_SYS_DIV_MASK ((uint32_t)(0xFFFFFF00))
#define CPM_SCDIVR_SYS_DIV_SHIFT_MASK ((uint32_t)(0))

// periphal clock divider register 1:PCDIVR1 0x000C ~ 0x000F
#define CPM_PCDIVR_SDRAM2LCD_DIV_MASK ((uint32_t)(0x0FFFFFFF))
#define CPM_PCDIVR_SDRAM2LCD_DIV_SHIFT_MASK (((uint32_t)28))
#define CPM_PCDIVR_ARITH_DIV_MASK ((uint32_t)(0xFFFF0FFF))
#define CPM_PCDIVR_ARITH_DIV_SHIFT_MASK (((uint32_t)12))
#define CPM_PCDIVR_AHB3_DIV_MASK ((uint32_t)(0xFFFFF0FF))
#define CPM_PCDIVR_AHB3_DIV_SHIFT_MASK ((uint32_t)(8))
#define CPM_PCDIVR_IPS_DIV_MASK ((uint32_t)(0xFFFFFFF0))
#define CPM_PCDIVR_IPS_DIV_SHIFT_MASK ((uint32_t)(0))

// periphal clock divider register 2:PCDIVR2 0x0010 ~ 0x0013
#define CPM_PCDIVR_TC_DIV_MASK ((uint32_t)(0x0FFFFFFF))
#define CPM_PCDIVR_TC_DIV_SHIFT_MASK ((uint32_t)(28))
#define CPM_PCDIVR_MESH_DIV_MASK ((uint32_t)(0xF0FFFFFF))
#define CPM_PCDIVR_MESH_DIV_SHIFT_MASK ((uint32_t)(24))
#define CPM_PCDIVR_CLCD_DIV_MASK ((uint32_t)(0xFF00FFFF))
#define CPM_PCDIVR_CLCD_DIV_SHIFT_MASK (((uint32_t)16))
#define CPM_PCDIVR_ADC_DIV_MASK ((uint32_t)(0xFFFF0FFF))
#define CPM_PCDIVR_ADC_DIV_SHIFT_MASK (((uint32_t)12))
#define CPM_PCDIVR_MCC_ADR_DIV_MASK ((uint32_t)(0xFFFFF1FF))
#define CPM_PCDIVR_MCC_ADR_DIV_SHIFT_MASK ((uint32_t)(9))
#define CPM_PCDIVR_MCC_DIV_MASK ((uint32_t)(0xFFFFFE00))
#define CPM_PCDIVR_MCC_DIV_SHIFT_MASK ((uint32_t)(0)) /

// periphal clock divider register 3:PCDIVR3 0x0010 ~ 0x0013
// clock divider update register：CDIVUPDR 0x0018 ~ 0x001B
#define CPM_CDIVUPDR_SYS_DIV_UPDATE (((uint32_t)1 << 1))
#define CPM_CDIVUPDR_PERIPHERAL_DIV_UPDATE (((uint32_t)1 << 0))

// clock divider enable register：CDIVENR 0x001C ~ 0x001F
#define CPM_CDIVENR_I2S_S_DIVEN (((uint32_t)1 << 23))
#define CPM_CDIVENR_I2S_M_DIVEN (((uint32_t)1 << 22))
#define CPM_CDIVENR_CLKOUT_CLK_DIV_EN (((uint32_t)1 << 15))
#define CPM_CDIVENR_TRACE_CLK_DIV_EN (((uint32_t)1 << 14))
#define CPM_CDIVENR_TC_CLK_DIV_EN (((uint32_t)1 << 13))
#define CPM_CDIVENR_MESH_CLK_DIV_EN (((uint32_t)1 << 12))
#define CPM_CDIVENR_ADC_CLK_DIV_EN (((uint32_t)1 << 10))
#define CPM_CDIVENR_MCC_CLK_DIV_EN (((uint32_t)1 << 8))
#define CPM_CDIVENR_ARITH_CLK_DIV_EN (((uint32_t)1 << 3))
#define CPM_CDIVENR_AHB3_CLK_DIV_EN (((uint32_t)1 << 2))
#define CPM_CDIVENR_IPS_CLK_DIV_EN (((uint32_t)1 << 0))

// oscillator control and status register：OCSR 0x0020 ~ 0x0023
#define CPM_OCSR_TRNG_OSCEN ((uint32_t)(0xF << 24))
#define CPM_OCSR_PLLNFC_STABLE (((uint32_t)1 << 15))
#define CPM_OCSR_PMU2K_STABLE (((uint32_t)1 << 14))
#define CPM_OCSR_RTC32K_STABLE (((uint32_t)1 << 13))
#define CPM_OCSR_OSCEXT_STABLE (((uint32_t)1 << 12))
#define CPM_OCSR_OSC400M_STABLE (((uint32_t)1 << 11))
#define CPM_OCSR_USBPHY240M_STABLE (((uint32_t)1 << 10))
#define CPM_OCSR_PMU128K_STABLE (((uint32_t)1 << 9))
#define CPM_OCSR_OSC8M_STABLE (((uint32_t)1 << 8))
#define CPM_OCSR_PLLNFC_EN (((uint32_t)1 << 7))
#define CPM_OCSR_PMU2K_CLK_EN (((uint32_t)1 << 6))
#define CPM_OCSR_RTC32K_CLK_EN (((uint32_t)1 << 5))
#define CPM_OCSR_OSCEXT_CLK_EN (((uint32_t)1 << 4))
#define CPM_OCSR_OSC400M_CLK_EN (((uint32_t)1 << 3))
#define CPM_OCSR_USBPHY240M_CLK_EN (((uint32_t)1 << 2))
#define CPM_OCSR_PMU128K_CLK_EN (((uint32_t)1 << 1))
#define CPM_OCSR_OSC8M_CLK_EN (((uint32_t)1 << 0))

// clock switch config register: CSWCFGR 0x0024 ~ 0x0027
#define CPM_CSWCFGR_OSC8M_SELECT (((uint32_t)1 << 8))
#define CPM_CSWCFGR_OSC400M_SELECT (((uint32_t)1 << 9))
#define CPM_CSWCFGR_USBPHY240M_SELECT (((uint32_t)1 << 10))
#define CPM_CSWCFGR_OSCEXT_SELECT (((uint32_t)1 << 11))
#define CPM_CSWCFGR_SOC_CLK_SOURCE_MASK ((uint32_t)(0xFFFFFFFC))
#define CPM_CSWCFGR_CLKOUT_SOURCE_SYS ((uint32_t)(0 << 24))
#define CPM_CSWCFGR_CLKOUT_SOURCE_ARITH (((uint32_t)1 << 24))
#define CPM_CSWCFGR_CLKOUT_SOURCE_PLLNFC ((uint32_t)(2 << 24))
#define CPM_CSWCFGR_CLKOUT_SOURCE_OSCL ((uint32_t)(3 << 24))

// core tick timer register:CTICKR 0x0028 ~ 0x002B
#define CPM_CTICKR_REFERENCE_CLK_SELECT_MASK (((uint32_t)1 << 25))
#define CPM_CTICKR_SKEW_EN (((uint32_t)1 << 24))

// chip config register:CHIPCFGR:CHIPCFGR 0x002C ~ 0x002F
#define CPM_CHIPCFGR_USBPHY_OSC_MODE_AUTO ((uint32_t)(0 << 30))
#define CPM_CHIPCFGR_USBPHY_OSC_MODE_AUTO_FOR_SIMU (((uint32_t)1 << 30))
#define CPM_CHIPCFGR_USBPHY_OSC_MODE_INTER ((uint32_t)(2 << 30))
#define CPM_CHIPCFGR_USBPHY_OSC_MODE_EXTER ((uint32_t)(3 << 30))
#define CPM_CHIPCFGR_USBPHY_CONF_SOFTWARE_MASK (((uint32_t)1 << 29))
#define CPM_CHIPCFGR_USBPHY_PLL_SOFTWARE_MASK (((uint32_t)1 << 28))
#define CPM_CHIPCFGR_USBPHY_RESET_SIGNAL_MASK (((uint32_t)1 << 25))
#define CPM_CHIPCFGR_USBPHY_POWER_SWITCH_EN (((uint32_t)1 << 24))
#define CPM_CHIPCFGR_USBPHY_IP_SOFTWARE_MASK (((uint32_t)1 << 23))
#define CPM_CHIPCFGR_PCI_H2L_ISOLATION_SEL_MASK (((uint32_t)1 << 17))
#define CPM_CHIPCFGR_PCI_H2L_ISOLATION_EN (((uint32_t)1 << 16))
#define CPM_CHIPCFGR_RTC1S_CLK_GATE_EN (((uint32_t)1 << 14))
#define CPM_CHIPCFGR_RTC1K_CLK_GATE_EN (((uint32_t)1 << 13))
#define CPM_CHIPCFGR_RTC32K_CLK_GATE_EN (((uint32_t)1 << 12))
#define CPM_CHIPCFGR_RTC32K_ISOLATION_EN (((uint32_t)1 << 11))
#define CPM_CHIPCFGR_RIM_ARST_MASK (((uint32_t)1 << 10))
#define CPM_CHIPCFGR_RIM_RST_MASK (((uint32_t)1 << 9))
#define CPM_CHIPCFGR_RIM_SOFTRST_MASK (((uint32_t)1 << 8))
#define CPM_CHIPCFGR_USBPHY_12M_EN_MASK (((uint32_t)1 << 3))
#define CPM_CHIPCFGR_OSCEXT_PAD_TE (((uint32_t)1 << 2))
#define CPM_CHIPCFGR_OSCEXT_PAD_SF ((uint32_t)(3 << 0))

// power control register:PWRCR 0x0030 ~ 0x0033
#define CPM_PWRCR_VCC_IO_LATCH_CLR_MASK ((uint32_t)1 << 31)
#define CPM_PWRCR_VCC_IO_LATCH_SET_MASK ((uint32_t)1 << 30)
#define CPM_PWRCR_VCC_3V3_LV_DETECT_RESET_EN (((uint32_t)1 << 29))
#define CPM_PWRCR_VCARD0_INTERFACE_ISOLATION_EN (((uint32_t)1 << 25))
#define CPM_PWRCR_VCC_3V3_LVD_POWERDOWN_MASK (((uint32_t)1 << 23))
#define CPM_PWRCR_CARD0_LV_DETECT_RESET_EN (((uint32_t)1 << 9))
#define CPM_PWRCR_VCC_3V3_LV_DETECT_INT_EN (((uint32_t)1 << 15))
#define CPM_PWRCR_CARD0_LV_DETECT_INT_EN (((uint32_t)1 << 13))
#define CPM_PWRCR_CARD0_IE_EN_FAIL (((uint32_t)1 << 11))
#define CPM_PWRCR_CARD0_RE_LVD (((uint32_t)1 << 9))
#define CPM_PWRCR_VCC_OE_LVDT33 (((uint32_t)1 << 7))
#define CPM_PWRCR_CARD0_OE_LVD (((uint32_t)1 << 5))
#define CPM_PWRCR_VCC_3V3_LV_DETECT_EN (((uint32_t)1 << 3))
#define CPM_PWRCR_CARD0_LV_DETECT_EN (((uint32_t)1 << 1))

// vcc general trim register:VCCGTRIMR 0x0050 ~ 0x0053
#define CPM_VCCGTRIMR_DISCHARGE_EN (((uint32_t)1 << 30))
#define CPM_VCCGTRIMR_2KHZ_CLK_GATE_EN (((uint32_t)1 << 23))
#define CPM_VCCGTRIMR_CORE_VOLTAGE_MASK (((uint32_t)1 << 15))
#define CPM_VCCGTRIMR_VCC_LATCH_AUTO_SET_MASK (((uint32_t)1 << 13))
#define CPM_VCCGTRIMR_VCC_LATCH_AUTO_CLR_MASK (((uint32_t)1 << 12))
#define CPM_VCCGTRIMR_VCC_LATCH_AUTO_PORCLR (((uint32_t)1 << 11))
#define CPM_VCCGTRIMR_TEST_BIAS_CURRENT_EN (((uint32_t)1 << 7))

// vcc lv detect trim register:VCCLTRIMR 0x0054 ~ 0x0057
#define CPM_VCCLTRIMR_OTP_LVDT_MASK (((uint32_t)1 << 25))
#define CPM_VCCLTRIMR_COARSE_LVD_MODULE_EN (((uint32_t)1 << 24))

// vcc vref trim register:VCCVTRIMR 0x0058 ~ 0x005B
#define CPM_VCCVTRIMR_SLEEP_CONF_REG_PROTECT_EN (((uint32_t)1 << 31))
#define CPM_VCCVTRIMR_POFF2_WAKEUP_SOURCE_USBDET (((uint32_t)1 << 16))
#define CPM_VCCVTRIMR_VREF_STABLE_MASK (((uint32_t)1 << 11))
#define CPM_VCCVTRIMR_VREF_TRIM_EN (((uint32_t)1 << 10))
#define CPM_VCCVTRIMR_VREF_TRIM_VALUE_LOAD_BIT (((uint32_t)1 << 9))
#define CPM_VCCVTRIMR_STORE_VREF_VOLTAGE_VALUE_EN (((uint32_t)1 << 8))

// vcc core test mode register:VCCCTMR 0x005C ~ 0x005F
#define CPM_VCCCTMR_OVERWRITE_CSWCFGR_TRIM_EN (((uint32_t)1 << 29))
#define CPM_VCCCTMR_OVERWRITE_RTCTRIMR_TRIM_EN (((uint32_t)1 << 28))
#define CPM_VCCCTMR_OVERWRITE_RTCSTIMER_TRIM_EN (((uint32_t)1 << 26))
#define CPM_VCCCTMR_OVERWRITE_CARDTRIMR_TRIM_EN (((uint32_t)1 << 24))
#define CPM_VCCCTMR_OVERWRITE_VCCGTRIMR_TRIM_EN (((uint32_t)1 << 23))
#define CPM_VCCCTMR_OVERWRITE_VCCLTRIMR_TRIM_EN (((uint32_t)1 << 22))
#define CPM_VCCCTMR_OVERWRITE_VCCVTRIMR_TRIM_EN (((uint32_t)1 << 21))
#define CPM_VCCCTMR_OVERWRITE_O8MTRIMR_TRIM_EN (((uint32_t)1 << 20))
#define CPM_VCCCTMR_OVERWRITE_O320MTRIMR_TRIM_EN (((uint32_t)1 << 19))
#define CPM_VCCCTMR_OVERWRITE_OSCLSTIMER_TRIM_EN (((uint32_t)1 << 18))
#define CPM_VCCCTMR_OVERWRITE_OSCHSTIMER_TRIM_EN (((uint32_t)1 << 17))
#define CPM_VCCCTMR_OVERWRITE_OSCESTIMER_TRIM_EN (((uint32_t)1 << 16))
#define CPM_VCCCTMR_OVERWRITE_ARITHCGTCR_TRIM_EN (((uint32_t)1 << 13))
#define CPM_VCCCTMR_OVERWRITE_SCDIVR_TRIM_EN (((uint32_t)1 << 11))
#define CPM_VCCCTMR_OVERWRITE_PCDIVR_TRIM_EN (((uint32_t)1 << 10))
#define CPM_VCCCTMR_OVERWRITE_OCSR_TRIM_EN (((uint32_t)1 << 9))
#define CPM_VCCCTMR_CPU_CORE_TEST_MODE_EN (((uint32_t)1 << 7))
#define CPM_VCCCTMR_SOFT_POR (((uint32_t)1 << 3))
#define CPM_VCCCTMR_OFF_MODE2 (((uint32_t)1 << 2))
#define CPM_VCCCTMR_EN_LP (((uint32_t)1 << 0))

// card ldo trim trgister:CARDTRIMR 0x006C ~ 0x006F
#define CPM_CARDTRIMR_WAKEUP_FILTER_EN (((uint32_t)1 << 30))
#define CPM_CARDTRIMR_WAKEUP_FILTER_BYPASS_EN (((uint32_t)1 << 29))
#define CPM_CARDTRIMR_WAKEUP_FILTER_CLK_GATE_EN (((uint32_t)1 << 28))
#define CPM_CARDTRIMR_WAKEUP_VDD33_PSWEN (((uint32_t)1 << 24))
#define CPM_CARDTRIMR_WAKEUP_ANALOG_FILTER_BYPASS_EN (((uint32_t)1 << 15))
#define CPM_CARDTRIMR_CARD0_REDUCE (((uint32_t)1 << 13))

// power status register:PWRSR 0x007C ~ 0x007F
#define CPM_PWRSR_VCARD_ISOLATION_FLAG (((uint32_t)1 << 26))
#define CPM_PWRSR_VCC3V3_LVD_FLAG (((uint32_t)1 << 23))
#define CPM_PWRSR_CARD0_LVD_FLAG (((uint32_t)1 << 21))
#define CPM_PWRSR_VCC3V3_LVD_REAL_TIME_FLAG (((uint32_t)1 << 19))
#define CPM_PWRSR_CARD0_LVD_REAL_TIME_FLAG (((uint32_t)1 << 17))
#define CPM_PWRSR_CARD0_LVD_FAIL_FLAG (((uint32_t)1 << 15))
#define CPM_PWRSR_VCC_HIGH_POWER_READY_FLAG (((uint32_t)1 << 3))
#define CPM_PWRSR_CARD0_READY_FLAG (((uint32_t)1 << 2))

// rtc trim register:RTCTRIMR 0x008C~ 0x008F
#define CPM_RTCTRIMR_RTC_TRIM_EN (((uint32_t)1 << 31))
#define CPM_RTCTRIMR_RTC_TRIM_LOAD_EN (((uint32_t)1 << 30))

// pad wakeup interrupt control register:PADWKINTCR 0x0090~ 0x0093
#define CPM_PADWKINTCR_RIM_ARST_RT (((uint32_t)1 << 31))
#define CPM_PADWKINTCR_DBG_PWRUP_RT (((uint32_t)1 << 30))
#define CPM_PADWKINTCR_ISORST_RT (((uint32_t)1 << 29))
#define CPM_PADWKINTCR_TCRST_RT (((uint32_t)1 << 28))
#define CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_STATUS (((uint32_t)1 << 27))
#define CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_STATUS (((uint32_t)1 << 26))
#define CPM_PADWKINTCR_WAKE_WAKEUP_SRC_STATUS (((uint32_t)1 << 25))
#define CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_STATUS (((uint32_t)1 << 24))
#define CPM_PADWKINTCR_RIM_ARST_EN (((uint32_t)1 << 23))
#define CPM_PADWKINTCR_DBG_PWRUP_EN (((uint32_t)1 << 22))
#define CPM_PADWKINTCR_ISORST_EN (((uint32_t)1 << 21))
#define CPM_PADWKINTCR_TCRST_EN                            (((uint32_t)1<<20)
#define CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_EN (((uint32_t)1 << 19))
#define CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_EN (((uint32_t)1 << 18))
#define CPM_PADWKINTCR_WAKE_WAKEUP_SRC_EN (((uint32_t)1 << 17))
#define CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_EN (((uint32_t)1 << 16))
#define CPM_PADWKINTCR_RIM_ARST_INTM (((uint32_t)1 << 15))
#define CPM_PADWKINTCR_DBG_PWRUP_INTM (((uint32_t)1 << 14))
#define CPM_PADWKINTCR_ISORST_INTM (((uint32_t)1 << 13))
#define CPM_PADWKINTCR_TCRST_INTM (((uint32_t)1 << 12))
#define CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_INT_EN (((uint32_t)1 << 11))
#define CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_INT_EN (((uint32_t)1 << 10))
#define CPM_PADWKINTCR_WAKE_WAKEUP_SRC_INT_EN (((uint32_t)1 << 9))
#define CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_INT_EN (((uint32_t)1 << 8))
#define CPM_PADWKINTCR_RIM_ARST_STAT (((uint32_t)1 << 7))
#define CPM_PADWKINTCR_DBG_PWRUP_STAT (((uint32_t)1 << 6))
#define CPM_PADWKINTCR_ISORST_STAT (((uint32_t)1 << 5))
#define CPM_PADWKINTCR_TCRST_STAT (((uint32_t)1 << 4))
#define CPM_PADWKINTCR_PCI_ATIMER_WAKEUP_SRC_INT_FLAG (((uint32_t)1 << 3))
#define CPM_PADWKINTCR_PCI_DET_WAKEUP_SRC_INT_FLAG (((uint32_t)1 << 2))
#define CPM_PADWKINTCR_WAKE_WAKEUP_SRC_INT_FLAG (((uint32_t)1 << 1))
#define CPM_PADWKINTCR_USB_DET_WAKEUP_SRC_INT_FLAG (((uint32_t)1 << 0))

// sleep config register 2:SLPCFGR2 0x00C0 ~ 0x00C3
#define CPM_SLPCFGR2_RIM_ARST_INTM_SGL (((uint32_t)1 << 23))
#define CPM_SLPCFGR2_DBG_PWRUP_INTM_SGL (((uint32_t)1 << 22))
#define CPM_SLPCFGR2_ISORST_INTM_SGL (((uint32_t)1 << 21))
#define CPM_SLPCFGR2_TCRST_INTM_SGL (((uint32_t)1 << 20))
#define CPM_SLPCFGR2_PCI_ATIMER_WAKEUP_SRC_SGL_INT_EN (((uint32_t)1 << 19))
#define CPM_SLPCFGR2_PCI_DET_WAKEUP_SRC_SGL_INT_EN (((uint32_t)1 << 18))
#define CPM_SLPCFGR2_WAKE_WAKEUP_SRC_SGL_INT_EN (((uint32_t)1 << 17))
#define CPM_SLPCFGR2_USB_DET_WAKEUP_SRC_SGL_INT_EN (((uint32_t)1 << 16))
#define CPM_SLPCFGR2_TRNG_SLPEN (((uint32_t)1 << 15))
#define CPM_SLPCFGR2_OTP_IDLE_WKPWAIT (((uint32_t)1 << 14))
#define CPM_SLPCFGR2_OTP_IDLE_SLPWAIT (((uint32_t)1 << 13))
#define CPM_SLPCFGR2_CACHE_IDLE_SLPWAIT (((uint32_t)1 << 12))
#define CPM_SLPCFGR2_CORE_F_CLK_SLEEP_EN (((uint32_t)1 << 11))
#define CPM_SLPCFGR2_CLKOUT_CLK_SLEEP_EN (((uint32_t)1 << 10))
#define CPM_SLPCFGR2_CPM_IPS_CLK_SLEEP_EN (((uint32_t)1 << 9))
#define CPM_SLPCFGR2_TC_CLK_SLEEP_EN (((uint32_t)1 << 8))
#define CPM_SLPCFGR2_PMURTC_SLPEN (((uint32_t)1 << 7))
#define CPM_SLPCFGR2_CAN_IDLE_SLPWAIT (((uint32_t)1 << 6))

// pll nfc config register 4:PLLNFCCFGR 0x00E0 ~ 0x00E3
#define CPM_PLLNFCCFGR_TEST_PORT_EN (((uint32_t)1 << 26))
#define CPM_PLLNFCCFGR_TEST_EN (((uint32_t)1 << 25))
#define CPM_PLLNFCCFGR_EN_XTAL (((uint32_t)1 << 24))

/**
 * @brief CPM 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t SLPCFGR;
    __IO uint32_t SLPCR;
    __IO uint32_t SCDIVR;
    __IO uint32_t PCDIVR1;

    __IO uint32_t PCDIVR2;
    __IO uint32_t PCDIVR3;
    __IO uint32_t CDIVUPDR;
    __IO uint32_t CDIVENR;

    __IO uint32_t OCSR;
    __IO uint32_t CSWCFGR;
    __IO uint32_t CTICKR;
    __IO uint32_t CHIPCFGR;

    __IO uint32_t PWRCR;
    __IO uint32_t SLPCNTR;
    __IO uint32_t WKPCNTR;
    __IO uint32_t MULTICGTCR;

    __IO uint32_t SYSCGTCR;
    __IO uint32_t AHB3CGTCR;
    __IO uint32_t ARITHCGTCR;
    __IO uint32_t IPSCGTCR;
    __IO uint32_t VCCGTRIMR;
    __IO uint32_t VCCLTRIMR;
    __IO uint32_t VCCVTRIMR;
    __IO uint32_t VCCCTMR;

    __IO uint32_t O8MTRIMR;
    __IO uint32_t RESERVED1;
    __IO uint32_t O400MTRIMR;
    __IO uint32_t CARDTRIMR;

    __IO uint32_t OSCLSTIMER;
    __IO uint32_t OSCHSTIMER;
    __IO uint32_t OSCESTIMER;
    __IO uint32_t PWRSR;
    __IO uint32_t EPORTSLPCFGR;
    __IO uint32_t EPORTCGTR;
    __IO uint32_t EPORTRSTCR;
    __IO uint32_t RTCTRIMR;
    __IO uint32_t PADWKINTCR;
    __IO uint32_t WKPFILTCNTR;
    __IO uint32_t CARDPOCR;
    __IO uint32_t RTCSTIMER;

    __IO uint32_t MPDSLPCR;
    __IO uint32_t RESERVED2[2];
    __IO uint32_t MULTIRSTCR;

    __IO uint32_t SYSRSTCR;
    __IO uint32_t AHB3RSTCR;
    __IO uint32_t ARITHRSTTCR;
    __IO uint32_t IPRSTCR;
    __IO uint32_t SLPCFGR2;
    __IO uint32_t RESERVED3[3];

    __IO uint32_t PDNCNTR;
    __IO uint32_t PONCNTR;
    __IO uint32_t PCDIVR4;
    __IO uint32_t RESERVED4;
    __IO uint32_t RESERVED5;
    __IO uint32_t PLLNFCCFGR;
    __IO uint32_t PLLNFCSTIMER;
    __IO uint32_t LOCKUPRSTMASK;	
} reg_cpm_t;

#ifdef __cplusplus
}
#endif


#endif
