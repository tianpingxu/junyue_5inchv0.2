/**
 * @file   crc_drv.h
 * @author Product application department
 * @brief  CRC 模块驱动层头文件
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef CRC_DRV_H_
#define CRC_DRV_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "crc_reg.h"

// 全局变量定义
#define CRC_DATA_FORMAT_BIGENDDING (0x01)    // Data format is big endding
#define CRC_DATA_FORMAT_LITTLEENDDING (0x00) // Data format is little endding

#define IS_CRC_DATA_FORMAT(DATA_FORMAT) (((DATA_FORMAT) == CRC_DATA_FORMAT_BIGENDDING) || \
                                         ((DATA_FORMAT) == CRC_DATA_FORMAT_LITTLEENDDING))

#define CRC_SOURCE_SEL_FROM_DMAC (0x01) // Data from DMAC write
#define CRC_SOURCE_SEL_FROM_CPU (0x00)  // Data from CPU transport

#define IS_CRC_SOURCE_SEL(SOURCE_SEL) (((SOURCE_SEL) == CRC_SOURCE_SEL_FROM_DMAC) || \
                                       ((SOURCE_SEL) == CRC_SOURCE_SEL_FROM_CPU))

#define IS_CRC_MODE(MODE) (((MODE) == CRC_MODE_CRC_32) || \
                           ((MODE) == CRC_MODE_CRC_16) || \
                           ((MODE) == CRC_MODE_CRC_8))

/**
 * @brief CRC 模块初始化结构体定义
 * 
 */
typedef struct
{
    uint8_t CRC_Mode;       // CRC data mode
    uint8_t CRC_SourceSel;  // Data from sram transport or CPU write
    uint8_t CRC_DataFormat; // Data format when in CRC32 mode
} crc_init_t;

// 函数声明
void drv_crc_config(reg_crc_t *CRC_CHANNEL, crc_init_t *CRC_InitStruct);
void drv_crc_setinitvalue(reg_crc_t *CRC_CHANNEL, uint32_t InitValue);
uint32_t drv_crc_calccrc32(reg_crc_t *CRC_CHANNEL, uint8_t *pBuffer, uint32_t BufferLen);
uint16_t drv_crc_calccrc16(reg_crc_t *CRC_CHANNEL, uint8_t *pBuffer, uint32_t BufferLen);
uint8_t drv_crc_calccrc8(reg_crc_t *CRC_CHANNEL, uint8_t *pBuffer, uint32_t BufferLen);

#ifdef __cplusplus
}
#endif

#endif
