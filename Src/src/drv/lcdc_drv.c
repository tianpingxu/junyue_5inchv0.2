/**
 * @file lcdc_drv.c
 * @author Product application department
 * @brief  LCDC 模块驱动层
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "lcdc_drv.h"

// 全局变量定义
#define REG_IOCRTL_BASE            (0x40000000)
#define REG_IOCRTL_SWAP2          (0x0000006C)
#define REG_EPORT3_BASE            (0x40025000)

// 函数定义
/**
 *  @brief  LCDC 模块GPIO 配置函数
 *
 */
void drv_lcdc_gpio_config(void)
{
    uint32_t regval = 0;
    
    // 根据 ioctrl / eport 模块驱动配置修改
     _io_write32(REG_IOCRTL_BASE + REG_IOCRTL_SWAP2,0xC0C00000);
     _io_write32(REG_EPORT3_BASE, 0xC0000000);    
     _io_write32(REG_EPORT3_BASE + 0x4, 0x00004000);
     _io_write32(REG_EPORT3_BASE + 0x4, 0x0000C000);
}

/**
 *  @brief  LCDC 模块设置帧同步信号和行同步信号函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param hsync 帧同步信号宽度
 *  @param vsync 行同步信号宽度
 */
void drv_lcdc_sync_size_set(reg_lcdc_g_t *p_lcdc_g, uint32_t hsync, uint32_t vsync)
{
    _lcdc_g_sync_size_set(p_lcdc_g, hsync, vsync);
}

/**
 *  @brief  LCDC 模块设置前宽信号和上宽信号函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param hbp 前宽信号宽度
 *  @param vbp 上宽信号宽度
 *  @note 累积值，如 param hbp, 实际是 (hsync + hbp)
 */
void drv_lcdc_back_porch_set(reg_lcdc_g_t *p_lcdc_g, uint32_t hbp, uint32_t vbp)
{
    _lcdc_g_back_porch_set(p_lcdc_g, hbp, vbp);
}

/**
 *  @brief  LCDC 模块设置显示屏宽度信号和高度信号函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param width 显示屏宽度设置
 *  @param height 显示屏高度设置
 *  @note 累积值，如 param width, 实际是 (hsync + hbp + width)
 */
void drv_lcdc_active_width_set(reg_lcdc_g_t *p_lcdc_g, uint32_t width, uint32_t height)
{
    _lcdc_g_active_width_set(p_lcdc_g, width, height);
}

/**
 *  @brief  LCDC 模块设置显示后宽信号和下宽信号函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param hfp 后宽信号宽度
 *  @param vfp 下宽信号宽度
 *  @note 累积值，如 param hfp, 实际是 (hsync + hbp + width + hfp)
 */
void drv_lcdc_total_width_set(reg_lcdc_g_t *p_lcdc_g, uint32_t hfp, uint32_t vfp)
{
    _lcdc_g_total_width_set(p_lcdc_g, hfp, vfp);
}

/**
 *  @brief  LCDC 模块设置显示 CRC 功能使能或禁能函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param crc_en 设置 crc 功能使能或禁能
 */
void drv_lcdc_crc_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t crc_en)
{
    _lcdc_g_crc_en_set(p_lcdc_g, crc_en);
}

/**
 *  @brief  LCDC 模块设置显示 Dither 功能使能或禁能函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param dither_en 设置 dither 功能使能或禁能
 */
void drv_lcdc_dither_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_en)
{
    _lcdc_g_dither_en_set(p_lcdc_g, dither_en);
}

/**
 *  @brief  LCDC 模块设置显示 Dither 功能红色分量设置函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param dither_red dither 功能红色分量设置
 */
void drv_lcdc_dither_red_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_red)
{
    _lcdc_g_dither_red_set(p_lcdc_g, dither_red);
}

/**
 *  @brief  LCDC 模块设置显示 Dither 功能绿色分量设置函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param dither_green dither 功能绿色分量设置
 */
void drv_lcdc_dither_green_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_green)
{
    _lcdc_g_dither_green_set(p_lcdc_g, dither_green);
}

/**
 *  @brief  LCDC 模块设置显示 Dither 功能蓝色分量设置函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param dither_blue dither 功能蓝色分量设置
 */
void drv_lcdc_dither_blue_set(reg_lcdc_g_t *p_lcdc_g, uint32_t dither_blue)
{
    _lcdc_g_dither_blue_set(p_lcdc_g, dither_blue);
}

/**
 *  @brief  LCDC 模块设置显示 gamma 功能使能或禁能函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param gamma gamma 功能使能或禁能
 */
void drv_lcdc_gamma_correction_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t gamma)
{
    _lcdc_g_gamma_correction_en_set(p_lcdc_g, gamma);
}

/**
 *  @brief  LCDC 模块设置显示 global 功能使能或禁能函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param global_en global 功能使能或禁能
 */
void drv_lcdc_global_en_set(reg_lcdc_g_t *p_lcdc_g, uint32_t global_en)
{
    _lcdc_g_global_en_set(p_lcdc_g, global_en);
}

/**
 *  @brief  LCDC 模块设置 global control 寄存器功能函数
 *
 *  @param p_lcdc_g LCDC 全局寄存器结构体指针
 *  @param value 寄存器数值
 */
void drv_lcdc_global_control_set(reg_lcdc_g_t *p_lcdc_g, uint32_t value)
{
    _lcdc_g_global_control_set(p_lcdc_g, value);
}

/**
 *  @brief  LCDC 模块设置 immediate reload 功能使能或禁能函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @param reload reload 使能或禁能
 */
void drv_lcdc_immediate_reload_set(reg_lcdc_g_t *p_lcdc_g, uint32_t reload)
{
    _lcdc_g_immediate_reload_set(p_lcdc_g, reload);
}

/**
 *  @brief  LCDC 模块设置 shadow reload control 寄存器功能函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @param value 寄存器数值
 */
void drv_lcdc_shadow_reload_ctrl_set(reg_lcdc_g_t *p_lcdc_g, uint32_t value)
{
    _lcdc_g_shadow_reload_ctrl_set(p_lcdc_g, value);
}

/**
 *  @brief  LCDC 模块设置背景层颜色函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @param background 背景层颜色
 */
void drv_lcdc_background_color_set(reg_lcdc_g_t *p_lcdc_g, uint32_t background)
{
    _lcdc_g_background_color_set(p_lcdc_g, background);
}

/**
 *  @brief  LCDC 模块设置中断功能函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @param irq_en 中断功能使能
 */
void drv_lcdc_irq_en_set(reg_lcdc_g_t *p_lcdc_g, lcdc_irq_t irq_en)
{
    _lcdc_g_irq_en_set(p_lcdc_g, irq_en);
}

/**
 *  @brief  LCDC 模块获取中断状态寄存器函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @return drv_lcdc_irq_en_set 返回中断状态
 */
lcdc_irq_t drv_lcdc_irq_status_get(reg_lcdc_g_t *p_lcdc_g)
{
    return _lcdc_g_irq_status_get(p_lcdc_g);
}

/**
 *  @brief  LCDC 模块清除中断状态寄存器函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @return 
 */
void drv_lcdc_irq_status_clear(reg_lcdc_g_t *p_lcdc_g,uint32_t value)
{
    _lcdc_g_irq_status_clear(p_lcdc_g,value);
}

/**
 *  @brief  LCDC 模块清空中断状态函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @param irq_clr 清理中断状态
 */
void drv_lcdc_irq_clr_set(reg_lcdc_g_t *p_lcdc_g, lcdc_irq_t irq_clr)
{
    _lcdc_g_irq_clr_set(p_lcdc_g, irq_clr);
}

/**
 *  @brief  LCDC 模块行号请求中断位置设置函数
 *
 *  @param p_lcdc_g 全局寄存器结构体指针
 *  @param line_pos 行号请求中断位置
 *  @note line_pos 参数是行中断请求位置, 实际是 (vsync + vbp + line_pos)
 */
void drv_lcdc_line_irq_position_ctrl_set(reg_lcdc_g_t *p_lcdc_g, uint32_t line_pos)
{
    _lcdc_g_line_irq_position_ctrl_set(p_lcdc_g, line_pos);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层混叠功能使能或禁能函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param blend_en 混叠功能使能或禁能
 */
void drv_lcdc_color_blend_en_set(reg_lcdc_l_t *p_lcdc_l, uint32_t blend_en)
{
    _lcdc_l_color_blend_en_set(p_lcdc_l, blend_en);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层水平功能使能或禁能函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param mirror_en 水平功能使能或禁能
 */
void drv_lcdc_hor_mirror_en_set(reg_lcdc_l_t *p_lcdc_l, uint32_t mirror_en)
{
    _lcdc_l_hor_mirror_en_set(p_lcdc_l, mirror_en);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层显示功能开启或关闭函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param layer_on 显示功能开启或关闭
 */
void drv_lcdc_layer_on_set(reg_lcdc_l_t *p_lcdc_l, uint32_t layer_on)
{
    _lcdc_l_layer_on_set(p_lcdc_l, layer_on);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层控制寄存器设置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param value 寄存器数值
 */
void drv_lcdc_layer_ctrl_set(reg_lcdc_l_t *p_lcdc_l, uint32_t value)
{
    _lcdc_l_layer_ctrl_set(p_lcdc_l, value);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层水平方向窗口结束位置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param hor_stop 水平方向窗口结束位置
 */
void drv_lcdc_hor_stop_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t hor_stop)
{
    _lcdc_l_hor_stop_pos_set(p_lcdc_l, hor_stop);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层水平方向窗口开始位置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param hor_start 水平方向窗口开始位置
 */
void drv_lcdc_hor_start_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t hor_start)
{
    _lcdc_l_hor_start_pos_set(p_lcdc_l, hor_start);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层水平方向窗口开窗位置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param hor_stop 水平方向窗口结束位置
 *  @param hor_start 水平方向窗口开始位置
 */
void drv_lcdc_window_hor_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t hor_stop, uint32_t hor_start)
{
    _lcdc_l_window_hor_pos_set(p_lcdc_l, hor_stop, hor_start);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层垂直方向窗口结束位置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param ver_stop 垂直方向窗口结束位置
 */
void drv_lcdc_ver_stop_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t ver_stop)
{
    _lcdc_l_ver_stop_pos_set(p_lcdc_l, ver_stop);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层垂直方向窗口开始位置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param ver_start 垂直方向窗口开始位置
 */
void drv_lcdc_ver_start_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t ver_start)
{
    _lcdc_l_ver_start_pos_set(p_lcdc_l, ver_start);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层垂直方向窗口开窗位置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param ver_stop 垂直方向窗口结束位置
 *  @param ver_start 垂直方向窗口开始位置
 */
void drv_lcdc_window_ver_pos_set(reg_lcdc_l_t *p_lcdc_l, uint32_t ver_stop, uint32_t ver_start)
{
    _lcdc_l_window_ver_pos_set(p_lcdc_l, ver_stop, ver_start);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层像素格式设置函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param pixel_format 像素格式
 */
void drv_lcdc_pixel_format_set(reg_lcdc_l_t *p_lcdc_l, lcdc_pixel_format_t pixel_format)
{
    _lcdc_l_pixel_format_set(p_lcdc_l, pixel_format);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层 alpha 通道数值设定函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param const_alpha alpha 通道数值
 */
void drv_lcdc_const_alpha_set(reg_lcdc_l_t *p_lcdc_l, uint32_t const_alpha)
{
    _lcdc_l_const_alpha_set(p_lcdc_l, const_alpha);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层默认颜色值函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param def_color 默认颜色值
 */
void drv_lcdc_default_color_set(reg_lcdc_l_t *p_lcdc_l, uint32_t def_color)
{
    _lcdc_l_default_color_set(p_lcdc_l, def_color);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层混叠参数 F1 选择函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param f1_en factor f1 选择: 0 - const_alpha, 1 - const_alpha * pixel_alpha
 */
void drv_lcdc_l_factor_f1_select(reg_lcdc_l_t *p_lcdc_l, uint32_t f1_en)
{
    if (f1_en)
    {
        _lcdc_l_factor_f1_set(p_lcdc_l, 0x6);
    }
    else
    {
        _lcdc_l_factor_f1_set(p_lcdc_l, 0x4);
    }
}

/**
 *  @brief  LCDC 模块L1 或 L2 层混叠参数 F2 选择函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param f2_en factor f2 选择: 0 - const_alpha, 1 - const_alpha * pixel_alpha
 */
void drv_lcdc_l_factor_f2_select(reg_lcdc_l_t *p_lcdc_l, uint32_t f2_en)
{
    if (f2_en)
    {
        _lcdc_l_factor_f2_set(p_lcdc_l, 0x7);
    }
    else
    {
        _lcdc_l_factor_f2_set(p_lcdc_l, 0x5);
    }
}

/**
 *  @brief  LCDC 模块L1 或 L2 层混叠参数层数选择函数
 *
 *  @param p_lcdc_l  L1 或 L2 层存器结构体指针
 *  @param layer_n L1 或 L2 层
 */
void drv_lcdc_l_factor_layer_select(reg_lcdc_l_t *p_lcdc_l, uint8_t layer_n)
{
    uint32_t regval = 0;

    if (layer_n == 1 || layer_n == 2)
    {
        regval = _lcdc_l_blend_config_get(p_lcdc_l);
        regval |= (layer_n - 1) << 16;
        _lcdc_l_blend_config_set(p_lcdc_l, regval);
    }
    else
    {
        //
    }
}

/**
 *  @brief  LCDC 模块L1 或 L2 层每次 Burst 读取的字数函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param fb_bus 每次 Burst 读取的字数
 */
void drv_lcdc_fb_bus_ctrl_set(reg_lcdc_l_t *p_lcdc_l, lcdc_fb_bus_t fb_bus)
{
    _lcdc_l_fb_bus_ctrl_set(p_lcdc_l, fb_bus);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层图像数据帧缓存首地址函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param fb_addr
 *  @note 首地址四字节对齐
 */
void drv_lcdc_color_fb_addr_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_addr)
{
    _lcdc_l_color_fb_addr_set(p_lcdc_l, fb_addr);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层行间距设定函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param fb_pitch 行间距设定
 *  @note 一个像素行的开始到下一个像素行的开始之间的字节增量
 */
void drv_lcdc_color_fb_pitch_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_pitch)
{
    _lcdc_l_color_fb_pitch_set(p_lcdc_l, fb_pitch);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层行长度设定函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param fb_length 行长度
 *  @note 行长度设定值：行间距 + 总线宽度 - 1, 总线宽度为 8 字节
 */
void drv_lcdc_color_fb_length_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_length)
{
    _lcdc_l_color_fb_length_set(p_lcdc_l, fb_length);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层行间距与行长度设定函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param fb_pitch 行间距
 */
void drv_lcdc_color_fb_pitch_length_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_pitch)
{
    _lcdc_l_color_fb_pitch_length_set(p_lcdc_l, fb_pitch);
}

/**
 *  @brief  LCDC 模块L1 或 L2 层行数设定函数
 *
 *  @param p_lcdc_l L1 或 L2 层存器结构体指针
 *  @param fb_lines 行数
 */
void drv_lcdc_color_fb_lines_set(reg_lcdc_l_t *p_lcdc_l, uint32_t fb_lines)
{
    _lcdc_l_color_fb_lines_set(p_lcdc_l, fb_lines);
}
