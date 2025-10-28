/**
 * @file trng_drv.c
 * @author Product application department
 * @brief  TRNG 模块驱动层
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "trng_drv.h"

// 函数定义

/**
 * @brief TRNG 模块设置使能或禁止函数
 * @param ptrng 随机数实例化
 * @param status 使能/失能
 */
void drv_trng_cmd(reg_trng_t *ptrng, functionalstate_t status)
{
    if (status == ENABLE)
    {
        _trng_start(ptrng);
    }

    else
    {
        _trng_stop(ptrng);
    }
}

/**
 * @brief TRNG 模块设置模拟时钟使能
 * @param ptrng 随机数实例化
 * @param status 使能/失能
 */
void drv_trng_configalalogmode(reg_trng_t *ptrng, functionalstate_t status)
{
    if (status == ENABLE)
    {
        _trng_alalog_model_en(ptrng);
    }

    else
    {
        _trng_alalog_model_dis(ptrng);
    }
}

/**
 * @brief TRNG 模块模设置拟时钟重启
 * @param ptrng 随机数实例化
 */
void drv_trng_resetalalogmode(reg_trng_t *ptrng)
{
    _trng_alalog_model_reset_en(ptrng);
}

/**
 * @brief TRNG 模块设置中断使能或禁止
 * @param ptrng 随机数实例化
 * @param status 使能/失能
 */
void drv_trng_config_it(reg_trng_t *ptrng, functionalstate_t status)
{
    if (status == ENABLE)
    {
        _trng_en_it(ptrng);
    }

    else
    {
        _trng_dis_it(ptrng);
    }
}

/**
 * @brief TRNG 模块清除中断标志位
 * @param ptrng 随机数实例化
 */
void drv_trng_clearflag_it(reg_trng_t *ptrng)
{
    _trng_clr_it_flag(ptrng);
}
/**
 * @brief TRNG 模块获取中断标志位
 *
 * @param ptrng 随机数实例化
 * @return uint32_t 返回状态值
 */
uint32_t drv_trng_getflag_it(reg_trng_t *ptrng)
{
    uint32_t status;

    status = _trng_get_it_flag(ptrng);

    return status;
}

/**
 * @brief TRNG 模块设置时钟分频数值
 *
 * @param ptrng 随机数实例化
 * @param dividor 分配系数
 */
void drv_trng_setclkprescaler(reg_trng_t *ptrng, uint8_t dividor)
{
    _trng_set_clk_prescaler(ptrng, dividor);
}

/**
 * @brief TRNG 模块随机数获取函数
 * @param ptrng 随机数实例化
 * @return
 */
uint32_t drv_trng_getword(reg_trng_t *ptrng)
{
    uint32_t random;

    while (_trng_get_it_flag(ptrng) == 0)
        ;

    random = ptrng->DR;

    _trng_clr_it_flag(ptrng);

    return random;
}
