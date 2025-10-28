/**
 * @file interrupt.c
 * @author Product application department
 * @brief  INTERRUPT 中断配置文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */
#define __INTERRUPT__
#ifdef __INTERRUPT__

// 头文件包含
#include "interrupt.h"
#include "spi_hal.h"
#include "dma_hal.h"
#include "freertos_test.h"
#include "can_hal.h"

/**
 * @brief 中断服务入口函数与模块对应表
OTP_IRQHandler
PMU_IRQHandler
TC_IRQHandler
PIT1_IRQHandler
PIT2_IRQHandler
TC2_IRQHandler
TC3_IRQHandler
DMA1_IRQHandler
DMA2_IRQHandler
TRNG_IRQHandler
SEC_FD_IRQHandler
CPM_IRQHandler
PMU_RTC_IRQHandler
SD_IRQHandler
DMA2D_IRQHandler
AESSM4_IRQHandler
QADC_IRQHandler
DAC_IRQHandler
UART5_IRQHandler
USB_IRQHandler
UART6_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
SPIM1_IRQHandler
SPIM2_IRQHandler
SPIM3_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
PSRAM_IRQHandler
GMAC_IRQHandler
I2C1_IRQHandler
EPORT0_0_IRQHandler
EPORT0_1_IRQHandler
EPORT0_2_IRQHandler
EPORT0_3_IRQHandler
EPORT0_4_IRQHandler
EPORT0_5_IRQHandler
EPORT0_6_IRQHandler
EPORT0_7_IRQHandler
EPORT1_0_IRQHandler
EPORT1_1_IRQHandler
EPORT1_2_IRQHandler
EPORT1_3_IRQHandler
EPORT1_4_IRQHandler
EPORT1_5_IRQHandler
EPORT1_6_IRQHandler
EPORT1_7_IRQHandler
SSISLV1_IRQHandler
I2C2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
LCDC_ROT_ERRORI_IRQHandler
CAN1_BUF00_03_IRQHandler
CAN1_BUF04_07_IRQHandler
CAN1_BUF08_11_IRQHandler
CAN1_BUF12_15_IRQHandler
CAN1_BUF16_31_IRQHandler
CAN1_BUF32_63_IRQHandler
BOFF_TRWARN_IRQHandler
CAN1_ERR_IRQHandler
CAN2_BUF00_03_IRQHandler
CAN2_BUF04_07_IRQHandler
CAN2_BUF08_11_IRQHandler
CAN2_BUF12_15_IRQHandler
CAN2_BUF16_31_IRQHandler
CAN2_BUF32_63_IRQHandler
BOFF2_TRWARN_IRQHandler
CAN2_ERR_IRQHandler
I2S1_IRQHandler
I2S2_IRQHandler
LCDC_CRC_ERROR_IRQHandler
LCDC_REG_RELOAD_IRQHandler
PWMT1_IRQHandler
PWMT2_IRQHandler
PWMT3_IRQHandler
LCDC_BUS_ERROR_IRQHandler
LCDC_FIFO_UNDERRUN_IRQHandler
LCDC_FIFO_WARN_IRQHandler
LCDC_IRQ_SCANLINE_IRQHandler
EPORT2_0_IRQHandler
EPORT2_1_IRQHandler
EPORT2_2_IRQHandler
EPORT2_3_IRQHandler
EPORT2_4_IRQHandler
EPORT2_5_IRQHandler
EPORT2_6_IRQHandler
EPORT2_7_IRQHandler
EPORT3_0_IRQHandler
EPORT3_1_IRQHandler
EPORT3_2_IRQHandler
EPORT3_3_IRQHandler
EPORT3_4_IRQHandler
EPORT3_5_IRQHandler
EPORT3_6_IRQHandler
EPORT3_7_IRQHandler
EPORT4_0_IRQHandler
EPORT4_1_IRQHandler
EPORT4_2_IRQHandler
EPORT4_3_IRQHandler
EPORT4_4_IRQHandler
EPORT4_5_IRQHandler
EPORT4_6_IRQHandler
EPORT4_7_IRQHandler
EPORT5_0_IRQHandler
EPORT5_1_IRQHandler
EPORT5_2_IRQHandler
EPORT5_3_IRQHandler
EPORT5_4_IRQHandler
EPORT5_5_IRQHandler
EPORT5_6_IRQHandler
EPORT5_7_IRQHandler
EPORT6_0_IRQHandler
EPORT6_1_IRQHandler
EPORT6_2_IRQHandler
EPORT6_3_IRQHandler
EPORT6_4_IRQHandler
EPORT6_5_IRQHandler
EPORT6_6_IRQHandler
EPORT6_7_IRQHandler
EPORT7_0_IRQHandler
EPORT7_1_IRQHandler
EPORT7_2_IRQHandler
EPORT7_3_IRQHandler
EPORT7_4_IRQHandler
EPORT7_5_IRQHandler
EPORT7_6_IRQHandler
EPORT7_7_IRQHandler
EPORT8_0_IRQHandler
EPORT8_1_IRQHandler
EPORT8_2_IRQHandler
EPORT8_3_IRQHandler
EPORT8_4_IRQHandler
EPORT8_5_IRQHandler
EPORT8_6_IRQHandler
EPORT8_7_IRQHandler
EPORT9_0_IRQHandler
EPORT9_1_IRQHandler
EPORT9_2_IRQHandler
EPORT9_3_IRQHandler
EPORT9_4_IRQHandler
EPORT9_5_IRQHandler
EPORT9_6_IRQHandler
EPORT9_7_IRQHandler
 */

void (*OTP_IRQHandler_Callback)(void);
void (*PMU_IRQHandler_Callback)(void);
void (*TC1_IRQHandler_Callback)(void);
void (*PIT1_IRQHandler_Callback)(void);
void (*PIT2_IRQHandler_Callback)(void);
void (*TC2_IRQHandler_Callback)(void);
void (*TC3_IRQHandler_Callback)(void);
void (*DMA1_IRQHandler_Callback)(void);
void (*DMA2_IRQHandler_Callback)(void);
void (*TRNG_IRQHandler_Callback)(void);
void (*SEC_FD_IRQHandler_Callback)(void);
void (*CPM_IRQHandler_Callback)(void);
void (*PMU_RTC_IRQHandler_Callback)(void);
void (*SD_IRQHandler_Callback)(void);
void (*DMA2D_IRQHandler_Callback)(void);
void (*AESSM4_IRQHandler_Callback)(void);
void (*QADC_IRQHandler_Callback)(void);
void (*DAC_IRQHandler_Callback)(void);
void (*UART5_IRQHandler_Callback)(void);
void (*USB_IRQHandler_Callback)(void);
void (*UART6_IRQHandler_Callback)(void);
void (*SPI1_IRQHandler_Callback)(void);
void (*SPI2_IRQHandler_Callback)(void);
void (*SPI3_IRQHandler_Callback)(void);
void (*SPIM1_IRQHandler_Callback)(void);
void (*SPIM2_IRQHandler_Callback)(void);
void (*SPIM3_IRQHandler_Callback)(void);
void (*UART1_IRQHandler_Callback)(void);
void (*UART2_IRQHandler_Callback)(void);
void (*PSRAM_IRQHandler_Callback)(void);
void (*GMAC_IRQHandler_Callback)(void);
void (*I2C1_IRQHandler_Callback)(void);
void (*EPORT0_0_IRQHandler_Callback)(void);
void (*EPORT0_1_IRQHandler_Callback)(void);
void (*EPORT0_2_IRQHandler_Callback)(void);
void (*EPORT0_3_IRQHandler_Callback)(void);
void (*EPORT0_4_IRQHandler_Callback)(void);
void (*EPORT0_5_IRQHandler_Callback)(void);
void (*EPORT0_6_IRQHandler_Callback)(void);
void (*EPORT0_7_IRQHandler_Callback)(void);
void (*EPORT1_0_IRQHandler_Callback)(void);
void (*EPORT1_1_IRQHandler_Callback)(void);
void (*EPORT1_2_IRQHandler_Callback)(void);
void (*EPORT1_3_IRQHandler_Callback)(void);
void (*EPORT1_4_IRQHandler_Callback)(void);
void (*EPORT1_5_IRQHandler_Callback)(void);
void (*EPORT1_6_IRQHandler_Callback)(void);
void (*EPORT1_7_IRQHandler_Callback)(void);
void (*SSISLV_IRQHandler_Callback)(void);
void (*I2C2_IRQHandler_Callback)(void);
void (*AXIDMA_IRQHandler_Callback)(void);
void (*UART3_IRQHandler_Callback)(void);
void (*UART4_IRQHandler_Callback)(void);
void (*LCDC_ROT_ERROR_IRQHandler_Callback)(void);
void (*CAN1_BUF00_03_IRQHandler_Callback)(void);
void (*CAN1_BUF04_07_IRQHandler_Callback)(void);
void (*CAN1_BUF08_11_IRQHandler_Callback)(void);
void (*CAN1_BUF12_15_IRQHandler_Callback)(void);
void (*CAN1_BUF16_31_IRQHandler_Callback)(void);
void (*CAN1_BUF32_63_IRQHandler_Callback)(void);
void (*BOFF_TRWARN_IRQHandler_Callback)(void);
void (*CAN1_ERR_IRQHandler_Callback)(void);
void (*CAN2_BUF00_03_IRQHandler_Callback)(void);
void (*CAN2_BUF04_07_IRQHandler_Callback)(void);
void (*CAN2_BUF08_11_IRQHandler_Callback)(void);
void (*CAN2_BUF12_15_IRQHandler_Callback)(void);
void (*CAN2_BUF16_31_IRQHandler_Callback)(void);
void (*CAN2_BUF32_63_IRQHandler_Callback)(void);
void (*BOFF2_TRWARN_IRQHandler_Callback)(void);
void (*CAN2_ERR_IRQHandler_Callback)(void);
void (*I2S1_IRQHandler_Callback)(void);
void (*I2S2_IRQHandler_Callback)(void);
void (*LCDC_CRC_ERROR_IRQHandler_Callback)(void);
void (*LCDC_REG_RELOAD_IRQHandler_Callback)(void);
void (*PWMT1_IRQHandler_Callback)(void);
void (*PWMT2_IRQHandler_Callback)(void);
void (*PWMT3_IRQHandler_Callback)(void);
void (*LCDC_BUS_ERROR_IRQHandler_Callback)(void);
void (*LCDC_FIFO_UNDERRUN_IRQHandler_Callback)(void);
void (*LCDC_FIFO_WARN_IRQHandler_Callback)(void);
void (*LCDC_IRQ_SCANLINE_IRQHandler_Callback)(void);
void (*IMGAGE_DECODER_IRQHandler_Callback)(void);
void (*EPORT2_0_IRQHandler_Callback)(void);
void (*EPORT2_1_IRQHandler_Callback)(void);
void (*EPORT2_2_IRQHandler_Callback)(void);
void (*EPORT2_3_IRQHandler_Callback)(void);
void (*EPORT2_4_IRQHandler_Callback)(void);
void (*EPORT2_5_IRQHandler_Callback)(void);
void (*EPORT2_6_IRQHandler_Callback)(void);
void (*EPORT2_7_IRQHandler_Callback)(void);
void (*EPORT3_0_IRQHandler_Callback)(void);
void (*EPORT3_1_IRQHandler_Callback)(void);
void (*EPORT3_2_IRQHandler_Callback)(void);
void (*EPORT3_3_IRQHandler_Callback)(void);
void (*EPORT3_4_IRQHandler_Callback)(void);
void (*EPORT3_5_IRQHandler_Callback)(void);
void (*EPORT3_6_IRQHandler_Callback)(void);
void (*EPORT3_7_IRQHandler_Callback)(void);
void (*EPORT4_0_IRQHandler_Callback)(void);
void (*EPORT4_1_IRQHandler_Callback)(void);
void (*EPORT4_2_IRQHandler_Callback)(void);
void (*EPORT4_3_IRQHandler_Callback)(void);
void (*EPORT4_4_IRQHandler_Callback)(void);
void (*EPORT4_5_IRQHandler_Callback)(void);
void (*EPORT4_6_IRQHandler_Callback)(void);
void (*EPORT4_7_IRQHandler_Callback)(void);
void (*EPORT5_0_IRQHandler_Callback)(void);
void (*EPORT5_1_IRQHandler_Callback)(void);
void (*EPORT5_2_IRQHandler_Callback)(void);
void (*EPORT5_3_IRQHandler_Callback)(void);
void (*EPORT5_4_IRQHandler_Callback)(void);
void (*EPORT5_5_IRQHandler_Callback)(void);
void (*EPORT5_6_IRQHandler_Callback)(void);
void (*EPORT5_7_IRQHandler_Callback)(void);
void (*EPORT6_0_IRQHandler_Callback)(void);
void (*EPORT6_1_IRQHandler_Callback)(void);
void (*EPORT6_2_IRQHandler_Callback)(void);
void (*EPORT6_3_IRQHandler_Callback)(void);
void (*EPORT6_4_IRQHandler_Callback)(void);
void (*EPORT6_5_IRQHandler_Callback)(void);
void (*EPORT6_6_IRQHandler_Callback)(void);
void (*EPORT6_7_IRQHandler_Callback)(void);
void (*EPORT7_0_IRQHandler_Callback)(void);
void (*EPORT7_1_IRQHandler_Callback)(void);
void (*EPORT7_2_IRQHandler_Callback)(void);
void (*EPORT7_3_IRQHandler_Callback)(void);
void (*EPORT7_4_IRQHandler_Callback)(void);
void (*EPORT7_5_IRQHandler_Callback)(void);
void (*EPORT7_6_IRQHandler_Callback)(void);
void (*EPORT7_7_IRQHandler_Callback)(void);
void (*EPORT8_0_IRQHandler_Callback)(void);
void (*EPORT8_1_IRQHandler_Callback)(void);
void (*EPORT8_2_IRQHandler_Callback)(void);
void (*EPORT8_3_IRQHandler_Callback)(void);
void (*EPORT8_4_IRQHandler_Callback)(void);
void (*EPORT8_5_IRQHandler_Callback)(void);
void (*EPORT8_6_IRQHandler_Callback)(void);
void (*EPORT8_7_IRQHandler_Callback)(void);
void (*EPORT9_0_IRQHandler_Callback)(void);
void (*EPORT9_1_IRQHandler_Callback)(void);
void (*EPORT9_2_IRQHandler_Callback)(void);
void (*EPORT9_3_IRQHandler_Callback)(void);
void (*EPORT9_4_IRQHandler_Callback)(void);
void (*EPORT9_5_IRQHandler_Callback)(void);
void (*EPORT9_6_IRQHandler_Callback)(void);
void (*EPORT9_7_IRQHandler_Callback)(void);
void (*SysTick_IRQHandler_Callback)(void);

/**
 * @brief EFLASH 中断服务入口函数
 */
void OTP_IRQHandler(void)
{
    OTP_IRQHandler_Callback();
}

/**
 * @brief PMU 中断服务入口函数
 */
void PMU_IRQHandler(void)
{
    PMU_IRQHandler_Callback();
}

/**
 * @brief TC 中断服务入口函数
 */
void TC1_IRQHandler(void)
{
    TC1_IRQHandler_Callback();
}

/**
 * @brief PIT1 中断服务入口函数
 * @note 32bits 可编程中断定时器
 */
void PIT1_IRQHandler(void)
{
    PIT1_IRQHandler_Callback();
}

/**
 * @brief PIT2 中断服务入口函数
 * @note 32bits 可编程中断定时器
 */
void PIT2_IRQHandler(void)
{
    PIT2_IRQHandler_Callback();
}

/**
 * @brief TC2 中断服务入口函数
 */
void TC2_IRQHandler(void)
{
    TC2_IRQHandler_Callback();
}

/**
 * @brief TC3 中断服务入口函数
 */
void TC3_IRQHandler(void)
{
    TC3_IRQHandler_Callback();
}

/**
 * @brief DMA1 中断服务入口函数
 */
void DMA1_IRQHandler(void)
{
    DMA1_IRQHandler_Callback();
}

/**
 * @brief DMA2 中断服务入口函数
 */
void DMA2_IRQHandler(void)
{
    DMA2_IRQHandler_Callback();
}

/**
 * @brief TRNG 中断服务入口函数
 */
void TRNG_IRQHandler(void)
{
    TRNG_IRQHandler_Callback();
}

/**
 * @brief SEC_FD 中断服务入口函数
 */
void SEC_FD_IRQHandler(void)
{
    SEC_FD_IRQHandler_Callback();
}

/**
 * @brief ASYNC_TIMER 中断服务入口函数
 */
void CPM_IRQHandler(void)
{
    CPM_IRQHandler_Callback();
}

/**
 * @brief RSA 中断服务入口函数
 */
void PMU_RTC_IRQHandler(void)
{
    PMU_RTC_IRQHandler_Callback();
}

/**
 * @brief SHA 中断服务入口函数
 */
void SD_IRQHandler(void)
{
    SD_IRQHandler_Callback();
}

/**
 * @brief AES 中断服务入口函数
 */
void DMA2D_IRQHandler(void)
{
    DMA2D_IRQHandler_Callback();
}

/**
 * @brief SMS4 中断服务入口函数
 */
void AESSM4_IRQHandler(void)
{
    AESSM4_IRQHandler_Callback();
}

/**
 * @brief QADC 中断服务入口函数
 */
void QADC_IRQHandler(void)
{
    QADC_IRQHandler_Callback();
}

/**
 * @brief DAC 中断服务入口函数
 */
void DAC_IRQHandler(void)
{
    DAC_IRQHandler_Callback();
}

/**
 * @brief UART5 中断服务入口函数
 */
void UART5_IRQHandler(void)
{
    UART5_IRQHandler_Callback();
}

/**
 * @brief USB 中断服务入口函数
 */
void USB_IRQHandler(void)
{
    USB_IRQHandler_Callback();
}

/**
 * @brief UART6 中断服务入口函数
 */
void UART6_IRQHandler(void)
{

    UART6_IRQHandler_Callback();
}

/**
 * @brief SPI1 中断服务入口函数
 */
void SPI1_IRQHandler(void)
{
    SPI1_IRQHandler_Callback();
}

/**
 * @brief SPI2 中断服务入口函数
 */
void SPI2_IRQHandler(void)
{
    SPI2_IRQHandler_Callback();
}

/**
 * @brief SPI3 中断服务入口函数
 */
void SPI3_IRQHandler(void)
{
    SPI3_IRQHandler_Callback();
}

/**
 * @brief SPIM1 中断服务入口函数
 */
void SPIM1_IRQHandler(void)
{
    SPIM1_IRQHandler_Callback();
}

/**
 * @brief SPIM2 中断服务入口函数
 */
void SPIM2_IRQHandler(void)
{
    SPIM2_IRQHandler_Callback();
}

/**
 * @brief SPIM3 中断服务入口函数
 */
void SPIM3_IRQHandler(void)
{
    SPIM3_IRQHandler_Callback();
}

/**
 * @brief UART1 中断服务入口函数
 */
void UART1_IRQHandler(void)
{
    UART1_IRQHandler_Callback();
}

/**
 * @brief UART2 中断服务入口函数
 */
void UART2_IRQHandler(void)
{
    UART2_IRQHandler_Callback();
}

/**
 * @brief PSRAM 中断服务入口函数
 */
void PSRAM_IRQHandler(void)
{
    PSRAM_IRQHandler_Callback();
}

/**
 * @brief GMAC 中断服务入口函数
 */
void GMAC_IRQHandler(void)
{
    GMAC_IRQHandler_Callback();
}

/**
 * @brief I2C1 中断服务入口函数
 */
void I2C1_IRQHandler(void)
{
    I2C1_IRQHandler_Callback();
}

/**
 * @brief EPORT 中断服务入口函数
 */
void EPORT0_0_IRQHandler(void)
{
    EPORT0_0_IRQHandler_Callback();
}
void EPORT0_1_IRQHandler(void)
{
    EPORT0_1_IRQHandler_Callback();
}
void EPORT0_2_IRQHandler(void)
{
    EPORT0_2_IRQHandler_Callback();
}
void EPORT0_3_IRQHandler(void)
{
    EPORT0_3_IRQHandler_Callback();
}
void EPORT0_4_IRQHandler(void)
{
    EPORT0_4_IRQHandler_Callback();
}
void EPORT0_5_IRQHandler(void)
{
    EPORT0_5_IRQHandler_Callback();
}
void EPORT0_6_IRQHandler(void)
{
    EPORT0_6_IRQHandler_Callback();
}
void EPORT0_7_IRQHandler(void)
{
    EPORT0_7_IRQHandler_Callback();
}
void EPORT1_0_IRQHandler(void)
{
    EPORT1_0_IRQHandler_Callback();
}
void EPORT1_1_IRQHandler(void)
{
    EPORT1_1_IRQHandler_Callback();
}
void EPORT1_2_IRQHandler(void)
{
    EPORT1_2_IRQHandler_Callback();
}
void EPORT1_3_IRQHandler(void)
{
    EPORT1_3_IRQHandler_Callback();
}
void EPORT1_4_IRQHandler(void)
{
    EPORT1_4_IRQHandler_Callback();
}
void EPORT1_5_IRQHandler(void)
{
    EPORT1_5_IRQHandler_Callback();
}
void EPORT1_6_IRQHandler(void)
{
    EPORT1_6_IRQHandler_Callback();
}
void EPORT1_7_IRQHandler(void)
{
    EPORT1_7_IRQHandler_Callback();
}
/**
 * @brief SSISLV 中断服务入口函数
 */
void SSISLV_IRQHandler(void)
{
    SSISLV_IRQHandler_Callback();
}

/**
 * @brief I2C2 中断服务入口函数
 */
void I2C2_IRQHandler(void)
{
    I2C2_IRQHandler_Callback();
}

/**
 * @brief AXIDMA 中断服务入口函数
 * 
 */
void AXIDMA_IRQHandler(void)
{
    AXIDMA_IRQHandler_Callback();
}

/**
 * @brief UART3 中断服务入口函数
 */
void UART3_IRQHandler(void)
{

    UART3_IRQHandler_Callback();
}

/**
 * @brief UART4 中断服务入口函数
 */
void UART4_IRQHandler(void)
{

    UART4_IRQHandler_Callback();
}
/**
 * @brief LCDC_ROT_ERROR 中断服务入口函数
 */
void LCDC_ROT_ERROR_IRQHandler(void)
{
    LCDC_ROT_ERROR_IRQHandler_Callback();
}

/**
 * @brief IMGAGE_DECODER 中断服务入口函数
 * 
 */
void IMGAGE_DECODER_IRQHandler(void)
{
    IMGAGE_DECODER_IRQHandler_Callback();
}

/**
 * @brief CAN 中断服务入口函数
 *
 */
void CAN1_BUF00_03_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN1_BUF04_07_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN1_BUF08_11_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN1_BUF12_15_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN1_BUF16_31_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN1_BUF32_63_IRQHandler(void)
{
    hal_can_irqhandle();
}

void BOFF_TRWARN_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN1_ERR_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN2_BUF00_03_IRQHandler(void)
{
    hal_can_irqhandle();
}

void CAN2_BUF04_07_IRQHandler(void)
{
    CAN2_BUF04_07_IRQHandler_Callback();
}

void CAN2_BUF08_11_IRQHandler(void)
{
    CAN2_BUF08_11_IRQHandler_Callback();
}

void CAN2_BUF12_15_IRQHandler(void)
{
    CAN2_BUF12_15_IRQHandler_Callback();
}

void CAN2_BUF16_31_IRQHandler(void)
{
    CAN2_BUF16_31_IRQHandler_Callback();
}

void CAN2_BUF32_63_IRQHandler(void)
{
    CAN2_BUF32_63_IRQHandler_Callback();
}

void BOFF2_TRWARN_IRQHandler(void)
{
    BOFF2_TRWARN_IRQHandler_Callback();
}

void CAN2_ERR_IRQHandler(void)
{
    CAN2_ERR_IRQHandler_Callback();
}

/**
 * @brief I2S1 中断服务入口函数
 * @param
 */
void I2S1_IRQHandler(void)
{
    I2S1_IRQHandler_Callback();
}

/**
 * @brief I2S2 中断服务入口函数
 * @param
 */
void I2S2_IRQHandler(void)
{
    I2S2_IRQHandler_Callback();
}

/**
 * @brief LCDC_CRC_ERROR 中断服务入口函数
 */
void LCDC_CRC_ERROR_IRQHandler(void)
{
    LCDC_CRC_ERROR_IRQHandler_Callback();
}

/**
 * @brief LCDC_REG_RELOAD 中断服务入口函数
 */
void LCDC_REG_RELOAD_IRQHandler(void)
{
    LCDC_REG_RELOAD_IRQHandler_Callback();
}

/**
 * @brief PWMT1 中断服务入口函数
 */
void PWMT1_IRQHandler(void)
{
    PWMT1_IRQHandler_Callback();
}

/**
 * @brief PWMT2 中断服务入口函数
 */
void PWMT2_IRQHandler(void)
{
    PWMT2_IRQHandler_Callback();
}

/**
 * @brief PWMT3 中断服务入口函数
 */
void PWMT3_IRQHandler(void)
{
    PWMT3_IRQHandler_Callback();
}

/**
 * @brief LCDC_BUS_ERROR 中断服务入口函数
 */
void LCDC_BUS_ERROR_IRQHandler(void)
{
    LCDC_BUS_ERROR_IRQHandler_Callback();
}

/**
 * @brief LCDC_FIFO_UNDERRUN 中断服务入口函数
 */
void LCDC_FIFO_UNDERRUN_IRQHandler(void)
{
    LCDC_FIFO_UNDERRUN_IRQHandler_Callback();
}

/**
 * @brief LCDC_FIFO_WARN中断服务入口函数
 */
void LCDC_FIFO_WARN_IRQHandler(void)
{
    LCDC_FIFO_WARN_IRQHandler_Callback();
}

/**
 * @brief LCDC_IRQ_SCANLINE中断服务入口函数
 */
void LCDC_IRQ_SCANLINE_IRQHandler(void)
{
    LCDC_IRQ_SCANLINE_IRQHandler_Callback();
}

/**
 * @brief EPORT 中断服务入口函数
 */
void EPORT2_0_IRQHandler(void)
{
    EPORT2_0_IRQHandler_Callback();
}
void EPORT2_1_IRQHandler(void)
{
    EPORT2_1_IRQHandler_Callback();
}
void EPORT2_2_IRQHandler(void)
{
    EPORT2_2_IRQHandler_Callback();
}
void EPORT2_3_IRQHandler(void)
{
    EPORT2_3_IRQHandler_Callback();
}
void EPORT2_4_IRQHandler(void)
{
    EPORT2_4_IRQHandler_Callback();
}
void EPORT2_5_IRQHandler(void)
{
    EPORT2_5_IRQHandler_Callback();
}
void EPORT2_6_IRQHandler(void)
{
    EPORT2_6_IRQHandler_Callback();
}
void EPORT2_7_IRQHandler(void)
{
    EPORT2_7_IRQHandler_Callback();
}
void EPORT3_0_IRQHandler(void)
{
    EPORT3_0_IRQHandler_Callback();
}
void EPORT3_1_IRQHandler(void)
{
    EPORT3_1_IRQHandler_Callback();
}
void EPORT3_2_IRQHandler(void)
{
    EPORT3_2_IRQHandler_Callback();
}
void EPORT3_3_IRQHandler(void)
{
    EPORT3_3_IRQHandler_Callback();
}
void EPORT3_4_IRQHandler(void)
{
    EPORT3_4_IRQHandler_Callback();
}
void EPORT3_5_IRQHandler(void)
{
    EPORT3_5_IRQHandler_Callback();
}
void EPORT3_6_IRQHandler(void)
{
    EPORT3_6_IRQHandler_Callback();
}
void EPORT3_7_IRQHandler(void)
{
    EPORT3_7_IRQHandler_Callback();
}
void EPORT4_0_IRQHandler(void)
{
    EPORT4_0_IRQHandler_Callback();
}
void EPORT4_1_IRQHandler(void)
{
    EPORT4_1_IRQHandler_Callback();
}
void EPORT4_2_IRQHandler(void)
{
    EPORT4_2_IRQHandler_Callback();
}
void EPORT4_3_IRQHandler(void)
{
    EPORT4_3_IRQHandler_Callback();
}
void EPORT4_4_IRQHandler(void)
{
    EPORT4_4_IRQHandler_Callback();
}
void EPORT4_5_IRQHandler(void)
{
    EPORT4_5_IRQHandler_Callback();
}
void EPORT4_6_IRQHandler(void)
{
    EPORT4_6_IRQHandler_Callback();
}
void EPORT4_7_IRQHandler(void)
{
    EPORT4_7_IRQHandler_Callback();
}
void EPORT5_0_IRQHandler(void)
{
    EPORT5_0_IRQHandler_Callback();
}
void EPORT5_1_IRQHandler(void)
{
    EPORT5_1_IRQHandler_Callback();
}
void EPORT5_2_IRQHandler(void)
{
    EPORT5_2_IRQHandler_Callback();
}
void EPORT5_3_IRQHandler(void)
{
    EPORT5_3_IRQHandler_Callback();
}
void EPORT5_4_IRQHandler(void)
{
    EPORT5_4_IRQHandler_Callback();
}
void EPORT5_5_IRQHandler(void)
{
    EPORT5_5_IRQHandler_Callback();
}
void EPORT5_6_IRQHandler(void)
{
    EPORT5_6_IRQHandler_Callback();
}
void EPORT5_7_IRQHandler(void)
{
    EPORT5_7_IRQHandler_Callback();
}
void EPORT6_0_IRQHandler(void)
{
    EPORT6_0_IRQHandler_Callback();
}
void EPORT6_1_IRQHandler(void)
{
    EPORT6_1_IRQHandler_Callback();
}
void EPORT6_2_IRQHandler(void)
{
    EPORT6_2_IRQHandler_Callback();
}
void EPORT6_3_IRQHandler(void)
{
    EPORT6_3_IRQHandler_Callback();
}
void EPORT6_4_IRQHandler(void)
{
    EPORT6_4_IRQHandler_Callback();
}
void EPORT6_5_IRQHandler(void)
{
    EPORT6_5_IRQHandler_Callback();
}
void EPORT6_6_IRQHandler(void)
{
    EPORT6_6_IRQHandler_Callback();
}
void EPORT6_7_IRQHandler(void)
{
    EPORT6_7_IRQHandler_Callback();
}
void EPORT7_0_IRQHandler(void)
{
    EPORT7_0_IRQHandler_Callback();
}
void EPORT7_1_IRQHandler(void)
{
    EPORT7_1_IRQHandler_Callback();
}
void EPORT7_2_IRQHandler(void)
{
    EPORT7_2_IRQHandler_Callback();
}
void EPORT7_3_IRQHandler(void)
{
    EPORT7_3_IRQHandler_Callback();
}
void EPORT7_4_IRQHandler(void)
{
    EPORT7_4_IRQHandler_Callback();
}
void EPORT7_5_IRQHandler(void)
{
    EPORT7_5_IRQHandler_Callback();
}
void EPORT7_6_IRQHandler(void)
{
    EPORT7_6_IRQHandler_Callback();
}
void EPORT7_7_IRQHandler(void)
{
    EPORT7_7_IRQHandler_Callback();
}

void EPORT8_0_IRQHandler(void)
{
    EPORT8_0_IRQHandler_Callback();
}
void EPORT8_1_IRQHandler(void)
{
    EPORT8_1_IRQHandler_Callback();
}
void EPORT8_2_IRQHandler(void)
{
    EPORT8_2_IRQHandler_Callback();
}
void EPORT8_3_IRQHandler(void)
{
    EPORT8_3_IRQHandler_Callback();
}
void EPORT8_4_IRQHandler(void)
{
    EPORT8_4_IRQHandler_Callback();
}
void EPORT8_5_IRQHandler(void)
{
    EPORT8_5_IRQHandler_Callback();
}
void EPORT8_6_IRQHandler(void)
{
    EPORT8_6_IRQHandler_Callback();
}
void EPORT8_7_IRQHandler(void)
{
    EPORT8_7_IRQHandler_Callback();
}
void EPORT9_0_IRQHandler(void)
{
    EPORT9_0_IRQHandler_Callback();
}
void EPORT9_1_IRQHandler(void)
{
    EPORT9_1_IRQHandler_Callback();
}
void EPORT9_2_IRQHandler(void)
{
    EPORT9_2_IRQHandler_Callback();
}
void EPORT9_3_IRQHandler(void)
{
    EPORT9_3_IRQHandler_Callback();
}
void EPORT9_4_IRQHandler(void)
{
    EPORT9_4_IRQHandler_Callback();
}
void EPORT9_5_IRQHandler(void)
{
    EPORT9_5_IRQHandler_Callback();
}
void EPORT9_6_IRQHandler(void)
{
    EPORT9_6_IRQHandler_Callback();
}
void EPORT9_7_IRQHandler(void)
{
    EPORT9_7_IRQHandler_Callback();
}

/**
 * @brief SYSTICK 中断服务入口函数
 *
 */
void SysTick_Handler(void)
{
    SysTick_IRQHandler_Callback();
}

/**
 * @brief 系统 中断服务入口函数
 *
 */
void NMI_Handler(void)
{
    printf("warning:NMI Handler\r\n");
}

void HardFault_Handler(void)
{
    printf("warning:HardFault Handler\r\n");
}

// void __weak MemManage_Handler(void)
// {
//   printf("warning:MemManage Handler\r\n");
// }

void BusFault_Handler(void)
{
    printf("warning:BusFault Handler\r\n");
}

void UsageFault_Handler(void)
{
    printf("warning:UsageFault Handler\r\n");
}

#if (!Pend_SVC_SysTick_EN)
void SVC_Handler(void)
{
    printf("warning:SVC Handler\r\n");
}
#endif

void DebugMon_Handler(void)
{
    printf("warning:DebugMon Handler\r\n");
}

#if (!Pend_SVC_SysTick_EN)
void PendSV_Handler(void)
{
    printf("warning:PendSV Handler\r\n");
}
#endif

#endif