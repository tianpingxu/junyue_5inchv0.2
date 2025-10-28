/**
 * @file reset_reg.h
 * @author Product application department
 * @brief  RESET 模块寄存器配置文件
 * @version  V1.0
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#define __RESET_REG_H_
#ifdef  __RESET_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define RESET_BASE_ADDR (0x40002000)
#define RST ((reg_reset_t *)(RESET_BASE_ADDR))

#define RESET_RCR_HFDE (((uint32_t)1U << 0))
#define RESET_RCR_HFDRE (((uint32_t)1U << 1))
#define RESET_RCR_HFDIE (((uint32_t)1U << 2))
#define RESET_RCR_HFDF (((uint32_t)1U << 3))
#define RESET_RCR_LFDE (((uint32_t)1U << 8))
#define RESET_RCR_LFDRE (((uint32_t)1U << 9))
#define RESET_RCR_LFDIE (((uint32_t)1U << 10))
#define RESET_RCR_LFDF (((uint32_t)1U << 11))
#define RESET_RCR_HVDE (((uint32_t)1U << 16))
#define RESET_RCR_HVDRE (((uint32_t)1U << 17))
#define RESET_RCR_HVDIE (((uint32_t)1U << 18))
#define RESET_RCR_HVDF (((uint32_t)1U << 19))
#define RESET_RCR_CRWE (((uint32_t)1U << 22))
#define RESET_RCR_CRE (((uint32_t)1U << 23))
#define RESET_RCR_LVDE (((uint32_t)1U << 24))
#define RESET_RCR_LVDRE (((uint32_t)1U << 25))
#define RESET_RCR_LVDIE (((uint32_t)1U << 26))
#define RESET_RCR_LVDF (((uint32_t)1U << 27))
#define RESET_RCR_FRCR_STOUT (((uint32_t)1U << 30))
#define RESET_RCR_SOFTRST (((uint32_t)1U << 31))

/**
 * @brief  RESET 模块寄存器定义
 */
typedef struct
{
    __IO uint32_t RCR;  // 0x00
    __IO uint8_t LVDCR; // 0x04
    __IO uint8_t HVDCR; // 0x05
    __IO uint8_t RTR;   // 0x06
    __IO uint8_t RSR;   // 0x07
} reg_reset_t;

#ifdef __cplusplus
}
#endif

#endif
