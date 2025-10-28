/**
 * @file ts_calibrate.c
 * @author Product application department
 * @brief  电阻触摸计算函数
 * @version V1.0
 * @date 2025-07-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件定义
#include "tslib.h"
#include <stdio.h>
#include <stdlib.h>

// 函数定义

/**
 * @brief 按x坐标进行排序函数
 *
 * @return int
 */
static int sort_by_x(const void *a, const void *b)
{
    return (((struct ts_sample *)a)->x - ((struct ts_sample *)b)->x);
}

/**
 * @brief 按y坐标进行排序函数
 *
 * @return int
 */
static int sort_by_y(const void *a, const void *b)
{
    return (((struct ts_sample *)a)->y - ((struct ts_sample *)b)->y);
}

/**
 * @brief 校准时获取样点函数
 *
 * @param ts TS设备名字
 * @param x x轴坐标
 * @param y y轴坐标
 * @return int
 */
int getxy(struct tsdev *ts, int *x, int *y)
{

#define MAX_SAMPLES 128

    struct ts_sample samp[MAX_SAMPLES];
    int index, middle;
    int ret;

    /*校准的时候直接使用raw读，也就是没有经过处理的原始数据*/
    samp[0].pressure = 0;

    do
    {
        ret = ts_read_raw(ts, &samp[0], 1);
        if (ret < 0)
        {
            return -1;
        }
        else if (ret == 1)
        {
            if (samp[0].pressure > 0)
            {
                break;
            }
        }
    } while (1);

    /* Now collect up to MAX_SAMPLES touches into the samp array. */
    index = 0;
    do
    {
        ret = ts_read_raw(ts, &samp[index], 1);

        if (ret < 0)
        {
            return -1;
        }
        else if (ret == 1)
        {

            if (samp[index].pressure <= 0)
            {
                break;
            }

            if (index < MAX_SAMPLES - 1)
                index++; // 读到数据了才增加索引
        }
        /*
            ，有可能读不到数据，转换速度不够快
            修改为，如果读不到数据，等.
        */
    } while (1);

    /*
     * At this point, we have samples in indices zero to (index-1)
     * which means that we have (index) number of samples.  We want
     * to calculate the median of the samples so that wild outliers
     * don't skew the result.  First off, let's assume that arrays
     * are one-based instead of zero-based.  If this were the case
     * and index was odd, we would need sample number ((index+1)/2)
     * of a sorted array; if index was even, we would need the
     * average of sample number (index/2) and sample number
     * ((index/2)+1).  To turn this into something useful for the
     * real world, we just need to subtract one off of the sample
     * numbers.  So for when index is odd, we need sample number
     * (((index+1)/2)-1).  Due to integer division truncation, we
     * can simplify this to just (index/2).  When index is even, we
     * need the average of sample number ((index/2)-1) and sample
     * number (index/2).  Calculate (index/2) now and we'll handle
     * the even odd stuff after we sort.
     */
    middle = index / 2;
    if (x)
    {
        /*   使用qsort 对数据排序*/
        qsort(samp, index, sizeof(struct ts_sample), sort_by_x);
        if (index & 1)
            *x = samp[middle].x;
        else
            *x = (samp[middle - 1].x + samp[middle].x) / 2;
    }

    if (y)
    {
        qsort(samp, index, sizeof(struct ts_sample), sort_by_y);
        if (index & 1)
            *y = samp[middle].y;
        else
            *y = (samp[middle - 1].y + samp[middle].y) / 2;
    }

    return 0;
}

/**
 * @brief 获取采样点
 *
 * @param ts TS设备名字
 * @param cal 采样点坐标
 * @param index
 * @param x
 * @param y
 * @param name
 */
void get_sample(struct tsdev *ts, calibration *cal, int index, int x, int y, char *name)
{
    getxy(ts, &cal->x[index], &cal->y[index]);

    cal->xfb[index] = x;
    cal->yfb[index] = y;
}
/**
 * @brief 进行校准计算函数
 *
 * @param cal 计算参数
 * @return int
 */

int perform_calibration(calibration *cal)
{
    int j;
    float n, x, y, x2, y2, xy, z, zx, zy;
    float det, det1, det2, det3;
    float scaling = 65536.0;

    n = x = y = x2 = y2 = xy = 0;
    for (j = 0; j < 5; j++)
    {
        if ((cal->x[j] > 10000) || (cal->y[j] > 10000))
        {
            return -1;
        }
        n += 1.0;
        x += (float)cal->x[j];
        y += (float)cal->y[j];
        x2 += (float)(cal->x[j] * cal->x[j]);
        y2 += (float)(cal->y[j] * cal->y[j]);
        xy += (float)(cal->x[j] * cal->y[j]);
    }

    det = n * (x2 * y2 - xy * xy) + x * (xy * y - x * y2) + y * (x * xy - y * x2);
    if (det < 0.1 && det > -0.1)
    {

        return -1;
    }

    z = zx = zy = 0;
    for (j = 0; j < 5; j++)
    {
        z += (float)cal->xfb[j];
        zx += (float)(cal->xfb[j] * cal->x[j]);
        zy += (float)(cal->xfb[j] * cal->y[j]);
    }

    det1 = n * (zx * y2 - xy * zy) + z * (xy * y - x * y2) + y * (x * zy - y * zx);
    det2 = n * (x2 * zy - zx * xy) + x * (zx * y - x * zy) + z * (x * xy - y * x2);
    det3 = z * (x2 * y2 - xy * xy) + x * (xy * zy - zx * y2) + y * (zx * xy - zy * x2);
    cal->a[0] = (int)((det1 / det) * scaling);
    cal->a[1] = (int)((det2 / det) * scaling);
    cal->a[2] = (int)((det3 / det) * scaling);

    z = zx = zy = 0;
    for (j = 0; j < 5; j++)
    {
        z += (float)cal->yfb[j];
        zx += (float)(cal->yfb[j] * cal->x[j]);
        zy += (float)(cal->yfb[j] * cal->y[j]);
    }

    det1 = n * (zx * y2 - xy * zy) + z * (xy * y - x * y2) + y * (x * zy - y * zx);
    det2 = n * (x2 * zy - zx * xy) + x * (zx * y - x * zy) + z * (x * xy - y * x2);
    det3 = z * (x2 * y2 - xy * xy) + x * (xy * zy - zx * y2) + y * (zx * xy - zy * x2);
    cal->a[3] = (int)((det1 / det) * scaling);
    cal->a[4] = (int)((det2 / det) * scaling);
    cal->a[5] = (int)((det3 / det) * scaling);
    cal->a[6] = (int)scaling;

    return 0;
}
