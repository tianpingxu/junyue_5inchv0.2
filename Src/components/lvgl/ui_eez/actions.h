#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_gesture_handle_cb(lv_event_t * e);
extern void action_mode_select_cb(lv_event_t * e);
extern void action_goto_new_screen(lv_event_t * e);
extern void action_slider_change_cb(lv_event_t * e);
extern void light_c_or_s_select_cb(lv_event_t * e);
extern void action_timer_ctrl(lv_event_t * e);
extern void action_language_select(lv_event_t * e);
extern void action_keyboard_input(lv_event_t * e);
extern void action_dev_deft_select_cb(lv_event_t * e);
extern void action_deft_roller_change_cb(lv_event_t * e);
extern void action_onoff_click_cb(lv_event_t * e);
extern void action_ui_version_select_cb(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/