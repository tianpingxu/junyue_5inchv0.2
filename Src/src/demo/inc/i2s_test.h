/**
 * @file i2s_test.h
 * @author Product Application Department
 * @brief I2S 模块测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup I2S I2S模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __I2S_TEST_H
#define __I2S_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件定义
#include "i2s_hal.h"
#include "debug.h"
#include "pinswap_drv.h"

// 函数声明
void i2s_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 I2S 模块分组
/** @} */  // 结束外设模块分组

#endif
