/**
 * @file algo_hal.c
 * @author Product application department
 * @brief  ALGO 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#include "algo_hal.h"
#include "trng_hal.h"
#include "debug.h"
//函数定义

/**
 * @brief SM4密码运算.
 *
 * @param[in] hcfg：SM4密码运算参数配置.
 * @param[in] pKey：SM4运算密钥.
 * @param[in] pIV：SM4运算初始向量.
 * @param[in] srcBuffer：源数据指针.
 * @param[in] length：源数据长度.
 * @param[out]destBuffer：消息数据指针.
 *
 * @retval 0:成功   1:失败
 */
uint8_t hal_sm4_cryptographic(sm4_config_t *hcfg, uint8_t *pKey, uint8_t *pIV, uint8_t *srcBuffer, uint8_t *destBuffer, uint32_t length)
{
    uint32_t key[4], iv[4];

    if (!IS_ALL_MODE_INSTANCE(hcfg->mode))
    {
        return 1;
    }

    if (!IS_ALL_SM4_INSTANCE(hcfg->type))
    {
        return 1;
    }

    if ((hcfg->type == ALG_CFB) ||
        (hcfg->type == ALG_OFB))
    {
        if ((hcfg->cofbits != ALG_COFBIT01) &&
            (hcfg->cofbits != ALG_COFBIT128))
        {
            return 1;
        }
    }
    else
    {
        if (hcfg->cofbits != ALG_COFBIT_DUMMY)
        {
            return 1;
        }
    }

    if ((length & 0x0F) || (length == 0)) // 不是16的整数倍
    {
        return 1;
    }

    if ((pKey == NULL) || (srcBuffer == NULL) || (destBuffer == NULL))
    {
        return 1;
    }
    _memcpy((uint8_t *)key, pKey, 16);

    if (hcfg->type == ALG_CBC)
    {
        if (pIV == NULL)
        {
            return 1;
        }

        _memcpy((uint8_t *)iv, pIV, 16);
    }
    // SMS4_Enable();
    LIB_SMS4_Enable();

    LIB_SM4_Cryptographic(hcfg->mode, hcfg->type, (ALG_STREAMMODE)hcfg->cofbits, (uint32_t *)srcBuffer, (uint32_t *)destBuffer, length, key, iv, hcfg->level);

    LIB_SMS4_Disable();
    dcache_invalidate_range(destBuffer,length);
    return 0;
}

/**
 * @brief AES密码运算.
 *
 * @param[in] hcfg：AES密码运算参数配置.
 * @param[in] pKey：AES运算密钥.
 * @param[in] pIV：AES运算初始向量.
 * @param[in] srcBuffer：源数据指针.
 * @param[in] length：源数据长度.
 * @param[out]destBuffer：消息数据指针.
 * @retval 0:成功   1:失败.
 */
uint8_t hal_aes_cryptographic(aes_config_t *hcfg, uint8_t *pKey, uint8_t *pIV, uint8_t *srcBuffer, uint8_t *destBuffer, uint32_t length)
{
    uint32_t key[8];
    uint32_t iv[4]; // CBC模式临时缓冲区

    if (!IS_ALL_LEVEL_INSTANCE(hcfg->level))
    {
        return 1;
    }

    if (!IS_ALL_MODE_INSTANCE(hcfg->mode))
    {
        return 1;
    }

    if (!IS_ALL_AES_INSTANCE(hcfg->type))
    {
        return 1;
    }

    if (!IS_ALL_AESKBITS_INSTANCE(hcfg->KBits))
    {
        return 1;
    }

    if ((hcfg->type == ALG_CFB) ||
        (hcfg->type == ALG_OFB))
    {
        if ((hcfg->cofbits != ALG_COFBIT01) &&
            (hcfg->cofbits != ALG_COFBIT128))
        {
            return 1;
        }
    }
    else
    {
        if (hcfg->cofbits != ALG_COFBIT_DUMMY)
        {
            return 1;
        }
    }

    if ((length & 7) || (length == 0)) // 不是8的整数倍
    {
        return 1;
    }

    if ((pKey == NULL) ||
        (srcBuffer == NULL) ||
        (destBuffer == NULL))
    {
        return 1;
    }

    _memcpy((uint8_t *)key, pKey, hcfg->KBits == ALG_KEY128 ? 16 : (hcfg->KBits == ALG_KEY192 ? 24 : 32));

    if (hcfg->type == ALG_CBC)
    {
        if (pIV == NULL)
        {
            return 1;
        }

        _memcpy((uint8_t *)iv, pIV, 16);
    }

    LIB_AES_Enable();
    LIB_AES_Cryptographic(hcfg->mode, (ALG_KEY_MODE)hcfg->KBits, (ALG_MODE)hcfg->type, (ALG_STREAMMODE)hcfg->cofbits, (uint32_t *)srcBuffer, (uint32_t *)destBuffer, length, (uint32_t *)pKey, (uint32_t *)pIV, hcfg->level);
    LIB_AES_Disable();
    dcache_invalidate_range(destBuffer,length);
    return 0;
}

