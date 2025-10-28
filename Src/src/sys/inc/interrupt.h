/**
 * @file interrupt.h
 * @author Product application department
 * @brief  INTERRUPT 中断配置头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
#include "debug.h"
#include "system_NVIC.h"

// 函数声明
// extern void HAL_CAN_IRQHandler(uint8_t can_channel);
extern void (*OTP_IRQHandler_Callback)(void);
extern void (*PMU_IRQHandler_Callback)(void);
extern void (*TC1_IRQHandler_Callback)(void);
extern void (*PIT1_IRQHandler_Callback)(void);
extern void (*PIT2_IRQHandler_Callback)(void);
extern void (*TC2_IRQHandler_Callback)(void);
extern void (*TC3_IRQHandler_Callback)(void);
extern void (*DMA1_IRQHandler_Callback)(void);
extern void (*DMA2_IRQHandler_Callback)(void);
extern void (*TRNG_IRQHandler_Callback)(void);
extern void (*SEC_FD_IRQHandler_Callback)(void);
extern void (*CPM_IRQHandler_Callback)(void);
extern void (*PMU_RTC_IRQHandler_Callback)(void);
extern void (*SD_IRQHandler_Callback)(void);
extern void (*DMA2D_IRQHandler_Callback)(void);
extern void (*AESSM4_IRQHandler_Callback)(void);
extern void (*QADC_IRQHandler_Callback)(void);
extern void (*DAC_IRQHandler_Callback)(void);
extern void (*UART5_IRQHandler_Callback)(void);
extern void (*USB_IRQHandler_Callback)(void);
extern void (*UART6_IRQHandler_Callback)(void);
extern void (*SPI1_IRQHandler_Callback)(void);
extern void (*SPI2_IRQHandler_Callback)(void);
extern void (*SPI3_IRQHandler_Callback)(void);
extern void (*SPIM1_IRQHandler_Callback)(void);
extern void (*SPIM2_IRQHandler_Callback)(void);
extern void (*SPIM3_IRQHandler_Callback)(void);
extern void (*UART1_IRQHandler_Callback)(void);
extern void (*UART2_IRQHandler_Callback)(void);
extern void (*PSRAM_IRQHandler_Callback)(void);
extern void (*GMAC_IRQHandler_Callback)(void);
extern void (*I2C1_IRQHandler_Callback)(void);
extern void (*EPORT0_0_IRQHandler_Callback)(void);
extern void (*EPORT0_1_IRQHandler_Callback)(void);
extern void (*EPORT0_2_IRQHandler_Callback)(void);
extern void (*EPORT0_3_IRQHandler_Callback)(void);
extern void (*EPORT0_4_IRQHandler_Callback)(void);
extern void (*EPORT0_5_IRQHandler_Callback)(void);
extern void (*EPORT0_6_IRQHandler_Callback)(void);
extern void (*EPORT0_7_IRQHandler_Callback)(void);
extern void (*EPORT1_0_IRQHandler_Callback)(void);
extern void (*EPORT1_1_IRQHandler_Callback)(void);
extern void (*EPORT1_2_IRQHandler_Callback)(void);
extern void (*EPORT1_3_IRQHandler_Callback)(void);
extern void (*EPORT1_4_IRQHandler_Callback)(void);
extern void (*EPORT1_5_IRQHandler_Callback)(void);
extern void (*EPORT1_6_IRQHandler_Callback)(void);
extern void (*EPORT1_7_IRQHandler_Callback)(void);
extern void (*SSISLV_IRQHandler_Callback)(void);
extern void (*I2C2_IRQHandler_Callback)(void);
extern void (*AXIDMA_IRQHandler_Callback)(void);
extern void (*UART3_IRQHandler_Callback)(void);
extern void (*UART4_IRQHandler_Callback)(void);
extern void (*LCDC_ROT_ERROR_IRQHandler_Callback)(void);
extern void (*CAN1_BUF00_03_IRQHandler_Callback)(void);
extern void (*CAN1_BUF04_07_IRQHandler_Callback)(void);
extern void (*CAN1_BUF08_11_IRQHandler_Callback)(void);
extern void (*CAN1_BUF12_15_IRQHandler_Callback)(void);
extern void (*CAN1_BUF16_31_IRQHandler_Callback)(void);
extern void (*CAN1_BUF32_63_IRQHandler_Callback)(void);
extern void (*BOFF_TRWARN_IRQHandler_Callback)(void);
extern void (*CAN1_ERR_IRQHandler_Callback)(void);
extern void (*CAN2_BUF00_03_IRQHandler_Callback)(void);
extern void (*CAN2_BUF04_07_IRQHandler_Callback)(void);
extern void (*CAN2_BUF08_11_IRQHandler_Callback)(void);
extern void (*CAN2_BUF12_15_IRQHandler_Callback)(void);
extern void (*CAN2_BUF16_31_IRQHandler_Callback)(void);
extern void (*CAN2_BUF32_63_IRQHandler_Callback)(void);
extern void (*BOFF2_TRWARN_IRQHandler_Callback)(void);
extern void (*CAN2_ERR_IRQHandler_Callback)(void);
extern void (*I2S1_IRQHandler_Callback)(void);
extern void (*I2S2_IRQHandler_Callback)(void);
extern void (*LCDC_CRC_ERROR_IRQHandler_Callback)(void);
extern void (*LCDC_REG_RELOAD_IRQHandler_Callback)(void);
extern void (*PWMT1_IRQHandler_Callback)(void);
extern void (*PWMT2_IRQHandler_Callback)(void);
extern void (*PWMT3_IRQHandler_Callback)(void);
extern void (*LCDC_BUS_ERROR_IRQHandler_Callback)(void);
extern void (*LCDC_FIFO_UNDERRUN_IRQHandler_Callback)(void);
extern void (*LCDC_FIFO_WARN_IRQHandler_Callback)(void);
extern void (*LCDC_IRQ_SCANLINE_IRQHandler_Callback)(void);
extern void (*IMGAGE_DECODER_IRQHandler_Callback)(void);
extern void (*EPORT2_0_IRQHandler_Callback)(void);
extern void (*EPORT2_1_IRQHandler_Callback)(void);
extern void (*EPORT2_2_IRQHandler_Callback)(void);
extern void (*EPORT2_3_IRQHandler_Callback)(void);
extern void (*EPORT2_4_IRQHandler_Callback)(void);
extern void (*EPORT2_5_IRQHandler_Callback)(void);
extern void (*EPORT2_6_IRQHandler_Callback)(void);
extern void (*EPORT2_7_IRQHandler_Callback)(void);
extern void (*EPORT3_0_IRQHandler_Callback)(void);
extern void (*EPORT3_1_IRQHandler_Callback)(void);
extern void (*EPORT3_2_IRQHandler_Callback)(void);
extern void (*EPORT3_3_IRQHandler_Callback)(void);
extern void (*EPORT3_4_IRQHandler_Callback)(void);
extern void (*EPORT3_5_IRQHandler_Callback)(void);
extern void (*EPORT3_6_IRQHandler_Callback)(void);
extern void (*EPORT3_7_IRQHandler_Callback)(void);
extern void (*EPORT4_0_IRQHandler_Callback)(void);
extern void (*EPORT4_1_IRQHandler_Callback)(void);
extern void (*EPORT4_2_IRQHandler_Callback)(void);
extern void (*EPORT4_3_IRQHandler_Callback)(void);
extern void (*EPORT4_4_IRQHandler_Callback)(void);
extern void (*EPORT4_5_IRQHandler_Callback)(void);
extern void (*EPORT4_6_IRQHandler_Callback)(void);
extern void (*EPORT4_7_IRQHandler_Callback)(void);
extern void (*EPORT5_0_IRQHandler_Callback)(void);
extern void (*EPORT5_1_IRQHandler_Callback)(void);
extern void (*EPORT5_2_IRQHandler_Callback)(void);
extern void (*EPORT5_3_IRQHandler_Callback)(void);
extern void (*EPORT5_4_IRQHandler_Callback)(void);
extern void (*EPORT5_5_IRQHandler_Callback)(void);
extern void (*EPORT5_6_IRQHandler_Callback)(void);
extern void (*EPORT5_7_IRQHandler_Callback)(void);
extern void (*EPORT6_0_IRQHandler_Callback)(void);
extern void (*EPORT6_1_IRQHandler_Callback)(void);
extern void (*EPORT6_2_IRQHandler_Callback)(void);
extern void (*EPORT6_3_IRQHandler_Callback)(void);
extern void (*EPORT6_4_IRQHandler_Callback)(void);
extern void (*EPORT6_5_IRQHandler_Callback)(void);
extern void (*EPORT6_6_IRQHandler_Callback)(void);
extern void (*EPORT6_7_IRQHandler_Callback)(void);
extern void (*EPORT7_0_IRQHandler_Callback)(void);
extern void (*EPORT7_1_IRQHandler_Callback)(void);
extern void (*EPORT7_2_IRQHandler_Callback)(void);
extern void (*EPORT7_3_IRQHandler_Callback)(void);
extern void (*EPORT7_4_IRQHandler_Callback)(void);
extern void (*EPORT7_5_IRQHandler_Callback)(void);
extern void (*EPORT7_6_IRQHandler_Callback)(void);
extern void (*EPORT7_7_IRQHandler_Callback)(void);
extern void (*EPORT8_0_IRQHandler_Callback)(void);
extern void (*EPORT8_1_IRQHandler_Callback)(void);
extern void (*EPORT8_2_IRQHandler_Callback)(void);
extern void (*EPORT8_3_IRQHandler_Callback)(void);
extern void (*EPORT8_4_IRQHandler_Callback)(void);
extern void (*EPORT8_5_IRQHandler_Callback)(void);
extern void (*EPORT8_6_IRQHandler_Callback)(void);
extern void (*EPORT8_7_IRQHandler_Callback)(void);
extern void (*EPORT9_0_IRQHandler_Callback)(void);
extern void (*EPORT9_1_IRQHandler_Callback)(void);
extern void (*EPORT9_2_IRQHandler_Callback)(void);
extern void (*EPORT9_3_IRQHandler_Callback)(void);
extern void (*EPORT9_4_IRQHandler_Callback)(void);
extern void (*EPORT9_5_IRQHandler_Callback)(void);
extern void (*EPORT9_6_IRQHandler_Callback)(void);
extern void (*EPORT9_7_IRQHandler_Callback)(void);
extern void (*SysTick_IRQHandler_Callback)(void);

#ifdef __cplusplus
}
#endif

#endif
