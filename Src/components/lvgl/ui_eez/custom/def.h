#ifndef DEF_CODE
#define DEF_CODE

#include "stdint.h"
#include "stdbool.h"
#include "rtc_hal.h"

typedef struct {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
}RTC_TIME;

typedef struct {
    unsigned short years;
    unsigned char  months;
    unsigned char  days;
    unsigned char  weeks;
    unsigned char  hours;
    unsigned char  minutes;
    unsigned char  seconds;
}RTC_TIMES;

//人感状态
typedef enum {
    HUMAN_SENSE_OFF,       //没人
	HUMAN_SENSE_ON		   //有人
} HUMAN_SENSE_STATSUS;		

//灯选择
typedef enum {
    CEILING_LIGHT = 1,
	SIDE_LIGHT,
} LIGHT_SELECT;

//语言
typedef enum {
    LANGUAGE_EN = 1,
	LANGUAGE_ES,
	LANGUAGE_FR,
	LANGUAGE_DE,
	LANGUAGE_CN,
	LANGUAGE_JP,
	LANGUAGE_KR,
} LANGUAGE_TYPE;

//定时状态
typedef enum {
    COUNTDOWN_NONE,
	COUNTDOWN_STOP,
	COUNTDOWN_RUN,
} COUNTDOWN_STATUS;

//UI VERSION
typedef enum {
    UI_VERSION_1 = 1,
	UI_VERSION_2,
	UI_VERSION_3,
	UI_VERSION_4,
	UI_VERSION_5,

} UI_VERSION;

//设置默认值
typedef struct {
	uint8_t default_fan_speed;
	uint8_t default_m_light_lum;
	uint8_t default_s_light_lum;
	uint8_t default_a_light_lum;
	uint8_t default_m_light_temp;
	uint8_t default_s_light_temp;
	uint8_t default_a_light_temp;

	uint8_t default_light_select;

	uint16_t data_year;
	uint8_t data_mon;
	uint8_t data_day;
	uint8_t time_hour;
	uint8_t time_minute;
	uint8_t time_second;

	uint16_t data_year_set;
	uint8_t data_mon_set;
	uint8_t data_day_set;
	uint8_t time_hour_set;
	uint8_t time_minute_set;

	uint8_t language_type;
	uint8_t ui_version_set;
	uint8_t ui_version;

	uint8_t dev_rodar_time;

	uint8_t Auto_vent_onoff;
	uint8_t Interval_time;
	uint8_t Duration_time;

	uint8_t power_first;
	uint8_t save_flag;
	uint8_t save_cnt;
} DEV_DEF_ATTR;

typedef struct {
	//当前值
	uint8_t fan_speed;
    uint8_t m_light_lum;
    uint8_t s_light_lum;
	uint8_t m_light_temp;
	uint8_t s_light_temp;
	uint8_t am_light_color;

	uint8_t light_select;

	bool fan_speed_change_flag;
    bool m_light_lum_change_flag;
    bool s_light_lum_change_flag;
	bool m_light_temp_change_flag;
	bool s_light_temp_change_flag;
	bool am_light_color_change_flag;

	//人感
	bool human_sense_status;

	uint8_t dev_rodar_time_read;
	uint8_t Interval_time_read;
	uint8_t Duration_time_read;

	bool mode_in_flag;
	bool sence_mode_meet_onoff;
	bool sence_mode_phone_onoff;
	bool sence_mode_relax_onoff;
	bool sence_mode_work_onoff;

	//风扇定时倒计时
	uint16_t fan_countdown_hour;
	uint16_t fan_countdown_minute;

	//使用时间
	uint16_t count_hour_user;
	uint16_t count_minute_user;
	uint16_t count_second_user;

	//倒计时
	uint8_t countdown_hour;
	uint8_t countdown_minute;
	uint8_t countdown_second;

	uint8_t countdown_hour_set;
	uint8_t countdown_minute_set;
	uint8_t countdown_second_set;

	uint8_t countdown_status; //0:未开始 1:进行中 2:结束
	uint8_t countdown_blink;
} DEV_INFO;


extern DEV_INFO dev_info;
extern DEV_DEF_ATTR dev_def_attr;

#endif /* DEF_CODE */
