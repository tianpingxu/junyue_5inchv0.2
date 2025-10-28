#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

#include "ff.h"
#include "rgb_lcd.h"

FIL bk_file;
extern uint8_t ADDR_L1_CPU[];
__attribute__((section("NO_INIT")))  __ALIGNED(8) uint8_t bk_decode_buffer[1024*500]={0};

void create_screen_page_home() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_home = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_event_cb(obj, action_gesture_handle_cb, LV_EVENT_GESTURE, (void *)1);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            // imgbtn_wifi_state
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_wifi_state = obj;
            lv_obj_set_pos(obj, 220, 124);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 40);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/wifi_off.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "1:/wifi_on.png", NULL);
        }
        {
            // container_home_time
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_home_time = obj;
            lv_obj_set_pos(obj, 60, 170);
            lv_obj_set_size(obj, 360, 180);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_home_time
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_time = obj;
                    lv_obj_set_pos(obj, 17, 19);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_128, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "13 59");
                }
                {
                    // label_t_blink
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_t_blink = obj;
                    lv_obj_set_pos(obj, 164, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_128, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ":");
                }
            }
        }
        {
            // container_home_timer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_home_timer = obj;
            lv_obj_set_pos(obj, 0, 170);
            lv_obj_set_size(obj, 480, 180);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_home_timer
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_timer = obj;
                    lv_obj_set_pos(obj, 49, 54);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_96, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00 00 30");
                }
                {
                    // label_home_timer_k
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_timer_k = obj;
                    lv_obj_set_pos(obj, 158, 47);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_96, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ":    :");
                }
            }
        }
        {
            // img_meeting
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_meeting = obj;
            lv_obj_set_pos(obj, 28, 514);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/meeting_off.png");
            lv_obj_add_event_cb(obj, action_mode_select_cb, LV_EVENT_CLICKED, (void *)1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_home_meeting
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_meeting = obj;
                    lv_obj_set_pos(obj, 13, 78);
                    lv_obj_set_size(obj, 180, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "meeting");
                }
            }
        }
        {
            // img_relax
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_relax = obj;
            lv_obj_set_pos(obj, 248, 514);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/relax_off.png");
            lv_obj_add_event_cb(obj, action_mode_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_home_relax
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_relax = obj;
                    lv_obj_set_pos(obj, 13, 78);
                    lv_obj_set_size(obj, 180, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_opa(obj, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "relax");
                }
            }
        }
        {
            // img_work
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_work = obj;
            lv_obj_set_pos(obj, 28, 656);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/work_off.png");
            lv_obj_add_event_cb(obj, action_mode_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_home_work
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_work = obj;
                    lv_obj_set_pos(obj, 13, 78);
                    lv_obj_set_size(obj, 180, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "work");
                }
            }
        }
        {
            // img_phone
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_phone = obj;
            lv_obj_set_pos(obj, 248, 656);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/phone_off.png");
            lv_obj_add_event_cb(obj, action_mode_select_cb, LV_EVENT_CLICKED, (void *)4);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_home_phone
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_home_phone = obj;
                    lv_obj_set_pos(obj, 13, 78);
                    lv_obj_set_size(obj, 180, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "phone");
                }
            }
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 214, 806);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/home_dock.png");
        }
    }
    
    tick_screen_page_home();
}

void tick_screen_page_home() {
}

void create_screen_page_funtion() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_funtion = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_event_cb(obj, action_gesture_handle_cb, LV_EVENT_GESTURE, (void *)2);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            // img_fun_light
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_light = obj;
            lv_obj_set_pos(obj, 48, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_light.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_light
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_light = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Light");
                }
            }
        }
        {
            // img_fun_fan
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_fan = obj;
            lv_obj_set_pos(obj, 252, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_fan.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_fan
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_fan = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fan");
                }
            }
        }
        {
            // img_fun_timer
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_timer = obj;
            lv_obj_set_pos(obj, 48, 232);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_timer.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_timer
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_timer = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Timer");
                }
            }
        }
        {
            // img_fun_time
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_time = obj;
            lv_obj_set_pos(obj, 252, 232);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_time.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)4);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_time
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_time = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Time");
                }
            }
        }
        {
            // img_fun_wifi
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_wifi = obj;
            lv_obj_set_pos(obj, 48, 416);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_wifi.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)5);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_wifi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_wifi = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Wi-Fi");
                }
            }
        }
        {
            // img_fun_languange
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_languange = obj;
            lv_obj_set_pos(obj, 252, 417);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_language.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)6);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_language
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_language = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Language");
                }
            }
        }
        {
            // img_fun_sys_inifo
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_sys_inifo = obj;
            lv_obj_set_pos(obj, 48, 600);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_sys_info.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)7);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_sys_info
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_sys_info = obj;
                    lv_obj_set_pos(obj, 24, 84);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "System\ninformation");
                }
            }
        }
        {
            // img_fun_settings
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fun_settings = obj;
            lv_obj_set_pos(obj, 252, 600);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_seetings.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)8);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_fun_settings
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_fun_settings = obj;
                    lv_obj_set_pos(obj, 24, 112);
                    lv_obj_set_size(obj, 149, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Settings");
                }
            }
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 214, 806);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fun_dock.png");
        }
    }
    
    tick_screen_page_funtion();
}

void tick_screen_page_funtion() {
}

void create_screen_page_light_ceiling_v1() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_ceiling_v1.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_ceiling_v1 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_ceiling_v1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_ceiling_v1 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_ceiling_light_state_show_v1 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/ceiling_light_frame_100.png");
            lv_image_set_src(obj, &img_ceiling_lum_max);
        }
        {
            // slider_ceiling_light_lum_v1
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_lum_v1 = obj;
            lv_obj_set_pos(obj, 75, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // label_light_ceiling_value_v1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_light_ceiling_value_v1 = obj;
            lv_obj_set_pos(obj, 288, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_72, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "60");
        }
        {
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_light_ceiling_logo_onoff_v1 = obj;
            lv_obj_set_pos(obj, 290, 450);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/light_logo_off.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "1:/light_logo_on.png", NULL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 240, 686);
            lv_obj_set_size(obj, 120, 120);
            lv_obj_add_event_cb(obj, light_c_or_s_select_cb, LV_EVENT_CLICKED, (void *)1);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_page_light_ceiling_v1();
}

void tick_screen_page_light_ceiling_v1() {
}

void create_screen_page_light_side_v1() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_side_v1.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_side_v1 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_side_v1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_side_v1 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_side_light_state_show_v1 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/side_light_frame_100.png");
            lv_image_set_src(obj, &img_side_lum_max);
        }
        {
            // slider_side_light_lum_v1
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_side_light_lum_v1 = obj;
            lv_obj_set_pos(obj, 75, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)2);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // label_light_side_value_v1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_light_side_value_v1 = obj;
            lv_obj_set_pos(obj, 288, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_72, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "60");
        }
        {
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_light_side_logo_onoff_v1 = obj;
            lv_obj_set_pos(obj, 290, 450);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/light_logo_off.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "1:/light_logo_on.png", NULL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 120, 686);
            lv_obj_set_size(obj, 120, 120);
            lv_obj_add_event_cb(obj, light_c_or_s_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_page_light_side_v1();
}

void tick_screen_page_light_side_v1() {
}

void create_screen_page_light_ceiling_v2() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_ceiling_v2.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_ceiling_v2 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_ceiling_v2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_ceiling_v2 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_ceiling_light_state_show_v2 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/ceiling_light_frame_100.png");
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_image_set_src(obj, &img_ceiling_lum_max);
        }
        {
            // slider_ceiling_light_lum_v2
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_lum_v2 = obj;
            lv_obj_set_pos(obj, 72, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_light_ceiling_value_v2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_light_ceiling_value_v2 = obj;
                    lv_obj_set_pos(obj, 49, 54);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "60");
                }
            }
        }
        {
            // slider_ceiling_light_temp_v2
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_temp_v2 = obj;
            lv_obj_set_pos(obj, 258, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 50, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)3);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_pad_top(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, "1:/light_temp_select.png", LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 240, 686);
            lv_obj_set_size(obj, 120, 120);
            lv_obj_add_event_cb(obj, light_c_or_s_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_page_light_ceiling_v2();
}

void tick_screen_page_light_ceiling_v2() {
}

void create_screen_page_light_side_v2() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_side_v2.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_side_v2 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_side_v2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_side_v2 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_side_light_state_show_v2 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/side_light_frame_100.png");
            lv_image_set_src(obj, &img_side_lum_max);
        }
        {
            // slider_side_light_lum_v2
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_side_light_lum_v2 = obj;
            lv_obj_set_pos(obj, 72, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)2);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_light_side_value_v2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_light_side_value_v2 = obj;
                    lv_obj_set_pos(obj, 49, 54);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "60");
                }
            }
        }
        {
            // slider_side_light_temp_v2
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_side_light_temp_v2 = obj;
            lv_obj_set_pos(obj, 258, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 50, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)4);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_pad_top(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, "1:/light_temp_select.png", LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 120, 686);
            lv_obj_set_size(obj, 120, 120);
            lv_obj_add_event_cb(obj, light_c_or_s_select_cb, LV_EVENT_CLICKED, (void *)4);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_page_light_side_v2();
}

void tick_screen_page_light_side_v2() {
}

void create_screen_page_light_ceiling_v3() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_ceiling_v3.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_ceiling_v3 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_ceiling_v3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_ceiling_v3 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_ceiling_light_state_show_v3 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/ceiling_light_frame_100.png");
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_image_set_src(obj, &img_ceiling_lum_max);
        }
        {
            // slider_ceiling_light_lum_v3
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_lum_v3 = obj;
            lv_obj_set_pos(obj, 72, 280);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_light_ceiling_value_v3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_light_ceiling_value_v3 = obj;
                    lv_obj_set_pos(obj, 49, 54);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "60");
                }
            }
        }
        {
            // slider_ceiling_light_temp_v3
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_temp_v3 = obj;
            lv_obj_set_pos(obj, 258, 280);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 50, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)3);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_pad_top(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, "1:/light_temp_select.png", LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_page_light_ceiling_v3();
}

void tick_screen_page_light_ceiling_v3() {
}

void create_screen_page_light_ceiling_v4() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_ceiling_v4.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_ceiling_v4 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_ceiling_v4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_ceiling_v4 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_ceiling_light_state_show_v4 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/ceiling_light_frame_100.png");
            lv_image_set_src(obj, &img_ceiling_lum_max);
        }
        {
            // slider_ceiling_light_lum_v4
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_lum_v4 = obj;
            lv_obj_set_pos(obj, 75, 280);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // label_light_ceiling_value_v4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_light_ceiling_value_v4 = obj;
            lv_obj_set_pos(obj, 288, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_72, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "60");
        }
        {
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_light_ceiling_logo_onoff_v4 = obj;
            lv_obj_set_pos(obj, 290, 450);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/light_logo_off.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "1:/light_logo_on.png", NULL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
    }
    
    tick_screen_page_light_ceiling_v4();
}

void tick_screen_page_light_ceiling_v4() {
}

void create_screen_page_light_ceiling_v5() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/light_ceiling_v5.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_ceiling_v5 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_light_ceiling_v5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_ceiling_v5 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_ceiling_light_state_show_v5 = obj;
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            // lv_image_set_src(obj, "1:/ceiling_light_frame_100.png");
            lv_obj_set_style_image_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_image_set_src(obj, &img_ceiling_lum_max);
        }
        {
            // slider_ceiling_light_lum_v5
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_lum_v5 = obj;
            lv_obj_set_pos(obj, 72, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)1);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_light_ceiling_value_v5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_light_ceiling_value_v5 = obj;
                    lv_obj_set_pos(obj, 49, 54);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "60");
                }
            }
        }
        {
            // slider_ceiling_light_temp_v5
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_ceiling_light_temp_v5 = obj;
            lv_obj_set_pos(obj, 258, 220);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 50, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)3);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_pad_top(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, "1:/light_temp_select.png", LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        // {
        //     lv_obj_t *obj = lv_button_create(parent_obj);
        //     lv_obj_set_pos(obj, 240, 686);
        //     lv_obj_set_size(obj, 120, 120);
        //     lv_obj_add_event_cb(obj, light_c_or_s_select_cb, LV_EVENT_CLICKED, (void *)5);
        //     lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        //     lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        // }
    }
    
    tick_screen_page_light_ceiling_v5();
}

void tick_screen_page_light_ceiling_v5() {
}

void create_screen_page_light_ambient_v5() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_light_ambient_v5 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_light_ambient_v5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_light_ambient_v5 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 364, 28);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_to_fan.png");
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 0, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/ambient_light_frame.png");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            lv_obj_set_pos(obj, 53, 257);
            lv_obj_set_size(obj, 375, 375);
            lv_arc_set_value(obj, 23);
            lv_arc_set_bg_start_angle(obj, 0);
            lv_arc_set_bg_end_angle(obj, 359);
            lv_arc_set_rotation(obj, 270);
            lv_obj_set_style_bg_image_src(obj, "1:/rgb_color_ring.png", LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_src(obj, "1:/rgb_select_ring.png", LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 65, LV_PART_KNOB | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // colorwhel_select_show
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.colorwhel_select_show = obj;
                    lv_obj_set_pos(obj, 107, 107);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/rgb_color_show_ring.png");
                }
            }
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 134, 702);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/ceiling_light_select_off.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 258, 702);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/ambient_light_select_on.png");
        }
    }
    
    tick_screen_page_light_ambient_v5();
}

void tick_screen_page_light_ambient_v5() {
}

void create_screen_page_fan() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/fan.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_fan = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)9);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_title_fan
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_fan = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Fan");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 345, 0);
            lv_obj_set_size(obj, 135, 130);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)1);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_fan_speed_show = obj;
            lv_obj_set_pos(obj, 0, 189);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/fan_speed_show_01.png");
        }
        {
            // slider_fan
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_fan = obj;
            lv_obj_set_pos(obj, 75, 280);
            lv_obj_set_size(obj, 150, 450);
            lv_slider_set_value(obj, 60, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)5);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // label_fan_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_fan_value = obj;
            lv_obj_set_pos(obj, 288, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_72, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "60");
        }
        {
            // imgbtn_fan_logo_onoff
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_fan_logo_onoff = obj;
            lv_obj_set_pos(obj, 290, 450);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/fan_logo_off.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "1:/fan_logo_on.png", NULL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
    }
    
    tick_screen_page_fan();
}

void tick_screen_page_fan() {
}

void create_screen_page_timer_set() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_timer_set = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_timer
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_timer = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Timer");
        }
        {
            // clock_set_hour
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.clock_set_hour = obj;
            lv_obj_set_pos(obj, 70, 146);
            lv_obj_set_size(obj, 88, 474);
            lv_roller_set_options(obj, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23", LV_ROLLER_MODE_INFINITE);
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_VALUE_CHANGED, (void *)1);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 36, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // clock_set_minute
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.clock_set_minute = obj;
            lv_obj_set_pos(obj, 205, 146);
            lv_obj_set_size(obj, 88, 474);
            lv_roller_set_options(obj, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59", LV_ROLLER_MODE_INFINITE);
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_VALUE_CHANGED, (void *)2);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 36, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // clock_set_second
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.clock_set_second = obj;
            lv_obj_set_pos(obj, 338, 146);
            lv_obj_set_size(obj, 88, 474);
            lv_roller_set_options(obj, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59", LV_ROLLER_MODE_INFINITE);
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_VALUE_CHANGED, (void *)3);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 36, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_line_space(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // clock_logo_h
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_logo_h = obj;
            lv_obj_set_pos(obj, 152, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "H");
        }
        {
            // clock_logo_m
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_logo_m = obj;
            lv_obj_set_pos(obj, 288, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "M");
        }
        {
            // clock_logo_s
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_logo_s = obj;
            lv_obj_set_pos(obj, 427, 350);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "S");
        }
        {
            // imgbtn_timer_start
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_timer_start = obj;
            lv_obj_set_pos(obj, 126, 662);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 63);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/timer_start_off.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "1:/timer_start_on.png", NULL);
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_CLICKED, (void *)10);
        }
    }
    
    tick_screen_page_timer_set();
}

void tick_screen_page_timer_set() {
}

void create_screen_page_timer_run() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_timer_run = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_timer_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_timer_1 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Timer");
        }
        {
            // imgbtn_timer_start_1
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.imgbtn_timer_start_1 = obj;
            lv_obj_set_pos(obj, 252, 662);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, 88);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/timer_stop.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "1:/timer_start.png", NULL);
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_CLICKED, (void *)11);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 36, 662);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/timer_end.png");
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_CLICKED, (void *)12);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // container_timer_remian
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_timer_remian = obj;
            lv_obj_set_pos(obj, 60, 350);
            lv_obj_set_size(obj, 360, 100);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_timer_remain
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_timer_remain = obj;
                    lv_obj_set_pos(obj, 17, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_64, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00 01 59");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 113, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_64, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ":      :");
                }
            }
        }
    }
    
    tick_screen_page_timer_run();
}

void tick_screen_page_timer_run() {
}

void create_screen_page_set_time() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_set_time = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_time = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Time");
        }
        {
            // label_time_set_now
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_time_set_now = obj;
            lv_obj_set_pos(obj, 97, 180);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_112, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "13 59");
        }
        {
            // label_time_set_blink
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_time_set_blink = obj;
            lv_obj_set_pos(obj, 226, 170);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_112, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, ":");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 32, 360);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/time_set.png");
            lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_CLICKED, (void *)20);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_time_set_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_time_set_title = obj;
                    lv_obj_set_pos(obj, 30, 25);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "TIME");
                }
                {
                    // label_time_set_time
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_time_set_time = obj;
                    lv_obj_set_pos(obj, 30, 88);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Time");
                }
                {
                    // label_time_set_now_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_time_set_now_1 = obj;
                    lv_obj_set_pos(obj, 280, 88);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "13 59");
                }
                {
                    // label_time_set_blink_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_time_set_blink_1 = obj;
                    lv_obj_set_pos(obj, 317, 85);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ":");
                }
            }
        }
        {
            // img_time_setting
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_time_setting = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/time_setting.png");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // time_set_window_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_set_window_title = obj;
                    lv_obj_set_pos(obj, 29, 407);
                    lv_obj_set_size(obj, 424, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Set time");
                }
                {
                    // roller_time_set_hour
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    objects.roller_time_set_hour = obj;
                    lv_obj_set_pos(obj, 110, 463);
                    lv_obj_set_size(obj, 120, 200);
                    lv_roller_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23", LV_ROLLER_MODE_INFINITE);
                    lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_VALUE_CHANGED, (void *)21);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00a2ff), LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // label_window_set_time_h
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_window_set_time_h = obj;
                    lv_obj_set_pos(obj, 217, 535);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "H");
                }
                {
                    // roller_time_set_minute
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    objects.roller_time_set_minute = obj;
                    lv_obj_set_pos(obj, 264, 463);
                    lv_obj_set_size(obj, 120, 200);
                    lv_roller_set_options(obj, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59", LV_ROLLER_MODE_INFINITE);
                    lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_VALUE_CHANGED, (void *)22);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00a2ff), LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // label_window_set_time_m
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_window_set_time_m = obj;
                    lv_obj_set_pos(obj, 373, 535);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "M");
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    lv_obj_set_pos(obj, 47, 716);
                    lv_obj_set_size(obj, 180, 80);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_CLICKED, (void *)23);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_window_set_time_canel
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_window_set_time_canel = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Canel");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    lv_obj_set_pos(obj, 250, 716);
                    lv_obj_set_size(obj, 180, 80);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_add_event_cb(obj, action_timer_ctrl, LV_EVENT_CLICKED, (void *)24);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_window_set_time_ok
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_window_set_time_ok = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "OK");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_set_time();
}

void tick_screen_page_set_time() {
}

void create_screen_page_set_language() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_set_language = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_language
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_language = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Language");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 124);
            lv_obj_set_size(obj, 480, 730);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn_language_eng
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_eng = obj;
                    lv_obj_set_pos(obj, 32, 4);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "English");
                        }
                    }
                }
                {
                    // btn_language_esp
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_esp = obj;
                    lv_obj_set_pos(obj, 32, 123);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)2);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Español");
                        }
                    }
                }
                {
                    // btn_language_fra
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_fra = obj;
                    lv_obj_set_pos(obj, 32, 243);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)3);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Français");
                        }
                    }
                }
                {
                    // btn_language_deu
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_deu = obj;
                    lv_obj_set_pos(obj, 33, 366);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)4);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Deutsch");
                        }
                    }
                }
                {
                    // btn_language_chn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_chn = obj;
                    lv_obj_set_pos(obj, 34, 494);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)5);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "简体(中文)");
                        }
                    }
                }
                {
                    // btn_language_jpa
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_jpa = obj;
                    lv_obj_set_pos(obj, 33, 610);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)6);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "にほんご");
                        }
                    }
                }
                {
                    // btn_language_kra
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_language_kra = obj;
                    lv_obj_set_pos(obj, 34, 730);
                    lv_obj_set_size(obj, 417, 96);
                    lv_obj_add_event_cb(obj, action_language_select, LV_EVENT_CLICKED, (void *)7);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_kr_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "한국어");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_set_language();
}

void tick_screen_page_set_language() {
}

void create_screen_page_set_sysinfo() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_set_sysinfo = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_sysinfo
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_sysinfo = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "System information");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 32, 128);
            lv_obj_set_size(obj, 416, 416);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_sysinfo_type
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_sysinfo_type = obj;
                    lv_obj_set_pos(obj, 24, 36);
                    lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "System type");
                }
                {
                    // label_sysinfo_id
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_sysinfo_id = obj;
                    lv_obj_set_pos(obj, 24, 120);
                    lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "System id");
                }
                {
                    // label_sysinfo_hardware
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_sysinfo_hardware = obj;
                    lv_obj_set_pos(obj, 24, 200);
                    lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Hardware unit");
                }
                {
                    // label_sysinfo_software
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_sysinfo_software = obj;
                    lv_obj_set_pos(obj, 24, 280);
                    lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Software unit");
                }
                {
                    // label_sysinfo_mac
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_sysinfo_mac = obj;
                    lv_obj_set_pos(obj, 24, 360);
                    lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Mac");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, 241, 36);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Joye-5 inch");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 298, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "OEKZQ");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_pos(obj, 295, 200);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "123456");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 295, 280);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "123456");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, 295, 360);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfffdfdfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "123456");
                }
            }
        }
    }
    
    tick_screen_page_set_sysinfo();
}

void tick_screen_page_set_sysinfo() {
}

void create_screen_page_keyboard() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_keyboard = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_keyboard_settings
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_keyboard_settings = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Settings");
        }
        {
            // label_key_input
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_key_input = obj;
            lv_obj_set_pos(obj, 0, 178);
            lv_obj_set_size(obj, 480, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Enter system code");
        }
        {
            // label_key_input_err
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_key_input_err = obj;
            lv_obj_set_pos(obj, 0, 178);
            lv_obj_set_size(obj, 480, LV_SIZE_CONTENT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfffd2525), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "System code don’t match");
        }
        {
            // key_input_status
            lv_obj_t *obj = lv_imagebutton_create(parent_obj);
            objects.key_input_status = obj;
            lv_obj_set_pos(obj, 99, 256);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "1:/key_input_null.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "1:/key_input_1.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "1:/key_input_2.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "1:/key_input_3.png", NULL);
            lv_imagebutton_set_src(obj, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "1:/key_input_4.png", NULL);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // container_keyboard
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_keyboard = obj;
            lv_obj_set_pos(obj, 0, 374);
            lv_obj_set_size(obj, 480, 480);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // key_1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_1 = obj;
                    lv_obj_set_pos(obj, 60, 36);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "1");
                        }
                    }
                }
                {
                    // key_2
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_2 = obj;
                    lv_obj_set_pos(obj, 198, 36);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)2);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "2");
                        }
                    }
                }
                {
                    // key_3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_3 = obj;
                    lv_obj_set_pos(obj, 336, 36);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)3);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "3");
                        }
                    }
                }
                {
                    // key_4
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_4 = obj;
                    lv_obj_set_pos(obj, 60, 144);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)4);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "4");
                        }
                    }
                }
                {
                    // key_5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_5 = obj;
                    lv_obj_set_pos(obj, 198, 144);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)5);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "5");
                        }
                    }
                }
                {
                    // key_6
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_6 = obj;
                    lv_obj_set_pos(obj, 336, 144);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)6);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "6");
                        }
                    }
                }
                {
                    // key_7
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_7 = obj;
                    lv_obj_set_pos(obj, 60, 252);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)7);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "7");
                        }
                    }
                }
                {
                    // key_8
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_8 = obj;
                    lv_obj_set_pos(obj, 198, 252);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)8);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "8");
                        }
                    }
                }
                {
                    // key_9
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_9 = obj;
                    lv_obj_set_pos(obj, 336, 252);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)9);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "9");
                        }
                    }
                }
                {
                    // key_0
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_0 = obj;
                    lv_obj_set_pos(obj, 199, 360);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_press.png", LV_PART_MAIN | LV_STATE_PRESSED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_cal_sans_semi_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0");
                        }
                    }
                }
                {
                    // key_del
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.key_del = obj;
                    lv_obj_set_pos(obj, 336, 361);
                    lv_obj_set_size(obj, 84, 84);
                    lv_obj_add_event_cb(obj, action_keyboard_input, LV_EVENT_CLICKED, (void *)10);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/key_del.png", LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_page_keyboard();
}

void tick_screen_page_keyboard() {
}

void create_screen_page_set() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_set = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)10);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_set_settings
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_set_settings = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Settings");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 32, 124);
            lv_obj_set_size(obj, 416, 180);
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)1);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 12);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/set_dev.png");
                }
                {
                    // label_dev_deft
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_dev_deft = obj;
                    lv_obj_set_pos(obj, 12, 117);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Device default");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj10 = obj;
            lv_obj_set_pos(obj, 32, 320);
            lv_obj_set_size(obj, 416, 180);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)12);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 12);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/set_ui.png");
                }
                {
                    // label_ui_version
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_ui_version = obj;
                    lv_obj_set_pos(obj, 12, 117);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "UI version");
                }
                {
                    // label_ui_version_nol
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_ui_version_nol = obj;
                    lv_obj_set_pos(obj, 261, 20);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Version 1");
                }
            }
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_waring_in = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/ui_in_waring.png");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_waring_in_title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_waring_in_title = obj;
                    lv_obj_set_pos(obj, 176, 214);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Notification");
                }
                {
                    // label_waring_in_explain
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_waring_in_explain = obj;
                    lv_obj_set_pos(obj, 67, 285);
                    lv_obj_set_size(obj, 346, 252);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Non-professionals are prohibited from modifying this function.\nFor settings, please contact after-sales support.\nIncorrect configuration may cause device abnormalities.");
                }
                {
                    // btn_waring_in_canel
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_waring_in_canel = obj;
                    lv_obj_set_pos(obj, 49, 559);
                    lv_obj_set_size(obj, 189, 80);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)13);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj11 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Canel");
                        }
                    }
                }
                {
                    // btn_waring_in_continue
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_waring_in_continue = obj;
                    lv_obj_set_pos(obj, 242, 559);
                    lv_obj_set_size(obj, 189, 80);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)14);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Continue");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_set();
}

void tick_screen_page_set() {
}

void create_screen_page_deft_light_v1() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_v1 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_1 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 248);
            lv_obj_set_size(obj, 420, 242);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_light_v1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_light_v1 = obj;
                    lv_obj_set_pos(obj, 24, 26);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Light");
                }
                {
                    // label_deft_ceiling_light_v1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_ceiling_light_v1 = obj;
                    lv_obj_set_pos(obj, 24, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Ceiling light");
                }
                {
                    // label_deft_side_light_v1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_side_light_v1 = obj;
                    lv_obj_set_pos(obj, 24, 172);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Side light");
                }
                {
                    // btn_deft_ceiling_light_lum_v1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ceiling_light_lum_v1 = obj;
                    lv_obj_set_pos(obj, 278, 77);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)21);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_lum_value_v1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_lum_value_v1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
                {
                    // btn_deft_side_light_lum_v1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_side_light_lum_v1 = obj;
                    lv_obj_set_pos(obj, 278, 160);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)23);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_side_light_lum_value_v1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_side_light_lum_value_v1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 519);
            lv_obj_set_size(obj, 420, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_fan_v1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_fan_v1 = obj;
                    lv_obj_set_pos(obj, 24, 38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fan");
                }
                {
                    // btn_deft_fan_v1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_fan_v1 = obj;
                    lv_obj_set_pos(obj, 278, 26);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)25);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_fan_value_v1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_fan_value_v1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_light_v1();
}

void tick_screen_page_deft_light_v1() {
}

void create_screen_page_deft_light_v2() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_v2 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_2 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 240);
            lv_obj_set_size(obj, 480, 614);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // container_ceiling
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.container_ceiling = obj;
                    lv_obj_set_pos(obj, 30, 8);
                    lv_obj_set_size(obj, 420, 242);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_v2 = obj;
                            lv_obj_set_pos(obj, 24, 26);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Ceiling light");
                        }
                        {
                            // label_deft_ceiling_light_brightness_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_brightness_v2 = obj;
                            lv_obj_set_pos(obj, 24, 89);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Brightness");
                        }
                        {
                            // label_deft_ceiling_light_colortemp_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_colortemp_v2 = obj;
                            lv_obj_set_pos(obj, 24, 172);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Color temperature");
                        }
                        {
                            // btn_deft_ceiling_light_lum_v2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_deft_ceiling_light_lum_v2 = obj;
                            lv_obj_set_pos(obj, 278, 77);
                            lv_obj_set_size(obj, 118, 56);
                            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)21);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_deft_ceiling_light_lum_value_v2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_deft_ceiling_light_lum_value_v2 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "60%");
                                }
                            }
                        }
                        {
                            // btn_deft_ceiling_light_temp_v2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_deft_ceiling_light_temp_v2 = obj;
                            lv_obj_set_pos(obj, 278, 160);
                            lv_obj_set_size(obj, 118, 56);
                            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)22);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_deft_ceiling_light_temp_value_v2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_deft_ceiling_light_temp_value_v2 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "60%");
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 30, 266);
                    lv_obj_set_size(obj, 420, 242);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_side_light_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_side_light_v2 = obj;
                            lv_obj_set_pos(obj, 24, 26);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Side light");
                        }
                        {
                            // label_deft_side_light_brightness_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_side_light_brightness_v2 = obj;
                            lv_obj_set_pos(obj, 24, 89);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Brightness");
                        }
                        {
                            // label_deft_side_light_colortemp_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_side_light_colortemp_v2 = obj;
                            lv_obj_set_pos(obj, 24, 172);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Color temperature");
                        }
                        {
                            // btn_deft_side_light_lum_v2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_deft_side_light_lum_v2 = obj;
                            lv_obj_set_pos(obj, 278, 77);
                            lv_obj_set_size(obj, 118, 56);
                            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)23);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_deft_side_light_lum_value_v2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_deft_side_light_lum_value_v2 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "60%");
                                }
                            }
                        }
                        {
                            // btn_deft_side_light_temp_v2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_deft_side_light_temp_v2 = obj;
                            lv_obj_set_pos(obj, 278, 160);
                            lv_obj_set_size(obj, 118, 56);
                            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)24);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_deft_side_light_temp_value_v2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_deft_side_light_temp_value_v2 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "60%");
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 30, 524);
                    lv_obj_set_size(obj, 420, 108);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_fan_v2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_fan_v2 = obj;
                            lv_obj_set_pos(obj, 24, 38);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Fan");
                        }
                        {
                            // btn_deft_fan_v2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.btn_deft_fan_v2 = obj;
                            lv_obj_set_pos(obj, 278, 26);
                            lv_obj_set_size(obj, 118, 56);
                            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)25);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // label_deft_fan_value_v2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.label_deft_fan_value_v2 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "60%");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_light_v2();
}

void tick_screen_page_deft_light_v2() {
}

void create_screen_page_deft_light_v3() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_v3 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_3 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 248);
            lv_obj_set_size(obj, 420, 242);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_light_v3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_light_v3 = obj;
                    lv_obj_set_pos(obj, 24, 26);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Light");
                }
                {
                    // label_deft_ceiling_light_brightness_v3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_ceiling_light_brightness_v3 = obj;
                    lv_obj_set_pos(obj, 24, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Brightness");
                }
                {
                    // label_deft_ceiling_light_colortemp_v3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_ceiling_light_colortemp_v3 = obj;
                    lv_obj_set_pos(obj, 24, 172);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Color temperature");
                }
                {
                    // btn_deft_ceiling_light_lum_v3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ceiling_light_lum_v3 = obj;
                    lv_obj_set_pos(obj, 278, 77);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)21);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_lum_value_v3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_lum_value_v3 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
                {
                    // btn_deft_ceiling_light_temp_v3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ceiling_light_temp_v3 = obj;
                    lv_obj_set_pos(obj, 278, 160);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)22);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_temp_value_v3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_temp_value_v3 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 519);
            lv_obj_set_size(obj, 420, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_fan_v3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_fan_v3 = obj;
                    lv_obj_set_pos(obj, 24, 38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fan");
                }
                {
                    // btn_deft_fan_v3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_fan_v3 = obj;
                    lv_obj_set_pos(obj, 278, 26);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)25);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_fan_value_v3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_fan_value_v3 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_light_v3();
}

void tick_screen_page_deft_light_v3() {
}

void create_screen_page_deft_light_v4() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_v4 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_4 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 248);
            lv_obj_set_size(obj, 420, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_light_v4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_light_v4 = obj;
                    lv_obj_set_pos(obj, 24, 38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Light");
                }
                {
                    // btn_deft_ceiling_light_lum_v4
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ceiling_light_lum_v4 = obj;
                    lv_obj_set_pos(obj, 278, 26);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)21);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_lum_value_v4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_lum_value_v4 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 372);
            lv_obj_set_size(obj, 420, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_fan_v4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_fan_v4 = obj;
                    lv_obj_set_pos(obj, 24, 38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fan");
                }
                {
                    // btn_deft_fan_v4
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_fan_v4 = obj;
                    lv_obj_set_pos(obj, 278, 26);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)25);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_fan_value_v4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_fan_value_v4 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_light_v4();
}

void tick_screen_page_deft_light_v4() {
}

void create_screen_page_deft_light_v5() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_v5 = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_5 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 248);
            lv_obj_set_size(obj, 420, 242);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_light_v5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_light_v5 = obj;
                    lv_obj_set_pos(obj, 24, 26);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Light");
                }
                {
                    // label_deft_ceiling_light_brightness_v5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_ceiling_light_brightness_v5 = obj;
                    lv_obj_set_pos(obj, 24, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Brightness");
                }
                {
                    // label_deft_ceiling_light_colortemp_v5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_ceiling_light_colortemp_v5 = obj;
                    lv_obj_set_pos(obj, 24, 172);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Color temperature");
                }
                {
                    // btn_deft_ceiling_light_lum_v5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ceiling_light_lum_v5 = obj;
                    lv_obj_set_pos(obj, 278, 77);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)21);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_lum_value_v5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_lum_value_v5 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
                {
                    // btn_deft_ceiling_light_temp_v5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ceiling_light_temp_v5 = obj;
                    lv_obj_set_pos(obj, 278, 160);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)22);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_ceiling_light_temp_value_v5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_ceiling_light_temp_value_v5 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 506);
            lv_obj_set_size(obj, 420, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // labnel_deft_ambient_v5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.labnel_deft_ambient_v5 = obj;
                    lv_obj_set_pos(obj, 24, 38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Ambient Light");
                }
                {
                    // btn_deft_ambient_v5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_ambient_v5 = obj;
                    lv_obj_set_pos(obj, 278, 26);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)26);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd8cd22), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 630);
            lv_obj_set_size(obj, 420, 108);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // labnel_deft_fan_v5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.labnel_deft_fan_v5 = obj;
                    lv_obj_set_pos(obj, 24, 38);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fan");
                }
                {
                    // btn_deft_fan_v5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_deft_fan_v5 = obj;
                    lv_obj_set_pos(obj, 278, 26);
                    lv_obj_set_size(obj, 118, 56);
                    lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)25);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_fan_value_v5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_fan_value_v5 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60%");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_light_v5();
}

void tick_screen_page_deft_light_v5() {
}

void create_screen_page_deft_light_lum_slider() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_lum_slider = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_6 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 29, 186);
            lv_obj_set_size(obj, 423, 644);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3c2b57), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_slider_lum_light_type
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_slider_lum_light_type = obj;
                    lv_obj_set_pos(obj, 24, 44);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Ceiling light");
                }
                {
                    // label_deft_slider_brightness
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_slider_brightness = obj;
                    lv_obj_set_pos(obj, 24, 84);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Brightness");
                }
                {
                    // img_deft_slider_lum_confirm
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.img_deft_slider_lum_confirm = obj;
                    lv_obj_set_pos(obj, 311, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/roller_confirm.png");
                    lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                }
                {
                    // slider_deft_light_lum
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.slider_deft_light_lum = obj;
                    lv_obj_set_pos(obj, 137, 144);
                    lv_obj_set_size(obj, 150, 450);
                    lv_slider_set_value(obj, 60, LV_ANIM_OFF);
                    lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)11);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_light_lum_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_light_lum_value = obj;
                            lv_obj_set_pos(obj, 57, 36);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_light_lum_slider();
}

void tick_screen_page_deft_light_lum_slider() {
}

void create_screen_page_deft_light_temp_slider() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_light_temp_slider = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_7
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_7 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 29, 186);
            lv_obj_set_size(obj, 423, 644);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3c2b57), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_slider_temp_light_type
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_slider_temp_light_type = obj;
                    lv_obj_set_pos(obj, 24, 44);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Ceiling light");
                }
                {
                    // label_deft_slider_color_temp
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_slider_color_temp = obj;
                    lv_obj_set_pos(obj, 24, 84);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Color temperature");
                }
                {
                    // img_deft_slider_temp_confirm
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.img_deft_slider_temp_confirm = obj;
                    lv_obj_set_pos(obj, 311, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/roller_confirm.png");
                    lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                }
                {
                    // slider_ceiling_light_temp_3
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.slider_ceiling_light_temp_3 = obj;
                    lv_obj_set_pos(obj, 137, 144);
                    lv_obj_set_size(obj, 150, 450);
                    lv_slider_set_value(obj, 50, LV_ANIM_OFF);
                    lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)12);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/colortemp_background.png", LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_image_src(obj, "1:/light_temp_select.png", LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_page_deft_light_temp_slider();
}

void tick_screen_page_deft_light_temp_slider() {
}

void create_screen_page_deft_fan_slider() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_fan_slider = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_8
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_8 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_on.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj14 = obj;
            lv_obj_set_pos(obj, 29, 186);
            lv_obj_set_size(obj, 423, 644);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3c2b57), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_deft_slider_fan
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_deft_slider_fan = obj;
                    lv_obj_set_pos(obj, 24, 44);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Fan");
                }
                {
                    // img_deft_roller_fan
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.img_deft_roller_fan = obj;
                    lv_obj_set_pos(obj, 311, 32);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/roller_confirm.png");
                    lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                }
                {
                    // slider_deft_fan
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.slider_deft_fan = obj;
                    lv_obj_set_pos(obj, 137, 144);
                    lv_obj_set_size(obj, 150, 450);
                    lv_slider_set_value(obj, 60, LV_ANIM_OFF);
                    lv_obj_add_event_cb(obj, action_slider_change_cb, LV_EVENT_VALUE_CHANGED, (void *)13);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 16, LV_PART_KNOB | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_deft_fan_value
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_deft_fan_value = obj;
                            lv_obj_set_pos(obj, 57, 36);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "60");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_deft_fan_slider();
}

void tick_screen_page_deft_fan_slider() {
}

void create_screen_page_deft_radar() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_radar = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_9
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_9 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_on.png");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 248);
            lv_obj_set_size(obj, 420, 568);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_radar_mont
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_radar_mont = obj;
                    lv_obj_set_pos(obj, 20, 28);
                    lv_obj_set_size(obj, 380, 38);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Radar monitoring time");
                }
                {
                    // roller_set_radar
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    objects.roller_set_radar = obj;
                    lv_obj_set_pos(obj, 166, 72);
                    lv_obj_set_size(obj, 88, 474);
                    lv_roller_set_options(obj, "MIN\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59", LV_ROLLER_MODE_INFINITE);
                    lv_obj_add_event_cb(obj, action_deft_roller_change_cb, LV_EVENT_VALUE_CHANGED, (void *)1);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 36, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // label_radar_m
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_radar_m = obj;
                    lv_obj_set_pos(obj, 267, 276);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "M");
                }
                {
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.obj16 = obj;
                    lv_obj_set_pos(obj, 155, 258);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 110, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.obj17 = obj;
                    lv_obj_set_pos(obj, 155, 349);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 110, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_page_deft_radar();
}

void tick_screen_page_deft_radar() {
}

void create_screen_page_deft_auto_vent() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_deft_auto_vent = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_title_deft_10
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_title_deft_10 = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Device default");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 63, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/light_fan_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_PRESSED, (void *)1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 196, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/radar_off.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)2);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 329, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/auto_ven_on.png");
            lv_obj_add_event_cb(obj, action_dev_deft_select_cb, LV_EVENT_CLICKED, (void *)3);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // label_auto_vent
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_auto_vent = obj;
            lv_obj_set_pos(obj, 32, 248);
            lv_obj_set_size(obj, 416, 93);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Auto ventilation");
        }
        {
            // btn_deft_auto_onoff
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.btn_deft_auto_onoff = obj;
            lv_obj_set_pos(obj, 328, 270);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/btn_off.png");
            lv_obj_add_event_cb(obj, action_onoff_click_cb, LV_EVENT_CLICKED, (void *)1);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.container_auto_vent = obj;
            lv_obj_set_pos(obj, 30, 352);
            lv_obj_set_size(obj, 408, 454);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_interval
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_interval = obj;
                    lv_obj_set_pos(obj, 63, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Interval");
                }
                {
                    // deft_roller_interval
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    objects.deft_roller_interval = obj;
                    lv_obj_set_pos(obj, 67, 88);
                    lv_obj_set_size(obj, 88, 300);
                    lv_roller_set_options(obj, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24", LV_ROLLER_MODE_INFINITE);
                    lv_obj_add_event_cb(obj, action_deft_roller_change_cb, LV_EVENT_VALUE_CHANGED, (void *)2);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 36, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // label_auto_h
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_auto_h = obj;
                    lv_obj_set_pos(obj, 167, 199);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "H");
                }
                {
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.obj20 = obj;
                    lv_obj_set_pos(obj, 55, 185);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 110, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.obj21 = obj;
                    lv_obj_set_pos(obj, 55, 280);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 110, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_duration = obj;
                    lv_obj_set_pos(obj, 240, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Duration");
                }
                {
                    // deft_roller_duration
                    lv_obj_t *obj = lv_roller_create(parent_obj);
                    objects.deft_roller_duration = obj;
                    lv_obj_set_pos(obj, 240, 88);
                    lv_obj_set_size(obj, 88, 300);
                    lv_roller_set_options(obj, "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59", LV_ROLLER_MODE_INFINITE);
                    lv_obj_add_event_cb(obj, action_deft_roller_change_cb, LV_EVENT_VALUE_CHANGED, (void *)3);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_48, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 36, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_line_space(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // label_auto_m
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_auto_m = obj;
                    lv_obj_set_pos(obj, 340, 199);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "M");
                }
                {
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.obj23 = obj;
                    lv_obj_set_pos(obj, 230, 185);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 110, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.obj24 = obj;
                    lv_obj_set_pos(obj, 230, 280);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    static lv_point_precise_t line_points[] = {
                        { 0, 0 },
                        { 110, 0 }
                    };
                    lv_line_set_points(obj, line_points, 2);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_opa(obj, 51, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_page_deft_auto_vent();
}

void tick_screen_page_deft_auto_vent() {
}

void create_screen_page_set_ui() {
    FATFS fs1;
	FILINFO info1;
	UINT br = 0;
	const char *fn1 = "1:/background.jpg";
	
	f_mount(&fs1, "1:", 1);
	f_open(&bk_file,  fn1, FA_CREATE_ALWAYS | FA_READ);
	f_stat(fn1, &info1);
	f_read(&bk_file, bk_decode_buffer, info1.fsize, &br);
	f_close(&bk_file);

	lvgl_decode(IMAGE_JPEG,JPEG_OUTPUT_RGB888,(uint32_t)bk_decode_buffer, br,(uint32_t)ADDR_L1_CPU);

    lv_obj_t *obj = lv_obj_create(0);
    objects.page_set_ui = obj;
    lv_obj_set_size(obj, 480, 854);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(lv_screen_active(),LV_OPA_TRANSP,LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_layer_bottom(), LV_OPA_TRANSP, LV_PART_MAIN);
    {
        lv_obj_t *parent_obj = obj;
        {
            // container_background
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 854);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_display_t *disp = lv_obj_get_display(obj);
            lv_display_set_color_format(disp, LV_COLOR_FORMAT_ARGB8888);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 120, 88);
            lv_obj_add_event_cb(obj, action_goto_new_screen, LV_EVENT_CLICKED, (void *)15);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, "1:/arrow_back.png");
                }
            }
        }
        {
            // label_set_ui_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_set_ui_title = obj;
            lv_obj_set_pos(obj, 88, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "UI version");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 118);
            lv_obj_set_size(obj, 480, 736);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // btn_ui_version1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_ui_version1 = obj;
                    lv_obj_set_pos(obj, 30, 6);
                    lv_obj_set_size(obj, 420, 152);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_set_ui_version1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_set_ui_version1 = obj;
                            lv_obj_set_pos(obj, 3, 17);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Version 1");
                        }
                        {
                            // label_version1_explain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_version1_explain = obj;
                            lv_obj_set_pos(obj, 3, 66);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Ceiling Light: Brightness;\nSide Light: Brightness;");
                        }
                    }
                }
                {
                    // btn_ui_version2
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_ui_version2 = obj;
                    lv_obj_set_pos(obj, 30, 174);
                    lv_obj_set_size(obj, 420, 184);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)2);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_set_ui_version2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_set_ui_version2 = obj;
                            lv_obj_set_pos(obj, 3, 17);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Version 2");
                        }
                        {
                            // label_version2_explain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_version2_explain = obj;
                            lv_obj_set_pos(obj, 3, 53);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Ceiling Light: \nBrightness & Color temperature;\nSide Light:\nBrightness & Color temperature;");
                        }
                    }
                }
                {
                    // btn_ui_version3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_ui_version3 = obj;
                    lv_obj_set_pos(obj, 32, 374);
                    lv_obj_set_size(obj, 420, 152);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)3);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_set_ui_version3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_set_ui_version3 = obj;
                            lv_obj_set_pos(obj, 3, 17);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Version 3");
                        }
                        {
                            // label_version3_explain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_version3_explain = obj;
                            lv_obj_set_pos(obj, 3, 66);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Ceiling Light: \nBrightness & Color temperature;");
                        }
                    }
                }
                {
                    // btn_ui_version4
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_ui_version4 = obj;
                    lv_obj_set_pos(obj, 30, 542);
                    lv_obj_set_size(obj, 420, 152);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)4);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_set_ui_version4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_set_ui_version4 = obj;
                            lv_obj_set_pos(obj, 3, 17);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Version 4");
                        }
                        {
                            // label_version4_explain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_version4_explain = obj;
                            lv_obj_set_pos(obj, 3, 66);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Ceiling Light: Brightness;\nSide Light: Brightness;");
                        }
                    }
                }
                {
                    // btn_ui_version5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_ui_version5 = obj;
                    lv_obj_set_pos(obj, 30, 710);
                    lv_obj_set_size(obj, 420, 152);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)5);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00a2ff), LV_PART_MAIN | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // label_set_ui_version5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_set_ui_version5 = obj;
                            lv_obj_set_pos(obj, 3, 17);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Version 5");
                        }
                        {
                            // label_version5_explain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_version5_explain = obj;
                            lv_obj_set_pos(obj, 3, 66);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Ceiling Light: Brightness;\nSide Light: Brightness;");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.img_ui_select_warning = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, "1:/ui_in_waring.png");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_waring_in_title_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_waring_in_title_1 = obj;
                    lv_obj_set_pos(obj, 176, 214);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Notification");
                }
                {
                    // label_waring_in_explain_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_waring_in_explain_1 = obj;
                    lv_obj_set_pos(obj, 67, 285);
                    lv_obj_set_size(obj, 346, 252);
                    lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Non-professionals are prohibited from modifying this function.\nFor settings, please contact after-sales support.\nIncorrect configuration may cause device abnormalities.");
                }
                {
                    // btn_waring_in_canel_1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_waring_in_canel_1 = obj;
                    lv_obj_set_pos(obj, 49, 559);
                    lv_obj_set_size(obj, 189, 80);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)6);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj25 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffa3a3a3), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Canel");
                        }
                    }
                }
                {
                    // btn_waring_in_continue_1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.btn_waring_in_continue_1 = obj;
                    lv_obj_set_pos(obj, 242, 559);
                    lv_obj_set_size(obj, 189, 80);
                    lv_obj_add_event_cb(obj, action_ui_version_select_cb, LV_EVENT_CLICKED, (void *)7);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_harmony_os_sans_sc_regular_font_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Continue");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_set_ui();
}

void tick_screen_page_set_ui() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_page_home,
    tick_screen_page_funtion,
    tick_screen_page_light_ceiling_v1,
    tick_screen_page_light_side_v1,
    tick_screen_page_light_ceiling_v2,
    tick_screen_page_light_side_v2,
    tick_screen_page_light_ceiling_v3,
    tick_screen_page_light_ceiling_v4,
    tick_screen_page_light_ceiling_v5,
    tick_screen_page_light_ambient_v5,
    tick_screen_page_fan,
    tick_screen_page_timer_set,
    tick_screen_page_timer_run,
    tick_screen_page_set_time,
    tick_screen_page_set_language,
    tick_screen_page_set_sysinfo,
    tick_screen_page_keyboard,
    tick_screen_page_set,
    tick_screen_page_deft_light_v1,
    tick_screen_page_deft_light_v2,
    tick_screen_page_deft_light_v3,
    tick_screen_page_deft_light_v4,
    tick_screen_page_deft_light_v5,
    tick_screen_page_deft_light_lum_slider,
    tick_screen_page_deft_light_temp_slider,
    tick_screen_page_deft_fan_slider,
    tick_screen_page_deft_radar,
    tick_screen_page_deft_auto_vent,
    tick_screen_page_set_ui,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_page_home();
    create_screen_page_funtion();
    create_screen_page_light_ceiling_v1();
    create_screen_page_light_side_v1();
    create_screen_page_light_ceiling_v2();
    create_screen_page_light_side_v2();
    create_screen_page_light_ceiling_v3();
    create_screen_page_light_ceiling_v4();
    create_screen_page_light_ceiling_v5();
    create_screen_page_light_ambient_v5();
    create_screen_page_fan();
    create_screen_page_timer_set();
    create_screen_page_timer_run();
    create_screen_page_set_time();
    create_screen_page_set_language();
    create_screen_page_set_sysinfo();
    create_screen_page_keyboard();
    create_screen_page_set();
    create_screen_page_deft_light_v1();
    create_screen_page_deft_light_v2();
    create_screen_page_deft_light_v3();
    create_screen_page_deft_light_v4();
    create_screen_page_deft_light_v5();
    create_screen_page_deft_light_lum_slider();
    create_screen_page_deft_light_temp_slider();
    create_screen_page_deft_fan_slider();
    create_screen_page_deft_radar();
    create_screen_page_deft_auto_vent();
    create_screen_page_set_ui();
}
