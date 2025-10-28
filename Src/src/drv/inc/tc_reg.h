/**
 *  @file tc_reg.h
 *  @author Product application department
 *  @brief  TC 模块寄存器配置文件
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __TC_REG_H_
#define __TC_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define TC_BASE_ADDR (0x40006000)
#define TC2_BASE_ADDR (0X4000A000)
#define TC3_BASE_ADDR (0X4000B000)
#define TC ((reg_tc_t *)(TC_BASE_ADDR))
#define TC2 ((reg_tc_t *)(TC2_BASE_ADDR))
#define TC3 ((reg_tc_t *)(TC3_BASE_ADDR))

// TCCR
#define TC_WAIT ((uint8_t)(1 << 11))
#define TC_DOZE ((uint8_t)(1 << 10))
#define TC_STOP ((uint8_t)(1 << 9))
#define TC_DEBUG ((uint8_t)(1 << 8))
#define TC_IF_MODE_MASK ((uint8_t)(1 << 3)) // TC计时器中断标志
#define TC_IE_MODE_MASK ((uint8_t)(1 << 2)) // TC计时器中断使能
#define TC_CU_MODE_MASK ((uint8_t)(1 << 1)) // TC计时器修改更新
#define TC_RN_MODE_MASK ((uint8_t)(1 << 0)) // TC计时器复位功能使能

/**
 *  @brief  TC 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint16_t CR;   // 0x00
    __IO uint16_t MR;   // 0x02
    __IO uint16_t CNTR; // 0x04
    __IO uint16_t SR;   // 0x06
} reg_tc_t;

#ifdef __cplusplus
}
#endif

#endif
