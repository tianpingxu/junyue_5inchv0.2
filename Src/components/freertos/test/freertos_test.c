/**
 * @file freertos_test.c
 * @author Product application department
 * @brief  FREERTOS 测试用例，仅供参考
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

// 头文件包含
#include "freertos_test.h"
#include "systick_drv.h"
#include "interrupt.h"

// 全局变量定义
TaskHandle_t FirstTask_Handler;
TaskHandle_t SecondTask_Handler;
#define START_TASK_PRIO        1
#define START_STK_SIZE         1024

StaticTask_t StartTaskTCB;
static TaskHandle_t StartTask_Handler = NULL;

// 函数定义
/**
 * @brief 任务1函数
 * 
 * @return TaskFunction_t 
 */
TaskFunction_t os_first_task(void)
{
    FREERTOSLOG_DEBUG("begin FIRST task.\r\n");

    while(1)
    {
        FREERTOSLOG_DEBUG("FIRST.\n");
        vTaskDelay(500);
    }
}

/**
 * @brief 任务2函数
 * 
 * @return TaskFunction_t 
 */


TaskFunction_t os_second_task(void)
{
    FREERTOSLOG_DEBUG("begin SECOND task.\r\n");

    while(1)
    {
        FREERTOSLOG_DEBUG("SECOND.\n");
        vTaskDelay(500);
    }
}

/**
 * @brief 创建任务函数
 * 
 */
static void StartTaskCreate(void)
{
      BaseType_t xReturn = pdPASS;
    FREERTOSLOG_DEBUG("%s\r\n", __FUNCTION__);
    taskENTER_CRITICAL();
      xReturn = xTaskCreate((TaskFunction_t)os_first_task,          
                          (const char *)"first_task",         
                          (uint16_t)FIRST_STK_SIZE,                    
                          (void *)NULL,                     
                          (UBaseType_t)FIRST_TASK_PRIO,                      
                          (TaskHandle_t *)&FirstTask_Handler); 
    if (pdPASS == xReturn)
        FREERTOSLOG_DEBUG("Create os_first_task success...\r\n");
        else
            FREERTOSLOG_DEBUG("Create os_first_task failed...\r\n");
        
        xReturn = xTaskCreate((TaskFunction_t)os_second_task,           
                          (const char *)"second_task",           
                          (uint16_t)SECOND_STK_SIZE,                     
                          (void *)NULL,                   
                          (UBaseType_t)SECOND_TASK_PRIO,                      
                          (TaskHandle_t *)&SecondTask_Handler);  
    if (pdPASS == xReturn)
        FREERTOSLOG_DEBUG("Create os_second_task success...\r\n");
        else
              FREERTOSLOG_DEBUG("Create os_second_task failed...\r\n");
    vTaskDelete(StartTask_Handler); //del start
    taskEXIT_CRITICAL();
}


/**
 * @brief FREERTOS 测试示例函数
 * 
 */
void freertos_demo(void)
{
   BaseType_t xReturn = pdPASS;
     SysTick_IRQHandler_Callback = drv_systick_handler;
     FREERTOSLOG_DEBUG("%s\r\n", __FUNCTION__);
     /* 创建开始任务 */
   xReturn = xTaskCreate((TaskFunction_t)StartTaskCreate,                             
                (const char *)"StartTaskCreate",                              
                (uint16_t)START_STK_SIZE,                                                     
                (void *)NULL,                                                      
                (UBaseType_t)START_TASK_PRIO,                                                        
                (TaskHandle_t *)&StartTask_Handler);        
    if(pdPASS == xReturn)
    {
        vTaskStartScheduler();
    }
    else
    {
        FREERTOSLOG_DEBUG("create AppTaskCreate failed\n");
    }
                                
}

/** @} */  // 结束 FREERTOS 模块分组
/** @} */  // 结束外设模块分组

