/**
 * @file i8080_drv.c
 * @author Product Application Department
 * @brief  I8080 模块驱动层
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "i8080_drv.h"

// 函数定义

/**
 * @brief I8080 模块配置FMC的时序函数
 *
 * @param initpara FMC初始化结构体
 */
void drv_fmc_timing_init(fmc_initstructure_t *initpara)
{
    initpara->instance->FMC_TIMING_0.B.TRC = initpara->trc;
    initpara->instance->FMC_TIMING_0.B.TAS = initpara->tas;
    initpara->instance->FMC_TIMING_0.B.TWP = initpara->twp;
    initpara->instance->FMC_TIMING_0.B.TBTA = initpara->tbta;
    initpara->instance->FMC_TIMING_0.B.TPRC = initpara->tprc;
}
/**
 * @brief I8080 模块复位FMC状态机函数
 *
 */
void drv_fmc_sm_reset(void)
{
    I8080_CONTROLLER->FMC_SMCTLR.B.SM_RP_N = SM_CTRL_RP_RESET_EN;
}
