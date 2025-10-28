/**
 * @file adc_test.h
 * @author Product application department
 * @brief  ADC 模块测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup ADC ADC模块
 * @ingroup Peripherals
 * @{
 */

#ifndef _ADC_TEST_H
#define _ADC_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "adc_hal.h"
#include "delay.h"
    
// 函数声明
void adc_demo(void);

#ifdef __cplusplus
}
#endif


/** @} */  // 结束 ADC 模块分组
/** @} */  // 结束外设模块分组

#endif
