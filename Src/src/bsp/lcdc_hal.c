/**
 * @file lcdc_hal.c
 * @author Product application department
 * @brief  LCDC 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "lcdc_hal.h"
#include "cpm_drv.h"
#include "pinswap_drv.h"
// 全局变量定义
static rgb_input_timing_para_t *p_rgb_para;

// 函数定义
/**
 *  @brief  LCDC 模块初始化函数
 *
 *  @param p_rgb_para rgb 显示屏时序参数结构体
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_init(rgb_input_timing_para_t *p_rgb_para)
{
    uint8_t clcd_div;
    uint32_t clk_freq;
    // global register 配置
    // 配置clcd分频
    if (drv_cpm_gettrimclk() == DRV_SYS_OSC_CLK_320M)
    {
        clk_freq = DRV_SYS_OSC_CLK_320M;
    }
    else if (drv_cpm_gettrimclk() == DRV_SYS_OSC_CLK_400M)
    {
        clk_freq = DRV_SYS_OSC_CLK_400M;
    }
    else if (drv_cpm_gettrimclk() == DRV_SYS_OSC_CLK_480M)
    {
        clk_freq = DRV_SYS_OSC_CLK_480M;
    }
    else if (drv_cpm_gettrimclk() == DRV_SYS_OSC_CLK_500M)
    {
        clk_freq = DRV_SYS_OSC_CLK_500M;
    }
    clcd_div = clk_freq / p_rgb_para->clcdclk;
    SwitchPinFunction(CLKOUT_FUN, CLCD_DATA18_FUN);
    drv_cpm_setclcddiv(clcd_div - 1);
    drv_lcdc_sync_size_set(LCDC_G, p_rgb_para->hsync, p_rgb_para->vsync);
    drv_lcdc_back_porch_set(LCDC_G, p_rgb_para->hsync + p_rgb_para->hbp, p_rgb_para->vsync + p_rgb_para->vbp);
    drv_lcdc_active_width_set(LCDC_G, p_rgb_para->hsync + p_rgb_para->hbp + p_rgb_para->width, p_rgb_para->vsync + p_rgb_para->vbp + p_rgb_para->height);
    drv_lcdc_total_width_set(LCDC_G, p_rgb_para->hsync + p_rgb_para->hbp + p_rgb_para->width + p_rgb_para->hfp, p_rgb_para->vsync + p_rgb_para->vbp + p_rgb_para->height + p_rgb_para->vfp);
    drv_lcdc_line_irq_position_ctrl_set(LCDC_G, p_rgb_para->vsync + p_rgb_para->vbp + p_rgb_para->height);
    drv_lcdc_irq_en_set(LCDC_G, LINE_IRQ);
    drv_lcdc_irq_clr_set(LCDC_G, LINE_IRQ);
    drv_lcdc_global_en_set(LCDC_G, LCDC_EN);
    drv_lcdc_background_color_set(LCDC_G, p_rgb_para->background_color);

    // l1 寄存器配置
    drv_lcdc_window_hor_pos_set(LCDC_L1, p_rgb_para->hsync + p_rgb_para->hbp + p_rgb_para->width, p_rgb_para->hsync + p_rgb_para->hbp);
    drv_lcdc_window_ver_pos_set(LCDC_L1, p_rgb_para->vsync + p_rgb_para->vbp + p_rgb_para->height, p_rgb_para->vsync + p_rgb_para->vbp);
    drv_lcdc_color_fb_lines_set(LCDC_L1, p_rgb_para->height);
    drv_lcdc_default_color_set(LCDC_L1, p_rgb_para->l1_default_color);
    drv_lcdc_fb_bus_ctrl_set(LCDC_L1, p_rgb_para->fb_bus1);

    // l2 寄存器配置
    drv_lcdc_window_hor_pos_set(LCDC_L2, p_rgb_para->hsync + p_rgb_para->hbp + p_rgb_para->width, p_rgb_para->hsync + p_rgb_para->hbp);
    drv_lcdc_window_ver_pos_set(LCDC_L2, p_rgb_para->vsync + p_rgb_para->vbp + p_rgb_para->height, p_rgb_para->vsync + p_rgb_para->vbp);
    drv_lcdc_color_fb_lines_set(LCDC_L2, p_rgb_para->height);
    drv_lcdc_default_color_set(LCDC_L2, p_rgb_para->l2_default_color);
    drv_lcdc_fb_bus_ctrl_set(LCDC_L2, p_rgb_para->fb_bus2);

    // l1 & l2 寄存器配置立即生效
    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x1);
    drv_lcdc_irq_en_set(LCDC_G, LCDC_G_REG_RELOAD_IRQ_STATUS_MASK);
    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 与 L2 层显示切换控制函数
 *
 *  @param ctrl L1 与 L2 层切换控制
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_layer_switch(rgb_layer_switch_t ctrl)
{
    if (ctrl > LAYER_ALL_ON)
    {
        return STATUS_ERROR;
    }

    switch (ctrl)
    {
    case LAYER_OFF:
        drv_lcdc_layer_on_set(LCDC_L1, LCDC_DIS);
        drv_lcdc_layer_on_set(LCDC_L2, LCDC_DIS);
        break;
    case LAYER1_ON:
        drv_lcdc_layer_on_set(LCDC_L1, LCDC_EN);
        drv_lcdc_layer_on_set(LCDC_L2, LCDC_DIS);
        break;
    case LAYER2_ON:
        drv_lcdc_layer_on_set(LCDC_L1, LCDC_DIS);
        drv_lcdc_layer_on_set(LCDC_L2, LCDC_EN);
        break;
    case LAYER_ALL_ON:
        drv_lcdc_layer_on_set(LCDC_L1, LCDC_EN);
        drv_lcdc_layer_on_set(LCDC_L2, LCDC_EN);
        break;
    }

    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 或 L2 层显示控制函数
 *
 *  @param layern L1 或 L2 层
 *  @param en en 显示控制: 1 - 开启, 0 - 关闭
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_layer_on(uint8_t layern, uint8_t en)
{
    if (layern == 1)
    {
        drv_lcdc_layer_on_set(LCDC_L1, en);
    }
    else if (layern == 2)
    {
        drv_lcdc_layer_on_set(LCDC_L2, en);
    }
    else
    {
        return STATUS_ERROR;
    }
    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 与 L2 层每次 Burst 读取的字数函数
 *
 *  @param fb_bus1 L1 层每次 Burst 读取的字数
 *  @param fb_bus2 L2 层每次 Burst 读取的字数
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_layer_burst_config(lcdc_fb_bus_t fb_bus1, lcdc_fb_bus_t fb_bus2)
{
    if (fb_bus1 > 0xF || fb_bus2 > 0xF)
    {
        return STATUS_ERROR;
    }

    drv_lcdc_fb_bus_ctrl_set(LCDC_L1, fb_bus1);
    drv_lcdc_fb_bus_ctrl_set(LCDC_L2, fb_bus2);
    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 与 L2 层图像格式与图像地址设定函数
 *
 *  @param l1_format L1 层图像格式
 *  @param l2_format L2 层图像格式
 *  @param l1_addr L1 图像地址
 *  @param l2_addr L2 图像地址
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_format_and_addr_config(rgb_input_timing_para_t *p_rgb_para, lcdc_pixel_format_t l1_format, lcdc_pixel_format_t l2_format, uint32_t l1_addr, uint32_t l2_addr)
{
    uint32_t pitch = 0;
    uint32_t width = 0;

    width = p_rgb_para->width;

    if (width <= 0)
    {
        return STATUS_ERROR;
    }
    // pixel format for layer1
    drv_lcdc_pixel_format_set(LCDC_L1, l1_format);
    if (l1_format >= LCDC_ARGB8888 && l1_format <= LCDC_BGRA8888)
    {
        pitch = (width * 4);
    }
    else if (l1_format == LCDC_RGB565 || l1_format == LCDC_BGR565)
    {
        pitch = (width * 2);
    }
    else if (l1_format == LCDC_RGB888)
    {
        pitch = (width * 3);
    }
    else
    {
        return STATUS_ERROR;
    }
    drv_lcdc_color_fb_pitch_length_set(LCDC_L1, pitch);
    drv_lcdc_color_fb_addr_set(LCDC_L1, l1_addr); // l1 层图像首地址

    // pixel format for layer2
    drv_lcdc_pixel_format_set(LCDC_L2, l2_format);
    if (l2_format >= LCDC_ARGB8888 && l2_format <= LCDC_BGRA8888)
    {
        pitch = (width * 4);
    }
    else if (l2_format == LCDC_RGB565 || l2_format == LCDC_BGR565)
    {
        pitch = (width * 2);
    }
    else if (l2_format == LCDC_RGB888)
    {
        pitch = (width * 3);
    }
    else
    {
        return STATUS_ERROR;
    }
    drv_lcdc_color_fb_pitch_length_set(LCDC_L2, pitch);
    drv_lcdc_color_fb_addr_set(LCDC_L2, l2_addr); // l2 层图像首地址

    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 或 L2 层图像格式设定
 *
 *  @param layern L1 或 L2 层
 *  @param l_format 图像格式
 *  @return status_t 函数运行状态返回值
 */
status_t hal_layer_format_config(rgb_input_timing_para_t *p_rgb_para, uint8_t layern, lcdc_pixel_format_t l_format)
{
    uint32_t pitch = 0;
    uint32_t width = 0;

    width = p_rgb_para->width;

    if (width <= 0)
    {
        return STATUS_ERROR;
    }
    // pixel format for layer

    if (l_format >= LCDC_ARGB8888 && l_format <= LCDC_BGRA8888)
    {
        pitch = (width * 4 << 16) | (width * 4 + 7);
    }
    else if (l_format == LCDC_RGB565 || l_format == LCDC_BGR565)
    {
        pitch = (width * 2 << 16) | (width * 2 + 7);
    }
    else if (l_format == LCDC_RGB888)
    {
        pitch = (width * 3 << 16) | (width * 3 + 7);
    }
    else
    {
        return STATUS_ERROR;
    }

    if (layern == 1)
    {
        drv_lcdc_pixel_format_set(LCDC_L1, l_format);
        drv_lcdc_color_fb_pitch_length_set(LCDC_L1, pitch);
    }
    else if (layern == 2)
    {
        drv_lcdc_pixel_format_set(LCDC_L2, l_format);
        drv_lcdc_color_fb_pitch_length_set(LCDC_L2, pitch);
    }
    else
    {
        return STATUS_ERROR;
    }
    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 或 L2 层图像地址设定函数
 *
 *  @param layern L1 或 L2 层
 *  @param l_addr 图像地址
 *  @return status_t 函数运行状态返回值
 */
status_t hal_layer_addr_config(rgb_input_timing_para_t *p_rgb_para, uint8_t layern, uint32_t l_addr)
{
    uint32_t pitch = 0;
    uint32_t width = 0;

    width = p_rgb_para->width;

    if (width <= 0)
    {
        return STATUS_ERROR;
    }
    if (layern == 1)
    {
        drv_lcdc_color_fb_addr_set(LCDC_L1, l_addr); // l1 层图像首地址
    }
    else if (layern == 2)
    {
        drv_lcdc_color_fb_addr_set(LCDC_L2, l_addr); // l2 层图像首地址
    }
    else
    {
        return STATUS_ERROR;
    }
    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 与 L2 层图像水平镜像设定函数
 *
 *  @param l1_format L1 层图像格式
 *  @param l2_format L2 层图像格式
 *  @param l1_mirror L1 层图像水平镜像使能或禁能
 *  @param l2_mirror L2 层图像水平镜像使能或禁能
 *  @param l1_addr L1 图像地址
 *  @param l2_addr L2 图像地址
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_mirror_config(rgb_input_timing_para_t *p_rgb_para, lcdc_pixel_format_t l1_format, lcdc_pixel_format_t l2_format, uint8_t l1_mirror, uint8_t l2_mirror, uint32_t l1_addr, uint32_t l2_addr)
{
    uint32_t length = 0;
    uint32_t bytecount = 0;
    uint32_t width = 0;

    width = p_rgb_para->width;

    if (l1_mirror > 1 || l2_mirror > 1 || width <= 0)
    {
        return STATUS_ERROR;
    }

    if (l1_format >= LCDC_ARGB8888 && l1_format <= LCDC_BGRA8888)
    {
        bytecount = 4;
    }
    else if (l1_format == LCDC_RGB565 || l1_format == LCDC_BGR565)
    {
        bytecount = 2;
    }
    else if (l1_format == LCDC_RGB888)
    {
        bytecount = 3;
    }
    else
    {
        return STATUS_ERROR;
    }

    if (l1_mirror == 1)
    {
        length = bytecount * width - 1;
        drv_lcdc_color_fb_addr_set(LCDC_L1, l1_addr + length); // l1 层 mirror 图像首地址
    }
    else if (l1_mirror == 0)
    {
        drv_lcdc_color_fb_addr_set(LCDC_L1, l1_addr); // l1 层图像首地址
    }
    drv_lcdc_hor_mirror_en_set(LCDC_L1, l1_mirror);

    if (l2_format >= LCDC_ARGB8888 && l2_format <= LCDC_BGRA8888)
    {
        bytecount = 4;
    }
    else if (l2_format == LCDC_RGB565 || l2_format == LCDC_BGR565)
    {
        bytecount = 2;
    }
    else if (l2_format == LCDC_RGB888)
    {
        bytecount = 3;
    }
    else
    {
        return STATUS_ERROR;
    }

    if (l2_mirror == 1)
    {
        length = bytecount * width - 1;
        drv_lcdc_color_fb_addr_set(LCDC_L2, l2_addr + length); // l2 层 mirror 图像首地址
    }
    else if (l2_mirror == 0)
    {
        drv_lcdc_color_fb_addr_set(LCDC_L2, l2_addr); // l2 层图像首地址
    }
    drv_lcdc_hor_mirror_en_set(LCDC_L2, l2_mirror);

    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}

/**
 *  @brief  LCDC 模块L1 与 L2 层混叠设定函数
 *
 *  @param l1_alpha l1 层固定 alpha 数值
 *  @param l2_alpha l2 层固定 alpha 数值
 *  @param l1_f1 l1 层参数混叠 F1 选择
 *  @param l1_f2 l1 层参数混叠 F2 选择
 *  @param l2_f1 l2 层参数混叠 F1 选择
 *  @param l2_f2 l2 层参数混叠 F2 选择
 *  @return status_t 函数运行状态返回值
 */
status_t hal_lcdc_layer_blend_config(uint32_t l1_alpha, uint32_t l2_alpha, uint8_t l1_f1, uint8_t l1_f2, uint8_t l2_f1, uint8_t l2_f2)
{
    uint32_t regval = 0;

    if (l1_f1 > 1 || l1_f2 > 1 || l2_f1 > 1 || l2_f2 > 1)
    {
        return STATUS_ERROR;
    }

    if (l1_alpha > 0xFF || l2_alpha > 0xFF)
    {
        return STATUS_ERROR;
    }

    // layer1 blending config
    drv_lcdc_const_alpha_set(LCDC_L1, l1_alpha);
    drv_lcdc_l_factor_layer_select(LCDC_L1, 1);
    drv_lcdc_l_factor_f1_select(LCDC_L1, l1_f1);
    drv_lcdc_l_factor_f2_select(LCDC_L1, l1_f2);

    // layer2 blending config
    drv_lcdc_const_alpha_set(LCDC_L2, l2_alpha);
    drv_lcdc_l_factor_layer_select(LCDC_L2, 2);
    drv_lcdc_l_factor_f1_select(LCDC_L2, l2_f1);
    drv_lcdc_l_factor_f2_select(LCDC_L2, l2_f2);

    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    return STATUS_OK;
}
/**
 * @brief LCDC 模块切换图层显示地址
 *
 * @param layern 图层
 * @param addr 图像地址
 * @return status_t 成功/失败
 */
status_t hal_lcdc_switch_address(uint8_t layern, uint32_t addr)
{
    if (layern == 1)
    {
        drv_lcdc_color_fb_addr_set(LCDC_L1, addr);
    }
    else if (layern == 2)
    {
        drv_lcdc_color_fb_addr_set(LCDC_L2, addr);
    }
    else
    {
        return STATUS_ERROR;
    }

    drv_lcdc_irq_status_clear(LCDC_G, LCDC_G_REG_RLIRQ_CLEAR_MASK);

    drv_lcdc_shadow_reload_ctrl_set(LCDC_G, 0x2);

    while (!(drv_lcdc_irq_status_get(LCDC_G) & LCDC_G_REG_IRQ_STAT))
    {
    };
    drv_lcdc_irq_status_clear(LCDC_G, LCDC_G_REG_RLIRQ_CLEAR_MASK);

    __DSB();
    __ISB();
    return STATUS_OK;
}
