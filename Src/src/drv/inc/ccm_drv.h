/**
 * @file ccm_drv.h
 * @author Product application department
 * @brief  CCM 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __CCM_DRV_H
#define __CCM_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "ccm_reg.h"

// 全局变量定义
#define _ccm_set_bmt(ccm, value) _reg_modify(ccm->CCR, 0xfffc, value)
#define _ccm_en_bmd(ccm) _bit_set(ccm->CCR, CCM_CCR_BMD)
#define _ccm_dis_bmd(ccm) _bit_clr(ccm->CCR, CCM_CCR_BMD)
#define _ccm_en_bme(ccm) _bit_set(ccm->CCR, CCM_CCR_BME)
#define _ccm_dis_bme(ccm) _bit_clr(ccm->CCR, CCM_CCR_BME)
#define _ccm_en_shint(ccm) _bit_set(ccm->CCR, CCM_CCR_SHINT)
#define _ccm_dis_shint(ccm) _bit_clr(ccm->CCR, CCM_CCR_SHINT)
#define _ccm_en_periph_bridge_pae(ccm) _bit_set(ccm->CCR, CCM_CCR_PERIPH_BRIDGE_PAE)
#define _ccm_dis_periph_bridge_pae(ccm) _bit_clr(ccm->CCR, CCM_CCR_PERIPH_BRIDGE_PAE)
#define _ccm_en_periph_bridge_rae(ccm) _bit_set(ccm->CCR, CCM_CCR_PERIPH_BRIDGE_RAE)
#define _ccm_dis_periph_bridge_rae(ccm) _bit_clr(ccm->CCR, CCM_CCR_PERIPH_BRIDGE_RAE)
#define _ccm_dis_jtag(ccm) _bit_set(ccm->CCR, CCM_CCR_JTAGDIS)
#define _ccm_en_jtag(ccm) _bit_clr(ccm->CCR, CCM_CCR_JTAGDIS)
#define _ccm_dis_test(ccm) _bit_set(ccm->CCR, CCM_CCR_TESTDIS)
#define _ccm_en_test(ccm) _bit_clr(ccm->CCR, CCM_CCR_TESTDIS)
#define _ccm_get_ccr_all(ccm) _reg_read(ccm->CCR)

#define _ccm_en_phy_pll(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_PLL_EN)
#define _ccm_dis_phy_pll(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_PLL_EN)
#define _ccm_en_phy_reg(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_REG_EN)
#define _ccm_dis_phy_reg(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_REG_EN)
#define _ccm_en_suspendm(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_SUSPENDM)
#define _ccm_dis_suspendm(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_SUSPENDM)
#define _ccm_select_term_reg(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_TERMSEL_DIR)
#define _ccm_select_term_USBC(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_TERMSEL_DIR)
#define _ccm_en_term(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_TERMSEL)
#define _ccm_dis_term(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_TERMSEL)
#define _ccm_select_phy_dir_reg(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_DIR)
#define _ccm_select_phy_dir_USBC(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_DIR)
#define _ccm_en_clk_12M(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_12M_EN_SEL)
#define _ccm_dis_clk_12M(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_12M_EN_SEL)
#define _ccm_select_phyreg_en_phypa(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USBPHY_REG_EN_SEL)
#define _ccm_select_phyreg_en_USBC(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USBPHY_REG_EN_SEL)
#define _ccm_en_phy_sessendvalid(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_SESSENDVALID)
#define _ccm_dis_phy_sessendvalid(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_SESSENDVALID)
#define _ccm_en_phy_avalid(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_AVALID)
#define _ccm_dis_phy_avalid(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_AVALID)
#define _ccm_en_phy_vbusvalid(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_VBUSVALID)
#define _ccm_dis_phy_vbusvalid(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_VBUSVALID)
#define _ccm_select_valid_dir_reg(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_VALID_DIR)
#define _ccm_select_valid_dir_USBC(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_VALID_DIR)
#define _ccm_select_phy_id_reg(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_ID_DIR)
#define _ccm_select_phy_id_USBC(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_ID_DIR)
#define _ccm_en_phy_id_pullup(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_ID_PULLUP)
#define _ccm_dir_phy_id_pullup(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_ID_PULLUP)
#define _ccm_select_resume_signal_LineState_powerState(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_PHY_RESUME_SEL)
#define _ccm_select_resume_signal_LineState(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_PHY_RESUME_SEL)
#define _ccm_select_little_endian(ccm) _bit_set(ccm->PHYPA, CCM_PHYPA_USB_REG_ENDIAN)
#define _ccm_select_big_endian(ccm) _bit_clr(ccm->PHYPA, CCM_PHYPA_USB_REG_ENDIAN)
#define _ccm_get_phypa_all(ccm) _reg_read(ccm->PHYPA)

#define _ccm_en_tdo_pull(ccm) _bit_set(ccm->PCFG3, CCM_PCFG3_TDO_PUE)
#define _ccm_dis_tdo_pull(ccm) _bit_clr(ccm->PCFG3, CCM_PCFG3_TDO_PUE)
#define _ccm_get_pcfg3_all(ccm) _reg_read(ccm->PCFG3)

#define _ccm_set_rstout_clkout_ds(ccm, value) _reg_modify(ccm->RSTCLKCFG, 0xffffffcf, value)
#define _ioctrl_rstout_clkout_slew_slow(ccm) _bit_set(ccm->RSTCLKCFG, CCM_RSTCLKCFG_RSTOUT_CLKOUT_SR)
#define _ioctrl_rstout_clkout_slew_fast(ccm) _bit_clr(ccm->RSTCLKCFG, CCM_RSTCLKCFG_RSTOUT_CLKOUT_SR)
#define _ccm_en_rstout_clkout_is(ccm) _bit_set(ccm->RSTCLKCFG, CCM_RSTCLKCFG_RSTOUT_CLKOUT_IS)
#define _ccm_dis_rstout_clkout_is(ccm) _bit_clr(ccm->RSTCLKCFG, CCM_RSTCLKCFG_RSTOUT_CLKOUT_IS)
#define _ccm_en_rstout_ps(ccm) _bit_set(ccm->RSTCLKCFG, CCM_RSTCLKCFG_RSTOUT_PS)
#define _ccm_dis_rstout_ps(ccm) _bit_clr(ccm->RSTCLKCFG, CCM_RSTCLKCFG_RSTOUT_PS)
#define _ccm_en_clkout_ps(ccm) _bit_set(ccm->RSTCLKCFG, CCM_RSTCLKCFG_CLKOUT_PS)
#define _ccm_dis_clkout_ps(ccm) _bit_clr(ccm->RSTCLKCFG, CCM_RSTCLKCFG_CLKOUT_PS)
#define _ccm_get_cfg3_all(ccm) _reg_read(ccm->RSTCLKCFG)

#define _ccm_set_osc_2k_clk_src1(ccm) _bit_set(ccm->RTCSR, CCM_PMCSR_OSC_2K_CLK_SRC)
#define _ccm_set_osc_2k_clk_src0(ccm) _bit_clr(ccm->RTCSR, CCM_PMCSR_OSC_2K_CLK_SRC)
#define _ccm_set_osc_128k_clk_src1(ccm) _bit_set(ccm->RTCSR, CCM_PMCSR_OSC_128K_CLK_SRC)
#define _ccm_set_osc_128k_clk_src0(ccm) _bit_clr(ccm->RTCSR, CCM_PMCSR_OSC_128K_CLK_SRC)
#define _ccm_en_lvdt3v3p_src(ccm) _bit_set(ccm->RTCSR, CCM_PMCSR_LVDT3P3V_SRC)
#define _ccm_dis_lvdt3v3p_src(ccm) _bit_clr(ccm->RTCSR, CCM_PMCSR_LVDT3P3V_SRC)
#define _ccm_get_rtcsr_all(ccm) _reg_read(ccm->RTCSR)

#define _ccm_set_usbphy_ctrl_usbc(ccm) _bit_clr(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_USBPHY_CTRL)
#define _ccm_set_usbphy_ctrl_reg(ccm) _bit_set(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_USBPHY_CTRL)
#define _ccm_en_usbphy_bisten(ccm) _bit_set(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_USBPHY_BISTEN)
#define _ccm_dis_usbphy_bisten(ccm) _bit_clr(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_USBPHY_BISTEN)
#define _ccm_en_bist_pll_rstn(ccm) _bit_set(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_BIST_PLL_RSTN)
#define _ccm_dis_bist_pll_rstn(ccm) _bit_clr(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_BIST_PLL_RSTN)
#define _ccm_en_bist_phy_reset(ccm) _bit_set(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_BIST_PHY_RESET)
#define _ccm_dis_bist_phy_reset(ccm) _bit_clr(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_BIST_PHY_RESET)
#define _ccm_en_bist_rege(ccm) _bit_set(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_BIST_REGE)
#define _ccm_dis_bist_rege(ccm) _bit_clr(ccm->OTG_PHY_CTRL, CCM_OTG_PHY_CTRL_BIST_REGE)
#define _ccm_get_otg_phy_ctrl_all(ccm) _reg_read(ccm->OTG_PHY_CTRL)

#define _ccm_en_ssi4_xip_en(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI4_XIP_EN)
#define _ccm_dis_ssi4_xip_en(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI4_XIP_EN)
#define _ccm_en_ssi5_xip_en(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI5_XIP_EN)
#define _ccm_dis_ssi5_xip_en(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI5_XIP_EN)
#define _ccm_en_ssi6_xip_en(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI6_XIP_EN)
#define _ccm_dis_ssi6_xip_en(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI6_XIP_EN)
#define _ccm_en_ssi4_data_arrange(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI4_DATA_ARRANGE)
#define _ccm_dis_ssi4_data_arrange(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI4_DATA_ARRANGE)
#define _ccm_en_ssi4_xip_sel(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI4_XIP_SEL)
#define _ccm_dis_ssi4_xip_sel(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI4_XIP_SEL)
#define _ccm_en_ssi5_xip_sel(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI5_XIP_SEL)
#define _ccm_dis_ssi5_xip_sel(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI5_XIP_SEL)
#define _ccm_en_ssi6_xip_sel(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI6_XIP_SEL)
#define _ccm_dis_ssi6_xip_sel(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI6_XIP_SEL)
#define _ccm_en_ssi5_data_arrange(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI5_DATA_ARRANGE)
#define _ccm_dis_ssi5_data_arrange(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI5_DATA_ARRANGE)
#define _ccm_en_ssi4_auto(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI4_AUTO_SWAP_EN)
#define _ccm_dis_ssi4_auto(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI4_AUTO_SWAP_EN)
#define _ccm_en_ssi5_auto(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI5_AUTO_SWAP_EN)
#define _ccm_dis_ssi5_auto(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI5_AUTO_SWAP_EN)
#define _ccm_en_ssi6_auto(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI6_AUTO_SWAP_EN)
#define _ccm_dis_ssi6_auto(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI6_AUTO_SWAP_EN)
#define _ccm_en_ssi6_data_arrange(ccm) _bit_set(ccm->SSICFGR, CCM_SSICFGR_SSI6_DATA_ARRANGE)
#define _ccm_dis_ssi6_data_arrange(ccm) _bit_clr(ccm->SSICFGR, CCM_SSICFGR_SSI6_DATA_ARRANGE)
#define _ccm_get_ssicfrg_all(ccm) _reg_read(ccm->SSICFGR)

#ifdef __cplusplus
}
#endif

#endif
