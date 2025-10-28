///*
// * FreeRTOS Kernel V10.3.1
// * Copyright (C) 2020 FreeRTOS.com, Inc. or its affiliates.  All Rights Reserved.
// *
// * Permission is hereby granted, free of charge, to any person obtaining a copy of
// * this software and associated documentation files (the "Software"), to deal in
// * the Software without restriction, including without limitation the rights to
// * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// * the Software, and to permit persons to whom the Software is furnished to do so,
// * subject to the following conditions:
// *
// * The above copyright notice and this permission notice shall be included in all
// * copies or substantial portions of the Software.
// *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// *
// * http://www.FreeRTOS.org
// * http://aws.FreeRTOS.com/freertos
// *
// * 1 tab == 4 spaces!
// */

//#ifndef FREERTOS_CONFIG_H
//#define FREERTOS_CONFIG_H

///*-----------------------------------------------------------
// * Application specific definitions.
// *
// * These definitions should be adjusted for your particular hardware and
// * application requirements.
// *
// * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
// * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
// *
// * See http://www.freertos.org/a00110.html
// *----------------------------------------------------------*/

///* Here is a good place to include header files that are required across
//your application. */

//#include "hal.h"


///**************************************************************************
// *                         FreeRTOS 基础配置选项
// *************************************************************************/
////1:使能抢占式调度
//#define configUSE_PREEMPTION                  1
////1：使能时间片调度
//#define configUSE_TIME_SLICING                  1
////1. 使能低功耗Tickless模式
//#define configUSE_TICKLESS_IDLE                 0
////用于定义CPU内核时钟频率
//#define configCPU_CLOCK_HZ                        (g_core_clk)
////RTOS系统节拍中断的频率，也即一秒中断的次数
//#define configTICK_RATE_HZ                        ( ( TickType_t ) 1000 )
////可使用最大优先级
//#define configMAX_PRIORITIES                  ( 5 )
////空闲任务使用的最小栈的大小
//#define configMINIMAL_STACK_SIZE              ( ( unsigned short ) 32 )
////任务名字符串长度
//#define configMAX_TASK_NAME_LEN                   ( 16 )
////如果希望包括其他结构成员和功能以帮助执行可视化和跟踪，请设置为1
//#define configUSE_TRACE_FACILITY              0
////节拍计数器变量
//#define configUSE_16_BIT_TICKS                    0
////用于控制空闲优先级任务的行为， 1： 正在使用抢占式调度程序给用户任务抢占， 2：该应用程序创建以空闲优先级运行的任务
//#define configIDLE_SHOULD_YIELD                   1
////1：开启任务通知功能
//#define configUSE_TASK_NOTIFICATIONS            1
////设置任务通知数组索引
//#define configTASK_NOTIFICATION_ARRAY_ENTRIES   3
////1：使用互斥信号量
//#define configUSE_MUTEXES                       1
////1：使用递归互斥信号量
//#define configUSE_RECURSIVE_MUTEXES             1
////1：使用计数信号量
//#define configUSE_COUNTING_SEMAPHORES           1
//#define configUSE_ALTERNATIVE_API               0 /* Deprecated! */
////设置可以注册的信号量和消息队列个数
//#define configQUEUE_REGISTRY_SIZE               10
//#define configUSE_QUEUE_SETS                    1
//////1：使能时间片调度
////#define configUSE_TIME_SLICING                  0


///* Memory allocation related definitions. */
////1: 内存静态分配
//#define configSUPPORT_STATIC_ALLOCATION         1
////1: 内存动态分配，没有配置此选项时系统默认使用动态分配方式
//#define configSUPPORT_DYNAMIC_ALLOCATION        1
////堆大小
//#define configTOTAL_HEAP_SIZE                 ( ( size_t ) ( 8 * 1024 ) )
////1: 允许应用程序将堆放在内存中的任意位置
//#define configAPPLICATION_ALLOCATED_HEAP        0

///************* Hook function related definitions. ***************/
////1: 使用IDLE钩子函数
//#define configUSE_IDLE_HOOK                       0
////1: 使用tick的钩子函数
//#define configUSE_TICK_HOOK                       1
//#define configCHECK_FOR_STACK_OVERFLOW          0
////1：内存分配失败时的一个钩子函数，由用户自行实现
//#define configUSE_MALLOC_FAILED_HOOK            0
//#define configUSE_DAEMON_TASK_STARTUP_HOOK      0


///*************** Co-routine definitions. **************/

////启用协程配置选项
//#define configUSE_CO_ROUTINES                     0
//#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )


///************ Software timer related definitions. *************/

////启用软件定时器
//#define configUSE_TIMERS                        1
////软件定时器优先级
//#define configTIMER_TASK_PRIORITY               3
////软件定时器队列长度
//#define configTIMER_QUEUE_LENGTH                10
////软件定时器任务栈大小
//#define configTIMER_TASK_STACK_DEPTH            configMINIMAL_STACK_SIZE

///* Define to trap errors during development. */
////#define configASSERT( ( x ) ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

///* FreeRTOS MPU specific definitions. */
//#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
//#define configTOTAL_MPU_REGIONS                                8        /* Default value. */
//#define configTEX_S_C_B_FLASH                                  0x07UL   /* Default value. */
//#define configTEX_S_C_B_SRAM                                   0x07UL   /* Default value. */
//#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY            1


///* Optional functions - most linkers will remove unused functions anyway. */
///***********************可选函数配置选项**************************/
//#define INCLUDE_vTaskPrioritySet                1
//#define INCLUDE_uxTaskPriorityGet               1
//#define INCLUDE_vTaskDelete                     1
//#define INCLUDE_vTaskSuspend                    1
//#define INCLUDE_xResumeFromISR                  0
//#define INCLUDE_vTaskDelayUntil                 1
//#define INCLUDE_vTaskDelay                      1
//#define INCLUDE_xTaskGetSchedulerState          1
//#define INCLUDE_xTaskGetCurrentTaskHandle       1
//#define INCLUDE_uxTaskGetStackHighWaterMark     0
//#define INCLUDE_xTaskGetIdleTaskHandle          0
//#define INCLUDE_eTaskGetState                   0
//#define INCLUDE_xEventGroupSetBitFromISR        1
//#define INCLUDE_xTimerPendFunctionCall          0
//#define INCLUDE_xTaskAbortDelay                 0
//#define INCLUDE_xTaskGetHandle                  0
//#define INCLUDE_xTaskResumeFromISR              1


///*******************************************************
// *                    中断优先级的设置
// * ****************************************************/
//#ifdef __NVIC_PRIO_BITS

//    // 这里 __NVIC_PRIO_BITS 被定义等于 3； 所以优先级从：0-7；
//    #define configPRIO_BITS __NVIC_PRIO_BITS

//#else
//    #define configPRIO_BITS 8           /* 64 priority levels */
//#endif

//#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY               0x07
//#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY          2

////系统中断时钟优先级
//#define configKERNEL_INTERRUPT_PRIORITY ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
////最高优先级，任何调用系统API的逻辑中断优先级应该小于此数值
//#define configMAX_SYSCALL_INTERRUPT_PRIORITY ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

//// /* This is the raw value as per the Cortex-M7 NVIC.  Values can be 8
//// (lowest) to 0 (1?) (highest). */
//// #define configKERNEL_INTERRUPT_PRIORITY        7
//// /* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
//// See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
//// #define configMAX_SYSCALL_INTERRUPT_PRIORITY   1 /* priority 1. */

//// #define configLIBRARY_KERNEL_INTERRUPT_PRIORITY    5

///*********************************************************
// *         与中断函数相关的服务配置选项
// * ******************************************************/
// #define xPortPendSVHandler    PendSV_Handler
// #define vPortSVCHandler       SVC_Handler
// #ifdef COMMON_TASK_DEMO
// #define xPortSysTickHandler     SysTick_Handler
// #endif

//#endif /* FREERTOS_CONFIG_H */
/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

*/



#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


//Õë¶Ô²»Í¬µÄ±àÒëÆ÷µ÷ÓÃ²»Í¬µÄstdint.hÎÄ¼þ
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include "stdio.h"
    #include <stdint.h>
    extern volatile uint32_t g_sys_clk;
#endif

//¶ÏÑÔ
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

#define configUSE_PREEMPTION                      1

#define configUSE_TIME_SLICING                  1

#define configUSE_PORT_OPTIMISED_TASK_SELECTION         1

#define configUSE_TICKLESS_IDLE                                                 0

#define configCPU_CLOCK_HZ                        g_sys_clk //(g_core_clk)

#define configTICK_RATE_HZ                        (( TickType_t )1000)

#define configMAX_PRIORITIES                      (5)

#define configMINIMAL_STACK_SIZE                ((unsigned short)32)

#define configMAX_TASK_NAME_LEN                 (16)

#define configUSE_16_BIT_TICKS                  0

#define configIDLE_SHOULD_YIELD                 1

#define configUSE_QUEUE_SETS                      0

#define configUSE_TASK_NOTIFICATIONS    1

#define configUSE_MUTEXES                           1

#define configUSE_RECURSIVE_MUTEXES         1

#define configUSE_COUNTING_SEMAPHORES       1

#define configQUEUE_REGISTRY_SIZE               10

#define configUSE_APPLICATION_TASK_TAG        0



#define configSUPPORT_DYNAMIC_ALLOCATION        1

#define configSUPPORT_STATIC_ALLOCATION                 0

#define configTOTAL_HEAP_SIZE                   ((size_t)(10*1024))


#define configUSE_IDLE_HOOK                     0

#define configUSE_TICK_HOOK                     1

#define configUSE_MALLOC_FAILED_HOOK            0

#define configCHECK_FOR_STACK_OVERFLOW          0

#define configGENERATE_RUN_TIME_STATS           0

#define configUSE_TRACE_FACILITY                      0

#define configUSE_STATS_FORMATTING_FUNCTIONS    1


#define configUSE_CO_ROUTINES                     0

#define configMAX_CO_ROUTINE_PRIORITIES       ( 2 )


#define configUSE_TIMERS                            0

#define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES-1)

#define configTIMER_QUEUE_LENGTH                10

#define configTIMER_TASK_STACK_DEPTH          (configMINIMAL_STACK_SIZE*2)

#define INCLUDE_xTaskGetSchedulerState       1
#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                        1
#define INCLUDE_vTaskCleanUpResources          1
#define INCLUDE_vTaskSuspend                       1
#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_vTaskDelay                         1
#define INCLUDE_eTaskGetState                      1
#define INCLUDE_xTimerPendFunctionCall       0
//#define INCLUDE_xTaskGetCurrentTaskHandle       1
//#define INCLUDE_uxTaskGetStackHighWaterMark     0
//#define INCLUDE_xTaskGetIdleTaskHandle          0

#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS             __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS             3
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         7

#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )    /* 240 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define xPortPendSVHandler  PendSV_Handler
#define vPortSVCHandler     SVC_Handler


#if ( configUSE_TRACE_FACILITY == 1 )
    #include "trcRecorder.h"
    #define INCLUDE_xTaskGetCurrentTaskHandle               1
#endif


#endif /* FREERTOS_CONFIG_H */


