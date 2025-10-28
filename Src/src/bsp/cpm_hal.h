/**
 * @file cpm_hal.h
 * @author Product application department
 * @brief  DAC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-01
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

#ifndef CPM_HAL_H_
#define CPM_HAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "cpm_drv.h"
#include "system_NVIC.h"
#include "ssi_hal.h"
 
// 全局变量定义
#define HAL_CPM_DEBUG
#define HAL_SYSCLKSOURCE_FLAG 0 
#define HAL_IPSCLKSOURCE_FLAG 1
#define HAL_EFMCLKSOURCE_FLAG 2
#define _CPM_SET_TRIM_EN _cpm_set_overwrite_vccgtrimr_trim_en;
#define _CPM_V33_SW_DIS _cpm_v33_sw_dis;

/**
 * @brief 系统时钟源选择枚举定义
 * 
 */
typedef enum
{
    HAL_SYSCLK_OSC8M = CPM_SYSCLK_OSC8M,
    HAL_SYSCLK_OSC400M = CPM_SYSCLK_OSC400M,
    HAL_SYSCLK_OSCUSBPHU240M = CPM_SYSCLK_USBPHY240M,
    HAL_SYSCLK_OSCEXT = CPM_SYSCLK_OSCEXT
} cpm_sysclksource_t;

/**
 * @brief CPM 模块时钟索引枚举定义
 * 
 */
typedef enum
{
    MODULE_CLK_EFM_BUS = 1,   
    MODULE_CLK_MCC = 5,       
    MODULE_CLK_MCCADR = 6,    
    MODULE_CLK_ADC = 7,       
    MODULE_CLK_MESH = 9,      
    MODULE_CLK_TC = 10,       
    MODULE_CLK_CLKOUT = 15,   
    MODULE_CLK_KEY_CTRL = 16, 
    MODULE_CLK_EFM_IPS = 18,  
    MODULE_CLK_CPM_IPS = 19,  
    MODULE_CLK_EPORT = 20,    
    MODULE_CLK_EPORT1 = 21,   
    MODULE_CLK_EPORT2 = 22,   
    MODULE_CLK_EPORT3 = 23,   
    MODULE_CLK_EPORT4 = 24,   
    MODULE_CLK_TRACE = 26,    

    MODULE_CLK_DMAC1 = 1 + 32,      
    MODULE_CLK_DMAC2 = 2 + 32,      
    MODULE_CLK_CRC0 = 4 + 32,       
    MODULE_CLK_CRC1 = 5 + 32,       
    MODULE_CLK_AHB2_MUX = 11 + 32,  
    MODULE_CLK_SRAMD = 12 + 32,     
    MODULE_CLK_SRAM0 = 13 + 32,     
    MODULE_CLK_SRAM1 = 14 + 32,     
    MODULE_CLK_SRAM2 = 15 + 32,     
    MODULE_CLK_SRAM3 = 16 + 32,     
    MODULE_CLK_SSI4 = 17 + 32,      
    MODULE_CLK_SSI5 = 18 + 32,      
    MODULE_CLK_ROM = 19 + 32,       
    MODULE_CLK_M2S_BUS_M = 22 + 32, 

    MODULE_CLK_USBC = 3 + 64,     
    MODULE_CLK_AHB3_MUX = 5 + 64, 

    MODULE_CLK_AES = 1 + 96,       
    MODULE_CLK_SM4 = 2 + 64,       
    MODULE_CLK_RF = 4 + 96,        
    MODULE_CLK_CRYPTO = 5 + 64,    
    MODULE_CLK_SHA = 6 + 96,       
    MODULE_CLK_EDMAC0 = 7 + 64,    
    MODULE_CLK_DES = 8 + 96,       
    MODULE_CLK_ZUC = 9 + 64,       
    MODULE_CLK_AHB2MLB = 10 + 96,  
    MODULE_CLK_AHB2IPS2 = 11 + 64, 

    MODULE_CLK_IO_CTRL = 0 + 128,    
    MODULE_CLK_WDT = 1 + 128,        
    MODULE_CLK_RTC = 2 + 128,        
    MODULE_CLK_PIT1 = 3 + 128,       
    MODULE_CLK_PIT2 = 4 + 128,       
    MODULE_CLK_USI1 = 5 + 128,       
    MODULE_CLK_EDMAC1 = 6 + 128,     
    MODULE_CLK_SPI1 = 7 + 128,       
    MODULE_CLK_SPI2 = 8 + 128,       
    MODULE_CLK_SPI3 = 9 + 128,       
    MODULE_CLK_SCI1 = 10 + 128,      
    MODULE_CLK_SCI2 = 11 + 128,      
    MODULE_CLK_USI2 = 12 + 128,      
    MODULE_CLK_CAN1 = 13 + 128,      
    MODULE_CLK_I2C1 = 14 + 128,      
    MODULE_CLK_PWM0 = 15 + 128,      
    MODULE_CLK_I2C2 = 16 + 128,      
    MODULE_CLK_CAN2 = 17 + 128,      
    MODULE_CLK_SCI3 = 18 + 128,      
    MODULE_CLK_QADC = 20 + 128,      
    MODULE_CLK_DAC  = 21 + 128,      
    MODULE_CLK_MCC_2   = 22 + 128,   
    MODULE_CLK_PWMT1   = 23 + 128,   
    MODULE_CLK_LD      = 24 + 128,   
    MODULE_CLK_PWMT2   = 25 + 128,   
    MODULE_CLK_PGD     = 26 + 128,   
    MODULE_CLK_SEC_DET = 27 + 128,   
    MODULE_CLK_PCI     = 28 + 128,   
    MODULE_CLK_PMURTC  = 29 + 128,   
    MODULE_CLK_AHB2IPS = 30 + 128,   
    MODULE_CLK_PWMT3   = 31 + 128,   
} cpm_moduleclkindex_t;
/**
* @brief CPM 模块时钟源索引枚举定义
*
*/
typedef enum
{
    HAL_CHIP_SYS_CLK_INDEX_CLKOUT = 0,
    HAL_CHIP_SYS_CLK_INDEX_TRACE,
    HAL_CHIP_SYS_CLK_INDEX_SYS,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_ARITH,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_AHB3,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_IPS,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_TC,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_MESH,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_ADC,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_MCC_ADR,
    HAL_CHIP_PERIPHERAL_CLK_INDEX_MCC
} cpm_clksourceindex_t;


/**
* @brief CPM 模块时钟初始化索引枚举定义
*
*/
typedef struct
{
    cpm_sysclksource_t SysClkSource;
    cpm_sysclktrim_t    SysClkTrim;
    cpm_sysclkdiv_t SysClkDiv;
    cpm_ipsclkdiv_t IpsClkDiv;

} cpm_clkinit_t;

// 函数声明
void hal_cpm_moduleclkcmd(cpm_moduleclkindex_t ModuleClkIdex, functionalstate_t NewState);
void hal_cpm_wakeupinit(cpm_padwakeupindex_t Src, functionalstate_t NewState);
void hal_cpm_porreset(void);
void hal_cpm_poweroff(void);
void hal_cpm_lowpower(void);
void hal_cpm_module_reset(cpm_module_t module);
uint32_t hal_cpm_getclockfreq(uint8_t ClkSourceFlg);
void hal_cpm_sdram2lcd_module_set_div(uint8_t div);

#ifdef __cplusplus
}
#endif

#endif