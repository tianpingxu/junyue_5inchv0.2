/**
 * @file dac_hal.h
 * @author Product application department
 * @brief  DAC 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-11
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

#ifndef _DAC_HAL_H
#define _DAC_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "dac_drv.h"
#include "status.h"
#include "pit32_hal.h"
#include "dma_hal.h"
    
// 函数声明
void hal_dac_start(dac_trigger_sel_t trigger_select, uint32_t rate);
status_t hal_dac_senddata(uint16_t data);
status_t hal_dac_deinit(void);
static void hal_dma_callback();
void hal_dac_irqhandler(void);
void hal_dac_init(dac_data_format_t data_format, dac_trigger_sel_t trigger_select, dac_ext_tmod_t external_mode,uint8_t dma_en);

#ifdef __cplusplus
}
#endif

#endif 


