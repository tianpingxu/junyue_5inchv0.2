/**
 * @file i2s_reg.h
 * @author Product Application Department
 * @brief  I2S 模块驱动层头文件
 * @version V1.0
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I2S_DRV_H
#define __I2S_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i2s_reg.h"
#include "status.h"
    
// 全局变量定义

/**
 * @brief I2S 模块工作模式枚举定义
 * 
 */
typedef enum
{
    I2S_MODE_PLAY,
    I2S_MODE_RECORD,
} i2s_mode_t;

/**
 * @brief I2S 模块初始化结构体定义
 * 
 */
typedef struct
{
    uint8_t Mode;          /**<I2S工作于播放还是录音
                                *- I2C_MODE_PLAY
                                *- I2C_MODE_RECORD
                                */
    uint8_t MclkPrescaler; /**<I2S MCLK时钟分频系数*/
    uint8_t SclkPrescaler; /**<I2S SCLK时钟分频系数*/
    uint8_t LrcPrescaler;  /**<I2S LRC时钟分频系数*/
} i2s_init_t;

// 函数声明
void drv_i2s_txen(reg_i2s_t *pi2s);
void drv_i2s_txdis(reg_i2s_t *pi2s);
void drv_i2s_rxen(reg_i2s_t *pi2s);
void drv_i2s_rxdis(reg_i2s_t *pi2s);
void drv_i2s_dmatxen(reg_i2s_t *pi2s);
void drv_i2s_dmatxdis(reg_i2s_t *pi2s);
void drv_i2s_dmarxen(reg_i2s_t *pi2s);
void drv_i2s_dmarxcnt(reg_i2s_t *pi2s, uint8_t cnt);
status_t drv_i2s_init(reg_i2s_t *pi2s, i2s_init_t *pinit);
status_t drv_i2s_transmit(reg_i2s_t *pi2s, uint8_t *pBuf, uint32_t Size, uint32_t timeout);
status_t drv_i2s_receive(reg_i2s_t *pi2s, uint8_t *pBuf, uint32_t Size, uint32_t timeout);
status_t drv_i2s_dma_transmit(reg_i2s_t *pi2s, uint8_t *pBuf, uint32_t Size, uint32_t timeout);
status_t drv_i2s_dma_receive(reg_i2s_t *pi2s, uint8_t *pBuf, uint32_t Size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif
