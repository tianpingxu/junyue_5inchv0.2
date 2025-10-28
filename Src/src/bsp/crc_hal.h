/**
 * @file crc_hal.h
 * @author Product application department
 * @brief  CRC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef _CRC_HAL_H
#define _CRC_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "crc_drv.h"

// 函数声明
void hal_crc_config(reg_crc_t *CRC_CH,crc_init_t *CRC_InitStruct);
void hal_crc_setinitvalue(reg_crc_t *CRC_CH,uint32_t InitValue);
uint32_t hal_crc_calccrc32(reg_crc_t *CRC_CH,uint8_t *pBuffer, uint32_t BufferLen);
uint32_t hal_crc_calccrc16(reg_crc_t *CRC_CH,uint8_t *pBuffer, uint32_t BufferLen);
uint32_t hal_crc_calccrc8(reg_crc_t *CRC_CH,uint8_t *pBuffer, uint32_t BufferLen);

#ifdef __cplusplus
}
#endif

#endif