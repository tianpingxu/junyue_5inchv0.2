/**
 * @file dac_drv.h
 * @author Product application department
 * @brief  DAC 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DAC_DRV_H__
#define __DAC_DRV_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "dac_reg.h"

// 全局变量定义
#ifdef DAC_DEMO
#define DAC_SYSTICK_INT
#define DAC_DMA_INT
#endif


#define _dac_en (DAC->DAC_CR |= DAC_DACEN)
#define _dac_dis (DAC->DAC_CR &= ~DAC_DACEN)
#define _dac_en_dma (DAC->DAC_CR |= DAC_DMAEN)

#define _dac_set_right_align (DAC->DAC_CR &= ~(DAC_ALIGN))
#define _dac_set_left_align (DAC->DAC_CR |= DAC_ALIGN)
#define _dac_set_eight_res (DAC->DAC_CR &= ~(DAC_RES))
#define _dac_set_twelve_res (DAC->DAC_CR |= DAC_RES)

#define _dac_clr_trigger_mode (DAC->DAC_CR &= ~(DAC_TSEL_MASK | DAC_EXT_TMOD_MASK))
#define _dac_set_trigger_mode(triggerMode, external_mode) (DAC->DAC_CR |= ((triggerMode << DAC_TSEL_SHIFT) | (external_mode << DAC_EXT_TMOD_SHIFT)))
#define _dac_diable_ext_verf (DAC->DAC_TRIMR &= ~(0x1000000))

#define _dac_set_data(data) (DAC->DAC_DR = data)
#define _dac_get_data (DAC->DAC_DOR << 4)
#define _dac_set_sw_trig (DAC->DAC_SWTR |= DAC_SW_TRIG)
#define _dac_get_fsr_flag (DAC->DAC_FSR & DAC_LD_DONE)
#define _dac_clr_fsr_flag (DAC->DAC_FSR |= DAC_LD_DONE)

/**
 * @brief DAC 模块格式枚举定义
 * 
 */
typedef enum
{
    LEFTALIGNED_8BITS = 0,
    LEFTALIGNED_12BITS,
    RIGHTALIGNED_8BITS,
    RIGHTALIGNED_12BITS
} dac_data_format_t;

/**
 * @brief DAC 模块触发模式选择枚举定义
 * 
 */
typedef enum
{
    TRIGGER_SOFTWARE = 0,
    TRIGGER_EXTERNAL,
    TRIGGER_PIT
} dac_trigger_sel_t;

/**
 * @brief DAC 模块触发电平选择枚举定义
 * 
 */
typedef enum _DAC_EXT_TMOD_
{
    MOD_RESERVED = 0,
    DET_ON_RISING = 1,
    DET_ON_FALLING,
    DET_ON_BOTH,
    DET_ON_HIGH,
    DET_ON_LOW
} dac_ext_tmod_t;

// 函数声明
void drv_dac_enable(void);
void drv_dac_close(void);
void drv_dac_sw_trig(void);
void drv_dac_init(dac_data_format_t data_format, dac_trigger_sel_t trigger_select, dac_ext_tmod_t external_mode, uint8_t dma_en);
void drv_dac_deinit(void);
void drv_dac_wait_load_done(void);
void drv_adc_send_data(uint16_t data);

#ifdef __cplusplus
}
#endif

#endif
