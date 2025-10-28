/**
 * @file i8080_reg.h
 * @author Product application department
 * @brief  I8080 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I8080_REG_H
#define __I8080_REG_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define FMC_BASE (0xA8000094)
#define I8080_CONTROLLER ((reg_i8080_t *)FMC_BASE)

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t TRC : 6;                 // 0:5,
        uint32_t TAS : 4;                 // 6:9,
        uint32_t TWP : 6;                 // 10:15,
        uint32_t TBTA : 3;                // 16:18,
        uint32_t TPRC : 4;                // 19:22,
        uint32_t PAGE_MODE : 1;           // 23,
        uint32_t PAGE_SIZE : 2;           // 24:25,
        uint32_t READY_MODE : 1;          // 26,
        uint32_t LOW_FREQUNCY_DEVICE : 1; // 27,
        uint32_t SM_READ_PIPE : 2;        // 29,
    } B;
} fmc_timing_0_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t TRC : 6;                 // 0:5,
        uint32_t TAS : 4;                 // 6:9,
        uint32_t TWP : 6;                 // 10:15,
        uint32_t TBTA : 3;                // 16:18,
        uint32_t TPRC : 4;                // 19:22,
        uint32_t PAGE_MODE : 1;           // 23,
        uint32_t PAGE_SIZE : 2;           // 24:25,
        uint32_t READY_MODE : 1;          // 26,
        uint32_t LOW_FREQUNCY_DEVICE : 1; // 27,
        uint32_t SM_READ_PIPE : 2;        // 29,
    } B;
} fmc_timing_1_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t TRC : 6;                 // 0:5,
        uint32_t TAS : 4;                 // 6:9,
        uint32_t TWP : 6;                 // 10:15,
        uint32_t TBTA : 3;                // 16:18,
        uint32_t TPRC : 4;                // 19:22,
        uint32_t PAGE_MODE : 1;           // 23,
        uint32_t PAGE_SIZE : 2;           // 24:25,
        uint32_t READY_MODE : 1;          // 26,
        uint32_t LOW_FREQUNCY_DEVICE : 1; // 27,
        uint32_t SM_READ_PIPE : 2;        // 29,
    } B;
} fmc_timing_2_u;

typedef volatile union
{
    uint32_t R;

    struct
    {
        uint32_t SM_RP_N : 1;            // 0,
        uint32_t WP_N : 3;               // 1:3,
        uint32_t RESERVED0 : 3;          // 4:6,
        uint32_t SM_DATA_WIDTH_SET0 : 3; // 7:9,
        uint32_t SM_DATA_WIDTH_SET1 : 3; // 10:12,
        uint32_t SM_DATA_WIDTH_SET2 : 3; // 13:15,
        uint32_t RESERVED1 : 16;         // 16:31,
    } B;
} fmc_smctrl_u;

/**
 * @brief FMC寄存器结构体
 *
 */
typedef volatile struct
{
    fmc_timing_0_u FMC_TIMING_0;
    fmc_timing_1_u FMC_TIMING_1;
    fmc_timing_2_u FMC_TIMING_2;
    uint32_t RESERVED0;
    fmc_smctrl_u FMC_SMCTLR;
} reg_i8080_t;

#ifdef __cplusplus
}
#endif

#endif
