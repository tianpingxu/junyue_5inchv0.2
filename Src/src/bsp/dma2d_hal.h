/**
 *  @file dma2d_hal.h
 *  @author Product application department
 *  @brief  DMA2D 模块硬件抽象层头文件
 *  @version v1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __DMA2D_HAL_H
#define __DMA2D_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "dma2d_drv.h"
#include "debug.h"
    
/**
 * @brief DMA2D 模块模式参数结构体定义
 * 
 */
typedef struct
{
    dma2d_color_mode_t color_mode;
    uint16_t pixels_per_line; // width
    uint16_t lines;           // height
    uint16_t output_offset;
    uint32_t out_addr;
    uint32_t out_color;
} dma2d_reg2mem_t;

/**
 * @brief  DMA2D 模块mem2mem or mem2mem pfc模式参数结构体定义
 * 
 */
typedef struct
{
    dma2d_color_mode_t fg_color_mode;
    dma2d_color_mode_t out_color_mode;    
    uint16_t pixels_per_line; // width
    uint16_t lines;           // height
    uint16_t fg_offset;
    uint16_t output_offset;
    uint32_t out_addr;
    uint32_t fg_addr;
} dma2d_mem2mem_t, dma2d_mem2mem_pfc_t;

/**
 * @brief DMA2D 模块mem2mem blend 模式参数结构体定义
 * 
 */
typedef struct
{
    dma2d_color_mode_t fg_color_mode;
    dma2d_color_mode_t bg_color_mode;
    dma2d_color_mode_t out_color_mode;
    dma2d_alpha_mode_t fg_alpha_mode;
    dma2d_alpha_mode_t bg_alpha_mode;
    uint8_t fg_fixed_alpha;
    uint8_t bg_fixed_alpha;
    uint16_t pixels_per_line; // width
    uint16_t lines;           // height
    uint16_t fg_offset;
    uint16_t bg_offset;
    uint16_t output_offset;
    uint32_t out_addr;
    uint32_t fg_addr;
    uint32_t bg_addr;
} dma2d_mem2mem_blend_t, dma2d_mem2mem_rbs_t;

/**
 * @brief  DMA2D 模块mem2mem mirror or fixed-rotate 模式参数结构体定义
 * 
 */
typedef struct
{
    dma2d_color_mode_t rotab_color_mode;
    dma2d_color_mode_t rotc_color_mode;
    uint16_t pixels_per_line;
    uint16_t lines;
    uint16_t rotab_offset;
    uint16_t rotc_offset;
    uint32_t rotc_addr;
    uint32_t rotab_addr;
} dma2d_mem2mem_mf_t;

/**
 * @brief DMA2D 模块mem2mem any-rotate 模式参数结构体定义
 * 
 */
typedef struct
{
    dma2d_color_mode_t rota_color_mode;
    dma2d_color_mode_t rotb_color_mode;
    dma2d_color_mode_t rotc_color_mode;
    dma2d_alpha_mode_t rota_alpha_mode;
    dma2d_alpha_mode_t rotb_alpha_mode;
    uint8_t rota_fixed_alpha;
    uint8_t rotb_fixed_alpha;
    uint16_t rota_center_w;
    uint16_t rota_center_h;
    uint16_t rota_w;
    uint16_t rota_h;
    uint16_t rotb_center_w;
    uint16_t rotb_center_h;
    uint16_t rotb_w;
    uint16_t rotb_h;
    uint32_t rotc_addr;
    uint32_t rota_addr;
    uint32_t rotb_addr;
    float sinv;
    float cosv;
} dma2d_mem2mem_rot_t;

// 函数声明
status_t hal_dma2d_reg2mem(dma_reg_t *pdma2d, dma2d_reg2mem_t *preg2mem);
status_t hal_dma2d_mem2mem(dma_reg_t *pdma2d, dma2d_mem2mem_t *pmem2mem);
status_t hal_dma2d_mem2mem_pfc(dma_reg_t *pdma2d, dma2d_mem2mem_pfc_t *pmem2mem_pfc);
status_t hal_dma2d_mem2mem_blend(dma_reg_t *pdma2d, dma2d_mem2mem_blend_t *pmem2mem_blend);
status_t hal_dma2d_mem2mem_rbs(dma_reg_t *pdma2d, dma2d_mem2mem_rbs_t *pmem2mem_rbs, uint8_t rbs_type);
status_t hal_dma2d_mem2mem_mf(dma_reg_t *pdma2d, dma2d_mem2mem_mf_t *pmem2mem_mf, dma2d_rot_ant_mode_t mf_type);
status_t hal_dma2d_mem2mem_rot(dma_reg_t *pdma2d, dma2d_mem2mem_rot_t *pmem2mem_rot, dma2d_rot_ant_mode_t rot_type);

#ifdef __cplusplus
}
#endif

#endif
