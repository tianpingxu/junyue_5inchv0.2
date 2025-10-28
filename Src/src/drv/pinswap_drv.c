/**
 * @file pinswap_drv.c
 * @author Product Application Department
 * @brief  模块 功能切换
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "pinswap_drv.h"
#include "adc_drv.h"
#include "ioctrl_drv.h"
#include "eport_drv.h"
#include "cpm_drv.h"
#include "uart_drv.h"
// 函数定义

/**
 * @brief 实现功能切换函数
 *
 * @param defaultFeature 当前引脚所处于的功能
 * @param newFeature 转换为的新的功能
 * @return status_t 返回状态
 */
status_t SwitchPinFunction(FeatureFunction defaultFeature, FeatureFunction newFeature)
{
    status_t ret = STATUS_OK;
    switch (defaultFeature)
    {
    case CLCD_DATA0_FUN:
    {
        switch (newFeature)
        {
        case SSI_SLAVE_SS_FUN:
            _ioctrl_swapcr7_swap16_set;
            break;
        case SPI5_CS_FUN:    
            _ioctrl_swapcr5_swap15_set;
            break;
        case PWMT1_0_FUN:
            _ioctrl_swapcr3_swap8_set;
            break;
        case EPORT7_PIN0_FUN:
            _ioctrl_swapcr5_swap14_clr;
            _ioctrl_swapcr6_swap24_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr7_swap16_clr;
            _ioctrl_swapcr5_swap15_clr;
            _ioctrl_swapcr3_swap8_clr;
            _ioctrl_swapcr6_swap24_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;

    case CLCD_DATA1_FUN:
    {
        switch (newFeature)
        {
        case SSI_SLAVE_CLK_FUN:
            _ioctrl_swapcr7_swap17_set;
            break;
        case SPI5_CLK_FUN:
            _ioctrl_swapcr5_swap14_set;
            break;
        case PWMT1_0_N_FUN:
            _ioctrl_swapcr3_swap9_set;
            break;
        case EPORT7_PIN1_FUN:
            _ioctrl_swapcr5_swap15_clr;
            _ioctrl_swapcr6_swap25_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr7_swap17_clr;
            _ioctrl_swapcr5_swap14_clr;
            _ioctrl_swapcr3_swap9_clr;
            _ioctrl_swapcr6_swap25_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;

    case CLCD_DATA2_FUN:
    {
        switch (newFeature)
        {
        case SSI_SLAVE_DATA0_FUN:
            _ioctrl_swapcr7_swap18_set;
            break;
        case SPI5_DATA0_FUN:
            _ioctrl_swapcr5_swap13_set;
            break;
        case PWMT1_1_FUN:
            _ioctrl_swapcr3_swap10_set;
            break;
        case EPORT7_PIN2_FUN:
            _ioctrl_swapcr5_swap13_clr;
            _ioctrl_swapcr6_swap26_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr7_swap18_clr;
            _ioctrl_swapcr5_swap13_clr;
            _ioctrl_swapcr3_swap10_clr;
            _ioctrl_swapcr6_swap26_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA3_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA0_FUN:
            _ioctrl_mculcdcr_swap0_set;
            break;
        case EPORT7_PIN3_FUN:
            _ioctrl_swapcr6_swap27_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap0_clr;
            _ioctrl_swapcr6_swap27_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA4_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA1_FUN:
            _ioctrl_mculcdcr_swap1_set;
            break;
        case EPORT7_PIN4_FUN:
            _ioctrl_swapcr6_swap28_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap1_clr;
            _ioctrl_swapcr6_swap28_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA5_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA2_FUN:
            _ioctrl_mculcdcr_swap2_set;
            break;
        case EPORT7_PIN5_FUN:
            _ioctrl_swapcr6_swap29_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap2_clr;
            _ioctrl_swapcr6_swap29_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA6_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA3_FUN:
            _ioctrl_mculcdcr_swap3_set;
            break;
        case EPORT7_PIN6_FUN:
            _ioctrl_swapcr6_swap30_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap3_clr;
            _ioctrl_swapcr6_swap30_clr;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA7_FUN:
    {

        switch (newFeature)
        {
        case I8080_DATA4_FUN:
            _ioctrl_mculcdcr_swap4_set;
            break;
        case EPORT7_PIN7_FUN:
            _ioctrl_swapcr6_swap31_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap4_clr;
            _ioctrl_swapcr6_swap31_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA8_FUN:
    {
        switch (newFeature)
        {
        case SSI_SLAVE_DATA1_FUN:
            _ioctrl_swapcr7_swap19_set;
            break;
        case SPI5_DATA1_FUN:
            _ioctrl_swapcr5_swap12_set;
            break;
        case EPORT8_PIN0_FUN:
            _ioctrl_swapcr5_swap12_clr;
            _ioctrl_swapcr7_swap0_set;
            break;
        case PWMT1_1_N_FUN:
            _ioctrl_swapcr3_swap11_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr7_swap19_clr;
            _ioctrl_swapcr5_swap12_clr;
            _ioctrl_swapcr7_swap0_clr;
            _ioctrl_swapcr3_swap11_clr;
            break;

        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA9_FUN:
    {
        switch (newFeature)
        {
        case SSI_SLAVE_DATA2_FUN:
            _ioctrl_swapcr7_swap20_set;
            break;
        case SPI5_DATA2_FUN:
            _ioctrl_swapcr5_swap11_set;
            break;
        case EPORT8_PIN1_FUN:
            _ioctrl_swapcr5_swap11_clr;
            _ioctrl_swapcr7_swap1_set;
            break;
        case PWMT1_2_FUN:
            _ioctrl_swapcr3_swap12_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr7_swap20_clr;
            _ioctrl_swapcr5_swap11_clr;
            _ioctrl_swapcr7_swap1_clr;
            _ioctrl_swapcr3_swap12_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA10_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA5_FUN:
            _ioctrl_mculcdcr_swap5_set;
            break;
        case EPORT8_PIN2_FUN:
            _ioctrl_swapcr7_swap2_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap5_clr;
            _ioctrl_swapcr7_swap2_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA11_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA6_FUN:
            _ioctrl_mculcdcr_swap6_set;
            break;
        case EPORT8_PIN3_FUN:
            _ioctrl_swapcr7_swap3_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap6_clr;
            _ioctrl_swapcr7_swap3_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA12_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA7_FUN:
            _ioctrl_mculcdcr_swap7_set;
            break;
        case EPORT3_PIN2_FUN:
            _ioctrl_swapcr2_swap26_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap7_clr;
            _ioctrl_swapcr2_swap26_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA13_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA8_FUN:
            _ioctrl_mculcdcr_swap8_set;
            break;
        case EPORT3_PIN3_FUN:
            _ioctrl_swapcr2_swap27_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap8_clr;
            _ioctrl_swapcr2_swap27_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA14_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA9_FUN:
            _ioctrl_mculcdcr_swap9_set;
            break;
        case EPORT3_PIN4_FUN:
            _ioctrl_swapcr2_swap28_set;
            break;

        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap9_clr;
            _ioctrl_swapcr2_swap28_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA15_FUN:
    {

        switch (newFeature)
        {
        case I8080_DATA10_FUN:
            _ioctrl_mculcdcr_swap10_set;
            break;
        case EPORT3_PIN5_FUN:
            _ioctrl_swapcr2_swap29_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap10_clr;
            _ioctrl_swapcr2_swap29_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA16_FUN:
    {
        switch (newFeature)
        {
        case SSI_SLAVE_DATA3_FUN:
            _ioctrl_swapcr7_swap21_set;
            break;
        case SPI5_DATA3_FUN:
            _ioctrl_swapcr5_swap10_set;
            break;
        case PWMT1_2_N_FUN:
            _ioctrl_swapcr3_swap13_set;
            break;
        case EPORT9_PIN0_FUN:
            _ioctrl_swapcr5_swap10_clr;
            _ioctrl_swapcr7_swap8_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr7_swap21_clr;
            _ioctrl_swapcr5_swap10_clr;
            _ioctrl_swapcr3_swap13_clr;
            _ioctrl_swapcr7_swap8_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA17_FUN:
    {
        switch (newFeature)
        {
        case PWMT1_3_FUN:
            _ioctrl_swapcr3_swap14_set;
            break;
        case EPORT9_PIN1_FUN:
            _ioctrl_swapcr7_swap9_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr3_swap14_clr;
            _ioctrl_swapcr7_swap9_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA18_FUN:
    {
        switch (newFeature)
        {
        case CLKOUT_FUN:
            _ioctrl_swapcr5_swap7_set;
            break;
        case PWMT1_3_N_FUN:
            _ioctrl_swapcr3_swap15_set;
            break;
        case EPORT9_PIN2_FUN:
            _ioctrl_swapcr7_swap10_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap7_clr;
            _ioctrl_swapcr3_swap15_clr;
            _ioctrl_swapcr7_swap10_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA19_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA11_FUN:
            _ioctrl_mculcdcr_swap11_set;
            break;
        case EPORT9_PIN3_FUN:
            _ioctrl_swapcr7_swap11_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap11_clr;
            _ioctrl_swapcr7_swap11_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA20_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA12_FUN:
            _ioctrl_mculcdcr_swap12_set;
            break;
        case EPORT9_PIN4_FUN:
            _ioctrl_swapcr7_swap12_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap12_clr;
            _ioctrl_swapcr7_swap12_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA21_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA13_FUN:
            _ioctrl_mculcdcr_swap13_set;
            break;
        case EPORT9_PIN5_FUN:
            _ioctrl_swapcr7_swap13_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap13_clr;
            _ioctrl_swapcr7_swap13_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA22_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA14_FUN:
            _ioctrl_mculcdcr_swap14_set;
            break;
        case EPORT9_PIN6_FUN:
            _ioctrl_swapcr7_swap14_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap14_clr;
            _ioctrl_swapcr7_swap14_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_DATA23_FUN:
    {
        switch (newFeature)
        {
        case I8080_DATA15_FUN:
            _ioctrl_mculcdcr_swap15_set;
            break;
        case EPORT9_PIN7_FUN:
            _ioctrl_swapcr7_swap15_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap15_clr;
            _ioctrl_swapcr7_swap15_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_CLAC_FUN:
    {
        switch (newFeature)
        {
        case I8080_RS_FUN:
            _ioctrl_mculcdcr_swap19_set;
            break;
        case EPORT3_PIN1_FUN:
            _ioctrl_swapcr2_swap25_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap19_clr;
            _ioctrl_swapcr2_swap25_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_CLCP_FUN:
    {
        switch (newFeature)
        {
        case I8080_RD_FUN:
            _ioctrl_mculcdcr_swap17_set;
            break;
        case EPORT6_PIN5_FUN:
            _ioctrl_swapcr6_swap21_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap17_clr;
            _ioctrl_swapcr6_swap21_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_CLLP_FUN:
    {
        switch (newFeature)
        {
        case I8080_WR_FUN:
            _ioctrl_mculcdcr_swap18_set;
            break;
        case EPORT8_PIN4_FUN:
            _ioctrl_swapcr7_swap4_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap18_clr;
            _ioctrl_mculcdcr_swap18_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLCD_CLFP_FUN:
    {
        switch (newFeature)
        {
        case I8080_CS_FUN:
            _ioctrl_mculcdcr_swap16_set;
            break;
        case EPORT3_PIN0_FUN:
            _ioctrl_swapcr2_swap24_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_mculcdcr_swap16_clr;
            _ioctrl_swapcr2_swap24_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI6_CS_FUN:
    {
        switch (newFeature)
        {
        case EPORT4_PIN0_FUN:
            _ioctrl_swapcr6_swap0_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap0_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;

    case SPI4_CS_FUN:
    {
        switch (newFeature)
        {
        case EPORT2_PIN0_FUN:
            _ioctrl_swapcr2_swap16_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap16_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI6_CLK_FUN:
    {
        switch (newFeature)
        {
        case EPORT4_PIN1_FUN:
            _ioctrl_swapcr6_swap1_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap1_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI6_DATA0_FUN:
    {
        switch (newFeature)
        {
        case EPORT4_PIN5_FUN:
            _ioctrl_swapcr6_swap5_set;
            break;
        case SPI3_SS_FUN:
            _ioctrl_swapcr8_swap8_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap5_clr;
            _ioctrl_swapcr8_swap8_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI6_DATA1_FUN:
    {
        switch (newFeature)
        {
        case EPORT4_PIN4_FUN:
            _ioctrl_swapcr6_swap4_set;
            break;
        case SPI3_CLK_FUN:
            _ioctrl_swapcr8_swap9_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap4_clr;
            _ioctrl_swapcr8_swap9_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI6_DATA2_FUN:
    {
        switch (newFeature)
        {
        case EPORT4_PIN3_FUN:
            _ioctrl_swapcr6_swap3_set;
            break;
        case SPI3_MOSI_FUN:
            _ioctrl_swapcr8_swap10_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap3_clr;
            _ioctrl_swapcr8_swap10_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI6_DATA3_FUN:
    {
        switch (newFeature)
        {
        case EPORT4_PIN2_FUN:
            _ioctrl_swapcr6_swap2_set;
            break;
        case SPI3_MISO_FUN:
            _ioctrl_swapcr8_swap11_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap2_clr;
            _ioctrl_swapcr8_swap11_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case PHY_TXEN_FUN:
    {
        switch (newFeature)
        {
        case I2S1_SD_FUN:
            _ioctrl_swapcr4_swap24_set;
            break;
        case EPORT5_PIN6_FUN:
            _ioctrl_swapcr6_swap14_set;
            break;
        case PWMT2_3_FUN:
            _ioctrl_swapcr3_swap22_set;
            break;
        case ADC_CHANNEL14_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN14);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap24_clr;
            _ioctrl_swapcr6_swap14_clr;
            _ioctrl_swapcr3_swap22_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN14);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case PHY_MDIO_FUN:
    {
        switch (newFeature)
        {
        case I2S1_LRCK_FUN:
            _ioctrl_swapcr4_swap25_set;
            break;
        case EPORT5_PIN7_FUN:
            _ioctrl_swapcr6_swap15_set;
            break;
        case PWMT2_2_FUN:
            _ioctrl_swapcr3_swap20_set;
            break;
        case ADC_CHANNEL3_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN3);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap25_clr;
            _ioctrl_swapcr6_swap15_clr;
            _ioctrl_swapcr3_swap20_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN3);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case PHY_TXD0_FUN:
    {
        switch (newFeature)
        {
        case I2S1_SCLK_FUN:
            _ioctrl_swapcr4_swap26_set;
            break;
        case EPORT5_PIN2_FUN:
            _ioctrl_swapcr6_swap10_set;
            break;
        case PWMT2_0_FUN:
            _ioctrl_swapcr3_swap16_set;
            break;
        case ADC_CHANNEL4_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN4);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap26_clr;
            _ioctrl_swapcr6_swap10_clr;
            _ioctrl_swapcr3_swap16_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN4);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case PHY_TXD1_FUN:
    {
        switch (newFeature)
        {
        case I2S1_MCLK_FUN:
            _ioctrl_swapcr4_swap27_set;
            break;
        case EPORT5_PIN3_FUN:
            _ioctrl_swapcr6_swap11_set;
            break;
        case PWMT2_0_N_FUN:
            _ioctrl_swapcr3_swap17_set;
            break;
        case ADC_CHANNEL12_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN12);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap27_clr;
            _ioctrl_swapcr6_swap11_clr;
            _ioctrl_swapcr3_swap17_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN12);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case PHY_RXD0_FUN:
    {
        switch (newFeature)
        {
        case I2S2_SD_FUN:
            _ioctrl_swapcr4_swap28_set;
            break;
        case EPORT5_PIN0_FUN:
            _ioctrl_swapcr6_swap8_set;
            break;
        case PWMT2_1_FUN:
            _ioctrl_swapcr3_swap18_set;
            break;
        case ADC_CHANNEL9_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN9);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap28_clr;
            _ioctrl_swapcr6_swap8_clr;
            _ioctrl_swapcr3_swap18_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN9);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case PHY_RXD1_FUN:
    {
        switch (newFeature)
        {
        case I2S2_LRCK_FUN:
            _ioctrl_swapcr4_swap29_set;
            break;
        case EPORT5_PIN1_FUN:
            _ioctrl_swapcr6_swap9_set;
            break;
        case PWMT2_1_N_FUN:
            _ioctrl_swapcr3_swap19_set;
            break;
        case ADC_CHANNEL13_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN13);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap29_clr;
            _ioctrl_swapcr6_swap9_clr;
            _ioctrl_swapcr3_swap19_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN13);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case RMII_MDC_FUN:
    {
        switch (newFeature)
        {
        case I2S2_SCLK_FUN:
            _ioctrl_swapcr4_swap30_set;
            break;
        case EPORT6_PIN0_FUN:
            _ioctrl_swapcr6_swap16_set;
            break;
        case PWMT2_2_N_FUN:
            _ioctrl_swapcr3_swap21_set;
            break;
        case ADC_CHANNEL15_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN15);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap30_clr;
            _ioctrl_swapcr6_swap16_clr;
            _ioctrl_swapcr3_swap21_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN15);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case RMII_CLK_FUN:
    {
        switch (newFeature)
        {
        case I2S2_MCLK_FUN:
            _ioctrl_swapcr4_swap31_set;
            break;
        case EPORT5_PIN4_FUN:
            _ioctrl_swapcr6_swap12_set;
            break;
        case ADC_CHANNEL11_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN11);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr4_swap31_clr;
            _ioctrl_swapcr6_swap12_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN11);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case RMII_RXDV_FUN:
    {
        switch (newFeature)
        {

        case EPORT5_PIN5_FUN:
            _ioctrl_swapcr6_swap13_set;
            break;
        case ADC_CHANNEL10_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN10);
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap13_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN10);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SDH_DATA0_FUN:
    {
        switch (newFeature)
        {

        case EPORT1_PIN5_FUN:
            _ioctrl_swapcr2_swap13_set;
            break;
        case PWMT3_1_FUN:
            _ioctrl_swapcr3_swap26_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap13_clr;
            _ioctrl_swapcr3_swap26_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SDH_DATA1_FUN:
    {
        switch (newFeature)
        {

        case EPORT1_PIN4_FUN:
            _ioctrl_swapcr2_swap12_set;
            break;
        case PWMT3_1_N_FUN:
            _ioctrl_swapcr3_swap27_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap12_clr;
            _ioctrl_swapcr3_swap27_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SDH_DATA2_FUN:
    {
        switch (newFeature)
        {

        case SPI1_MOSI_FUN:
            _ioctrl_swapcr5_swap30_set;
            break;
        case EPORT1_PIN3_FUN:
            _ioctrl_swapcr2_swap11_set;
            break;
        case PWMT3_2_FUN:
            _ioctrl_swapcr3_swap28_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap30_clr;
            _ioctrl_swapcr2_swap11_clr;
            _ioctrl_swapcr3_swap28_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SDH_DATA3_FUN:
    {
        switch (newFeature)
        {

        case SPI1_MISO_FUN:
            _ioctrl_swapcr5_swap31_set;
            break;
        case EPORT1_PIN2_FUN:
            _ioctrl_swapcr2_swap10_set;
            break;
        case PWMT3_2_N_FUN:
            _ioctrl_swapcr3_swap29_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap31_clr;
            _ioctrl_swapcr2_swap10_clr;
            _ioctrl_swapcr3_swap29_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SDH_CMD_FUN:
    {
        switch (newFeature)
        {

        case SPI1_CLK_FUN:
            _ioctrl_swapcr5_swap29_set;
            break;
        case EPORT1_PIN1_FUN:
            _ioctrl_swapcr2_swap9_set;
            break;
        case PWMT3_0_N_FUN:
            _ioctrl_swapcr3_swap25_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap29_clr;
            _ioctrl_swapcr2_swap9_clr;
            _ioctrl_swapcr3_swap25_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SDH_CLK_FUN:
    {
        switch (newFeature)
        {

        case SPI1_SS_FUN:
            _ioctrl_swapcr5_swap28_set;
            break;
        case EPORT1_PIN0_FUN:
            _ioctrl_swapcr2_swap8_set;
            break;
        case PWMT3_0_FUN:
            _ioctrl_swapcr3_swap24_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap28_clr;
            _ioctrl_swapcr2_swap8_clr;
            _ioctrl_swapcr3_swap24_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART1_RX_FUN:
    {
        switch (newFeature)
        {

        case CAN1_TX_FUN:
            _ioctrl_swapcr5_swap0_set;
            break;
        case ADC_CHANNEL1_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN1);
            break;
        case EPORT0_PIN3_FUN:
            _ioctrl_swapcr2_swap3_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap0_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN1);
            _ioctrl_swapcr2_swap3_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART1_TX_FUN:
    {
        switch (newFeature)
        {

        case CAN1_RX_FUN:
            _ioctrl_swapcr5_swap1_set;
            break;
        case ADC_CHANNEL5_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN5);
            break;
        case EPORT0_PIN2_FUN:
            _ioctrl_swapcr2_swap2_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap1_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN5);
            _ioctrl_swapcr2_swap2_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART2_RX_FUN:
    {
        switch (newFeature)
        {

        case CAN2_TX_FUN:
            _ioctrl_swapcr5_swap2_set;
            break;

        case EPORT6_PIN7_FUN:
            _ioctrl_swapcr6_swap23_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap2_clr;
            _ioctrl_swapcr6_swap23_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART2_TX_FUN:
    {
        switch (newFeature)
        {

        case CAN2_RX_FUN:
            _ioctrl_swapcr5_swap3_set;
            break;

        case EPORT6_PIN6_FUN:
            _ioctrl_swapcr6_swap22_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap3_clr;
            _ioctrl_swapcr6_swap22_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART3_RX_FUN:
    {
        switch (newFeature)
        {

        case EPORT2_PIN7_FUN:
            _ioctrl_swapcr2_swap23_set;
            break;        
        case PWMT3_3_FUN:
            _ioctrl_swapcr3_swap30_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap23_clr;
            _ioctrl_swapcr3_swap30_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART3_TX_FUN:
    {
        switch (newFeature)
        {

        case EPORT2_PIN6_FUN:
            _ioctrl_swapcr2_swap22_set;
            break;
        case PWMT3_3_N_FUN:
            _ioctrl_swapcr3_swap31_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap22_clr;
            _ioctrl_swapcr3_swap31_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART4_RX_FUN:
    {
        switch (newFeature)
        {

        case EPORT3_PIN7_FUN:
            _ioctrl_swapcr2_swap31_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap31_clr;
            break;

        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART4_TX_FUN:
    {
        switch (newFeature)
        {

        case EPORT3_PIN6_FUN:
            _ioctrl_swapcr2_swap30_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap30_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART5_RX_FUN:
    {
        switch (newFeature)
        {

        case I2C1_SCL_FUN:

            _ioctrl_swapcr5_swap21_set;
            break;
        case SDH_WPRT_FUN:
            _ioctrl_sdhcr_swap29_set;
            break;
        case EPORT4_PIN7_FUN:
            _ioctrl_swapcr6_swap7_set;
            break;
        case ADC_CHANNEL2_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN2);
            break;
        case PWMT3_ETR_FUN:
         _ioctrl_swapcr3_swap6_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap21_clr;
            _ioctrl_sdhcr_swap29_clr;
            _ioctrl_swapcr6_swap7_clr;
            _ioctrl_swapcr3_swap6_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN2);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART5_TX_FUN:
    {
        switch (newFeature)
        {

        case I2C1_SDA_FUN:
            _ioctrl_swapcr5_swap20_set;
            break;
        case SDH_DET_FUN:
            _ioctrl_sdhcr_swap28_set;
            break;
        case EPORT4_PIN6_FUN:
            _ioctrl_swapcr6_swap6_set;
            break;
        case ADC_CHANNEL6_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN6);
            break;
        case PWMT3_BRK_FUN:
            _ioctrl_swapcr3_swap7_set;
             break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap20_clr;
            _ioctrl_sdhcr_swap28_clr;
            _ioctrl_swapcr6_swap6_clr;
            _ioctrl_swapcr3_swap7_clr;
            _adc_clr_channel_sel_value(1 << ADC_IN6);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART6_RX_FUN:
    {
        switch (newFeature)
        {

        case I2C2_SCL_FUN:
            _ioctrl_swapcr5_swap25_set;
            break;
        case SDH_RST_FUN:
            _ioctrl_sdhcr_swap31_set;
            break;
        case EPORT6_PIN2_FUN:
            _ioctrl_swapcr6_swap18_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap25_clr;
            _ioctrl_sdhcr_swap31_clr;
            _ioctrl_swapcr6_swap18_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case UART6_TX_FUN:
    {
        switch (newFeature)
        {

        case I2C2_SDA_FUN:
            _ioctrl_swapcr5_swap24_set;
            break;
        case SDH_INT_FUN:
            _ioctrl_sdhcr_swap30_set;
            break;
        case EPORT6_PIN1_FUN:
            _ioctrl_swapcr6_swap17_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr5_swap24_clr;
            _ioctrl_sdhcr_swap30_clr;
            _ioctrl_swapcr6_swap17_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI2_SS_FUN:
    {
        switch (newFeature)
        {

        case SDH_DATA4_FUN:
            _ioctrl_sdhcr_swap24_set;
            break;

        case EPORT0_PIN4_FUN:
            _ioctrl_swapcr2_swap4_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_sdhcr_swap24_clr;
            _ioctrl_swapcr2_swap4_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI2_CLK_FUN:
    {
        switch (newFeature)
        {

        case SDH_DATA5_FUN:
            _ioctrl_sdhcr_swap25_set;
            break;

        case EPORT0_PIN5_FUN:
            _ioctrl_swapcr2_swap5_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_sdhcr_swap25_clr;
            _ioctrl_swapcr2_swap5_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI2_MOSI_FUN:
    {
        switch (newFeature)
        {

        case SDH_DATA7_FUN:
            _ioctrl_sdhcr_swap27_set;
            break;

        case EPORT0_PIN7_FUN:
            _ioctrl_swapcr2_swap7_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_sdhcr_swap27_clr;
            _ioctrl_swapcr2_swap7_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case SPI2_MISO_FUN:
    {
        switch (newFeature)
        {

        case SDH_DATA6_FUN:
            _ioctrl_sdhcr_swap26_set;
            break;

        case EPORT0_PIN6_FUN:
            _ioctrl_swapcr2_swap6_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_sdhcr_swap26_clr;
            _ioctrl_swapcr2_swap6_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case USBDET_FUN:
    {
        switch (newFeature)
        {

        case EPORT6_PIN4_FUN:
            _ioctrl_swapcr6_swap20_set;
            break;
        case PWMT1_BRK_FUN:
            _ioctrl_swapcr3_swap3_set;
            break;   
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap20_clr;
            _ioctrl_swapcr3_swap3_clr;
            break;
        
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case WAKEUP_FUN:
    {
        switch (newFeature)
        {

        case EPORT6_PIN3_FUN:
            _ioctrl_swapcr6_swap19_set;
            break;
        case PWMT1_ETR_FUN:
            _ioctrl_swapcr3_swap2_set;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr6_swap19_clr;
            _ioctrl_swapcr3_swap2_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case CLKOUT_FUN:
    {
        switch (newFeature)
        {

        case EPORT0_PIN0_FUN:
            _ioctrl_swapcr2_swap0_set;
            break;
        case PWMT2_ETR_FUN:
            _ioctrl_swapcr3_swap4_set;
            break;  
        case CLCD_DATA18_FUN:
            _ioctrl_swapcr5_swap7_clr;
            break;
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap0_clr;
            _ioctrl_swapcr3_swap4_clr;
            break;

        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case RSTOUT_FUN:
    {
        switch (newFeature)
        {

        case EPORT0_PIN1_FUN:
            _ioctrl_swapcr2_swap1_set;
            break;
        case PWMT2_BRK_FUN:
            _ioctrl_swapcr3_swap5_set;
            break;       
        case DEFAULT_FUN:
            _ioctrl_swapcr2_swap1_clr;
            _ioctrl_swapcr3_swap5_clr;
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    case TRACE_FUN:
    {
        switch (newFeature)
        {

        case ADC_CHANNEL7_FUN:
            _adc_set_channel_sel_value(1 << ADC_IN7);
            break;
        case DEFAULT_FUN:
            _adc_clr_channel_sel_value(1 << ADC_IN7);
            break;
        default:
            ret = STATUS_ERROR;
            break;
        }
    }
    break;
    default:

        ret = STATUS_ERROR;
        break;
    }
    return ret;
}
