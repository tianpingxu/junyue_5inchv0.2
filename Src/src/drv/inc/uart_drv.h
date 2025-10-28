/**
 * @file uart_drv.h
 * @author Product application department
 * @brief  UART 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DRV_UART_H
#define __DRV_UART_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "status.h"
#include "drv_gpio_def.h"
#include "ioctrl_drv.h"
#include "uart_reg.h"

// 全局变量定义
#define UART_PIN_INDEX_TXD ((uint8_t)(0x01))
#define UART_PIN_INDEX_RXD ((uint8_t)(0x00))

#define UART_PARITY_MODE_NONE (0x00)
#define UART_PARITY_MODE_EVEN ((uint8_t)UART_PARITY_ENABLE)
#define UART_PARITY_MODE_ODD ((uint8_t)(UART_PARITY_ENABLE | UART_PARITY_ODD))

// UARTCR1
#define _uart_en_loops(uart) (uart->CR1 | UART_LOOPS_MODE)
#define _uart_dis_loops(uart) (uart->CR1 &= UART_LOOPS_NORMAL_MODE)
#define _uart_pin_opendrai_mode(uart) (uart->CR1 |= UART_OPEN_DRAIN_MODE)
#define _uart_pin_cmos_mode(uart) (uart->CR1 &= UART_CMOS_MODE)
#define _uart_data_format_9(uart) (uart->CR1 |= UART_DATA_FORMAT_MODE_9BITS)
#define _uart_data_format_8(uart) (uart->CR1 &= UART_DATA_FORMAT_MODE_8BITS)
#define _uart_wakeup_mode_add_match(uart) (uart->CR1 |= UART_WAKEUP_MODE_ADDRESS)
#define _uart_wakeup_mode_idle_lin(uart) (uart->CR1 &= UART_WAKEUP_IDLE_LINE)
#define _uart_idle_start_afer_stop(uart) (uart->CR1 |= UART_IDLE_LINE_AFTER_STOP)
#define _uart_idle_start_afer_start(uart) (uart->CR1 &= UART_IDLE_LINE_AFTER_START)
#define _uart_en_parity(uart) (uart->CR1 |= UART_PARITY_ENABLE)
#define _uart_dis_parity(uart) (uart->CR1 &= UART_PARITY_DISABLE)
#define _uart_parity_odd(uart) (uart->CR1 |= UART_PARITY_ODD)
#define _uart_parity_even(uart) (uart->CR1 &= ~UART_PARITY_ODD)

// UARTCR2
#define _uart_en_sbk(uart) _bit_set(uart->CR2, UART_SBK)
#define _uart_dis_sbk(uart) _bit_clr(uart->CR2, UART_SBK)
#define _uart_en_txd(uart) (uart->CR2 |= UART_TE)
#define _uart_dis_txd(uart) (uart->CR2 &= ~UART_TE)
#define _uart_en_rxd(uart) (uart->CR2 |= UART_RE)
#define _uart_dis_rxd(uart) (uart->CR2 &= ~UART_RE)
#define _uart_en_rx_it(uart) (uart->CR2 |= UART_IT_RIE)
#define _uart_dis_rx_it(uart) (uart->CR2 &= ~UART_IT_RIE)
#define _uart_en_tc_it(uart) (uart->CR2 |= UART_IT_TCIE)
#define _uart_en_tdre_it(uart) (uart->CR2 |= UART_IT_TIE)
#define _uart_dis_tc_it(uart) (uart->CR2 &= ~UART_IT_TCIE)
#define _uart_dis_tdre_it(uart) (uart->CR2 &= ~UART_IT_TIE)
#define _uart_en_idle_it(uart) _bit_set(uart->CR2, UART_IT_IDLE)
#define _uart_dis_idle_it(uart) _bit_clr(uart->CR2, UART_IT_IDLE)
#define _uart_get_it_source(uart, index) (uart->CR2 & index ? SET : RESET)

// UARTSR1
#define _uart_get_tx_it_flag(uart) (uart->SR1 & UART_IT_FLAG_TC)
#define _uart_get_tc_flag(uart) (uart->SR1 & UART_IT_FLAG_TC)
#define _uart_get_tdre_it_flag(uart) (uart->SR1 & UART_IT_FLAG_TDRE)
#define _uart_get_rx_it_flag(uart) (uart->SR1 & UART_IT_FLAG_RDRF)
#define _uart_get_pf_flag(uart) (uart->SR1 & UART_IT_FLAG_PF)
#define _uart_get_idle_flag(uart) (uart->SR1 & UART_IT_FLAG_IDLE)
#define _uart_clear_tx_it_flag(uart) (uart->SR1)
#define _uart_clear_rx_it_flag(uart) (uart->SR1)
#define _uart_clear_raf_it_flag(uart) (uart->SR2)
#define _uart_get_data(uart) (uart->DRL) 
#define _uart_set_tx_bit(uart) (uart->PORT |= 0x1 << UART_PIN_TXD)
#define _uart_set_rx_bit(uart) (uart->PORT |= 0x1 << UART_PIN_RXD)
#define _uart_reset_tx_bit(uart) (uart->PORT &= ~(0x1 << UART_PIN_TXD))
#define _uart_reset_rx_bit(uart) (uart->PORT &= ~(0x1 << UART_PIN_RXD))
#define _uart_get_tx_bit(uart) (uart->PORT & (0x1 << UART_PIN_TXD))
#define _uart_get_rx_bit(uart) (uart->PORT & (0x1 << UART_PIN_RXD))
#define _uart_pin_dir_output(uart, pin) _bit_set(uart->DDR, (1 << (pin + UART_PIN_INDEX_RXD)))
#define _uart_pin_dir_input(uart, pin) _bit_clr(uart->DDR, (1 << (pin + UART_PIN_INDEX_RXD)))
#define _uart_set_pin(uart, pin) _bit_set(uart->PORT, 1 << (pin + UART_PIN_INDEX_RXD))
#define _uart_reset_pin(uart, pin) _bit_clr(uart->PORT, 1 << (pin + UART_PIN_INDEX_RXD))
#define _uart_set_pin_bit(uart, pin) _bit_set(uart->PORT, 1 << (pin + UART_PIN_INDEX_RXD))
#define _uart_reset_pin_bit(uart, pin) _bit_clr(uart->PORT, 1 << (pin + UART_PIN_INDEX_RXD))
#define _uart_get_pin_bit(uart, pin) _bit_get(uart->PORT, 1 << (pin + UART_PIN_INDEX_RXD))
#define _uart_pin_output_cmos(uart) _bit_clr(uart->CR1, (1 << UART_WOMS_SHIFT_MASK))
#define _uart_pin_output_opendrain(uart) _bit_set(uart->CR1, (1 << UART_WOMS_SHIFT_MASK))
#define _uart_pin_pullup_en(uart, pin) _bit_set(uart->PURD, (1 << (pin + UART_PU_SHIFT_MASK)))
#define _uart_pin_pullup_dis(uart, pin) _bit_clr(uart->PURD, (1 << (pin + UART_PU_SHIFT_MASK)))
#define _uart_txd_output(uart) (uart->DDR |= UART_TXD_OUT)
#define _uart_rxd_output(uart) (uart->DDR |= UART_RXD_OUT)
#define _uart_txd_input(uart) (uart->DDR &= ~UART_TXD_OUT)
#define _uart_rxd_input(uart) (uart->DDR &= ~UART_RXD_OUT)
#define _uart_en_pullup(uart) (uart->PURD |= UART_PULLUP_EN)
#define _uart_dis_pullup(uart) (uart->PURD &= UART_PULLUP_DIS)
#define _uart_en_full_drive(uart) (uart->PURD &= UART_FULL_DRIVE)
#define _uart_dis_full_drive(uart) (uart->PURD |= UART_REDUCE_DRIVE)
#define _uart_reset_control1_value(uart) (uart->CR1 = 0)
#define _uart_reset_control2_value(uart) (uart->CR2 = 0)
#define _uart_get_nine_bit(uart) ((uart->DRH & 0X80) == 0X80 ? 1 : 0)

// UARTFCR
#define _uart_fifo_rx_en(uart) _bit_set(uart->FCR, UART_RF_EN)
#define _uart_fifo_rx_dis(uart) _bit_clr(uart->FCR, UART_RF_EN)
#define _uart_fifo_tx_en(uart) _bit_set(uart->FCR, UART_TF_EN)
#define _uart_fifo_tx_dis(uart) _bit_clr(uart->FCR, UART_TF_EN)
#define _uart_set_rx_fifo_level(uart, level) _reg_modify(uart->FCR, UART_RX_FLSEL_BITS_MASK, (level << UART_RX_FLSEL_SHIFT_MASK))
#define _uart_set_tx_fifo_level(uart, level) _reg_modify(uart->FCR, UART_TX_FLSEL_BITS_MASK, (level << UART_TX_FLSEL_SHIFT_MASK))
#define _uart_fifo_txrx_en(uart) _bit_set(uart->FCR, (UART_RF_EN | UART_TF_EN))
#define _uart_fifo_txrx_dis(uart) _bit_clr(uart->FCR, (UART_RF_EN | UART_TF_EN))

// UARTFSR
#define _uart_get_fifo_flag(uart, flag) _bit_get(uart->FSR, flag)
#define _uart_get_fifo_flags(uart) _reg_read(uart->FSR)

// UARTDCR
#define _uart_tx_dma_en(uart) _bit_set(uart->DCR, UART_TX_DMA_EN)
#define _uart_tx_dma_dis(uart) _bit_clr(uart->DCR, UART_TX_DMA_EN)
#define _uart_get_rx_flag(uart) _bit_get(uart->DCR, UART_RX_DMA_EN)
#define _uart_rx_dma_en(uart) _bit_set(uart->DCR, UART_RX_DMA_EN)
#define _uart_rx_dma_dis(uart) _bit_clr(uart->DCR, UART_RX_DMA_EN)
#define _uart_txrx_dma_en(uart) _bit_set(uart->DCR, (UART_TX_DMA_EN | UART_RX_DMA_EN))
#define _uart_txrx_dma_dis(uart) _bit_clr(uart->DCR, (UART_TX_DMA_EN | UART_RX_DMA_EN))

// UARTFCR2
#define _uart_fifo_tx_it_en(uart) _bit_set(uart->FCR2, UART_FIFO_TXF_IE)
#define _uart_fifo_txfc_it_en(uart) _bit_set(uart->FCR2, UART_FIFO_TXFC_IE)
#define _uart_fifo_rx_it_en(uart) _bit_set(uart->FCR2, UART_FIFO_RXF_IE)
#define _uart_fifo_rx_overrun_it_en(uart) _bit_set(uart->FCR2, UART_FIFO_RXFOR_IE)
#define _uart_fifo_rx_timeout_it_en(uart) _bit_set(uart->FCR2, UART_FIFO_RXFTO_IE)
#define _uart_fifo_rx_timeout_en(uart) _bit_set(uart->FCR2, UART_FIFO_RXF_TO_EN)
#define _uart_fifo_tx_it_dis(uart) _bit_clr(uart->FCR2, UART_FIFO_TXF_IE)
#define _uart_fifo_txfc_it_dis(uart) _bit_clr(uart->FCR2, UART_FIFO_TXFC_IE)
#define _uart_fifo_rx_it_dis(uart) _bit_clr(uart->FCR2, UART_FIFO_RXF_IE)
#define _uart_fifo_rx_overrun_it_dis(uart) _bit_clr(uart->FCR2, UART_FIFO_RXFOR_IE)
#define _uart_fifo_rx_timeout_it_dis(uart) _bit_clr(uart->FCR2, UART_FIFO_RXFTO_IE)
#define _uart_fifo_rx_timeout_dis(uart) _bit_clr(uart->FCR2, UART_FIFO_RXF_TO_EN)
#define _uart_fifo_tx_clr(uart) _bit_set(uart->FCR2, UART_FIFO_TXF_CLR)
#define _uart_fifo_rx_clr(uart) _bit_set(uart->FCR2, UART_FIFO_RXF_CLR)

// UARTRXFTOCRT
#define _uart_set_rx_fifo_tiemout_cnt(uart, cnt) _reg_write(uart->RXTOCTR, cnt)

// UARTFSR2
#define _uart_get_fifo_mode_overrun_flag(uart) _bit_get(uart->FSR2, UART_FXOR)
#define _uart_get_fifo_mode_noise_flag(uart) _bit_get(uart->FSR2, UART_FXNF)
#define _uart_get_fifo_mode_frame_err_flag(uart) _bit_get(uart->FSR2, UART_FXFE)
#define _uart_get_fifo_mode_parity_err_flag(uart) _bit_get(uart->FSR2, UART_FXPF)
#define _uart_clear_fifo_mode_overrun_flag(uart) _bit_set(uart->FSR2, UART_FXOR)
#define _uart_clear_fifo_mode_noise_flag(uart) _bit_set(uart->FSR2, UART_FXNF)
#define _uart_clear_fifo_mode_frame_err_flag(uart) _bit_set(uart->FSR2, UART_FXFE)
#define _uart_clear_fifo_mode_parity_err_flag(uart) _bit_set(uart->FSR2, UART_FXPF)

/**
 * @brief UART 模块TXRX管脚枚举定义
 */
typedef enum
{
    UART_PIN_RXD,
    UART_PIN_TXD
} uart_pin_t;

/**
 * @brief UART 模块标志索引枚举定义
 */
typedef enum
{
    UART_FLAG_INDEX_PF,
    UART_FLAG_INDEX_FE,
    UART_FLAG_INDEX_NF,
    UART_FLAG_INDEX_OR,
    UART_FLAG_INDEX_IDLE,
    UART_FLAG_INDEX_RDRF,
    UART_FLAG_INDEX_TC,
    UART_FLAG_INDEX_TDRE,
    UART_FLAG_INDEX_RAF,
} uart_flagindex_t;

/**
 * @brief UART 模块fifo标志索引枚举定义
 */
typedef enum
{
    UART_FLAG_INDEX_TFTS = 7,
    UART_FLAG_INDEX_FTC = 6,
    UART_FLAG_INDEX_RFTS = 5,
    UART_FLAG_INDEX_RTOS = 4,
    UART_FLAG_INDEX_T_FULL = 3,
    UART_FLAG_INDEX_T_EMPTY = 2,
    UART_FLAG_INDEX_R_FULL = 1,
    UART_FLAG_INDEX_R_EMPTY = 0,
} uart_fifoflagindex_t;

/**
 * @brief UART 模块中断索引枚举定义
 */
typedef enum
{
    UART_IT_INDEX_TDRE = 0X80,
    UART_IT_INDEX_TCIE = 0X40,
    UART_IT_INDEX_RIE = 0X20,
    UART_IT_INDEX_ILIE = 0X10,
} uart_itindex_t;

/**
 * @brief UART 模块fifo中断索引枚举定义
 */
typedef enum
{
    UART_IT_INDEX_TXFIE = 0X80,
    UART_IT_INDEX_TXFCIE = 0X40,
    UART_IT_INDEX_RXFIE = 0X20,
    UART_IT_INDEX_RXORIE = 0X10,
    UART_IT_INDEX_RXFTOIE = 0X08,
    UART_IT_INDEX_RXFTOE = 0X04
} uart_fifoitindex_t;

/**
 * @brief UART 模块fifo深度枚举定义
 */
typedef enum
{
    UART_FIFO_1_8 = 0x0,
    UART_FIFO_1_4 = 0x1,
    UART_FIFO_1_2 = 0x2,
    UART_FIFO_3_4 = 0x3,
    UART_FIFO_7_8 = 0x4,
} uart_fifofull_t;

/**
 * @brief UART 模块初始化结构体定义
 */
typedef struct
{
    uint32_t BaudRate;
    uint32_t DatabitsLength;
    uint32_t StopbitsLength;
    uint32_t Parity;
    uint32_t IPSFreq;
    uint8_t RxFifoEn;
    uint8_t RxFifoFull;
    uint8_t TxFifoEn;
    uint8_t TxFifoFull;
    uint8_t IdleEn;
} uart_init_t, *p_uart_init_t;

/**
 * @brief UART 模块DMA缓存结构体定义
 */
typedef struct
{
    uint8_t *p_src;
    uint32_t buff_len;
    uint8_t **pp_wr;
    uint8_t *p_rd;
} uart_ringbuf_t;

// 函数声明
void drv_uart_funcswap(uart_typedef_t *puart);
void drv_uart_init(uart_typedef_t *puart, uart_init_t Init);
void drv_uart_deinit(uart_typedef_t *puart);
void drv_uart_sendbyte(uart_typedef_t *puart, uint8_t outbyte);
void drv_uart_sendbytes(uart_typedef_t *puart, uint8_t *pbuf, uint16_t len);
void drv_uart_entx(uart_typedef_t *puart);
void drv_uart_distx(uart_typedef_t *puart);
void drv_uart_enrx(uart_typedef_t *puart);
void drv_uart_disrx(uart_typedef_t *puart);
void drv_uart_dis(uart_typedef_t *puart);
void drv_uart_en(uart_typedef_t *puart);
void drv_uart_sendbytehex(uart_typedef_t *puart, uint8_t send);
void drv_uart_sendstring(uart_typedef_t *puart, char *str);
void drv_uart_disittie(uart_typedef_t *puart);
void drv_uart_disittcie(uart_typedef_t *puart);
void drv_uart_disitre(uart_typedef_t *puart);
void drv_uart_enittie(uart_typedef_t *puart);
void drv_uart_enittcie(uart_typedef_t *puart);
void drv_uart_enitre(uart_typedef_t *puart);
void drv_uart_enfifoit(uart_typedef_t *puart, uint8_t index);
void drv_uart_disfifoit(uart_typedef_t *puart, uint8_t index);
void drv_uart_enit(uart_typedef_t *puart, uart_itindex_t index);
void drv_uart_disit(uart_typedef_t *puart, uart_itindex_t index);
status_t drv_uart_getflag(uart_typedef_t *puart,uart_flagindex_t index,flagstatus_t *flag);
status_t drv_uart_clearflag(uart_typedef_t *puart,uart_flagindex_t index);
status_t drv_uart_waitonflagtimeout(uart_typedef_t *puart, uart_flagindex_t index,flagstatus_t status,uint32_t timeout);
status_t drv_uart_senddata(uart_typedef_t *puart, uint16_t tosend, uint8_t bits);
status_t drv_uart_getdata(uart_typedef_t *puart, uint16_t *pres, uint8_t bits);
status_t drv_uart_getstatus(uart_typedef_t *puart, uint8_t *pstatus1, uint8_t *pstatus2);
flagstatus_t drv_uart_getitsource(uart_typedef_t *puart, uart_itindex_t index);
flagstatus_t drv_uart_getfifoitsource(uart_typedef_t *puart, uint8_t index);
void drv_uart_settxddiroutput(uart_typedef_t *puart);
void drv_uart_settxddirinput(uart_typedef_t *puart);
void drv_uart_setrxddiroutput(uart_typedef_t *puart);
void drv_uart_setrxddirinput(uart_typedef_t *puart);
void drv_uart_enpullup(uart_typedef_t *puart);
void drv_uart_dispullup(uart_typedef_t *puart);
void drv_uart_setoutputopendrain(uart_typedef_t *puart);
void drv_uart_setoutputcmos(uart_typedef_t *puart);
void drv_uart_settxdpinbit(uart_typedef_t *puart);
void drv_uart_resettxdpinbit(uart_typedef_t *puart);
void drv_uart_setrxdpinbit(uart_typedef_t *puart);
void drv_uart_resetrxdpinbit(uart_typedef_t *puart);
gpio_pinstate_t drv_uart_gettxdpinbit(uart_typedef_t *puart);
gpio_pinstate_t drv_uart_getrxdpinbit(uart_typedef_t *puart);
void drv_uart_setpinbit(uart_typedef_t *puart, uint8_t pin);
void drv_uart_resetpinbit(uart_typedef_t *puart, uint8_t pin);
gpio_pinstate_t drv_uart_getpinbit(uart_typedef_t *puart, uint8_t pin);
void drv_uart_rxdpintoggle(uart_typedef_t *puart);
void drv_uart_txdpintoggle(uart_typedef_t *puart);
void drv_uart_putsdev(volatile const uint8_t *s);
status_t drv_uart_setrxfifotiemout(uart_typedef_t *puart, uint8_t cnt);
uint32_t drv_uart_ringbuf_getdatalen(uart_typedef_t *puart);
status_t drv_uart_ringbuf_read(uart_typedef_t *puart, uint8_t *prxbuf, uint32_t rxlen);
status_t drv_uart_dmareceive_ringbuf_init(uart_typedef_t *puart, uint8_t channel, uint8_t *dest, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
