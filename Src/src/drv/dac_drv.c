/**
 * @file dac_drv.c
 * @author Product application department
 * @brief  DAC 模块驱动层
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "dac_drv.h"

// 函数定义

/**
 * @brief DAC 模块使能函数
 *
 */
void drv_dac_enable(void)
{
    _dac_en;
}

/**
 * @brief DAC模块禁用函数
 *
 */
void drv_dac_close(void)
{
    _dac_dis;
}

/**
 * @brief DAC 模块配置软件触发函数
 *
 */
void drv_dac_sw_trig(void)
{
    _dac_set_sw_trig;
}

/**
 * @brief DAC 模块初始化函数
 *
 * @param data_format 数据格式
 * @param trigger_select 触发方式
 * @param external_mode 外部触发模块
 * @param dma_en 是否使能DMA
 */
void drv_dac_init(dac_data_format_t data_format, dac_trigger_sel_t trigger_select, dac_ext_tmod_t external_mode, uint8_t dma_en)
{
    uint32_t cr_reg;

    if (LEFTALIGNED_8BITS == data_format)
    {
        cr_reg |= DAC_ALIGN;
    }
    else if (LEFTALIGNED_12BITS == data_format)
    {
        cr_reg |= (DAC_ALIGN | DAC_RES);
    }
    else if (RIGHTALIGNED_12BITS == data_format)
    {
        cr_reg |= DAC_RES;
    }
    else
        cr_reg = 0;

    cr_reg &= ~(DAC_TSEL_MASK | DAC_EXT_TMOD_MASK);
    cr_reg |= ((trigger_select << DAC_TSEL_SHIFT) | (external_mode << DAC_EXT_TMOD_SHIFT));
    if (dma_en == 1)
        cr_reg |= DAC_DMAEN;

    DAC->DAC_CR = cr_reg | DAC_DACEN;
    DAC->DAC_TRIMR &= ~(0x1000000);
    
}

/**
 * @brief DAC 模块反初始化函数
 *
 */
void drv_dac_deinit(void)
{
    _dac_clr_trigger_mode;
    _dac_dis;
}

/**
 * @brief DAC 等待数据完成函数
 *
 */
void drv_dac_wait_load_done(void)
{
    while (0 == (DAC->DAC_FSR & DAC_LD_DONE))
        ;
}

/**
 * @brief DAC 发送数据函数
 * @param data 待发送数据
 */
void drv_adc_send_data(uint16_t data)
{
    _dac_set_data(data);
    _dac_set_sw_trig;
    drv_dac_wait_load_done();
}
