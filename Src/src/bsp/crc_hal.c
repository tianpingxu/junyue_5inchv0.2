/**
 * @file crc_hal.c
 * @author Product application department
 * @brief  CRC 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "crc_hal.h"

// 函数定义
/** 
 * @brief CRC 模块配置函数
 * @param CRC_InitStruct CRC 模块结构体指针
 */
void hal_crc_config(reg_crc_t *CRC_CH,crc_init_t *CRC_InitStruct)
{
    drv_crc_config(CRC_CH,CRC_InitStruct);
}

/**
 * @brief CRC 模块初始值设置函数
 * @param InitValue 设置CRC初始值
 */
void hal_crc_setinitvalue(reg_crc_t *CRC_CH,uint32_t InitValue)
{
    drv_crc_setinitvalue(CRC_CH, InitValue);
}

/**
 * @brief CRC 模块32计算函数
 * 
 * @param pBuffer 需要计算CRC的数据缓冲
 * @param BufferLen 需要就按的CRC数据缓冲长度
 * @return uint32_t 
 */
uint32_t hal_crc_calccrc32(reg_crc_t *CRC_CH,uint8_t *pBuffer, uint32_t BufferLen)
{
   return drv_crc_calccrc32( CRC_CH,pBuffer,BufferLen);
}

/**
 * @brief CRC 模块16计算函数
 * 
 * @param pBuffer 需要计算CRC的数据缓冲
 * @param BufferLen 需要就按的CRC数据缓冲长度
 * @return uint32_t 
 */
uint32_t hal_crc_calccrc16(reg_crc_t *CRC_CH,uint8_t *pBuffer, uint32_t BufferLen)
{
   return drv_crc_calccrc16( CRC_CH,pBuffer,BufferLen);
}


/**
 * @brief CRC 模块8计算函数
 * 
 * @param pBuffer 需要计算CRC的数据缓冲
 * @param BufferLen 需要就按的CRC数据缓冲长度
 * @return uint32_t 
 */
uint32_t hal_crc_calccrc8(reg_crc_t *CRC_CH,uint8_t *pBuffer, uint32_t BufferLen)
{
   return drv_crc_calccrc8( CRC_CH,pBuffer,BufferLen);
}