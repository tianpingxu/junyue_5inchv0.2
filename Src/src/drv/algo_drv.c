/**
 * @file algo_drv.c
 * @author Product application department
 * @brief  ALGO 模块驱动层
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
// 头文件包含
#include "algo_drv.h"

// 函数定义

/**
 * @brief U32转U8函数
 *
 * @param src 源数据buffer
 * @param inlen 待转换长度
 * @param dest 目的数据buffer
 * @return uint32_t
 */
uint32_t u32_2_u8(uint32_t *src, uint32_t inlen, uint8_t *dest)
{
    uint16_t j;
    uint8_t *p = (uint8_t *)src;

    if (!inlen)
        return 0;

    for (j = 0x0; j < inlen; j++)
    {
        dest[j * 4] = p[(inlen - j) * 4 - 1];
        dest[j * 4 + 1] = p[(inlen - j) * 4 - 2];
        dest[j * 4 + 2] = p[(inlen - j) * 4 - 3];
        dest[j * 4 + 3] = p[(inlen - j) * 4 - 4];
    }
    return (inlen << 2);
}

/**
 * @brief U8转U32函数
 *
 * @param src 源数据buffer
 * @param inlen 待转换长度
 * @param dest 目的数据buffer
 * @return uint32_t
 */
uint32_t u8_2_u32(uint8_t *src, uint32_t inlen, uint32_t *dest)
{
    uint32_t end_index, i;
    uint32_t temp;

    if (inlen < 4)
        return 0;
    // 计算末尾位置
    end_index = inlen >> 2;
    if (inlen & 3)
    {
        end_index++;
    }

    for (i = 0x0; i < end_index; i++)
    {
        temp = ((uint32_t)src[i * 4] << 24) | ((uint32_t)src[i * 4 + 1] << 16) | ((uint32_t)src[i * 4 + 2] << 8) | (uint32_t)src[i * 4 + 3];
        dest[end_index - 1 - i] = temp;
    }
    return end_index;
}

// len为字长度，以字为单位整体翻转，字内不变

/**
 * @brief 字翻转函数
 *
 * @param dest 目的数据buffer
 * @param src  源数据buffer
 * @param wordLen 字长
 */
void swap_word(uint32_t *dest, uint32_t *src, uint32_t wordLen)
{
    uint32_t i;
    uint32_t temp;

    // 输入输出使用同一个BUF
    if (src == dest)
    {
        for (i = 0; i < wordLen / 2; i++)
        {
            temp = dest[i];
            dest[i] = src[wordLen - 1 - i];
            dest[wordLen - 1 - i] = temp;
        }
    }
    else
    {
        for (i = 0; i < wordLen; i++)
        {
            dest[i] = src[wordLen - 1 - i];
        }
    }
}
