// /*
//  * my_actions.c
//  *
//  *  Created on: 2024年7月22日
//  *      Author: TianPing Xu
//  */

#include "actions.h"
#include "screens.h"
#include "images.h"
#include "fonts.h"

#include "def.h"
#include "crc16.h"
#include "protocol.h"

#include "rtc_test.h"

uint32_t temp_show_idx = 0;
static const uint32_t color_temp_table[] = {
    0xFFFFF9FB, // 6500K
    0xFFFFF8F8, // 6400K
    0xFFFFF7F5, // 6300K
    0xFFFFF6F3, // 6200K
    0xFFFFF5F0, // 6100K
    0xFFFFF4ED, // 6000K
    0xFFFFF3EA, // 5900K
    0xFFFFF1E7, // 5800K
    0xFFFFF0E4, // 5700K
    0xFFFFEFE1, // 5600K
    0xFFFFEEDE, // 5500K
    0xFFFFEDDA, // 5400K
    0xFFFFEBD7, // 5300K
    0xFFFFEAD3, // 5200K
    0xFFFFE8D0, // 5100K
    0xFFFFE7CC, // 5000K
    0xFFFFE5C8, // 4900K
    0xFFFFE4C4, // 4800K
    0xFFFFE2C0, // 4700K
    0xFFFFE1BC, // 4600K
    0xFFFFDFB8, // 4500K
    0xFFFFDDB4, // 4400K
    0xFFFFDBAF, // 4300K
    0xFFFFD9AB, // 4200K
    0xFFFFD7A6, // 4100K
    0xFFFFD5A1, // 4000K
    0xFFFFD39C, // 3900K
    0xFFFFD097, // 3800K
    0xFFFFCE92, // 3700K
    0xFFFFCB8D, // 3600K
    0xFFFFC987, // 3500K
    0xFFFFC682, // 3400K
    0xFFFFC37C, // 3300K
    0xFFFFC076, // 3200K
    0xFFFFBD6F, // 3100K
    0xFFFFB969, // 3000K
    0xFFFFB662, // 2900K
    0xFFFFB25B, // 2800K
    0xFFFFA957, // 2700K
};

static void timer_date_handle_cb(lv_timer_t * timer);
static void timer_countdown_cb(lv_timer_t * timer);

static void page_language_refresh(uint8_t page);

uint8_t password[4];
uint8_t password_len = 0;

rtc_time_t time_h;
t_ctimes g_time;
t_ctimes s_time = {2025, 07, 11, 3, 8, 30, 30};
char label_time[20] = {0};

bool first_power_flag = 0;
uint8_t cnt_300ms_first = 0;

void action_init(void){
    hal_rtc_get_time(&time_h);
    get_time(&g_time, time_h);
    dev_def_attr.time_hour = g_time.hours;
    dev_def_attr.time_minute = g_time.minutes;
    dev_def_attr.time_second = g_time.seconds;
    dev_info.countdown_status = COUNTDOWN_NONE;

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    create_screen_page_home();
    sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
    lv_label_set_text(objects.label_home_time, label_time);
    page_language_refresh(SCREEN_ID_PAGE_HOME);
    lv_screen_load(objects.page_home);

    lv_timer_t * timer_1 = lv_timer_create(timer_date_handle_cb, 300, NULL); // 300ms周期
    lv_timer_t * timer_2 = lv_timer_create(timer_countdown_cb, 100, NULL); // 100ms周期

    dev_info.countdown_status = COUNTDOWN_NONE;
    printf("ui_version = %d\n", dev_def_attr.ui_version);
    printf("language_type = %d\n", dev_def_attr.language_type);
}

/****************************************************************  lvgl timer ********************************************************************/
bool save_flag = 0, light_in_flag = 0, end_flag = 0;
uint8_t cnt_300ms_1 = 0, cnt_300ms_2 = 0, cnt_300ms_3 = 0;
static void timer_date_handle_cb(lv_timer_t * timer) {
    tx_data_hadle();
    rx_data_hadle();

    if(save_flag) {
        cnt_300ms_1++;
        if(cnt_300ms_1 > 30) {
            save_flag = 0;
            cnt_300ms_1 = 0;
            XY_Write();
        }
    }

    if(!first_power_flag) {
        cnt_300ms_first++;
        if(cnt_300ms_first > 3) {
            cnt_300ms_first = 0;
            first_power_flag = 1;
            if(!dev_def_attr.dev_rodar_time) {
                rodar_buff_generate(30);
            }else {
                rodar_buff_generate(dev_def_attr.dev_rodar_time * 60);
            }
        }
    }
}

bool blink = 0, blink_countdown = 0;
char label_countdown_time[20] = {0};
uint8_t cnt_100ms_blink = 0;
static void timer_countdown_cb(lv_timer_t * timer) {
    hal_rtc_get_time(&time_h);      // 获取芯片RTC时间
    get_time(&g_time, time_h);      // 获取时间戳

    if(dev_def_attr.time_second != (uint8_t)g_time.seconds) {
        dev_def_attr.time_second = (uint8_t)g_time.seconds;
        blink = !blink;
        if(lv_obj_is_valid(objects.label_home_time) && lv_obj_is_valid(objects.label_t_blink)) {
            if(blink)
                lv_obj_add_flag(objects.label_t_blink, LV_OBJ_FLAG_HIDDEN);
            else
                lv_obj_remove_flag(objects.label_t_blink, LV_OBJ_FLAG_HIDDEN);
        }else if(lv_obj_is_valid(objects.label_time_set_now) && lv_obj_is_valid(objects.label_time_set_blink)) {
            if(blink) {
                lv_obj_add_flag(objects.label_time_set_blink, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.label_time_set_blink_1, LV_OBJ_FLAG_HIDDEN);
            }else {
                lv_obj_remove_flag(objects.label_time_set_blink, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(objects.label_time_set_blink_1, LV_OBJ_FLAG_HIDDEN);
            }
        }

        // timer
        if(dev_info.countdown_status == COUNTDOWN_RUN) {
            if(dev_info.countdown_hour || dev_info.countdown_minute || dev_info.countdown_second) {
                if(dev_info.countdown_second == 0) {
                    if(dev_info.countdown_minute > 0) {
                        dev_info.countdown_minute--;
                        dev_info.countdown_second = 59;
                    }else {
                        if(dev_info.countdown_hour > 0) {
                            dev_info.countdown_hour--;
                            dev_info.countdown_minute = 59;
                            dev_info.countdown_second = 59;
                        }else {
                            dev_info.countdown_status = COUNTDOWN_NONE;
                        }
                    }
                }else {
                    dev_info.countdown_second--;
                }
                if(lv_obj_is_valid(objects.container_home_timer) && lv_obj_is_valid(objects.label_home_timer)) {
                    sprintf(label_countdown_time, "%02d %02d %02d", dev_info.countdown_hour, dev_info.countdown_minute, dev_info.countdown_second);
                    lv_label_set_text(objects.label_home_timer, label_countdown_time);
                }else if(lv_obj_is_valid(objects.container_timer_remian) && lv_obj_is_valid(objects.label_timer_remain)) {
                    sprintf(label_countdown_time, "%02d %02d %02d", dev_info.countdown_hour, dev_info.countdown_minute, dev_info.countdown_second);
                    lv_label_set_text(objects.label_timer_remain, label_countdown_time);
                }else{
                }
            }else {
                dev_info.countdown_hour = 0;
                dev_info.countdown_minute = 0;
                dev_info.countdown_second = 0;
                dev_info.countdown_status = COUNTDOWN_NONE;
                if(lv_obj_is_valid(objects.container_home_timer) && lv_obj_is_valid(objects.label_home_timer)) {
                    lv_label_set_text(objects.label_home_timer, "00 00 00");
                    lv_obj_add_flag(objects.container_home_timer, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_remove_flag(objects.container_home_time, LV_OBJ_FLAG_HIDDEN);
                }else if(lv_obj_is_valid(objects.container_timer_remian) && lv_obj_is_valid(objects.label_timer_remain)) {
                    lv_label_set_text(objects.label_timer_remain, "00 00 00");
                    lv_obj_t* now_screen_obj = lv_scr_act();
                    lv_obj_clean(now_screen_obj);
                    create_screen_page_timer_set();
                    dev_info.countdown_hour_set = 0;
                    dev_info.countdown_minute_set = 0;
                    dev_info.countdown_second_set = 0;
                    page_language_refresh(SCREEN_ID_PAGE_TIMER_SET);
                    lv_screen_load(objects.page_timer_set);
                    lv_obj_delete(now_screen_obj);
                }
            }
        }
    }
    // 时间刷新
    if(dev_def_attr.time_minute != (uint8_t)g_time.minutes) {
        dev_def_attr.time_hour = (uint8_t)g_time.hours;
        dev_def_attr.time_minute = (uint8_t)g_time.minutes;
        sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
        if(lv_obj_is_valid(objects.label_home_time)) {
            lv_label_set_text(objects.label_home_time, label_time);
        }else if(lv_obj_is_valid(objects.label_time_set_now) && lv_obj_is_valid(objects.label_time_set_blink)) {
            lv_label_set_text(objects.label_time_set_now, label_time);
            lv_label_set_text(objects.label_time_set_now_1, label_time);
        }
        
    }

    // 倒计时
    if(dev_info.countdown_status == COUNTDOWN_RUN) {
        if(!dev_info.countdown_hour && !dev_info.countdown_minute && dev_info.countdown_second <= 30) {
            cnt_100ms_blink++;
            if(cnt_100ms_blink >= 5) {
                cnt_100ms_blink = 0;
                blink_countdown = !blink_countdown;
                if(blink_countdown) {
                    if(lv_obj_is_valid(objects.container_home_timer) && lv_obj_is_valid(objects.label_home_timer)) {
                        lv_obj_add_flag(objects.container_home_timer, LV_OBJ_FLAG_HIDDEN);
                    }else if(lv_obj_is_valid(objects.container_timer_remian) && lv_obj_is_valid(objects.label_timer_remain)) {
                        lv_obj_add_flag(objects.container_timer_remian, LV_OBJ_FLAG_HIDDEN);
                    }
                }else {
                    if(lv_obj_is_valid(objects.container_home_timer) && lv_obj_is_valid(objects.label_home_timer)) {
                        lv_obj_remove_flag(objects.container_home_timer, LV_OBJ_FLAG_HIDDEN);
                    }else if(lv_obj_is_valid(objects.container_timer_remian) && lv_obj_is_valid(objects.label_timer_remain)) {
                        lv_obj_remove_flag(objects.container_timer_remian, LV_OBJ_FLAG_HIDDEN);
                    }
                }
            }
        }
    }
}


const char * fan_img_files[25] = {
    "1:/fan_speed_show_01.png",
    "1:/fan_speed_show_06.png",
    "1:/fan_speed_show_11.png",
    "1:/fan_speed_show_16.png",
    "1:/fan_speed_show_21.png",
    "1:/fan_speed_show_26.png",
    "1:/fan_speed_show_31.png",
    "1:/fan_speed_show_36.png",
    "1:/fan_speed_show_41.png",
    "1:/fan_speed_show_46.png",
    "1:/fan_speed_show_51.png",
    "1:/fan_speed_show_56.png",
    "1:/fan_speed_show_61.png",
    "1:/fan_speed_show_66.png",
    "1:/fan_speed_show_71.png",
    "1:/fan_speed_show_76.png",
    "1:/fan_speed_show_81.png",
    "1:/fan_speed_show_86.png",
    "1:/fan_speed_show_91.png",
    "1:/fan_speed_show_96.png",
    "1:/fan_speed_show_101.png",
    "1:/fan_speed_show_106.png",
    "1:/fan_speed_show_111.png",
    "1:/fan_speed_show_116.png",
    "1:/fan_speed_show_121.png",
};

lv_timer_t *timer_fan;
static void page_fan_del_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_DELETE) {
        if(timer_fan) {
            lv_timer_del(timer_fan);
            timer_fan = NULL;
        }
    }
}

static void fan_speed_pic_cb(lv_timer_t * timer)
{
    static int cnt_1 = 0;
    if(lv_obj_is_valid(objects.label_title_fan) && lv_obj_is_valid(objects.img_fan_speed_show) && dev_info.fan_speed) {
        const char * path_1 = fan_img_files[cnt_1++ % 25];
        lv_img_set_src(objects.img_fan_speed_show, path_1);   // 直接换图
    }else {
    }
}
/**************************************************************** handle_fun ******************************************************************/
void light_in_handle(bool info_send) {
    lv_obj_t* now_screen_obj = lv_scr_act();
    lv_obj_t* parent;
    lv_obj_clean(now_screen_obj);
    switch(dev_def_attr.ui_version) {
    case UI_VERSION_1:
        create_screen_page_light_ceiling_v1();
        parent = objects.page_light_ceiling_v1;
        page_language_refresh(SCREEN_ID_PAGE_LIGHT_CEILING_V1);
        lv_slider_set_value(objects.slider_ceiling_light_lum_v1, dev_info.m_light_lum, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v1, "%d", dev_info.m_light_lum);
        if(dev_info.m_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v1, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
        else lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v1, LV_IMAGEBUTTON_STATE_RELEASED);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);

        if(info_send) {
            buff_generate(FAN_SPEED, dev_info.fan_speed);
            buff_generate(M_LIGHT_LUM, dev_info.m_light_lum);
            buff_generate(S_LIGHT_LUM, dev_info.s_light_lum);
        }
        break;
    case UI_VERSION_2:
        create_screen_page_light_ceiling_v2();
        parent = objects.page_light_ceiling_v2;
        page_language_refresh(SCREEN_ID_PAGE_LIGHT_CEILING_V2);
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v2, "%d", dev_info.s_light_lum);
        lv_slider_set_value(objects.slider_ceiling_light_lum_v2, dev_info.s_light_lum, LV_ANIM_OFF);
        lv_slider_set_value(objects.slider_ceiling_light_temp_v2, dev_info.s_light_temp, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);

        if(info_send) {
            buff_generate(FAN_SPEED, dev_info.fan_speed);
            buff_generate(M_LIGHT_TEMP, dev_info.m_light_temp);
            buff_generate(M_LIGHT_LUM, dev_info.m_light_lum);
            buff_generate(S_LIGHT_TEMP, dev_info.s_light_temp);
            buff_generate(S_LIGHT_LUM, dev_info.s_light_lum);
        }
        break;
    case UI_VERSION_3:
        create_screen_page_light_ceiling_v3();
        parent = objects.page_light_ceiling_v3;
        page_language_refresh(SCREEN_ID_PAGE_LIGHT_CEILING_V3);
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v3, "%d", dev_info.s_light_lum);
        lv_slider_set_value(objects.slider_ceiling_light_lum_v3, dev_info.s_light_lum, LV_ANIM_OFF);
        lv_slider_set_value(objects.slider_ceiling_light_temp_v3, dev_info.s_light_temp, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);

        if(info_send) {
            buff_generate(FAN_SPEED, dev_info.fan_speed);
            buff_generate(M_LIGHT_TEMP, dev_info.m_light_temp);
            buff_generate(M_LIGHT_LUM, dev_info.m_light_lum);
        }
        break;
    case UI_VERSION_4:
        create_screen_page_light_ceiling_v4();
        parent = objects.page_light_ceiling_v4;
        page_language_refresh(SCREEN_ID_PAGE_LIGHT_CEILING_V4);
        lv_slider_set_value(objects.slider_ceiling_light_lum_v4, dev_info.m_light_lum, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v4, "%d", dev_info.m_light_lum);
        if(dev_info.m_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v4, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
        else lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v4, LV_IMAGEBUTTON_STATE_RELEASED);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);

        if(info_send) {
            buff_generate(FAN_SPEED, dev_info.fan_speed);
            buff_generate(M_LIGHT_LUM, dev_info.m_light_lum);
        }
        break;
    case UI_VERSION_5:
        create_screen_page_light_ceiling_v5();
        parent = objects.page_light_ceiling_v5;
        page_language_refresh(SCREEN_ID_PAGE_LIGHT_CEILING_V5);
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v5, "%d", dev_info.s_light_lum);
        lv_slider_set_value(objects.slider_ceiling_light_lum_v5, dev_info.s_light_lum, LV_ANIM_OFF);
        lv_slider_set_value(objects.slider_ceiling_light_temp_v5, dev_info.s_light_temp, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);

        if(info_send) {
            buff_generate(FAN_SPEED, dev_info.fan_speed);
            buff_generate(M_LIGHT_TEMP, dev_info.m_light_temp);
            buff_generate(M_LIGHT_LUM, dev_info.m_light_lum);
            buff_generate(ATMOSPHERE_COLOR, dev_info.s_light_lum);
        }
        break;
    default:
        break;
    }
    dev_info.light_select = CEILING_LIGHT;
}

/**************************************************************** action_cb ******************************************************************/
void action_gesture_handle_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_GESTURE) {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        uint32_t buf = (uint32_t)lv_event_get_user_data(e);
        lv_obj_t* now_screen_obj = lv_scr_act();
        lv_obj_t* parent;
        if(dir == LV_DIR_LEFT) {
            if(buf == 1) {
                lv_obj_clean(now_screen_obj);
                create_screen_page_funtion();
                parent = objects.page_funtion;
                page_language_refresh(SCREEN_ID_PAGE_FUNTION);
                lv_screen_load(parent);
                lv_obj_delete(now_screen_obj);
            }
        }else if(dir == LV_DIR_RIGHT) {
            lv_obj_clean(now_screen_obj);
            create_screen_page_home();
            parent = objects.page_home;
            if(dev_info.sence_mode_meet_onoff) {
                lv_image_set_src(objects.img_meeting, "1:/meeting_on.png");
            }else if(dev_info.sence_mode_relax_onoff) {
                lv_image_set_src(objects.img_relax, "1:/relax_on.png");
            }else if(dev_info.sence_mode_work_onoff) {
                lv_image_set_src(objects.img_work, "1:/work_on.png");
            }else if(dev_info.sence_mode_phone_onoff) {
                lv_image_set_src(objects.img_phone, "1:/phone_on.png");
            }
            page_language_refresh(SCREEN_ID_PAGE_HOME);
            if(dev_info.countdown_status == COUNTDOWN_RUN || dev_info.countdown_status == COUNTDOWN_STOP) {
                lv_obj_add_flag(objects.container_home_time, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(objects.container_home_timer, LV_OBJ_FLAG_HIDDEN);
                sprintf(label_time, "%02d %02d %02d", dev_info.countdown_hour, dev_info.countdown_minute, dev_info.countdown_second);
                lv_label_set_text(objects.label_home_timer, label_time);
            }else {
                sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
                lv_label_set_text(objects.label_home_time, label_time);
            }
            lv_screen_load(parent);
            lv_obj_delete(now_screen_obj);
        }
    }
}

void action_mode_select_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    switch(buf) {
    case 1:
        dev_info.fan_speed = 100;
        dev_info.m_light_lum = 100;
        dev_info.m_light_temp = 40;
        dev_info.sence_mode_meet_onoff = 1;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        break;
    case 2:
        dev_info.fan_speed = 60;
        dev_info.m_light_lum = 50;
        dev_info.m_light_temp = 90;
        dev_info.sence_mode_relax_onoff = 1;
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    case 3:
        dev_info.fan_speed = 75;
        dev_info.m_light_lum = 70;
        dev_info.m_light_temp = 40;
        dev_info.sence_mode_work_onoff = 1;
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        break;
    case 4:
        dev_info.fan_speed = 75;
        dev_info.m_light_lum = 30;
        dev_info.m_light_temp = 65;
        dev_info.sence_mode_phone_onoff = 1;
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    }
    dev_info.mode_in_flag = 1;
    light_in_handle(1);
}

void action_goto_new_screen(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t* now_screen_obj = lv_scr_act();
    lv_obj_t* parent;
    switch(buf) {
    case 1: 
        light_in_handle(0);
        break;
    case 2: 
        lv_obj_clean(now_screen_obj);
        create_screen_page_fan();
        parent = objects.page_fan;
        // 控件状态刷新
        if(dev_info.fan_speed) {
            lv_imagebutton_set_state(objects.imgbtn_fan_logo_onoff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
        }else {
            lv_imagebutton_set_state(objects.imgbtn_fan_logo_onoff, LV_IMAGEBUTTON_STATE_RELEASED);
        }
        lv_slider_set_value(objects.slider_fan, dev_info.fan_speed, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.label_fan_value, "%d", dev_info.fan_speed);
        page_language_refresh(SCREEN_ID_PAGE_FAN);
        // 添加事件监听删除
        lv_obj_add_event_cb(parent, page_fan_del_event_cb, LV_EVENT_DELETE, NULL);
        // 创建一个定时器
        timer_fan = lv_timer_create(fan_speed_pic_cb, 550 - dev_info.fan_speed * 5, NULL);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 3:
        lv_obj_clean(now_screen_obj);
        if(dev_info.countdown_status == COUNTDOWN_NONE) {
            create_screen_page_timer_set();
            parent = objects.page_timer_set;
            dev_info.countdown_hour_set = 0;
            dev_info.countdown_minute_set = 0;
            dev_info.countdown_second_set = 0;
            page_language_refresh(SCREEN_ID_PAGE_TIMER_SET);
        }else if(dev_info.countdown_status == COUNTDOWN_RUN || dev_info.countdown_status == COUNTDOWN_STOP) {
            create_screen_page_timer_run();
            parent = objects.page_timer_run;
            if(dev_info.countdown_status == COUNTDOWN_STOP) lv_imagebutton_set_state(objects.imgbtn_timer_start_1, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
            sprintf(label_time, "%02d %02d %02d", dev_info.countdown_hour, dev_info.countdown_minute, dev_info.countdown_second);
            lv_label_set_text(objects.label_timer_remain, label_time);
            page_language_refresh(SCREEN_ID_PAGE_TIMER_RUN);
        }
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 4:
        lv_obj_clean(now_screen_obj);
        create_screen_page_set_time();
        parent = objects.page_set_time;
        sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
        lv_label_set_text(objects.label_time_set_now, label_time);
        sprintf(label_time, "%02d:%02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
        lv_label_set_text(objects.label_time_set_now_1, label_time);
        page_language_refresh(SCREEN_ID_PAGE_SET_TIME);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 5:
        // wifi
        break;
    case 6:
        lv_obj_clean(now_screen_obj);
        create_screen_page_set_language();
        parent = objects.page_set_language;
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_language, "Language");
            lv_obj_add_state(objects.btn_language_eng, LV_STATE_CHECKED);
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_language, "Idioma");
            lv_obj_add_state(objects.btn_language_esp, LV_STATE_CHECKED);
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_language, "Langue");
            lv_obj_add_state(objects.btn_language_fra, LV_STATE_CHECKED);
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_language, "Sprache");
            lv_obj_add_state(objects.btn_language_deu, LV_STATE_CHECKED);
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_language, "语言");
            lv_obj_add_state(objects.btn_language_chn, LV_STATE_CHECKED);
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_language, "言語");
            lv_obj_add_state(objects.btn_language_jpa, LV_STATE_CHECKED);
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_language, "언어");
            lv_obj_add_state(objects.btn_language_kra, LV_STATE_CHECKED);
            break;
        default:
            break;
        }
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 7:
        lv_obj_clean(now_screen_obj);
        create_screen_page_set_sysinfo();
        page_language_refresh(SCREEN_ID_PAGE_SET_SYSINFO);
        parent = objects.page_set_sysinfo;
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 8:
        lv_obj_clean(now_screen_obj);
        create_screen_page_keyboard();
        page_language_refresh(SCREEN_ID_PAGE_KEYBOARD);
        parent = objects.page_keyboard;
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 9:
        lv_obj_clean(now_screen_obj);
        if(dev_info.mode_in_flag) {
            dev_info.mode_in_flag = 0;
            create_screen_page_home();
            parent = objects.page_home;
            if(dev_info.sence_mode_meet_onoff) {
                lv_image_set_src(objects.img_meeting, "1:/meeting_on.png");
            }else if(dev_info.sence_mode_relax_onoff) {
                lv_image_set_src(objects.img_relax, "1:/relax_on.png");
            }else if(dev_info.sence_mode_work_onoff) {
                lv_image_set_src(objects.img_work, "1:/work_on.png");
            }else if(dev_info.sence_mode_phone_onoff) {
                lv_image_set_src(objects.img_phone, "1:/phone_on.png");
            }
            page_language_refresh(SCREEN_ID_PAGE_HOME);
            if(dev_info.countdown_status == COUNTDOWN_RUN || dev_info.countdown_status == COUNTDOWN_STOP) {
                lv_obj_add_flag(objects.container_home_time, LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(objects.container_home_timer, LV_OBJ_FLAG_HIDDEN);
                sprintf(label_time, "%02d %02d %02d", dev_info.countdown_hour, dev_info.countdown_minute, dev_info.countdown_second);
                lv_label_set_text(objects.label_home_timer, label_time);
            }else {
                sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
                lv_label_set_text(objects.label_home_time, label_time);
            }
        }else {
            create_screen_page_funtion();
            parent = objects.page_funtion;
            page_language_refresh(SCREEN_ID_PAGE_FUNTION);
        }
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 10:
        lv_obj_clean(now_screen_obj);
        create_screen_page_funtion();
        parent = objects.page_funtion;
        page_language_refresh(SCREEN_ID_PAGE_FUNTION);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 11:
        // null
        break;
    case 12:
        lv_obj_remove_flag(objects.img_waring_in, LV_OBJ_FLAG_HIDDEN);
        break;
    case 13:
        lv_obj_add_flag(objects.img_waring_in, LV_OBJ_FLAG_HIDDEN);
        break;  
    case 14:
        lv_obj_clean(now_screen_obj);
        create_screen_page_set_ui();
        parent = objects.page_set_ui;
        switch(dev_def_attr.ui_version) {
        case UI_VERSION_1:
            lv_obj_add_state(objects.btn_ui_version1, LV_STATE_CHECKED);
            break;
        case UI_VERSION_2:
            lv_obj_add_state(objects.btn_ui_version2, LV_STATE_CHECKED);
            break;
        case UI_VERSION_3:
            lv_obj_add_state(objects.btn_ui_version3, LV_STATE_CHECKED);
            break;
        case UI_VERSION_4:
            lv_obj_add_state(objects.btn_ui_version4, LV_STATE_CHECKED);
            break;
        case UI_VERSION_5:
            lv_obj_add_state(objects.btn_ui_version5, LV_STATE_CHECKED);
            break;
        }
        page_language_refresh(SCREEN_ID_PAGE_SET_UI);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 15:
        lv_obj_clean(now_screen_obj);
        create_screen_page_set();
        parent = objects.page_set;
        page_language_refresh(SCREEN_ID_PAGE_SET);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 21:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_light_lum_slider();
        parent = objects.page_deft_light_lum_slider;
        dev_def_attr.default_light_select = CEILING_LIGHT;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_LUM_SLIDER);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 22:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_light_lum_slider();
        parent = objects.page_deft_light_lum_slider;
        dev_def_attr.default_light_select = CEILING_LIGHT;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_LUM_SLIDER);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 23:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_light_temp_slider();
        parent = objects.page_deft_light_temp_slider;
        dev_def_attr.default_light_select = SIDE_LIGHT;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_TEMP_SLIDER);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 24:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_light_temp_slider();
        parent = objects.page_deft_light_temp_slider;
        dev_def_attr.default_light_select = SIDE_LIGHT;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_TEMP_SLIDER);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 25:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_fan_slider();
        parent = objects.page_deft_fan_slider;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_FAN_SLIDER);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    }
}

void action_dev_deft_select_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t* now_screen_obj = lv_scr_act();
    lv_obj_t* parent;
    switch(buf) {
    case 1: 
        lv_obj_clean(now_screen_obj);
        switch(dev_def_attr.ui_version) {
        case UI_VERSION_1:
            create_screen_page_deft_light_v1();
            parent = objects.page_deft_light_v1;
            page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_V1);
            // 刷新控件状态
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_lum_value_v1, "%d%%", dev_def_attr.default_m_light_lum);
            lv_label_set_text_fmt(objects.label_deft_side_light_lum_value_v1, "%d%%", dev_def_attr.default_s_light_lum);
            lv_label_set_text_fmt(objects.label_deft_fan_value_v1, "%d%%", dev_def_attr.default_fan_speed);
            break;
        case UI_VERSION_2:
            create_screen_page_deft_light_v2();
            parent = objects.page_deft_light_v2;
            page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_V2);
            // 刷新控件状态
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_lum_value_v2, "%d%%", dev_def_attr.default_m_light_lum);
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_temp_value_v2, "%d%%", dev_def_attr.default_m_light_temp);
            lv_label_set_text_fmt(objects.label_deft_side_light_lum_value_v2, "%d%%", dev_def_attr.default_s_light_lum);
            lv_label_set_text_fmt(objects.label_deft_side_light_temp_value_v2, "%d%%", dev_def_attr.default_s_light_temp);
            lv_label_set_text_fmt(objects.label_deft_fan_value_v2, "%d%%", dev_def_attr.default_fan_speed);
            break;
        case UI_VERSION_3:
            create_screen_page_deft_light_v3();
            parent = objects.page_deft_light_v3;
            page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_V3);
            // 刷新控件状态
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_lum_value_v3, "%d%%", dev_def_attr.default_m_light_lum);
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_temp_value_v3, "%d%%", dev_def_attr.default_m_light_temp);
            lv_label_set_text_fmt(objects.label_deft_fan_value_v3, "%d%%", dev_def_attr.default_fan_speed);
            break;
        case UI_VERSION_4:
            create_screen_page_deft_light_v4();
            parent = objects.page_deft_light_v4;
            page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_V4);
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_lum_value_v4, "%d%%", dev_def_attr.default_m_light_lum);
            lv_label_set_text_fmt(objects.label_deft_fan_value_v4, "%d%%", dev_def_attr.default_fan_speed);
            // 刷新控件状态
            break;
        case UI_VERSION_5:
            create_screen_page_deft_light_v5();
            parent = objects.page_deft_light_v5;
            page_language_refresh(SCREEN_ID_PAGE_DEFT_LIGHT_V5);
            // 刷新控件状态
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_lum_value_v5, "%d%%", dev_def_attr.default_m_light_lum);
            lv_label_set_text_fmt(objects.label_deft_ceiling_light_temp_value_v5, "%d%%", dev_def_attr.default_m_light_temp);
            lv_label_set_text_fmt(objects.label_deft_fan_value_v5, "%d%%", dev_def_attr.default_fan_speed);
            break;
        default:
            break;
        }
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 2:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_radar();
        parent = objects.page_deft_radar;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_RADAR);
        lv_roller_set_selected(objects.roller_set_radar, dev_def_attr.dev_rodar_time, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 3:
        lv_obj_clean(now_screen_obj);
        create_screen_page_deft_auto_vent();
        parent = objects.page_deft_auto_vent;
        page_language_refresh(SCREEN_ID_PAGE_DEFT_AUTO_VENT);
        if(dev_def_attr.Auto_vent_onoff) {
            lv_image_set_src(objects.btn_deft_auto_onoff, "1:/btn_on.png");
            lv_obj_remove_flag(objects.container_auto_vent, LV_OBJ_FLAG_HIDDEN);
        }
        lv_roller_set_selected(objects.deft_roller_interval, dev_def_attr.Interval_time, LV_ANIM_OFF);
        lv_roller_set_selected(objects.deft_roller_duration, dev_def_attr.Duration_time, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    default:
        break;
    }
}

void action_slider_change_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    switch(buf) {
    case 1:
        dev_info.m_light_lum = value;
        switch(dev_def_attr.ui_version) {
        case UI_VERSION_1:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v1, dev_info.m_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_ceiling_value_v1, "%d", dev_info.m_light_lum);
            if(dev_info.m_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v1, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
            else lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v1, LV_IMAGEBUTTON_STATE_RELEASED);
            break;
        case UI_VERSION_2:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v2, dev_info.m_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_ceiling_value_v2, "%d", dev_info.m_light_lum);
            break;
        case UI_VERSION_3:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v3, dev_info.m_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_ceiling_value_v3, "%d", dev_info.m_light_lum);
            break;
        case UI_VERSION_4:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v4, dev_info.m_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_ceiling_value_v4, "%d", dev_info.m_light_lum);
            if(dev_info.m_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v4, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
            else lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v4, LV_IMAGEBUTTON_STATE_RELEASED);
            break;
        case UI_VERSION_5:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v5, dev_info.m_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_ceiling_value_v5, "%d", dev_info.m_light_lum);
            break;
        }
        dev_info.m_light_lum_change_flag = 1;
        // mode --- off
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    case 2:
        dev_info.s_light_lum = value;
        switch(dev_def_attr.ui_version) {
        case UI_VERSION_1:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v1, dev_info.s_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_side_value_v1, "%d", dev_info.s_light_lum);
            if(dev_info.s_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_side_logo_onoff_v1, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
            else lv_imagebutton_set_state(objects.imgbtn_light_side_logo_onoff_v1, LV_IMAGEBUTTON_STATE_RELEASED);
            break;
        case UI_VERSION_2:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v2, dev_info.s_light_lum * 255 / 100, 0);
            lv_label_set_text_fmt(objects.label_light_side_value_v2, "%d", dev_info.s_light_lum);
            break;
        case UI_VERSION_3:
        case UI_VERSION_4:
            break;
        case UI_VERSION_5:
            lv_obj_set_style_image_opa(objects.img_ceiling_light_state_show_v5, dev_info.s_light_lum * 255 / 100, 0);
            break;
        }

        dev_info.s_light_lum_change_flag = 1;
        // mode --- off
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    case 3:
        dev_info.m_light_temp = value;
        switch(dev_def_attr.ui_version) {
        case UI_VERSION_1: break;
        case UI_VERSION_2:
            temp_show_idx = dev_info.m_light_temp * 38 / 100;
            lv_obj_set_style_image_recolor(objects.img_ceiling_light_state_show_v2, lv_color_hex(color_temp_table[temp_show_idx]), 0);
            break;
        case UI_VERSION_3:
            temp_show_idx = dev_info.m_light_temp * 38 / 100;
            lv_obj_set_style_image_recolor(objects.img_ceiling_light_state_show_v3, lv_color_hex(color_temp_table[temp_show_idx]), 0);
            break;
        case UI_VERSION_4:
            break;
        case UI_VERSION_5:
            temp_show_idx = dev_info.m_light_temp * 38 / 100;
            lv_obj_set_style_image_recolor(objects.img_ceiling_light_state_show_v5, lv_color_hex(color_temp_table[temp_show_idx]), 0);
            break;
        }

        dev_info.m_light_temp_change_flag = 1;
        // mode --- off
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    case 4:
        dev_info.s_light_temp = value;
        if(dev_def_attr.ui_version == UI_VERSION_2) {
            temp_show_idx = dev_info.s_light_temp * 38 / 100;
            lv_obj_set_style_image_recolor(objects.img_side_light_state_show_v2, lv_color_hex(color_temp_table[temp_show_idx]), 0);
        }

        dev_info.s_light_temp_change_flag = 1;
        // mode --- off
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    case 5:
        dev_info.fan_speed = value;
        lv_label_set_text_fmt(objects.label_fan_value, "%d", value);
        if(dev_info.fan_speed){
            lv_imagebutton_set_state(objects.imgbtn_fan_logo_onoff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
        }else {
            lv_imagebutton_set_state(objects.imgbtn_fan_logo_onoff, LV_IMAGEBUTTON_STATE_RELEASED);
        }
        lv_timer_set_period(timer_fan, 550 - dev_info.fan_speed * 5);

        dev_info.fan_speed_change_flag = 1;
        // mode --- off
        dev_info.sence_mode_meet_onoff = 0;
        dev_info.sence_mode_phone_onoff = 0;
        dev_info.sence_mode_relax_onoff = 0;
        dev_info.sence_mode_work_onoff = 0;
        break;
    case 11: 
        dev_def_attr.default_m_light_lum = value;
        lv_label_set_text_fmt(objects.label_deft_light_lum_value, "%d", value);
        if(dev_def_attr.default_light_select == CEILING_LIGHT) {
            dev_def_attr.default_m_light_lum = value;
        }else {
            dev_def_attr.default_s_light_lum = value;
        }
        save_flag = 1;
        break;
    case 12:
        if(dev_def_attr.default_light_select == CEILING_LIGHT) {
            dev_def_attr.default_m_light_temp = value;
        }else {
            dev_def_attr.default_s_light_temp = value;
        }
        save_flag = 1;
        break;
    case 13:
        dev_def_attr.default_fan_speed = value;
        lv_label_set_text_fmt(objects.label_deft_fan_value, "%d", value);
        save_flag = 1;
        break;
    default :
        break;
    }
}

void light_c_or_s_select_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t* now_screen_obj = lv_scr_act();
    lv_obj_t* parent;
    switch(buf) {
    case 1:
        lv_obj_clean(now_screen_obj);
        create_screen_page_light_side_v1();
        parent = objects.page_light_side_v1;
        lv_slider_set_value(objects.slider_side_light_lum_v1, dev_info.s_light_lum, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.label_light_side_value_v1, "%d", dev_info.s_light_lum);
        if(dev_info.s_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_side_logo_onoff_v1, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
        else lv_imagebutton_set_state(objects.imgbtn_light_side_logo_onoff_v1, LV_IMAGEBUTTON_STATE_RELEASED);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 2:
        lv_obj_clean(now_screen_obj);
        create_screen_page_light_ceiling_v1();
        parent = objects.page_light_ceiling_v1;
        lv_slider_set_value(objects.slider_ceiling_light_lum_v1, dev_info.m_light_lum, LV_ANIM_OFF);
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v1, "%d", dev_info.m_light_lum);
        if(dev_info.m_light_lum) lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v1, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED);
        else lv_imagebutton_set_state(objects.imgbtn_light_ceiling_logo_onoff_v1, LV_IMAGEBUTTON_STATE_RELEASED);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 3:
        lv_obj_clean(now_screen_obj);
        create_screen_page_light_ceiling_v2();
        parent = objects.page_light_ceiling_v2;
        lv_label_set_text_fmt(objects.label_light_ceiling_value_v2, "%d", dev_info.s_light_lum);
        lv_slider_set_value(objects.slider_ceiling_light_lum_v2, dev_info.s_light_lum, LV_ANIM_OFF);
        lv_slider_set_value(objects.slider_ceiling_light_temp_v2, dev_info.s_light_temp, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    case 4:
        lv_obj_clean(now_screen_obj);
        create_screen_page_light_side_v2();
        parent = objects.page_light_side_v2;
        lv_label_set_text_fmt(objects.label_light_side_value_v2, "%d", dev_info.s_light_lum);
        lv_slider_set_value(objects.slider_side_light_lum_v2, dev_info.s_light_lum, LV_ANIM_OFF);
        lv_slider_set_value(objects.slider_side_light_temp_v2, dev_info.s_light_temp, LV_ANIM_OFF);
        lv_screen_load(parent);
        lv_obj_delete(now_screen_obj);
        break;
    }
}

void action_timer_ctrl(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t * roller = lv_event_get_target(e);
    uint32_t value = lv_roller_get_selected(roller);
    lv_obj_t* now_screen_obj = lv_scr_act();
    switch(buf) {
    case 1: 
        dev_info.countdown_hour_set = value;
        if(!dev_info.countdown_hour_set && !dev_info.countdown_minute_set && !dev_info.countdown_second_set) {
            lv_imagebutton_set_state(objects.imgbtn_timer_start, LV_IMGBTN_STATE_RELEASED);
        }else {
            lv_imagebutton_set_state(objects.imgbtn_timer_start, LV_IMGBTN_STATE_CHECKED_PRESSED);
        }
        break;
    case 2:
        dev_info.countdown_minute_set = value;
        if(!dev_info.countdown_hour_set && !dev_info.countdown_minute_set && !dev_info.countdown_second_set) {
            lv_imagebutton_set_state(objects.imgbtn_timer_start, LV_IMGBTN_STATE_RELEASED);
        }else {
            lv_imagebutton_set_state(objects.imgbtn_timer_start, LV_IMGBTN_STATE_CHECKED_PRESSED);
        }
        break;
    case 3:
        dev_info.countdown_second_set = value;
        if(!dev_info.countdown_hour_set && !dev_info.countdown_minute_set && !dev_info.countdown_second_set) {
            lv_imagebutton_set_state(objects.imgbtn_timer_start, LV_IMGBTN_STATE_RELEASED);
        }else {
            lv_imagebutton_set_state(objects.imgbtn_timer_start, LV_IMGBTN_STATE_CHECKED_PRESSED);
        }
        break;
    case 10:
        if(!dev_info.countdown_hour_set && !dev_info.countdown_minute_set && !dev_info.countdown_second_set) break;
        lv_obj_clean(now_screen_obj);

        create_screen_page_home();
        dev_info.countdown_status = COUNTDOWN_RUN;
        dev_info.countdown_hour = dev_info.countdown_hour_set;
        dev_info.countdown_minute = dev_info.countdown_minute_set;
        dev_info.countdown_second = dev_info.countdown_second_set;
        lv_obj_add_flag(objects.container_home_time, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(objects.container_home_timer, LV_OBJ_FLAG_HIDDEN);
        sprintf(label_time, "%02d %02d %02d", dev_info.countdown_hour, dev_info.countdown_minute, dev_info.countdown_second);
        lv_label_set_text(objects.label_home_timer, label_time);
        lv_screen_load(objects.page_home);
        lv_obj_delete(now_screen_obj);
        break;
    case 11:
        if(dev_info.countdown_status == COUNTDOWN_RUN) {
            dev_info.countdown_status = COUNTDOWN_STOP;
            lv_imagebutton_set_state(objects.imgbtn_timer_start_1, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED);
        }else if(dev_info.countdown_status == COUNTDOWN_STOP) {
            dev_info.countdown_status = COUNTDOWN_RUN;
            lv_imagebutton_set_state(objects.imgbtn_timer_start_1, LV_IMGBTN_STATE_RELEASED);
        }
        break;
    case 12:
        lv_obj_clean(now_screen_obj);
        create_screen_page_timer_set();
        lv_roller_set_selected(objects.clock_set_hour, dev_info.countdown_hour_set, LV_ANIM_OFF);
        lv_roller_set_selected(objects.clock_set_minute, dev_info.countdown_minute_set, LV_ANIM_OFF);
        lv_roller_set_selected(objects.clock_set_second, dev_info.countdown_second_set, LV_ANIM_OFF);
        dev_info.countdown_status = COUNTDOWN_NONE;
        dev_info.countdown_hour = dev_info.countdown_hour_set;
        dev_info.countdown_minute = dev_info.countdown_minute_set;
        dev_info.countdown_second = dev_info.countdown_second_set;
        lv_screen_load(objects.page_timer_set);
        lv_obj_delete(now_screen_obj);
        break;
    case 20:
        lv_roller_set_selected(objects.roller_time_set_hour, dev_def_attr.time_hour_set, LV_ANIM_OFF);
        lv_roller_set_selected(objects.roller_time_set_minute, dev_def_attr.time_minute_set, LV_ANIM_OFF);
        lv_obj_remove_flag(objects.img_time_setting, LV_OBJ_FLAG_HIDDEN);
        break;
    case 21:
        dev_def_attr.time_hour_set = value;
        break;
    case 22:
        dev_def_attr.time_minute_set = value;
        break;
    case 23:
        dev_def_attr.time_hour_set = 0;
        dev_def_attr.time_minute_set = 0;
        lv_obj_add_flag(objects.img_time_setting, LV_OBJ_FLAG_HIDDEN);
        break;
    case 24:
        dev_def_attr.time_hour = dev_def_attr.time_hour_set;
        dev_def_attr.time_minute = dev_def_attr.time_minute_set;
        lv_obj_add_flag(objects.img_time_setting, LV_OBJ_FLAG_HIDDEN);

        sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
        lv_label_set_text(objects.label_time_set_now, label_time);
        sprintf(label_time, "%02d %02d", dev_def_attr.time_hour, dev_def_attr.time_minute);
        lv_label_set_text(objects.label_time_set_now_1, label_time);

        t_ctimes s_time_set = {2025, 07, 11, 3, dev_def_attr.time_hour, dev_def_attr.time_minute, 00};
        set_time(s_time_set, &time_h);
        dev_set_rtc_time(&time_h);
        dev_def_attr.time_hour_set = 0;
        dev_def_attr.time_minute_set = 0;
        break;
    default :
        break;
    }
}

void action_onoff_click_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    if(buf == 1) {
        dev_def_attr.Auto_vent_onoff = !dev_def_attr.Auto_vent_onoff;
        if(dev_def_attr.Auto_vent_onoff) {
            lv_image_set_src(objects.btn_deft_auto_onoff, "1:/btn_on.png");
            lv_obj_remove_flag(objects.container_auto_vent, LV_OBJ_FLAG_HIDDEN);
        }else {
            lv_image_set_src(objects.btn_deft_auto_onoff, "1:/btn_off.png");
            lv_obj_add_flag(objects.container_auto_vent, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void action_deft_roller_change_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t * roller = lv_event_get_target(e);
    uint32_t value = lv_roller_get_selected(roller);
    switch(buf) {
    case 1:
        // deft_radar
        dev_def_attr.dev_rodar_time = value;
        if(!value) {
            rodar_buff_generate(30);
        }else {
            rodar_buff_generate(value * 60);
        }
        save_flag = 1;
        break;
    case 2:
        // deft_auto interval
        dev_def_attr.Interval_time = value;
        if(dev_def_attr.Auto_vent_onoff) {
            auto_buff_generate(dev_def_attr.Interval_time + 1, dev_def_attr.Duration_time + 1);
        }
        save_flag = 1;
        break;
    case 3:
        // deft_auto duration
        dev_def_attr.Duration_time = value;
        if(dev_def_attr.Auto_vent_onoff) {
            auto_buff_generate(dev_def_attr.Interval_time + 1, dev_def_attr.Duration_time + 1);
        }
        save_flag = 1;
        break;
    default :
        break;
    }
}

void action_ui_version_select_cb(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t* now_screen_obj = lv_scr_act();
    lv_obj_t* parent;
    switch(buf) {
    case 1: 
        if(dev_def_attr.ui_version == 1) return;
        dev_def_attr.ui_version_set = 1;
        lv_obj_remove_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        break;
    case 2: 
        if(dev_def_attr.ui_version == 2) return;
        dev_def_attr.ui_version_set = 2;
        lv_obj_remove_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        break;
    case 3: 
        if(dev_def_attr.ui_version == 3) return;
        dev_def_attr.ui_version_set = 3;
        lv_obj_remove_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        break;
    case 4: 
        if(dev_def_attr.ui_version == 4) return;
        dev_def_attr.ui_version_set = 4;
        lv_obj_remove_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        break;
    case 5: 
        if(dev_def_attr.ui_version == 5) return;
        dev_def_attr.ui_version_set = 5;
        lv_obj_remove_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        break;
    case 6:
        lv_obj_add_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        break;
    case 7:
        lv_obj_add_flag(objects.img_ui_select_warning, LV_OBJ_FLAG_HIDDEN);
        save_flag = 1;
        dev_def_attr.ui_version = dev_def_attr.ui_version_set;
        if(lv_obj_has_state(objects.btn_ui_version1, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_ui_version1, LV_STATE_CHECKED);
        if(lv_obj_has_state(objects.btn_ui_version2, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_ui_version2, LV_STATE_CHECKED);
        if(lv_obj_has_state(objects.btn_ui_version3, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_ui_version3, LV_STATE_CHECKED);
        if(lv_obj_has_state(objects.btn_ui_version4, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_ui_version4, LV_STATE_CHECKED);
        if(lv_obj_has_state(objects.btn_ui_version5, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_ui_version5, LV_STATE_CHECKED);
        switch(dev_def_attr.ui_version) {
        case 1: lv_obj_add_state(objects.btn_ui_version1, LV_STATE_CHECKED); break;
        case 2: lv_obj_add_state(objects.btn_ui_version2, LV_STATE_CHECKED); break;
        case 3: lv_obj_add_state(objects.btn_ui_version3, LV_STATE_CHECKED); break;
        case 4: lv_obj_add_state(objects.btn_ui_version4, LV_STATE_CHECKED); break;
        case 5: lv_obj_add_state(objects.btn_ui_version5, LV_STATE_CHECKED); break;
        default: break;
        }
        break;
    }
}

void languange_unselect_handle(void) {
    if(lv_obj_has_state(objects.btn_language_eng, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_eng, LV_STATE_CHECKED);
    if(lv_obj_has_state(objects.btn_language_chn, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_chn, LV_STATE_CHECKED);
    if(lv_obj_has_state(objects.btn_language_fra, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_fra, LV_STATE_CHECKED);
    if(lv_obj_has_state(objects.btn_language_esp, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_esp, LV_STATE_CHECKED);
    if(lv_obj_has_state(objects.btn_language_jpa, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_jpa, LV_STATE_CHECKED);
    if(lv_obj_has_state(objects.btn_language_deu, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_deu, LV_STATE_CHECKED);
    if(lv_obj_has_state(objects.btn_language_kra, LV_STATE_CHECKED)) lv_obj_remove_state(objects.btn_language_kra, LV_STATE_CHECKED);
}

void action_language_select(lv_event_t * e){
    uint32_t buf = (uint32_t)lv_event_get_user_data(e);
    switch(buf) {
    case 1: 
        if(dev_def_attr.language_type == LANGUAGE_EN) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_EN;
        lv_label_set_text(objects.label_title_language, "Language");
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_sc_regular_font_36, 0);
        lv_obj_add_state(objects.btn_language_eng, LV_STATE_CHECKED);
        break;
    case 2:
        if(dev_def_attr.language_type == LANGUAGE_ES) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_ES;
        lv_label_set_text(objects.label_title_language, "Idioma");
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_sc_regular_font_36, 0);
        lv_obj_add_state(objects.btn_language_esp, LV_STATE_CHECKED);
        break;
    case 3:
        if(dev_def_attr.language_type == LANGUAGE_FR) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_FR;
        lv_label_set_text(objects.label_title_language, "Langue");
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_sc_regular_font_36, 0);
        lv_obj_add_state(objects.btn_language_fra, LV_STATE_CHECKED);
        break;
    case 4:
        if(dev_def_attr.language_type == LANGUAGE_DE) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_DE;
        lv_label_set_text(objects.label_title_language, "Sprache");
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_sc_regular_font_36, 0);
        lv_obj_add_state(objects.btn_language_deu, LV_STATE_CHECKED);
        break;
    case 5:
        if(dev_def_attr.language_type == LANGUAGE_CN) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_CN;
        lv_label_set_text(objects.label_title_language, "语言");
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_sc_regular_font_36, 0);
        lv_obj_add_state(objects.btn_language_chn, LV_STATE_CHECKED);
        break;
    case 6:
        if(dev_def_attr.language_type == LANGUAGE_JP) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_JP;
        lv_label_set_text(objects.label_title_language, "言語");
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_sc_regular_font_36, 0);
        lv_obj_add_state(objects.btn_language_jpa, LV_STATE_CHECKED);
        break;
    case 7:
        if(dev_def_attr.language_type == LANGUAGE_KR) break;
        save_flag = 1;
        languange_unselect_handle();
        dev_def_attr.language_type = LANGUAGE_KR;
        lv_obj_set_style_text_font(objects.label_title_language, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
        lv_label_set_text(objects.label_title_language, "언어");
        lv_obj_add_state(objects.btn_language_kra, LV_STATE_CHECKED);
        break;
    default:
        break;
    }
}

void action_keyboard_input(lv_event_t * e){
    uint32_t no = (uint32_t)lv_event_get_user_data(e);
    if(no != 10) {
        password_len++;
        password[password_len - 1] = no;
    }else {
        if(password_len) password_len--;
    }
    switch(password_len) {
    case 1: lv_imagebutton_set_state(objects.key_input_status, LV_IMAGEBUTTON_STATE_PRESSED); break;
    case 2: lv_imagebutton_set_state(objects.key_input_status, LV_IMAGEBUTTON_STATE_DISABLED); break;
    case 3: lv_imagebutton_set_state(objects.key_input_status, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED); break;
    case 4: lv_imagebutton_set_state(objects.key_input_status, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED); break;
    default : lv_imagebutton_set_state(objects.key_input_status, LV_IMAGEBUTTON_STATE_RELEASED); break;
    }
    if(password_len == 1) {
        lv_obj_remove_flag(objects.label_key_input, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.label_key_input_err, LV_OBJ_FLAG_HIDDEN);
    }
    if(password_len >= 4) {
        if(password[0] == 2 && password[1] == 0 && password[2] == 1 && password[3] == 3) {
            lv_obj_t* now_screen_obj = lv_scr_act();
            create_screen_page_set();
            lv_screen_load(objects.page_set);
            page_language_refresh(SCREEN_ID_PAGE_SET);
            lv_obj_delete(now_screen_obj);
        }else {
            lv_obj_add_flag(objects.label_key_input, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_flag(objects.label_key_input_err, LV_OBJ_FLAG_HIDDEN);
        }
        password_len = 0;
        memset(password, 0, sizeof(password));
    }
}

char version_nol[20] = {0};
static void page_language_refresh(uint8_t page) {
    switch(page) {
    case SCREEN_ID_PAGE_HOME: // home page
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_home_meeting, "Meeting");
            lv_label_set_text(objects.label_home_phone, "Phone");
            lv_label_set_text(objects.label_home_relax, "Relax");
            lv_label_set_text(objects.label_home_work, "Work");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_home_meeting, "Reunión");
            lv_label_set_text(objects.label_home_phone, "Teléfono");
            lv_label_set_text(objects.label_home_relax, "Relajación");
            lv_label_set_text(objects.label_home_work, "Trabajo");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_home_meeting, "Réunion");
            lv_label_set_text(objects.label_home_phone, "Téléphone");
            lv_label_set_text(objects.label_home_relax, "Détente");
            lv_label_set_text(objects.label_home_work, "Travail");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_home_meeting, "Meeting");
            lv_label_set_text(objects.label_home_phone, "Telefon");
            lv_label_set_text(objects.label_home_relax, "Entspannung");
            lv_label_set_text(objects.label_home_work, "Arbeit");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_home_meeting, "会议");
            lv_label_set_text(objects.label_home_phone, "电话");
            lv_label_set_text(objects.label_home_relax, "放松");
            lv_label_set_text(objects.label_home_work, "工作");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_home_meeting, "会議");
            lv_label_set_text(objects.label_home_phone, "電話");
            lv_label_set_text(objects.label_home_relax, "リラックス");
            lv_label_set_text(objects.label_home_work, "仕事");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_home_meeting, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_home_phone, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_home_relax, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_home_work, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_home_meeting, "회의");
            lv_label_set_text(objects.label_home_phone, "전화");
            lv_label_set_text(objects.label_home_relax, "휴식"); 
            lv_label_set_text(objects.label_home_work, "일");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_FUNTION: // fun page
        switch(dev_def_attr.language_type) {  
        case LANGUAGE_EN:   
            lv_label_set_text(objects.label_fun_light, "Light");
            lv_label_set_text(objects.label_fun_fan, "Fan");
            lv_label_set_text(objects.label_fun_timer, "Timer");
            lv_label_set_text(objects.label_fun_time, "Time");
            lv_label_set_text(objects.label_fun_wifi, "Wi-Fi");
            lv_label_set_text(objects.label_fun_language, "Language");
            lv_label_set_text(objects.label_fun_sys_info, "System\ninformation");
            lv_label_set_text(objects.label_fun_settings, "Settings");
            break;        
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_fun_light, "Iluminación");
            lv_label_set_text(objects.label_fun_fan, "Ventilador");
            lv_label_set_text(objects.label_fun_timer, "Temporizador");
            lv_label_set_text(objects.label_fun_wifi, "Red");
            lv_label_set_text(objects.label_fun_time, "Hora");
            lv_label_set_text(objects.label_fun_language, "Idioma");
            lv_label_set_text(objects.label_fun_sys_info, "Información del sistema");
            lv_label_set_text(objects.label_fun_settings, "Configuración");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_fun_light, "Éclairage");
            lv_label_set_text(objects.label_fun_fan, "Ventilateur");
            lv_label_set_text(objects.label_fun_timer, "Minuterie");
            lv_label_set_text(objects.label_fun_time, "Heure");
            lv_label_set_text(objects.label_fun_wifi, "Réseau");
            lv_label_set_text(objects.label_fun_language, "Langue");
            lv_label_set_text(objects.label_fun_sys_info, "Informations système");
            lv_label_set_text(objects.label_fun_settings, "Paramètres");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_fun_light, "Beleuchtung");
            lv_label_set_text(objects.label_fun_fan, "Ventilator");
            lv_label_set_text(objects.label_fun_timer, "Timer");
            lv_label_set_text(objects.label_fun_time, "Uhrzeit");
            lv_label_set_text(objects.label_fun_wifi, "Netzwerk");
            lv_label_set_text(objects.label_fun_language, "Sprache");
            lv_label_set_text(objects.label_fun_sys_info, "Systeminformationen");
            lv_label_set_text(objects.label_fun_settings, "Einstellungen");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_fun_light, "灯光");
            lv_label_set_text(objects.label_fun_fan, "风扇");
            lv_label_set_text(objects.label_fun_timer, "定时");
            lv_label_set_text(objects.label_fun_time, "时间");
            lv_label_set_text(objects.label_fun_wifi, "网络");
            lv_label_set_text(objects.label_fun_language, "语言");
            lv_label_set_text(objects.label_fun_sys_info, "系统信息");
            lv_label_set_text(objects.label_fun_settings, "设置");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_fun_light, "照明");
            lv_label_set_text(objects.label_fun_fan, "扇風機");
            lv_label_set_text(objects.label_fun_timer, "タイマー");
            lv_label_set_text(objects.label_fun_time, "時刻");
            lv_label_set_text(objects.label_fun_wifi, "ネットワーク");
            lv_label_set_text(objects.label_fun_language, "言語");
            lv_label_set_text(objects.label_fun_sys_info, "システム情報");
            lv_label_set_text(objects.label_fun_settings, "設定");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_fun_light, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_fun_fan, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_fun_timer, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_fun_time, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_fun_wifi, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_fun_language, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_fun_sys_info, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_fun_settings, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_label_set_text(objects.label_fun_light, "조명");
            lv_label_set_text(objects.label_fun_fan, "선풍기");
            lv_label_set_text(objects.label_fun_timer, "타이머");
            lv_label_set_text(objects.label_fun_time, "시간");
            lv_label_set_text(objects.label_fun_wifi, "네트워크");
            lv_label_set_text(objects.label_fun_language, "언어");
            lv_label_set_text(objects.label_fun_sys_info, "시스템 정보");
            lv_label_set_text(objects.label_fun_settings, "설정");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_CEILING_V1: // ceiling light page --- ui version 1
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_ceiling_v1, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_ceiling_v1, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_ceiling_v1, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_ceiling_v1, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_ceiling_v1, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_ceiling_v1, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_ceiling_v1, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_ceiling_v1, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_SIDE_V1: // sisde light page --- ui version 1
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_side_v1, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_side_v1, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_side_v1, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_side_v1, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_side_v1, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_side_v1, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_side_v1, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_side_v1, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_CEILING_V2: // light page --- ui version 2
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_ceiling_v2, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_ceiling_v2, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_ceiling_v2, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_ceiling_v2, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_ceiling_v2, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_ceiling_v2, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_ceiling_v2, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_ceiling_v2, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_SIDE_V2: // light page --- ui version 2
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_side_v2, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_side_v2, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_side_v2, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_side_v2, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_side_v2, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_side_v2, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_side_v2, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_side_v2, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_CEILING_V3: // light page --- ui version 3
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_ceiling_v3, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_ceiling_v3, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_ceiling_v3, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_ceiling_v3, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_ceiling_v3, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_ceiling_v3, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_ceiling_v3, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_ceiling_v3, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_CEILING_V4: // light page --- ui version 4
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_ceiling_v4, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_ceiling_v4, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_ceiling_v4, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_ceiling_v4, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_ceiling_v4, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_ceiling_v4, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_ceiling_v4, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_ceiling_v4, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_CEILING_V5: // ceiling light page --- ui version 5
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_ceiling_v5, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_ceiling_v5, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_ceiling_v5, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_ceiling_v5, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_ceiling_v5, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_ceiling_v5, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_ceiling_v5, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_ceiling_v5, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_LIGHT_AMBIENT_V5: // ambient light page --- ui version 5
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_light_ambient_v5, "Light");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_light_ambient_v5, "Iluminación");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_light_ambient_v5, "Éclairage");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_light_ambient_v5, "Beleuchtung");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_light_ambient_v5, "灯光");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_light_ambient_v5, "照明");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_light_ambient_v5, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_light_ambient_v5, "조명");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_FAN: // fan page
        switch(dev_def_attr.language_type) {  
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_fan, "Fan");
            break;  
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_fan, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_fan, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_fan, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_fan, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_fan, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_fan, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_fan, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_TIMER_SET: // timer set page
        switch(dev_def_attr.language_type) {  
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_fun_timer, "Timer");
            lv_label_set_text(objects.clock_logo_h, "H");
            lv_label_set_text(objects.clock_logo_m, "M");
            lv_label_set_text(objects.clock_logo_s, "S");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_fun_timer, "Temporizador");
            lv_label_set_text(objects.clock_logo_h, "H");
            lv_label_set_text(objects.clock_logo_m, "M");
            lv_label_set_text(objects.clock_logo_s, "S");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_fun_timer, "Minuterie");
            lv_label_set_text(objects.clock_logo_h, "H");
            lv_label_set_text(objects.clock_logo_m, "M");
            lv_label_set_text(objects.clock_logo_s, "S");
            break;  
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_fun_timer, "Timer");
            lv_label_set_text(objects.clock_logo_h, "H");
            lv_label_set_text(objects.clock_logo_m, "M");
            lv_label_set_text(objects.clock_logo_s, "S");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_fun_timer, "定时");
            lv_label_set_text(objects.clock_logo_h, "时");
            lv_label_set_text(objects.clock_logo_m, "分");
            lv_label_set_text(objects.clock_logo_s, "秒");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_fun_timer, "タイマー");
            lv_label_set_text(objects.clock_logo_h, "時");
            lv_label_set_text(objects.clock_logo_m, "分");
            lv_label_set_text(objects.clock_logo_s, "秒");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_fun_timer, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.clock_logo_h, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.clock_logo_m, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.clock_logo_s, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_label_set_text(objects.label_fun_timer, "타이머");
            lv_label_set_text(objects.clock_logo_h, "시");
            lv_label_set_text(objects.clock_logo_m, "분");
            lv_label_set_text(objects.clock_logo_s, "초");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_TIMER_RUN: // timer run page
        switch(dev_def_attr.language_type) {  
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_timer_1, "Timer");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_timer_1, "Temporizador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_timer_1, "Minuterie");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_timer_1, "Timer");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_timer_1, "定时");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_timer_1, "タイマー");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_timer_1, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_label_set_text(objects.label_title_timer_1, "타이머");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_SET_TIME: // set data page
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_time, "Time");
            lv_label_set_text(objects.label_time_set_title, "TIME");
            lv_label_set_text(objects.label_time_set_time, "Time");
            lv_label_set_text(objects.time_set_window_title, "Set time");
            lv_label_set_text(objects.label_window_set_time_h, "H");
            lv_label_set_text(objects.label_window_set_time_m, "M");
            lv_label_set_text(objects.label_window_set_time_canel, "Canel");
            lv_label_set_text(objects.label_window_set_time_ok, "OK");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_time, "Hora");
            lv_label_set_text(objects.label_time_set_title, "Hora");
            lv_label_set_text(objects.label_time_set_time, "Hora");
            lv_label_set_text(objects.time_set_window_title, "Configurar hora");
            lv_label_set_text(objects.label_window_set_time_h, "H");
            lv_label_set_text(objects.label_window_set_time_m, "M");
            lv_label_set_text(objects.label_window_set_time_canel, "Cancelar");
            lv_label_set_text(objects.label_window_set_time_ok, "Aceptar");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_time, "Heure");
            lv_label_set_text(objects.label_time_set_title, "Heure");
            lv_label_set_text(objects.label_time_set_time, "Heure");
            lv_label_set_text(objects.time_set_window_title, "Régler l'heure");
            lv_label_set_text(objects.label_window_set_time_h, "H");
            lv_label_set_text(objects.label_window_set_time_m, "M");
            lv_label_set_text(objects.label_window_set_time_canel, "Annuler");
            lv_label_set_text(objects.label_window_set_time_ok, "Confirmer");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_time, "Uhrzeit");
            lv_label_set_text(objects.label_time_set_title, "Uhrzeit");
            lv_label_set_text(objects.label_time_set_time, "Uhrzeit");
            lv_label_set_text(objects.time_set_window_title, "Uhrzeit einstellen");
            lv_label_set_text(objects.label_window_set_time_h, "H");
            lv_label_set_text(objects.label_window_set_time_m, "M");
            lv_label_set_text(objects.label_window_set_time_canel, "Abbrechen");
            lv_label_set_text(objects.label_window_set_time_ok, "Bestätigen");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_time, "时间");
            lv_label_set_text(objects.label_time_set_title, "时间");
            lv_label_set_text(objects.label_time_set_time, "时间");
            lv_label_set_text(objects.time_set_window_title, "设置时间");
            lv_label_set_text(objects.label_window_set_time_h, "时");
            lv_label_set_text(objects.label_window_set_time_m, "分");
            lv_label_set_text(objects.label_window_set_time_canel, "取消");
            lv_label_set_text(objects.label_window_set_time_ok, "确定");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_time, "時刻");
            lv_label_set_text(objects.label_time_set_title, "時刻");
            lv_label_set_text(objects.label_time_set_time, "時刻");
            lv_label_set_text(objects.time_set_window_title, "時間を設定");
            lv_label_set_text(objects.label_window_set_time_h, "時");
            lv_label_set_text(objects.label_window_set_time_m, "分");
            lv_label_set_text(objects.label_window_set_time_canel, "キャンセル");
            lv_label_set_text(objects.label_window_set_time_ok, "確定");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_time, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_time_set_title, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_time_set_time, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.time_set_window_title, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.label_window_set_time_h, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_window_set_time_m, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_window_set_time_canel, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_window_set_time_ok, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_time, "시간");
            lv_label_set_text(objects.label_time_set_title, "시간");
            lv_label_set_text(objects.label_time_set_time, "시간");
            lv_label_set_text(objects.time_set_window_title, "시간 설정");
            lv_label_set_text(objects.label_window_set_time_h, "시");
            lv_label_set_text(objects.label_window_set_time_m, "분");
            lv_label_set_text(objects.label_window_set_time_canel, "취소");
            lv_label_set_text(objects.label_window_set_time_ok, "확인");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_SET_SYSINFO:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_sysinfo, "System information");
            lv_label_set_text(objects.label_sysinfo_type, "System type");
            lv_label_set_text(objects.label_sysinfo_id, "System ID");
            lv_label_set_text(objects.label_sysinfo_hardware, "Hardware unit");
            lv_label_set_text(objects.label_sysinfo_software, "Software unit");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_sysinfo, "Información del sistema");
            lv_label_set_text(objects.label_sysinfo_type, "Tipo de sistema");
            lv_label_set_text(objects.label_sysinfo_id, "ID del sistema");
            lv_label_set_text(objects.label_sysinfo_hardware, "Unidad de hardware");
            lv_label_set_text(objects.label_sysinfo_software, "Unidad de software");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_sysinfo, "Informations système");
            lv_label_set_text(objects.label_sysinfo_type, "Type de système");
            lv_label_set_text(objects.label_sysinfo_id, "ID du système");
            lv_label_set_text(objects.label_sysinfo_hardware, "Unité matérielle");
            lv_label_set_text(objects.label_sysinfo_software, "Unité logicielle");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_sysinfo, "Systeminformation");
            lv_label_set_text(objects.label_sysinfo_type, "Systemtyp");
            lv_label_set_text(objects.label_sysinfo_id, "System-ID");
            lv_label_set_text(objects.label_sysinfo_hardware, "Hardware-Einheit");
            lv_label_set_text(objects.label_sysinfo_software, "Software-Einheit");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_sysinfo, "系统信息");
            lv_label_set_text(objects.label_sysinfo_type, "系统类型");
            lv_label_set_text(objects.label_sysinfo_id, "系统ID");
            lv_label_set_text(objects.label_sysinfo_hardware, "硬件单元");
            lv_label_set_text(objects.label_sysinfo_software, "软件单元");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_sysinfo, "システム情報");
            lv_label_set_text(objects.label_sysinfo_type, "システムタイプ");
            lv_label_set_text(objects.label_sysinfo_id, "システムID");
            lv_label_set_text(objects.label_sysinfo_hardware, "ハードウェアユニット");
            lv_label_set_text(objects.label_sysinfo_software, "ソフトウェアユニット");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_sysinfo, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_sysinfo_type, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_sysinfo_id, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_sysinfo_hardware, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_sysinfo_software, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_sysinfo, "시스템 정보");
            lv_label_set_text(objects.label_sysinfo_type, "시스템 유형");
            lv_label_set_text(objects.label_sysinfo_id, "시스템 ID");
            lv_label_set_text(objects.label_sysinfo_hardware, "하드웨어 유닛");
            lv_label_set_text(objects.label_sysinfo_software, "소프트웨어 유닛");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_KEYBOARD: // set password page
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_keyboard_settings, "Settings");
            lv_label_set_text(objects.label_key_input, "Enter system code");
            lv_label_set_text(objects.label_key_input_err, "System code don’t match");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_keyboard_settings, "Configuración");
            lv_label_set_text(objects.label_key_input, "Ingresar contraseña del sistema");
            lv_label_set_text(objects.label_key_input_err, "La contraseña del sistema no coincide");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_keyboard_settings, "Paramètres");
            lv_label_set_text(objects.label_key_input, "Entrer le mot de passe système");
            lv_label_set_text(objects.label_key_input_err, "Le mot de passe système ne correspond pas");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_keyboard_settings, "Einstellungen");
            lv_label_set_text(objects.label_key_input, "Systempasswort eingeben");
            lv_label_set_text(objects.label_key_input_err, "Systempasswort stimmt nicht überein");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_keyboard_settings, "设置");
            lv_label_set_text(objects.label_key_input, "输入系统密码");
            lv_label_set_text(objects.label_key_input_err, "系统密码不匹配");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_keyboard_settings, "設定");
            lv_label_set_text(objects.label_key_input, "システムパスワードを入力");
            lv_label_set_text(objects.label_key_input_err, "システムパスワードが一致しません");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_keyboard_settings, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_key_input, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.label_key_input_err, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_label_set_text(objects.label_keyboard_settings, "설정");
            lv_label_set_text(objects.label_key_input, "시스템비밀번호입력");
            lv_label_set_text(objects.label_key_input_err, "시스템비밀번호가일치하지않습니다");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_SET: // set page
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_set_settings, "Settings");
            lv_label_set_text(objects.label_dev_deft, "Device default");
            lv_label_set_text(objects.label_ui_version, "UI version");
            sprintf(version_nol, "Version %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_set_settings, "Configuración");
            lv_label_set_text(objects.label_dev_deft, "Valores iniciales");
            lv_label_set_text(objects.label_ui_version, "Versión de interfaz");
            sprintf(version_nol, "Versión %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_set_settings, "Paramètres");
            lv_label_set_text(objects.label_dev_deft, "Valeurs par défaut");
            lv_label_set_text(objects.label_ui_version, "Version de l'interface");
            sprintf(version_nol, "Version %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_set_settings, "Einstellungen");
            lv_label_set_text(objects.label_dev_deft, "Werkseinstellungen");
            lv_label_set_text(objects.label_ui_version, "Oberflächenversion");
            sprintf(version_nol, "version %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_set_settings, "设置");
            lv_label_set_text(objects.label_dev_deft, "设备初始值");
            lv_label_set_text(objects.label_ui_version, "界面版本");
            sprintf(version_nol, "版本 %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_set_settings, "設定");
            lv_label_set_text(objects.label_dev_deft, "初期設定値");
            lv_label_set_text(objects.label_ui_version, "インターフェースバージョン");
            sprintf(version_nol, "バージョン %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_set_settings, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_dev_deft, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_ui_version, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_ui_version_nol, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_set_settings, "설정");
            lv_label_set_text(objects.label_dev_deft, "초기 설정값");
            lv_label_set_text(objects.label_ui_version, "인터페이스 버전");
            sprintf(version_nol, "버전 %d", dev_def_attr.ui_version);
            lv_label_set_text(objects.label_ui_version_nol, version_nol);
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_V1:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_1, "Device default");
            lv_label_set_text(objects.label_deft_light_v1, "Light");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "Ceiling light");
            lv_label_set_text(objects.label_deft_side_light_v1, "Side Light");
            lv_label_set_text(objects.label_deft_fan_v1, "Fan");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_1, "Valores iniciales");
            lv_label_set_text(objects.label_deft_light_v1, "Iluminación");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "Luz principal");
            lv_label_set_text(objects.label_deft_side_light_v1, "Luz lateral");
            lv_label_set_text(objects.label_deft_fan_v1, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_1, "Valeurs par défaut");
            lv_label_set_text(objects.label_deft_light_v1, "Éclairage");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "Lampe principale");
            lv_label_set_text(objects.label_deft_side_light_v1, "Lampe latérale");
            lv_label_set_text(objects.label_deft_fan_v1, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_1, "Werkseinstellungen");
            lv_label_set_text(objects.label_deft_light_v1, "Beleuchtung");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "Hauptlicht");
            lv_label_set_text(objects.label_deft_side_light_v1, "Seitenlicht");
            lv_label_set_text(objects.label_deft_fan_v1, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_1, "设备初始值");
            lv_label_set_text(objects.label_deft_light_v1, "灯光");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "主灯");
            lv_label_set_text(objects.label_deft_side_light_v1, "侧灯");
            lv_label_set_text(objects.label_deft_fan_v1, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_1, "初期設定値");
            lv_label_set_text(objects.label_deft_light_v1, "照明");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "メインライト");
            lv_label_set_text(objects.label_deft_side_light_v1, "サイドライト");
            lv_label_set_text(objects.label_deft_fan_v1, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_1, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_light_v1, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_v1, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_side_light_v1, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_fan_v1, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_deft_1, "초기 설정값");
            lv_label_set_text(objects.label_deft_light_v1, "조명");
            lv_label_set_text(objects.label_deft_ceiling_light_v1, "메인 라이트");
            lv_label_set_text(objects.label_deft_side_light_v1, "사이드 라이트");
            lv_label_set_text(objects.label_deft_fan_v1, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_V2:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_2, "Device default");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "Ceiling light");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "Brightness");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "Color Temperature");
            lv_label_set_text(objects.label_deft_side_light_v2, "Side Light");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "Brightness");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "Color  Temperature");
            lv_label_set_text(objects.label_deft_fan_v2, "Fan");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_2, "Valores iniciales");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "Luz principal");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "Brillo");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "Temperatura de color");
            lv_label_set_text(objects.label_deft_side_light_v2, "Luz lateral");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "Brillo");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "Temperatura de color");
            lv_label_set_text(objects.label_deft_fan_v2, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_2, "Valeurs par défaut");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "Lampe principale");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "Luminosité");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "Température de couleur");
            lv_label_set_text(objects.label_deft_side_light_v2, "Lampe latérale");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "Luminosité");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "Température de couleur");
            lv_label_set_text(objects.label_deft_fan_v2, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_2, "Werkseinstellungen");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "Hauptlicht");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "Helligkeit");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "Farbtemperatur");
            lv_label_set_text(objects.label_deft_side_light_v2, "Seitenlicht");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "Helligkeit");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "Farbtemperatur");
            lv_label_set_text(objects.label_deft_fan_v2, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_2, "设备初始值");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "主灯");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "亮度");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "色温");
            lv_label_set_text(objects.label_deft_side_light_v2, "侧灯");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "亮度");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "色温");
            lv_label_set_text(objects.label_deft_fan_v2, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_2, "初期設定値");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "メインライト");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "明るさ");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "色温度");
            lv_label_set_text(objects.label_deft_side_light_v2, "サイドライト");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "明るさ");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "色温度");
            lv_label_set_text(objects.label_deft_fan_v2, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_2, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_v2, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_brightness_v2, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_colortemp_v2, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_side_light_v2, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_deft_side_light_brightness_v2, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_side_light_colortemp_v2, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_fan_v2, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_deft_2, "초기 설정값");
            lv_label_set_text(objects.label_deft_ceiling_light_v2, "메인 라이트");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v2, "밝기");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v2, "색온도");
            lv_label_set_text(objects.label_deft_side_light_v2, "사이드 라이트");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "밝기");
            lv_label_set_text(objects.label_deft_side_light_colortemp_v2, "색온도");
            lv_label_set_text(objects.label_deft_fan_v2, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_V3:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_3, "Device default");
            lv_label_set_text(objects.label_deft_light_v3, "Light");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "Brightness");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "Color Temperature");
            lv_label_set_text(objects.label_deft_fan_v3, "Fan");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_3, "Valores iniciales");
            lv_label_set_text(objects.label_deft_light_v3, "Iluminación");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "Brillo");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "Temperatura de color");
            lv_label_set_text(objects.label_deft_fan_v3, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_3, "Valeurs par défaut");
            lv_label_set_text(objects.label_deft_light_v3, "Éclairage");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "Luminosité");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "Température de couleur");
            lv_label_set_text(objects.label_deft_fan_v3, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_3, "Werkseinstellungen");
            lv_label_set_text(objects.label_deft_light_v3, "Beleuchtung");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "Helligkeit");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "Farbtemperatur");
            lv_label_set_text(objects.label_deft_fan_v3, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_3, "设备初始值");
            lv_label_set_text(objects.label_deft_light_v3, "灯光");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "亮度");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "色温");
            lv_label_set_text(objects.label_deft_fan_v3, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_3, "初期設定値");
            lv_label_set_text(objects.label_deft_light_v3, "照明");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "明るさ");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "色温度");
            lv_label_set_text(objects.label_deft_fan_v3, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_3, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_light_v3, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_brightness_v3, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_colortemp_v3, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_fan_v3, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_deft_3, "초기 설정값");
            lv_label_set_text(objects.label_deft_light_v3, "조명");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v3, "밝기");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v3, "색온도");
            lv_label_set_text(objects.label_deft_fan_v3, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_V4:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_4, "Device default");
            lv_label_set_text(objects.label_deft_light_v4, "Light");
            lv_label_set_text(objects.label_deft_fan_v4, "Fan");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_4, "Valores iniciales");
            lv_label_set_text(objects.label_deft_light_v4, "Iluminación");
            lv_label_set_text(objects.label_deft_fan_v4, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_4, "Valeurs par défaut");
            lv_label_set_text(objects.label_deft_light_v4, "Éclairage");
            lv_label_set_text(objects.label_deft_fan_v4, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_4, "Werkseinstellungen");
            lv_label_set_text(objects.label_deft_light_v4, "Beleuchtung");
            lv_label_set_text(objects.label_deft_fan_v4, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_4, "设备初始值");
            lv_label_set_text(objects.label_deft_light_v4, "灯光");
            lv_label_set_text(objects.label_deft_fan_v4, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_4, "初期設定値");
            lv_label_set_text(objects.label_deft_light_v4, "照明");
            lv_label_set_text(objects.label_deft_fan_v4, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_4, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_light_v4, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_fan_v4, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_deft_4, "초기 설정값");
            lv_label_set_text(objects.label_deft_light_v4, "조명");
            lv_label_set_text(objects.label_deft_fan_v4, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_V5:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_5, "Device default");
            lv_label_set_text(objects.label_deft_light_v5, "Light");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "Brightness");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "Color Temperature");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "Fan");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_5, "Valores iniciales");
            lv_label_set_text(objects.label_deft_light_v5, "Iluminación");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "Brillo");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "Temperatura de color");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_5, "Valeurs par défaut");
            lv_label_set_text(objects.label_deft_light_v5, "Éclairage");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "Luminosité");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "Température de couleur");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_5, "Werkseinstellungen");
            lv_label_set_text(objects.label_deft_light_v5, "Beleuchtung");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "Helligkeit");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "Farbtemperatur");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_5, "设备初始值");
            lv_label_set_text(objects.label_deft_light_v5, "灯光");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "亮度");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "色温");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_5, "初期設定値");
            lv_label_set_text(objects.label_deft_light_v5, "照明");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "明るさ");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "色温度");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_5, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_light_v5, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_brightness_v5, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_deft_ceiling_light_colortemp_v5, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.labnel_deft_ambient_v5, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.labnel_deft_fan_v5, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_label_set_text(objects.label_title_deft_5, "초기 설정값");
            lv_label_set_text(objects.label_deft_light_v5, "조명");
            lv_label_set_text(objects.label_deft_ceiling_light_brightness_v5, "밝기");
            lv_label_set_text(objects.label_deft_ceiling_light_colortemp_v5, "색온도");
            lv_label_set_text(objects.labnel_deft_ambient_v5, "Ambient Light");
            lv_label_set_text(objects.labnel_deft_fan_v5, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_LUM_SLIDER:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_6, "Device default");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "Ceiling light");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "Side Light");
            lv_label_set_text(objects.label_deft_slider_brightness, "Brightness");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_6, "Valores iniciales");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "Luz principal");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "Luz lateral");
            lv_label_set_text(objects.label_deft_slider_brightness, "Brillo");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_6, "Valeurs par défaut");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "Lampe principale");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "Luminosité");
            lv_label_set_text(objects.label_deft_slider_brightness, "Luminosité");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_6, "Werkseinstellungen");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "Hauptlicht");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "Seitenlicht");
            lv_label_set_text(objects.label_deft_slider_brightness, "Helligkeit");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_6, "设备初始值");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "主灯");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "侧灯");
            lv_label_set_text(objects.label_deft_slider_brightness, "亮度");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_6, "初期設定値");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "メインライト");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "サイドライト");
            lv_label_set_text(objects.label_deft_slider_brightness, "明るさ");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_6, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_slider_lum_light_type, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.label_deft_slider_brightness, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_label_set_text(objects.label_title_deft_6, "초기 설정값");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_lum_light_type, "메인 라이트");
            else lv_label_set_text(objects.label_deft_slider_lum_light_type, "사이드 라이트");
            lv_label_set_text(objects.label_deft_slider_brightness, "밝기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_LIGHT_TEMP_SLIDER:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_7, "Device default");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "Ceiling light");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "Side Light");
            lv_label_set_text(objects.label_deft_slider_color_temp, "Color  Temperature");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_7, "Valores iniciales");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "Luz principal");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "Luz lateral");
            lv_label_set_text(objects.label_deft_slider_color_temp, "Temperatura de color");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_7, "Valeurs par défaut");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "Lampe principale");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "Lampe latérale");
            lv_label_set_text(objects.label_deft_slider_color_temp, "Température de couleur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_7, "Werkseinstellungen");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "Hauptlicht");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "Seitenlicht");
            lv_label_set_text(objects.label_deft_slider_color_temp, "Farbtemperatur");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_7, "设备初始值");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "主灯");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "侧灯");
            lv_label_set_text(objects.label_deft_slider_color_temp, "色温");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_7, "初期設定値");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "メインライト");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "サイドライト");
            lv_label_set_text(objects.label_deft_side_light_brightness_v2, "明るさ");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_7, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_slider_temp_light_type, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.label_deft_slider_color_temp, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_label_set_text(objects.label_title_deft_7, "초기 설정값");
            if(dev_def_attr.default_light_select == CEILING_LIGHT) lv_label_set_text(objects.label_deft_slider_temp_light_type, "메인 라이트");
            else lv_label_set_text(objects.label_deft_slider_temp_light_type, "사이드 라이트");
            lv_label_set_text(objects.label_deft_slider_color_temp, "색온도");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_FAN_SLIDER:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_8, "Device default");
            lv_label_set_text(objects.label_deft_slider_fan, "Fan");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_8, "Valores iniciales");
            lv_label_set_text(objects.label_deft_slider_fan, "Ventilador");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_8, "Valeurs par défaut");
            lv_label_set_text(objects.label_deft_slider_fan, "Ventilateur");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_8, "Werkseinstellungen");
            lv_label_set_text(objects.label_deft_slider_fan, "Ventilator");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_8, "设备初始值");
            lv_label_set_text(objects.label_deft_slider_fan, "风扇");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_8, "初期設定値");
            lv_label_set_text(objects.label_deft_slider_fan, "扇風機");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_8, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_deft_slider_fan, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_label_set_text(objects.label_title_deft_8, "초기 설정값");
            lv_label_set_text(objects.label_deft_slider_fan, "선풍기");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_RADAR:
        switch(dev_def_attr.language_type) {  
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_9, "Device default");
            lv_label_set_text(objects.label_radar_mont, "Radar monitoring time");
            lv_label_set_text(objects.label_radar_m, "M");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_9, "Valores iniciales");
            lv_label_set_text(objects.label_radar_mont, "Tiempo de detección por radar");
            lv_label_set_text(objects.label_radar_m, "M");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_9, "Valeurs par défaut");
            lv_label_set_text(objects.label_radar_mont, "Temps de détection radar");
            lv_label_set_text(objects.label_radar_m, "M");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_9, "Werkseinstellungen");
            lv_label_set_text(objects.label_radar_mont, "Radarerfassungszeit");
            lv_label_set_text(objects.label_radar_m, "M");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_9, "设备初始值");
            lv_label_set_text(objects.label_radar_mont, "雷达探测时间");
            lv_label_set_text(objects.label_radar_m, "分");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_9, "初期設定値");
            lv_label_set_text(objects.label_radar_mont, "レーダー検知時間");
            lv_label_set_text(objects.label_radar_m, "分");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_9, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_radar_mont, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.label_radar_m, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_label_set_text(objects.label_title_deft_9, "초기 설정값");
            lv_label_set_text(objects.label_radar_mont, "레이더 탐지 시간");
            lv_label_set_text(objects.label_radar_m, "분");
            break;
        default:
            break;
        }
        break;
    case SCREEN_ID_PAGE_DEFT_AUTO_VENT:
        switch(dev_def_attr.language_type) {
        case LANGUAGE_EN:
            lv_label_set_text(objects.label_title_deft_10, "Device default");
            lv_label_set_text(objects.label_auto_vent, "Auto ventilation");
            lv_label_set_text(objects.label_interval, "Interval");
            lv_label_set_text(objects.label_duration, "Duration");
            lv_label_set_text(objects.label_auto_h, "H");
            lv_label_set_text(objects.label_auto_m, "M");
            break;
        case LANGUAGE_ES:
            lv_label_set_text(objects.label_title_deft_10, "Valores iniciales");
            lv_label_set_text(objects.label_auto_vent, "Ventilación automática");
            lv_label_set_text(objects.label_interval, "Intervalo de tiempo");
            lv_label_set_text(objects.label_duration, "Duración");
            lv_label_set_text(objects.label_auto_h, "H");
            lv_label_set_text(objects.label_auto_m, "M");
            break;
        case LANGUAGE_FR:
            lv_label_set_text(objects.label_title_deft_10, "Valeurs par défaut");
            lv_label_set_text(objects.label_auto_vent, "Ventilation automatique");
            lv_label_set_text(objects.label_interval, "Intervalle de temps");
            lv_label_set_text(objects.label_duration, "Durée");
            lv_label_set_text(objects.label_auto_h, "H");
            lv_label_set_text(objects.label_auto_m, "M");
            break;
        case LANGUAGE_DE:
            lv_label_set_text(objects.label_title_deft_10, "Werkseinstellungen");
            lv_label_set_text(objects.label_auto_vent, "Automatische Belüftung");
            lv_label_set_text(objects.label_interval, "Zeitintervall");
            lv_label_set_text(objects.label_duration, "Dauer");
            lv_label_set_text(objects.label_auto_h, "H");
            lv_label_set_text(objects.label_auto_m, "M");
            break;
        case LANGUAGE_CN:
            lv_label_set_text(objects.label_title_deft_10, "设备初始值");
            lv_label_set_text(objects.label_auto_vent, "自动换气");
            lv_obj_set_style_text_font(objects.label_interval, &ui_font_harmony_os_sans_sc_regular_font_28_backup, 0);
            lv_obj_set_style_text_font(objects.label_duration, &ui_font_harmony_os_sans_sc_regular_font_28_backup, 0);
            lv_label_set_text(objects.label_interval, "间隔时间");
            lv_label_set_text(objects.label_duration, "持续时间");
            lv_label_set_text(objects.label_auto_h, "时");
            lv_label_set_text(objects.label_auto_m, "分");
            break;
        case LANGUAGE_JP:
            lv_label_set_text(objects.label_title_deft_10, "初期設定値");
            lv_label_set_text(objects.label_auto_vent, "自動換気");
            lv_obj_set_style_text_font(objects.label_interval, &ui_font_harmony_os_sans_sc_regular_font_28_backup, 0);
            lv_obj_set_style_text_font(objects.label_duration, &ui_font_harmony_os_sans_sc_regular_font_28_backup, 0);
            lv_label_set_text(objects.label_interval, "間隔時間");
            lv_label_set_text(objects.label_duration, "持続時間");
            lv_label_set_text(objects.label_auto_h, "時");
            lv_label_set_text(objects.label_auto_m, "分");
            break;
        case LANGUAGE_KR:
            lv_obj_set_style_text_font(objects.label_title_deft_10, &ui_font_harmony_os_sans_kr_regular_font_36, 0);
            lv_obj_set_style_text_font(objects.label_auto_vent, &ui_font_harmony_os_sans_kr_regular_font_32, 0);
            lv_obj_set_style_text_font(objects.label_interval, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_duration, &ui_font_harmony_os_sans_kr_regular_font_28, 0);
            lv_obj_set_style_text_font(objects.label_auto_h, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_obj_set_style_text_font(objects.label_auto_m, &ui_font_harmony_os_sans_kr_regular_font_24, 0);
            lv_label_set_text(objects.label_title_deft_10, "초기 설정값");
            lv_label_set_text(objects.label_auto_vent, "자동 환기");
            lv_label_set_text(objects.label_interval, "간격 시간");
            lv_label_set_text(objects.label_duration, "지속 시간");
            lv_label_set_text(objects.label_auto_h, "시");
            lv_label_set_text(objects.label_auto_m, "분");
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

