/**
 * @file i8080_drv.h
 * @author Product Application Department
 * @brief  I8080 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I8080_DRV_H
#define __I8080_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i8080_reg.h"

// 全局变量定义
#define SM_CTRL_RP_RESET_EN 0x01

/**
 * @brief FMC 模块初始化结构体定义
 * 
 */
typedef struct
{
    reg_i8080_t *instance;
    uint8_t trc;
    uint8_t tas;
    uint8_t twp;
    uint8_t tbta;
    uint8_t tprc;
} fmc_initstructure_t;

// 函数声明
void drv_fmc_timing_init(fmc_initstructure_t *initpara);
void drv_fmc_sm_reset(void);

#ifdef __cplusplus
}
#endif

#endif
