/**
 * @file spi_hal.h
 * @author Product application department
 * @brief  SPI 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef _SPI_HAL_H
#define _SPI_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "spi_drv.h"
#include "dma_hal.h"
#include "interrupt.h"
#include "pinswap_drv.h"
    
// 全局变量定义
#define CMD_HEAD ((uint32_t)0x55)
#define DUMMY_DATA ((uint32_t)0x5A)
#define HAL_SPI_ERROR_NONE ((uint32_t)0x00000000)
#define HAL_SPI_ERROR_MODF ((uint32_t)0x00000001)
#define HAL_SPI_ERROR_CRC ((uint32_t)0x00000002)
#define HAL_SPI_ERROR_OVR ((uint32_t)0x00000004)
#define HAL_SPI_ERROR_FRE ((uint32_t)0x00000008)
#define HAL_SPI_ERROR_DMA ((uint32_t)0x00000010)
#define HAL_SPI_ERROR_FLAG ((uint32_t)0x00000020)

/**
 * @brief SPI 模块分频系数枚举定义
 * 
 */
typedef enum
{
    SPI_SPPR0_DIV2 = 0,
    SPI_SPPR1_DIV2 = 0,

    SPI_SPPR0_DIV4 = 1,
    SPI_SPPR1_DIV4 = 0,

    SPI_SPPR0_DIV6 = 0,
    SPI_SPPR1_DIV6 = 2,

    SPI_SPPR0_DIV8 = 2,
    SPI_SPPR1_DIV8 = 0,

    SPI_SPPR0_DIV10 = 0,
    SPI_SPPR1_DIV10 = 4,

    SPI_SPPR0_DIV12 = 1,
    SPI_SPPR1_DIV12 = 2,

    SPI_SPPR0_DIV14 = 0,
    SPI_SPPR1_DIV14 = 6,

    SPI_SPPR0_DIV16 = 3,
    SPI_SPPR1_DIV16 = 0,

    SPI_SPPR0_DIV20 = 1,
    SPI_SPPR1_DIV20 = 4,

    SPI_SPPR0_DIV24 = 1,
    SPI_SPPR1_DIV24 = 5,

    SPI_SPPR0_DIV28 = 1,
    SPI_SPPR1_DIV28 = 6,

    SPI_SPPR0_DIV32 = 4,
    SPI_SPPR1_DIV32 = 0,

    SPI_SPPR0_DIV40 = 2,
    SPI_SPPR1_DIV40 = 4,

    SPI_SPPR0_DIV64 = 5,
    SPI_SPPR1_DIV64 = 0,

    SPI_SPPR0_DIV128 = 6,
    SPI_SPPR1_DIV128 = 0,

    SPI_SPPR0_DIV256 = 7,
    SPI_SPPR1_DIV256 = 0,
 } spi_div_t;

/**
 * @brief SPI 模块状态标志枚举定义
 * 
 */
typedef enum
{
    HAL_SPI_STATE_RESET = 0x00,
    HAL_SPI_STATE_READY = 0x01,
    HAL_SPI_STATE_BUSY = 0x02,
    HAL_SPI_STATE_BUSY_TX = 0x12,
    HAL_SPI_STATE_BUSY_RX = 0x22,
    HAL_SPI_STATE_BUSY_TX_RX = 0x32,
    HAL_SPI_STATE_ERROR = 0x03
} spi_state_t;

typedef void (*hal_spi_callback)(void *);

/**
 * @brief SPI 模块句柄结构体定义
 * 
 */
typedef struct
{
    reg_spi_t *Instance;
    spi_init_t Init;
    uint8_t *pRxBuf;
    uint16_t RxSize;
    uint16_t RxCnt;
    uint8_t *pTxBuf;
    uint16_t TxSize;
    uint16_t TxCnt;
    spi_state_t State;
    __IO uint32_t ErrorCode;
    hal_spi_callback XferCpltCallback;
    hal_spi_callback ErrCallback;
    hal_spi_callback TxIsrCallback;
    hal_spi_callback RxIsrCallback;
} spi_handletypedef_t;

// 函数声明
void hal_spi_lli_irqhandler(void);
void hal_spi_init(volatile spi_handletypedef_t *hspi);
void hal_spi_dmac_lli_m2p_transfer(reg_dmac_t *DMAC, uint8_t channel, uint32_t *addr_peri, uint8_t *buf, int buf_len, int pkt_len);
status_t hal_spi_transmit(volatile spi_handletypedef_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
status_t hal_spi_receive(volatile spi_handletypedef_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
void hal_spi_dis(volatile spi_handletypedef_t *hspi);
void hal_spi_en(volatile spi_handletypedef_t *hspi);
void hal_spi_clrrxfifo(volatile spi_handletypedef_t *hspi);
void hal_spi_clrtxfifo(volatile spi_handletypedef_t *hspi);
void hal_spi_gpiowritepin(reg_spi_t *pspi, uint16_t Pin, gpio_pinstate_t PinState);
void hal_spi_irqhandler(void);
void hal_spi_enrxdma(volatile spi_handletypedef_t *hspi);
void hal_spi_entxdma(volatile spi_handletypedef_t *hspi);
status_t hal_spi_transmitit(volatile spi_handletypedef_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
status_t hal_spi_dma_mastertxpolling(reg_dmac_t *pdmac, uint8_t ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len);
status_t hal_spi_dma_masterrxpolling(reg_dmac_t *pdmac, uint8_t tx_ch, uint8_t rx_ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len);
status_t hal_spi_dma_slaverxpolling(reg_dmac_t *pdmac, uint8_t ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len);
status_t hal_spi_dma_slavetxpolling(reg_dmac_t *pdmac, uint8_t ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len);
status_t hal_spi_receiveit(volatile spi_handletypedef_t *hspi, uint8_t *pdata, uint16_t size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif