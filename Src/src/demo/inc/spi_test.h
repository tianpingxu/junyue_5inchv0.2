/**
 * @file spi_test.h
 * @author Product application department
 * @brief  SPI 模块测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup SPI SPI模块
 * @ingroup Peripherals
 * @{
 */

#ifndef _SPI_TEST_H
#define _SPI_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "spi_hal.h"
#include "delay.h"
    
// 函数声明
void spi_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 SPI 模块分组
/** @} */  // 结束外设模块分组

#endif
