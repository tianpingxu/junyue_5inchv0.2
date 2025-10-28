/**
 * @file uart_hal.h
 * @author Product application department
 * @brief  UART 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __HAL_UART_H
#define __HAL_UART_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "uart_drv.h"
#include "interrupt.h"

// 全局变量定义
#define UART_BUFFER_SIZE 0x100
#define HAL_UART_ERROR_NONE ((uint32_t)0x00)
#define HAL_UART_ERROR_PE ((uint32_t)0x01)
#define HAL_UART_ERROR_NE ((uint32_t)0x02)
#define HAL_UART_ERROR_FE ((uint32_t)0x04)
#define HAL_UART_ERROR_ORE ((uint32_t)0x08)
#define HAL_UART_ERROR_DMA ((uint32_t)0x10)

/**
 * @brief UART 模块状态结构体定义
 * 
 */
typedef enum
{
    HAL_UART_STATE_RESET = 0x00,
    HAL_UART_STATE_READY = 0x20,
    HAL_UART_STATE_BUSY = 0x24,
    HAL_UART_STATE_BUSY_TX = 0x21,
    HAL_UART_STATE_BUSY_RX = 0x22,
    HAL_UART_STATE_BUSY_TX_RX = 0x23,
    HAL_UART_STATE_TIMEOUT = 0xA0,
    HAL_UART_STATE_ERROR = 0xE0
} uart_state_t;

/**
 * @brief UART 模块句柄结构体定义
 * 
 */
typedef struct
{
    uart_typedef_t *Instance;
    uart_init_t Init;
    uint8_t *pTxBuffPtr;
    uint16_t TxXferSize;
    uint16_t TxXferCount;
    uint8_t *pRxBuffPtr;
    uint16_t RxXferSize;
    uint16_t RxXferCount;
    uart_state_t State;
    uint32_t ErrorCode;
} uart_handle_t;

// 函数声明
void hal_uartswap_init(uart_typedef_t *huart);
status_t hal_uart_init(uart_handle_t *huart);
void hal_uart_itinit(void);
status_t hal_uart_transmit(uart_handle_t *huart, uint8_t *pdata, uint16_t size, uint32_t timeout);
status_t hal_uart_receive(uart_handle_t *huart, uint8_t *pdata, uint16_t size, uint32_t timeout);
status_t hal_uart_transmitit(uart_handle_t *huart, uint8_t *pdata, uint16_t size);
status_t hal_uart_receiveit(uart_handle_t *huart, uint8_t *pdata, uint16_t size);
gpio_pinstate_t hal_uart_gpioreadpin(uart_typedef_t *puart, uart_pin_t Pin);
void hal_uart_gpioinit(uart_typedef_t *puart, gpio_init_t *gpio_init);
void hal_uart_enrxdma(uart_typedef_t *huart);
void hal_uart_senddata(uart_typedef_t *huart, uint8_t *send, uint16_t len);
status_t hal_uart_setrxfifotiemout(uart_typedef_t *huart, uint8_t cnt);
status_t hal_uart_dmareceive_ringbuf_init(uart_typedef_t *puart, uint8_t channel, uint8_t *dest, uint32_t len);
void hal_uart_reset(void);
#ifdef __cplusplus
}
#endif

#endif
