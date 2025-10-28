/**
 * @file algo_drv.h
 * @author Product application department
 * @brief  ALGO 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __ALGO_DRV_H
#define __ALGO_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"

// 全局变量定义

/**
 * @brief  ALGO 模块加解密枚举定义
 * 
 */
typedef enum
{
    ALG_ENCRYPT = 0,
    ALG_DECRYPT = 1
} ALG_EN_DE_MODE;

/**
 * @brief ALGO 模块对称算法加解密模式枚举定义
 * 
 */
typedef enum
{
    ALG_ECB,
    ALG_CBC,
    ALG_CTR,
    ALG_CFB,
    ALG_OFB,
} ALG_MODE;

/**
 * @brief  ALGO 模块AES算法密钥长度枚举定义
 * 
 */
typedef enum
{
    AES_KEY128 = 0,
    AES_KEY192,
    AES_KEY256,
} AES_KEY_BITS;

/**
 * @brief ALOGO 模块算法密钥模式枚举定义
 * 
 */
typedef enum
{
    ALG_KEY64,
    ALG_KEY128,
    ALG_KEY192,
    ALG_KEY256,
    ALG_KEY384,
    ALG_KEY512
} ALG_KEY_MODE;

/**
 * @brief ALGO 模块COF bit枚举定义
 * 
 */
typedef enum
{
    ALG_COFBIT_DUMMY = 0,
    ALG_COFBIT01,
    ALG_COFBIT08,
    ALG_COFBIT16,
    ALG_COFBIT32,
    ALG_COFBIT64,
    ALG_COFBIT128,
} ALG_COFBITS;

/**
 * @brief ALGO 模块AES算法密钥长度枚举定义
 * 
 */
typedef enum
{
    ALG_DUMMY,
    ALG_CO1,
    ALG_CO8,
    ALG_CO16,
    ALG_CO32,
    ALG_CO64,
    ALG_CO128
} ALG_STREAMMODE;

/**
 * @brief ALGO 模块防护等级枚举定义
 * 
 */
typedef enum
{
    dpa_middle,  // 中等防护等级
    dpa_high,    // 最高防护等级
    dpa_low,     // 最低防护等级
    dpa_disable, // 没有防护
    dpa_others,
} dpa_level_t;

// 函数声明
uint32_t u32_2_u8(uint32_t *src, uint32_t inlen, uint8_t *dest);
uint32_t u8_2_u32(uint8_t *src, uint32_t inlen, uint32_t *dest);
void swap_word(uint32_t *dest, uint32_t *src, uint32_t wordLen);

#ifdef __cplusplus
}
#endif

#endif
