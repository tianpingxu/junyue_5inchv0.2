/**
 *  @file dma2d_test.h
 *  @author Product application department
 *  @brief  DMA2D 模块测试用例头文件
 *  @version v1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup DMA2D DMA2D模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __DMA2D_TEST_H
#define __DMA2D_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif
    
// 头文件包含
#include "dma2d_hal.h"

// 全局变量定义
/**
 *  @brief  DMA2D 基本功能类型枚举
 *
 */
typedef enum
{
    REG2MEM_FUNC = 0,
    MEM2MEM_FUNC = 1,
    MEM2MEM_PFC_FUNC = 2,
    MEM2MEM_BLEND_FUNC = 3,
    MEM2MEM_MIRROR_V_FUNC = 4,
    MEM2MEM_MIRROR_H_FUNC = 5,
    MEM2MEM_FIX_ROT90_FUNC = 6,
    MEM2MEM_FIX_ROT180_FUNC = 7,
    MEM2MEM_FIX_ROT270_FUNC = 8,
    MEM2MEM_RBS_FUNC = 9,
    MEM2MEM_ROT_FUNC = 10
} dma2d_func_t;

// 函数声明
void dma2d_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 DMA2D 模块分组
/** @} */  // 结束外设模块分组

#endif
