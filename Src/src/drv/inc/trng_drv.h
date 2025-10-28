/**
 * @file trng_drv.h
 * @author Product application department
 * @brief  TRNG 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef _TRNG_DRV_H_
#define _TRNG_DRV_H_

// 头文件包含
#include "iomacros.h"
#include "trng_reg.h"

#ifdef __cplusplus
extern "C"
{
#endif

// 全局变量定义
#define _trng_clk_sel_osc_clk(trng) _bit_set(trng->CTRL, TRNG_CLK_SEL)
#define _trng_clk_sel_sys_clk(trng) _bit_clr(trng->CTRL, TRNG_CLK_SEL)
// trng alalogmodel reset enable
#define _trng_alalog_model_reset_en(trng) _reg_modify(trng->CTRL, TRNG_RST_ANA_MASK, (0X0F << (TRNG_RST_ANA_SHIFT_MASK)))
#define _trng_alalog_model_en(trng) _reg_modify(trng->CTRL, TRNG_EN_ANA_MASK, (0X0F << (TRNG_EN_ANA_SHIFT_MASK)))
#define _trng_alalog_model_dis(trng) _reg_modify(trng->CTRL, TRNG_EN_ANA_MASK, TRNG_EN_ANA_MASK)
#define _trng_en_sm3(trng) _bit_set(trng->CTRL, TRNG_SM3_EN)
#define _trng_dis_sm3(trng) _bit_clr(trng->CTRL, TRNG_SM3_EN)
#define _trng_get_sm3_rdy_done_flag(trng) _reg_chk(trng->CTRL, _bit(TRNG_SM3_SM3_RD_DONE))
#define _trng_get_it_flag(trng) _reg_chk(trng->CTRL, TRNG_IT_MASK)                                                            /**< 获取中断标志>   */
#define _trng_clr_it_flag(trng) _bit_set(trng->CTRL, TRNG_CLR_IT)                                                             /**< 清除中断标志>*/
#define _trng_en_it(trng) _bit_set(trng->CTRL, TRNG_EN_IT)                                                                    /**< TRNG 中断使能> */
#define _trng_dis_it(trng) _bit_clr(trng->CTRL, TRNG_EN_IT)                                                                   /**< TRNG 中断使能>*/
#define _trng_start(trng) _bit_set(trng->CTRL, TRNG_EN)                                                                       /**< TRNG 使能 >*/
#define _trng_stop(trng) _bit_clr(trng->CTRL, TRNG_EN)                                                                        /**< TRNG禁止>*/
#define _trng_set_clk_prescaler(trng, value) _reg_modify(trng->CTRL, TRNG_CLK_DIV_MASK, ((value) << TRNG_CLK_DIV_SHIFT_MASK)) /**< 设置分频数>*/

/**
 * @brief  TRNG 模块速枚举定义
 */
typedef enum
{
    TRNG_SPEED_LOW,
    TRNG_SPEED_HIGH
} trng_speed_t;

// 函数声明
void drv_trng_cmd(reg_trng_t *ptrng, functionalstate_t status);
void drv_trng_configalalogmode(reg_trng_t *ptrng, functionalstate_t status);
void drv_trng_resetalalogmode(reg_trng_t *ptrng);
void drv_trng_config_it(reg_trng_t *ptrng, functionalstate_t status);
void drv_trng_clearflag_it(reg_trng_t *ptrng);
uint32_t drv_trng_getflag_it(reg_trng_t *ptrng);
void drv_trng_setclkprescaler(reg_trng_t *ptrng, uint8_t dividor);
uint32_t drv_trng_getword(reg_trng_t *ptrng);

#ifdef __cplusplus
}
#endif

#endif
