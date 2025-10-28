/**
 *  @file dma2d_test.c
 *  @author Product application department
 *  @brief  DMA2D 模块测试用例，仅供参考
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

// 头文件包含
#include "dma2d_test.h"
#include "color_def.h"
// 全局变量定义

#define DMA2D_DEBUG 1

static dma2d_reg2mem_t preg2mem =
{
    .color_mode = CM_ARGB8888,
    .pixels_per_line = 16,
    .lines = 16,
    .output_offset = 0,
    .out_addr = 0x1C000000,
    .out_color = SEA_GREEN
};

static dma_reg_t *pdma2d;

// 函数定义
/**
 * @brief DMA2D 模块测试示例函数
 *
 */
void dma2d_demo(void)
{
    dma2d_func_t func = REG2MEM_FUNC;

    hal_dma2d_reg2mem(DMA2D, &preg2mem);
    if (DMA2D_DEBUG)
    {
        uint32_t paddr = preg2mem.out_addr;
        for (uint32_t num = 0; num < preg2mem.lines * preg2mem.pixels_per_line; num++)
        {
            if ((*(uint32_t *)(paddr + 4 * num)) == (preg2mem.out_color))
                printf("dma2d reg2mem test end!\r\n");
            else
                printf("dma2d reg2mem test error!\r\n");
        }
    }
}


/** @} */  // 结束 DMA2D 模块分组
/** @} */  // 结束外设模块分组
