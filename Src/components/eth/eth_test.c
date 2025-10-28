/**
 * @file eth_test.c
 * @author Product application department
 * @brief  ETH 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup ThirdPart 第三方模块
 * @{
 *
 * @defgroup ETHERNET ETHERNET模块
 * @ingroup ThirdPart
 * @{
 */

// 头文件包含
#include "eth_test.h"
#include "iperf_client.h"
#include "sys_arch.h"
#include "bsp_eth.h"

/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "iperf_client.h"

// 全局变量定义
static TaskHandle_t AppTaskCreate_Handle = NULL;

// 函数定义
/**
 * @brief 任务创建函数
 *
 */
static void AppTaskCreate(void)
{
    BaseType_t xReturn = pdPASS;
    TCPIP_Init();

    iperf_client_init();

    vTaskDelete(AppTaskCreate_Handle);
}

/**
 * @brief ETH 模块测试示例函数
 *
 */
int eth_demo(void)
{
    BaseType_t xReturn = pdPASS;
    //    Eth_Reset();
    xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                          (const char *)"AppTaskCreate",
                          (uint16_t)512,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&AppTaskCreate_Handle);

    if (pdPASS == xReturn)
        vTaskStartScheduler();
    else
        return -1;

    while (1)
        ;
}

/** @} */  // 结束 ETHERNET 模块分组
/** @} */  // 结束外设模块分组
