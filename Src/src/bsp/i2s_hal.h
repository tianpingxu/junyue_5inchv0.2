/**
 * @file i2s_reg.h
 * @author Product Application Department
 * @brief  I2S 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I2S_HAL_H
#define __I2S_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i2s_drv.h"
#include "status.h"
#include "interrupt.h"
#include "dma_hal.h"
    
// 全局定义
#define HAL_I2S_ERROR_NONE (0x00000000U)    /*!< No error              */
#define HAL_I2S_ERROR_BERR (0x00000001U)    /*!< BERR error            */
#define HAL_I2S_ERROR_ARLO (0x00000002U)    /*!< ARLO error            */
#define HAL_I2S_ERROR_AF (0x00000004U)      /*!< ACKF error            */
#define HAL_I2S_ERROR_OVR (0x00000008U)     /*!< OVR error             */
#define HAL_I2S_ERROR_DMA (0x00000010U)     /*!< DMA transfer error    */
#define HAL_I2S_ERROR_TIMEOUT (0x00000020U) /*!< Timeout error         */
#define HAL_I2S_ERROR_SIZE (0x00000040U)    /*!< Size Management error */

/**
 * @brief I2S 模块通信状态枚举定义
 * 
 */
typedef enum
{
    HAL_I2S_STATE_RESET = 0x00,   /*!< Peripheral is not yet Initialized              */
    HAL_I2S_STATE_READY = 0x20,   /*!< Peripheral Initialized and ready for use      */
    HAL_I2S_STATE_BUSY = 0x24,    /*!< An internal process is ongoing                 */
    HAL_I2S_STATE_BUSY_TX = 0x21, /*!< Data Transmission process is ongoing           */
    HAL_I2S_STATE_BUSY_RX = 0x22, /*!< Data Reception process is ongoing              */
    HAL_I2S_STATE_BUSY_DEVADD_READ = 0X23,
    HAL_I2S_STATE_LISTEN = 0x28,         /*!< Address Listen Mode is ongoing                 */
    HAL_I2S_STATE_BUSY_TX_LISTEN = 0x29, /*!< Address Listen Mode and Data Transmission process is ongoing */
    HAL_I2S_STATE_BUSY_RX_LISTEN = 0x2A, /*!< Address Listen Mode and Data Reception process is ongoing    */
    HAL_I2S_STATE_ABORT = 0x60,          /*!< Abort user request ongoing                     */
    HAL_I2S_STATE_TIMEOUT = 0xA0,        /*!< Timeout state                                  */
    HAL_I2S_STATE_ERROR = 0xE0,          /*!< Error                                         */
    HAL_I2S_STATE_BUSY_MEM_SUBADD = 0XF0,
    HAL_I2S_STATE_BUSY_MEM_TX = 0XF1,
    HAL_I2S_STATE_BUSY_MEM_RX = 0XF2,
    HAL_I2S_STATE_BUSY_MEM_DEVADD_RESTART_READ = 0XF3,
    HAL_I2S_STATE_BUSY_MEM_STOP = 0XF4,
} i2s_state_t;

/**
 * @brief I2S 模块初始化结构体定义.
 * 
 */
typedef struct
{
    reg_i2s_t *Instance;
    i2s_init_t Init;
    uint32_t SubAdd;
    uint32_t MemAdd;
    uint32_t MemAddSize;
    uint8_t XferFlag;
    uint8_t *pXferBuf;
    uint8_t *pTxBuf;
    uint32_t XferSize;
    uint32_t XferCnt;
    i2s_state_t State;
    __IO i2s_mode_t Mode;
    uint32_t ErrorCode;
} i2s_handle_t;

// 函数声明
status_t hal_i2s_init(i2s_handle_t *hi2s);
status_t hal_i2s_mastertransmit(i2s_handle_t *hi2s, uint8_t *pData, uint32_t Size, uint32_t Timeout);
status_t hal_i2s_masterreceive(i2s_handle_t *hi2s, uint8_t *pData, uint32_t Size, uint32_t Timeout);
status_t hal_i2s_dmactx(uint8_t ch, reg_i2s_t *pi2s, uint8_t *pbuf, uint32_t len);
status_t hal_i2s_dmacrx(uint8_t ch, reg_i2s_t *pi2s, uint8_t *pbuf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
