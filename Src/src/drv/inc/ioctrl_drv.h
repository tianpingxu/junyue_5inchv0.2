/**
 * @file ioctrl_drv.h
 * @author Product Application Department
 * @brief  IOCTRL 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __IOCTRL_DRV_H
#define __IOCTRL_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "ioctrl_reg.h"

// 全局变量定义

// SPICR
#define _ioctrl_spi1_ss_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SS1_PS)
#define _ioctrl_spi1_ss_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SS1_PS)
#define _ioctrl_spi1_sck_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SCK1_PS)
#define _ioctrl_spi1_sck_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SCK1_PS)
#define _ioctrl_spi1_miso_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MISO1_PS)
#define _ioctrl_spi1_miso_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MISO1_PS)
#define _ioctrl_spi1_mosi_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MOSI1_PS)
#define _ioctrl_spi1_mosi_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MOSI1_PS)
#define _ioctrl_spi1_ss_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SS1_IE)
#define _ioctrl_spi1_ss_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SS1_IE)
#define _ioctrl_spi1_sck_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SCK1_IE)
#define _ioctrl_spi1_sck_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SCK1_IE)
#define _ioctrl_spi1_miso_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MISO1_IE)
#define _ioctrl_spi1_miso_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MISO1_IE)
#define _ioctrl_spi1_mosi_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MOSI1_IE)
#define _ioctrl_spi1_mosi_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MOSI1_IE)
#define _ioctrl_spi2_ss_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SS2_PS)
#define _ioctrl_spi2_ss_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SS2_PS)
#define _ioctrl_spi2_sck_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SCK2_PS)
#define _ioctrl_spi2_sck_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SCK2_PS)
#define _ioctrl_spi2_miso_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MISO2_PS)
#define _ioctrl_spi2_miso_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MISO2_PS)
#define _ioctrl_spi2_mosi_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MOSI2_PS)
#define _ioctrl_spi2_mosi_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MOSI2_PS)
#define _ioctrl_spi2_ss_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SS2_IE)
#define _ioctrl_spi2_ss_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SS2_IE)
#define _ioctrl_spi2_sck_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SCK2_IE)
#define _ioctrl_spi2_sck_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SCK2_IE)
#define _ioctrl_spi2_miso_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MISO2_IE)
#define _ioctrl_spi2_miso_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MISO2_IE)
#define _ioctrl_spi2_mosi_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MOSI2_IE)
#define _ioctrl_spi2_mosi_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MOSI2_IE)
#define _ioctrl_spi3_ss_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SS3_PS)
#define _ioctrl_spi3_ss_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SS3_PS)
#define _ioctrl_spi3_sck_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SCK3_PS)
#define _ioctrl_spi3_sck_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SCK3_PS)
#define _ioctrl_spi3_miso_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MISO3_PS)
#define _ioctrl_spi3_miso_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MISO3_PS)
#define _ioctrl_spi3_mosi_pull_down _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MOSI3_PS)
#define _ioctrl_spi3_mosi_pull_up _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MOSI3_PS)
#define _ioctrl_spi3_ss_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SS3_IE)
#define _ioctrl_spi3_ss_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SS3_IE)
#define _ioctrl_spi3_sck_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_SCK3_IE)
#define _ioctrl_spi3_sck_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_SCK3_IE)
#define _ioctrl_spi3_miso_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MISO3_IE)
#define _ioctrl_spi3_miso_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MISO3_IE)
#define _ioctrl_spi3_mosi_input_dis _bit_clr(IOCTRL->SPICR, IOCTRL_SPICR_MOSI3_IE)
#define _ioctrl_spi3_mosi_input_en _bit_set(IOCTRL->SPICR, IOCTRL_SPICR_MOSI3_IE)

// I2CCR
#define _ioctrl_i2c_ds_2ma _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_DS1_DS0)
#define _ioctrl_i2c_ds_4ma _reg_modify(IOCTRL->I2CCR, ~IOCTRL_I2CCR_DS1_DS0, IOCTRL_I2CCR_DS1)
#define _ioctrl_i2c_ds_8ma _reg_modify(IOCTRL->I2CCR, ~IOCTRL_I2CCR_DS1_DS0, IOCTRL_I2CCR_DS0)
#define _ioctrl_i2c_ds_12ma _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_DS1_DS0)
#define _ioctrl_i2c_slew_fast _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SR)
#define _ioctrl_i2c_slew_slow _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SR)
#define _ioctrl_i2c_input_cmos _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_IS)
#define _ioctrl_i2c_input_schmitt _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_IS)
#define _ioctrl_i2c1_scl_pull_down _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL1_PS)
#define _ioctrl_i2c1_scl_pull_up _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL1_PS)
#define _ioctrl_i2c1_sda_pull_down _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA1_PS)
#define _ioctrl_i2c1_sda_pull_up _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA1_PS)
#define _ioctrl_i2c1_scl_input_dis _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL1_IE)
#define _ioctrl_i2c1_scl_input_en _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL1_IE)
#define _ioctrl_i2c1_sda_input_dis _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA1_IE)
#define _ioctrl_i2c1_sda_input_en _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA1_IE)
#define _ioctrl_i2c2_scl_pull_down _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL2_PS)
#define _ioctrl_i2c2_scl_pull_up _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL2_PS)
#define _ioctrl_i2c2_sda_pull_down _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA2_PS)
#define _ioctrl_i2c2_sda_pull_up _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA2_PS)
#define _ioctrl_i2c2_scl_input_dis _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL2_IE)
#define _ioctrl_i2c2_scl_input_en _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SCL2_IE)
#define _ioctrl_i2c2_sda_input_dis _bit_clr(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA2_IE)
#define _ioctrl_i2c2_sda_input_en _bit_set(IOCTRL->I2CCR, IOCTRL_I2CCR_SDA2_IE)

// UARTCR
#define _ioctrl_uart_ds_2ma _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_DS1_DS0)
#define _ioctrl_uart_ds_4ma _reg_modify(IOCTRL->UARTCR, ~IOCTRL_UARTCR_DS1_DS0, IOCTRL_UARTCR_DS1)
#define _ioctrl_uart_ds_8ma _reg_modify(IOCTRL->UARTCR, ~IOCTRL_UARTCR_DS1_DS0, IOCTRL_UARTCR_DS0)
#define _ioctrl_uart_ds_12ma _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_DS1_DS0)
#define _ioctrl_uart_slew_fast _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_SR)
#define _ioctrl_uart_slew_slow _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_SR)
#define _ioctrl_uart_input_cmos _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_IS)
#define _ioctrl_uart_input_schmitt _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_IS)
#define _ioctrl_uart1_txd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD1_PS)
#define _ioctrl_uart1_txd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD1_PS)
#define _ioctrl_uart1_rxd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD1_PS)
#define _ioctrl_uart1_rxd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD1_PS)
#define _ioctrl_uart1_cts_pull_down_dis _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_CTS1_PUE)
#define _ioctrl_uart1_cts_pull_down_en _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_CTS1_PUE)
#define _ioctrl_uart2_txd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD2_PS)
#define _ioctrl_uart2_txd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD2_PS)
#define _ioctrl_uart2_rxd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD2_PS)
#define _ioctrl_uart2_rxd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD2_PS)
#define _ioctrl_uart2_cts_pull_down_dis _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_CTS2_PUE)
#define _ioctrl_uart2_cts_pull_down_en _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_CTS2_PUE)
#define _ioctrl_uart3_txd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD3_PS)
#define _ioctrl_uart3_txd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD3_PS)
#define _ioctrl_uart3_rxd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD3_PS)
#define _ioctrl_uart3_rxd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD3_PS)
#define _ioctrl_uart3_cts_pull_down_dis _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_CTS3_PUE)
#define _ioctrl_uart3_cts_pull_down_en _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_CTS3_PUE)
#define _ioctrl_uart4_txd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD4_PS)
#define _ioctrl_uart4_txd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD4_PS)
#define _ioctrl_uart4_rxd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD4_PS)
#define _ioctrl_uart4_rxd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD4_PS)
#define _ioctrl_uart5_txd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD5_PS)
#define _ioctrl_uart5_txd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD5_PS)
#define _ioctrl_uart5_rxd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD5_PS)
#define _ioctrl_uart5_rxd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD5_PS)
#define _ioctrl_uart6_txd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD6_PS)
#define _ioctrl_uart6_txd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_TXD6_PS)
#define _ioctrl_uart6_rxd_pull_down _bit_clr(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD6_PS)
#define _ioctrl_uart6_rxd_pull_up _bit_set(IOCTRL->UARTCR, IOCTRL_UARTCR_RXD6_PS)

// EPORT0CR
#define _ioctrl_eport0_pin0_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN0_IE)
#define _ioctrl_eport0_pin0_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN0_IE)
#define _ioctrl_eport0_pin1_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN1_IE)
#define _ioctrl_eport0_pin1_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN1_IE)
#define _ioctrl_eport0_pin2_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN2_IE)
#define _ioctrl_eport0_pin2_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN2_IE)
#define _ioctrl_eport0_pin3_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN3_IE)
#define _ioctrl_eport0_pin3_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN3_IE)
#define _ioctrl_eport0_pin4_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN4_IE)
#define _ioctrl_eport0_pin4_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN4_IE)
#define _ioctrl_eport0_pin5_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN5_IE)
#define _ioctrl_eport0_pin5_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN5_IE)
#define _ioctrl_eport0_pin6_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN6_IE)
#define _ioctrl_eport0_pin6_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN6_IE)
#define _ioctrl_eport0_pin7_input_dis _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN7_IE)
#define _ioctrl_eport0_pin7_input_en _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN7_IE)
#define _ioctrl_eport0_pin0_pull_down _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN0_PS)
#define _ioctrl_eport0_pin0_pull_up _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN0_PS)
#define _ioctrl_eport0_pin1_pull_down _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN1_PS)
#define _ioctrl_eport0_pin1_pull_up _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN1_PS)
#define _ioctrl_eport0_pin2_pull_down _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN2_PS)
#define _ioctrl_eport0_pin2_pull_up _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN2_PS)
#define _ioctrl_eport0_pin3_pull_down _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN3_PS)
#define _ioctrl_eport0_pin3_pull_up _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN3_PS)
#define _ioctrl_eport0_pin4_pull_down _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN4_PS)
#define _ioctrl_eport0_pin4_pull_up _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN4_PS)
#define _ioctrl_eport0_pin5_pull_down _bit_clr(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN5_PS)
#define _ioctrl_eport0_pin5_pull_up _bit_set(IOCTRL->EPORT0CR, IOCTRL_EPORT0CR_PIN5_PS)

// EPORT1CR
#define _ioctrl_eport1_ds_2ma _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport1_ds_4ma _reg_modify(IOCTRL->EPORT1CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport1_ds_8ma _reg_modify(IOCTRL->EPORT1CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport1_ds_12ma _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport1_slew_fast _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_SR)
#define _ioctrl_eport1_slew_slow _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_SR)
#define _ioctrl_eport1_input_cmos _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_IS)
#define _ioctrl_eport1_input_schmitt _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_IS)
#define _ioctrl_eport1_pin0_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN0_IE)
#define _ioctrl_eport1_pin0_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN0_IE)
#define _ioctrl_eport1_pin1_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN1_IE)
#define _ioctrl_eport1_pin1_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN1_IE)
#define _ioctrl_eport1_pin2_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN2_IE)
#define _ioctrl_eport1_pin2_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN2_IE)
#define _ioctrl_eport1_pin3_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN3_IE)
#define _ioctrl_eport1_pin3_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN3_IE)
#define _ioctrl_eport1_pin4_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN4_IE)
#define _ioctrl_eport1_pin4_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN4_IE)
#define _ioctrl_eport1_pin5_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN5_IE)
#define _ioctrl_eport1_pin5_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN5_IE)
#define _ioctrl_eport1_pin6_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN6_IE)
#define _ioctrl_eport1_pin6_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN6_IE)
#define _ioctrl_eport1_pin7_input_dis _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN7_IE)
#define _ioctrl_eport1_pin7_input_en _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN7_IE)
#define _ioctrl_eport1_pin4_pull_down _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN4_PS)
#define _ioctrl_eport1_pin4_pull_up _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN4_PS)
#define _ioctrl_eport1_pin5_pull_down _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN5_PS)
#define _ioctrl_eport1_pin5_pull_up _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN5_PS)
#define _ioctrl_eport1_pin6_pull_down _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN6_PS)
#define _ioctrl_eport1_pin6_pull_up _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN6_PS)
#define _ioctrl_eport1_pin7_pull_down _bit_clr(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN7_PS)
#define _ioctrl_eport1_pin7_pull_up _bit_set(IOCTRL->EPORT1CR, IOCTRL_EPORT1CR_PIN7_PS)

// SWAPCR
#define _ioctrl_swapcr_swap0_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT0)
#define _ioctrl_swapcr_swap0_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT0)
#define _ioctrl_swapcr_swap1_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT1)
#define _ioctrl_swapcr_swap1_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT1)
#define _ioctrl_swapcr_swap2_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT2)
#define _ioctrl_swapcr_swap2_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT2)
#define _ioctrl_swapcr_swap3_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT3)
#define _ioctrl_swapcr_swap3_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT3)
#define _ioctrl_swapcr_swap4_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT4)
#define _ioctrl_swapcr_swap4_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT4)
#define _ioctrl_swapcr_swap5_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT5)
#define _ioctrl_swapcr_swap5_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT5)
#define _ioctrl_swapcr_swap6_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT6)
#define _ioctrl_swapcr_swap6_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT6)
#define _ioctrl_swapcr_swap7_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT7)
#define _ioctrl_swapcr_swap7_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT7)
#define _ioctrl_swapcr_swap8_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT8)
#define _ioctrl_swapcr_swap8_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT8)
#define _ioctrl_swapcr_swap9_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT9)
#define _ioctrl_swapcr_swap9_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT9)
#define _ioctrl_swapcr_swap10_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT10)
#define _ioctrl_swapcr_swap10_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT10)
#define _ioctrl_swapcr_swap11_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT11)
#define _ioctrl_swapcr_swap11_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT11)
#define _ioctrl_swapcr_swap12_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT12)
#define _ioctrl_swapcr_swap12_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT12)
#define _ioctrl_swapcr_swap13_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT13)
#define _ioctrl_swapcr_swap13_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT13)
#define _ioctrl_swapcr_swap14_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT14)
#define _ioctrl_swapcr_swap14_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT14)
#define _ioctrl_swapcr_swap15_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT15)
#define _ioctrl_swapcr_swap15_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT15)
#define _ioctrl_swapcr_swap16_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT16)
#define _ioctrl_swapcr_swap16_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT16)
#define _ioctrl_swapcr_swap17_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT17)
#define _ioctrl_swapcr_swap17_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT17)
#define _ioctrl_swapcr_swap18_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT18)
#define _ioctrl_swapcr_swap18_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT18)
#define _ioctrl_swapcr_swap19_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT19)
#define _ioctrl_swapcr_swap19_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT19)
#define _ioctrl_swapcr_swap20_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT20)
#define _ioctrl_swapcr_swap20_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT20)
#define _ioctrl_swapcr_swap21_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT21)
#define _ioctrl_swapcr_swap21_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT21)
#define _ioctrl_swapcr_swap22_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT22)
#define _ioctrl_swapcr_swap22_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT22)
#define _ioctrl_swapcr_swap23_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT23)
#define _ioctrl_swapcr_swap23_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT23)
#define _ioctrl_swapcr_swap24_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT24)
#define _ioctrl_swapcr_swap24_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT24)
#define _ioctrl_swapcr_swap25_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT25)
#define _ioctrl_swapcr_swap25_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT25)
#define _ioctrl_swapcr_swap26_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT26)
#define _ioctrl_swapcr_swap26_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT26)
#define _ioctrl_swapcr_swap27_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT27)
#define _ioctrl_swapcr_swap27_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT27)
#define _ioctrl_swapcr_swap28_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT28)
#define _ioctrl_swapcr_swap28_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT28)
#define _ioctrl_swapcr_swap29_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT29)
#define _ioctrl_swapcr_swap29_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT29)
#define _ioctrl_swapcr_swap30_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT30)
#define _ioctrl_swapcr_swap30_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT30)
#define _ioctrl_swapcr_swap31_clr _bit_clr(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT31)
#define _ioctrl_swapcr_swap31_set _bit_set(IOCTRL->SWAPCR, IOCTRL_SWAPCR_SWAP_BIT31)

// SPIM1CR
#define _ioctrl_spim1_d_ds_2ma _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D_DS1_DS0)
#define _ioctrl_spim1_d_ds_4ma _reg_modify(IOCTRL->SPIM1CR, ~IOCTRL_SPIM1CR_D_DS1_DS0, IOCTRL_SPIM1CR_D_DS1)
#define _ioctrl_spim1_d_ds_8ma _reg_modify(IOCTRL->SPIM1CR, ~IOCTRL_SPIM1CR_D_DS1_DS0, IOCTRL_SPIM1CR_D_DS0)
#define _ioctrl_spim1_d_ds_12ma _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D_DS1_DS0)
#define _ioctrl_spim1_d_slew_fast _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D_SR)
#define _ioctrl_spim1_d_slew_slow _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D_SR)
#define _ioctrl_spim1_d_input_cmos _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D_IS)
#define _ioctrl_spim1_d_input_schmitt _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D_IS)

#define _ioctrl_spim1_pull_up_down_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_PUE)
#define _ioctrl_spim1_pull_up_down_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_PUE)
#define _ioctrl_spim1_output_cmos _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_ODE)
#define _ioctrl_spim1_output_open_d _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_ODE)

#define _ioctrl_spim1_sck_ds_2ma _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_DS1_DS0)
#define _ioctrl_spim1_sck_ds_4ma _reg_modify(IOCTRL->SPIM1CR, ~IOCTRL_SPIM1CR_SCK_DS1_DS0, IOCTRL_SPIM1CR_SCK_DS1)
#define _ioctrl_spim1_sck_ds_8ma _reg_modify(IOCTRL->SPIM1CR, ~IOCTRL_SPIM1CR_SCK_DS1_DS0, IOCTRL_SPIM1CR_SCK_DS0)
#define _ioctrl_spim1_sck_ds_12ma _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_DS1_DS0)
#define _ioctrl_spim1_sck_slew_fast _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_SR)
#define _ioctrl_spim1_sck_slew_slow _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_SR)
#define _ioctrl_spim1_sck_input_cmos _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_IS)
#define _ioctrl_spim1_sck_input_schmitt _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_IS)

#define _ioctrl_spim1_ss_ds_2ma _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_DS1_DS0)
#define _ioctrl_spim1_ss_ds_4ma _reg_modify(IOCTRL->SPIM1CR, ~IOCTRL_SPIM1CR_SS_DS1_DS0, IOCTRL_SPIM1CR_SS_DS1)
#define _ioctrl_spim1_ss_ds_8ma _reg_modify(IOCTRL->SPIM1CR, ~IOCTRL_SPIM1CR_SS_DS1_DS0, IOCTRL_SPIM1CR_SS_DS0)
#define _ioctrl_spim1_ss_ds_12ma _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_DS1_DS0)
#define _ioctrl_spim1_ss_slew_fast _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_SR)
#define _ioctrl_spim1_ss_slew_slow _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_SR)
#define _ioctrl_spim1_ss_input_cmos _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_IS)
#define _ioctrl_spim1_ss_input_schmitt _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_IS)

#define _ioctrl_spim1_ss_pull_down _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_PS)
#define _ioctrl_spim1_ss_pull_up _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_PS)
#define _ioctrl_spim1_sck_pull_down _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_PS)
#define _ioctrl_spim1_sck_pull_up _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_PS)
#define _ioctrl_spim1_d0_pull_down _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D0_PS)
#define _ioctrl_spim1_d0_pull_up _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D0_PS)
#define _ioctrl_spim1_d1_pull_down _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D1_PS)
#define _ioctrl_spim1_d1_pull_up _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D1_PS)
#define _ioctrl_spim1_d2_pull_down _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D2_PS)
#define _ioctrl_spim1_d2_pull_up _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D2_PS)
#define _ioctrl_spim1_d3_pull_down _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D3_PS)
#define _ioctrl_spim1_d3_pull_up _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D3_PS)
#define _ioctrl_spim1_ss_input_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_IE)
#define _ioctrl_spim1_ss_input_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SS_IE)
#define _ioctrl_spim1_sck_input_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_IE)
#define _ioctrl_spim1_sck_input_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_SCK_IE)
#define _ioctrl_spim1_d0_input_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D0_IE)
#define _ioctrl_spim1_d0_input_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D0_IE)
#define _ioctrl_spim1_d1_input_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D1_IE)
#define _ioctrl_spim1_d1_input_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D1_IE)
#define _ioctrl_spim1_d2_input_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D2_IE)
#define _ioctrl_spim1_d2_input_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D2_IE)
#define _ioctrl_spim1_d3_input_dis _bit_clr(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D3_IE)
#define _ioctrl_spim1_d3_input_en _bit_set(IOCTRL->SPIM1CR, IOCTRL_SPIM1CR_D3_IE)

// SPIM2CR
#define _ioctrl_spim2_d_ds_2ma _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D_DS1_DS0)
#define _ioctrl_spim2_d_ds_4ma _reg_modify(IOCTRL->SPIM2CR, ~IOCTRL_SPIM2CR_D_DS1_DS0, IOCTRL_SPIM2CR_D_DS1)
#define _ioctrl_spim2_d_ds_8ma _reg_modify(IOCTRL->SPIM2CR, ~IOCTRL_SPIM2CR_D_DS1_DS0, IOCTRL_SPIM2CR_D_DS0)
#define _ioctrl_spim2_d_ds_12ma _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D_DS1_DS0)
#define _ioctrl_spim2_d_slew_fast _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D_SR)
#define _ioctrl_spim2_d_slew_slow _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D_SR)
#define _ioctrl_spim2_d_input_cmos _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D_IS)
#define _ioctrl_spim2_d_input_schmitt _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D_IS)

#define _ioctrl_spim2_pull_up_down_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_PUE)
#define _ioctrl_spim2_pull_up_down_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_PUE)
#define _ioctrl_spim2_output_cmos _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_ODE)
#define _ioctrl_spim2_output_open_d _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_ODE)

#define _ioctrl_spim2_sck_ds_2ma _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_DS1_DS0)
#define _ioctrl_spim2_sck_ds_4ma _reg_modify(IOCTRL->SPIM2CR, ~IOCTRL_SPIM2CR_SCK_DS1_DS0, IOCTRL_SPIM2CR_SCK_DS1)
#define _ioctrl_spim2_sck_ds_8ma _reg_modify(IOCTRL->SPIM2CR, ~IOCTRL_SPIM2CR_SCK_DS1_DS0, IOCTRL_SPIM2CR_SCK_DS0)
#define _ioctrl_spim2_sck_ds_12ma _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_DS1_DS0)
#define _ioctrl_spim2_sck_slew_fast _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_SR)
#define _ioctrl_spim2_sck_slew_slow _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_SR)
#define _ioctrl_spim2_sck_input_cmos _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_IS)
#define _ioctrl_spim2_sck_input_schmitt _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_IS)

#define _ioctrl_spim2_ss_ds_2ma _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_DS1_DS0)
#define _ioctrl_spim2_ss_ds_4ma _reg_modify(IOCTRL->SPIM2CR, ~IOCTRL_SPIM2CR_SS_DS1_DS0, IOCTRL_SPIM2CR_SS_DS1)
#define _ioctrl_spim2_ss_ds_8ma _reg_modify(IOCTRL->SPIM2CR, ~IOCTRL_SPIM2CR_SS_DS1_DS0, IOCTRL_SPIM2CR_SS_DS0)
#define _ioctrl_spim2_ss_ds_12ma _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_DS1_DS0)
#define _ioctrl_spim2_ss_slew_fast _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_SR)
#define _ioctrl_spim2_ss_slew_slow _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_SR)
#define _ioctrl_spim2_ss_input_cmos _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_IS)
#define _ioctrl_spim2_ss_input_schmitt _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_IS)

#define _ioctrl_spim2_ss_pull_down _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_PS)
#define _ioctrl_spim2_ss_pull_up _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_PS)
#define _ioctrl_spim2_sck_pull_down _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_PS)
#define _ioctrl_spim2_sck_pull_up _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_PS)
#define _ioctrl_spim2_d0_pull_down _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D0_PS)
#define _ioctrl_spim2_d0_pull_up _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D0_PS)
#define _ioctrl_spim2_d1_pull_down _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D1_PS)
#define _ioctrl_spim2_d1_pull_up _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D1_PS)
#define _ioctrl_spim2_d2_pull_down _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D2_PS)
#define _ioctrl_spim2_d2_pull_up _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D2_PS)
#define _ioctrl_spim2_d3_pull_down _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D3_PS)
#define _ioctrl_spim2_d3_pull_up _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D3_PS)
#define _ioctrl_spim2_ss_input_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_IE)
#define _ioctrl_spim2_ss_input_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SS_IE)
#define _ioctrl_spim2_sck_input_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_IE)
#define _ioctrl_spim2_sck_input_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_SCK_IE)
#define _ioctrl_spim2_d0_input_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D0_IE)
#define _ioctrl_spim2_d0_input_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D0_IE)
#define _ioctrl_spim2_d1_input_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D1_IE)
#define _ioctrl_spim2_d1_input_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D1_IE)
#define _ioctrl_spim2_d2_input_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D2_IE)
#define _ioctrl_spim2_d2_input_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D2_IE)
#define _ioctrl_spim2_d3_input_dis _bit_clr(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D3_IE)
#define _ioctrl_spim2_d3_input_en _bit_set(IOCTRL->SPIM2CR, IOCTRL_SPIM2CR_D3_IE)
#define _ioctrl_spim2_input_dis(bits) _bit_clr(IOCTRL->SPIM2CR, (bits << IOCTRL_SPIM2CR_IE))
#define _ioctrl_spim2_input_en(bits) _bit_set(IOCTRL->SPIM2CR, (bits << IOCTRL_SPIM2CR_IE))
#define _ioctrl_spim2_pull_down(bits) _bit_clr(IOCTRL->SPIM2CR, (bits << IOCTRL_SPIM2CR_PS))
#define _ioctrl_spim2_pull_up(bits) _bit_set(IOCTRL->SPIM2CR, (bits << IOCTRL_SPIM2CR_PS))

// SPIM3CR
#define _ioctrl_spim3_d_ds_2ma _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D_DS1_DS0)
#define _ioctrl_spim3_d_ds_4ma _reg_modify(IOCTRL->SPIM3CR, ~IOCTRL_SPIM3CR_D_DS1_DS0, IOCTRL_SPIM3CR_D_DS1)
#define _ioctrl_spim3_d_ds_8ma _reg_modify(IOCTRL->SPIM3CR, ~IOCTRL_SPIM3CR_D_DS1_DS0, IOCTRL_SPIM3CR_D_DS0)
#define _ioctrl_spim3_d_ds_12ma _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D_DS1_DS0)
#define _ioctrl_spim3_d_slew_fast _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D_SR)
#define _ioctrl_spim3_d_slew_slow _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D_SR)
#define _ioctrl_spim3_d_input_cmos _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D_IS)
#define _ioctrl_spim3_d_input_schmitt _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D_IS)

#define _ioctrl_spim3_pull_up_down_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_PUE)
#define _ioctrl_spim3_pull_up_down_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_PUE)
#define _ioctrl_spim3_output_cmos _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_ODE)
#define _ioctrl_spim3_output_open_d _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_ODE)

#define _ioctrl_spim3_sck_ds_2ma _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_DS1_DS0)
#define _ioctrl_spim3_sck_ds_4ma _reg_modify(IOCTRL->SPIM3CR, ~IOCTRL_SPIM3CR_SCK_DS1_DS0, IOCTRL_SPIM3CR_SCK_DS1)
#define _ioctrl_spim3_sck_ds_8ma _reg_modify(IOCTRL->SPIM3CR, ~IOCTRL_SPIM3CR_SCK_DS1_DS0, IOCTRL_SPIM3CR_SCK_DS0)
#define _ioctrl_spim3_sck_ds_12ma _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_DS1_DS0)
#define _ioctrl_spim3_sck_slew_fast _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_SR)
#define _ioctrl_spim3_sck_slew_slow _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_SR)
#define _ioctrl_spim3_sck_input_cmos _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_IS)
#define _ioctrl_spim3_sck_input_schmitt _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_IS)

#define _ioctrl_spim3_ss_ds_2ma _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_DS1_DS0)
#define _ioctrl_spim3_ss_ds_4ma _reg_modify(IOCTRL->SPIM3CR, ~IOCTRL_SPIM3CR_SS_DS1_DS0, IOCTRL_SPIM3CR_SS_DS1)
#define _ioctrl_spim3_ss_ds_8ma _reg_modify(IOCTRL->SPIM3CR, ~IOCTRL_SPIM3CR_SS_DS1_DS0, IOCTRL_SPIM3CR_SS_DS0)
#define _ioctrl_spim3_ss_ds_12ma _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_DS1_DS0)
#define _ioctrl_spim3_ss_slew_fast _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_SR)
#define _ioctrl_spim3_ss_slew_slow _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_SR)
#define _ioctrl_spim3_ss_input_cmos _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_IS)
#define _ioctrl_spim3_ss_input_schmitt _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_IS)

#define _ioctrl_spim3_ss_pull_down _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_PS)
#define _ioctrl_spim3_ss_pull_up _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_PS)
#define _ioctrl_spim3_sck_pull_down _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_PS)
#define _ioctrl_spim3_sck_pull_up _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_PS)
#define _ioctrl_spim3_d0_pull_down _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D0_PS)
#define _ioctrl_spim3_d0_pull_up _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D0_PS)
#define _ioctrl_spim3_d1_pull_down _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D1_PS)
#define _ioctrl_spim3_d1_pull_up _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D1_PS)
#define _ioctrl_spim3_d2_pull_down _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D2_PS)
#define _ioctrl_spim3_d2_pull_up _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D2_PS)
#define _ioctrl_spim3_d3_pull_down _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D3_PS)
#define _ioctrl_spim3_d3_pull_up _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D3_PS)
#define _ioctrl_spim3_ss_input_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_IE)
#define _ioctrl_spim3_ss_input_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SS_IE)
#define _ioctrl_spim3_sck_input_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_IE)
#define _ioctrl_spim3_sck_input_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_SCK_IE)
#define _ioctrl_spim3_d0_input_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D0_IE)
#define _ioctrl_spim3_d0_input_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D0_IE)
#define _ioctrl_spim3_d1_input_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D1_IE)
#define _ioctrl_spim3_d1_input_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D1_IE)
#define _ioctrl_spim3_d2_input_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D2_IE)
#define _ioctrl_spim3_d2_input_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D2_IE)
#define _ioctrl_spim3_d3_input_dis _bit_clr(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D3_IE)
#define _ioctrl_spim3_d3_input_en _bit_set(IOCTRL->SPIM3CR, IOCTRL_SPIM3CR_D3_IE)

// CLCDCR
#define _ioctrl_clcdcr_ds_2ma _bit_clr(IOCTRL->CLCDCR, IOCTRL_CLCDCR_DS1_DS0)
#define _ioctrl_clcdcr_ds_4ma _reg_modify(IOCTRL->CLCDCR, ~IOCTRL_CLCDCR_DS1_DS0, IOCTRL_CLCDCR_DS0)
#define _ioctrl_clcdcr_ds_8ma _reg_modify(IOCTRL->CLCDCR, ~IOCTRL_CLCDCR_DS1_DS0, IOCTRL_CLCDCR_DS1)
#define _ioctrl_clcdcr_ds_12ma _bit_set(IOCTRL->CLCDCR, IOCTRL_CLCDCR_DS1_DS0)
#define _ioctrl_clcdcr_slew_fast _bit_clr(IOCTRL->CLCDCR, IOCTRL_CLCDCR_SR)
#define _ioctrl_clcdcr_slew_slow _bit_set(IOCTRL->CLCDCR, IOCTRL_CLCDCR_SR)
#define _ioctrl_clfp_pull_up _bit_set(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLFP_PS)
#define _ioctrl_clfp_pull_down _bit_clr(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLFP_PS)
#define _ioctrl_clac_pull_up _bit_set(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLAC_PS)
#define _ioctrl_clac_pull_down _bit_clr(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLAC_PS)
#define _ioctrl_clcdclcp_pull_up _bit_set(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLCP_PS)
#define _ioctrl_clcdclcp_pull_down _bit_clr(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLCP_PS)
#define _ioctrl_clcdcllp_pull_up _bit_set(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLLP_PS)
#define _ioctrl_clcdcllp_pull_down _bit_clr(IOCTRL->CLCDCR, IOCTRL_CLCDCR_CLLP_PS)
// CLCDPSCR
#define _ioctrl_clcdd0_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D0_PS)
#define _ioctrl_clcdd0_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D0_PS)
#define _ioctrl_clcdd1_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D1_PS)
#define _ioctrl_clcdd1_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D1_PS)
#define _ioctrl_clcdd2_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D2_PS)
#define _ioctrl_clcdd2_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D2_PS)
#define _ioctrl_clcdd3_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D3_PS)
#define _ioctrl_clcdd3_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D3_PS)
#define _ioctrl_clcdd4_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D4_PS)
#define _ioctrl_clcdd4_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D4_PS)
#define _ioctrl_clcdd5_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D5_PS)
#define _ioctrl_clcdd5_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D5_PS)
#define _ioctrl_clcdd6_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D6_PS)
#define _ioctrl_clcdd6_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D6_PS)
#define _ioctrl_clcdd7_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D7_PS)
#define _ioctrl_clcdd7_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D7_PS)
#define _ioctrl_clcdd8_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D8_PS)
#define _ioctrl_clcdd8_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D8_PS)
#define _ioctrl_clcdd9_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D9_PS)
#define _ioctrl_clcdd9_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D9_PS)
#define _ioctrl_clcdd10_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D10_PS)
#define _ioctrl_clcdd10_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D10_PS)
#define _ioctrl_clcdd11_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D11_PS)
#define _ioctrl_clcdd11_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D11_PS)
#define _ioctrl_clcdd12_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D12_PS)
#define _ioctrl_clcdd12_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D12_PS)
#define _ioctrl_clcdd13_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D13_PS)
#define _ioctrl_clcdd13_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D13_PS)
#define _ioctrl_clcdd14_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D14_PS)
#define _ioctrl_clcdd14_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D14_PS)
#define _ioctrl_clcdd15_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D15_PS)
#define _ioctrl_clcdd15_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D15_PS)
#define _ioctrl_clcdd16_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D16_PS)
#define _ioctrl_clcdd16_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D16_PS)
#define _ioctrl_clcdd17_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D17_PS)
#define _ioctrl_clcdd17_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D17_PS)
#define _ioctrl_clcdd18_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D18_PS)
#define _ioctrl_clcdd18_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D18_PS)
#define _ioctrl_clcdd19_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D19_PS)
#define _ioctrl_clcdd19_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D19_PS)
#define _ioctrl_clcdd20_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D20_PS)
#define _ioctrl_clcdd20_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D20_PS)
#define _ioctrl_clcdd21_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D21_PS)
#define _ioctrl_clcdd21_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D21_PS)
#define _ioctrl_clcdd22_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D22_PS)
#define _ioctrl_clcdd22_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D22_PS)
#define _ioctrl_clcdd23_pull_up _bit_set(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D23_PS)
#define _ioctrl_clcdd23_pull_down _bit_clr(IOCTRL->CLCDPSCR, IOCTRL_CLCDCR_D23_PS)

// GMACWKCR
#define _ioctrl_gmacwkcr_ds_2ma _bit_clr(IOCTRL->GMACWKCR, IOCTRL_GMACCR_DS1_DS0)
#define _ioctrl_gmacwkcr_ds_4ma _reg_modify(IOCTRL->GMACWKCR, ~IOCTRL_GMACCR_DS1_DS0, IOCTRL_GMACCR_DS1)
#define _ioctrl_gmacwkcr_ds_8ma _reg_modify(IOCTRL->GMACWKCR, ~IOCTRL_GMACCR_DS1_DS0, IOCTRL_GMACCR_DS0)
#define _ioctrl_gmacwkcr_ds_12ma _bit_set(IOCTRL->GMACWKCR, IOCTRL_GMACCR_DS1_DS0)
#define _ioctrl_wkusbdetcr_ds_2ma _bit_clr(IOCTRL->GMACWKCR, IOCTRL_WKUSBDETCR_DS1_DS0)
#define _ioctrl_wkusbdetcr_ds_4ma _reg_modify(IOCTRL->GMACWKCR, ~IOCTRL_WKUSBDETCR_DS1_DS0, IOCTRL_WKUSBDETCR_DS1)
#define _ioctrl_wkusbdetcr_ds_8ma _reg_modify(IOCTRL->GMACWKCR, ~IOCTRL_WKUSBDETCR_DS1_DS0, IOCTRL_WKUSBDETCR_DS0)
#define _ioctrl_wkusbdetcr_ds_12ma _bit_set(IOCTRL->GMACWKCR, IOCTRL_WKUSBDETCR_DS1_DS0)
#define _ioctrl_gmacwkcr_slew_fast _bit_clr(IOCTRL->GMACWKCR, IOCTRL_GMACCR_SR)
#define _ioctrl_gmacwkcr_slew_slow _bit_set(IOCTRL->GMACWKCR, IOCTRL_GMACCR_SR)
#define _ioctrl_wkusbdetcr_slew_fast _bit_clr(IOCTRL->GMACWKCR, IOCTRL_WKUSBDETCR_SR)
#define _ioctrl_wkusbdetcr_slew_slow _bit_set(IOCTRL->GMACWKCR, IOCTRL_WKUSBDETCR_SR)

#define _ioctrl_wakeup_pull_up _bit_set(IOCTRL->GMACWKCR, IOCTRL_GMACWKCR_WAKEUP_PS)
#define _ioctrl_wakeup_pull_down _bit_clr(IOCTRL->GMACWKCR, IOCTRL_GMACWKCR_WAKEUP_PS)
#define _ioctrl_usbdet_pull_up _bit_set(IOCTRL->GMACWKCR, IOCTRL_GMACWKCR_USBDET_PS)
#define _ioctrl_usbdet_pull_down _bit_clr(IOCTRL->GMACWKCR, IOCTRL_GMACWKCR_USBDET_PS)

#define _ioctrl_gmacwkcr_pull_up _bit_set(IOCTRL->GMACWKCR, IOCTRL_GMACWKCR_PS)
#define _ioctrl_gmacwkcr_pull_down _bit_clr(IOCTRL->GMACWKCR, IOCTRL_GMACWKCR_PS)
// PSRAMCR1
#define _ioctrl_psramcr1_psram_dis _bit_clr(IOCTRL->PSRAMCR1, IOCTRL_PSRAMCR1_PSRAM_EN)
#define _ioctrl_psramcr1_psram_en _bit_set(IOCTRL->PSRAMCR1, IOCTRL_PSRAMCR1_PSRAM_EN)

// PSRAMCR2
#define _ioctrl_psramcr2_psram_dis _bit_clr(IOCTRL->PSRAMCR2, IOCTRL_PSRAMCR2_PSRAM_EN)
#define _ioctrl_psramcr2_psram_en _bit_set(IOCTRL->PSRAMCR2, IOCTRL_PSRAMCR2_PSRAM_EN)

// PSRAMCR3
#define _ioctrl_psramcr3_psram_dis _bit_clr(IOCTRL->PSRAMCR3, IOCTRL_PSRAMCR3_PSRAM_EN)
#define _ioctrl_psramcr3_psram_en _bit_set(IOCTRL->PSRAMCR3, IOCTRL_PSRAMCR3_PSRAM_EN)

// EPORT2CR
#define _ioctrl_eport2_ds_2ma _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport2_ds_4ma _reg_modify(IOCTRL->EPORT2CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport2_ds_8ma _reg_modify(IOCTRL->EPORT2CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport2_ds_12ma _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport2_pin0_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN0)
#define _ioctrl_eport2_pin0_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN0)
#define _ioctrl_eport2_pin1_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN1)
#define _ioctrl_eport2_pin1_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN1)
#define _ioctrl_eport2_pin2_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN2)
#define _ioctrl_eport2_pin2_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN2)
#define _ioctrl_eport2_pin3_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN3)
#define _ioctrl_eport2_pin3_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN3)
#define _ioctrl_eport2_pin4_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN4)
#define _ioctrl_eport2_pin4_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN4)
#define _ioctrl_eport2_pin5_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN5)
#define _ioctrl_eport2_pin5_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN5)
#define _ioctrl_eport2_pin6_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN6)
#define _ioctrl_eport2_pin6_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN6)
#define _ioctrl_eport2_pin7_input_dis _bit_clr(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN7)
#define _ioctrl_eport2_pin7_input_en _bit_set(IOCTRL->EPORT2CR, IOCTRL_EPORT2CR_IE_PIN7)

    // EPORT3CR

#define _ioctrl_eport3_ds_2ma _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport3_ds_4ma _reg_modify(IOCTRL->EPORT3CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport3_ds_8ma _reg_modify(IOCTRL->EPORT3CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport3_ds_12ma _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport3_pin0_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN0)
#define _ioctrl_eport3_pin0_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN0)
#define _ioctrl_eport3_pin1_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN1)
#define _ioctrl_eport3_pin1_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN1)
#define _ioctrl_eport3_pin2_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN2)
#define _ioctrl_eport3_pin2_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN2)
#define _ioctrl_eport3_pin3_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN3)
#define _ioctrl_eport3_pin3_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN3)
#define _ioctrl_eport3_pin4_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN4)
#define _ioctrl_eport3_pin4_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN4)
#define _ioctrl_eport3_pin5_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN5)
#define _ioctrl_eport3_pin5_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN5)
#define _ioctrl_eport3_pin6_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN6)
#define _ioctrl_eport3_pin6_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN6)
#define _ioctrl_eport3_pin7_input_dis _bit_clr(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN7)
#define _ioctrl_eport3_pin7_input_en _bit_set(IOCTRL->EPORT3CR, IOCTRL_EPORT3CR_IE_PIN7)

// EPORT4CR
#define _ioctrl_eport4_ds_2ma _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport4_ds_4ma _reg_modify(IOCTRL->EPORT4CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport4_ds_8ma _reg_modify(IOCTRL->EPORT4CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport4_ds_12ma _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport4_pin0_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN0)
#define _ioctrl_eport4_pin0_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN0)
#define _ioctrl_eport4_pin1_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN1)
#define _ioctrl_eport4_pin1_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN1)
#define _ioctrl_eport4_pin2_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN2)
#define _ioctrl_eport4_pin2_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN2)
#define _ioctrl_eport4_pin3_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN3)
#define _ioctrl_eport4_pin3_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN3)
#define _ioctrl_eport4_pin4_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN4)
#define _ioctrl_eport4_pin4_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN4)
#define _ioctrl_eport4_pin5_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN5)
#define _ioctrl_eport4_pin5_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN5)
#define _ioctrl_eport4_pin6_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN6)
#define _ioctrl_eport4_pin6_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN6)
#define _ioctrl_eport4_pin7_input_dis _bit_clr(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN7)
#define _ioctrl_eport4_pin7_input_en _bit_set(IOCTRL->EPORT4CR, IOCTRL_EPORT4CR_IE_PIN7)

// EPORT5CR
#define _ioctrl_eport5_ds_2ma _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport5_ds_4ma _reg_modify(IOCTRL->EPORT5CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport5_ds_8ma _reg_modify(IOCTRL->EPORT5CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport5_ds_12ma _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport5_pin0_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN0)
#define _ioctrl_eport5_pin0_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN0)
#define _ioctrl_eport5_pin1_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN1)
#define _ioctrl_eport5_pin1_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN1)
#define _ioctrl_eport5_pin2_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN2)
#define _ioctrl_eport5_pin2_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN2)
#define _ioctrl_eport5_pin3_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN3)
#define _ioctrl_eport5_pin3_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN3)
#define _ioctrl_eport5_pin4_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN4)
#define _ioctrl_eport5_pin4_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN4)
#define _ioctrl_eport5_pin5_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN5)
#define _ioctrl_eport5_pin5_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN5)
#define _ioctrl_eport5_pin6_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN6)
#define _ioctrl_eport5_pin6_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN6)
#define _ioctrl_eport5_pin7_input_dis _bit_clr(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN7)
#define _ioctrl_eport5_pin7_input_en _bit_set(IOCTRL->EPORT5CR, IOCTRL_EPORT5CR_IE_PIN7)

// EPORT6CR
#define _ioctrl_eport6_ds_2ma _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport6_ds_4ma _reg_modify(IOCTRL->EPORT6CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport6_ds_8ma _reg_modify(IOCTRL->EPORT6CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport6_ds_12ma _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport6_pin0_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN0)
#define _ioctrl_eport6_pin0_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN0)
#define _ioctrl_eport6_pin1_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN1)
#define _ioctrl_eport6_pin1_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN1)
#define _ioctrl_eport6_pin2_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN2)
#define _ioctrl_eport6_pin2_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN2)
#define _ioctrl_eport6_pin3_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN3)
#define _ioctrl_eport6_pin3_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN3)
#define _ioctrl_eport6_pin4_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN4)
#define _ioctrl_eport6_pin4_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN4)
#define _ioctrl_eport6_pin5_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN5)
#define _ioctrl_eport6_pin5_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN5)
#define _ioctrl_eport6_pin6_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN6)
#define _ioctrl_eport6_pin6_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN6)
#define _ioctrl_eport6_pin7_input_dis _bit_clr(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN7)
#define _ioctrl_eport6_pin7_input_en _bit_set(IOCTRL->EPORT6CR, IOCTRL_EPORT6CR_IE_PIN7)

// EPORT7CR
#define _ioctrl_eport7_ds_2ma _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport7_ds_4ma _reg_modify(IOCTRL->EPORT7CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport7_ds_8ma _reg_modify(IOCTRL->EPORT7CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport7_ds_12ma _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport7_pin0_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN0)
#define _ioctrl_eport7_pin0_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN0)
#define _ioctrl_eport7_pin1_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN1)
#define _ioctrl_eport7_pin1_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN1)
#define _ioctrl_eport7_pin2_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN2)
#define _ioctrl_eport7_pin2_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN2)
#define _ioctrl_eport7_pin3_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN3)
#define _ioctrl_eport7_pin3_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN3)
#define _ioctrl_eport7_pin4_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN4)
#define _ioctrl_eport7_pin4_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN4)
#define _ioctrl_eport7_pin5_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN5)
#define _ioctrl_eport7_pin5_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN5)
#define _ioctrl_eport7_pin6_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN6)
#define _ioctrl_eport7_pin6_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN6)
#define _ioctrl_eport7_pin7_input_dis _bit_clr(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN7)
#define _ioctrl_eport7_pin7_input_en _bit_set(IOCTRL->EPORT7CR, IOCTRL_EPORT7CR_IE_PIN7)

// EPORT8CR
#define _ioctrl_eport8_ds_2ma _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport8_ds_4ma _reg_modify(IOCTRL->EPORT8CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport8_ds_8ma _reg_modify(IOCTRL->EPORT8CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport8_ds_12ma _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport8_pin0_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN0)
#define _ioctrl_eport8_pin0_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN0)
#define _ioctrl_eport8_pin1_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN1)
#define _ioctrl_eport8_pin1_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN1)
#define _ioctrl_eport8_pin2_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN2)
#define _ioctrl_eport8_pin2_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN2)
#define _ioctrl_eport8_pin3_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN3)
#define _ioctrl_eport8_pin3_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN3)
#define _ioctrl_eport8_pin4_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN4)
#define _ioctrl_eport8_pin4_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN4)
#define _ioctrl_eport8_pin5_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN5)
#define _ioctrl_eport8_pin5_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN5)
#define _ioctrl_eport8_pin6_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN6)
#define _ioctrl_eport8_pin6_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN6)
#define _ioctrl_eport8_pin7_input_dis _bit_clr(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN7)
#define _ioctrl_eport8_pin7_input_en _bit_set(IOCTRL->EPORT8CR, IOCTRL_EPORT8CR_IE_PIN7)

// EPORT9CR
#define _ioctrl_eport9_ds_2ma _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport9_ds_4ma _reg_modify(IOCTRL->EPORT9CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS1)
#define _ioctrl_eport9_ds_8ma _reg_modify(IOCTRL->EPORT9CR, ~IOCTRL_EPORT1CR_DS1_DS0, IOCTRL_EPORT1CR_DS0)
#define _ioctrl_eport9_ds_12ma _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT1CR_DS1_DS0)
#define _ioctrl_eport9_pin0_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN0)
#define _ioctrl_eport9_pin0_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN0)
#define _ioctrl_eport9_pin1_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN1)
#define _ioctrl_eport9_pin1_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN1)
#define _ioctrl_eport9_pin2_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN2)
#define _ioctrl_eport9_pin2_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN2)
#define _ioctrl_eport9_pin3_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN3)
#define _ioctrl_eport9_pin3_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN3)
#define _ioctrl_eport9_pin4_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN4)
#define _ioctrl_eport9_pin4_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN4)
#define _ioctrl_eport9_pin5_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN5)
#define _ioctrl_eport9_pin5_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN5)
#define _ioctrl_eport9_pin6_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN6)
#define _ioctrl_eport9_pin6_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN6)
#define _ioctrl_eport9_pin7_input_dis _bit_clr(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN7)
#define _ioctrl_eport9_pin7_input_en _bit_set(IOCTRL->EPORT9CR, IOCTRL_EPORT9CR_IE_PIN7)

// SWAPCR2
#define _ioctrl_swapcr2_swap0_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT0)
#define _ioctrl_swapcr2_swap0_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT0)
#define _ioctrl_swapcr2_swap1_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT1)
#define _ioctrl_swapcr2_swap1_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT1)
#define _ioctrl_swapcr2_swap2_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT2)
#define _ioctrl_swapcr2_swap2_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT2)
#define _ioctrl_swapcr2_swap3_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT3)
#define _ioctrl_swapcr2_swap3_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT3)
#define _ioctrl_swapcr2_swap4_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT4)
#define _ioctrl_swapcr2_swap4_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT4)
#define _ioctrl_swapcr2_swap5_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT5)
#define _ioctrl_swapcr2_swap5_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT5)
#define _ioctrl_swapcr2_swap6_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT6)
#define _ioctrl_swapcr2_swap6_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT6)
#define _ioctrl_swapcr2_swap7_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT7)
#define _ioctrl_swapcr2_swap7_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT7)
#define _ioctrl_swapcr2_swap8_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT8)
#define _ioctrl_swapcr2_swap8_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT8)
#define _ioctrl_swapcr2_swap9_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT9)
#define _ioctrl_swapcr2_swap9_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT9)
#define _ioctrl_swapcr2_swap10_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT10)
#define _ioctrl_swapcr2_swap10_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT10)
#define _ioctrl_swapcr2_swap11_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT11)
#define _ioctrl_swapcr2_swap11_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT11)
#define _ioctrl_swapcr2_swap12_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT12)
#define _ioctrl_swapcr2_swap12_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT12)
#define _ioctrl_swapcr2_swap13_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT13)
#define _ioctrl_swapcr2_swap13_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT13)
#define _ioctrl_swapcr2_swap14_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT14)
#define _ioctrl_swapcr2_swap14_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT14)
#define _ioctrl_swapcr2_swap15_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT15)
#define _ioctrl_swapcr2_swap15_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT15)
#define _ioctrl_swapcr2_swap16_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT16)
#define _ioctrl_swapcr2_swap16_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT16)
#define _ioctrl_swapcr2_swap17_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT17)
#define _ioctrl_swapcr2_swap17_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT17)
#define _ioctrl_swapcr2_swap18_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT18)
#define _ioctrl_swapcr2_swap18_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT18)
#define _ioctrl_swapcr2_swap19_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT19)
#define _ioctrl_swapcr2_swap19_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT19)
#define _ioctrl_swapcr2_swap20_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT20)
#define _ioctrl_swapcr2_swap20_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT20)
#define _ioctrl_swapcr2_swap21_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT21)
#define _ioctrl_swapcr2_swap21_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT21)
#define _ioctrl_swapcr2_swap22_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT22)
#define _ioctrl_swapcr2_swap22_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT22)
#define _ioctrl_swapcr2_swap23_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT23)
#define _ioctrl_swapcr2_swap23_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT23)
#define _ioctrl_swapcr2_swap24_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT24)
#define _ioctrl_swapcr2_swap24_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT24)
#define _ioctrl_swapcr2_swap25_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT25)
#define _ioctrl_swapcr2_swap25_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT25)
#define _ioctrl_swapcr2_swap26_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT26)
#define _ioctrl_swapcr2_swap26_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT26)
#define _ioctrl_swapcr2_swap27_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT27)
#define _ioctrl_swapcr2_swap27_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT27)
#define _ioctrl_swapcr2_swap28_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT28)
#define _ioctrl_swapcr2_swap28_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT28)
#define _ioctrl_swapcr2_swap29_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT29)
#define _ioctrl_swapcr2_swap29_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT29)
#define _ioctrl_swapcr2_swap30_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT30)
#define _ioctrl_swapcr2_swap30_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT30)
#define _ioctrl_swapcr2_swap31_clr _bit_clr(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT31)
#define _ioctrl_swapcr2_swap31_set _bit_set(IOCTRL->SWAPCR2, IOCTRL_SWAPCR2_SWAP_BIT31)

// SWAPCR3
#define _ioctrl_swapcr3_swap0_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT0)
#define _ioctrl_swapcr3_swap0_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT0)
#define _ioctrl_swapcr3_swap1_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT1)
#define _ioctrl_swapcr3_swap1_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT1)
#define _ioctrl_swapcr3_swap2_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT2)
#define _ioctrl_swapcr3_swap2_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT2)
#define _ioctrl_swapcr3_swap3_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT3)
#define _ioctrl_swapcr3_swap3_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT3)
#define _ioctrl_swapcr3_swap4_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT4)
#define _ioctrl_swapcr3_swap4_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT4)
#define _ioctrl_swapcr3_swap5_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT5)
#define _ioctrl_swapcr3_swap5_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT5)
#define _ioctrl_swapcr3_swap6_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT6)
#define _ioctrl_swapcr3_swap6_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT6)
#define _ioctrl_swapcr3_swap7_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT7)
#define _ioctrl_swapcr3_swap7_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT7)
#define _ioctrl_swapcr3_swap8_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT8)
#define _ioctrl_swapcr3_swap8_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT8)
#define _ioctrl_swapcr3_swap9_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT9)
#define _ioctrl_swapcr3_swap9_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT9)
#define _ioctrl_swapcr3_swap10_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT10)
#define _ioctrl_swapcr3_swap10_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT10)
#define _ioctrl_swapcr3_swap11_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT11)
#define _ioctrl_swapcr3_swap11_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT11)
#define _ioctrl_swapcr3_swap12_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT12)
#define _ioctrl_swapcr3_swap12_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT12)
#define _ioctrl_swapcr3_swap13_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT13)
#define _ioctrl_swapcr3_swap13_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT13)
#define _ioctrl_swapcr3_swap14_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT14)
#define _ioctrl_swapcr3_swap14_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT14)
#define _ioctrl_swapcr3_swap15_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT15)
#define _ioctrl_swapcr3_swap15_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT15)
#define _ioctrl_swapcr3_swap16_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT16)
#define _ioctrl_swapcr3_swap16_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT16)
#define _ioctrl_swapcr3_swap17_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT17)
#define _ioctrl_swapcr3_swap17_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT17)
#define _ioctrl_swapcr3_swap18_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT18)
#define _ioctrl_swapcr3_swap18_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT18)
#define _ioctrl_swapcr3_swap19_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT19)
#define _ioctrl_swapcr3_swap19_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT19)
#define _ioctrl_swapcr3_swap20_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT20)
#define _ioctrl_swapcr3_swap20_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT20)
#define _ioctrl_swapcr3_swap21_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT21)
#define _ioctrl_swapcr3_swap21_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT21)
#define _ioctrl_swapcr3_swap22_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT22)
#define _ioctrl_swapcr3_swap22_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT22)
#define _ioctrl_swapcr3_swap23_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT23)
#define _ioctrl_swapcr3_swap23_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT23)
#define _ioctrl_swapcr3_swap24_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT24)
#define _ioctrl_swapcr3_swap24_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT24)
#define _ioctrl_swapcr3_swap25_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT25)
#define _ioctrl_swapcr3_swap25_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT25)
#define _ioctrl_swapcr3_swap26_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT26)
#define _ioctrl_swapcr3_swap26_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT26)
#define _ioctrl_swapcr3_swap27_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT27)
#define _ioctrl_swapcr3_swap27_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT27)
#define _ioctrl_swapcr3_swap28_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT28)
#define _ioctrl_swapcr3_swap28_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT28)
#define _ioctrl_swapcr3_swap29_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT29)
#define _ioctrl_swapcr3_swap29_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT29)
#define _ioctrl_swapcr3_swap30_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT30)
#define _ioctrl_swapcr3_swap30_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT30)
#define _ioctrl_swapcr3_swap31_clr _bit_clr(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT31)
#define _ioctrl_swapcr3_swap31_set _bit_set(IOCTRL->SWAPCR3, IOCTRL_SWAPCR3_SWAP_BIT31)

// SWAPCR4
#define _ioctrl_swapcr4_swap0_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT0)
#define _ioctrl_swapcr4_swap0_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT0)
#define _ioctrl_swapcr4_swap1_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT1)
#define _ioctrl_swapcr4_swap1_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT1)
#define _ioctrl_swapcr4_swap2_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT2)
#define _ioctrl_swapcr4_swap2_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT2)
#define _ioctrl_swapcr4_swap3_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT3)
#define _ioctrl_swapcr4_swap3_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT3)
#define _ioctrl_swapcr4_swap4_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT4)
#define _ioctrl_swapcr4_swap4_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT4)
#define _ioctrl_swapcr4_swap5_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT5)
#define _ioctrl_swapcr4_swap5_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT5)
#define _ioctrl_swapcr4_swap6_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT6)
#define _ioctrl_swapcr4_swap6_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT6)
#define _ioctrl_swapcr4_swap7_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT7)
#define _ioctrl_swapcr4_swap7_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT7)
#define _ioctrl_swapcr4_swap8_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT8)
#define _ioctrl_swapcr4_swap8_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT8)
#define _ioctrl_swapcr4_swap9_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT9)
#define _ioctrl_swapcr4_swap9_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT9)
#define _ioctrl_swapcr4_swap10_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT10)
#define _ioctrl_swapcr4_swap10_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT10)
#define _ioctrl_swapcr4_swap11_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT11)
#define _ioctrl_swapcr4_swap11_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT11)
#define _ioctrl_swapcr4_swap12_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT12)
#define _ioctrl_swapcr4_swap12_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT12)
#define _ioctrl_swapcr4_swap13_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT13)
#define _ioctrl_swapcr4_swap13_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT13)
#define _ioctrl_swapcr4_swap14_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT14)
#define _ioctrl_swapcr4_swap14_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT14)
#define _ioctrl_swapcr4_swap15_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT15)
#define _ioctrl_swapcr4_swap15_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT15)
#define _ioctrl_swapcr4_swap16_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT16)
#define _ioctrl_swapcr4_swap16_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT16)
#define _ioctrl_swapcr4_swap17_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT17)
#define _ioctrl_swapcr4_swap17_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT17)
#define _ioctrl_swapcr4_swap18_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT18)
#define _ioctrl_swapcr4_swap18_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT18)
#define _ioctrl_swapcr4_swap19_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT19)
#define _ioctrl_swapcr4_swap19_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT19)
#define _ioctrl_swapcr4_swap20_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT20)
#define _ioctrl_swapcr4_swap20_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT20)
#define _ioctrl_swapcr4_swap21_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT21)
#define _ioctrl_swapcr4_swap21_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT21)
#define _ioctrl_swapcr4_swap22_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT22)
#define _ioctrl_swapcr4_swap22_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT22)
#define _ioctrl_swapcr4_swap23_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT23)
#define _ioctrl_swapcr4_swap23_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT23)
#define _ioctrl_swapcr4_swap24_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT24)
#define _ioctrl_swapcr4_swap24_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT24)
#define _ioctrl_swapcr4_swap25_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT25)
#define _ioctrl_swapcr4_swap25_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT25)
#define _ioctrl_swapcr4_swap26_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT26)
#define _ioctrl_swapcr4_swap26_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT26)
#define _ioctrl_swapcr4_swap27_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT27)
#define _ioctrl_swapcr4_swap27_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT27)
#define _ioctrl_swapcr4_swap28_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT28)
#define _ioctrl_swapcr4_swap28_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT28)
#define _ioctrl_swapcr4_swap29_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT29)
#define _ioctrl_swapcr4_swap29_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT29)
#define _ioctrl_swapcr4_swap30_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT30)
#define _ioctrl_swapcr4_swap30_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT30)
#define _ioctrl_swapcr4_swap31_clr _bit_clr(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT31)
#define _ioctrl_swapcr4_swap31_set _bit_set(IOCTRL->SWAPCR4, IOCTRL_SWAPCR4_SWAP_BIT31)

// SWAPCR5
#define _ioctrl_swapcr5_swap0_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT0)
#define _ioctrl_swapcr5_swap0_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT0)
#define _ioctrl_swapcr5_swap1_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT1)
#define _ioctrl_swapcr5_swap1_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT1)
#define _ioctrl_swapcr5_swap2_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT2)
#define _ioctrl_swapcr5_swap2_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT2)
#define _ioctrl_swapcr5_swap3_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT3)
#define _ioctrl_swapcr5_swap3_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT3)
#define _ioctrl_swapcr5_swap4_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT4)
#define _ioctrl_swapcr5_swap4_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT4)
#define _ioctrl_swapcr5_swap5_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT5)
#define _ioctrl_swapcr5_swap5_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT5)
#define _ioctrl_swapcr5_swap6_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT6)
#define _ioctrl_swapcr5_swap6_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT6)
#define _ioctrl_swapcr5_swap7_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT7)
#define _ioctrl_swapcr5_swap7_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT7)
#define _ioctrl_swapcr5_swap8_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT8)
#define _ioctrl_swapcr5_swap8_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT8)
#define _ioctrl_swapcr5_swap9_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT9)
#define _ioctrl_swapcr5_swap9_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT9)
#define _ioctrl_swapcr5_swap10_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT10)
#define _ioctrl_swapcr5_swap10_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT10)
#define _ioctrl_swapcr5_swap11_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT11)
#define _ioctrl_swapcr5_swap11_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT11)
#define _ioctrl_swapcr5_swap12_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT12)
#define _ioctrl_swapcr5_swap12_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT12)
#define _ioctrl_swapcr5_swap13_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT13)
#define _ioctrl_swapcr5_swap13_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT13)
#define _ioctrl_swapcr5_swap14_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT14)
#define _ioctrl_swapcr5_swap14_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT14)
#define _ioctrl_swapcr5_swap15_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT15)
#define _ioctrl_swapcr5_swap15_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT15)
#define _ioctrl_swapcr5_swap16_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT16)
#define _ioctrl_swapcr5_swap16_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT16)
#define _ioctrl_swapcr5_swap17_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT17)
#define _ioctrl_swapcr5_swap17_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT17)
#define _ioctrl_swapcr5_swap18_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT18)
#define _ioctrl_swapcr5_swap18_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT18)
#define _ioctrl_swapcr5_swap19_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT19)
#define _ioctrl_swapcr5_swap19_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT19)
#define _ioctrl_swapcr5_swap20_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT20)
#define _ioctrl_swapcr5_swap20_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT20)
#define _ioctrl_swapcr5_swap21_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT21)
#define _ioctrl_swapcr5_swap21_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT21)
#define _ioctrl_swapcr5_swap22_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT22)
#define _ioctrl_swapcr5_swap22_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT22)
#define _ioctrl_swapcr5_swap23_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT23)
#define _ioctrl_swapcr5_swap23_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT23)
#define _ioctrl_swapcr5_swap24_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT24)
#define _ioctrl_swapcr5_swap24_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT24)
#define _ioctrl_swapcr5_swap25_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT25)
#define _ioctrl_swapcr5_swap25_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT25)
#define _ioctrl_swapcr5_swap26_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT26)
#define _ioctrl_swapcr5_swap26_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT26)
#define _ioctrl_swapcr5_swap27_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT27)
#define _ioctrl_swapcr5_swap27_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT27)
#define _ioctrl_swapcr5_swap28_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT28)
#define _ioctrl_swapcr5_swap28_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT28)
#define _ioctrl_swapcr5_swap29_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT29)
#define _ioctrl_swapcr5_swap29_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT29)
#define _ioctrl_swapcr5_swap30_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT30)
#define _ioctrl_swapcr5_swap30_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT30)
#define _ioctrl_swapcr5_swap31_clr _bit_clr(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT31)
#define _ioctrl_swapcr5_swap31_set _bit_set(IOCTRL->SWAPCR5, IOCTRL_SWAPCR5_SWAP_BIT31)

// I2SIOCR
#define _ioctrl_i2siocr_i2s1_ds_2ma _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_DS1_DS0)
#define _ioctrl_i2siocr_i2s1_ds_4ma _reg_modify(IOCTRL->I2SIOCR, ~IOCTRL_I2SIOCR_I2S1_DS1_DS0, IOCTRL_I2SIOCR_I2S1_DS1)
#define _ioctrl_i2siocr_i2s1_ds_8ma _reg_modify(IOCTRL->I2SIOCR, ~IOCTRL_I2SIOCR_I2S1_DS1_DS0, IOCTRL_I2SIOCR_I2S1_DS0)
#define _ioctrl_i2siocr_i2s1_ds_12ma _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_DS1_DS0)
#define _ioctrl_i2siocr_i2s1_slew_fast _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SR)
#define _ioctrl_i2siocr_i2s1_slew_slow _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SR)
#define _ioctrl_i2siocr_i2s1_input_cmos _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_IS)
#define _ioctrl_i2siocr_i2s1_input_schmitt _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_IS)
#define _ioctrl_i2siocr_i2s1_sd_input_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SD_IE)
#define _ioctrl_i2siocr_i2s1_sd_input_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SD_IE)
#define _ioctrl_i2siocr_i2s1_sclk_input_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SCLK_IE)
#define _ioctrl_i2siocr_i2s1_sclk_input_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SCLK_IE)
#define _ioctrl_i2siocr_i2s1_sd_pull_up_down_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SD_PUE)
#define _ioctrl_i2siocr_i2s1_sd_pull_up_down_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SD_PUE)
#define _ioctrl_i2siocr_i2s1_sclk_pull_up_down_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SCLK_PUE)
#define _ioctrl_i2siocr_i2s1_sclk_pull_up_down_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SCLK_PUE)
#define _ioctrl_i2siocr_i2s1_sd_pull_down _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SD_PS)
#define _ioctrl_i2siocr_i2s1_sd_pull_up _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SD_PS)
#define _ioctrl_i2siocr_i2s1_sclk_pull_down _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SCLK_PS)
#define _ioctrl_i2siocr_i2s1_sclk_pull_up _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S1_SCLK_PS)

#define _ioctrl_i2siocr_i2s2_ds_2ma _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_DS1_DS0)
#define _ioctrl_i2siocr_i2s2_ds_4ma _reg_modify(IOCTRL->I2SIOCR, ~IOCTRL_I2SIOCR_I2S2_DS1_DS0, IOCTRL_I2SIOCR_I2S2_DS1)
#define _ioctrl_i2siocr_i2s2_ds_8ma _reg_modify(IOCTRL->I2SIOCR, ~IOCTRL_I2SIOCR_I2S2_DS1_DS0, IOCTRL_I2SIOCR_I2S2_DS0)
#define _ioctrl_i2siocr_i2s2_ds_12ma _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_DS1_DS0)
#define _ioctrl_i2siocr_i2s2_slew_fast _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SR)
#define _ioctrl_i2siocr_i2s2_slew_slow _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SR)
#define _ioctrl_i2siocr_i2s2_input_cmos _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_IS)
#define _ioctrl_i2siocr_i2s2_input_schmitt _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_IS)
#define _ioctrl_i2siocr_i2s2_sd_input_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SD_IE)
#define _ioctrl_i2siocr_i2s2_sd_input_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SD_IE)
#define _ioctrl_i2siocr_i2s2_sclk_input_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SCLK_IE)
#define _ioctrl_i2siocr_i2s2_sclk_input_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SCLK_IE)
#define _ioctrl_i2siocr_i2s2_sd_pull_up_down_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SD_PUE)
#define _ioctrl_i2siocr_i2s2_sd_pull_up_down_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SD_PUE)
#define _ioctrl_i2siocr_i2s2_sclk_pull_up_down_dis _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SCLK_PUE)
#define _ioctrl_i2siocr_i2s2_sclk_pull_up_down_en _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SCLK_PUE)
#define _ioctrl_i2siocr_i2s2_sd_pull_down _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SD_PS)
#define _ioctrl_i2siocr_i2s2_sd_pull_up _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SD_PS)
#define _ioctrl_i2siocr_i2s2_sclk_pull_down _bit_clr(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SCLK_PS)
#define _ioctrl_i2siocr_i2s2_sclk_pull_up _bit_set(IOCTRL->I2SIOCR, IOCTRL_I2SIOCR_I2S2_SCLK_PS)

// PWMTCR
#define _ioctrl_pwmtcr_pwmt1_etr_pull_up_down_dis _bit_clr(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT1_ETR_PUE)
#define _ioctrl_pwmtcr_pwmt1_etr_pull_up_down_en _bit_set(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT1_ETR_PUE)
#define _ioctrl_pwmtcr_pwmt1_brk_pull_up_down_dis _bit_clr(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT1_BRK_PUE)
#define _ioctrl_pwmtcr_pwmt1_brk_pull_up_down_en _bit_set(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT1_BRK_PUE)
#define _ioctrl_pwmtcr_pwmt2_etr_pull_up_down_dis _bit_clr(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT2_ETR_PUE)
#define _ioctrl_pwmtcr_pwmt2_etr_pull_up_down_en _bit_set(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT2_ETR_PUE)
#define _ioctrl_pwmtcr_pwmt2_brk_pull_up_down_dis _bit_clr(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT2_BRK_PUE)
#define _ioctrl_pwmtcr_pwmt2_brk_pull_up_down_en _bit_set(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT2_BRK_PUE)
#define _ioctrl_pwmtcr_pwmt3_etr_pull_up_down_dis _bit_clr(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT3_ETR_PUE)
#define _ioctrl_pwmtcr_pwmt3_etr_pull_up_down_en _bit_set(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT3_ETR_PUE)
#define _ioctrl_pwmtcr_pwmt3_brk_pull_up_down_dis _bit_clr(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT3_BRK_PUE)
#define _ioctrl_pwmtcr_pwmt3_brk_pull_up_down_en _bit_set(IOCTRL->PWMTCR, IOCTRL_PWMTCR_PWMT3_BRK_PUE)

// CANCR
#define _ioctrl_cancr_can1_rx_pull_up_down_dis _bit_clr(IOCTRL->CANCR, IOCTRL_CANCR_CAN1_RX_PUE)
#define _ioctrl_cancr_can1_rx_pull_up_down_en _bit_set(IOCTRL->CANCR, IOCTRL_CANCR_CAN1_RX_PUE)
#define _ioctrl_cancr_can1_tx_pull_up_down_dis _bit_clr(IOCTRL->CANCR, IOCTRL_CANCR_CAN1_TX_PUE)
#define _ioctrl_cancr_can1_tx_pull_up_down_en _bit_set(IOCTRL->CANCR, IOCTRL_CANCR_CAN1_TX_PUE)
#define _ioctrl_cancr_can2_rx_pull_up_down_dis _bit_clr(IOCTRL->CANCR, IOCTRL_CANCR_CAN2_RX_PUE)
#define _ioctrl_cancr_can2_rx_pull_up_down_en _bit_set(IOCTRL->CANCR, IOCTRL_CANCR_CAN2_RX_PUE)
#define _ioctrl_cancr_can2_tx_pull_up_down_dis _bit_clr(IOCTRL->CANCR, IOCTRL_CANCR_CAN2_TX_PUE)
#define _ioctrl_cancr_can2_tx_pull_up_down_en _bit_set(IOCTRL->CANCR, IOCTRL_CANCR_CAN2_TX_PUE)
#define _ioctrl_cancr_can3_rx_pull_up_down_dis _bit_clr(IOCTRL->CANCR, IOCTRL_CANCR_CAN3_RX_PUE)
#define _ioctrl_cancr_can3_rx_pull_up_down_en _bit_set(IOCTRL->CANCR, IOCTRL_CANCR_CAN3_RX_PUE)
#define _ioctrl_cancr_can3_tx_pull_up_down_dis _bit_clr(IOCTRL->CANCR, IOCTRL_CANCR_CAN3_TX_PUE)
#define _ioctrl_cancr_can3_tx_pull_up_down_en _bit_set(IOCTRL->CANCR, IOCTRL_CANCR_CAN3_TX_PUE)

// SPI1CR
#define _ioctrl_spi1_d_ds_2ma _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_D_DS1_DS0)
#define _ioctrl_spi1_d_ds_4ma _reg_modify(IOCTRL->SPI1CR, ~IOCTRL_SPI1CR_D_DS1_DS0, IOCTRL_SPI1CR_D_DS1)
#define _ioctrl_spi1_d_ds_8ma _reg_modify(IOCTRL->SPI1CR, ~IOCTRL_SPI1CR_D_DS1_DS0, IOCTRL_SPI1CR_D_DS0)
#define _ioctrl_spi1_d_ds_12ma _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_D_DS1_DS0)
#define _ioctrl_spi1_d_slew_fast _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_D_SR)
#define _ioctrl_spi1_d_slew_slow _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_D_SR)
#define _ioctrl_spi1_d_input_cmos _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_D_IS)
#define _ioctrl_spi1_d_input_schmitt _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_D_IS)

#define _ioctrl_spi1_sck_ds_2ma _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SCK_DS1_DS0)
#define _ioctrl_spi1_sck_ds_4ma _reg_modify(IOCTRL->SPI1CR, ~IOCTRL_SPI1CR_SCK_DS1_DS0, IOCTRL_SPI1CR_SCK_DS1)
#define _ioctrl_spi1_sck_ds_8ma _reg_modify(IOCTRL->SPI1CR, ~IOCTRL_SPI1CR_SCK_DS1_DS0, IOCTRL_SPI1CR_SCK_DS0)
#define _ioctrl_spi1_sck_ds_12ma _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SCK_DS1_DS0)
#define _ioctrl_spi1_sck_slew_fast _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SCK_SR)
#define _ioctrl_spi1_sck_slew_slow _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SCK_SR)
#define _ioctrl_spi1_sck_input_cmos _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SCK_IS)
#define _ioctrl_spi1_sck_input_schmitt _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SCK_IS)

#define _ioctrl_spi1_ss_ds_2ma _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SS_DS1_DS0)
#define _ioctrl_spi1_ss_ds_4ma _reg_modify(IOCTRL->SPI1CR, ~IOCTRL_SPI1CR_SS_DS1_DS0, IOCTRL_SPI1CR_SS_DS1)
#define _ioctrl_spi1_ss_ds_8ma _reg_modify(IOCTRL->SPI1CR, ~IOCTRL_SPI1CR_SS_DS1_DS0, IOCTRL_SPI1CR_SS_DS0)
#define _ioctrl_spi1_ss_ds_12ma _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SS_DS1_DS0)
#define _ioctrl_spi1_ss_slew_fast _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SS_SR)
#define _ioctrl_spi1_ss_slew_slow _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SS_SR)
#define _ioctrl_spi1_ss_input_cmos _bit_clr(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SS_IS)
#define _ioctrl_spi1_ss_input_schmitt _bit_set(IOCTRL->SPI1CR, IOCTRL_SPI1CR_SS_IS)

// SPI2CR
#define _ioctrl_spi2_d_ds_2ma _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_D_DS1_DS0)
#define _ioctrl_spi2_d_ds_4ma _reg_modify(IOCTRL->SPI2CR, ~IOCTRL_SPI2CR_D_DS1_DS0, IOCTRL_SPI2CR_D_DS1)
#define _ioctrl_spi2_d_ds_8ma _reg_modify(IOCTRL->SPI2CR, ~IOCTRL_SPI2CR_D_DS1_DS0, IOCTRL_SPI2CR_D_DS0)
#define _ioctrl_spi2_d_ds_12ma _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_D_DS1_DS0)
#define _ioctrl_spi2_d_slew_fast _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_D_SR)
#define _ioctrl_spi2_d_slew_slow _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_D_SR)
#define _ioctrl_spi2_d_input_cmos _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_D_IS)
#define _ioctrl_spi2_d_input_schmitt _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_D_IS)

#define _ioctrl_spi2_sck_ds_2ma _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SCK_DS1_DS0)
#define _ioctrl_spi2_sck_ds_4ma _reg_modify(IOCTRL->SPI2CR, ~IOCTRL_SPI2CR_SCK_DS1_DS0, IOCTRL_SPI2CR_SCK_DS1)
#define _ioctrl_spi2_sck_ds_8ma _reg_modify(IOCTRL->SPI2CR, ~IOCTRL_SPI2CR_SCK_DS1_DS0, IOCTRL_SPI2CR_SCK_DS0)
#define _ioctrl_spi2_sck_ds_12ma _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SCK_DS1_DS0)
#define _ioctrl_spi2_sck_slew_fast _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SCK_SR)
#define _ioctrl_spi2_sck_slew_slow _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SCK_SR)
#define _ioctrl_spi2_sck_input_cmos _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SCK_IS)
#define _ioctrl_spi2_sck_input_schmitt _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SCK_IS)

#define _ioctrl_spi2_ss_ds_2ma _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SS_DS1_DS0)
#define _ioctrl_spi2_ss_ds_4ma _reg_modify(IOCTRL->SPI2CR, ~IOCTRL_SPI2CR_SS_DS1_DS0, IOCTRL_SPI2CR_SS_DS1)
#define _ioctrl_spi2_ss_ds_8ma _reg_modify(IOCTRL->SPI2CR, ~IOCTRL_SPI2CR_SS_DS1_DS0, IOCTRL_SPI2CR_SS_DS0)
#define _ioctrl_spi2_ss_ds_12ma _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SS_DS1_DS0)
#define _ioctrl_spi2_ss_slew_fast _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SS_SR)
#define _ioctrl_spi2_ss_slew_slow _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SS_SR)
#define _ioctrl_spi2_ss_input_cmos _bit_clr(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SS_IS)
#define _ioctrl_spi2_ss_input_schmitt _bit_set(IOCTRL->SPI2CR, IOCTRL_SPI2CR_SS_IS)

// SPI3CR
#define _ioctrl_spi3_d_ds_2ma _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_D_DS1_DS0)
#define _ioctrl_spi3_d_ds_4ma _reg_modify(IOCTRL->SPI3CR, ~IOCTRL_SPI3CR_D_DS1_DS0, IOCTRL_SPI3CR_D_DS1)
#define _ioctrl_spi3_d_ds_8ma _reg_modify(IOCTRL->SPI3CR, ~IOCTRL_SPI3CR_D_DS1_DS0, IOCTRL_SPI3CR_D_DS0)
#define _ioctrl_spi3_d_ds_12ma _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_D_DS1_DS0)
#define _ioctrl_spi3_d_slew_fast _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_D_SR)
#define _ioctrl_spi3_d_slew_slow _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_D_SR)
#define _ioctrl_spi3_d_input_cmos _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_D_IS)
#define _ioctrl_spi3_d_input_schmitt _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_D_IS)

#define _ioctrl_spi3_sck_ds_2ma _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SCK_DS1_DS0)
#define _ioctrl_spi3_sck_ds_4ma _reg_modify(IOCTRL->SPI3CR, ~IOCTRL_SPI3CR_SCK_DS1_DS0, IOCTRL_SPI3CR_SCK_DS1)
#define _ioctrl_spi3_sck_ds_8ma _reg_modify(IOCTRL->SPI3CR, ~IOCTRL_SPI3CR_SCK_DS1_DS0, IOCTRL_SPI3CR_SCK_DS0)
#define _ioctrl_spi3_sck_ds_12ma _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SCK_DS1_DS0)
#define _ioctrl_spi3_sck_slew_fast _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SCK_SR)
#define _ioctrl_spi3_sck_slew_slow _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SCK_SR)
#define _ioctrl_spi3_sck_input_cmos _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SCK_IS)
#define _ioctrl_spi3_sck_input_schmitt _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SCK_IS)

#define _ioctrl_spi3_ss_ds_2ma _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SS_DS1_DS0)
#define _ioctrl_spi3_ss_ds_4ma _reg_modify(IOCTRL->SPI3CR, ~IOCTRL_SPI3CR_SS_DS1_DS0, IOCTRL_SPI3CR_SS_DS1)
#define _ioctrl_spi3_ss_ds_8ma _reg_modify(IOCTRL->SPI3CR, ~IOCTRL_SPI3CR_SS_DS1_DS0, IOCTRL_SPI3CR_SS_DS0)
#define _ioctrl_spi3_ss_ds_12ma _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SS_DS1_DS0)
#define _ioctrl_spi3_ss_slew_fast _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SS_SR)
#define _ioctrl_spi3_ss_slew_slow _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SS_SR)
#define _ioctrl_spi3_ss_input_cmos _bit_clr(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SS_IS)
#define _ioctrl_spi3_ss_input_schmitt _bit_set(IOCTRL->SPI3CR, IOCTRL_SPI3CR_SS_IS)

// SDHCR
#define _ioctrl_sdhdat_ds_2ma _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_DS1_DS0)
#define _ioctrl_sdhdat_ds_4ma _reg_modify(IOCTRL->SDHCR, ~IOCTRL_SDHCR_DS1_DS0, IOCTRL_SDHCR_DS1_DS0)
#define _ioctrl_sdhdat_ds_8ma _reg_modify(IOCTRL->SDHCR, ~IOCTRL_SDHCR_DS1_DS0, IOCTRL_SDHCR_DS0)
#define _ioctrl_sdhdat_ds_12ma _bit_set(IOCTRL->SDHCR, IOCTRL_SPI3CR_SS_DS1_DS0)
#define _ioctrl_sdhdat_slew_fast _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SR)
#define _ioctrl_sdhdat_slew_slow _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SR)
#define _ioctrl_sdhcr_swap2_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT2)
#define _ioctrl_sdhcr_swap2_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT2)
#define _ioctrl_sdhcr_swap3_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT3)
#define _ioctrl_sdhcr_swap3_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT3)
#define _ioctrl_sdhcr_swap4_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT4)
#define _ioctrl_sdhcr_swap4_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT4)
#define _ioctrl_sdhcr_swap5_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT5)
#define _ioctrl_sdhcr_swap5_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT5)
#define _ioctrl_sdhcr_swap6_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT6)
#define _ioctrl_sdhcr_swap6_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT6)
#define _ioctrl_sdhcr_swap7_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT7)
#define _ioctrl_sdhcr_swap7_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT7)
#define _ioctrl_sdhcr_swap8_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT8)
#define _ioctrl_sdhcr_swap8_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT8)
#define _ioctrl_sdhcr_swap9_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT9)
#define _ioctrl_sdhcr_swap9_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT9)
#define _ioctrl_sdhcr_swap10_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT10)
#define _ioctrl_sdhcr_swap10_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT10)
#define _ioctrl_sdhcr_swap11_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT11)
#define _ioctrl_sdhcr_swap11_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT11)
#define _ioctrl_sdhcr_swap12_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT12)
#define _ioctrl_sdhcr_swap12_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT12)
#define _ioctrl_sdhcr_swap13_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT13)
#define _ioctrl_sdhcr_swap13_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT13)
#define _ioctrl_sdhcr_swap14_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT14)
#define _ioctrl_sdhcr_swap14_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT14)
#define _ioctrl_sdhcr_swap15_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT15)
#define _ioctrl_sdhcr_swap15_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT15)
#define _ioctrl_sdhcr_swap16_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT16)
#define _ioctrl_sdhcr_swap16_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT16)
#define _ioctrl_sdhcr_swap17_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT17)
#define _ioctrl_sdhcr_swap17_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT17)
#define _ioctrl_sdhcr_swap18_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT18)
#define _ioctrl_sdhcr_swap18_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT18)
#define _ioctrl_sdhcr_swap19_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT19)
#define _ioctrl_sdhcr_swap19_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT19)
#define _ioctrl_sdhcr_data0_pull_up _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT20)
#define _ioctrl_sdhcr_data0_pull_down _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT20)
#define _ioctrl_sdhcr_data1_pull_up _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT21)
#define _ioctrl_sdhcr_data1_pull_down _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT21)
#define _ioctrl_sdhcr_data2_pull_up _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT22)
#define _ioctrl_sdhcr_data2_pull_down _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT22)
#define _ioctrl_sdhcr_data3_pull_up _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT23)
#define _ioctrl_sdhcr_data3_pull_down _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT23)
#define _ioctrl_sdhcr_swap24_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT24)
#define _ioctrl_sdhcr_swap24_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT24)
#define _ioctrl_sdhcr_swap25_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT25)
#define _ioctrl_sdhcr_swap25_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT25)
#define _ioctrl_sdhcr_swap26_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT26)
#define _ioctrl_sdhcr_swap26_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT26)
#define _ioctrl_sdhcr_swap27_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT27)
#define _ioctrl_sdhcr_swap27_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT27)
#define _ioctrl_sdhcr_swap28_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT28)
#define _ioctrl_sdhcr_swap28_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT28)
#define _ioctrl_sdhcr_swap29_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT29)
#define _ioctrl_sdhcr_swap29_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT29)
#define _ioctrl_sdhcr_swap30_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT30)
#define _ioctrl_sdhcr_swap30_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT30)
#define _ioctrl_sdhcr_swap31_clr _bit_clr(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT31)
#define _ioctrl_sdhcr_swap31_set _bit_set(IOCTRL->SDHCR, IOCTRL_SDHCR_SWAP_BIT31)
// MCULCDCR
#define _ioctrl_mculcdcr_swap0_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT0)
#define _ioctrl_mculcdcr_swap0_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT0)
#define _ioctrl_mculcdcr_swap1_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT1)
#define _ioctrl_mculcdcr_swap1_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT1)
#define _ioctrl_mculcdcr_swap2_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT2)
#define _ioctrl_mculcdcr_swap2_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT2)
#define _ioctrl_mculcdcr_swap3_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT3)
#define _ioctrl_mculcdcr_swap3_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT3)
#define _ioctrl_mculcdcr_swap4_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT4)
#define _ioctrl_mculcdcr_swap4_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT4)
#define _ioctrl_mculcdcr_swap5_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT5)
#define _ioctrl_mculcdcr_swap5_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT5)
#define _ioctrl_mculcdcr_swap6_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT6)
#define _ioctrl_mculcdcr_swap6_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT6)
#define _ioctrl_mculcdcr_swap7_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT7)
#define _ioctrl_mculcdcr_swap7_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT7)
#define _ioctrl_mculcdcr_swap8_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT8)
#define _ioctrl_mculcdcr_swap8_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT8)
#define _ioctrl_mculcdcr_swap9_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT9)
#define _ioctrl_mculcdcr_swap9_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT9)
#define _ioctrl_mculcdcr_swap10_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT10)
#define _ioctrl_mculcdcr_swap10_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT10)
#define _ioctrl_mculcdcr_swap11_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT11)
#define _ioctrl_mculcdcr_swap11_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT11)
#define _ioctrl_mculcdcr_swap12_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT12)
#define _ioctrl_mculcdcr_swap12_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT12)
#define _ioctrl_mculcdcr_swap13_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT13)
#define _ioctrl_mculcdcr_swap13_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT13)
#define _ioctrl_mculcdcr_swap14_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT14)
#define _ioctrl_mculcdcr_swap14_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT14)
#define _ioctrl_mculcdcr_swap15_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT15)
#define _ioctrl_mculcdcr_swap15_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT15)
#define _ioctrl_mculcdcr_swap16_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT16)
#define _ioctrl_mculcdcr_swap16_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT16)
#define _ioctrl_mculcdcr_swap17_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT17)
#define _ioctrl_mculcdcr_swap17_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT17)
#define _ioctrl_mculcdcr_swap18_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT18)
#define _ioctrl_mculcdcr_swap18_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT18)
#define _ioctrl_mculcdcr_swap19_clr _bit_clr(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT19)
#define _ioctrl_mculcdcr_swap19_set _bit_set(IOCTRL->MCULCDCR, IOCTRL_MCULCDCR_SWAP_BIT19)

// SWAPCR6
#define _ioctrl_swapcr6_swap0_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT0)
#define _ioctrl_swapcr6_swap0_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT0)
#define _ioctrl_swapcr6_swap1_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT1)
#define _ioctrl_swapcr6_swap1_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT1)
#define _ioctrl_swapcr6_swap2_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT2)
#define _ioctrl_swapcr6_swap2_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT2)
#define _ioctrl_swapcr6_swap3_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT3)
#define _ioctrl_swapcr6_swap3_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT3)
#define _ioctrl_swapcr6_swap4_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT4)
#define _ioctrl_swapcr6_swap4_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT4)
#define _ioctrl_swapcr6_swap5_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT5)
#define _ioctrl_swapcr6_swap5_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT5)
#define _ioctrl_swapcr6_swap6_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT6)
#define _ioctrl_swapcr6_swap6_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT6)
#define _ioctrl_swapcr6_swap7_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT7)
#define _ioctrl_swapcr6_swap7_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT7)
#define _ioctrl_swapcr6_swap8_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT8)
#define _ioctrl_swapcr6_swap8_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT8)
#define _ioctrl_swapcr6_swap9_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT9)
#define _ioctrl_swapcr6_swap9_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT9)
#define _ioctrl_swapcr6_swap10_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT10)
#define _ioctrl_swapcr6_swap10_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT10)
#define _ioctrl_swapcr6_swap11_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT11)
#define _ioctrl_swapcr6_swap11_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT11)
#define _ioctrl_swapcr6_swap12_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT12)
#define _ioctrl_swapcr6_swap12_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT12)
#define _ioctrl_swapcr6_swap13_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT13)
#define _ioctrl_swapcr6_swap13_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT13)
#define _ioctrl_swapcr6_swap14_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT14)
#define _ioctrl_swapcr6_swap14_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT14)
#define _ioctrl_swapcr6_swap15_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT15)
#define _ioctrl_swapcr6_swap15_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT15)
#define _ioctrl_swapcr6_swap16_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT16)
#define _ioctrl_swapcr6_swap16_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT16)
#define _ioctrl_swapcr6_swap17_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT17)
#define _ioctrl_swapcr6_swap17_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT17)
#define _ioctrl_swapcr6_swap18_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT18)
#define _ioctrl_swapcr6_swap18_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT18)
#define _ioctrl_swapcr6_swap19_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT19)
#define _ioctrl_swapcr6_swap19_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT19)
#define _ioctrl_swapcr6_swap20_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT20)
#define _ioctrl_swapcr6_swap20_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT20)
#define _ioctrl_swapcr6_swap21_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT21)
#define _ioctrl_swapcr6_swap21_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT21)
#define _ioctrl_swapcr6_swap22_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT22)
#define _ioctrl_swapcr6_swap22_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT22)
#define _ioctrl_swapcr6_swap23_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT23)
#define _ioctrl_swapcr6_swap23_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT23)
#define _ioctrl_swapcr6_swap24_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT24)
#define _ioctrl_swapcr6_swap24_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT24)
#define _ioctrl_swapcr6_swap25_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT25)
#define _ioctrl_swapcr6_swap25_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT25)
#define _ioctrl_swapcr6_swap26_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT26)
#define _ioctrl_swapcr6_swap26_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT26)
#define _ioctrl_swapcr6_swap27_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT27)
#define _ioctrl_swapcr6_swap27_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT27)
#define _ioctrl_swapcr6_swap28_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT28)
#define _ioctrl_swapcr6_swap28_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT28)
#define _ioctrl_swapcr6_swap29_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT29)
#define _ioctrl_swapcr6_swap29_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT29)
#define _ioctrl_swapcr6_swap30_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT30)
#define _ioctrl_swapcr6_swap30_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT30)
#define _ioctrl_swapcr6_swap31_clr _bit_clr(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT31)
#define _ioctrl_swapcr6_swap31_set _bit_set(IOCTRL->SWAPCR6, IOCTRL_SWAPCR6_SWAP_BIT31)
// SWAPCR7
#define _ioctrl_swapcr7_swap0_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT0)
#define _ioctrl_swapcr7_swap0_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT0)
#define _ioctrl_swapcr7_swap1_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT1)
#define _ioctrl_swapcr7_swap1_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT1)
#define _ioctrl_swapcr7_swap2_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT2)
#define _ioctrl_swapcr7_swap2_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT2)
#define _ioctrl_swapcr7_swap3_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT3)
#define _ioctrl_swapcr7_swap3_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT3)
#define _ioctrl_swapcr7_swap4_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT4)
#define _ioctrl_swapcr7_swap4_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT4)
#define _ioctrl_swapcr7_swap5_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT5)
#define _ioctrl_swapcr7_swap5_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT5)
#define _ioctrl_swapcr7_swap6_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT6)
#define _ioctrl_swapcr7_swap6_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT6)
#define _ioctrl_swapcr7_swap7_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT7)
#define _ioctrl_swapcr7_swap7_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT7)
#define _ioctrl_swapcr7_swap8_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT8)
#define _ioctrl_swapcr7_swap8_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT8)
#define _ioctrl_swapcr7_swap9_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT9)
#define _ioctrl_swapcr7_swap9_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT9)
#define _ioctrl_swapcr7_swap10_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT10)
#define _ioctrl_swapcr7_swap10_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT10)
#define _ioctrl_swapcr7_swap11_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT11)
#define _ioctrl_swapcr7_swap11_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT11)
#define _ioctrl_swapcr7_swap12_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT12)
#define _ioctrl_swapcr7_swap12_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT12)
#define _ioctrl_swapcr7_swap13_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT13)
#define _ioctrl_swapcr7_swap13_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT13)
#define _ioctrl_swapcr7_swap14_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT14)
#define _ioctrl_swapcr7_swap14_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT14)
#define _ioctrl_swapcr7_swap15_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT15)
#define _ioctrl_swapcr7_swap15_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT15)
#define _ioctrl_swapcr7_swap16_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT16)
#define _ioctrl_swapcr7_swap16_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT16)
#define _ioctrl_swapcr7_swap17_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT17)
#define _ioctrl_swapcr7_swap17_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT17)
#define _ioctrl_swapcr7_swap18_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT18)
#define _ioctrl_swapcr7_swap18_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT18)
#define _ioctrl_swapcr7_swap19_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT19)
#define _ioctrl_swapcr7_swap19_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT19)
#define _ioctrl_swapcr7_swap20_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT20)
#define _ioctrl_swapcr7_swap20_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT20)
#define _ioctrl_swapcr7_swap21_clr _bit_clr(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT21)
#define _ioctrl_swapcr7_swap21_set _bit_set(IOCTRL->SWAPCR7, IOCTRL_SWAPCR7_SWAP_BIT21)

// SWAPCR8
#define _ioctrl_swapcr8_swap0_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT0)
#define _ioctrl_swapcr8_swap0_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT0)
#define _ioctrl_swapcr8_swap1_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT1)
#define _ioctrl_swapcr8_swap1_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT1)
#define _ioctrl_swapcr8_swap2_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT2)
#define _ioctrl_swapcr8_swap2_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT2)
#define _ioctrl_swapcr8_swap3_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT3)
#define _ioctrl_swapcr8_swap3_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT3)
#define _ioctrl_swapcr8_swap4_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT4)
#define _ioctrl_swapcr8_swap4_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT4)
#define _ioctrl_swapcr8_swap5_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT5)
#define _ioctrl_swapcr8_swap5_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT5)
#define _ioctrl_swapcr8_swap6_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT6)
#define _ioctrl_swapcr8_swap6_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT6)
#define _ioctrl_swapcr8_swap7_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT7)
#define _ioctrl_swapcr8_swap7_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT7)
#define _ioctrl_swapcr8_swap8_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT8)
#define _ioctrl_swapcr8_swap8_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT8)
#define _ioctrl_swapcr8_swap9_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT9)
#define _ioctrl_swapcr8_swap9_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT9)
#define _ioctrl_swapcr8_swap10_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT10)
#define _ioctrl_swapcr8_swap10_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT10)
#define _ioctrl_swapcr8_swap11_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT11)
#define _ioctrl_swapcr8_swap11_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT11)
#define _ioctrl_swapcr8_swap12_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT12)
#define _ioctrl_swapcr8_swap12_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT12)
#define _ioctrl_swapcr8_swap13_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT13)
#define _ioctrl_swapcr8_swap13_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT13)
#define _ioctrl_swapcr8_swap14_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT14)
#define _ioctrl_swapcr8_swap14_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT14)
#define _ioctrl_swapcr8_swap15_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT15)
#define _ioctrl_swapcr8_swap15_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT15)
#define _ioctrl_swapcr8_swap16_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT16)
#define _ioctrl_swapcr8_swap16_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT16)
#define _ioctrl_swapcr8_swap17_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT17)
#define _ioctrl_swapcr8_swap17_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT17)
#define _ioctrl_swapcr8_swap18_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT18)
#define _ioctrl_swapcr8_swap18_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT18)
#define _ioctrl_swapcr8_swap19_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT19)
#define _ioctrl_swapcr8_swap19_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT19)
#define _ioctrl_swapcr8_swap20_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT20)
#define _ioctrl_swapcr8_swap20_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT20)
#define _ioctrl_swapcr8_swap21_clr _bit_clr(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT21)
#define _ioctrl_swapcr8_swap21_set _bit_set(IOCTRL->SWAPCR8, IOCTRL_SWAPCR8_SWAP_BIT21)

 /**
  * @brief IOCTRL 模块IO驱动能力枚举定义
  * 
  */
 typedef enum
 {
    DS_2MA,
    DS_4MA,
    DS_8MA,
    DS_12MA,
} ioctrl_ds_t;

/**
 * @brief IOCTRL 模块IO转换速率枚举定义
 * 
 */
typedef enum
{
    SR_NULL = 0,
    SR_SLEW_FAST,
    SR_SLEW_SLOW,
} ioctrl_sr_t;

/**
 * @brief IOCTRL 模块IO输入类型枚举定义
 * 
 */
typedef enum
{
    IS_NULL = 0,
    IS_INPUT_CMOS,
    IS_INPUT_SCHMITT,
} ioctrl_is_t;

/**
 * @brief IOCTRL 模块IO输入模式枚举定义
 * 
 */
typedef enum
{
    PS_PULL_NULL = 0,
    PS_PULL_DOWN,
    PS_PULL_UP,
} ioctrl_ps_t;

/**
 * @brief  IOCTRL 模块IO输入使能枚举定义
 * 
 */
typedef enum
{
    IE_INPUT_NULL = 0,
    IE_INPUT_DIS,
    IE_INPUT_EN,
} ioctrl_ie_t;

/**
 * @brief IOCTRL 模块IO输入使能枚举定义
 * 
 */
typedef enum
{
    PUE_PULL_NULL = 0,
    PUE_PULL_DIS,
    PUE_PULL_EN,
} ioctrl_pue_t;

/**
 * @brief IOCTRL 模块IO输出模式枚举定义
 * 
 */
typedef enum
{
    ODE_OUTPUT_NULL = 0,
    ODE_OUTPUT_CMOS,
    ODE_OUTPUT_OPEN_DRAIN,
} ioctrl_ode_t;

/**
 * @brief IOCTRL 模块SPI模块枚举定义
 * 
 */
typedef enum
{
    IOCTRL_SPI1 = 0,
    IOCTRL_SPI2,
    IOCTRL_SPI3,
} ioctrl_spiid_t;

/**
 * @brief IOCTRL 模块I2C模块枚举定义
 * 
 */
typedef enum
{
    IOCTRL_I2C1 = 0,
    IOCTRL_I2C2,
} ioctrl_i2cid_t;

/**
 * @brief IOCTRL 模块UART模块枚举定义
 * 
 */
typedef enum
{
    IOCTRL_UART1 = 0,
    IOCTRL_UART2,
    IOCTRL_UART3,
    IOCTRL_UART4,
    IOCTRL_UART5,
    IOCTRL_UART6,
} ioctrl_uartid_t;

/**
 * @brief IOCTRL 模块SSI模块枚举定义
 * 
 */
typedef enum
{
    IOCTRL_SPIM1 = 0,
    IOCTRL_SPIM2,
    IOCTRL_SPIM3,
} ioctrl_ssiid_t;

/**
 * @brief IOCTRL 模块EPORT模块枚举定义
 * 
 */
typedef enum
{
    IOCTRL_EPORT0 = 0,
    IOCTRL_EPORT1,
    IOCTRL_EPORT2,
    IOCTRL_EPORT3,
    IOCTRL_EPORT4,
    IOCTRL_EPORT5,
    IOCTRL_EPORT6,
    IOCTRL_EPORT7,
    IOCTRL_EPORT8,
    IOCTRL_EPORT9,
} ioctrl_eportid_t;

/**
 * @brief IOCTRL 模块I2S模块枚举定义
 *
 */
typedef enum
{
    IOCTRL_I2S1 = 0,
    IOCTRL_I2S2,
} ioctrl_i2sid_t;
/**
 * @brief IOCTRL 模块SPI模块引脚枚举定义
 *
 */
typedef enum
{
    IOCTRL_SPI_SS = 0x01,
    IOCTRL_SPI_SCK = 0x02,
    IOCTRL_SPI_MISO = 0x04,
    IOCTRL_SPI_MOSI = 0x08,
} ioctrl_spipin_t;

/**
 * @brief IOCTRL 模块I2CI模块引脚枚举定义
 *
 */
typedef enum
 {
    IOCTRL_I2C_SCL = 0x01,
    IOCTRL_I2C_SDA = 0x02,
} ioctrl_i2cpin_t;
/**
 * @brief IOCTRL 模块UART模块引脚枚举定义
 *
 */
typedef enum
{
    IOCTRL_UART_TXD = 0x01,
    IOCTRL_UART_RXD = 0x02,
    IOCTRL_UART_CTS = 0x08,
} ioctrl_uartpin_t;
/**
 * @brief EPORT 模块PIN脚枚举定义
 *
  */
 typedef enum
 {
    // EPORT0
    EPORT0_PIN0 = _bit(0),  //GINT0
    EPORT0_PIN1 = _bit(1),  //GINT1
    EPORT0_PIN2 = _bit(2),  //GINT2
    EPORT0_PIN3 = _bit(3),  //GINT3
    EPORT0_PIN4 = _bit(4),  //GINT4
    EPORT0_PIN5 = _bit(5),  //GINT5
    EPORT0_PIN6 = _bit(6),  //GINT6
    EPORT0_PIN7 = _bit(7),  //GINT7
    // EPORT1
    EPORT1_PIN0 = _bit(0),  //GINT8
    EPORT1_PIN1 = _bit(1),  //GINT9
    EPORT1_PIN2 = _bit(2),  //GINT10
    EPORT1_PIN3 = _bit(3),  //GINT11
    EPORT1_PIN4 = _bit(4),  //GINT12
    EPORT1_PIN5 = _bit(5),  //GINT13
    EPORT1_PIN6 = _bit(6),  //GINT14
    EPORT1_PIN7 = _bit(7),  //GINT15
    // EPORT2
    EPORT2_PIN0 = _bit(0),  //GINT16
    EPORT2_PIN1 = _bit(1),  //GINT17
    EPORT2_PIN2 = _bit(2),  //GINT18
    EPORT2_PIN3 = _bit(3),  //GINT19
    EPORT2_PIN4 = _bit(4),  //GINT20
    EPORT2_PIN5 = _bit(5),  //GINT21
    EPORT2_PIN6 = _bit(6),  //GINT22
    EPORT2_PIN7 = _bit(7),  //GINT23
    // EPORT3
    EPORT3_PIN0 = _bit(0),  //GINT24
    EPORT3_PIN1 = _bit(1),  //GINT25
    EPORT3_PIN2 = _bit(2),  //GINT26
    EPORT3_PIN3 = _bit(3),  //GINT27
    EPORT3_PIN4 = _bit(4),  //GINT28
    EPORT3_PIN5 = _bit(5),  //GINT29
    EPORT3_PIN6 = _bit(6),  //GINT30
    EPORT3_PIN7 = _bit(7),  //GINT31
    // EPORT4
    EPORT4_PIN0 = _bit(0),  //GINT32
    EPORT4_PIN1 = _bit(1),  //GINT33
    EPORT4_PIN2 = _bit(2),  //GINT34
    EPORT4_PIN3 = _bit(3),  //GINT35
    EPORT4_PIN4 = _bit(4),  //GINT36
    EPORT4_PIN5 = _bit(5),  //GINT37
    EPORT4_PIN6 = _bit(6),  //GINT38
    EPORT4_PIN7 = _bit(7),  //GINT39
    // EPORT5
    EPORT5_PIN0 = _bit(0),  //GINT40
    EPORT5_PIN1 = _bit(1),  //GINT41
    EPORT5_PIN2 = _bit(2),  //GINT42
    EPORT5_PIN3 = _bit(3),  //GINT43
    EPORT5_PIN4 = _bit(4),  //GINT44
    EPORT5_PIN5 = _bit(5),  //GINT45
    EPORT5_PIN6 = _bit(6),  //GINT46
    EPORT5_PIN7 = _bit(7),  //GINT47
    // EPORT6
    EPORT6_PIN0 = _bit(0),  //GINT48
    EPORT6_PIN1 = _bit(1),  //GINT49
    EPORT6_PIN2 = _bit(2),  //GINT50
    EPORT6_PIN3 = _bit(3),  //GINT51
    EPORT6_PIN4 = _bit(4),  //GINT52
    EPORT6_PIN5 = _bit(5),  //GINT53
    EPORT6_PIN6 = _bit(6),  //GINT54
    EPORT6_PIN7 = _bit(7),  //GINT55
    // EPORT7
    EPORT7_PIN0 = _bit(0),  //GINT56
    EPORT7_PIN1 = _bit(1),  //GINT57
    EPORT7_PIN2 = _bit(2),  //GINT58
    EPORT7_PIN3 = _bit(3),  //GINT59
    EPORT7_PIN4 = _bit(4),  //GINT60
    EPORT7_PIN5 = _bit(5),  //GINT61
    EPORT7_PIN6 = _bit(6),  //GINT62
    EPORT7_PIN7 = _bit(7),  //GINT63
    
    // EPORT8
    EPORT8_PIN0 = _bit(0),  //GINT64
    EPORT8_PIN1 = _bit(1),  //GINT65
    EPORT8_PIN2 = _bit(2),  //GINT66
    EPORT8_PIN3 = _bit(3),  //GINT67
    EPORT8_PIN4 = _bit(4),  //GINT68
    EPORT8_PIN5 = _bit(5),  //GINT69
    EPORT8_PIN6 = _bit(6),  //GINT70
    EPORT8_PIN7 = _bit(7),  //GINT71
    // EPORT9
    EPORT9_PIN0 = _bit(0),  //GINT72
    EPORT9_PIN1 = _bit(1),  //GINT73
    EPORT9_PIN2 = _bit(2),  //GINT74
    EPORT9_PIN3 = _bit(3),  //GINT75
    EPORT9_PIN4 = _bit(4),  //GINT76
    EPORT9_PIN5 = _bit(5),  //GINT77
    EPORT9_PIN6 = _bit(6),  //GINT78
    EPORT9_PIN7 = _bit(7),  //GINT79
} eport_pin_t;
/**
 * @brief IOCTRL 模块SSI模块引脚枚举定义
 *
 */
typedef enum
{
    IOCTRL_SPIM_SS = 0x01,
    IOCTRL_SPIM_SCK = 0x02,
    IOCTRL_SPIM_D0 = 0x04,
    IOCTRL_SPIM_D1 = 0x08,
    IOCTRL_SPIM_D2 = 0x10,
    IOCTRL_SPIM_D3 = 0x20,
} ioctrl_ssibit_t;
/**
 * @brief IOCTRL 模块PIN脚方向枚举定义
 *
 */
typedef enum
{
    PIN_INPUT = 0,
    PIN_OUTPUT,
} ioctrl_pindir_t;

/**
 * @brief IOCTRL 模块I2S引脚枚举定义
 *
 */
typedef enum
{
    IOCTRL_I2S_SD = 0x01,
    IOCTRL_I2S_SCLK = 0x02,
} ioctrl_i2spin_t;
/**
 * @brief IOCTRL 模块PWMT引脚枚举定义
 *
 */
typedef enum
{
    IOCTRL_PWMT_ETR = 0x00,
    IOCTRL_PWMT_BRK,
} ioctrl_pwmtpin_t;
/**
 * @brief IOCTRL 模块CAN引脚枚举定义
 *
 */
typedef enum
{
    IOCTRL_CAN_RX = 0x00,
    IOCTRL_CAN_TX,
} ioctrl_canpin_t;

// 函数声明
void drv_ioctrl_setspiie(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_ie_t ie);
void drv_ioctrl_setspips(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_ps_t ps);
void drv_ioctrl_setspids(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_ds_t ds);
void drv_ioctrl_setspisr(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_sr_t sr);
void drv_ioctrl_setspiis(ioctrl_spiid_t spiid, ioctrl_spipin_t spipin, ioctrl_is_t is);
void drv_ioctrl_seti2cds(ioctrl_ds_t ds);
void drv_ioctrl_seti2csr(ioctrl_sr_t sr);
void drv_ioctrl_seti2cis(ioctrl_is_t is);
void drv_ioctrl_seti2cps(ioctrl_i2cid_t i2cid, ioctrl_i2cpin_t i2cpins, ioctrl_ps_t ps);
void drv_ioctrl_seti2cie(ioctrl_i2cid_t i2cid, ioctrl_i2cpin_t i2cpins, ioctrl_ie_t ie);
void drv_ioctrl_setuartds(ioctrl_ds_t ds);
void drv_ioctrl_setuartsr(ioctrl_sr_t sr);
void drv_ioctrl_setuartis(ioctrl_is_t is);
void drv_ioctrl_setuartps(ioctrl_uartid_t uartid, ioctrl_uartpin_t uartpin, ioctrl_ps_t ie);
void drv_ioctrl_seteportds(ioctrl_eportid_t id,eport_pin_t pins, ioctrl_ds_t ds);
void drv_ioctrl_seteportsr(ioctrl_eportid_t id,eport_pin_t pins, ioctrl_sr_t sr);
void drv_ioctrl_seteportps(ioctrl_eportid_t id,eport_pin_t pins, ioctrl_ps_t ps);
void drv_ioctrl_setssids(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ds_t ds);
void drv_ioctrl_setssisr(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_sr_t sr);
void drv_ioctrl_setssiie(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ie_t ie);
void drv_ioctrl_setssiide(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ode_t ode);
void drv_ioctrl_setssips(ioctrl_ssiid_t ssiid, ioctrl_ssibit_t ssipins, ioctrl_ps_t ps);
void drv_ioctrl_seti2sds(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spin, ioctrl_ds_t ds);
void drv_ioctrl_seti2ssr(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spin, ioctrl_sr_t sr);
void drv_ioctrl_seti2sie(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spins, ioctrl_ie_t ie);
void drv_ioctrl_seti2sps(ioctrl_i2sid_t i2sid, ioctrl_i2spin_t i2spins, ioctrl_ps_t ps);
void drv_ioctrl_setsdhpue(ioctrl_pue_t pue);

#ifdef __cplusplus
}
#endif

#endif
