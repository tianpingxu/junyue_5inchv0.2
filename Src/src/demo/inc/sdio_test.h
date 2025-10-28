/**
 * @file sdio_test.h
 * @author Product Application Department
 * @brief  SDIO 模块测试用例头文件，仅供参考
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
 * @defgroup SDIO SDIO模块
 * @ingroup Peripherals
 * @{
 */

#ifndef SDIO_TEST_H_
#define SDIO_TEST_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "sdio_hal.h"
#include "debug.h"

// 函数声明
void sdio_sd_test(void);
void sdio_fatfs_test(void);

#ifdef __cplusplus
}
#endif


/** @} */  // 结束 SDIO 模块分组
/** @} */  // 结束外设模块分组

#endif
