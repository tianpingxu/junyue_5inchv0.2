/**
 * @file i8080_hal.c
 * @author Product Application Department
 * @brief  I8080 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "i8080_hal.h"

// 函数定义
/**
 * @brief I8080 模块 FMC 初始化
 *
 * @param initpara fmc初始化结构体
 */
void hal_fmc_init(fmc_initstructure_t *initpara)
{
    drv_fmc_timing_init(initpara);
    drv_fmc_sm_reset();
}
