/**
 * @file reset_test.h
 * @author Product Application Department
 * @brief  RESET 模块测试用例文件，仅供参考
 * @version V1.0
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */


/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup RESET RESET模块
 * @ingroup Peripherals
 * @{
 */

#ifndef RESET_DEMO_H_
#define RESET_DEMO_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "reset_hal.h"
#include "debug.h"
#include "delay.h"

// 函数声明
void reset_demo(void);

#ifdef __cplusplus
}
#endif


/** @} */  // 结束 RESET 模块分组
/** @} */  // 结束外设模块分组

#endif
