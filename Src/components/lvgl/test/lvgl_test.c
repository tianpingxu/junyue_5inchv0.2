/**
 * @file lvgl_test.c
 * @author Product application department
 * @brief  LVGL 测试用例，仅供参考
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
 * @defgroup LVGL LVGL模块
 * @ingroup ThirdPart
 * @{
 */

// 头文件包含
#include <stdio.h>
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "systick_drv.h"
#include "lcd_interface.h"
#include "tp_interface.h"
#include "lvgl_test.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "cmsis_armclang.h"
#include "lv_port_fs.h"
#include "cpm_drv.h"

#include "custom.h"
#include "rgb_lcd.h"
#include "lcd_iap.h"
#include "iap_test.h"
uint8_t fsize_1 = 16;
uint8_t ypos_1 = 2;
uint16_t j_1 = 0;

// 全局变量定义
extern tp_handle_t tp_dev;
extern lcd_handle_t lcd_dev;

static TaskHandle_t AppTaskCreate_Handle = NULL;
static TaskHandle_t LVGL_Task_Handle = NULL;
SemaphoreHandle_t g_mutex;

// 函数定义

/**
 * @brief LVGL 心跳初始化
 *
 * @param
 */
void LVGL_SYSTICK_Init(void)
{

    SysTick_IRQHandler_Callback = drv_systick_handler;
    drv_systick_config(g_core_clk / 1000); // 1ms
    drv_systick_enable(TRUE);
}

/**
 * @brief LVGL FREERTOS心跳中断处理函数
 *
 */
void LVGL_SYSTIC_Handler(void)
{
    lv_tick_inc(1);
}

/**
 * @brief LVGL 裸跑心跳中断处理函数
 *
 */
void LVGL_TASK_Handler(void)
{
    lv_task_handler();
}

/**
 * @brief LVGL UI初始化函数
 *
 */
void LVGL_UI_Init(void)
{
    lv_init();
    lv_port_disp_init();
    lv_port_fs_init();
    lv_port_indev_init();
	
#if LV_USE_DEMO_WIDGETS
    extern void lv_demo_widgets(void);
    lv_demo_widgets();
#else

    custom_init();

#endif
}
/**
 * @brief LVGL 心跳FREERTOS 处理函数
 *
 */
void vApplicationTickHook()
{
    LVGL_SYSTIC_Handler();
}

/**
 * @brief LVGL 任务函数
 *
 * @param parameter
 */
static void LVGL_Task(void *parameter)
{
    while (1)
    {
        xSemaphoreTake(g_mutex, portMAX_DELAY);
        lv_task_handler();
        xSemaphoreGive(g_mutex);
        //      DelayMS_OS(5);
    }
}
/**
 * @brief LVGL 任务创建函数
 *
 */
static void AppTaskCreate(void)
{
    BaseType_t xReturn = pdPASS;
    taskENTER_CRITICAL();

    g_mutex = xSemaphoreCreateMutex();

    /* 创建LVGL UI任务 */
    xReturn = xTaskCreate((TaskFunction_t)LVGL_Task,
                          (const char *)"LVGL_Task",
                          (uint16_t)2048,
                          (void *)NULL,
                          (UBaseType_t)1,
                          (TaskHandle_t *)&LVGL_Task_Handle);
    if (pdPASS == xReturn)
        printf("Create lvgl display success...\r\n");

    xSemaphoreGive(g_mutex);

    vTaskDelete(AppTaskCreate_Handle);
    taskEXIT_CRITICAL();
}

/**
 * @brief LVGL 任务初始化函数
 *
 */
void LVGL_OS_Init(void)
{

    xTaskCreate((TaskFunction_t)AppTaskCreate,
                (const char *)"AppTaskCreate",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)1,
                (TaskHandle_t *)&AppTaskCreate_Handle);

    vTaskStartScheduler();
}

/**
 * @brief LVGL 显示初始化函数
 *
 */
void LVGL_DISP_Init(void)
{
    lcd_dev.lcd_itf_type = LCD_RGB;
    lcd_dev.lcd_ic = RGB_480854;
    lcd_dev.lcd_size.x = LCD_DISP_HOR_RES;
    lcd_dev.lcd_size.y = LCD_DISP_VER_RES;

    lcd_init(&lcd_dev);
}

/**
 * @brief LVGL 刷屏初始化函数
 *
 * @param x1 X轴开始坐标
 * @param y1 Y轴开始坐标
 * @param x2 X轴结束坐标
 * @param y2 Y轴结束坐标
 * @param color 颜色显示
 * @return int
 */
int LVGL_DISP_Color_Fill(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *color)
{
    return lcd_write_dots(&lcd_dev, 0, 0, lcd_dev.lcd_size.x, lcd_dev.lcd_size.y, color);
}

/**
 * @brief LVGL 触摸初始化函数
 *
 */
void LVGL_TP_Init(void)
{
    tp_dev.touchtype = TP_INTERFACE;
    tp_init(&tp_dev);
}
/**
 * @brief LVGL 获取触摸状态函数
 *
 * @return int
 */
int LVGL_GetTouchIntStatus(void)
{
    return tp_get_status();
}

/**
 * @brief LVGL 获取触摸坐标函数
 *
 * @param x
 * @param y
 */
void LVGL_GetTouchCoords(int16_t *x, int16_t *y)
{
    tp_getxy(x, y);
}
/**
 * @brief LVGL 测试例程初始化函数
 *
 */
void LVGL_APP_Init(void)
{
    LVGL_DISP_Init();
    LVGL_TP_Init(); // 如果需要使用触摸，注意下gt911.c文件不开优化

    LVGL_UI_Init();
    LVGL_SYSTICK_Init();
}
#include "libaxiflow.h"
/**
 * @brief LVGL 模块测试示例函数
 * @param
 */
void lvgl_demo(void)
{

    // axiflow_cdc_blend();
    // uint8_t cpuqos_w = axi_get_wr_qos(AXI_M6_CPU_PORT_QOS_ID);
    // uint8_t cpuqos_r = axi_get_rd_qos(AXI_M6_CPU_PORT_QOS_ID);
    
    // uint8_t cdcqos_w = axi_get_wr_qos(AXI_M3_CDC_PORT_QOS_ID);
    // uint8_t cdcqos_r = axi_get_rd_qos(AXI_M3_CDC_PORT_QOS_ID);


    // printf("cpu w qos = %d\r\n", cpuqos_w);
    // printf("cpu r qos = %d\r\n", cpuqos_r);
    // printf("cdc w qos = %d\r\n", cdcqos_w);
    // printf("cdc r qos = %d\r\n", cdcqos_r);


    // axi_set_wr_qos(AXI_M6_CPU_PORT_QOS_ID, 1);
    // axi_set_rd_qos(AXI_M6_CPU_PORT_QOS_ID, 1);

    // axi_set_wr_qos(AXI_M3_CDC_PORT_QOS_ID, 15);
    // axi_set_rd_qos(AXI_M3_CDC_PORT_QOS_ID, 15);


    // cpuqos_w = axi_get_wr_qos(AXI_M6_CPU_PORT_QOS_ID);
    // cpuqos_r = axi_get_rd_qos(AXI_M6_CPU_PORT_QOS_ID);

    // cdcqos_w = axi_get_wr_qos(AXI_M3_CDC_PORT_QOS_ID);
    // cdcqos_r = axi_get_rd_qos(AXI_M3_CDC_PORT_QOS_ID);

    // printf("cpu w qos = %d\r\n", cpuqos_w);
    // printf("cpu r qos = %d\r\n", cpuqos_r);
    // printf("cdc w qos = %d\r\n", cdcqos_w);
    // printf("cdc r qos = %d\r\n", cdcqos_r);


    // axi_set_wr_token_enable(AXI_M6_CPU_PORT_TOKEN_ID, TOKEN_H_512, 2);
    // axi_set_rd_token_enable(AXI_M6_CPU_PORT_TOKEN_ID, TOKEN_H_512, 2);

    LVGL_APP_Init();

#ifdef LVGL_OS // if define 'LVGL_OS' in MDK 'Options/C/C++/Preprocessor Symbols', then freertos will run

    LVGL_OS_Init();
#endif

#ifdef LVGL_MCU // if define 'LVGL_MCU' in MDK 'Options/C/C++/Preprocessor Symbols', then MCU will run

    while (1)
    {
        LVGL_TASK_Handler();
    }
#endif
}

/** @} */ // 结束 LVGL 模块分组
/** @} */ // 结束外设模块分组
