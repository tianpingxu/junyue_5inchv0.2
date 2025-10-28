/**
 * @file algo_hal.h
 * @author Product application department
 * @brief  ALGO 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __ALGO_HAL_H
#define __ALGO_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "algo_drv.h"
#include "AES_Algorithm.h"
#include "SM4_Algorithm.h"

// 全局变量定义
#define IS_ALL_LEVEL_INSTANCE(INSTANCE) (((INSTANCE) == dpa_disable) || \
                                         ((INSTANCE) == dpa_low) ||     \
                                         ((INSTANCE) == dpa_middle) ||  \
                                         ((INSTANCE) == dpa_high))

#define IS_SM2_LEVEL_INSTANCE(INSTANCE) (((INSTANCE) == dpa_disable) || \
                                         ((INSTANCE) == dpa_high))

#define IS_ALL_MODE_INSTANCE(INSTANCE) (((INSTANCE) == ALG_ENCRYPT) || \
                                        ((INSTANCE) == ALG_DECRYPT))


#define IS_ALL_SM4_INSTANCE(INSTANCE) (((INSTANCE) == ALG_ECB) || \
                                       ((INSTANCE) == ALG_CBC))


#define IS_ALL_AES_INSTANCE(INSTANCE) IS_ALL_SM4_INSTANCE(INSTANCE)


#define IS_ALL_AESKBITS_INSTANCE(INSTANCE) (((INSTANCE) == ALG_KEY128) || \
                                            ((INSTANCE) == ALG_KEY192) || \
                                            ((INSTANCE) == ALG_KEY256))


#define IS_ALL_HASHMODE_INSTANCE(INSTANCE) (((INSTANCE) == MODE_SM3) ||    \
                                            ((INSTANCE) == MODE_SHA0) ||   \
                                            ((INSTANCE) == MODE_SHA1) ||   \
                                            ((INSTANCE) == MODE_SHA224) || \
                                            ((INSTANCE) == MODE_SHA256) || \
                                            ((INSTANCE) == MODE_SHA384) || \
                                            ((INSTANCE) == MODE_SHA512))


#define IS_ALL_RSAMODE_INSTANCE(INSTANCE) (((INSTANCE) == 0) || \
                                           ((INSTANCE) == 1))

    
/**
 * @brief SM4算法配置参数结构体定义
 * 
 */
typedef struct
{
    uint8_t mode; /**<加解密模式选择 */
    ALG_MODE type; /**<算法类型选择 */
    ALG_COFBITS cofbits; /**<CFB OFB bits*/
    dpa_level_t level; /**<算法防护等级 */
} sm4_config_t;

/**
 * @brief AES算法配置参数结构体定义
 * 
 */
typedef struct
{
    uint8_t mode;       /**<加解密模式选择 */
    ALG_KEY_MODE KBits; /**<支持的密钥长度*/
    ALG_MODE type;      /**<算法类型选择 */
    uint8_t cofbits;    /**<CFB OFB bits*/
    uint32_t *cnt;
    uint32_t level; /**<算法防护等级 */
} aes_config_t;

 // 函数声明
uint8_t hal_sm4_cryptographic(sm4_config_t *hcfg, uint8_t *pKey, uint8_t *pIV, uint8_t *srcBuffer, uint8_t *destBuffer, uint32_t length);
uint8_t hal_aes_cryptographic(aes_config_t *hcfg, uint8_t *pKey, uint8_t *pIV, uint8_t *srcBuffer, uint8_t *destBuffer, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif
