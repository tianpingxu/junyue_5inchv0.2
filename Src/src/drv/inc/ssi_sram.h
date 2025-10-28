/**
 *  @file ssi_drv.h
 *  @author Product application department
 *  @brief  SSI flash模块驱动层头文件
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __SSI_SRAM_H
#define __SSI_SRAM_H

#ifdef __cplusplus
"C"
{
#endif

// 头文件包含
#include "cpm_drv.h"
#include "ccm_drv.h"
#include "ssi_reg.h"
#include "debug.h"
#include "status.h"
#include "ssi_drv.h"
// 全局变量定义
#define SSIID1        (1)
#define SSIID2        (2)
#define SSIID3        (3)

// 函数声明
void drv_ssi_setsamdelay(reg_ssi_t *ssi_id,uint32_t sample_delay);
void drv_ssi_eflash_write_enable(reg_ssi_t *SSIReg, uint32_t timeout);
void drv_xipflash_erase(ssi_para_t *pssi);
void drv_xipflash_program(ssi_para_t *pssi);

#ifdef __cplusplus
}
#endif

#endif
