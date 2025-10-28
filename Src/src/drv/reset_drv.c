/**
 * @file reset_drv.c
 * @author Product application department
 * @brief  RESET 模块驱动层
 * @version V1.0
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */
// 头文件包含
#include "reset_drv.h"

// 函数定义

/**
 * @brief RESET 模块芯片软复位实现函数.
 * @param[in] NONE
 * @retval NONE
 */
void drv_reset_softreset(void)
{
    _reset_softreset;
}

/**
 * @brief RESET 模块低压检测复位使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_lvd_reset_enable(void)
{
    _reset_en_lvd_control;
    _reset_en_lvd_rst;
}

/**
 * @brief RESET 模块关闭低压检测复位函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_lvd_reset_disable(void)
{
    _reset_en_lvd_control;
    _reset_dis_lvd_rst;
}

/**
 * @brief RESET 模块高电压检测复位使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_hvd_reset_enable(void)
{
    _reset_en_hvd_rst_control;
    _reset_en_hvd_rst;
}

/**
 * @brief RESET 模块关闭高电压检测复位功能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_hvd_reset_disable(void)
{
    _reset_en_hvd_rst_control;
    _reset_dis_hvd_rst;
}

/**
 * @brief RESET 模块获取低频检测指示状态函数.
 * @param[in] NONE
 * @retval NONE
 */
bool drv_lfd_gerstatus(void)
{
    if (_reset_get_lfd_status != 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief RESET 模块低频检测中断使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_lfd_interrupt_enable(void)
{
    _reset_en_lfd_int;
}

/**
 * @brief RESET 模块关闭低频检测中断使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_lfd_interrupt_disable(void)
{
    _reset_dis_lfd_int;
}

/**
 * @brief RESET 模块低频检测复位使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_lfd_reset_enable(void)
{
    _reset_en_lfd_control;
    _reset_en_lfd_rst;
}

/**
 * @brief RESET 模块关闭低频检测复位功能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_lfd_reset_disable(void)
{
    _reset_en_lfd_control;
    _reset_dis_lfd_rst;
}

/**
 * @brief RESET 模块获取高频检测指示状态函数
 * @param[in] NONE
 * @retval NONE
 */
bool drv_hfd_getstatus(void)
{
    if (_reset_get_hfd_status != 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @brief RESET 模块高频检测中断使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_hfd_interrupt_enable(void)
{
    _reset_en_hfd_int;
}

/**
 * @brief RESET 模块关闭高频检测中断使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_hfd_interrupt_disable(void)
{
    _reset_dis_hfd_int;
}

/**
 * @brief RESET 模块高频检测复位使能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_hfd_reset_enable(void)
{
    _reset_en_hfd_control;
    _reset_en_hfd_rst;
}

/**
 * @brief RESET 模块关闭高频检测复位功能函数
 * @param[in] NONE
 * @retval NONE
 */
void drv_hfd_reset_disable(void)
{
    _reset_en_hfd_control;
    _reset_dis_hfd_rst;
}

/**
 * @brief RESET 模块设置低压阈值函数
 * @param[in] 芯片供电电压
 * @param[in] 低压检测阈值
 * @retval NONE
 */
void drv_set_lvdthreahold(uint8_t power, uint8_t threshold)
{
    RST->LVDCR = 0;
    if (POWER_1P8_V == power)
    {
        RST->LVDCR |= (threshold << 4);
    }
    else if (POWER_3P3_V == power)
    {
        RST->LVDCR |= (threshold << 2);
    }
    else // POWER_5P0_V
    {
        RST->LVDCR |= (threshold << 0);
    }
}

/**
 * @brief RESET 模块设置高压阈值函数
 * @param[in] 芯片供电电压
 * @param[in] 低压检测阈值
 * @retval NONE
 */
void drv_set_hvdthreahold(uint8_t power, uint8_t threshold)
{
    RST->HVDCR = 0;
    if (POWER_1P8_V == power)
    {
        RST->HVDCR |= (threshold << 4);
    }
    else if (POWER_3P3_V == power)
    {
        RST->HVDCR |= (threshold << 2);
    }
    else // POWER_5P0_V
    {
        RST->HVDCR |= (threshold << 0);
    }
}

/**
 * @brief RESET 模块获取系统的复位状态函数
 * @param[in] NONE
 * @retval uint8_t
 * - 1  SimCard导致复位.
 * - 2  频率检测导致复位.
 * - 3  POR上电复位.
 * - 4  看门狗导致复位.
 * - 5  软件复位.
 * - 6  电压检测导致复位.
 * - 7  TC定时器导致复位.
 */
uint8_t drv_reset_getstatus(void)
{
    uint8_t temp;
    uint8_t i;

    temp = _reset_get_status;

    for (i = 0; i < 8; i++)
        if (0 != (temp & (1 << i)))
            return (i);

    return (0);
}
