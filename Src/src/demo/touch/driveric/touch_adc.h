/**
 * @file touch_adc.h
 * @author Product application department
 * @brief  ADC电阻触摸驱动头文件
 * @version V1.0
 * @date 2025-07-02
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 * 
 */
#ifndef __TOUCH_ADC_H__
#define __TOUCH_ADC_H__

 /**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup TOUCHADC TOUCHADC模块
 * @ingroup Peripherals
 * @{
 */
//头文件定义
#include "type.h"
#include "tp_interface.h"
#include "adc_drv.h"
#include "lcdc_hal.h"
#include "pit32_hal.h"

//函数声明
tp_status_t touch_adc_init(void);
uint8_t touch_adc_sacn(uint8_t mode);
void ts_pit32_1_irqhandler(void);
uint16_t touch_r_get_value(void);
uint16_t touch_x_get_value(void);
uint16_t touch_y_get_value(void);
#endif

/** @} */  // 结束 TOUCHADC 模块分组
/** @} */  // 结束外设模块分组