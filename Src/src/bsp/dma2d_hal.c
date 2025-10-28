/**
 *  @file dma2d_hal.c
 *  @author Product application department
 *  @brief  DMA2D 模块硬件抽象层，供应用层调用，仅供参考
 *  @version v1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "dma2d_hal.h"

// 全局变量定义
extern dma_reg_t *pdma2d;

// 函数定义
/**
 * @brief 获取DMA2D颜色模式对应的字节数
 * 
 * @param color_mode 
 * @return uint8_t 
 */
uint8_t hal_get_byte_color_mode(dma2d_color_mode_t color_mode)
{
    switch (color_mode)
    {
        case CM_ARGB8888:
        case CM_RGBA8888:
        case CM_BGRA8888:
        case CM_ABGR8888:
        case CM_XRGB8888:
        case CM_XBGR8888:
        case CM_RGBX8888:
        case CM_BGRX8888:
            return 4; // 32 bits
        case CM_RGB888:
        case CM_BGR888:
            return 3; // 24 bits
        case CM_RGB565:
        case CM_BGR565:
            return 2; // 16 bits
        case CM_ARGB1555:
        case CM_ARGB4444:
        case CM_AL88:
            return 2; // 16 bits
        case CM_L8:
        case CM_GRAY:
        case CM_A8:
        case CM_AL44:
        case CM_L4:
        case CM_A4:
            return 1; // 8 bits
    }
}


/**
 *  @brief  DMA2D reg2mem 模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param preg2mem reg2mem 模式参数结构体
 *  @return status_t  函数运行状态
 */
status_t hal_dma2d_reg2mem(dma_reg_t *pdma2d, dma2d_reg2mem_t *preg2mem)
{
    dma2d_work_mode_t workmode = REG2MEM;
    uint32_t timeout = 0x00;

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_fg_color_mode_set(pdma2d, preg2mem->color_mode);
    drv_dma2d_output_color_mode_set(pdma2d, preg2mem->color_mode);
    drv_dma2d_output_color_set(pdma2d, preg2mem->out_color);
    drv_dma2d_output_color_addr_set(pdma2d, preg2mem->out_addr);
    drv_dma2d_out_line_offset_set(pdma2d, preg2mem->output_offset);
    drv_dma2d_pixels_and_lines_set(pdma2d, preg2mem->pixels_per_line, preg2mem->lines);
    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("reg2mem error\r\n");
            return STATUS_TIMEOUT;
        }
    }
    
    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)preg2mem->out_addr, 
        preg2mem->pixels_per_line * preg2mem->lines * hal_get_byte_color_mode(preg2mem->color_mode));

    return STATUS_OK;
}

/**
 *  @brief  DMA2D mem2mem 模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pmem2mem mem2mem 模式参数结构体
 *  @return status_t  函数运行状态
 */
status_t hal_dma2d_mem2mem(dma_reg_t *pdma2d, dma2d_mem2mem_t *pmem2mem)
{
    dma2d_work_mode_t workmode = MEM2MEM;
    uint32_t timeout = 0x00;

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_fg_color_mode_set(pdma2d, pmem2mem->fg_color_mode);
    drv_dma2d_output_color_mode_set(pdma2d, pmem2mem->out_color_mode);

    drv_dma2d_fg_addr_set(pdma2d, pmem2mem->fg_addr);
    drv_dma2d_output_color_addr_set(pdma2d, pmem2mem->out_addr);
    drv_dma2d_out_line_offset_set(pdma2d, pmem2mem->output_offset);
    drv_dma2d_fg_line_offset_set(pdma2d, pmem2mem->fg_offset);

    drv_dma2d_pixels_and_lines_set(pdma2d, pmem2mem->pixels_per_line, pmem2mem->lines);
    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem error\r\n");
            return STATUS_TIMEOUT;
        }
    }
    
    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)pmem2mem->out_addr, 
        pmem2mem->pixels_per_line * pmem2mem->lines * hal_get_byte_color_mode(pmem2mem->out_color_mode));

    return STATUS_OK;
}

/**
 *  @brief  DMA2D mem2mem pfc 模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pmem2mem_pfc mem2mem_pfc 模式参数结构体
 *  @return status_t  函数运行状态
 */
status_t hal_dma2d_mem2mem_pfc(dma_reg_t *pdma2d, dma2d_mem2mem_pfc_t *pmem2mem_pfc)
{
    dma2d_work_mode_t workmode = MEM2MEM_PFC;
    uint32_t timeout = 0x00;

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_fg_color_mode_set(pdma2d, pmem2mem_pfc->fg_color_mode);
    drv_dma2d_output_color_mode_set(pdma2d, pmem2mem_pfc->out_color_mode);

    drv_dma2d_fg_addr_set(pdma2d, pmem2mem_pfc->fg_addr);
    drv_dma2d_output_color_addr_set(pdma2d, pmem2mem_pfc->out_addr);
    drv_dma2d_out_line_offset_set(pdma2d, pmem2mem_pfc->output_offset);
    drv_dma2d_fg_line_offset_set(pdma2d, pmem2mem_pfc->fg_offset);

    drv_dma2d_pixels_and_lines_set(pdma2d, pmem2mem_pfc->pixels_per_line, pmem2mem_pfc->lines);
    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem pfc error\r\n");
            return STATUS_TIMEOUT;
        }
    }
    
    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)pmem2mem_pfc->out_addr, 
        pmem2mem_pfc->pixels_per_line * pmem2mem_pfc->lines * hal_get_byte_color_mode(pmem2mem_pfc->out_color_mode));

    return STATUS_OK;
}

/**
 *  @brief  DMA2D mem2mem blend 模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pmem2mem_pfc mem2mem_blend 模式参数结构体
 *  @return status_t  函数运行状态
 */
status_t hal_dma2d_mem2mem_blend(dma_reg_t *pdma2d, dma2d_mem2mem_blend_t *pmem2mem_blend)
{
    dma2d_work_mode_t workmode = MEM2MEM_BLEND;
    uint32_t timeout = 0x00;

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_fg_color_mode_set(pdma2d, pmem2mem_blend->fg_color_mode);
    drv_dma2d_bg_color_mode_set(pdma2d, pmem2mem_blend->bg_color_mode);
    drv_dma2d_output_color_mode_set(pdma2d, pmem2mem_blend->out_color_mode);

    drv_dma2d_fg_addr_set(pdma2d, pmem2mem_blend->fg_addr);
    drv_dma2d_bg_addr_set(pdma2d, pmem2mem_blend->bg_addr);
    drv_dma2d_output_color_addr_set(pdma2d, pmem2mem_blend->out_addr);

    drv_dma2d_out_line_offset_set(pdma2d, pmem2mem_blend->output_offset);
    drv_dma2d_fg_line_offset_set(pdma2d, pmem2mem_blend->fg_offset);
    drv_dma2d_bg_line_offset_set(pdma2d, pmem2mem_blend->bg_offset);

    if (pmem2mem_blend->fg_alpha_mode <= REPLACE_BY_ALPHA_AND_CHN)
    {
        drv_dma2d_fg_pfc_alpha_set(pdma2d, pmem2mem_blend->fg_alpha_mode, pmem2mem_blend->fg_fixed_alpha);
    }
    else
    {
        return STATUS_ERROR;
    }

    if (pmem2mem_blend->bg_alpha_mode <= REPLACE_BY_ALPHA_AND_CHN)
    {
        drv_dma2d_bg_pfc_alpha_set(pdma2d, pmem2mem_blend->bg_alpha_mode, pmem2mem_blend->bg_fixed_alpha);
    }
    else
    {
        return STATUS_ERROR;
    }

    drv_dma2d_pixels_and_lines_set(pdma2d, pmem2mem_blend->pixels_per_line, pmem2mem_blend->lines);
    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem blend error\r\n");
            return STATUS_TIMEOUT;
        }
    }
    
    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)pmem2mem_blend->out_addr, 
        pmem2mem_blend->pixels_per_line * pmem2mem_blend->lines * hal_get_byte_color_mode(pmem2mem_blend->out_color_mode));

    return STATUS_OK;
}

/**
 *  @brief  DMA2D mem2mem blend rbs模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pmem2mem_rbs mem2mem_rbs 模式参数结构体
 *  @param rbs_type rbs 模式选择
 *  @return status_t  函数运行状态
 */
status_t hal_dma2d_mem2mem_rbs(dma_reg_t *pdma2d, dma2d_mem2mem_rbs_t *pmem2mem_rbs, uint8_t rbs_type)
{
    dma2d_work_mode_t workmode = MEM2MEM_BLEND;
    uint32_t timeout = 0x00;

    if (rbs_type > 3)
    {
        return STATUS_ERROR;
    }

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_fg_color_mode_set(pdma2d, pmem2mem_rbs->fg_color_mode);
    drv_dma2d_bg_color_mode_set(pdma2d, pmem2mem_rbs->bg_color_mode);
    drv_dma2d_output_color_mode_set(pdma2d, pmem2mem_rbs->out_color_mode);

    drv_dma2d_fg_addr_set(pdma2d, pmem2mem_rbs->fg_addr);
    drv_dma2d_bg_addr_set(pdma2d, pmem2mem_rbs->bg_addr);
    drv_dma2d_output_color_addr_set(pdma2d, pmem2mem_rbs->out_addr);

    drv_dma2d_out_line_offset_set(pdma2d, pmem2mem_rbs->output_offset);
    drv_dma2d_fg_line_offset_set(pdma2d, pmem2mem_rbs->fg_offset);
    drv_dma2d_bg_line_offset_set(pdma2d, pmem2mem_rbs->bg_offset);

    if (pmem2mem_rbs->fg_alpha_mode <= REPLACE_BY_ALPHA_AND_CHN)
    {
        drv_dma2d_fg_pfc_alpha_set(pdma2d, pmem2mem_rbs->fg_alpha_mode, pmem2mem_rbs->fg_fixed_alpha);
    }
    else
    {
        return STATUS_ERROR;
    }

    if (pmem2mem_rbs->bg_alpha_mode <= REPLACE_BY_ALPHA_AND_CHN)
    {
        drv_dma2d_bg_pfc_alpha_set(pdma2d, pmem2mem_rbs->bg_alpha_mode, pmem2mem_rbs->bg_fixed_alpha);
    }
    else
    {
        return STATUS_ERROR;
    }

    drv_dma2d_byte_swap_set(pdma2d, rbs_type, DMA2D_EN);
    drv_dma2d_pixels_and_lines_set(pdma2d, pmem2mem_rbs->pixels_per_line, pmem2mem_rbs->lines);
    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem rbs error\r\n");
            return STATUS_TIMEOUT;
        }
    }

    
    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)pmem2mem_rbs->out_addr, 
        pmem2mem_rbs->pixels_per_line * pmem2mem_rbs->lines * hal_get_byte_color_mode(pmem2mem_rbs->out_color_mode));


    return STATUS_OK;
}

/**
 *  @brief  DMA2D mem2mem mirror or fixed-rotate 模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pmem2mem_mf mem2mem_rbs 模式参数结构体
 *  @param mf_type mf_type 模式选择
 *  @return status_t  函数运行状态
 *  @note 包含固定角度旋转的操作（90°或者270°）时，输出后 width 与 height 需要互换，旋转方向为顺时针
 */
status_t hal_dma2d_mem2mem_mf(dma_reg_t *pdma2d, dma2d_mem2mem_mf_t *pmem2mem_mf, dma2d_rot_ant_mode_t mf_type)
{
    dma2d_work_mode_t workmode = MEM2MEM_PFC;
    uint32_t timeout = 0x00;

    if (mf_type > ROT_ANT_VER_ROTATE_270)
    {
        return STATUS_ERROR;
    }

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_rota_color_mode_set(pdma2d, pmem2mem_mf->rotab_color_mode);
    drv_dma2d_rotb_color_mode_set(pdma2d, pmem2mem_mf->rotab_color_mode);
    drv_dma2d_rotc_color_mode_set(pdma2d, pmem2mem_mf->rotc_color_mode);

    drv_dma2d_rota_addr_set(pdma2d, pmem2mem_mf->rotab_addr);
    drv_dma2d_rotb_addr_set(pdma2d, pmem2mem_mf->rotab_addr);
    drv_dma2d_rotc_color_addr_set(pdma2d, pmem2mem_mf->rotc_addr);

    drv_dma2d_rota_pixels_and_lines_set(pdma2d, pmem2mem_mf->pixels_per_line, pmem2mem_mf->lines);
    drv_dma2d_rotb_pixels_and_lines_set(pdma2d, pmem2mem_mf->pixels_per_line, pmem2mem_mf->lines);

    drv_dma2d_rot_ant_config_set(pdma2d, mf_type);
    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem mf error\r\n");
            return STATUS_TIMEOUT;
        }
    }

    while (drv_dma2d_rot_ant_status_get(pdma2d) != 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem mf error\r\n");
            return STATUS_TIMEOUT;
        }
    }

    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)pmem2mem_mf->rotc_addr, 
        pmem2mem_mf->pixels_per_line * pmem2mem_mf->lines * hal_get_byte_color_mode(pmem2mem_mf->rotc_color_mode));

    return STATUS_OK;
}

/**
 *  @brief  DMA2D mem2mem any-rotate 模式配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pmem2mem_rot mem2mem_rot 模式参数结构体
 *  @param rot_type any-rotate 模式选择
 *  @return status_t  函数运行状态
 */
status_t hal_dma2d_mem2mem_rot(dma_reg_t *pdma2d, dma2d_mem2mem_rot_t *pmem2mem_rot, dma2d_rot_ant_mode_t rot_type)
{
    dma2d_work_mode_t workmode = MEM2MEM_BLEND;
    uint32_t timeout = 0x00;
    
    if (rot_type != 32 && rot_type != 96)
    {
        return STATUS_ERROR;
    }
    if (pmem2mem_rot->rota_h < pmem2mem_rot->rota_center_h || pmem2mem_rot->rota_w < pmem2mem_rot->rota_center_w || pmem2mem_rot->rotb_h < pmem2mem_rot->rotb_center_h || pmem2mem_rot->rota_w < pmem2mem_rot->rotb_center_w)
    {
        return STATUS_ERROR;
    }

    drv_dma2d_mode_clear();
    drv_dma2d_start_en(pdma2d, DMA2D_DIS);
    drv_dma2d_mode_set(pdma2d, workmode);
    drv_dma2d_rota_color_mode_set(pdma2d, pmem2mem_rot->rota_color_mode);
    drv_dma2d_rotb_color_mode_set(pdma2d, pmem2mem_rot->rotb_color_mode);
    drv_dma2d_rotc_color_mode_set(pdma2d, pmem2mem_rot->rotc_color_mode);

    drv_dma2d_rota_addr_set(pdma2d, pmem2mem_rot->rota_addr);
    drv_dma2d_rotb_addr_set(pdma2d, pmem2mem_rot->rotb_addr);
    drv_dma2d_rotc_color_addr_set(pdma2d, pmem2mem_rot->rotc_addr);

    drv_dma2d_rot_sin_val_set(pdma2d, pmem2mem_rot->sinv);
    drv_dma2d_rot_cos_val_set(pdma2d, pmem2mem_rot->cosv);
    
    drv_dma2d_rota_center_config_set(pdma2d, pmem2mem_rot->rota_center_w, pmem2mem_rot->rotb_center_w);
    drv_dma2d_rotb_center_config_set(pdma2d, pmem2mem_rot->rotb_center_w, pmem2mem_rot->rotb_center_h);

    drv_dma2d_rota_pixels_and_lines_set(pdma2d, pmem2mem_rot->rota_w, pmem2mem_rot->rota_h);
    drv_dma2d_rotb_pixels_and_lines_set(pdma2d, pmem2mem_rot->rotb_w, pmem2mem_rot->rotb_h);

    drv_dma2d_rot_ant_config_set(pdma2d, rot_type);

    drv_dma2d_start_en(pdma2d, DMA2D_EN);

    while ((drv_dma2d_intr_status_get(pdma2d) & DMA2D_TCIF_MASK) == 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem rot error\r\n");
            return STATUS_TIMEOUT;
        }
    }

    while (drv_dma2d_rot_ant_status_get(pdma2d) != 0)
    {
        timeout++;
        if (timeout > MAX_TIMEOUT)
        {
            printf("mem2mem rot error\r\n");
            return STATUS_TIMEOUT;
        }
    }

    drv_dma2d_intr_status_clr(pdma2d, 0x3F);

    //invalidate dcache
    dcache_invalidate_range((void *)pmem2mem_rot->rotc_addr, 
        pmem2mem_rot->rota_w * pmem2mem_rot->rota_h * hal_get_byte_color_mode(pmem2mem_rot->rotc_color_mode));

    return STATUS_OK;
}
