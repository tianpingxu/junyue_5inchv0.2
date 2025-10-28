/**
 *  @file dma2d_drv.c
 *  @author Product application department
 *  @brief  DMA2D 模块驱动层
 *  @version v1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "dma2d_drv.h"
#include "cpm_drv.h"

// 全局变量定义
static dma_reg_t *pdma2d;

// 函数定义

/**
 *  @brief  DMA2D 功能模式清零
 *
 */
void drv_dma2d_mode_clear(void)
{
    _cpm_set_sys_module_reset_en(12);
    __NOP();
    __DSB();
    __ISB();
    _cpm_set_sys_module_reset_dis(12);
    __NOP();
    __DSB();
    __ISB();
}

/**
 *  @brief  DMA2D 工作模式设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param mode DMA2D 工作模式
 *  @return status_t DMA2D 函数运行状态
 */
status_t drv_dma2d_mode_set(dma_reg_t *pdma2d, dma2d_work_mode_t mode)
{
    if (mode > 3)
    {
        return STATUS_ERROR;
    }
    _dma2d_mode_set(pdma2d, mode);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 工作模式获取
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @return dma2d_work_mode_t DMA2D 工作模式
 */
dma2d_work_mode_t drv_dma2d_mode_get(dma_reg_t *pdma2d)
{
    return _dma2d_mode_get(pdma2d);
}

/**
 *  @brief  DMA2D 中止设置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param en DMA2D 中止使能或禁能
 *  @return status_t DMA2D 函数运行状态
 */
status_t drv_dma2d_abort_en(dma_reg_t *pdma2d, uint32_t en)
{
    if (en > 1)
    {
        return STATUS_ERROR;
    }
    _dma2d_abort_set(pdma2d, en);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 暂停设置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param en DMA2D 暂停使能或禁能
 *  @return status_t DMA2D 函数运行状态
 */
status_t drv_dma2d_susp_en(dma_reg_t *pdma2d, uint32_t en)
{
    if (en > 1)
    {
        return STATUS_ERROR;
    }
    _dma2d_susp_set(pdma2d, en);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 启动设置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param en DMA2D 启动使能或禁能
 *  @return status_t DMA2D 函数运行状态
 */
status_t drv_dma2d_start_en(dma_reg_t *pdma2d, uint32_t en)
{
    if (en > 1)
    {
        return STATUS_ERROR;
    }
    _dma2d_start_set(pdma2d, en);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 中断状态获取
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @return uint32_t 中断状态返回值
 */
uint32_t drv_dma2d_intr_status_get(dma_reg_t *pdma2d)
{
    return _dma2d_intr_status_get(pdma2d);
}

/**
 *  @brief  DMA2D 中断状态清除
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param status 中断状态清零设置值
 *  @return status_t DMA2D 函数运行状态
 */
status_t drv_dma2d_intr_status_clr(dma_reg_t *pdma2d, uint32_t status)
{
    if (status > 0x3F)
    {
        return STATUS_ERROR;
    }
    _dma2d_intr_status_clr(pdma2d, status);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) 的数据起始地址
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @param addr FG 的数据地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_addr_set(dma_reg_t *pdma2d, uint32_t addr)
{
    _dma2d_fg_rota_addr_set(pdma2d, addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的 A 层旋转的数据起始地址
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @param addr A 旋转的数据地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_rota_addr_set(dma_reg_t *pdma2d, uint32_t addr)
{
    _dma2d_fg_rota_addr_set(pdma2d, addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) 的行偏移量
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @param offset FG 行偏移量
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_line_offset_set(dma_reg_t *pdma2d, uint32_t offset)
{
    if (offset > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_fg_offset_set(pdma2d, offset);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) 的数据起始地址
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @param addr BG 的数据地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_addr_set(dma_reg_t *pdma2d, uint32_t addr)
{
    _dma2d_bg_rotb_addr_set(pdma2d, addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的 B 层旋转的数据起始地址
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @param addr B 旋转的数据地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_rotb_addr_set(dma_reg_t *pdma2d, uint32_t addr)
{
    _dma2d_bg_rotb_addr_set(pdma2d, addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) 的行偏移量
 *
 *  @param pdma2d  DMA2D 模块寄存器结构体
 *  @param offset BG 行偏移量
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_line_offset_set(dma_reg_t *pdma2d, uint32_t offset)
{
    if (offset > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_bg_offset_set(pdma2d, offset);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) alpha 通道配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param alpha alpha 通道数值
 *  @param alpha_mode alpha数值模式选择
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_pfc_alpha_set(dma_reg_t *pdma2d, uint32_t alpha_mode, uint32_t alpha)
{
    if ((alpha > 0xFF) || (alpha_mode > 0x3))
    {
        return STATUS_ERROR;
    }

    _dma2d_fg_rota_alpha_set(pdma2d, alpha);
    _dma2d_fg_rota_alpha_am_set(pdma2d, alpha_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) PFC 控制配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param color_mode 前景层颜色格式
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_color_mode_set(dma_reg_t *pdma2d, dma2d_color_mode_t color_mode)
{
    if (color_mode > 0x14)
    {
        return STATUS_ERROR;
    }
    _dma2d_fg_cm_set(pdma2d, color_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的 A 层PFC 控制配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param color_mode 前景层颜色格式
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_rota_color_mode_set(dma_reg_t *pdma2d, dma2d_color_mode_t color_mode)
{
    if (color_mode > 0x14)
    {
        return STATUS_ERROR;
    }
    _dma2d_fg_cm_set(pdma2d, color_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) PFC CLUT 控制配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param clut_size CLUT 查找表大小
 *  @param clut_color_mode CLUT 查找表颜色模式
 *  @param clut_start CLUT 查找表载入使能或禁能
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_pfc_clut_set(dma_reg_t *pdma2d, uint32_t clut_size, uint32_t clut_color_mode, uint32_t clut_start)
{
    if ((clut_size > 0xFF) || (clut_start > 1) || (clut_color_mode > 0x1))
    {
        return STATUS_ERROR;
    }

    _dma2d_fg_clut_size_set(pdma2d, clut_size);
    _dma2d_fg_clut_cm_set(pdma2d, clut_color_mode);
    _dma2d_fg_clut_load_set(pdma2d, clut_start);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) 颜色分量配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param r_val 颜色分量 R
 *  @param g_val 颜色分量 G
 *  @param b_val 颜色分量 B
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_color_set(dma_reg_t *pdma2d, uint8_t r_val, uint8_t g_val, uint8_t b_val)
{
    _dma2d_fg_r_val_set(pdma2d, r_val);
    _dma2d_fg_g_val_set(pdma2d, g_val);
    _dma2d_fg_b_val_set(pdma2d, b_val);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) alpha 通道配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param alpha alpha 通道数值
 *  @param alpha_mode alpha 数值模式选择
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_pfc_alpha_set(dma_reg_t *pdma2d, uint32_t alpha, uint32_t alpha_mode)
{
    if ((alpha > 0xFF) || (alpha_mode > 0x3))
    {
        return STATUS_ERROR;
    }

    _dma2d_bg_rotb_alpha_set(pdma2d, alpha);
    _dma2d_bg_rotb_alpha_am_set(pdma2d, alpha_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) 颜色格式设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param color_mode 前景层颜色格式
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_rotb_color_mode_set(dma_reg_t *pdma2d, uint32_t color_mode)
{
    if (color_mode > 0x14)
    {
        return STATUS_ERROR;
    }
    _dma2d_bg_cm_set(pdma2d, color_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的 B 层颜色格式设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param color_mode B 层颜色格式
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_color_mode_set(dma_reg_t *pdma2d, dma2d_color_mode_t color_mode)
{
    if (color_mode > 0x14)
    {
        return STATUS_ERROR;
    }
    _dma2d_bg_cm_set(pdma2d, color_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) PFC CLUT 控制配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param clut_size CLUT 查找表大小
 *  @param clut_color_mode CLUT 查找表颜色模式
 *  @param clut_start CLUT 查找表载入使能或禁能
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_pfc_clut_set(dma_reg_t *pdma2d, uint32_t clut_size, uint32_t clut_color_mode, uint32_t clut_start)
{
    if ((clut_size > 0xFF) || (clut_start > 1) || (clut_color_mode > 0x1))
    {
        return STATUS_ERROR;
    }

    _dma2d_bg_clut_size_set(pdma2d, clut_size);
    _dma2d_bg_clut_cm_set(pdma2d, clut_color_mode);
    _dma2d_bg_clut_load_set(pdma2d, clut_start);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) 颜色分量配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param r_val 颜色分量 R
 *  @param g_val 颜色分量 G
 *  @param b_val 颜色分量 B
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_color_set(dma_reg_t *pdma2d, uint8_t r_val, uint8_t g_val, uint8_t b_val)
{
    _dma2d_bg_r_val_set(pdma2d, r_val);
    _dma2d_bg_g_val_set(pdma2d, g_val);
    _dma2d_bg_b_val_set(pdma2d, b_val);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的前景层 (FG) 颜色查找表地址
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param clut_addr FG 颜色查找表地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_fg_clut_addr_set(dma_reg_t *pdma2d, uint32_t clut_addr)
{
    _dma2d_fg_clut_addr_set(pdma2d, clut_addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 的背景层 (BG) 颜色查找表地址
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param clut_addr BG 颜色查找表地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_bg_clut_addr_set(dma_reg_t *pdma2d, uint32_t clut_addr)
{
    _dma2d_bg_clut_addr_set(pdma2d, clut_addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D PFC 输出颜色模式
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param color_mode 输出颜色模式
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_output_color_mode_set(dma_reg_t *pdma2d, uint32_t color_mode)
{
    if (color_mode > 0xF)
    {
        return STATUS_ERROR;
    }

    _dma2d_out_rotc_cm_ctrl_set(pdma2d, color_mode);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D PFC 输出颜色模式
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param color_mode ROTC 输出颜色模式
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_rotc_color_mode_set(dma_reg_t *pdma2d, uint32_t color_mode)
{
    if (color_mode > 0xF)
    {
        return STATUS_ERROR;
    }

    _dma2d_out_rotc_cm_ctrl_set(pdma2d, color_mode);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 输出颜色设置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param out_color 输出颜色
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_output_color_set(dma_reg_t *pdma2d, uint32_t out_color)
{
    _dma2d_out_color_set(pdma2d, out_color);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 输出地址设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param out_addr 输出地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_output_color_addr_set(dma_reg_t *pdma2d, uint32_t out_addr)
{
    _dma2d_out_rotc_addr_set(pdma2d, out_addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D ROTC 输出地址设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param out_addr ROTC 输出地址
 *  @return status_t  函数运行状态
 */
status_t drv_dma2d_rotc_color_addr_set(dma_reg_t *pdma2d, uint32_t out_addr)
{
    _dma2d_out_rotc_addr_set(pdma2d, out_addr);
    return STATUS_OK;
}

/**
 *  @brief  DMA2D 输出层的行偏移量
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param offset 输出层行偏移量
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_out_line_offset_set(dma_reg_t *pdma2d, uint32_t offset)
{
    if (offset > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_out_offset_set(pdma2d, offset);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 前景层与背景层每行像素数与行数设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pixels 每行像素数
 *  @param lines 行数
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_pixels_and_lines_set(dma_reg_t *pdma2d, uint32_t pixels, uint32_t lines)
{
    if (pixels > 0x3FFF || lines > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_fbg_rota_pixel_lines_set(pdma2d, pixels);
    _dma2d_fbg_rota_number_lines_set(pdma2d, lines);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D ROTA 每行像素数与行数设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pixels 每行像素数
 *  @param lines 行数
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rota_pixels_and_lines_set(dma_reg_t *pdma2d, uint32_t pixels, uint32_t lines)
{
    if (pixels > 0x3FFF || lines > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_fbg_rota_pixel_lines_set(pdma2d, pixels);
    _dma2d_fbg_rota_number_lines_set(pdma2d, lines);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 行水印设置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param wline 行水印标记设置
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_line_watermark_set(dma_reg_t *pdma2d, uint32_t wline)
{
    if (wline > 0xFFFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_line_watermark_set(pdma2d, wline);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D AHB死区时间时钟周期设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param time_cycle 时钟周期设定值
 *  @param en 死区功能使能或禁能
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_ahb_dead_time_set(dma_reg_t *pdma2d, uint32_t time_cycle, uint32_t en)
{
    if (time_cycle > 0xFFFF || en > 1)
    {
        return STATUS_ERROR;
    }
    _dma2d_ahb_dead_time_val_set(pdma2d, time_cycle);
    _dma2d_ahb_dead_time_en_set(pdma2d, en);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 字节交换模式与交换使能配置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param swap_mode 字节交换模式
 *  @param en 交换功能使能或禁能
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_byte_swap_set(dma_reg_t *pdma2d, uint32_t swap_mode, uint32_t en)
{
    if (swap_mode > 3 || en > 1)
    {
        return STATUS_ERROR;
    }
    _dma2d_byte_swap_mode_set(pdma2d, swap_mode);
    _dma2d_byte_swap_en_set(pdma2d, en);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 像素位置转换模式设置
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param rot_ant_mode 像素位置转换模式
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rot_ant_config_set(dma_reg_t *pdma2d, dma2d_rot_ant_mode_t rot_ant_mode)
{
    if (rot_ant_mode > 0x7F)
    {
        return STATUS_ERROR;
    }
    _dma2d_rot_ant_config_set(pdma2d, rot_ant_mode);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 像素位置转换状态获取
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @return dma2d_rot_ant_mode_t 像素位置转换状态
 */
dma2d_rot_ant_mode_t drv_dma2d_rot_ant_status_get(dma_reg_t *pdma2d)
{
    return _dma2d_rot_ant_status_get(pdma2d);
}

/**
 *  @brief  DMA2D 旋转sin值设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param sinv sin值设定
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rot_sin_val_set(dma_reg_t *pdma2d, float sinv)
{
    if (sinv > 1.000001)
    {
        return STATUS_ERROR;
    }
    _dma2d_rot_sin_val_set(pdma2d, sinv);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D 旋转cos值设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param sinv cos值设定
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rot_cos_val_set(dma_reg_t *pdma2d, float cosv)
{
    if (cosv > 1.000001)
    {
        return STATUS_ERROR;
    }
    _dma2d_rot_cos_val_set(pdma2d, cosv);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D ROTA 旋转中心设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param center_w ROTA 宽度方向旋转中心设定值
 *  @param center_h ROTA 高度方向旋转中心设定值
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rota_center_config_set(dma_reg_t *pdma2d, uint32_t center_w, uint32_t center_h)
{
    if (center_w > 0x3FFF || center_h > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_rota_center_width_set(pdma2d, center_w);
    _dma2d_rota_center_height_set(pdma2d, center_h);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D ROTB 旋转中心设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param center_w ROTB 宽度方向旋转中心设定值
 *  @param center_h ROTB 高度方向旋转中心设定值
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rotb_center_config_set(dma_reg_t *pdma2d, uint32_t center_w, uint32_t center_h)
{
    if (center_w > 0x3FFF || center_h > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_rotb_center_width_set(pdma2d, center_w);
    _dma2d_rotb_center_height_set(pdma2d, center_h);

    return STATUS_OK;
}

/**
 *  @brief  DMA2D ROTB 每行像素数与行数设定
 *
 *  @param pdma2d DMA2D 模块寄存器结构体
 *  @param pixels 每行像素数
 *  @param lines 行数
 *  @return status_t 函数运行状态
 */
status_t drv_dma2d_rotb_pixels_and_lines_set(dma_reg_t *pdma2d, uint32_t pixels, uint32_t lines)
{
    if (pixels > 0x3FFF || lines > 0x3FFF)
    {
        return STATUS_ERROR;
    }
    _dma2d_rotb_pixel_lines_set(pdma2d, pixels);
    _dma2d_rotb_number_lines_set(pdma2d, lines);

    return STATUS_OK;
}
