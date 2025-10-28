/**
 * @file tslib.h
 * @author Product application department
 * @brief  tslib电阻触摸算法头文件
 * @version V1.0
 * @date 2025-07-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */
#ifndef __TSLIB_H__
#define __TSLIB_H__
// 头文件声明
#include "type.h"

// 全局变量定义

#define NR_SAMPHISTLEN 4
struct ts_hist
{
    int x;
    int y;
    unsigned int p;
};

struct ts_sample // 触摸屏一个样点
{
    int x;
    int y;
    unsigned int pressure;
};

struct tslib_dejitter
{
    int delta;
    int x;
    int y;
    int down;
    int nr;
    int head;
    struct ts_hist hist[NR_SAMPHISTLEN];
};

struct tslib_variance
{
    int delta;
    struct ts_sample last;  // 上一个样点
    struct ts_sample noise; // 噪声（可疑）
    unsigned int flags;
};

/*
    使用五点校准法，将5对LCD坐标跟触摸屏数据传入，计算出7个校准数据
    原来放在校准文件的，移植后全部归入tslib模块
*/
typedef struct
{
    int x[5], xfb[5]; // x,y是触摸屏，xfb，yfb是对应的LCD坐标值
    int y[5], yfb[5];
    unsigned int a[7]; // 校准得到的7个参数
} calibration;

struct tslib_linear
{
    int swap_xy;
    int p_offset;
    int p_mult;
    int p_div;
    int a[7];
};

struct tsdev
{
    int fd;
};

// 函数声明
void dev_touchscreen_init(void);
void dev_touchscreen_open(void);
struct tsdev *ts_open(const char *name, int nonblock);
int ts_read_raw(struct tsdev *ts, struct ts_sample *samp, int nr);
void get_sample(struct tsdev *ts, calibration *cal, int index, int x, int y, char *name);
int perform_calibration(calibration *cal);
void ts_set_cal(calibration *CalSet);
s32 dev_touchscreen_write(struct ts_sample *samp, int nr);
s32 dev_touchscreen_read(struct ts_sample *samp, int nr);
int ts_read(struct tsdev *ts, struct ts_sample *samp, int nr);

#endif