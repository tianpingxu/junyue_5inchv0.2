/**
 * @file freertos_test.h
 * @author Product application department
 * @brief  FREERTOS 测试用例头文件
 * @version V1.0
 * @date 2025-03-01
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

/**
 * @defgroup ThirdPart 第三方模块
 * @{
 *
 * @defgroup FREERTOS FREERTOS模块
 * @ingroup ThirdPart
 * @{
 */

#ifndef _FREERTOS_TEST_H
#define _FREERTOS_TEST_H

// 头文件包含
#include "FreeRTOS.h"
#include "task.h"

// 全局变量定义
#define Pend_SVC_SysTick_EN 1
#define FIRST_TASK_PRIO        3
#define FIRST_STK_SIZE         512
#define FREERTOSLOG_DEBUG(...) printf(__VA_ARGS__) 
extern TaskHandle_t FirstTask_Handler;
#define SECOND_TASK_PRIO        3
#define SECOND_STK_SIZE         512

extern TaskHandle_t SecondTask_Handler;
 
// 函数声明
void freertos_demo(void);

/** @} */  // 结束 FREERTOS 模块分组
/** @} */  // 结束外设模块分组

#endif
