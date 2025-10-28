#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *page_home;
    lv_obj_t *page_funtion;
    lv_obj_t *page_light_ceiling_v1;
    lv_obj_t *page_light_side_v1;
    lv_obj_t *page_light_ceiling_v2;
    lv_obj_t *page_light_side_v2;
    lv_obj_t *page_light_ceiling_v3;
    lv_obj_t *page_light_ceiling_v4;
    lv_obj_t *page_light_ceiling_v5;
    lv_obj_t *page_light_ambient_v5;
    lv_obj_t *page_fan;
    lv_obj_t *page_timer_set;
    lv_obj_t *page_timer_run;
    lv_obj_t *page_set_time;
    lv_obj_t *page_set_language;
    lv_obj_t *page_set_sysinfo;
    lv_obj_t *page_keyboard;
    lv_obj_t *page_set;
    lv_obj_t *page_deft_light_v1;
    lv_obj_t *page_deft_light_v2;
    lv_obj_t *page_deft_light_v3;
    lv_obj_t *page_deft_light_v4;
    lv_obj_t *page_deft_light_v5;
    lv_obj_t *page_deft_light_lum_slider;
    lv_obj_t *page_deft_light_temp_slider;
    lv_obj_t *page_deft_fan_slider;
    lv_obj_t *page_deft_radar;
    lv_obj_t *page_deft_auto_vent;
    lv_obj_t *page_set_ui;
    lv_obj_t *imgbtn_wifi_state;
    lv_obj_t *container_home_time;
    lv_obj_t *label_home_time;
    lv_obj_t *label_t_blink;
    lv_obj_t *container_home_timer;
    lv_obj_t *label_home_timer;
    lv_obj_t *label_home_timer_k;
    lv_obj_t *img_meeting;
    lv_obj_t *label_home_meeting;
    lv_obj_t *img_relax;
    lv_obj_t *label_home_relax;
    lv_obj_t *img_work;
    lv_obj_t *label_home_work;
    lv_obj_t *img_phone;
    lv_obj_t *label_home_phone;
    lv_obj_t *img_fun_light;
    lv_obj_t *label_fun_light;
    lv_obj_t *img_fun_fan;
    lv_obj_t *label_fun_fan;
    lv_obj_t *img_fun_timer;
    lv_obj_t *label_fun_timer;
    lv_obj_t *img_fun_time;
    lv_obj_t *label_fun_time;
    lv_obj_t *img_fun_wifi;
    lv_obj_t *label_fun_wifi;
    lv_obj_t *img_fun_languange;
    lv_obj_t *label_fun_language;
    lv_obj_t *img_fun_sys_inifo;
    lv_obj_t *label_fun_sys_info;
    lv_obj_t *img_fun_settings;
    lv_obj_t *label_fun_settings;
    lv_obj_t *label_title_light_ceiling_v1;
    lv_obj_t *img_ceiling_light_state_show_v1;
    lv_obj_t *slider_ceiling_light_lum_v1;
    lv_obj_t *label_light_ceiling_value_v1;
    lv_obj_t *imgbtn_light_ceiling_logo_onoff_v1;
    lv_obj_t *label_title_light_side_v1;
    lv_obj_t *img_side_light_state_show_v1;
    lv_obj_t *slider_side_light_lum_v1;
    lv_obj_t *label_light_side_value_v1;
    lv_obj_t *imgbtn_light_side_logo_onoff_v1;
    lv_obj_t *label_title_light_ceiling_v2;
    lv_obj_t *img_ceiling_light_state_show_v2;
    lv_obj_t *slider_ceiling_light_lum_v2;
    lv_obj_t *label_light_ceiling_value_v2;
    lv_obj_t *slider_ceiling_light_temp_v2;
    lv_obj_t *label_title_light_side_v2;
    lv_obj_t *img_side_light_state_show_v2;
    lv_obj_t *slider_side_light_lum_v2;
    lv_obj_t *label_light_side_value_v2;
    lv_obj_t *slider_side_light_temp_v2;
    lv_obj_t *label_title_light_ceiling_v3;
    lv_obj_t *img_ceiling_light_state_show_v3;
    lv_obj_t *slider_ceiling_light_lum_v3;
    lv_obj_t *label_light_ceiling_value_v3;
    lv_obj_t *slider_ceiling_light_temp_v3;
    lv_obj_t *label_title_light_ceiling_v4;
    lv_obj_t *img_ceiling_light_state_show_v4;
    lv_obj_t *slider_ceiling_light_lum_v4;
    lv_obj_t *label_light_ceiling_value_v4;
    lv_obj_t *imgbtn_light_ceiling_logo_onoff_v4;
    lv_obj_t *label_title_light_ceiling_v5;
    lv_obj_t *img_ceiling_light_state_show_v5;
    lv_obj_t *slider_ceiling_light_lum_v5;
    lv_obj_t *label_light_ceiling_value_v5;
    lv_obj_t *slider_ceiling_light_temp_v5;
    lv_obj_t *label_title_light_ambient_v5;
    lv_obj_t *colorwhel_select_show;
    lv_obj_t *label_title_fan;
    lv_obj_t *img_fan_speed_show;
    lv_obj_t *slider_fan;
    lv_obj_t *label_fan_value;
    lv_obj_t *imgbtn_fan_logo_onoff;
    lv_obj_t *label_title_timer;
    lv_obj_t *clock_set_hour;
    lv_obj_t *clock_set_minute;
    lv_obj_t *clock_set_second;
    lv_obj_t *clock_logo_h;
    lv_obj_t *clock_logo_m;
    lv_obj_t *clock_logo_s;
    lv_obj_t *imgbtn_timer_start;
    lv_obj_t *label_title_timer_1;
    lv_obj_t *imgbtn_timer_start_1;
    lv_obj_t *container_timer_remian;
    lv_obj_t *obj1;
    lv_obj_t *label_timer_remain;
    lv_obj_t *label_title_time;
    lv_obj_t *label_time_set_now;
    lv_obj_t *label_time_set_blink;
    lv_obj_t *label_time_set_title;
    lv_obj_t *label_time_set_time;
    lv_obj_t *label_time_set_now_1;
    lv_obj_t *label_time_set_blink_1;
    lv_obj_t *img_time_setting;
    lv_obj_t *time_set_window_title;
    lv_obj_t *roller_time_set_hour;
    lv_obj_t *label_window_set_time_h;
    lv_obj_t *roller_time_set_minute;
    lv_obj_t *label_window_set_time_m;
    lv_obj_t *label_window_set_time_canel;
    lv_obj_t *label_window_set_time_ok;
    lv_obj_t *label_title_language;
    lv_obj_t *btn_language_eng;
    lv_obj_t *btn_language_esp;
    lv_obj_t *btn_language_fra;
    lv_obj_t *btn_language_deu;
    lv_obj_t *btn_language_chn;
    lv_obj_t *btn_language_jpa;
    lv_obj_t *btn_language_kra;
    lv_obj_t *label_title_sysinfo;
    lv_obj_t *label_sysinfo_type;
    lv_obj_t *label_sysinfo_id;
    lv_obj_t *label_sysinfo_hardware;
    lv_obj_t *label_sysinfo_software;
    lv_obj_t *label_sysinfo_mac;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *label_keyboard_settings;
    lv_obj_t *label_key_input;
    lv_obj_t *label_key_input_err;
    lv_obj_t *key_input_status;
    lv_obj_t *container_keyboard;
    lv_obj_t *key_1;
    lv_obj_t *key_2;
    lv_obj_t *key_3;
    lv_obj_t *key_4;
    lv_obj_t *key_5;
    lv_obj_t *key_6;
    lv_obj_t *key_7;
    lv_obj_t *key_8;
    lv_obj_t *key_9;
    lv_obj_t *key_0;
    lv_obj_t *key_del;
    lv_obj_t *label_set_settings;
    lv_obj_t *obj9;
    lv_obj_t *label_dev_deft;
    lv_obj_t *obj10;
    lv_obj_t *label_ui_version;
    lv_obj_t *label_ui_version_nol;
    lv_obj_t *img_waring_in;
    lv_obj_t *label_waring_in_title;
    lv_obj_t *label_waring_in_explain;
    lv_obj_t *btn_waring_in_canel;
    lv_obj_t *obj11;
    lv_obj_t *btn_waring_in_continue;
    lv_obj_t *label_title_deft_1;
    lv_obj_t *label_deft_light_v1;
    lv_obj_t *label_deft_ceiling_light_v1;
    lv_obj_t *label_deft_side_light_v1;
    lv_obj_t *btn_deft_ceiling_light_lum_v1;
    lv_obj_t *label_deft_ceiling_light_lum_value_v1;
    lv_obj_t *btn_deft_side_light_lum_v1;
    lv_obj_t *label_deft_side_light_lum_value_v1;
    lv_obj_t *label_deft_fan_v1;
    lv_obj_t *btn_deft_fan_v1;
    lv_obj_t *label_deft_fan_value_v1;
    lv_obj_t *label_title_deft_2;
    lv_obj_t *container_ceiling;
    lv_obj_t *label_deft_ceiling_light_v2;
    lv_obj_t *label_deft_ceiling_light_brightness_v2;
    lv_obj_t *label_deft_ceiling_light_colortemp_v2;
    lv_obj_t *btn_deft_ceiling_light_lum_v2;
    lv_obj_t *label_deft_ceiling_light_lum_value_v2;
    lv_obj_t *btn_deft_ceiling_light_temp_v2;
    lv_obj_t *label_deft_ceiling_light_temp_value_v2;
    lv_obj_t *label_deft_side_light_v2;
    lv_obj_t *label_deft_side_light_brightness_v2;
    lv_obj_t *label_deft_side_light_colortemp_v2;
    lv_obj_t *btn_deft_side_light_lum_v2;
    lv_obj_t *label_deft_side_light_lum_value_v2;
    lv_obj_t *btn_deft_side_light_temp_v2;
    lv_obj_t *label_deft_side_light_temp_value_v2;
    lv_obj_t *label_deft_fan_v2;
    lv_obj_t *btn_deft_fan_v2;
    lv_obj_t *label_deft_fan_value_v2;
    lv_obj_t *label_title_deft_3;
    lv_obj_t *label_deft_light_v3;
    lv_obj_t *label_deft_ceiling_light_brightness_v3;
    lv_obj_t *label_deft_ceiling_light_colortemp_v3;
    lv_obj_t *btn_deft_ceiling_light_lum_v3;
    lv_obj_t *label_deft_ceiling_light_lum_value_v3;
    lv_obj_t *btn_deft_ceiling_light_temp_v3;
    lv_obj_t *label_deft_ceiling_light_temp_value_v3;
    lv_obj_t *label_deft_fan_v3;
    lv_obj_t *btn_deft_fan_v3;
    lv_obj_t *label_deft_fan_value_v3;
    lv_obj_t *label_title_deft_4;
    lv_obj_t *label_deft_light_v4;
    lv_obj_t *btn_deft_ceiling_light_lum_v4;
    lv_obj_t *label_deft_ceiling_light_lum_value_v4;
    lv_obj_t *label_deft_fan_v4;
    lv_obj_t *btn_deft_fan_v4;
    lv_obj_t *label_deft_fan_value_v4;
    lv_obj_t *label_title_deft_5;
    lv_obj_t *label_deft_light_v5;
    lv_obj_t *label_deft_ceiling_light_brightness_v5;
    lv_obj_t *label_deft_ceiling_light_colortemp_v5;
    lv_obj_t *btn_deft_ceiling_light_lum_v5;
    lv_obj_t *label_deft_ceiling_light_lum_value_v5;
    lv_obj_t *btn_deft_ceiling_light_temp_v5;
    lv_obj_t *label_deft_ceiling_light_temp_value_v5;
    lv_obj_t *labnel_deft_ambient_v5;
    lv_obj_t *btn_deft_ambient_v5;
    lv_obj_t *labnel_deft_fan_v5;
    lv_obj_t *btn_deft_fan_v5;
    lv_obj_t *label_deft_fan_value_v5;
    lv_obj_t *label_title_deft_6;
    lv_obj_t *obj12;
    lv_obj_t *label_deft_slider_lum_light_type;
    lv_obj_t *label_deft_slider_brightness;
    lv_obj_t *img_deft_slider_lum_confirm;
    lv_obj_t *slider_deft_light_lum;
    lv_obj_t *label_deft_light_lum_value;
    lv_obj_t *label_title_deft_7;
    lv_obj_t *obj13;
    lv_obj_t *label_deft_slider_temp_light_type;
    lv_obj_t *label_deft_slider_color_temp;
    lv_obj_t *img_deft_slider_temp_confirm;
    lv_obj_t *slider_ceiling_light_temp_3;
    lv_obj_t *label_title_deft_8;
    lv_obj_t *obj14;
    lv_obj_t *label_deft_slider_fan;
    lv_obj_t *img_deft_roller_fan;
    lv_obj_t *slider_deft_fan;
    lv_obj_t *label_deft_fan_value;
    lv_obj_t *label_title_deft_9;
    lv_obj_t *label_radar_mont;
    lv_obj_t *roller_set_radar;
    lv_obj_t *label_radar_m;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *label_title_deft_10;
    lv_obj_t *label_auto_vent;
    lv_obj_t *btn_deft_auto_onoff;
    lv_obj_t *container_auto_vent;
    lv_obj_t *label_interval;
    lv_obj_t *deft_roller_interval;
    lv_obj_t *label_auto_h;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *label_duration;
    lv_obj_t *deft_roller_duration;
    lv_obj_t *label_auto_m;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *label_set_ui_title;
    lv_obj_t *btn_ui_version1;
    lv_obj_t *label_set_ui_version1;
    lv_obj_t *label_version1_explain;
    lv_obj_t *btn_ui_version2;
    lv_obj_t *label_set_ui_version2;
    lv_obj_t *label_version2_explain;
    lv_obj_t *btn_ui_version3;
    lv_obj_t *label_set_ui_version3;
    lv_obj_t *label_version3_explain;
    lv_obj_t *btn_ui_version4;
    lv_obj_t *label_set_ui_version4;
    lv_obj_t *label_version4_explain;
    lv_obj_t *btn_ui_version5;
    lv_obj_t *label_set_ui_version5;
    lv_obj_t *label_version5_explain;
    lv_obj_t *img_ui_select_warning;
    lv_obj_t *label_waring_in_title_1;
    lv_obj_t *label_waring_in_explain_1;
    lv_obj_t *btn_waring_in_canel_1;
    lv_obj_t *obj25;
    lv_obj_t *btn_waring_in_continue_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_PAGE_HOME = 1,
    SCREEN_ID_PAGE_FUNTION = 2,
    SCREEN_ID_PAGE_LIGHT_CEILING_V1 = 3,
    SCREEN_ID_PAGE_LIGHT_SIDE_V1 = 4,
    SCREEN_ID_PAGE_LIGHT_CEILING_V2 = 5,
    SCREEN_ID_PAGE_LIGHT_SIDE_V2 = 6,
    SCREEN_ID_PAGE_LIGHT_CEILING_V3 = 7,
    SCREEN_ID_PAGE_LIGHT_CEILING_V4 = 8,
    SCREEN_ID_PAGE_LIGHT_CEILING_V5 = 9,
    SCREEN_ID_PAGE_LIGHT_AMBIENT_V5 = 10,
    SCREEN_ID_PAGE_FAN = 11,
    SCREEN_ID_PAGE_TIMER_SET = 12,
    SCREEN_ID_PAGE_TIMER_RUN = 13,
    SCREEN_ID_PAGE_SET_TIME = 14,
    SCREEN_ID_PAGE_SET_LANGUAGE = 15,
    SCREEN_ID_PAGE_SET_SYSINFO = 16,
    SCREEN_ID_PAGE_KEYBOARD = 17,
    SCREEN_ID_PAGE_SET = 18,
    SCREEN_ID_PAGE_DEFT_LIGHT_V1 = 19,
    SCREEN_ID_PAGE_DEFT_LIGHT_V2 = 20,
    SCREEN_ID_PAGE_DEFT_LIGHT_V3 = 21,
    SCREEN_ID_PAGE_DEFT_LIGHT_V4 = 22,
    SCREEN_ID_PAGE_DEFT_LIGHT_V5 = 23,
    SCREEN_ID_PAGE_DEFT_LIGHT_LUM_SLIDER = 24,
    SCREEN_ID_PAGE_DEFT_LIGHT_TEMP_SLIDER = 25,
    SCREEN_ID_PAGE_DEFT_FAN_SLIDER = 26,
    SCREEN_ID_PAGE_DEFT_RADAR = 27,
    SCREEN_ID_PAGE_DEFT_AUTO_VENT = 28,
    SCREEN_ID_PAGE_SET_UI = 29,
};

void create_screen_page_home();
void tick_screen_page_home();

void create_screen_page_funtion();
void tick_screen_page_funtion();

void create_screen_page_light_ceiling_v1();
void tick_screen_page_light_ceiling_v1();

void create_screen_page_light_side_v1();
void tick_screen_page_light_side_v1();

void create_screen_page_light_ceiling_v2();
void tick_screen_page_light_ceiling_v2();

void create_screen_page_light_side_v2();
void tick_screen_page_light_side_v2();

void create_screen_page_light_ceiling_v3();
void tick_screen_page_light_ceiling_v3();

void create_screen_page_light_ceiling_v4();
void tick_screen_page_light_ceiling_v4();

void create_screen_page_light_ceiling_v5();
void tick_screen_page_light_ceiling_v5();

void create_screen_page_light_ambient_v5();
void tick_screen_page_light_ambient_v5();

void create_screen_page_fan();
void tick_screen_page_fan();

void create_screen_page_timer_set();
void tick_screen_page_timer_set();

void create_screen_page_timer_run();
void tick_screen_page_timer_run();

void create_screen_page_set_time();
void tick_screen_page_set_time();

void create_screen_page_set_language();
void tick_screen_page_set_language();

void create_screen_page_set_sysinfo();
void tick_screen_page_set_sysinfo();

void create_screen_page_keyboard();
void tick_screen_page_keyboard();

void create_screen_page_set();
void tick_screen_page_set();

void create_screen_page_deft_light_v1();
void tick_screen_page_deft_light_v1();

void create_screen_page_deft_light_v2();
void tick_screen_page_deft_light_v2();

void create_screen_page_deft_light_v3();
void tick_screen_page_deft_light_v3();

void create_screen_page_deft_light_v4();
void tick_screen_page_deft_light_v4();

void create_screen_page_deft_light_v5();
void tick_screen_page_deft_light_v5();

void create_screen_page_deft_light_lum_slider();
void tick_screen_page_deft_light_lum_slider();

void create_screen_page_deft_light_temp_slider();
void tick_screen_page_deft_light_temp_slider();

void create_screen_page_deft_fan_slider();
void tick_screen_page_deft_fan_slider();

void create_screen_page_deft_radar();
void tick_screen_page_deft_radar();

void create_screen_page_deft_auto_vent();
void tick_screen_page_deft_auto_vent();

void create_screen_page_set_ui();
void tick_screen_page_set_ui();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/