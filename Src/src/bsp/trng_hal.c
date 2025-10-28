/**
 * @file trng_hal.c
 * @author Product application department
 * @brief  TRNG 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */
// 头文件包含
#include "trng_hal.h"

// 函数定义

/**
 * @brief TRNG 模块初始化
 *
 * @param htrng 随机数实例
 */
void hal_trng_init(trng_handle_t *htrng)
{
    drv_trng_cmd(htrng->instance, DISABLE);

    drv_trng_setclkprescaler(htrng->instance, htrng->dividor);

    drv_trng_resetalalogmode(htrng->instance);

    drv_trng_configalalogmode(htrng->instance, ENABLE);

    drv_trng_clearflag_it(htrng->instance);

    drv_trng_cmd(htrng->instance, ENABLE);
}

/**
 * @brief TRNG 模块去初始化函数.
 *
 * @param htrng 随机数实例
 */
void hal_trng_deinit(trng_handle_t *htrng)
{

    drv_trng_configalalogmode(htrng->instance, DISABLE);

    drv_trng_cmd(htrng->instance, DISABLE);
}

/**
 * @brief TRNG 模块获取随机数值
 *
 * @param htrng
 * @return uint32_t 随机数之
 */
uint32_t hal_trng_getrandom(trng_handle_t *htrng)
{
    return drv_trng_getword(htrng->instance);
}
