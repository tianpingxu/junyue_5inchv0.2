/**
 * @file lowpower_test.h
 * @author Product Application Department
 * @brief  低功耗测试文件，仅供参考
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup LOWPOWER LOWPOWER模块
 * @ingroup Peripherals
 * @{
 */

#ifndef LOWPOWER_TEST_H_
#define LOWPOWER_TEST_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "cpm_hal.h"
#include "debug.h"
#include "delay.h"

// 函数声明
void lowerpower_demo(void);

#ifdef __cplusplus
}
#endif


/** @} */  // 结束 LOWPOWER 模块分组
/** @} */  // 结束外设模块分组

#endif
