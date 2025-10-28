/**
 * @file     system_ARMCM7.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM7 Device
 * @version  V1.0.1
 * @date     15. November 2019
******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "libpsram.h"
#include "cpm_drv.h"
#include "chipconfig.h"
#if defined(ARMCM7)
#include "ARMCM7.h"
#elif defined(ARMCM7_SP)
#include "ARMCM7_SP.h"
#elif defined(ARMCM7_DP)
#include "ARMCM7_DP.h"
#else
#error device not specified!
#endif

///*----------------------------------------------------------------------------
//  Define clocks
// *----------------------------------------------------------------------------*/
// #define  XTAL            ( 1000000U)      /* Oscillator frequency             */

// #define  SYSTEM_CLOCK    (25 * XTAL)

///*----------------------------------------------------------------------------
//  System Core Clock Variable
// *----------------------------------------------------------------------------*/
// uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency      */

// void SystemCoreClockUpdate (void)
//{
//   SystemCoreClock = SYSTEM_CLOCK;
// }

extern void __Vectors(void);
extern void sys_init(void);
extern void drv_psram_openxip(uint32_t ssi_rx_sample_delay);
extern void drv_psram_closexip(void);
extern void mpu_config(void);
extern void hal_uart_reset(void);
static void cpu_cache_enable(void)
{
    /* Enable I-Cache */
    SCB_EnableICache();

    /* Enable D-Cache */
    SCB_EnableDCache();
}
static void cpu_cache_disable(void)
{
    // 1. 禁用指令缓存前确保足够NOP
    __ISB(); // 指令同步屏障
    __DSB(); // 数据同步屏障   
    // 2. 禁用指令缓存
    SCB_DisableICache();
    __ISB(); // 指令同步屏障
    __DSB(); // 数据同步屏障   
    // 3. clean 数据缓存
    SCB_CleanDCache();
    __ISB(); // 指令同步屏障
    __DSB(); // 数据同步屏障  
    // 4. 无效化数据缓存
    SCB_CleanInvalidateDCache(); 	
    __ISB(); // 指令同步屏障
    __DSB(); // 数据同步屏障	

}
#include "adc_drv.h"
void cpm_overwrite_test_mode(uint32_t ovwr_data)
{
        uint32_t tmp = (CPM->VCCCTMR & 0x3fffffff);

        CPM->VCCCTMR = tmp;
        CPM->VCCCTMR = tmp | 0x40000000;
        CPM->VCCCTMR = tmp | 0x80000000;
        CPM->VCCCTMR = tmp | 0xc0000000;
        CPM->VCCCTMR |= ovwr_data;
        CPM->VCCCTMR &= 0x3fffffff;
}
extern uint16_t hal_adc_getconversionvalue(void);
extern void debugg_test();
void adc_init(void)
{
	    uint16_t DATA;
			uint32_t reg;
	   CPM->VCCVTRIMR |= 1<<10;
	   _adc_set_prescaler_clk_div(3);
    _adc_set_startup_counter(0x20);
    _adc_set_sampling_time(0x20);
    _adc_set_data_resolution(ADC_RESOLUTION_12BIT);

    // ADC转换队列设置
    _adc_set_sequence_length(0);
    _adc_set_number0_channel_name(0);
   	_adc_sel_external_vref;
    _adc_set_continuous_conversion;
  	_adc_set_overrun_mode_last;
    _adc_set_data_right_alignment;
	  _adc_set_channel_sel_value(1 << 0);
	  drv_adc_trigger_mode(0);
    drv_adc_trigger_select(0);
	  drv_adc_module_enable();
	  DATA = hal_adc_getconversionvalue();
	if(DATA<0x470)
	{

		cpm_overwrite_test_mode(1 << 21);
		reg = CPM->VCCVTRIMR & 0x0000000f;
		reg = reg + 0x03; //上抬档位
		CPM->VCCVTRIMR = (CPM->VCCVTRIMR & ~0x0000000f) | reg;
		CPM->VCCVTRIMR |= (0x03 << 8);
		delay(1);
		CPM->VCCVTRIMR &= ~(0x03 << 8);
		delay(1);
	}
	CPM->IPRSTCR |= 1<<20;
		CPM->IPRSTCR &= ~(1<<20);
	 CPM->VCCVTRIMR &= ~(1<<10);
   
}
 void delayms1(__IO uint32_t delayms)
{
     __IO uint32_t k = 0;
     __IO uint32_t counter_ms = 0;

    counter_ms = 100*1000000 / 3000;

    while (delayms--)
    {
        while (k < counter_ms)
            k++;

        k = 0;
    }

}

void SystemInit(void)
{

    hal_uart_reset();
#if defined(__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
    //  SCB->VTOR = (uint32_t) &(__VECTOR_TABLE[0]);
    SCB->VTOR = ((unsigned int)__Vectors) & 0xFFFFFC00;
#endif

#if defined(__FPU_USED) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3U << 10U * 2U) | /* enable CP10 Full Access */
                   (3U << 11U * 2U)); /* enable CP11 Full Access */
#endif
    if( (SCB->CCR & 0x10000)==0x10000)
    {      
        SCB_DisableICache();
        SCB_DisableDCache();      
    }

#if(CM4211_START_MODE == 2)

#else
    mpu_config(); // MPU 配置
    cpu_cache_enable();  
    delayms1(10);		
    sys_init();

	  
     adc_init();	

    #if (CCM4211_CHIP_PACKAGE == 0)
    psram_int(PSRAM_TYPE_3208X2, drv_cpm_getcoreclk()/2, PSRAM_DRIV_1);
    #elif(CCM4211_CHIP_PACKAGE == 1)
    psram_int(PSRAM_TYPE_128, drv_cpm_getcoreclk()/2, PSRAM_DRIV_0);
    #elif(CCM4211_CHIP_PACKAGE == 2)
    psram_int(PSRAM_TYPE_256, drv_cpm_getcoreclk()/2, PSRAM_DRIV_0);
    #elif(CCM4211_CHIP_PACKAGE == 3)
    psram_int(PSRAM_TYPE_128, drv_cpm_getcoreclk()/2, PSRAM_DRIV_0);
    #endif 
#endif
}

void LVD_EN(void)
{
    //    _bit_set(CPM->PWRCR,CPM_PWRCR_VCC_5V_LV_DETECT_EN);
    //    _bit_set(CPM->PWRCR,CPM_PWRCR_VCC_3V3_LV_DETECT_EN);
}

void IO_Latch_Clr(void)
{
    //    _bit_clr(CPM->PWRCR,CPM_PWRCR_VCC_IO_LATCH_SET_MASK);
    //    _bit_set(CPM->PWRCR,CPM_PWRCR_VCC_IO_LATCH_CLR_MASK);
    //    _bit_clr(CPM->PWRCR,CPM_PWRCR_VCC_IO_LATCH_CLR_MASK);
}
