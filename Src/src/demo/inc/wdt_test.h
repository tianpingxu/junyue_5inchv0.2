/**
 * @file wdt_test.h
 * @author Product application department
 * @brief  WDT 模块测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup WDT WDT模块
 * @ingroup Peripherals
 * @{
 */


#ifndef __WDT_TEST_H
#define __WDT_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "wdt_hal.h"
#include "debug.h"

// 函数声明
void wdt_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 WDT 模块分组
/** @} */  // 结束外设模块分组

#endif
