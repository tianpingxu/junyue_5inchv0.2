/**
 ******************************************************************************
 * @file    ccm4211.h
 * @author  MCD Application Team
 * @version V2.4.2
 * @date    13-November-2015
 * @brief   CMSIS CCM4211 Device Peripheral Access Layer Header File.
 *
 *          This file contains:
 *           - Data structures and the address mapping for all peripherals
 *           - Peripheral's registers declarations and bits definition
 *           - Macros to access peripheral’s registers hardware
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 C*core</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of C*core nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

#ifndef __CCM4211_H
#define __CCM4211_H

#ifdef __cplusplus
extern "C"
{
#endif

#define __CM7_REV 0x0001         /*!< Core revision r0p1                            */
#define __MPU_PRESENT 1          /*!< CM7 provides an MPU                     */
#define __NVIC_PRIO_BITS 3       /*!< CM7 uses 3 Bits for the Priority Levels */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT 1          /*!< FPU present                                   */
#define __ICACHE_PRESENT 1       /*!< CM7 instruction cache present                 */
#define __DCACHE_PRESENT 1       /*!< CM7 data cache present                        */

/**
 * @brief CCM4211 Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum
{
    /******  Cortex-M7 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_IRQn = -14,   //  Non Maskable Interrupt
    MemoryManagement_IRQn = -12, //  Cortex-M7 Memory Management Interrupt
    BusFault_IRQn = -11,         //  Cortex-M7 Bus Fault Interrupt
    UsageFault_IRQn = -10,       //  Cortex-M7 Usage Fault Interrupt
    SVCall_IRQn = -5,            //  Cortex-M7 SV Call Interrupt
    DebugMonitor_IRQn = -4,      //  Cortex-M7 Debug Monitor Interrupt
    PendSV_IRQn = -2,            //  Cortex-M7 Pend SV Interrupt
    SysTick_IRQn = -1,           //  Cortex-M7 System Tick Interrupt
    /******  ccm4211 specific Interrupt Numbers **********************************************************************/
    OTP_IRQn = 0,               //  OTP Interrupt
    PMU_IRQn = 1,               //  PMU Interrupt
    TC_IRQn = 2,                //  TC Interrup
    PIT1_IRQn = 3,              //  PIT1 interrupt
    PIT2_IRQn = 4,              //  PIT2 interrupt
    TC2_IRQ = 5,                //  TC2 Interrupt
    TC3_IRQ = 6,                //  TC3 Interrupt
    DMA1_IRQn = 7,              //  DMA1 Interrupt
    DMA2_IRQn = 8,              //  DMA2 Interrupt
    TRNG_IRQn = 10,             //  TRNG Interrupt
    SEC_PGD_FD_IRQn = 11,       //  SEC_FD Interrupt
    CPM_IRQn = 14,              //  WAKEUP/USBDET Interrupt
    PMU_RTC_IRQn = 15,          //  PMU RTC Interrupt
    SD_IRQn = 16,               //  SD  Interrupt
    DMA2D_IRQn = 17,            //  DMA2D Interrupt
    AESSMS4_IRQn = 19,          //  SM4/AES Interrupt
    QADC_IRQn = 20,             //  QADC Interrupt
    DAC_IRQn = 21,              //  DAC  Interrupt
    UART5_IRQn = 23,            //  UART5 Interrupt
    USBC_Irqn = 24,             //  USBC  Interrupt
    UART6_IRQn = 25,            //  UART6 Interrupt
    SPI1_IRQn = 26,             //  SPI1  Interrupt
    SPI2_IRQn = 27,             //  SPI2  Interrupt
    SPI3_IRQn = 28,             //  SPI3  Interrupt
    SPIM1_IRQn = 29,            //  SPIM1 Interrupt
    SPIM2_IRQn = 30,            //  SPIM2 Interrupt
    SPIM3_IRQn = 31,            //  SPIM3 Interrupt
    UART1_IRQn = 32,            //  UART1 Interrupt
    UART2_IRQn = 33,            //  UART2 Interrupt
    PSRAM_IRQn = 34,            //  PSRAM Interrupt
    GMAC_IRQn = 35,             //  GMAC  Interrupt
    I2C1_IRQn = 36,             //  I2C1  Interrupt
    EPORT0_0_IRQn = 41,         //  EPORT0_0 Interrupt
    EPORT0_1_IRQn = 42,         //  EPORT0_1 Interrupt
    EPORT0_2_IRQn = 43,         //  EPORT0_2 Interrupt
    EPORT0_3_IRQn = 44,         //  EPORT0_3 Interrupt
    EPORT0_4_IRQn = 45,         //  EPORT0_4 Interrupt
    EPORT0_5_IRQn = 46,         //  EPORT0_5 Interrupt
    EPORT0_6_IRQn = 47,         //  EPORT0_6 Interrupt
    EPORT0_7_IRQn = 48,         //  EPORT0_7 Interrupt
    EPORT1_0_IRQn = 49,         //  EPORT1_0 Interrupt
    EPORT1_1_IRQn = 50,         //  EPORT1_1 Interrupt
    EPORT1_2_IRQn = 51,         //  EPORT1_2 Interrupt
    EPORT1_3_IRQn = 52,         //  EPORT1_3 Interrupt
    EPORT1_4_IRQn = 53,         //  EPORT1_4 Interrupt
    EPORT1_5_IRQn = 54,         //  EPORT1_5 Interrupt
    EPORT1_6_IRQn = 55,         //  EPORT1_6 Interrupt
    EPORT1_7_IRQn = 56,         //  EPORT1_7 Interrupt
    SSISLV1_IRQn = 57,          //  SSISLAVE Interrupt
    JPEG_ACCELERATOR_IRQn = 58, //  JPEG_ACCELERATOR Interrupt
    I2C2_IRQn = 59,             //  I2C2  Interrupt
    AXIDMA_IRQn = 60,           //  AXIDMA Interrupt
    UART3_IRQn = 61,            //  UART3 Interrupt
    UART4_IRQn = 62,            //  UART4 Interrupt
    LCDC_ROT_ERRORIRQn = 63,    //  LCDCROT_ERROR  Interrupt
    CAN1_BUF00_03_IRQn = 64,    //  CAN1  Interrupt
    CAN1_BUF04_07_IRQn = 65,    //  CAN1  Interrupt
    CAN1_BUF08_11_IRQn = 66,    //  CAN1  Interrupt
    CAN1_BUF12_15_IRQn = 67,    //  CAN1  Interrupt
    CAN1_BUF16_31_IRQn = 68,    //  CAN1  Interrupt
    CAN1_BUF32_63_IRQn = 69,    //  CAN1  Interrupt
    BOFF_TRWARN_IRQn = 70,      //  CAN1  Interrupt
    CAN1_ERR_IRQn = 71,         //  CAN1  Interrupt
    CAN2_BUF00_03_IRQn = 72,    //  CAN2  Interrupt
    CAN2_BUF04_07_IRQn = 73,    //  CAN2  Interrupt
    CAN2_BUF08_11_IRQn = 74,    //  CAN2  Interrupt
    CAN2_BUF12_15_IRQn = 75,    //  CAN2  Interrupt
    CAN2_BUF16_31_IRQn = 76,    //  CAN2  Interrupt
    CAN2_BUF32_63_IRQn = 77,    //  CAN2  Interrupt
    BOFF2_TRWARN_IRQn = 78,     //  CAN2  Interrupt
    CAN2_ERR_IRQn = 79,         //  CAN2  Interrupt
    I2S1_IRQn = 80,             //  I2S1  Interrupt
    I2S2_IRQn = 81,             //  I2S2  Interrupt
    LCDC_CRC_ERRORIRQn = 82,    //  LCDCCRC_ERROR  Interrupt
    LCDC_REG_RELOADIRQn = 83,   //  LCDCREG_RELOAD  Interrupt
    PWMT1_IRQn = 84,            //  PWMT1  Interrupt
    PWMT2_IRQn = 85,            //  PWMT2  Interrupt
    PWMT3_IRQn = 86,            //  PWMT3  Interrupt
    LCDC_BUS_ERRORIRQn = 87,    //  LCDCCBUS_ERROR  Interrupt
    LCDC_FIFO_UNDERRUNRQn = 88, //  LCDC_FIFO_UNDERRUNR  Interrupt
    LCDC_FIFO_WARNRQn = 89,     //  LCDC_FIFO_WARN  Interrupt
    LCDC_IRQ_SCANLINERQn = 90,  //  LCDC_IRQ_SCANLINE Interrupt
    IMAGE_DECODER_IRQ = 91,     //  IMAGE_DECODER Interrupt
    EPORT2_0_IRQn = 92,         //  EPORT2_0 Interrupt
    EPORT2_1_IRQn = 93,         //  EPORT2_1 Interrupt
    EPORT2_2_IRQn = 94,         //  EPORT2_2 Interrupt
    EPORT2_3_IRQn = 95,         //  EPORT2_3 Interrupt
    EPORT2_4_IRQn = 96,         //  EPORT2_4 Interrupt
    EPORT2_5_IRQn = 97,         //  EPORT2_5 Interrupt
    EPORT2_6_IRQn = 98,         //  EPORT2_6 Interrupt
    EPORT2_7_IRQn = 99,         //  EPORT2_7 Interrupt
    EPORT3_0_IRQn = 100,        //  EPORT3_0 Interrupt
    EPORT3_1_IRQn = 101,        //  EPORT3_1 Interrupt
    EPORT3_2_IRQn = 102,        //  EPORT3_2 Interrupt
    EPORT3_3_IRQn = 103,        //  EPORT3_3 Interrupt
    EPORT3_4_IRQn = 104,        //  EPORT3_4 Interrupt
    EPORT3_5_IRQn = 105,        //  EPORT3_5 Interrupt
    EPORT3_6_IRQn = 106,        //  EPORT3_6 Interrupt
    EPORT3_7_IRQn = 107,        //  EPORT3_7 Interrupt
    EPORT4_0_IRQn = 108,        //  EPORT4_0 Interrupt
    EPORT4_1_IRQn = 109,        //  EPORT4_1 Interrupt
    EPORT4_2_IRQn = 110,        //  EPORT4_2 Interrupt
    EPORT4_3_IRQn = 111,        //  EPORT4_3 Interrupt
    EPORT4_4_IRQn = 112,        //  EPORT4_4 Interrupt
    EPORT4_5_IRQn = 113,        //  EPORT4_5 Interrupt
    EPORT4_6_IRQn = 114,        //  EPORT4_6 Interrupt
    EPORT4_7_IRQn = 115,        //  EPORT4_7 Interrupt
    EPORT5_0_IRQn = 116,        //  EPORT5_0 Interrupt
    EPORT5_1_IRQn = 117,        //  EPORT5_1 Interrupt
    EPORT5_2_IRQn = 118,        //  EPORT5_2 Interrupt
    EPORT5_3_IRQn = 119,        //  EPORT5_3 Interrupt
    EPORT5_4_IRQn = 120,        //  EPORT5_4 Interrupt
    EPORT5_5_IRQn = 121,        //  EPORT5_5 Interrupt
    EPORT5_6_IRQn = 122,        //  EPORT5_6 Interrupt
    EPORT5_7_IRQn = 123,        //  EPORT5_7 Interrupt
    EPORT6_0_IRQn = 124,        //  EPORT6_0 Interrupt
    EPORT6_1_IRQn = 125,        //  EPORT6_1 Interrupt
    EPORT6_2_IRQn = 126,        //  EPORT6_2 Interrupt
    EPORT6_3_IRQn = 127,        //  EPORT6_3 Interrupt
    EPORT6_4_IRQn = 128,        //  EPORT6_4 Interrupt
    EPORT6_5_IRQn = 129,        //  EPORT6_5 Interrupt
    EPORT6_6_IRQn = 130,        //  EPORT6_6 Interrupt
    EPORT6_7_IRQn = 131,        //  EPORT6_6 Interrupt
    EPORT7_0_IRQn = 132,        //  EPORT7_0 Interrupt
    EPORT7_1_IRQn = 133,        //  EPORT7_1 Interrupt
    EPORT7_2_IRQn = 134,        //  EPORT7_2 Interrupt
    EPORT7_3_IRQn = 135,        //  EPORT7_3 Interrupt
    EPORT7_4_IRQn = 136,        //  EPORT7_4 Interrupt
    EPORT7_5_IRQn = 137,        //  EPORT7_5 Interrupt
    EPORT7_6_IRQn = 138,        //  EPORT7_6 Interrupt
    EPORT7_7_IRQn = 139,        //  EPORT7_7 Interrupt
    EPORT8_0_IRQn = 140,        //  EPORT8_0 Interrupt
    EPORT8_1_IRQn = 141,        //  EPORT8_1 Interrupt
    EPORT8_2_IRQn = 142,        //  EPORT8_2 Interrupt
    EPORT8_3_IRQn = 143,        //  EPORT8_3 Interrupt
    EPORT8_4_IRQn = 144,        //  EPORT8_4 Interrupt
    EPORT8_5_IRQn = 145,        //  EPORT8_5 Interrupt
    EPORT8_6_IRQn = 146,        //  EPORT8_6 Interrupt
    EPORT8_7_IRQn = 147,        //  EPORT8_7 Interrupt
    EPORT9_0_IRQn = 148,        //  EPORT9_0 Interrupt
    EPORT9_1_IRQn = 149,        //  EPORT9_1 Interrupt
    EPORT9_2_IRQn = 150,        //  EPORT9_2 Interrupt
    EPORT9_3_IRQn = 151,        //  EPORT9_3 Interrupt
    EPORT9_4_IRQn = 152,        //  EPORT9_4 Interrupt
    EPORT9_5_IRQn = 153,        //  EPORT9_5 Interrupt
    EPORT9_6_IRQn = 154,        //  EPORT9_6 Interrupt
    EPORT9_7_IRQn = 155,        //  EPORT9_7 Interrupt
} IRQn_Type;
#include "core_cm7.h" /* Cortex-M7 processor and core peripherals */

#include <stdint.h>

#ifdef __cplusplus
}
#endif

#endif
