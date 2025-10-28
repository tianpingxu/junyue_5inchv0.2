/**
 * @file trng_reg.h
 * @author Product application department
 * @brief  TRNG 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __TRNG_REG_H_
#define __TRNG_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define TRNG_BASE_ADDR (0x40032000)
#define TRNG ((reg_trng_t *)TRNG_BASE_ADDR)

#define TRNG_CLK_SEL (((uint32_t)1 << 31))
#define TRNG_ANA_VALUE_MASK ((uint32_t)0x8FFFFFFFF))
#define TRNG_ANA_VALUE_SHIFT_MASK ((uint32_t)(28))
#define TRNG_RST_ANA_MASK ((uint32_t)(0xFF0FFFFF))
#define TRNG_RST_ANA_SHIFT_MASK ((uint32_t)(20))
#define TRNG_EN_ANA_MASK ((uint32_t)(0xFFF0FFFF))
#define TRNG_EN_ANA_SHIFT_MASK (((uint32_t)16))
#define TRNG_SM3_EN (((uint32_t)1 << 15))
#define TRNG_SM3_SM3_RD_DONE (((uint32_t)1 << 14))
#define TRNG_IT_MASK (((uint32_t)1 << 11))
#define TRNG_CLR_IT (((uint32_t)1 << 10))
#define TRNG_EN_IT (((uint32_t)1 << 9))
#define TRNG_EN (((uint32_t)1 << 8))

#define TRNG_CLK_DIV_MASK ((uint32_t)0xFFFFFF00)
#define TRNG_CLK_DIV_SHIFT_MASK ((uint32_t)(0))

/**
 * @brief  TRNG 模块寄存器定义
 */
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t DR;
    __IO uint32_t TMCTRL;
    __IO uint32_t STSCR;
    __IO uint32_t OSCR_Mx[4];
    __IO uint32_t RESERVED0[10];
    __IO uint32_t SM3DRx[8];
    __IO uint32_t OSCTRIMR1;
    __IO uint32_t OSCTRIMR2;
    __IO uint32_t OSCCTR;
    __IO uint32_t OSCDIVR;
} reg_trng_t;

#ifdef __cplusplus
}
#endif

#endif
