/**
 * @file crc_drv.c
 * @author Product application department
 * @brief  CRC 模块驱动层
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "crc_drv.h"

// 函数定义

/**
 * @brief CRC 模块配置函数
 * @param CRC_InitStruct CRC 模块结构体指针
 */
void drv_crc_config(reg_crc_t *CRC_CHANNEL, crc_init_t *CRC_InitStruct)
{
    if (CRC_InitStruct->CRC_Mode == CRC_MODE_CRC_32)
    {
        CRC_CHANNEL->CR = ((CRC_InitStruct->CRC_Mode << 29) | (CRC_InitStruct->CRC_DataFormat << 26) | (CRC_InitStruct->CRC_SourceSel << 27));
    }
    else
    {
        CRC_CHANNEL->CR = ((CRC_InitStruct->CRC_Mode << 29) | (CRC_InitStruct->CRC_SourceSel << 27));
    }
}

/**
 * @brief CRC 模块初始值设置函数
 * @param InitValue 设置CRC初始值
 */
void drv_crc_setinitvalue(reg_crc_t *CRC_CHANNEL, uint32_t InitValue)
{
    CRC_CHANNEL->INIT_DATA = InitValue;
    CRC_CHANNEL->CR |= CRC_MODE_UPDATA;
}

/**
 * @brief CRC 模块32计算函数
 *
 * @param pBuffer 需要计算CRC的数据缓冲
 * @param BufferLen 需要就按的CRC数据缓冲长度
 * @return uint32_t
 */
uint32_t drv_crc_calccrc32(reg_crc_t *CRC_CHANNEL, uint8_t *pBuffer, uint32_t BufferLen)
{
    uint32_t i;
    uint32_t aSize = BufferLen;
    uint8_t *point = pBuffer;

    if (aSize % 4 == 0)
    {
        for (i = 0; i < aSize; i = i + 4)
        {
            CRC_CHANNEL->DATA_IN = (*(point + i) << 24) | (*(point + i + 1) << 16) | (*(point + i + 2) << 8) | (*(point + i + 3)); // ������ݵ��ڴ���֯��ʽ������λ�����ڵ͵�ַ
        }
    }
    else if (aSize % 4 == 1)
    {
        for (i = 0; i < aSize - 1; i = i + 4)
        {
            CRC_CHANNEL->DATA_IN = (*(point + i) << 24) | (*(point + i + 1) << 16) | (*(point + i + 2) << 8) | (*(point + i + 3));
        }
        CRC_CHANNEL->DATA_IN = (*(point + i) << 24);
    }
    else if (aSize % 4 == 2)
    {
        for (i = 0; i < aSize - 2; i = i + 4)
        {
            CRC_CHANNEL->DATA_IN = (*(point + i) << 24) | (*(point + i + 1) << 16) | (*(point + i + 2) << 8) | (*(point + i + 3));
        }
        CRC_CHANNEL->DATA_IN = (*(point + i) << 24) | (*(point + i + 1) << 16);
    }
    else
    {
        for (i = 0; i < aSize - 3; i = i + 4)
        {
            CRC_CHANNEL->DATA_IN = (*(point + i) << 24) | (*(point + i + 1) << 16) | (*(point + i + 2) << 8) | (*(point + i + 3));
        }
        CRC_CHANNEL->DATA_IN = (*(point + i) << 24) | (*(point + i + 1) << 16) | (*(point + i + 2) << 8);
    }

    return (CRC_CHANNEL->RES);
}

/**
 * @brief CRC 模块16计算函数
 *
 * @param pBuffer 需要计算CRC的数据缓冲
 * @param BufferLen 需要就按的CRC数据缓冲长度
 * @return uint16_t
 */
uint16_t drv_crc_calccrc16(reg_crc_t *CRC_CHANNEL, uint8_t *pBuffer, uint32_t BufferLen)
{
    uint32_t i;

    if (BufferLen % 2 == 0)
    {
        for (i = 0; i < BufferLen; i = i + 2)
        {
            CRC_CHANNEL->DATA_IN = (*(pBuffer + i) << 8) | (*(pBuffer + i + 1));
        }
    }
    else
    {
        for (i = 0; i < BufferLen - 1; i = i + 2)
        {
            CRC_CHANNEL->DATA_IN = (*(pBuffer + i) << 24) | (*(pBuffer + i + 1) << 16);
        }
        CRC_CHANNEL->DATA_IN = (*(pBuffer + i) << 24);
    }
    return ((uint16_t)(CRC_CHANNEL->RES));
}

/**
 * @brief CRC 模块8计算函数
 *
 * @param pBuffer 需要计算CRC的数据缓冲
 * @param BufferLen 需要就按的CRC数据缓冲长度
 * @return uint8_t
 */
uint8_t drv_crc_calccrc8(reg_crc_t *CRC_CHANNEL, uint8_t *pBuffer, uint32_t BufferLen)
{
    uint32_t i;

    for (i = 0; i < BufferLen; i++)
    {
        CRC_CHANNEL->DATA_IN = *(pBuffer + i);
    }
    return ((uint8_t)(CRC_CHANNEL->RES));
}
