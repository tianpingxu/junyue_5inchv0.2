/**
 * @file uart_test.h
 * @author Product application department
 * @brief  UART 模块测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup UART UART模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __UART_TEST_H
#define __UART_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "uart_hal.h"
#include "cpm_drv.h"

// 函数声明
void uart_demo(void);

void buff_send_to_uart(uint8_t* buf, uint16_t len);

#ifdef __cplusplus
}
#endif


/** @} */  // 结束 UART 模块分组
/** @} */  // 结束外设模块分组

#endif
