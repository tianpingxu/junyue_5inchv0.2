/**
 * @file lv_ccore_conf.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-08-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
    
#ifndef LV_CCORE_CONF_H
#define LV_CCORE_CONF_H

#ifdef __cplusplus
extern "C" {
#endif
/////////////////////////////////////////////////////////////////////////////////////////////
#define LV_CCORE_WIDTH      480
#define LV_CCORE_HEIGHT     854

/////////////////////////////////////////////////////////////////////////////////////////////
/*选择是否使用A通道
*1. 如果不使用A通道画布（LV_CCORE_RENDER_MODE_NO_A），则正常使用即可;
*2. 如果使用A通道画布（LV_CCORE_RENDER_MODE_USE_A）:
1) LVGL色深必须使用ARGB8888模式；
2）绘制画布需要新加画布和控件透明接口：
    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    lv_display_t *disp = lv_obj_get_display(控件名);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
3）LCDC必须使用Blend模式，背景层图片资源需要自行控制切换；
*/
#define LV_CCORE_RENDER_MODE_NO_A      0
#define LV_CCORE_RENDER_MODE_USE_A     1


/////////////////////////////////////////////////////////////////////////////////////////////
/*选择无A模式，正常使用LVGL即可，LCDC不需要额外配置Blend */
#if LV_CCORE_RENDER_MODE_NO_A
/*
*配置刷图方式为局部或全图
*/
#define LV_CCORE_RENDER_MODE_PARTIAL        0
#define LV_CCORE_RENDER_MODE_FULL           1
/*
*选择颜色格式
*/
#define DISPLAY_RGB565                      0
#define DISPLAY_RGB888                      1
#define DISPLAY_ARGB8888                    0

#endif


/////////////////////////////////////////////////////////////////////////////////////////////
/*选择A模式，需要配置LCDC blend，并做背景资源控制*/
#if LV_CCORE_RENDER_MODE_USE_A

/*
*配置刷图方式为局部或全图
*/
#define LV_CCORE_RENDER_MODE_PARTIAL        0
#define LV_CCORE_RENDER_MODE_FULL           1
/*
*选择颜色格式 必须为ARGB8888
*/
#define DISPLAY_ARGB8888                    1
#endif

#ifdef __cplusplus
}
#endif

#endif /* LV_CCORE_CONF_H */