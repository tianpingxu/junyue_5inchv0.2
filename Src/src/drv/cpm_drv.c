/**
 * @file cpm_drv.c
 * @author Product application department
 * @brief  DAC 模块驱动层
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "cpm_drv.h"
#include "interrupt.h"
#include "chipconfig.h"
// 全局变量定义
__IO uint32_t g_core_clk ; 
__IO uint32_t g_sys_clk ;  
__IO uint32_t g_ips_clk   ; 
__IO uint32_t g_ahb3_clk ;
#define g_trim_clk           drv_cpm_gettrimclk()


// 函数定义

/**
 * @brief CPM 模块获取Trim时钟函数
 *
 * @return uint32_t Trim时钟
 */
uint32_t drv_cpm_gettrimclk(void)
{
    uint32_t clk_freq = 0;
    if(_cpm_get_osc400mhz_trim_value == TRIM_500M_VALUE)
    {
        clk_freq = DRV_SYS_OSC_CLK_500M;
    }
    else if(_cpm_get_osc400mhz_trim_value == TRIM_400M_VALUE)
    {
        clk_freq = DRV_SYS_OSC_CLK_400M;
    }

    return clk_freq;
}
/**
 * @brief CPM 模块中断处理函数
 *
 */
void drv_cpm_irqhandler(void)
{
    if (_cpm_get_usb_det_wakeup_src_int_flag)
    {
        _cpm_clr_usb_det_wakeup_src_int_flag;
    }

    if (_cpm_get_wake_wakeup_src_int_flag)
    {
        _cpm_clr_wake_wakeup_src_int_flag;
    }
}

/**
 * @brief CPM 模块8M系统时钟选择函数
 *
 */
void drv_cpm_systemclk_osc8mselect(void)
{
    _cpm_set_osc8m_clk_en;
    while (!_cpm_get_osc8m_stable_flag)
        ;

    _cpm_set_soc_clk_osc8m_en;
    while (!_cpm_get_osc8m_select_flag)
        ;
}

/**
 * @brief CPM 模块400M系统时钟选择函数
 *
 */
void drv_cpm_systemclk_osc400mselect(void)
{
    _cpm_set_osc400m_clk_en;
    while (!_cpm_get_osc400m_stable_flag)
        ;

    _cpm_set_soc_clk_osc400m_en;
    while (!_cpm_get_osc400m_select_flag)
        ;
}

/**
 * @brief CPM 模块240M系统时钟选择函数
 *
 * @param[in] @ref NONE
 * @return @ref NONE
 */
void drv_cpm_systemclk_osc240mselect(void)
{
    _cpm_set_usbphy240m_clk_en;
    while (!_cpm_get_usbphy240m_stable_flag)
        ;

    _cpm_set_soc_clk_usbphy240m_en;
    while (!_cpm_get_usbphy240m_select_flag)
        ;
}

/**
 * @brief CPM 模块外部晶振系统时钟选择函数
 *
 */
void drv_cpm_systemclk_oscextselect(void)
{
    _cpm_set_oscext_clk_en;
    while (!_cpm_get_oscext_stable_flag)
        ;

    _cpm_set_soc_clk_oscext_en;
    while (!_cpm_get_oscext_select_flag)
        ;
}

/**
 * @brief CPM 模块系统测试模式key设置函数
 *
 */
void drv_cpm_vcccore_testmodekeyset(void)
{
    uint32_t tmp = (_cpm_get_core_test_mode_value & 0x3FFFFFFF);

    _cpm_write_core_test_mode_value(tmp);
    _cpm_write_core_test_mode_value(tmp | 0x40000000);
    _cpm_write_core_test_mode_value(tmp | 0x80000000);
    _cpm_write_core_test_mode_value(tmp | 0xC0000000);
}

/**
 * @brief CPM 模块系统测试模式设置函数
 * @param val 系统测试模式设置值
 */
void drv_cpm_vcccore_testmodeset(uint32_t val)
{
    drv_cpm_vcccore_testmodekeyset();
    _cpm_set_core_test_mode_value(val);
}

/**
 * @brief CPM 模块系统电压Trim值设置函数
 * @param trim_value 系统时钟trim设置值
 */
void drv_cpm_systemclkvreftrim(uint32_t trim_value)
{
    drv_cpm_vcccore_testmodekeyset();

    _cpm_set_overwrite_vccgtrimr_trim_en;

    if (trim_value == CPM_VREF_TRIM_090)
    {
        _cpm_set_core_voltage_0V9_on;
    }
    else
    {
        _cpm_set_core_voltage_0V9_off;
        _cpm_set_ldo_trim_value(trim_value);
       
    }
}

/**
 * @brief CPM 模块关闭模块时钟函数
 *
 * @param module_index 被关闭的时钟索引
 */
void drv_cpm_moduleclkoff(uint8_t module_index)
{
    if (module_index < 32)
    {
        _cpm_set_multicgtcr_clk_off(module_index);
    }
    else if (module_index >= 32 && module_index < 64)
    {
        _cpm_set_syscgtcr_clk_off(module_index - 32);
    }
    else if (module_index >= 64 && module_index < 96)
    {
        _cpm_set_ahb3cgtcr_clk_off(module_index - 64);
    }
    else if (module_index >= 96 && module_index < 128)
    {
        _cpm_set_arithcgtcr_clk_off(module_index - 96);
    }
    else if (module_index >= 128 && module_index < 160)
    {
        _cpm_set_ipscgtcr_clk_off(module_index - 128);
    }
}

/**
 * @brief CPM 模块打开模块时钟函数
 *
 * @param module_index 被打开的时钟索引
 */
void drv_cpm_moduleclkon(uint8_t module_index)
{
    if (module_index < 32)
    {
        _cpm_set_multicgtcr_clk_on(module_index);
    }
    else if (module_index >= 32 && module_index < 64)
    {
        _cpm_set_syscgtcr_clk_on(module_index - 32);
    }
    else if (module_index >= 64 && module_index < 96)
    {
        _cpm_set_ahb3cgtcr_clk_on(module_index - 64);
    }
    else if (module_index >= 96 && module_index < 128)
    {
        _cpm_set_arithcgtcr_clk_on(module_index - 96);
    }
    else if (module_index >= 128 && module_index < 160)
    {
        _cpm_set_ipscgtcr_clk_on(module_index - 128);
    }
}

/**
 * @brief CPM 模块获取内核时钟函数
 *
 * @return uint32_t 内核时钟，单位HZ
 */
uint32_t drv_cpm_getcoreclk(void)
{
    uint32_t clk_freq;

    if (_cpm_chk_sys_clk_src(CPM_SYSCLK_OSC8M))
    {
        clk_freq = 8 * 1000 * 1000;
    }
    else if (_cpm_chk_sys_clk_src(CPM_SYSCLK_OSC400M))
    {
        if (g_trim_clk == DRV_SYS_OSC_CLK_320M)
        {
            clk_freq = DRV_SYS_OSC_CLK_320M;
        }
        else if (g_trim_clk == DRV_SYS_OSC_CLK_400M)
        {
            clk_freq = DRV_SYS_OSC_CLK_400M;
        }
        else if (g_trim_clk == DRV_SYS_OSC_CLK_480M)
        {
            clk_freq = DRV_SYS_OSC_CLK_480M;
        }
        else if (g_trim_clk == DRV_SYS_OSC_CLK_500M)
        {
            clk_freq = DRV_SYS_OSC_CLK_500M;
        }
    }
    else if (_cpm_chk_sys_clk_src(CPM_SYSCLK_USBPHY240M))
    {
        clk_freq = DRV_SYS_OSC_CLK_240M;
    }
    else if (_cpm_chk_sys_clk_src(CPM_SYSCLK_OSCEXT) == CPM_SYSCLK_OSCEXT)
    {
        clk_freq = DRV_SYS_OSC_CLK_12M;
    }
    else
    {
        clk_freq = 0;
    }

    return ((uint32_t)(clk_freq / (((_cpm_get_sys_clk_value & 0xf0000000)>>28) + 1)));
}

/**
 * @brief CPM 模块获取系统时钟函数
 *
 * @return uint32_t 系统时钟，单位HZ
 */
uint32_t drv_cpm_getsysclk(void)
{
    uint32_t clk_freq;

    if (_cpm_chk_sys_clk_src(CPM_SYSCLK_OSC8M))
    {
        clk_freq = 8 * 1000 * 1000;
        ;
    }
    else if (_cpm_chk_sys_clk_src(CPM_SYSCLK_OSC400M))
    {
        if (g_trim_clk == DRV_SYS_OSC_CLK_320M)
        {
            clk_freq = DRV_SYS_OSC_CLK_320M;
        }
        else if (g_trim_clk == DRV_SYS_OSC_CLK_400M)
        {
            clk_freq = DRV_SYS_OSC_CLK_400M;
        }
        else if (g_trim_clk == DRV_SYS_OSC_CLK_480M)
        {
            clk_freq = DRV_SYS_OSC_CLK_480M;
        }
        else if (g_trim_clk == DRV_SYS_OSC_CLK_500M)
        {
            clk_freq = DRV_SYS_OSC_CLK_500M;
        }
    }
    else if (_cpm_chk_sys_clk_src(CPM_SYSCLK_USBPHY240M))
    {
        clk_freq = DRV_SYS_OSC_CLK_240M;
    }
    else if (_cpm_chk_sys_clk_src(CPM_SYSCLK_OSCEXT) == CPM_SYSCLK_OSCEXT)
    {
        clk_freq = DRV_SYS_OSC_CLK_12M;
    }
    else
    {
        clk_freq = 0;
    }

    return ((uint32_t)(clk_freq / ((_cpm_get_sys_clk_value & 0xff) + 1)/(((_cpm_get_sys_clk_value & 0xf0000000)>>28) + 1)));
}

/**
 * @brief CPM 模块获取IPS时钟函数
 *
 * @return uint32_t 系统时钟，单位HZ
 */
uint32_t drv_cpm_getipsclk(void)
{
    uint32_t ips_clk;

    if (_cpm_chk_ips_clk_div_en)
    {
        ips_clk = g_sys_clk / ((_cpm_get_peripheral1_clk_div_value & 0x0F) + 1);
    }
    else
    {
        ips_clk = drv_cpm_getsysclk();
    }

    return ips_clk;
}

/**
 * @brief CPM 模块获取AHB3时钟函数
 *
 * @return uint32_t 系统时钟，单位HZ
 */
uint32_t drv_cpm_getahbclk(void)
{
    uint32_t ahb3_clk;

    if (_cpm_chk_ips_clk_div_en)
    {
        ahb3_clk = g_sys_clk / (((_cpm_get_peripheral1_clk_div_value >> 8) & 0x0F) + 1);
    }
    else
    {
        ahb3_clk = g_sys_clk;
    }

    return ahb3_clk;
}

/**
 * @brief CPM 模块系统时钟分频设置函数
 * 
 * @param core_div 主频分频系数
 * @param sys_div 系统分频系数
 */
 void drv_cpm_setsysclkdiv(uint8_t core_div, uint8_t sys_div)
{
    _cpm_set_core_clk_div(core_div);
    _cpm_set_sys_clk_div(sys_div);
    _cpm_update_sys_clk_div;
}

/**
 * @brief CPM 模块CLCD分频设置函数
 * 
 * @param clcd_div clcd分频系数
 */
 void drv_cpm_setclcddiv(uint8_t clcd_div)
{
    _cpm_set_peripheral_clcd_clk_div(clcd_div);
    _cpm_update_sys_clk_div;
    _cpm_update_peripheral_clk_div;
}
/**
 * @brief CPM 模块clkout输出时钟源设置函数
 * @param source 时钟源选择
 */
void drv_cpm_setclkoutsource(uint8_t source)
{
    drv_cpm_vcccore_testmodeset(1 << 29);
    _cpm_set_clkout_source(source);
}

/**
 * @brief CPM 模块clk 校准函数
 * 
 * @param value 校准值
 */
void drv_cpm_clktrim(uint32_t value)
{
    delay(10);
    drv_cpm_vcccore_testmodekeyset();
    _cpm_set_core_test_mode_value(1<<19);
    _cpm_set_osc400mhz_trim_value(value);
    drv_cpm_systemclk_osc400mselect();
    delay(10);
}
/**
 * @brief CPM 模块CLKOUT输出时钟源分频设置函数
 * @param div clkout时钟源分频系数，取值范围【0x00~0xff】
 */
void drv_cpm_setclkoutdiv(uint8_t div)
{
    _cpm_set_clkout_clk_div_en;
    _cpm_set_clkout_clk_div(div);
    _cpm_update_sys_clk_div;
}

/**
 * @brief CPM 模块算法时钟输出时钟源分频设置函数
 * @param div 分频系数
 */
void drv_cpm_setarithclkdiv(uint8_t div)
{
    _cpm_set_arith_clk_div_en;
    _cpm_set_peripheral_arith_clk_div(div);
    _cpm_update_peripheral_clk_div;
}

/**
 * @brief CPM 模块AHB3时钟输出时钟源分频设置函数
 *
 * @param div Ahb3时钟源分频系数，取值范围【0x00~0x0f】
 */
void drv_cpm_setahb3clkdiv(uint8_t div)
{
    _cpm_set_ahb3_clk_div_en;
    _cpm_set_peripheral_ahb3_clk_div(div);
    _cpm_update_peripheral_clk_div;
}

/**
 * @brief CPM 模块IPS时钟分频设置函数
 *
 * @param div IPS时钟源分频系数，取值范围【0x00~0x0f】
 */
 void drv_cpm_setipsclkdiv(uint8_t div)
{
    _cpm_set_ips_clk_div_en;
    _cpm_set_peripheral_ips_clk_div(div);
    _cpm_set_peripheral_ahb3_clk_div(div);
    _cpm_set_peripheral_arith_clk_div(div);
    _cpm_set_peripheral_sdram2lcd_clk_div(div);
    _cpm_update_peripheral_clk_div;
}

/**
 * @brief CPM 模块TC时钟分频设置函数
 *
 * @param div TC时钟源分频系数，取值范围【0x00~0x0f】
 */
void drv_cpm_settcclkdiv(uint8_t div)
{
    _cpm_set_tc_clk_div_en;
    _cpm_set_peripheral_tc_clk_div(div);
    _cpm_update_peripheral_clk_div;
}

/**
 * @brief CPM 模块ADC时钟分频设置函数
 *
 * @param div ADC时钟源分频系数，取值范围【0x00~0x0f】
 */
void drv_cpm_setadcclkdiv(uint8_t div)
{
    _cpm_set_adc_clk_div_en;
    _cpm_set_peripheral_adc_clk_div(div);
    _cpm_update_peripheral_clk_div;
}

/**
 * @brief CPM 模块USBC PHY时钟初始化设置韩素华
 *
 * @param src_type 时钟源
 */
void drv_cpm_usbphyinit(uint8_t src_type)
{
    drv_cpm_setahb3clkdiv(1);
    // select the osc mode
    _cpm_select_usbphy_osc_mode(src_type);

    if (src_type != 0x02)
    {
        _cpm_set_oscext_clk_stable_time_value(0x3000);
        _cpm_set_oscext_clk_en;
    }

    // Enable PHY Power Switch
    _cpm_set_usbphy_power_switch_en;

    // delay at least 10ms, sys clk is 320MHz, in release obj, one clock_cycle is 6 clock
    // so delay(x) = (6 * x / 120)us = 0.05x us, we use 11ms here.so 11ms = (6 * x / 120)=>x=220000
    delayms(11);

    // Enable PHY Regulator
    CCM->PHYPA &= ~0xFF;

    // delay at least 10us
    delay(300);

    //    _cpm_set_usbphy_input_isolation_dis;
    //    _cpm_set_usbphy_output_isolation_dis;

    if (src_type != 0x02)
    {
        volatile uint32_t timeout = 0;
        while (!_cpm_get_oscext_stable_flag)
        {
            timeout++;
            if (timeout > 0x10000)
            {
                break;
            }
        }
    }

    // delay at least 10ms
    delayms(10);
    _cpm_set_usbphy_conf_software_reset_dis;

    // delay at least 1ms
    delayms(1);
    _cpm_set_usbphy_pll_software_reset_dis;

    // delay at least 1ms
    delayms(1);
    _cpm_set_usbphy_reset_signal_mask_dis;

    // delay at least 1ms
    delayms(1);
}

/**
 * @brief CPM 模块USBC PHY清理函数
 *
 */
void drv_cpm_usbphydeinit(void)
{
    // delay at least 1ms
    delayms(1);

    // delay at least 10ms
    _cpm_set_usbphy_reset_signal_mask_en;
    delayms(1);

    // delay at least 1ms
    _cpm_set_usbphy_pll_software_reset_en;
    delayms(1);

    // delay at least 1ms
    _cpm_set_usbphy_conf_software_reset_en;
    delayms(10);

    //    _cpm_set_usbphy_input_isolation_en;
    //    _cpm_set_usbphy_output_isolation_en;

    // delay at least 10us
    delay(300);

    // delay at least 10ms, sys clk is 320MHz, in release obj, one clock_cycle is 6 clock
    // so delay(x) = (6 * x / 120)us = 0.05x us, we use 11ms here.so 11ms = (6 * x / 120)=>x=220000
    delayms(11);

    // Disable PHY Power Switch
    _cpm_set_usbphy_power_switch_dis;

    _cpm_set_oscext_clk_dis;
}

/**
 * @brief CPM 模块系统复位函数
 *
 */
void drv_cpm_porreset(void)
{
    drv_cpm_vcccore_testmodekeyset();
    _cpm_soft_por_reset;
    while (1)
        ;
}

/**
 * @brief CPM 模块唤醒中断源初始化函数
 *
 * @param Src CPM唤醒源选择
 * @param NewState 是否使能中断
 */
void drv_cpm_wakeupinit(cpm_padwakeupindex_t Src, functionalstate_t NewState)
{
    switch (Src)
    {
    case PAD_WAKEUP_INDEX_USBDET:
        _cpm_set_usb_det_wakeup_src_en;
        if (NewState == ENABLE)
        {
            NVIC_Init(3, 1, CPM_IRQn, 2);
            _cpm_set_usb_det_wakeup_src_int_en;
        }
        break;

    case PAD_WAKEUP_INDEX_WAKE:
        _cpm_set_wake_wakeup_src_en;
        if (NewState == ENABLE)
        {
            NVIC_Init(3, 1, CPM_IRQn, 2);
            _cpm_set_wake_wakeup_src_int_en;
        }
        break;

    default:
        break;
    }
}

/**
 * @brief CPM 模块 外设复位函数
 * @param
 */
void drv_cpm_module_reset(cpm_module_t module)
{
    switch (module)
    {
    case SDRAM2LCD_MODULE:
        _cpm_set_multi_module_reset_en(27);
        _cpm_set_multi_module_reset_dis(27);
        _cpm_set_sys_module_reset_en(24);
        _cpm_set_sys_module_reset_dis(24);
        break;
    case LCDC_MODULE:
        _cpm_set_multi_module_reset_en(26);
        _cpm_set_multi_module_reset_dis(26);
        _cpm_set_sys_module_reset_en(22);
        _cpm_set_sys_module_reset_dis(22);
        _cpm_set_sys_module_reset_en(21);
        _cpm_set_sys_module_reset_dis(21);
        break;
    case DMA2D_MODULE:
        _cpm_set_multi_module_reset_en(25);
        _cpm_set_multi_module_reset_dis(25);
        _cpm_set_sys_module_reset_en(12);
        _cpm_set_sys_module_reset_dis(12);
        _cpm_set_sys_module_reset_en(21);
        _cpm_set_sys_module_reset_dis(21);
        break;
    case SDHOST_MODULE:
        _cpm_set_multi_module_reset_en(24);
        _cpm_set_multi_module_reset_dis(24);
        _cpm_set_multi_module_reset_en(23);
        _cpm_set_multi_module_reset_dis(23);
        _cpm_set_multi_module_reset_en(22);
        _cpm_set_multi_module_reset_dis(22);
        break;
    case MAC_MODULE:
        _cpm_set_multi_module_reset_en(21);
        _cpm_set_multi_module_reset_dis(21);
        _cpm_set_multi_module_reset_en(20);
        _cpm_set_multi_module_reset_dis(20);
        _cpm_set_sys_module_reset_en(16);
        _cpm_set_sys_module_reset_dis(16);
        break;

    case CRC1_MODULE:
        _cpm_set_multi_module_reset_en(15);
        _cpm_set_multi_module_reset_dis(15);
        break;

    case CRC0_MODULE:
        _cpm_set_multi_module_reset_en(14);
        _cpm_set_multi_module_reset_dis(14);
        break;
    case I2S_SLAVE_MODULE:
        _cpm_set_multi_module_reset_en(13);
        _cpm_set_multi_module_reset_dis(13);
        break;

    case I2S_MASTER_MODULE:
        _cpm_set_multi_module_reset_en(12);
        _cpm_set_multi_module_reset_dis(12);
        break;
    case TC_MODULE:
        _cpm_set_multi_module_reset_en(5);
        _cpm_set_multi_module_reset_dis(5);
        _cpm_set_ips_module_reset_en(2);
        _cpm_set_ips_module_reset_dis(2);
        break;
    case ADC_MODULE:
        _cpm_set_multi_module_reset_en(3);
        _cpm_set_multi_module_reset_dis(3);
        _cpm_set_ips_module_reset_en(20);
        _cpm_set_ips_module_reset_dis(20);
        break;
    case PSRAM_MODULE:
        _cpm_set_sys_module_reset_en(17);
        _cpm_set_sys_module_reset_dis(17);
        _cpm_set_sys_module_reset_en(27);
        _cpm_set_sys_module_reset_dis(27);
        _cpm_set_sys_module_reset_en(23);
        _cpm_set_sys_module_reset_dis(23);
        break;
    case AXIDMA_MODULE:
        _cpm_set_sys_module_reset_en(18);
        _cpm_set_sys_module_reset_dis(18);
        _cpm_set_sys_module_reset_en(11);
        _cpm_set_sys_module_reset_dis(11);
        break;
    case JEPG_MODULE:
        _cpm_set_sys_module_reset_en(10);
        _cpm_set_sys_module_reset_dis(10);
        break;
    case SSI6_MODULE:
        _cpm_set_sys_module_reset_en(8);
        _cpm_set_sys_module_reset_dis(8);
        break;
    case SSI5_MODULE:
        _cpm_set_sys_module_reset_en(7);
        _cpm_set_sys_module_reset_en(6);
        _cpm_set_sys_module_reset_dis(7);
        _cpm_set_sys_module_reset_dis(6);
        break;
    case SSI4_MODULE:
        _cpm_set_sys_module_reset_en(5);
        _cpm_set_sys_module_reset_dis(5);
        break;
    case SD_EMMC_HOST:
        _cpm_set_sys_module_reset_en(4);
        _cpm_set_sys_module_reset_en(3);
        _cpm_set_sys_module_reset_dis(3);
        _cpm_set_sys_module_reset_dis(4);
        break;
    case DMAC2_MODULE:
        _cpm_set_sys_module_reset_en(1);
        _cpm_set_sys_module_reset_dis(1);
        break;
    case DMAC1_MODULE:
        _cpm_set_sys_module_reset_en(0);
        _cpm_set_sys_module_reset_dis(0);
        break;
    case I2S2_MODULE:
        _cpm_set_ahb3_module_reset_en(7);
        _cpm_set_ahb3_module_reset_en(7);
        break;
    case I2S1_MODULE:
        _cpm_set_ahb3_module_reset_en(6);
        _cpm_set_ahb3_module_reset_en(6);
        break;
    case USBC_MODULE:
        _cpm_set_ahb3_module_reset_en(3);
        _cpm_set_ahb3_module_reset_en(3);
        break;
    case AES_MODULE:
        _cpm_set_arith_module_reset_en(10);
        _cpm_set_arith_module_reset_en(4);
        _cpm_set_arith_module_reset_en(1);
        _cpm_set_arith_module_reset_dis(10);
        _cpm_set_arith_module_reset_dis(4);
        _cpm_set_arith_module_reset_dis(1);
        break;
    case SM4_MODULE:
        _cpm_set_arith_module_reset_en(10);
        _cpm_set_arith_module_reset_en(4);
        _cpm_set_arith_module_reset_en(2);
        _cpm_set_arith_module_reset_dis(10);
        _cpm_set_arith_module_reset_dis(4);
        _cpm_set_arith_module_reset_dis(2);
        break;
    case TRNG_MODULE:
        _cpm_set_ips_module_reset_en(26);
        _cpm_set_ips_module_reset_dis(26);
        break;
    case PWMT3_MODULE:
        _cpm_set_ips_module_reset_en(25);
        _cpm_set_ips_module_reset_dis(25);
        break;
    case PWMT2_PWMT3_MODULE:
        _cpm_set_ips_module_reset_en(23);
        _cpm_set_ips_module_reset_dis(23);
        break;
    case UART6_MODULE:
        _cpm_set_ips_module_reset_en(22);
        _cpm_set_ips_module_reset_dis(22);
        break;
    case DAC_MODULE:
        _cpm_set_ips_module_reset_en(21);
        _cpm_set_ips_module_reset_dis(21);
        break;
    case UART5_MODULE:
        _cpm_set_ips_module_reset_en(19);
        _cpm_set_ips_module_reset_dis(19);
        break;
    case UART3_MODULE:
        _cpm_set_ips_module_reset_en(18);
        _cpm_set_ips_module_reset_dis(18);
        break;
    case CAN2_MODULE:
        _cpm_set_ips_module_reset_en(17);
        _cpm_set_ips_module_reset_dis(17);
        break;
    case I2C2_MODULE:
        _cpm_set_ips_module_reset_en(16);
        _cpm_set_ips_module_reset_dis(16);
        break;
    case I2C1_MODULE:
        _cpm_set_ips_module_reset_en(14);
        _cpm_set_ips_module_reset_dis(14);
        break;
    case CAN1_MODULE:
        _cpm_set_ips_module_reset_en(13);
        _cpm_set_ips_module_reset_dis(13);
        break;
    case UART4_MODULE:
        _cpm_set_ips_module_reset_en(12);
        _cpm_set_ips_module_reset_dis(12);
        break;
    case UART2_MODULE:
        _cpm_set_ips_module_reset_en(11);
        _cpm_set_ips_module_reset_dis(11);
        break;
    case UART1_MODULE:
        _cpm_set_ips_module_reset_en(10);
        _cpm_set_ips_module_reset_dis(10);
        break;
    case SPI3_MODULE:
        _cpm_set_ips_module_reset_en(9);
        _cpm_set_ips_module_reset_dis(9);
        break;
    case SPI2_MODULE:
        _cpm_set_ips_module_reset_en(8);
        _cpm_set_ips_module_reset_dis(8);
        break;
    case SPI1_MODULE:
        _cpm_set_ips_module_reset_en(7);
        _cpm_set_ips_module_reset_dis(7);
        break;
    case PIT2_MODULE:
        _cpm_set_ips_module_reset_en(4);
        _cpm_set_ips_module_reset_dis(4);
        break;
    case PIT1_MODULE:
        _cpm_set_ips_module_reset_en(3);
        _cpm_set_ips_module_reset_dis(3);
        break;
    case WDT_MODULE:
        _cpm_set_ips_module_reset_en(1);
        _cpm_set_ips_module_reset_dis(1);
        break;
    default:
        break;
    }
}

/**
 * @brief CPM 模块芯片进入Lowpower低功耗（sleep mode）函数
 * @param
 */
void drv_cpm_lowpower(void)
{
    // 进入Lowpower模式
    if(CM4211_START_MODE == 0)
    _cpm_sleep_mode_sel(0x04);
    else if(CM4211_START_MODE == 1)
    _cpm_sleep_mode_sel(0x10);
    else
    _cpm_sleep_mode_sel(0x00);	
    // 当系统进入lowerpower或hibernation模式，CPM_IPS_SLPEN 应该被配置为0
    _cpm_set_cpm_ips_clk_sleep_dis;
    _cpm_pmu128k_sleep_dis;//PMU128K SLEEP OFF
    _cpm_rtc32k_sleep_dis;//PMU32K SLEEP OFF
    // 存储器不掉电
    _cpm_write_power_saving_mode_register(0x1faa000a);

    // overwrite OSCL STABLE/OSCH STABLE/VCC/CARDLDO TRIM.
    // drv_cpm_vcccore_testmodeset(0x01a60000); // 设置VCCCTMR
    _cpm_set_sleep_counter_val(0x00000080);
    _cpm_set_wakeup_counter_val(0x00000080);
    _cpm_set_wakeup_filter_val(0x00000040);
    // VCCCTMR bit18 set 1 ,before set_oscl_stable_time_value
    _cpm_set_oscl_stable_time_value(0x00);
    _cpm_set_osch_stable_time_value(0x001001FF);

    // wake-up digit filter enable, analog filter bypass.
    _cpm_wakeup_filter_en;
    _cpm_wakeup_filter_clk_gate_en;
    // VCCCTMR bit24 set 1 ,before wakeup_analog_filter_bypass_en
    _cpm_wakeup_analog_filter_bypass_en;
    _cpm_wakeup_filter_bypass_dis;
    // 使能wake_en wake_intm 唤醒源中断都有效。
    _cpm_write_wakeup_src(0x000303FF);

    NVIC_Init(3, 3, CPM_IRQn, 2);
    CPM_IRQHandler_Callback = drv_cpm_irqhandler;
    sys_standby();
}

/**
 * @brief CPM 模块芯片进入Lowpower低功耗（poweroff mode）函数
 * @param
 */
void drv_cpm_poweroff(void)
{

   if(CM4211_START_MODE == 0)
    _cpm_sleep_mode_sel(0x84);
   else if(CM4211_START_MODE == 1)
    _cpm_sleep_mode_sel(0x90);
   else
    _cpm_sleep_mode_sel(0x80);	

    _cpm_set_cpm_ips_clk_sleep_dis;

    _cpm_write_power_saving_mode_register(0x1faa000a);

    drv_cpm_vcccore_testmodeset(0x01860000);
    _cpm_set_sleep_counter_val(0x00000080);
    _cpm_set_wakeup_counter_val(0x00000080);
    _cpm_set_wakeup_filter_val(0x00000040);
    _cpm_set_oscl_stable_time_value(0x20);
    _cpm_set_osch_stable_time_value(0x001001FF);

    _cpm_wakeup_filter_en;
    _cpm_wakeup_filter_clk_gate_en;
    _cpm_wakeup_analog_filter_bypass_en;
    _cpm_wakeup_filter_bypass_dis;

    _cpm_write_wakeup_src(0x000303FF);


    NVIC_Init(3, 3, CPM_IRQn, 2);
    CPM_IRQHandler_Callback = drv_cpm_irqhandler;
    sys_standby();
}
/**
 * @brief CPM 模块SDRAM2LCD分频设置函数
 * 
 * @param div 分频系数
 */
void drv_cpm_sdram2lcd_module_set_div(uint8_t div)
{
    _cpm_set_peripheral_sdram2lcd_clk_div(div);
    _cpm_update_sys_clk_div;
    _cpm_update_peripheral_clk_div;
}

void drv_cpm_porset(void)
{
    _cpm_porset(0);
}