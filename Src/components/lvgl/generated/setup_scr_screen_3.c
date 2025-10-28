/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"

//#include "lv_types.h"

//#include "custom.h"

extern lv_ui guider_ui;

static lv_timer_t * g_timer;

#include "rgb_lcd.h"
#include "ff.h"

extern uint8_t ADDR_L1_CPU[];
FIL bk_file;

extern uint8_t buf_jpg[1024 * 600];
extern uint8_t buf_raw[1024 * 600 * 4];

static void lv_timer_cb(lv_timer_t *timer)
{	
	printf("1");
	lv_image_set_src(guider_ui.screen_3_img_1, &_fan_speed_ARGB8888_228x228);
}

void setup_scr_screen_3(lv_ui *ui)
{
#if LV_CCORE_RENDER_MODE_USE_A

#if 0
	
    lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)jpeg_image, jpeg_image_len,(uint32_t)ADDR_L1_CPU);
	
#else	
	
	FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	FRESULT res;
	const char *fn1 = "1:/background.jpg";
	
	res = f_mount(&fs1, "1:", 1);
	printf("f_mount = %d.\r\n", res);
	res = f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	printf("f_open = %d.\r\n", res);
	res = f_stat(fn1, &info1);
	printf("f_stat = %d.\r\n", res);
	res = f_read(&bk_file, buf_jpg, info1.fsize, &br);
	printf("f_read = %d.\r\n", res);
	f_close(&bk_file);

	
	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)buf_jpg, br,(uint32_t)ADDR_L1_CPU);
#endif

#endif
	
    //Write codes screen_3
    ui->screen_3 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_3, 1024, 600);
    lv_obj_set_scrollbar_mode(ui->screen_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


#if LV_CCORE_RENDER_MODE_USE_A
    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
#endif

//////////////////////////////////////////////////////////////////////////////
    //Write codes screen_3_img_1
//////////////////////////////////////////////////////////////////////////////	
	
    //Write codes screen_3_img_1
    ui->screen_3_img_1 = lv_image_create(ui->screen_3);
    lv_obj_set_pos(ui->screen_3_img_1, 122, 111);
	
#if 1

	lv_obj_set_size(ui->screen_3_img_1, 228, 228);
    lv_obj_add_flag(ui->screen_3_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_3_img_1, &_fan_speed_ARGB8888_228x228);
	
#else

//	const char *fn2 = "1:/fan.png";
//	
//	res = f_mount(&fs1, "1:", 1);
//	printf("f_mount = %d.\r\n", res);
//	res = f_open(&bk_file,  fn2, FA_CREATE_ALWAYS | FA_READ);
//	printf("f_open = %d.\r\n", res);
//	res = f_stat(fn2, &info1);
//	printf("f_stat = %d.\r\n", res);
//	res = f_read(&bk_file, buf_jpg, info1.fsize, &br);
//	printf("f_read = %d.\r\n", res);
//	f_close(&bk_file);

//	printf("br=%d; %x,%x\r\n", br, buf_jpg[0], buf_jpg[1]);

//	lvgl_decode(IMAGE_PNG,JPEG_OUTPUT_ARGB888,(uint32_t)buf_jpg, br,(uint32_t)buf_raw);

	lv_obj_set_size(ui->screen_3_img_1, 260, 200); 
	lv_obj_add_flag(ui->screen_3_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_image_set_src(ui->screen_3_img_1, "1:/fan.png");
	
//	lv_image_set_src(ui->screen_3_img_1, &_fan_speed_41x41);
//	
#endif

    lv_image_set_pivot(ui->screen_3_img_1, 50,50);
    lv_image_set_rotation(ui->screen_3_img_1, 0);

    //Write style for screen_3_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_3_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_3_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

#if LV_CCORE_RENDER_MODE_USE_A
    lv_display_t *disp1 = lv_obj_get_display(ui->screen_3_img_1);
    lv_display_set_color_format(disp1, LV_COLOR_FORMAT_ARGB8888);
#endif

    //Write codes screen_3_slider_1
    ui->screen_3_slider_1 = lv_slider_create(ui->screen_3);
    lv_obj_set_pos(ui->screen_3_slider_1, 447, 380);
    lv_obj_set_size(ui->screen_3_slider_1, 436, 93);
    lv_slider_set_range(ui->screen_3_slider_1, 0, 100);
    lv_slider_set_mode(ui->screen_3_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_3_slider_1, 50, LV_ANIM_OFF);

    //Write style for screen_3_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_3_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_3_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_3_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_3_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_3_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_3_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_3_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_3_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_3_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_3_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_3_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_3_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_3_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_3_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

#if LV_CCORE_RENDER_MODE_USE_A
    lv_display_t *disp2 = lv_obj_get_display(ui->screen_3_slider_1);
    lv_display_set_color_format(disp2, LV_COLOR_FORMAT_ARGB8888);
#endif

    //Write codes screen_3_img_2
    ui->screen_3_img_2 = lv_image_create(ui->screen_3);
    lv_obj_set_pos(ui->screen_3_img_2, 601, 100);
    lv_obj_set_size(ui->screen_3_img_2, 260, 200);
    lv_obj_add_flag(ui->screen_3_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_pivot(ui->screen_3_img_2, 50,50);
    lv_image_set_rotation(ui->screen_3_img_2, 0);

#if 0

#else
	lv_image_set_src(ui->screen_3_img_2, "1:/light.png");//"1:/fan.png"
#endif

    //Write style for screen_3_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_3_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_3_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_3.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_3);
	
	g_timer = lv_timer_create(lv_timer_cb, 100,  (void *)ui);//定时周期50ms

}
