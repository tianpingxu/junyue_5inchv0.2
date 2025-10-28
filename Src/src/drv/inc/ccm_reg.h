/**
 * @file ccm_reg.h
 * @author Product application department
 * @brief  CCM 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __CCM_REG_H_
#define __CCM_REG_H_

// 全局变量定义
#define CCM_BASE_ADDR (0x40001000)
#define CCM ((reg_ccm_t *)CCM_BASE_ADDR)

// FDCR
#define CCM_FDCR_LFDCR ((uint16_t)0xff << 0)
#define CCM_FDCR_HFDCR ((uint16_t)0xff << 8)

// CCR 0x02
#define CCM_CCR_BMT ((uint16_t)3 << 0)
#define CCM_CCR_BMD ((uint16_t)1 << 2)
#define CCM_CCR_BME ((uint16_t)1 << 3)
#define CCM_CCR_SHINT ((uint16_t)1 << 4)
#define CCM_CCR_PERIPH_BRIDGE_RAE ((uint16_t)1 << 5)
#define CCM_CCR_PERIPH_BRIDGE_PAE ((uint16_t)1 << 6)
#define CCM_CCR_MODE ((uint16_t)7 << 8)
#define CCM_CCR_CLKMODE_PDE ((uint16_t)1 << 11)
#define CCM_CCR_JTAGDIS ((uint16_t)1 << 12)
#define CCM_CCR_BTLDDIS ((uint16_t)1 << 13)
#define CCM_CCR_TESTDIS ((uint16_t)1 << 14)
#define CCM_CCR_SWAPDIS ((uint16_t)1 << 15)

// PHYPA 0x06
#define CCM_PHYPA_USBPHY_PLL_EN ((uint16_t)1 << 0)
#define CCM_PHYPA_USBPHY_REG_EN ((uint16_t)1 << 1)
#define CCM_PHYPA_USBPHY_SUSPENDM ((uint16_t)1 << 2)
#define CCM_PHYPA_USBPHY_TERMSEL_DIR ((uint16_t)1 << 3)
#define CCM_PHYPA_USBPHY_TERMSEL ((uint16_t)1 << 4)
#define CCM_PHYPA_USBPHY_DIR ((uint16_t)1 << 5)
#define CCM_PHYPA_USBPHY_12M_EN_SEL ((uint16_t)1 << 6)
#define CCM_PHYPA_USBPHY_REG_EN_SEL ((uint16_t)1 << 7)

#define CCM_PHYPA_PHY_SESSENDVALID ((uint16_t)1 << 8)
#define CCM_PHYPA_PHY_AVALID ((uint16_t)1 << 9)
#define CCM_PHYPA_PHY_VBUSVALID ((uint16_t)1 << 10)
#define CCM_PHYPA_PHY_VALID_DIR ((uint16_t)1 << 11)
#define CCM_PHYPA_PHY_ID_DIR ((uint16_t)1 << 12)
#define CCM_PHYPA_PHY_ID_PULLUP ((uint16_t)1 << 13)
#define CCM_PHYPA_PHY_RESUME_SEL ((uint16_t)1 << 14)
#define CCM_PHYPA_USB_REG_ENDIAN ((uint16_t)1 << 15)

// PCFG3 0x14
#define CCM_PCFG3_PWM1_EN ((uint32_t)1 << 0)
#define CCM_PCFG3_PWM2_EN ((uint32_t)1 << 1)
#define CCM_PCFG3_PWM3_EN ((uint32_t)1 << 2)
#define CCM_PCFG3_CLKOUT_PUE ((uint32_t)1 << 8)
#define CCM_PCFG3_RSTOUT_PUE ((uint32_t)1 << 9)
#define CCM_PCFG3_TDO_PUE ((uint32_t)1 << 10)
#define CCM_PCFG3_SS2_SWAP ((uint32_t)1 << 13)

// RSTCLKCFG 0x1c
#define CCM_RSTCLKCFG_RTC_TESTMODE_EN ((uint32_t)1 << 17)
#define CCM_RSTCLKCFG_RSTOUT_CLKOUT_SR ((uint32_t)1 << 10)
#define CCM_RSTCLKCFG_RSTOUT_CLKOUT_IS ((uint32_t)1 << 11)
#define CCM_RSTCLKCFG_RSTOUT_PS ((uint32_t)1 << 12)
#define CCM_RSTCLKCFG_CLKOUT_PS ((uint32_t)1 << 13)
// PMCSR 0x20
#define CCM_PMCSR_OSC_2K_CLK_SRC ((uint32_t)1 << 24)
#define CCM_PMCSR_OSC_128K_CLK_SRC ((uint32_t)1 << 25)
#define CCM_PMCSR_LVDT1P8V_SRC ((uint32_t)1 << 26)
#define CCM_PMCSR_LVDT3P3V_SRC ((uint32_t)1 << 27)

#define CCM_SSICFGR_SSI4_XIP_EN  ((uint16_t)1 << 16)
#define CCM_SSICFGR_SSI5_XIP_EN  ((uint16_t)1 << 17)
#define CCM_SSICFGR_SSI6_XIP_EN  ((uint16_t)1 << 18)
#define CCM_SSICFGR_SSI4_DATA_ARRANGE ((uint16_t)1 << 19)
#define CCM_SSICFGR_SSI4_XIP_SEL  ((uint16_t)1 << 20)
#define CCM_SSICFGR_SSI5_XIP_SEL  ((uint16_t)1 << 21)
#define CCM_SSICFGR_SSI6_XIP_SEL  ((uint16_t)1 << 22)
#define CCM_SSICFGR_SSI5_DATA_ARRANGE ((uint16_t)1 << 23)
#define CCM_SSICFGR_SSI4_AUTO_SWAP_EN ((uint16_t)1 << 24)
#define CCM_SSICFGR_SSI5_AUTO_SWAP_EN ((uint16_t)1 << 25)
#define CCM_SSICFGR_SSI6_AUTO_SWAP_EN ((uint16_t)1 << 26)
#define CCM_SSICFGR_SSI6_DATA_ARRANGE ((uint16_t)1 << 27)
/**
 * @brief  CCM 模块寄存器定义
 */
typedef struct
{
    __IO uint16_t RESERVED0; // 00
    __IO uint16_t CCR;         // 0x02
    __IO uint16_t RESERVED1; // 02
    __IO uint16_t PHYPA;     // 06
    __IO uint16_t RESERVED2; // 08
    __IO uint16_t CTR;       // 0a
    __IO uint32_t RESERVED3;

    __IO uint32_t PCFG12;    // 10
    __IO uint32_t PCFG3;     // 14
    __IO uint32_t RESERVED4; // 0x18
    __IO uint32_t RSTCLKCFG; // 1c
    __IO uint32_t RESERVED5[2]; // 0x20

    __IO uint32_t OTG_PHY_CTRL; // 28
    __IO uint32_t RESERVED6[4]; // 0x2C
    __IO uint32_t SSICFGR; // 3c
} reg_ccm_t;

#endif
