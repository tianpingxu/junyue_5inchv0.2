/**
 * @file pwmt_test.h
 * @author Product Application Department
 * @brief  PWMT 模块测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup PWMT PWMT模块
 * @ingroup Peripherals
 * @{
 */

#ifndef _PWMT_TEST_H
#define _PWMT_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "pwmt_hal.h"
#include "dma_hal.h"
#include "pinswap_drv.h"
#include "debug.h"
    
// 函数声明
void pwmt_demo(void);


#ifdef __cplusplus
}
#endif


/** @} */  // 结束 PWMT 模块分组
/** @} */  // 结束外设模块分组

#endif
