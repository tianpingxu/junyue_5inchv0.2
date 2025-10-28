/**
 * @file i2c_hal.h
 * @author Product Application Department
 * @brief I2C 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-12
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef _I2C_HAL_H
#define _I2C_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i2c_drv.h"
#include "debug.h"
#include "interrupt.h"
#include "pinswap_drv.h"
#include "eport_drv.h"
#include "status.h"
    
// 全局变量定义
#define HAL_I2C_ERROR_NONE (0x00000000U)
#define HAL_I2C_ERROR_BERR (0x00000001U)
#define HAL_I2C_ERROR_ARLO (0x00000002U)
#define HAL_I2C_ERROR_AF (0x00000004U)
#define HAL_I2C_ERROR_OVR (0x00000008U)
#define HAL_I2C_ERROR_DMA (0x00000010U)
#define HAL_I2C_ERROR_TIMEOUT (0x00000020U)
#define HAL_I2C_ERROR_SIZE (0x00000040U)

/**
 * @brief I2C 模块通信状态枚举定义
 * 
 */
typedef enum
{
    HAL_I2C_STATE_RESET = 0x00,
    HAL_I2C_STATE_READY = 0x20,
    HAL_I2C_STATE_BUSY = 0x24,
    HAL_I2C_STATE_BUSY_TX = 0x21,
    HAL_I2C_STATE_BUSY_RX = 0x22,
    HAL_I2C_STATE_BUSY_DEVADD_READ = 0X23,
    HAL_I2C_STATE_LISTEN = 0x28,
    HAL_I2C_STATE_BUSY_TX_LISTEN = 0x29,
    HAL_I2C_STATE_BUSY_RX_LISTEN = 0x2A,
    HAL_I2C_STATE_ABORT = 0x60,
    HAL_I2C_STATE_TIMEOUT = 0xA0,
    HAL_I2C_STATE_ERROR = 0xE0,
    HAL_I2C_STATE_BUSY_MEM_SUBADD = 0XF0,
    HAL_I2C_STATE_BUSY_MEM_TX = 0XF1,
    HAL_I2C_STATE_BUSY_MEM_RX = 0XF2,
    HAL_I2C_STATE_BUSY_MEM_DEVADD_RESTART_READ = 0XF3,
    HAL_I2C_STATE_BUSY_MEM_STOP = 0XF4,
} i2c_state_t;

/**
 * @brief I2C 模块初始化结构体定义
 * 
 */
typedef struct __I2C_HandleTypeDef
{
    reg_i2c_t *Instance;
    i2c_init_t Init;
    uint32_t SubAdd;
    uint32_t MemAdd;
    uint32_t MemAddSize;
    uint8_t XferFlag;
    uint8_t *pXferBuf;
    uint8_t *pTxBuf;
    uint16_t XferSize;
    uint16_t XferCnt;
    __IO uint32_t PreviousState;
    __IO i2c_state_t State;
    __IO i2c_mode_t Mode;
    __IO uint32_t ErrorCode;
    void (*XferISR)(struct __I2C_HandleTypeDef *hi2c, uint8_t BasicITFlags, uint8_t SlvHighspeedFlags, uint8_t ITSources);
} i2c_handle_t;

// 函数声明
status_t hal_i2c_init(i2c_handle_t *hi2c);
status_t hal_i2c_memwrite(i2c_handle_t *hi2c,
                              uint16_t DevAddress,
                              uint32_t MemAddress,
                              uint16_t MemAddSize,
                              uint8_t *pData,
                              uint16_t Size,
                              uint32_t Timeout);

status_t hal_i2c_memread(i2c_handle_t *hi2c,
                             uint16_t DevAddress,
                             uint32_t MemAddress,
                             uint16_t MemAddSize,
                             uint8_t *pData,
                             uint16_t Size,
                             uint32_t Timeout);

void hal_i2c_irqhandler(void);

status_t hal_i2c_mastertransmit(i2c_handle_t *hi2c,
                                        uint16_t DevAddress,
                                        uint8_t *pData,
                                        uint16_t Size,
                                        uint32_t Timeout);

status_t hal_i2c_masterreceive(i2c_handle_t *hi2c,
                                       uint16_t DevAddress,
                                       uint8_t *pData,
                                       uint16_t Size,
                                       uint32_t Timeout);

status_t hal_i2c_slavetransmit(i2c_handle_t *hi2c,
                                       uint8_t *pData,
                                       uint16_t Size,
                                       uint32_t Timeout);

status_t hal_i2c_slavereceive(i2c_handle_t *hi2c,
                                      uint8_t *pData,
                                      uint16_t Size,
                                      uint32_t Timeout);

status_t hal_i2c_slavereceiveit(i2c_handle_t *hi2c,
                                        uint8_t *pData,
                                        uint16_t Size,
                                        uint32_t Timeout);
status_t hal_i2c_slavetransmitit(i2c_handle_t *hi2c,
                                         uint8_t *pData,
                                         uint16_t Size,
                                         uint32_t Timeout);

status_t hal_i2c_mastertransmitit(i2c_handle_t *hi2c,
                                          uint16_t DevAddress,
                                          uint8_t *pData,
                                          uint16_t Size,
                                          uint32_t Timeout);

status_t hal_i2c_masterreceiveit(i2c_handle_t *hi2c,
                                         uint16_t DevAddress,
                                         uint8_t *pData,
                                         uint16_t Size,
                                         uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif
