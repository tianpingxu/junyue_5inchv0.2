/**
 * @file algo_test.h
 * @author Product application department
 * @brief  ALGO 模块测试用例头文件，仅供参考
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
 * @defgroup ALGO ALGO模块
 * @ingroup Peripherals
 * @{
 */

#ifndef _ALGO_TEST_H
#define _ALGO_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "algo_hal.h"
#include "debug.h"
#include "trng_hal.h"
#include "crc_hal.h"

// 函数声明
void algo_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 ALGO 模块分组
/** @} */  // 结束外设模块分组

#endif
