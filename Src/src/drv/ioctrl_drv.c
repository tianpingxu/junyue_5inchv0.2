/**
 * @file ioctrl_drv.c
 * @author Product application department
 * @brief  IOCTRL 模块驱动层
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "ioctrl_drv.h"
#include "eport_drv.h"
#include "spi_drv.h"
#include "ccm_drv.h"
#include "i2c_drv.h"
#include "uart_drv.h"
#include "ccm_drv.h"

// 函数定义

/**
 * @brief IOCTRL 模块 SPI 输入使能控制函数
 *
 */
void drv_ioctrl_setspiie(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_ie_t ie)
{
    switch (ie)
    {
    case IE_INPUT_EN:
    {
        switch (spiid)
        {
        case IOCTRL_SPI1:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi1_mosi_input_en;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_miso_input_en;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_input_en;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_input_en;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI2:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi2_mosi_input_en;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_miso_input_en;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_input_en;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_input_en;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI3:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi3_mosi_input_en;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_miso_input_en;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_input_en;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_input_en;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IE_INPUT_DIS:
    {
        switch (spiid)
        {
        case IOCTRL_SPI1:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi1_mosi_input_dis;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_miso_input_dis;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_input_dis;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_input_dis;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI2:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi2_mosi_input_dis;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_miso_input_dis;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_input_dis;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_input_dis;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI3:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi3_mosi_input_dis;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_miso_input_dis;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_input_dis;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_input_dis;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块 SPI 输入上下拉控制函数
 *
 */
void drv_ioctrl_setspips(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_ps_t ps)
{
    switch (ps)
    {
    case PS_PULL_UP:
    {
        switch (spiid)
        {
        case IOCTRL_SPI1:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi1_mosi_pull_up;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_miso_pull_up;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_pull_up;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI2:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi2_mosi_pull_up;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_miso_pull_up;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_pull_up;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI3:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi3_mosi_pull_up;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_miso_pull_up;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_pull_up;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case PS_PULL_DOWN:
    {
        switch (spiid)
        {
        case IOCTRL_SPI1:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi1_mosi_pull_down;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_miso_pull_down;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_pull_down;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI2:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi2_mosi_pull_down;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_miso_pull_down;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_pull_down;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPI3:
        {
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
                _ioctrl_spi3_mosi_pull_down;
                break;
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_miso_pull_down;
                break;
            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_pull_down;
                break;
            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;

    case PS_PULL_NULL:
    {
        switch (spiid)
        {
        case IOCTRL_SPI1:
        {
            _spi_dis_pullup(SPI1);
        }
        break;
        case IOCTRL_SPI2:
        {
            _spi_dis_pullup(SPI2);
        }
        break;
        case IOCTRL_SPI3:
        {
            _spi_dis_pullup(SPI3);
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SPI 驱动力函数
 * @param pins SPI 引脚
 * @param ds 驱动能力
 */
void drv_ioctrl_setspids(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_ds_t ds)
{
    switch (ds)
    {
    case DS_2MA:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_ds_2ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_ds_2ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_ds_2ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_ds_2ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_ds_2ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_ds_2ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_ds_2ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_ds_2ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_ds_2ma;
                break;

            default:
                break;
            }
            break;
        }
        break;

    case DS_4MA:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_ds_4ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_ds_4ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_ds_4ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_ds_4ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_ds_4ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_ds_4ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_ds_4ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_ds_4ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_ds_4ma;
                break;

            default:
                break;
            }
            break;
        }
        break;
    case DS_8MA:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_ds_8ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_ds_8ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_ds_8ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_ds_8ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_ds_8ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_ds_8ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_ds_8ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_ds_8ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_ds_8ma;
                break;

            default:
                break;
            }
            break;
        }
        break;
    case DS_12MA:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_ds_12ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_ds_12ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_ds_12ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_ds_12ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_ds_12ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_ds_12ma;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_ds_12ma;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_ds_12ma;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_ds_12ma;
                break;

            default:
                break;
            }
            break;
        }
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SPI IO 翻转速率函数
 *
 * @param pins SPI 引脚
 * @param sr 翻转速率
 */
void drv_ioctrl_setspisr(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_sr_t sr)
{
    switch (sr)
    {
    case SR_SLEW_FAST:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_slew_fast;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_slew_fast;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_slew_fast;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_slew_fast;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_slew_fast;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_slew_fast;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_slew_fast;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_slew_fast;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_slew_fast;
                break;

            default:
                break;
            }
            break;
        }
        break;

    case SR_SLEW_SLOW:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_slew_slow;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_slew_slow;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_slew_slow;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_slew_slow;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_slew_slow;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_slew_slow;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_slew_slow;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_slew_slow;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_slew_slow;
                break;

            default:
                break;
            }
            break;
        }
        break;

    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SPI IO 输入属性函数
 *
 * @param pins SPI 引脚
 * @param sr 翻转速率
 */
void drv_ioctrl_setspiis(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_is_t is)
{
    switch (is)
    {
    case IS_INPUT_CMOS:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_input_cmos;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_input_cmos;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_input_cmos;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_input_cmos;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_input_cmos;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_input_cmos;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_input_cmos;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_input_cmos;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_input_cmos;
                break;

            default:
                break;
            }
            break;
        }
        break;

    case IS_INPUT_SCHMITT:
        switch (spiid)
        {
        case IOCTRL_SPI1:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi1_d_input_schmitt;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi1_sck_input_schmitt;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi1_ss_input_schmitt;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI2:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi2_d_input_schmitt;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi2_sck_input_schmitt;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi2_ss_input_schmitt;
                break;

            default:
                break;
            }
            break;
        case IOCTRL_SPI3:
            switch (spipin)
            {
            case IOCTRL_SPI_MOSI:
            case IOCTRL_SPI_MISO:
                _ioctrl_spi3_d_input_schmitt;
                break;

            case IOCTRL_SPI_SCK:
                _ioctrl_spi3_sck_input_schmitt;
                break;

            case IOCTRL_SPI_SS:
                _ioctrl_spi3_ss_input_schmitt;
                break;

            default:
                break;
            }
            break;
        }
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置I2C 驱动函数
 *
 * @param ds 驱动能力
 */
void drv_ioctrl_seti2cds(ioctrl_ds_t ds)
{
    switch (ds)
    {
    case DS_2MA:
        _ioctrl_i2c_ds_2ma;
        break;
    case DS_4MA:
        _ioctrl_i2c_ds_4ma;
        break;
    case DS_8MA:
        _ioctrl_i2c_ds_8ma;
        break;
    case DS_12MA:
        _ioctrl_i2c_ds_12ma;
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置I2C IO 翻转速率函数
 *
 * @param sr 翻转速率
 */
void drv_ioctrl_seti2csr(ioctrl_sr_t sr)
{
    switch (sr)
    {
    case SR_SLEW_FAST:
        _ioctrl_i2c_slew_fast;
        break;
    case SR_SLEW_SLOW:
        _ioctrl_i2c_slew_slow;
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置I2C IO 输入属性函数
 *
 * @param is 输入类型
 */
void drv_ioctrl_seti2cis(ioctrl_is_t is)
{
    switch (is)
    {
    case IS_INPUT_CMOS:
        _ioctrl_i2c_input_cmos;
        break;
    case IS_INPUT_SCHMITT:
        _ioctrl_i2c_input_schmitt;
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置I2C IO 上下拉函数
 *
 * @param pins I2C 引脚
 * @param ps 上拉/下拉/浮空
 */
void drv_ioctrl_seti2cps(ioctrl_i2cid_t i2cid, ioctrl_i2cpin_t i2cpins, ioctrl_ps_t ps)
{

    switch (ps)
    {
    case PS_PULL_UP:
        switch (i2cid)
        {
        case IOCTRL_I2C1:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c1_scl_pull_up;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c1_sda_pull_up;
                break;
            default:
                break;
            }
            break;
        case IOCTRL_I2C2:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c2_scl_pull_up;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c2_sda_pull_up;
                break;
            default:
                break;
            }
        }
        break;
    case PS_PULL_DOWN:
        switch (i2cid)
        {
        case IOCTRL_I2C1:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c1_scl_pull_down;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c1_sda_pull_down;
                break;
            default:
                break;
            }
            break;
        case IOCTRL_I2C2:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c2_scl_pull_down;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c2_sda_pull_down;
                break;
            default:
                break;
            }
        }
        break;
    case PS_PULL_NULL:
        switch (i2cid)
        {
        case IOCTRL_I2C1:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _i2c_scl_dis_pullup(I2C1);
                break;
            case IOCTRL_I2C_SDA:
                _i2c_sda_dis_pullup(I2C1);
                break;
            default:
                break;
            }
            break;
        case IOCTRL_I2C2:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _i2c_scl_dis_pullup(I2C2);
                break;
            case IOCTRL_I2C_SDA:
                _i2c_sda_dis_pullup(I2C2);
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}

/**
 * @brief IOCTRL 模块设置I2C IO 输入使能函数
 *
 * @param pins I2C 引脚
 * @param ie 输入使能
 */
void drv_ioctrl_seti2cie(ioctrl_i2cid_t i2cid, ioctrl_i2cpin_t i2cpins, ioctrl_ie_t ie)
{

    switch (ie)
    {
    case IE_INPUT_EN:
        switch (i2cid)
        {
        case IOCTRL_I2C1:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c1_scl_input_en;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c1_sda_input_en;
                break;
            default:
                break;
            }
            break;
        case IOCTRL_I2C2:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c2_scl_input_en;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c1_sda_input_en;
                break;
            default:
                break;
            }
        }
        break;
    case IE_INPUT_DIS:
        switch (i2cid)
        {
        case IOCTRL_I2C1:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c1_scl_input_dis;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c1_sda_input_dis;
                break;
            default:
                break;
            }
            break;
        case IOCTRL_I2C2:
            switch (i2cpins)
            {
            case IOCTRL_I2C_SCL:
                _ioctrl_i2c2_scl_input_dis;
                break;
            case IOCTRL_I2C_SDA:
                _ioctrl_i2c2_sda_input_dis;
                break;
            default:
                break;
            }
        }
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置UART 驱动力
 *
 * @param ds 驱动能力
 */
void drv_ioctrl_setuartds(ioctrl_ds_t ds)
{
    switch (ds)
    {
    case DS_2MA:
        _ioctrl_uart_ds_2ma;
        break;
    case DS_4MA:
        _ioctrl_uart_ds_4ma;
        break;
    case DS_8MA:
        _ioctrl_uart_ds_8ma;
        break;
    case DS_12MA:
        _ioctrl_uart_ds_12ma;
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置UART IO 翻转速率函数
 *
 * @param sr 翻转速率
 */
void drv_ioctrl_setuartsr(ioctrl_sr_t sr)
{
    switch (sr)
    {
    case SR_SLEW_FAST:
        _ioctrl_uart_slew_fast;
        break;
    case SR_SLEW_SLOW:
        _ioctrl_uart_slew_slow;
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置UART IO 输入属性函数
 *
 * @param is 输入类型
 */
void drv_ioctrl_setuartis(ioctrl_is_t is)
{
    switch (is)
    {
    case IS_INPUT_CMOS:
        _ioctrl_uart_input_cmos;
        break;
    case IS_INPUT_SCHMITT:
        _ioctrl_uart_input_schmitt;
        break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置UART IO 上下拉函数
 *
 * @param pins 串口引脚
 * @param ps 上拉/下拉/浮空
 */
void drv_ioctrl_setuartps(ioctrl_uartid_t uartid, ioctrl_uartpin_t uartpin, ioctrl_ps_t ps)
{
    switch (ps)
    {
    case PS_PULL_UP:
    {
        switch (uartid)
        {
        case IOCTRL_UART1:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart1_txd_pull_up;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart1_rxd_pull_up;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART2:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart2_txd_pull_up;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart2_rxd_pull_up;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART3:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart3_txd_pull_up;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart3_rxd_pull_up;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART4:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart4_txd_pull_up;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart4_rxd_pull_up;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART5:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart5_txd_pull_up;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart5_rxd_pull_up;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART6:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart6_txd_pull_up;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart6_rxd_pull_up;
                break;

            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case PS_PULL_DOWN:
    {
        switch (uartid)
        {
        case IOCTRL_UART1:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart1_txd_pull_down;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart1_rxd_pull_down;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART2:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart2_txd_pull_down;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart2_rxd_pull_down;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART3:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart3_txd_pull_down;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart3_rxd_pull_down;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART4:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart4_txd_pull_down;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart4_rxd_pull_down;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART5:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart5_txd_pull_down;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart5_rxd_pull_down;
                break;

            default:
                break;
            }
        }
        break;
        case IOCTRL_UART6:
        {
            switch (uartpin)
            {
            case IOCTRL_UART_TXD:
                _ioctrl_uart6_txd_pull_down;
                break;
            case IOCTRL_UART_RXD:
                _ioctrl_uart6_rxd_pull_down;
                break;

            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case PS_PULL_NULL:
    {
        switch (uartid)
        {
        case IOCTRL_UART1:
        {
            _uart_dis_pullup(UART1);
        }
        break;
        case IOCTRL_UART2:
        {
            _uart_dis_pullup(UART2);
        }
        break;
        case IOCTRL_UART3:
        {
            _uart_dis_pullup(UART3);
        }
        break;
        case IOCTRL_UART4:
        {
            _uart_dis_pullup(UART4);
        }
        break;
        case IOCTRL_UART5:
        {
            _uart_dis_pullup(UART5);
        }
        break;
        case IOCTRL_UART6:
        {
            _uart_dis_pullup(UART6);
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置EPORT 驱动力函数
 *
 * @param ds 驱动能力
 */
void drv_ioctrl_seteportds(ioctrl_eportid_t id, eport_pin_t pins, ioctrl_ds_t ds)
{
    if (id == IOCTRL_EPORT0)
    {
        if (pins == EPORT0_PIN0 | pins == EPORT0_PIN1)
        {
            switch (ds)
            {
            case DS_2MA:
                _ccm_set_rstout_clkout_ds(CCM, DS_2MA);
                break;
            case DS_4MA:
                _ccm_set_rstout_clkout_ds(CCM, DS_4MA);
                break;
            case DS_8MA:
                _ccm_set_rstout_clkout_ds(CCM, DS_8MA);
                break;
            case DS_12MA:
                _ccm_set_rstout_clkout_ds(CCM, DS_12MA);
                break;
            default:
                break;
            }
        }

        else if (pins == EPORT0_PIN2 | pins == EPORT0_PIN3 | pins == EPORT2_PIN6 | pins == EPORT2_PIN7 | pins == EPORT6_PIN6 | pins == EPORT6_PIN7 | pins == EPORT3_PIN6 | pins == EPORT3_PIN7 | pins == EPORT4_PIN6 | pins == EPORT4_PIN7 | pins == EPORT6_PIN1 | pins == EPORT6_PIN2)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_uart_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_uart_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_uart_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_uart_ds_12ma;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN4)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spi2_ss_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spi2_ss_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spi2_ss_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spi2_ss_ds_12ma;
                break;
            default:
                break;
            }
        }

        else if (pins == EPORT0_PIN5)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spi2_sck_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spi2_sck_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spi2_sck_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spi2_sck_ds_12ma;
                break;
            default:
                break;
            }
        }

        else if (pins == EPORT0_PIN6 | pins == EPORT0_PIN7)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spi2_d_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spi2_d_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spi2_d_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spi2_d_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT1)
    {
        if (pins == EPORT1_PIN0 | pins == EPORT1_PIN1 | pins == EPORT1_PIN2 | pins == EPORT1_PIN3 | pins == EPORT1_PIN4)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_sdhdat_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_sdhdat_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_sdhdat_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_sdhdat_ds_12ma;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN5 | pins == EPORT1_PIN6 | pins == EPORT1_PIN7)

        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_eport1_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_eport1_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_eport1_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_eport1_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT2)
    {
        if (pins == EPORT2_PIN0)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim1_ss_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim1_ss_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim1_ss_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim1_ss_ds_12ma;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN1)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim1_sck_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim1_sck_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim1_sck_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim1_sck_ds_12ma;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN2 | pins == EPORT2_PIN3 | pins == EPORT2_PIN4 | pins == EPORT2_PIN5)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim1_d_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim1_d_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim1_d_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim1_d_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT3)
    {
        if (pins == EPORT3_PIN0 | pins == EPORT3_PIN1 | pins == EPORT6_PIN5 | pins == EPORT8_PIN4 | pins == EPORT7_PIN0 | pins == EPORT7_PIN1 | pins == EPORT7_PIN2 | pins == EPORT7_PIN3 | pins == EPORT7_PIN4 | pins == EPORT7_PIN5 | pins == EPORT7_PIN6 | pins == EPORT7_PIN7 | pins == EPORT8_PIN0 | pins == EPORT8_PIN1 | pins == EPORT8_PIN2 | pins == EPORT8_PIN3 | pins == EPORT3_PIN2 | pins == EPORT3_PIN3 | pins == EPORT3_PIN4 | pins == EPORT3_PIN5 | pins == EPORT9_PIN0 | pins == EPORT9_PIN1 | pins == EPORT9_PIN2 | pins == EPORT9_PIN3 | pins == EPORT9_PIN4 | pins == EPORT9_PIN5 | pins == EPORT9_PIN6 | pins == EPORT9_PIN7)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_clcdcr_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_clcdcr_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_clcdcr_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_clcdcr_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT4)
    {
        if (pins == EPORT4_PIN0)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim3_ss_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim3_ss_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim3_ss_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim3_ss_ds_12ma;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN1)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim3_sck_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim3_sck_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim3_sck_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim3_sck_ds_12ma;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN2 | pins == EPORT4_PIN3 | pins == EPORT4_PIN4 | pins == EPORT4_PIN5)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim3_d_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim3_d_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim3_d_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim3_d_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT5)
    {
        if (pins == EPORT5_PIN0 | pins == EPORT5_PIN1 | pins == EPORT5_PIN2 | pins == EPORT5_PIN3 | pins == EPORT5_PIN4 | pins == EPORT5_PIN5 | pins == EPORT5_PIN6 | pins == EPORT5_PIN7 | pins == EPORT6_PIN0)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_gmacwkcr_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_gmacwkcr_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_gmacwkcr_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_gmacwkcr_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT6)
    {
        if (pins == EPORT6_PIN3 | pins == EPORT6_PIN4)
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_wkusbdetcr_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_wkusbdetcr_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_wkusbdetcr_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_wkusbdetcr_ds_12ma;
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief IOCTRL 模块设置EPORT 翻转速率函数
 *
 * @param ds 驱动能力
 */
void drv_ioctrl_seteportsr(ioctrl_eportid_t id, eport_pin_t pins, ioctrl_sr_t sr)
{
    if (id == IOCTRL_EPORT0)
    {
        if (pins == EPORT0_PIN0 | pins == EPORT0_PIN1)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_rstout_clkout_slew_fast(CCM);
                break;
            case SR_SLEW_SLOW:
                _ioctrl_rstout_clkout_slew_slow(CCM);
                break;
            default:
                break;
            }
        }

        else if (pins == EPORT0_PIN2 | pins == EPORT0_PIN3 | pins == EPORT2_PIN6 | pins == EPORT2_PIN7 | pins == EPORT6_PIN6 | pins == EPORT6_PIN7 | pins == EPORT3_PIN6 | pins == EPORT3_PIN7 | pins == EPORT4_PIN6 | pins == EPORT4_PIN7 | pins == EPORT6_PIN1 | pins == EPORT6_PIN2)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_uart_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_uart_slew_slow;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN4)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spi2_ss_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spi2_ss_slew_slow;
                break;

            default:
                break;
            }
        }

        else if (pins == EPORT0_PIN5)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spi2_sck_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spi2_sck_slew_slow;
                break;
            default:
                break;
            }
        }

        else if (pins == EPORT0_PIN6 | pins == EPORT0_PIN7)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spi2_d_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spi2_d_slew_slow;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT1)
    {
        if (pins == EPORT1_PIN0 | pins == EPORT1_PIN1 | pins == EPORT1_PIN2 | pins == EPORT1_PIN3 | pins == EPORT1_PIN4)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_sdhdat_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_sdhdat_slew_slow;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN5 | pins == EPORT1_PIN6 | pins == EPORT1_PIN7)

        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_eport1_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_eport1_slew_slow;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT2)
    {
        if (pins == EPORT2_PIN0)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim1_ss_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim1_ss_slew_slow;
                break;

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN1)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim1_sck_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim1_sck_slew_slow;
                break;

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN2 | pins == EPORT2_PIN3 | pins == EPORT2_PIN4 | pins == EPORT2_PIN5)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim1_d_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim1_d_slew_slow;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT3)
    {
        if (pins == EPORT3_PIN0 | pins == EPORT3_PIN1 | pins == EPORT6_PIN5 | pins == EPORT8_PIN4 | pins == EPORT7_PIN0 | pins == EPORT7_PIN1 | pins == EPORT7_PIN2 | pins == EPORT7_PIN3 | pins == EPORT7_PIN4 | pins == EPORT7_PIN5 | pins == EPORT7_PIN6 | pins == EPORT7_PIN7 | pins == EPORT8_PIN0 | pins == EPORT8_PIN1 | pins == EPORT8_PIN2 | pins == EPORT8_PIN3 | pins == EPORT3_PIN2 | pins == EPORT3_PIN3 | pins == EPORT3_PIN4 | pins == EPORT3_PIN5 | pins == EPORT9_PIN0 | pins == EPORT9_PIN1 | pins == EPORT9_PIN2 | pins == EPORT9_PIN3 | pins == EPORT9_PIN4 | pins == EPORT9_PIN5 | pins == EPORT9_PIN6 | pins == EPORT9_PIN7)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_clcdcr_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_clcdcr_slew_slow;
                break;
            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT4)
    {
        if (pins == EPORT4_PIN0)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim3_ss_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim3_ss_slew_slow;
                break;

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN1)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim3_sck_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim3_sck_slew_slow;
                break;
            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN2 | pins == EPORT4_PIN3 | pins == EPORT4_PIN4 | pins == EPORT4_PIN5)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim3_d_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim3_d_slew_slow;
                break;

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT5)
    {
        if (pins == EPORT5_PIN0 | pins == EPORT5_PIN1 | pins == EPORT5_PIN2 | pins == EPORT5_PIN3 | pins == EPORT5_PIN4 | pins == EPORT5_PIN5 | pins == EPORT5_PIN6 | pins == EPORT5_PIN7 | pins == EPORT6_PIN0)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_gmacwkcr_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_gmacwkcr_slew_slow;
                break;

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT6)
    {
        if (pins == EPORT6_PIN3 | pins == EPORT6_PIN4)
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_wkusbdetcr_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_wkusbdetcr_slew_slow;
                break;

            default:
                break;
            }
        }
    }
}

/**
 * @brief  IOCTRL 模块设置EPORT引脚输入函数
 * @param pins EPORT 引脚
 * @param ps 上拉 /下拉/浮空
 */
void drv_ioctrl_seteportps(ioctrl_eportid_t id, eport_pin_t pins, ioctrl_ps_t ps)
{
    if (id == IOCTRL_EPORT0)
    {
        if (pins == EPORT0_PIN0)
        {
            _ioctrl_eport0_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN0);
                _ccm_en_clkout_ps(CCM);
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN0);
                _ccm_dis_clkout_ps(CCM);
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN1)
        {
            _ioctrl_eport0_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN1);
                _ccm_en_rstout_ps(CCM);
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN1);
                _ccm_dis_rstout_ps(CCM);
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN2)
        {
            _ioctrl_eport0_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN2);
                _ioctrl_uart1_txd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN1);
                _ioctrl_uart1_txd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN3)
        {
            _ioctrl_eport0_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN3);
                _ioctrl_uart1_rxd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN3);
                _ioctrl_uart1_rxd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN4)
        {
            _ioctrl_eport0_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN4);
                _ioctrl_spi2_ss_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN4);
                _ioctrl_spi2_ss_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN5)
        {
            _ioctrl_eport0_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN5);
                _ioctrl_spi2_sck_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN5);
                _ioctrl_spi2_sck_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN6)
        {
            _ioctrl_eport0_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN6);
                _ioctrl_spi2_miso_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN6);
                _ioctrl_spi2_miso_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT0_PIN7)
        {
            _ioctrl_eport0_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN7);
                _ioctrl_spi2_mosi_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN7);
                _ioctrl_spi2_mosi_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT1)
    {
        if (pins == EPORT1_PIN0)
        {
            _ioctrl_eport1_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT0, EPORT0_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN7);
                _ioctrl_spi2_mosi_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT0, EPORT0_PIN7);
                _ioctrl_spi2_mosi_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT0, EPORT0_PIN7);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN0) // 不支持下拉
        {
            _ioctrl_eport1_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN0);
                _ioctrl_spi2_mosi_pull_up;
                break;
            case PS_PULL_DOWN:
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN1) // 不支持下拉
        {
            _ioctrl_eport1_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT0_PIN1);
                _ioctrl_spi2_mosi_pull_up;
                break;
            case PS_PULL_DOWN:
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT0_PIN7);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN2)
        {
            _ioctrl_eport1_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN2);
                _ioctrl_sdhcr_data3_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN2);
                _ioctrl_sdhcr_data3_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN3)
        {
            _ioctrl_eport1_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN3);
                _ioctrl_sdhcr_data2_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN3);
                _ioctrl_sdhcr_data2_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN4)
        {
            _ioctrl_eport1_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN4);
                _ioctrl_sdhcr_data1_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN4);
                _ioctrl_sdhcr_data1_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN5)
        {
            _ioctrl_eport1_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN5);
                _ioctrl_sdhcr_data0_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN5);
                _ioctrl_sdhcr_data0_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN6)
        {
            _ioctrl_eport1_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN6);
                _ioctrl_eport1_pin6_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN6);
                _ioctrl_eport1_pin6_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT1_PIN7)
        {
            _ioctrl_eport1_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT1, EPORT1_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN7);
                _ioctrl_eport1_pin7_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT1, EPORT1_PIN7);
                _ioctrl_eport1_pin7_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT1, EPORT1_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT2)
    {
        if (pins == EPORT2_PIN0)
        {
            _ioctrl_eport2_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN0);
                _ioctrl_spim1_ss_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN0);
                _ioctrl_spim1_ss_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN1)
        {
            _ioctrl_eport2_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN1);
                _ioctrl_spim1_sck_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN1);
                _ioctrl_spim1_sck_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN2)
        {
            _ioctrl_eport2_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN2);
                _ioctrl_spim1_d3_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN2);
                _ioctrl_spim1_d3_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN3)
        {
            _ioctrl_eport2_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN3);
                _ioctrl_spim1_d2_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN3);
                _ioctrl_spim1_d2_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN4)
        {
            _ioctrl_eport2_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN4);
                _ioctrl_spim1_d1_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN4);
                _ioctrl_spim1_d1_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN5)
        {
            _ioctrl_eport2_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN5);
                _ioctrl_spim1_d0_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN5);
                _ioctrl_spim1_d0_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN6)
        {
            _ioctrl_eport2_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN6);
                _ioctrl_uart3_txd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN6);
                _ioctrl_uart3_txd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT2_PIN7)
        {
            _ioctrl_eport2_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT2, EPORT2_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN7);
                _ioctrl_uart3_rxd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT2, EPORT2_PIN7);
                _ioctrl_uart3_rxd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT2, EPORT2_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT3)
    {
        if (pins == EPORT3_PIN0)
        {
            _ioctrl_eport3_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN0);
                _ioctrl_clfp_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN0);
                _ioctrl_clfp_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN1)
        {
            _ioctrl_eport3_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN1);
                _ioctrl_clac_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN1);
                _ioctrl_clac_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN2)
        {
            _ioctrl_eport3_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN2);
                _ioctrl_clcdd12_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN2);
                _ioctrl_clcdd12_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN3)
        {
            _ioctrl_eport3_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN3);
                _ioctrl_clcdd13_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN3);
                _ioctrl_clcdd13_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN4)
        {
            _ioctrl_eport3_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN4);
                _ioctrl_clcdd14_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN4);
                _ioctrl_clcdd14_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN5)
        {
            _ioctrl_eport3_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN5);
                _ioctrl_clcdd15_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN5);
                _ioctrl_clcdd15_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN6)
        {
            _ioctrl_eport3_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN6);
                _ioctrl_uart4_txd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN6);
                _ioctrl_uart4_txd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT3_PIN7)
        {
            _ioctrl_eport3_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT3, EPORT3_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN7);
                _ioctrl_uart4_rxd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT3, EPORT3_PIN7);
                _ioctrl_uart4_rxd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT3, EPORT3_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT4)
    {
        if (pins == EPORT4_PIN0)
        {
            _ioctrl_eport4_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN0);
                _ioctrl_spim3_ss_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN0);
                _ioctrl_spim3_ss_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN1)
        {
            _ioctrl_eport4_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN1);
                _ioctrl_spim3_sck_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN1);
                _ioctrl_spim3_sck_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN2)
        {
            _ioctrl_eport4_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN2);
                _ioctrl_spim3_d3_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN2);
                _ioctrl_spim3_d3_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN3)
        {
            _ioctrl_eport4_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN3);
                _ioctrl_spim3_d2_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN3);
                _ioctrl_spim3_d2_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN4)
        {
            _ioctrl_eport4_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN4);
                _ioctrl_spim3_d1_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN4);
                _ioctrl_spim3_d1_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN5)
        {
            _ioctrl_eport4_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN5);
                _ioctrl_spim3_d0_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN5);
                _ioctrl_spim3_d0_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN6)
        {
            _ioctrl_eport4_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN6);
                _ioctrl_uart5_txd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN6);
                _ioctrl_uart5_txd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT4_PIN7)
        {
            _ioctrl_eport4_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT4, EPORT4_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN7);
                _ioctrl_uart5_rxd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT4, EPORT4_PIN7);
                _ioctrl_uart5_rxd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT4, EPORT4_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT5)
    {
        if (pins == EPORT5_PIN0) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN0);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN0);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN1) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN1);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN1);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN2) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN2);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN2);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN3) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN3);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN3);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN4) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN4);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN4);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN5) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN5);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN5);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN6) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN6);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN6);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT5_PIN7) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport5_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT5_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN7);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT5_PIN7);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT5_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT6)
    {
        if (pins == EPORT6_PIN0) // EPORT5_PIN0~EPORT6_PIN0 只能同时一起上拉或者一起下拉
        {
            _ioctrl_eport6_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT5, EPORT6_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT6_PIN0);
                _ioctrl_gmacwkcr_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT5, EPORT6_PIN0);
                _ioctrl_gmacwkcr_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT5, EPORT6_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN1)
        {
            _ioctrl_eport6_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN1);
                _ioctrl_uart6_txd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN1);
                _ioctrl_uart6_txd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN2)
        {
            _ioctrl_eport6_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN2);
                _ioctrl_uart6_rxd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN2);
                _ioctrl_uart6_rxd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN3)
        {
            _ioctrl_eport6_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN3);
                _ioctrl_wakeup_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN3);
                _ioctrl_wakeup_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN4)
        {
            _ioctrl_eport6_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN4);
                _ioctrl_usbdet_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN4);
                _ioctrl_usbdet_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN5)
        {
            _ioctrl_eport6_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN5);
                _ioctrl_clcdclcp_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN5);
                _ioctrl_clcdclcp_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN6)
        {
            _ioctrl_eport6_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN6);
                _ioctrl_uart2_txd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN6);
                _ioctrl_uart2_txd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT6_PIN7)
        {
            _ioctrl_eport6_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT6, EPORT6_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN7);
                _ioctrl_uart2_rxd_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT6, EPORT6_PIN7);
                _ioctrl_uart2_rxd_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT6, EPORT6_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT7)
    {
        if (pins == EPORT7_PIN0)
        {
            _ioctrl_eport7_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN0);
                _ioctrl_clcdd0_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN0);
                _ioctrl_clcdd0_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN1)
        {
            _ioctrl_eport7_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN1);
                _ioctrl_clcdd1_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN1);
                _ioctrl_clcdd1_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN2)
        {
            _ioctrl_eport7_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN2);
                _ioctrl_clcdd2_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN2);
                _ioctrl_clcdd2_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN3)
        {
            _ioctrl_eport7_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN3);
                _ioctrl_clcdd3_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN3);
                _ioctrl_clcdd3_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN4)
        {
            _ioctrl_eport7_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN4);
                _ioctrl_clcdd4_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN4);
                _ioctrl_clcdd4_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN5)
        {
            _ioctrl_eport7_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN5);
                _ioctrl_clcdd5_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN5);
                _ioctrl_clcdd5_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN6)
        {
            _ioctrl_eport7_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN6);
                _ioctrl_clcdd6_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN6);
                _ioctrl_clcdd6_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT7_PIN7)
        {
            _ioctrl_eport7_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT7, EPORT7_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN7);
                _ioctrl_clcdd7_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT7, EPORT7_PIN7);
                _ioctrl_clcdd7_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT7, EPORT7_PIN7);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT8)
    {
        if (pins == EPORT8_PIN0)
        {
            _ioctrl_eport8_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT8, EPORT8_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN0);
                _ioctrl_clcdd8_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN0);
                _ioctrl_clcdd8_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT8, EPORT8_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT8_PIN1)
        {
            _ioctrl_eport8_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT8, EPORT8_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN1);
                _ioctrl_clcdd9_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN1);
                _ioctrl_clcdd9_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT8, EPORT8_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT8_PIN2)
        {
            _ioctrl_eport8_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT8, EPORT8_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN2);
                _ioctrl_clcdd10_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN2);
                _ioctrl_clcdd10_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT8, EPORT8_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT8_PIN3)
        {
            _ioctrl_eport8_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT8, EPORT8_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN3);
                _ioctrl_clcdd11_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN3);
                _ioctrl_clcdd11_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT8, EPORT8_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT8_PIN4)
        {
            _ioctrl_eport8_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT8, EPORT8_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN4);
                _ioctrl_clcdcllp_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT8, EPORT8_PIN4);
                _ioctrl_clcdcllp_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT8, EPORT8_PIN4);

            default:
                break;
            }
        }
    }
    else if (id == IOCTRL_EPORT9)
    {
        if (pins == EPORT9_PIN0)
        {
            _ioctrl_eport9_pin0_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN0);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN0);
                _ioctrl_clcdd16_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN0);
                _ioctrl_clcdd16_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN0);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN1)
        {
            _ioctrl_eport9_pin1_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN1);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN1);
                _ioctrl_clcdd17_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN1);
                _ioctrl_clcdd17_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN1);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN2)
        {
            _ioctrl_eport9_pin2_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN2);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN2);
                _ioctrl_clcdd18_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN2);
                _ioctrl_clcdd18_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN2);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN3)
        {
            _ioctrl_eport9_pin3_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN3);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN3);
                _ioctrl_clcdd19_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN3);
                _ioctrl_clcdd19_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN3);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN4)
        {
            _ioctrl_eport9_pin4_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN4);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN4);
                _ioctrl_clcdd20_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN4);
                _ioctrl_clcdd20_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN4);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN5)
        {
            _ioctrl_eport9_pin5_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN5);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN5);
                _ioctrl_clcdd21_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN5);
                _ioctrl_clcdd21_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN5);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN6)
        {
            _ioctrl_eport9_pin6_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN6);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN6);
                _ioctrl_clcdd22_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN6);
                _ioctrl_clcdd22_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN6);

            default:
                break;
            }
        }
        else if (pins == EPORT9_PIN7)
        {
            _ioctrl_eport9_pin7_input_en;
            _eport_epddr_pins_input_set(EPORT9, EPORT9_PIN7);
            switch (ps)
            {
            case PS_PULL_UP:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN7);
                _ioctrl_clcdd23_pull_up;
                break;
            case PS_PULL_DOWN:
                _eport_eppuer_pins_pull_up_en(EPORT9, EPORT9_PIN7);
                _ioctrl_clcdd23_pull_down;
                break;
            case PS_PULL_NULL:
                _eport_eppuer_pins_pull_up_dis(EPORT9, EPORT9_PIN7);

            default:
                break;
            }
        }
    }
}

/**
 * @brief IOCTRL 模块设置SSI 驱动力函数
 *
 * @param ds 驱动能力
 */
void drv_ioctrl_setssids(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ds_t ds)
{
    switch (ssiid)
    {
    case IOCTRL_SPIM1:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim1_ss_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim1_ss_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim1_ss_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim1_ss_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim1_sck_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim1_sck_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim1_sck_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim1_sck_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        case IOCTRL_SPIM_D1:
        case IOCTRL_SPIM_D2:
        case IOCTRL_SPIM_D3:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim1_d_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim1_d_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim1_d_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim1_d_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM2:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim2_ss_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim2_ss_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim2_ss_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim2_ss_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim2_sck_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim2_sck_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim2_sck_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim2_sck_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        case IOCTRL_SPIM_D1:
        case IOCTRL_SPIM_D2:
        case IOCTRL_SPIM_D3:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim2_d_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim2_d_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim2_d_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim2_d_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM3:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim3_ss_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim3_ss_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim3_ss_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim3_ss_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim3_sck_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim3_sck_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim3_sck_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim3_sck_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        case IOCTRL_SPIM_D1:
        case IOCTRL_SPIM_D2:
        case IOCTRL_SPIM_D3:
        {
            switch (ds)
            {
            case DS_2MA:
                _ioctrl_spim3_d_ds_2ma;
                break;
            case DS_4MA:
                _ioctrl_spim3_d_ds_4ma;
                break;
            case DS_8MA:
                _ioctrl_spim3_d_ds_8ma;
                break;
            case DS_12MA:
                _ioctrl_spim3_d_ds_12ma;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SSI 翻转速率函数
 *
 * @param sr 翻转速率
 */
void drv_ioctrl_setssisr(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_sr_t sr)
{
    switch (ssiid)
    {
    case IOCTRL_SPIM1:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim1_ss_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim1_ss_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim1_sck_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim1_sck_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        case IOCTRL_SPIM_D1:
        case IOCTRL_SPIM_D2:
        case IOCTRL_SPIM_D3:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim1_d_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim1_d_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM2:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim2_ss_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim2_ss_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim2_sck_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim2_sck_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        case IOCTRL_SPIM_D1:
        case IOCTRL_SPIM_D2:
        case IOCTRL_SPIM_D3:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim2_d_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim2_d_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM3:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim3_ss_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim3_ss_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim3_sck_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim3_sck_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        case IOCTRL_SPIM_D1:
        case IOCTRL_SPIM_D2:
        case IOCTRL_SPIM_D3:
        {
            switch (sr)
            {
            case SR_SLEW_FAST:
                _ioctrl_spim3_d_slew_fast;
                break;
            case SR_SLEW_SLOW:
                _ioctrl_spim3_d_slew_slow;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SSI 输入使能函数
 *
 * @param ie 输入使能
 */
void drv_ioctrl_setssiie(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ie_t ie)
{

    switch (ssiid)
    {
    case IOCTRL_SPIM1:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim1_ss_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim1_ss_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim1_sck_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim1_sck_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim1_d0_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim1_d0_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D1:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim1_d1_input_dis;

                break;
            case IE_INPUT_EN:
                _ioctrl_spim1_d1_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D2:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim1_d2_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim1_d2_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D3:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim1_d3_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim1_d3_input_en;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM2:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim2_ss_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim2_ss_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim2_sck_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim2_sck_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim2_d0_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim2_d0_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D1:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim2_d1_input_dis;

                break;
            case IE_INPUT_EN:
                _ioctrl_spim2_d1_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D2:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim2_d2_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim2_d2_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D3:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim2_d3_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim2_d3_input_en;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM3:
    {
        switch (ssipins)
        {
        case IOCTRL_SPIM_SS:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim3_ss_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim3_ss_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_SCK:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim3_sck_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim3_sck_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D0:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim3_d0_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim3_d0_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D1:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim3_d1_input_dis;

                break;
            case IE_INPUT_EN:
                _ioctrl_spim3_d1_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D2:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim3_d2_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim3_d2_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM_D3:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_spim3_d3_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_spim3_d3_input_en;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SSI 输出属性函数
 *
 * @param ode 输出属性
 */
void drv_ioctrl_setssiide(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ode_t ode)
{

    switch (ssiid)
    {
    case IOCTRL_SPIM1:
    {
        switch (ode)
        {
        case ODE_OUTPUT_CMOS:
            _ioctrl_spim1_output_cmos;
            break;
        case ODE_OUTPUT_OPEN_DRAIN:
            _ioctrl_spim1_output_open_d;
            break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM2:
    {
        switch (ode)
        {
        case ODE_OUTPUT_CMOS:
            _ioctrl_spim2_output_cmos;
            break;
        case ODE_OUTPUT_OPEN_DRAIN:
            _ioctrl_spim2_output_open_d;
            break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_SPIM3:
    {
        switch (ode)
        {
        case ODE_OUTPUT_CMOS:
            _ioctrl_spim3_output_cmos;
            break;
        case ODE_OUTPUT_OPEN_DRAIN:
            _ioctrl_spim3_output_open_d;
            break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块设置SSI 输入模式函数
 *
 * @param ps 上拉/下拉/输入浮空
 */
void drv_ioctrl_setssips(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ps_t ps)
{
    switch (ps)
    {
    case PS_PULL_UP:
    {
        switch (ssiid)
        {
        case IOCTRL_SPIM1:
        {
            _ioctrl_spim1_pull_up_down_en;
            switch (ssipins)
            {
            case IOCTRL_SPIM_SS:
                _ioctrl_spim1_ss_pull_up;
                break;
            case IOCTRL_SPIM_SCK:
                _ioctrl_spim1_sck_pull_up;
                break;
            case IOCTRL_SPIM_D0:
                _ioctrl_spim1_d0_pull_up;
                break;
            case IOCTRL_SPIM_D1:
                _ioctrl_spim1_d1_pull_up;
                break;
            case IOCTRL_SPIM_D2:
                _ioctrl_spim1_d2_pull_up;
                break;
            case IOCTRL_SPIM_D3:
                _ioctrl_spim1_d3_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM2:
        {
            _ioctrl_spim2_pull_up_down_en;
            switch (ssipins)
            {
            case IOCTRL_SPIM_SS:
                _ioctrl_spim2_ss_pull_up;
                break;
            case IOCTRL_SPIM_SCK:
                _ioctrl_spim2_sck_pull_up;
                break;
            case IOCTRL_SPIM_D0:
                _ioctrl_spim2_d0_pull_up;
                break;
            case IOCTRL_SPIM_D1:
                _ioctrl_spim2_d1_pull_up;
                break;
            case IOCTRL_SPIM_D2:
                _ioctrl_spim2_d2_pull_up;
                break;
            case IOCTRL_SPIM_D3:
                _ioctrl_spim2_d3_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM3:
        {
            _ioctrl_spim2_pull_up_down_en;
            switch (ssipins)
            {
            case IOCTRL_SPIM_SS:
                _ioctrl_spim3_ss_pull_up;
                break;
            case IOCTRL_SPIM_SCK:
                _ioctrl_spim3_sck_pull_up;
                break;
            case IOCTRL_SPIM_D0:
                _ioctrl_spim3_d0_pull_up;
                break;
            case IOCTRL_SPIM_D1:
                _ioctrl_spim3_d1_pull_up;
                break;
            case IOCTRL_SPIM_D2:
                _ioctrl_spim3_d2_pull_up;
                break;
            case IOCTRL_SPIM_D3:
                _ioctrl_spim3_d3_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case PS_PULL_DOWN:
    {
        switch (ssiid)
        {
        case IOCTRL_SPIM1:
        {
            _ioctrl_spim1_pull_up_down_en;
            switch (ssipins)
            {
            case IOCTRL_SPIM_SS:
                _ioctrl_spim1_ss_pull_down;
                break;
            case IOCTRL_SPIM_SCK:
                _ioctrl_spim1_sck_pull_down;
                break;
            case IOCTRL_SPIM_D0:
                _ioctrl_spim1_d0_pull_down;
                break;
            case IOCTRL_SPIM_D1:
                _ioctrl_spim1_d1_pull_down;
                break;
            case IOCTRL_SPIM_D2:
                _ioctrl_spim1_d2_pull_down;
                break;
            case IOCTRL_SPIM_D3:
                _ioctrl_spim1_d3_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM2:
        {
            _ioctrl_spim2_pull_up_down_en;
            switch (ssipins)
            {
            case IOCTRL_SPIM_SS:
                _ioctrl_spim2_ss_pull_down;
                break;
            case IOCTRL_SPIM_SCK:
                _ioctrl_spim2_sck_pull_down;
                break;
            case IOCTRL_SPIM_D0:
                _ioctrl_spim2_d0_pull_down;
                break;
            case IOCTRL_SPIM_D1:
                _ioctrl_spim2_d1_pull_down;
                break;
            case IOCTRL_SPIM_D2:
                _ioctrl_spim2_d2_pull_down;
                break;
            case IOCTRL_SPIM_D3:
                _ioctrl_spim2_d3_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_SPIM3:
        {
            _ioctrl_spim2_pull_up_down_en;
            switch (ssipins)
            {
            case IOCTRL_SPIM_SS:
                _ioctrl_spim3_ss_pull_down;
                break;
            case IOCTRL_SPIM_SCK:
                _ioctrl_spim3_sck_pull_down;
                break;
            case IOCTRL_SPIM_D0:
                _ioctrl_spim3_d0_pull_down;
                break;
            case IOCTRL_SPIM_D1:
                _ioctrl_spim3_d1_pull_down;
                break;
            case IOCTRL_SPIM_D2:
                _ioctrl_spim3_d2_pull_down;
                break;
            case IOCTRL_SPIM_D3:
                _ioctrl_spim3_d3_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;

    case PS_PULL_NULL:
    {
        switch (ssiid)
        {
        case IOCTRL_SPIM1:
        {
            _ioctrl_spim1_pull_up_down_dis;
        }
        break;
        case IOCTRL_SPIM2:
        {
            _ioctrl_spim2_pull_up_down_dis;
        }
        break;
        case IOCTRL_SPIM3:
        {
            _ioctrl_spim3_pull_up_down_dis;
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief  IOCTRL 模块设置I2S 驱动力函数
 *
 * @param ds 驱动能力
 */
void drv_ioctrl_seti2sds(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spin, ioctrl_ds_t ds)
{
    switch (ds)
    {
    case DS_2MA:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
            _ioctrl_i2siocr_i2s1_ds_2ma;

            break;
        case IOCTRL_I2S2:
            _ioctrl_i2siocr_i2s2_ds_2ma;
            break;
        default:
            break;
        }
    }
    break;
    case DS_4MA:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
            _ioctrl_i2siocr_i2s1_ds_4ma;

            break;
        case IOCTRL_I2S2:
            _ioctrl_i2siocr_i2s2_ds_4ma;
            break;
        default:
            break;
        }
    }
    break;
    case DS_8MA:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
            _ioctrl_i2siocr_i2s1_ds_8ma;

            break;
        case IOCTRL_I2S2:
            _ioctrl_i2siocr_i2s2_ds_8ma;
            break;
        default:
            break;
        }
    }
    break;
    case DS_12MA:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
            _ioctrl_i2siocr_i2s1_ds_12ma;

            break;
        case IOCTRL_I2S2:
            _ioctrl_i2siocr_i2s2_ds_12ma;
            break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief  IOCTRL 模块设置I2S 翻转速率函数
 *
 * @param sr 翻转速率
 */
void drv_ioctrl_seti2ssr(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spin, ioctrl_sr_t sr)
{
    switch (sr)
    {
    case SR_SLEW_FAST:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
            _ioctrl_i2siocr_i2s1_slew_fast;

            break;
        case IOCTRL_I2S2:
            _ioctrl_i2siocr_i2s2_slew_fast;
            break;
        default:
            break;
        }
    }
    break;
    case SR_SLEW_SLOW:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
            _ioctrl_i2siocr_i2s1_slew_slow;

            break;
        case IOCTRL_I2S2:
            _ioctrl_i2siocr_i2s2_slew_slow;

            break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块I2S 输入功能是否开启
 *
 * @param pins I2S pin脚
 * @param ie 输入使能
 */
void drv_ioctrl_seti2sie(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spins, ioctrl_ie_t ie)
{

    switch (i2sid)
    {
    case IOCTRL_I2S1:
    {
        switch (i2spins)
        {
        case IOCTRL_I2S_SD:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_i2siocr_i2s1_sd_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_i2siocr_i2s1_sd_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_I2S_SCLK:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_i2siocr_i2s1_sclk_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_i2siocr_i2s1_sclk_input_en;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case IOCTRL_I2S2:
    {
        switch (i2spins)
        {
        case IOCTRL_I2S_SD:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_i2siocr_i2s2_sd_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_i2siocr_i2s2_sd_input_en;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_I2S_SCLK:
        {
            switch (ie)
            {
            case IE_INPUT_DIS:
                _ioctrl_i2siocr_i2s2_sclk_input_dis;
                break;
            case IE_INPUT_EN:
                _ioctrl_i2siocr_i2s2_sclk_input_en;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;

    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块I2S1 输入功能设置函数
 *
 * @param pins I2S pin 脚
 * @param ps 上拉/下拉/浮空
 */
void drv_ioctrl_seti2sps(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spins, ioctrl_ps_t ps)
{
    switch (ps)
    {
    case PS_PULL_UP:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
        {
            switch (i2spins)
            {
            case IOCTRL_I2S_SD:
                _ioctrl_i2siocr_i2s1_sd_pull_up_down_en;
                _ioctrl_i2siocr_i2s1_sd_pull_up;
                break;
            case IOCTRL_I2S_SCLK:
                _ioctrl_i2siocr_i2s1_sclk_pull_up_down_en;
                _ioctrl_i2siocr_i2s1_sclk_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_I2S2:
        {
            switch (i2spins)
            {
            case IOCTRL_I2S_SD:
                _ioctrl_i2siocr_i2s2_sd_pull_up_down_en;
                _ioctrl_i2siocr_i2s2_sd_pull_up;
                break;
            case IOCTRL_I2S_SCLK:
                _ioctrl_i2siocr_i2s2_sclk_pull_up_down_en;
                _ioctrl_i2siocr_i2s2_sclk_pull_up;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case PS_PULL_DOWN:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
        {
            switch (i2spins)
            {
            case IOCTRL_I2S_SD:
                _ioctrl_i2siocr_i2s1_sd_pull_up_down_en;
                _ioctrl_i2siocr_i2s1_sd_pull_down;
                break;
            case IOCTRL_I2S_SCLK:
                _ioctrl_i2siocr_i2s1_sclk_pull_up_down_en;
                _ioctrl_i2siocr_i2s1_sclk_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_I2S2:
        {
            switch (i2spins)
            {
            case IOCTRL_I2S_SD:
                _ioctrl_i2siocr_i2s2_sd_pull_up_down_en;
                _ioctrl_i2siocr_i2s2_sd_pull_down;
                break;
            case IOCTRL_I2S_SCLK:
                _ioctrl_i2siocr_i2s2_sclk_pull_up_down_en;
                _ioctrl_i2siocr_i2s2_sclk_pull_down;
                break;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    break;
    case PS_PULL_NULL:
    {
        switch (i2sid)
        {
        case IOCTRL_I2S1:
        {
            switch (i2spins)
            {
            case IOCTRL_I2S_SD:
                _ioctrl_i2siocr_i2s1_sd_pull_up_down_dis;
                break;
            case IOCTRL_I2S_SCLK:
                _ioctrl_i2siocr_i2s1_sclk_pull_up_down_dis;
                break;
            default:
                break;
            }
        }
        break;
        case IOCTRL_I2S2:
        {
            switch (i2spins)
            {
            case IOCTRL_I2S_SD:
                _ioctrl_i2siocr_i2s2_sd_pull_up_down_dis;
                break;
            case IOCTRL_I2S_SCLK:
                _ioctrl_i2siocr_i2s2_sclk_pull_up_down_dis;
                break;
            default:
                break;
            }
        }
        break;

        default:
            break;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * @brief IOCTRL 模块SDHOST 上下拉设置函数
 * 
 * @param pue 模块IO输入上下拉使能枚举
 */
void drv_ioctrl_setsdhpue(ioctrl_pue_t pue)
{
    if (pue == PUE_PULL_EN)
    {
        _ioctrl_sdhcr_swap8_set;
        _ioctrl_sdhcr_data0_pull_up;

        _ioctrl_sdhcr_swap9_set;
        _ioctrl_sdhcr_data1_pull_up;

        _ioctrl_sdhcr_swap10_set;
        _ioctrl_sdhcr_data2_pull_up;

        _ioctrl_sdhcr_swap11_set;
        _ioctrl_sdhcr_data3_pull_up;
    }
    else if (pue == PUE_PULL_DIS)
    {
        _ioctrl_sdhcr_swap8_clr;
        _ioctrl_sdhcr_swap9_clr;
        _ioctrl_sdhcr_swap10_clr;
        _ioctrl_sdhcr_swap11_clr;
    }
}
