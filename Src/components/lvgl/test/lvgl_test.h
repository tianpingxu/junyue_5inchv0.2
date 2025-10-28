/**
 * @file lvgl_test.h
 * @author Product application department
 * @brief  LVGL 测试用例头文件，仅供参考
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

#ifndef __LVGL_TEST_H_
#define __LVGL_TEST_H_
//头文件定义
#include "type.h"

// 函数声明
void LVGL_APP_Init(void);
void LVGL_APP_Run(void);
int LVGL_GetTouchIntStatus(void);
void LVGL_GetTouchCoords(int16_t *x, int16_t *y);
int LVGL_DISP_Color_Fill(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *color);
void lvgl_demo(void);


/** @} */  // 结束 LVGL 模块分组
/** @} */  // 结束外设模块分组

#endif
