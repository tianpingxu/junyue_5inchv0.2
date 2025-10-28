/**
 * @file dac_test.h
 * @author Product application department
 * @brief  DAC 模块测试用例头文件，仅供参考
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
 * @defgroup DAC DAC模块
 * @ingroup Peripherals
 * @{
 */

#ifndef _DAC_TEST_H_
#define _DAC_TEST_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "dac_hal.h"
#include "delay.h"

// 函数声明
void dac_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 DAC 模块分组
/** @} */  // 结束外设模块分组

#endif
