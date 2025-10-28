/**
 * @file libccm4211.h
 * @author Product application department
 * @brief  CCM4211 库函数接口头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __LIBCCM4211_H
#define __LIBCCM4211_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
#define LOCK_JTAG_KEY 0xA5A5A5A5

// 函数声明
void LIB_CPM_OscSwitch(int32_t osc_sel);

#ifdef __cplusplus
}
#endif

#endif