/**
 * @file spi_drv.h
 * @author Product application department
 * @brief  SPI 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __SPI_DRV_H
#define __SPI_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "status.h"
#include "drv_gpio_def.h"
#include "ioctrl_drv.h"
#include "spi_reg.h"

// 全局变量定义
#define SPI_IT_SPIF (uint8_t)(1)
#define SPI_IT_WCOL (uint8_t)(2)
#define SPI_IT_FLOST (uint8_t)(3)

#define SPI_PIN_CS 0X03
#define SPI_PIN_CLK 0X02
#define SPI_PIN_MOSI 0X01
#define SPI_PIN_MISO 0X00
#define SPI_FIFO_MAX_SIZE 0X08

#define SPI_IT_INDEX_SPIE 0X80
#define SPI_IT_INDEX_FLOSTIE 0X20
#define SPI_IT_INDEX_MODFIE 0X10
#define SPI_IT_INDEX_SSIE 0X80

#define SPI_IT_INDEX_RXFTOIE 0X80
#define SPI_IT_INDEX_RXFTOE 0X40

#define SPI_IT_INDEX_TXFTOIE 0X80
#define SPI_IT_INDEX_TXFTOE 0X40

#define SPI_IT_INDEX_RXFOVIE 0X40
#define SPI_IT_INDEX_RXFUDIE 0X20
#define SPI_IT_INDEX_RXFSTHIE 0X10

#define SPI_IT_INDEX_TXFOVIE 0X40
#define SPI_IT_INDEX_TXFUDIE 0X20
#define SPI_IT_INDEX_TXFSTHIE 0X10

// frame register
#define _spi_en_continous_cs(spi) _bit_set(spi->FR, SPI_EN_CONT_CS)
#define _spi_dis_continous_cs(spi) _bit_clr(spi->FR, SPI_EN_CONT_CS)
#define _spi_en_guard_time(spi) _bit_set(spi->FR, SPI_EN_GUARD_TIME)
#define _spi_dis_guard_time(spi) _bit_clr(spi->FR, SPI_EN_GUARD_TIME)
#define _spi_loop_back_mode(spi) _bit_set(spi->FR, SPI_LOOP_BACK_MODE)
#define _spi_loop_normal_mode(spi) _bit_clr(spi->FR, SPI_LOOP_BACK_MODE)
#define _spi_frame_format_ti(spi) _bit_set(spi->FR, SPI_FRAME_FORMAT_TI)
#define _spi_frame_format_freescale(spi) _bit_clr(spi->FR, SPI_FRAME_FORMAT_TI)
#define _spi_set_frame_size(spi, size) _reg_modify(spi->FR, SPI_FRAME_SIZE_MASK, size)

// control register 1
#define _spi_en_it(spi) _bit_set(spi->CR1, SPI_EN_IT)
#define _spi_dis_it(spi) _bit_clr(spi->CR1, SPI_EN_IT)
#define _spi_get_it(spi) _bit_get(spi->CR1, SPI_EN_IT)
#define _spi_en(spi) _bit_set(spi->CR1, SPI_EN)
#define _spi_dis(spi) _bit_clr(spi->CR1, SPI_EN)
#define _spi_get_en(spi) _bit_get(spi->CR1, SPI_EN)
#define _spi_out_mode_cmos(spi) _bit_set(spi->CR1, SPI_WIRED_OR_MODE_CMOS)
#define _spi_out_mode_opendrain(spi) _bit_clr(spi->CR1, SPI_WIRED_OR_MODE_CMOS)
#define _spi_pin_output_cmos(spi) _bit_set(spi->CR1, SPI_WIRED_OR_MODE_CMOS)
#define _spi_pin_output_opendrain(spi) _bit_clr(spi->CR1, SPI_WIRED_OR_MODE_CMOS)
#define _spi_master(spi) _bit_set(spi->CR1, SPI_MASTER)
#define _spi_slave(spi) _bit_clr(spi->CR1, SPI_MASTER)
#define _spi_cpol_idle_high(spi) _bit_set(spi->CR1, SPI_CPOL_HIGH)
#define _spi_cpol_idle_low(spi) _bit_clr(spi->CR1, SPI_CPOL_HIGH)
#define _spi_cpha_edge_2(spi) _bit_set(spi->CR1, SPI_CPHA_2EDGE)
#define _spi_cpha_edge_1(spi) _bit_clr(spi->CR1, SPI_CPHA_2EDGE)
#define _spi_en_ssoe(spi) _bit_set(spi->CR1, SPI_EN_SSOE)
#define _spi_dis_ssoe(spi) _bit_clr(spi->CR1, SPI_EN_SSOE)
#define _spi_data_lsb(spi) _bit_set(spi->CR1, SPI_FIRSTBIT_LSB)
#define _spi_data_msb(spi) _bit_clr(spi->CR1, SPI_FIRSTBIT_LSB)

// spi control register2
#define _spi_set_guard_time(spi, time) _reg_modify(spi->CR2, SPI_GUARD_TIME_MASK, time)
#define _spi_doze_inactive(spi) _bit_set(spi->CR2, SPI_DOZE_INACTIVE_MODE)
#define _spi_doze_active(spi) _bit_clr(spi->CR2, SPI_DOZE_INACTIVE_MODE)
#define _spi_spc0_normal_mode(spi) _bit_set(spi->CR2, SPI_SPC0_BIDIR_MODE)
#define _spi_spc0_bidir_mode(spi) _bit_clr(spi->CR2, SPI_SPC0_BIDIR_MODE)

// tx fifo timeout counter register
#define _spi_en_tx_fifo_timeout_it(spi) _bit_set(spi->TXFTOCRT, SPI_EN_TX_FIFO_TINEOUT_IT)
#define _spi_dis_tx_fifo_timeout_it(spi) _bit_clr(spi->TXFTOCRT, SPI_EN_TX_FIFO_TINEOUT_IT)
#define _spi_dis_tx_fifo_timeout_it(spi) _bit_clr(spi->TXFTOCRT, SPI_EN_TX_FIFO_TINEOUT_IT)
#define _spi_get_tx_fifo_timeout_it(spi) _bit_get(spi->TXFTOCRT, SPI_EN_TX_FIFO_TINEOUT_IT)
#define _spi_en_tx_fifo_timeout(spi) _bit_set(spi->TXFTOCRT, SPI_EN_TX_FIFO_TINEOUT)
#define _spi_dis_tx_fifo_timeout(spi) _bit_clr(spi->TXFTOCRT, SPI_EN_TX_FIFO_TINEOUT)
#define _spi_set_tx_fifo_time_cnt(spi, cnt) _reg_modify(spi->TXFTOCTR, SPI_TX_FIFO_TIMEOUT_CNT_MASK, cnt)

// rx fifo timeout counter register
#define _spi_en_rx_fifo_timeout_it(spi) _bit_set(spi->RXFTOCRT, SPI_EN_RX_FIFO_TINEOUT_IT)
#define _spi_dis_rx_fifo_timeout_it(spi) _bit_clr(spi->RXFTOCRT, SPI_EN_RX_FIFO_TINEOUT_IT)
#define _spi_get_rx_fifo_timeout_it(spi) _bit_get(spi->RXFTOCRT, SPI_EN_RX_FIFO_TINEOUT_IT)
#define _spi_en_rx_fifo_timeout(spi) _bit_set(spi->RXFTOCRT, SPI_EN_RX_FIFO_TINEOUT)
#define _spi_dis_rx_fifo_timeout(spi) _bit_clr(spi->RXFTOCRT, SPI_EN_RX_FIFO_TINEOUT)
#define _spi_set_rx_fifo_time_cnt(spi, cnt) _reg_modify(spi->RXFTOCTR, SPI_RX_FIFO_TIMEOUT_CNT_MASK, cnt)

// spi tx fifo cotrol register
#define _spi_clr_tx_fifo(spi) _bit_set(spi->TXFCR, SPI_TX_FIFO_CLEAR)
#define _spi_en_tx_fifo_overflow_it(spi) _bit_set(spi->TXFCR, SPI_EN_TX_FIFO_OVERFLOW_IT)
#define _spi_get_tx_fifo_overflow_it(spi) _bit_get(spi->TXFCR, SPI_EN_TX_FIFO_OVERFLOW_IT)
#define _spi_en_tx_fifo_underflow_it(spi) _bit_set(spi->TXFCR, SPI_EN_TX_FIFO_UNDERFLOW_IT)
#define _spi_dis_tx_fifo_underflow_it(spi) _bit_clr(spi->TXFCR, SPI_EN_TX_FIFO_UNDERFLOW_IT)
#define _spi_get_tx_fifo_underflow_it(spi) _bit_get(spi->TXFCR, SPI_EN_TX_FIFO_UNDERFLOW_IT)
#define _spi_en_tx_fifo_service_th_it(spi) _bit_set(spi->TXFCR, SPI_EN_TX_FIFO_SERVICE_THRESHOLD_IT)
#define _spi_dis_tx_fifo_service_th_it(spi) _bit_clr(spi->TXFCR, 0x10)
#define _spi_get_tx_fifo_service_th_it(spi) _bit_get(spi->TXFCR, 0x10)
#define _spi_set_tx_fifo_threshold(spi, threshold) _reg_modify(spi->TXFCR, SPI_TX_FIFO_SERVICE_TRHESHOLD_MASK, threshold)

// spi rx fifo cotrol register
#define _spi_clr_rx_fifo(spi) _bit_set(spi->RXFCR, SPI_RX_FIFO_CLEAR)
#define _spi_en_rx_fifo_overflow_it(spi) _bit_set(spi->RXFCR, SPI_EN_RX_FIFO_OVERFLOW_IT)
#define _spi_dis_rx_fifo_overflow_it(spi) _bit_clr(spi->RXFCR, SPI_EN_RX_FIFO_OVERFLOW_IT)
#define _spi_get_rx_fifo_overflow_it(spi) _bit_get(spi->RXFCR, SPI_EN_RX_FIFO_OVERFLOW_IT)
#define _spi_en_rx_fifo_underflow_it(spi) _bit_set(spi->RXFCR, SPI_EN_RX_FIFO_UNDERFLOW_IT)
#define _spi_dis_rx_fifo_underflow_it(spi) _bit_clr(spi->RXFCR, SPI_EN_RX_FIFO_UNDERFLOW_IT)
#define _spi_get_rx_fifo_underflow_it(spi) _bit_get(spi->RXFCR, SPI_EN_RX_FIFO_UNDERFLOW_IT)
#define _spi_en_rx_fifo_service_th_it(spi) _bit_set(spi->RXFCR, SPI_EN_RX_FIFO_SERVICE_THRESHOLD_IT)
#define _spi_dis_rx_fifo_service_th_it(spi) _bit_clr(spi->RXFCR, SPI_EN_RX_FIFO_SERVICE_THRESHOLD_IT)
#define _spi_get_rx_fifo_service_th_it(spi) _bit_get(spi->RXFCR, SPI_EN_RX_FIFO_SERVICE_THRESHOLD_IT)
#define _spi_set_rx_fifo_threshold(spi, threshold) _reg_modify(spi->RXFCR, SPI_RX_FIFO_SERVICE_TRHESHOLD_MASK, threshold)

// pullup and reduced driver register
#define _spi_en_high_speed(spi) _bit_set(spi->PURD, SPI_EN_HIGH_SPEED)
#define _spi_dis_high_speed(spi) _bit_clr(spi->PURD, SPI_EN_HIGH_SPEED)
#define _spi_en_mosi_miso_switch(spi) _bit_set(spi->PURD, SPI_EN_MISO_MOSI_SWITCH)
#define _spi_dis_mosi_miso_switch(spi) _bit_clr(spi->PURD, SPI_EN_MISO_MOSI_SWITCH)
#define _spi_en_tx_data_double_mode(spi) _bit_set(spi->PURD, SPI_EN_DOUBLE_TX_DATA_MODE)
#define _spi_dis_tx_data_double_mode(spi) _bit_clr(spi->PURD, SPI_EN_DOUBLE_TX_DATA_MODE)
#define _spi_set_smaple_delay(spi, tt) _reg_modify(spi->PURD, SPI_MASTER_SAMPLE_POINT_DELAY_MASK, tt)
#define _spi_en_pullup(spi) _bit_set(spi->PURD, SPI_EN_PULLUP_DEVICE)
#define _spi_dis_pullup(spi) _bit_clr(spi->PURD, SPI_EN_PULLUP_DEVICE)
#define _spi_en_pulldown(spi) _bit_set(spi->PURD, SPI_EN_PULLDOWN_DEVICE)
#define _spi_dis_pulldown(spi) _bit_clr(spi->PURD, SPI_EN_PULLDOWN_DEVICE)

// SPI port data direction register
#define _spi_pin_spi(spi, pin) _bit_clr(spi->DDR, (1 << (pin + SPI_PPS_SHIFT_MASK)))
#define _spi_pin_gpio(spi, pin) _bit_set(spi->DDR, (1 << (pin + SPI_PPS_SHIFT_MASK)))
#define _spi_pin_output(spi, pin) _bit_set(spi->DDR, (1 << pin))
#define _spi_pin_input(spi, pin) _bit_clr(spi->DDR, (1 << pin))
#define _spi_pin_dir_output(spi, pin) _bit_set(spi->DDR, (1 << pin))
#define _spi_pin_dir_input(spi, pin) _bit_clr(spi->DDR, (1 << pin))
// spi port data register
#define _spi_set_pin_bit(spi, pin) _bit_set(spi->PORT, (1 << pin))
#define _spi_reset_pin_bit(spi, pin) _bit_clr(spi->PORT, (1 << pin))
#define _spi_set_cs_bit(spi) _bit_set(spi->PORT, 1 << SPI_PIN_CS)
#define _spi_reset_cs_bit(spi) _bit_clr(spi->PORT, 1 << SPI_PIN_CS)
#define _spi_set_mosi_bit(spi) _bit_set(spi->PORT, 1 << SPI_PIN_MOSI)
#define _spi_reset_mosi_bit(spi) _bit_clr(spi->PORT, 1 << SPI_PIN_MOSI)
#define _spi_set_miso_bit(spi) _bit_set(spi->PORT, 1 << SPI_PIN_MISO)
#define _spi_reset_miso_bit(spi) _bit_clr(spi->PORT, 1 << SPI_PIN_MISO)
#define _spi_set_clk_bit(spi) _bit_set(spi->PORT, 1 << SPI_PIN_CLK)
#define _spi_reset_clk_bit(spi) _bit_clr(spi->PORT, 1 << SPI_PIN_CLK)
#define _spi_get_pin_bit(spi, pin) _bit_get(spi->PORT, (1 << pin))
#define _spi_get_cs_bit(spi) ((spi->PORT & (1 << SPI_PIN_CS)) ? 1 : 0)
#define _spi_get_mosi_bit(spi) ((spi->PORT & (1 << SPI_PIN_MOSI)) ? 1 : 0)
#define _spi_get_miso_bit(spi) ((spi->PORT & (1 << SPI_PIN_MISO)) ? 1 : 0)
#define _spi_get_clk_bit(spi) ((spi->PORT & (1 << SPI_PIN_CLK)) ? 1 : 0)
#define _spi_bit_set(spi, pin) _bit_set(spi->PORT, (1 << pin))
#define _spi_reset_bit(spi, pin) _bit_clr(spi->PORT, (1 << pin))
#define _spi_get_pin_bit(spi, pin) _bit_get(spi->PORT, (1 << pin))
#define _spi_toggle_pin(spi, pin) (spi->PORT ^= (1 << pin))
#define _spi_get_port_bits(spi) _reg_read(spi->PORT)

// interrupt register of SS pin
#define _spi_en_ss_it(spi) _bit_set(spi->IRSP, SPI_EN_SS_IT)
#define _spi_dis_ss_it(spi) _bit_clr(spi->IRSP, SPI_EN_SS_IT)
#define _spi_get_ss_it(spi) _bit_get(spi->IRSP, SPI_EN_SS_IT)
#define _spi_ss_pin_trigger_level_high(spi) _bit_set(spi->IRSP, SPI_SS_LEVEL_HIGH)
#define _spi_ss_pin_trigger_level_low(spi) _bit_clr(spi->IRSP, SPI_SS_LEVEL_HIGH)
#define _spi_get_ss_pin_falg(spi) _bit_get(spi->IRSP, SPI_SS_PIN_FLAG)
#define _spi_ss_pin_clear_flag(spi) _bit_set(spi->IRSP, SPI_SS_PIN_FLAG)
#define _spi_get_ss_pin_bit(spi) _bit_get(spi->IRSP, SPI_SS_PIN_DATA_BIT)
#define _spi_set_sspin_assignment(spi, a) _reg_modify(spi->IRSP, SPI_SS_PIN_ASSIGNMENT_SEL_MASK, a)

// TX FIFO status register
#define _spi_get_tx_fifo_next_pointer(spi) (spi->TXFSR >> SPI_TX_FIFO_NEXT_POINTER_SHIFT_MASK)
#define _spi_get_tx_fifo_data_counter(spi) (spi->TXFSR & 0x0f)
#define _spi_get_rx_fifo_next_pointer(spi) (spi->RXFSR >> SPI_RX_FIFO_NEXT_POINTER_SHIFT_MASK)
#define _spi_get_rx_fifo_data_counter(spi) (spi->RXFSR & 0x0f)

// SPI 获取标志
#define _spi_get_flag_finish(spi) _bit_get(spi->SR, SPI_FLAG_FINISH)
#define _spi_get_flag_frame_lost(spi) _bit_get(spi->SR, SPI_FLAG_FRAME_LOST)
#define _spi_get_flag_transmission_end(spi) _bit_get(spi->SR, SPI_FLAG_TRANSMISSION_END)
#define _spi_get_flag_mode_fault(spi) _bit_get(spi->SR, SPI_FLAG_MODE_FAULT)
#define _spi_get_flag_tx_fifo_full(spi) _bit_get(spi->SR, SPI_FLAG_TX_FIFO_FULL)
#define _spi_get_flag_tx_fifo_empty(spi) _bit_get(spi->SR, SPI_FLAG_TX_FIFO_EMPTY)
#define _spi_get_flag_rx_fifo_full(spi) _bit_get(spi->SR, SPI_FLAG_RX_FIFO_FULL)
#define _spi_get_flag_rx_fifo_empty(spi) _bit_get(spi->SR, SPI_FLAG_RX_FIFO_EMPTY)
#define _spi_get_flag_rx_fifo_service(spi) _bit_get(spi->SR, SPI_FLAG_RX_FIFO_SERVICE)
#define _spi_get_flag_rx_fifo_underflow(spi) _bit_get(spi->SR, SPI_FLAG_RX_FIFO_UNDEFLOW)
#define _spi_get_flag_rx_fifo_overflow(spi) _bit_get(spi->SR, SPI_FLAG_RX_FIFO_OVERFLOW)
#define _spi_get_flag_rx_fifo_timeout(spi) _bit_get(spi->SR, SPI_FLAG_RX_FIFO_TIMEOUT)
#define _spi_get_flag_tx_fifo_service(spi) _bit_get(spi->SR, SPI_FLAG_TX_FIFO_SERVICE)
#define _spi_get_flag_tx_fifo_underflow(spi) _bit_get(spi->SR, SPI_FLAG_TX_FIFO_UNDERFLOW)
#define _spi_get_flag_tx_fifo_overflow(spi) _bit_get(spi->SR, SPI_FLAG_TX_FIFO_OVERFLOW)
#define _spi_get_flag_tx_fifo_timeout(spi) _bit_get(spi->SR, SPI_FLAG_TX_FIFO_TIMEOUT)
#define _spi_clr_flag_frame_lost(spi) _bit_set(spi->SR, SPI_FLAG_FRAME_LOST)
#define _spi_clr_flag_transmission_end(spi) _bit_set(spi->SR, SPI_FLAG_TRANSMISSION_END)
#define _spi_clr_flag_rx_fifo_underflow(spi) _bit_set(spi->SR, SPI_FLAG_RX_FIFO_UNDEFLOW)
#define _spi_clr_flag_rx_fifo_overflow(spi) _bit_set(spi->SR, SPI_FLAG_RX_FIFO_OVERFLOW)
#define _spi_clr_flag_rx_fifo_timeout(spi) _bit_set(spi->SR, SPI_FLAG_RX_FIFO_TIMEOUT)
#define _spi_clr_flag_tx_fifo_underflow(spi) _bit_set(spi->SR, SPI_FLAG_TX_FIFO_UNDERFLOW)
#define _spi_clr_flag_tx_fifo_overflow(spi) _bit_set(spi->SR, SPI_FLAG_TX_FIFO_OVERFLOW)
#define _spi_clr_flag_tx_fifo_timeout(spi) _bit_set(spi->SR, SPI_FLAG_TX_FIFO_TIMEOUT)

// interrupt control register
#define _spi_en_mode_fault_it(spi) _bit_set(spi->ICR, SPI_EN_MODE_FAULT_IT)
#define _spi_dis_mode_fault_it(spi) _bit_clr(spi->ICR, SPI_EN_MODE_FAULT_IT)
#define _spi_en_frame_lost_it(spi) _bit_set(spi->ICR, SPI_EN_FRAME_LOST_IT)
#define _spi_dis_frame_lost_it(spi) _bit_clr(spi->ICR, SPI_EN_FRAME_LOST_IT)

// DMA control register
#define _spi_en_tx_dma(spi) _bit_set(spi->DMACR, SPI_EN_TX_DMA)
#define _spi_dis_tx_dma(spi) _bit_clr(spi->DMACR, SPI_EN_TX_DMA)
#define _spi_get_tx_dma(spi) _bit_get(spi->DMACR, SPI_EN_TX_DMA)
#define _spi_en_rx_dma(spi) _bit_set(spi->DMACR, SPI_EN_RX_DMA)
#define _spi_dis_rx_dma(spi) _bit_clr(spi->DMACR, SPI_EN_RX_DMA)
#define _spi_get_rx_dma(spi) _bit_get(spi->DMACR, SPI_EN_RX_DMA)
/**
 * @brief SPI 模块标志索引枚举定义
 *
 */
typedef enum
{
    SPI_FLAG_INDEX_RXFEMP = 0,
    SPI_FLAG_INDEX_RXFFULL,
    SPI_FLAG_INDEX_XFEMP,
    SPI_FLAG_INDEX_TXFFFUL,
    SPI_FLAG_INDEX_MODE,
    SPI_FLAG_INDEX_EOTF,
    SPI_FLAG_INDEX_FLOST,
    SPI_FLAG_INDEX_SPIF,
    SPI_FLAG_INDEX_RXFSER,
    SPI_FLAG_INDEX_RXFUDF,
    SPI_FLAG_INDEX_RXFOVFM,
    SPI_FLAG_INDEX_RXFTO,
    SPI_FLAG_INDEX_TXFSER,
    SPI_FLAG_INDEX_TXFUDF,
    SPI_FLAG_INDEX_TXFOVFM,
    SPI_FLAG_INDEX_TXFTO,
} spi_flagindex_t;

/**
 * @brief SPI SS中断触发方式枚举定义
 */
typedef enum
{
    SPI_SS_ASSIGNMENT_SEL_LEVEL = 0,
    SPI_SS_ASSIGNMENT_SEL_RISING_EDGE,
    SPI_SS_ASSIGNMENT_SEL_FALLING_EDGE,
    SPI_SS_ASSIGNMENT_SEL_BOTH_EDGE,
} spi_sssssignmentsel_t;
/**
 * @brief SPI 模块FIFO控制枚举定义
 */
typedef struct
{
    uint8_t tx_fifo_en;
    uint8_t rx_fifo_en;
    uint8_t tx_fifo_threshold;
    uint8_t rx_fifo_threshold;
    uint8_t tx_fifo_timeout_cnt;
    uint8_t rx_fifo_timeout_cnt;
} spi_fifoinit_t;

/**
 * @brief SPI 模块初始化结构体定义.
 */
typedef struct
{
    uint8_t Function;
    uint8_t OutputMode;
    uint8_t Mode;
    uint8_t Cpol;
    uint8_t Cpha;
    uint8_t Ssoe;
    uint8_t FirstBit;
    uint8_t GuardTime;
    uint8_t Spc0;
    uint8_t DozeMode;
    uint8_t BaudratePreselectionBits;
    uint8_t BaudrateBits;
    uint8_t GuradTimeEn;
    uint8_t SlaveHighSpeedEn;
    uint8_t ReducedDriveCap;
    uint8_t Pullup;
    spi_fifoinit_t FifoInit;
} spi_init_t;
// 函数声明
void drv_spi_deinit(reg_spi_t *pspi);
status_t drv_spi_init(reg_spi_t *pspi, volatile spi_init_t *init);
void drv_spi_en(reg_spi_t *pspi);
void drv_spi_dis(reg_spi_t *pspi);
void drv_spi_cmd(reg_spi_t *pspi, functionalstate_t newstate);
void drv_spi_iten(reg_spi_t *pspi);
status_t drv_spi_transmitbyte(reg_spi_t *pspi, uint8_t tosend);
status_t drv_spi_receivebyte(reg_spi_t *pspi, uint8_t *rx);
status_t drv_spi_transmitbytes(reg_spi_t *pspi,uint8_t *pbuf,uint32_t size);
status_t drv_spi_receivebytes(reg_spi_t *pspi, uint8_t *pbuf, uint32_t len);
status_t drv_spi_slavereceivebyte(reg_spi_t *pspi,uint8_t *rx,uint32_t timeout);
status_t drv_spi_slavetransmitbyte(reg_spi_t *pspi,uint8_t tosend, uint32_t timeout);
status_t drv_spi_slavetransmitbytes(reg_spi_t *pspi,uint8_t *pbuf, uint32_t len, uint32_t timeout);
status_t drv_spi_slavereceivebytes(reg_spi_t *pspi,uint8_t *pbuf,uint32_t len,uint32_t timeout);
void drv_spi_setdr(reg_spi_t *pspi, uint8_t val);
void drv_spi_getdr(reg_spi_t *pspi, uint8_t *pval);
status_t drv_spi_getflag(reg_spi_t *pspi, spi_flagindex_t flagIndex, flagstatus_t *pflag);
status_t drv_spi_clrflag(reg_spi_t *pspi, spi_flagindex_t flagIndex);
status_t drv_spi_waitonflagtimeout(reg_spi_t *pspi,spi_flagindex_t index,flagstatus_t status,uint32_t timeout);
status_t drv_spi_gpioinit(reg_spi_t *pspi, gpio_init_t *init);
void drv_spi_gpiodeinit(reg_spi_t *pspi, uint8_t pin);
void drv_spi_writepin(reg_spi_t *pspi, uint8_t pin, gpio_pinstate_t state);
gpio_pinstate_t drv_spi_readpin(reg_spi_t *pspi, uint8_t pin);
void drv_spi_set_frame_size(reg_spi_t *pspi, uint8_t value);
void drv_spi_clr_rx_fifo(volatile reg_spi_t *hspi);
void drv_spi_clr_tx_fifo(volatile reg_spi_t *hspi);
void drv_spi_dis_it(volatile reg_spi_t *hspi);
void drv_spi_en_it(volatile reg_spi_t *hspi);
void drv_spi_en_tx_dma(volatile reg_spi_t *hspi);
void drv_spi_en_rx_dma(volatile reg_spi_t *hspi);

#ifdef __cplusplus
}
#endif

#endif
