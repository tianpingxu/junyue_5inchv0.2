#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_ceiling_lum_max;
extern const lv_img_dsc_t img_side_lum_max;
extern const lv_img_dsc_t img_fan_speed_show_01;
extern const lv_img_dsc_t img_fan_speed_show_02;
extern const lv_img_dsc_t img_fan_speed_show_03;
extern const lv_img_dsc_t img_fan_speed_show_04;
extern const lv_img_dsc_t img_fan_speed_show_05;
extern const lv_img_dsc_t img_fan_speed_show_06;
extern const lv_img_dsc_t img_fan_speed_show_07;
extern const lv_img_dsc_t img_fan_speed_show_08;
extern const lv_img_dsc_t img_fan_speed_show_09;
extern const lv_img_dsc_t img_fan_speed_show_10;


#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const void *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[12];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/