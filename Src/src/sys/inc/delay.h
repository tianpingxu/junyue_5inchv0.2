/**
 * @file delay.h
 * @author Product application department
 * @brief  DELAY 延迟配置头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 函数声明
void delay(__IO uint32_t time);
void delayms(__IO uint32_t delayms);
void delayus(__IO uint32_t delayus);

#ifdef __cplusplus
}
#endif

#endif
