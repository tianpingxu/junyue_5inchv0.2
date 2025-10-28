/**
 * @file reset_hal.c
 * @author Product application department
 * @brief  RESET 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

 // 头文件包含
#include "reset_hal.h"

// 函数定义

/**
 * @brief RESET 模块复位函数
 *
 */
void hal_reset_softreset(void)
{
    drv_reset_softreset();
}

/**
 * @brief RESET 模块获取复位状态函数
 *
 * @param reset 复位状态
 */
void hal_reset_getstatus(reset_status_t *reset)
{
    *reset = (reset_status_t)drv_reset_getstatus();
}

/**
 * @brief RESET 模块复位失能函数
 *
 * @param source 复位源
 */
void hal_reset_disable(reset_source_t source)
{

    if (HAL_RESET_SRC_HFD == source)
    {
        drv_hfd_reset_disable();
    }

    if (HAL_RESET_SRC_LFD == source)
    {
        drv_lfd_reset_disable();
    }

    if (HAL_RESET_SRC_HVD == source)
    {
        drv_hvd_reset_disable();
    }

    if (HAL_RESET_SRC_LVD == source)
    {
        drv_lvd_reset_disable();
    }
}

/**
 * @brief RESET 模块复位使能函数
 *
 * @param source 复位源
 */
void hal_reset_enable(reset_source_t source)
{

    if (HAL_RESET_SRC_HFD == source)
    {
        drv_hfd_reset_enable();
    }

    if (HAL_RESET_SRC_LFD == source)
    {
        drv_lfd_reset_enable();
    }

    if (HAL_RESET_SRC_HVD == source)
    {
        drv_hvd_reset_enable();
    }

    if (HAL_RESET_SRC_LVD == source)
    {
        drv_lvd_reset_enable();
    }
}

/**
 * @brief RESET 模块LVD阈值设置函数
 *
 * @param power
 * @param threshold
 */
void hal_set_lvdthreshold(uint8_t power, uint8_t threshold)
{
    if ((power > POWER_5P0_V) | (threshold > 3))
    {
        return;
    }

    drv_set_lvdthreahold(power, threshold);
}

/**
 * @brief RESET 模块HVD阈值设置函数
 *
 * @param power
 * @param threshold
 */
void hal_set_hvdthreshold(uint8_t power, uint8_t threshold)
{
    if ((power > POWER_5P0_V) | (threshold > 3))
    {
        return;
    }

    drv_set_hvdthreahold(power, threshold);
}
