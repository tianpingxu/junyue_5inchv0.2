/**
 * @file tslib.c
 * @author Product application department
 * @brief  tslib电阻触摸算法
 * @version V1.0
 * @date 2025-07-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup TSLIB TSLIB模块
 * @ingroup Peripherals
 * @{
 */

//头文件定义 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "tslib.h"

//全局变量定义 
s32 TpSgd = -2;
#define DEV_TP_QUE_MAX (250)
#define VAR_PENDOWN 0x00000001
#define VAR_LASTVALID 0x00000002
#define VAR_NOISEVALID 0x00000004
#define VAR_SUBMITNOISE 0x00000008

volatile u16 TpQueWindex = 0;
volatile u16 TpQueRindex = 0;

struct ts_sample DevTpSampleQue[DEV_TP_QUE_MAX];
struct tslib_dejitter TsDejitter;
struct tslib_variance TsVariance;
struct tslib_linear TslibLinear;

calibration TsCalSet;
static const unsigned char weight[NR_SAMPHISTLEN - 1][NR_SAMPHISTLEN + 1] =
    {
        /* The last element is pow2(SUM(0..3)) */
        {5, 3, 0, 0, 3}, /* When we have 2 samples ... */
        {8, 5, 3, 0, 4}, /* When we have 3 samples ... */
        {6, 4, 3, 3, 4}, /* When we have 4 samples ... */
};

//函数定义
/**
 * @brief 平方根函数
 *
 * @param x 输入值
 * @return int 输出值
 */
static int sqr(int x)
{
    return x * x;
}

/**
 * @brief 求平均值函数
 *
 * @param djt 采样值
 * @param samp 计算出的平均值
 */
static void average(struct tslib_dejitter *djt, struct ts_sample *samp)
{
    const unsigned char *w;
    int sn = djt->head;
    int i, x = 0, y = 0;
    unsigned int p = 0;

    w = weight[djt->nr - 2];

    for (i = 0; i < djt->nr; i++)
    {
        x += djt->hist[sn].x * w[i];
        y += djt->hist[sn].y * w[i];
        p += djt->hist[sn].p * w[i];
        sn = (sn - 1) & (NR_SAMPHISTLEN - 1);
    }

    samp->x = x >> w[NR_SAMPHISTLEN];
    samp->y = y >> w[NR_SAMPHISTLEN];
    samp->pressure = p >> w[NR_SAMPHISTLEN];
}
/**
 * @brief 电阻触摸参数初始化函数
 * 
 */
void dev_touchscreen_init(void)
{
    TpSgd = -1;
}

/**
 * @brief 电阻触摸校准打开函数
 * 
 */
void dev_touchscreen_open(void)
{
    TpSgd = 0;
    TpQueWindex = TpQueWindex;
}

/**
 * @brief 电阻触摸去抖初始化函数
 * @param  
 * @return 成功
 */
static int mod_dejitter_init(void)
{
    struct tslib_dejitter *djt;

    djt = &TsDejitter;

    memset(djt, 0, sizeof(struct tslib_dejitter));

    djt->delta = 100;
    djt->head = 0;

    djt->delta = sqr(djt->delta);

    return 1;
}
/**
 * @brief 电阻触摸方差初始化函数
 * 
 * @return int 
 */
static int mod_variance_init(void)
{
    struct tslib_variance *var;

    var = &TsVariance;

    if (var == NULL)
        return NULL;

    var->delta = 10;
    var->flags = 0;

    var->delta = sqr(var->delta);

    return 1;
}

/**
 * @brief 电阻触摸校准数据获取函数
 * 
 * @return int 
 */
static int mod_linear_init(void)
{

    struct tslib_linear *lin;

    printf("mod_linear_init\r\n");

    lin = &TslibLinear;

    /*  下面四个数据不会修改？  */
    lin->p_offset = 0;
    lin->p_mult = 1;
    lin->p_div = 1;
    lin->swap_xy = 0;

    /*
     以下内容就是获取系统的校准数据
     */
    lin->a[0] = TsCalSet.a[0];
    lin->a[1] = TsCalSet.a[1];
    lin->a[2] = TsCalSet.a[2];
    lin->a[3] = TsCalSet.a[3];
    lin->a[4] = TsCalSet.a[4];
    lin->a[5] = TsCalSet.a[5];
    lin->a[6] = TsCalSet.a[6];

    printf("mod linear init ok\r\n");

    return 1;
}

/**
 * @brief 电阻触摸打开一个TS设备函数
 * 
 * @param name TS设备名字
 * @param nonblock 长度
 * @return struct tsdev* 
 */
struct tsdev *ts_open(const char *name, int nonblock)
{
    mod_dejitter_init();
    mod_variance_init();
    mod_linear_init();
    return (struct tsdev *)1;
}

/**
 * @brief 电阻触摸读触摸屏样点数据函数
 * 
 * @param samp 采样值
 * @param nr 数量
 * @return int 
 */
static int ts_input_read(struct ts_sample *samp, int nr)
{
    int ret = nr;

    ret = dev_touchscreen_read(samp, nr);

    return ret;
}

/**
 * @brief 电阻触摸校准数据读取函数
 * 
 * @param samp 校准值
 * @param nr 长度
 * @return int 
 */
static int linear_read(struct ts_sample *samp, int nr)
{
    struct tslib_linear *lin = &TslibLinear;

    int ret;
    int xtemp, ytemp;

    // 从下一层读取样点
    ret = ts_input_read(samp, nr);
    // 读到ret个样点
    if (ret >= 0)
    {
        int nr; // 重新申请一个nr变量?有必要也叫nr吗？让人误解

        for (nr = 0; nr < ret; nr++, samp++)
        {
            xtemp = samp->x;
            ytemp = samp->y;

            samp->x = (lin->a[2] +
                       lin->a[0] * xtemp +
                       lin->a[1] * ytemp) /
                      lin->a[6];

            samp->y = (lin->a[5] +
                       lin->a[3] * xtemp +
                       lin->a[4] * ytemp) /
                      lin->a[6];

            samp->pressure = ((samp->pressure + lin->p_offset) * lin->p_mult) / lin->p_div;

            /*XY轴对调*/
            if (lin->swap_xy)
            {
                int tmp = samp->x;
                samp->x = samp->y;
                samp->y = tmp;
            }
        }
    }

    return ret;
}

/**
 * @brief 电阻触摸滤波算法处理函数
 * 
 * @param samp 滤波值
 * @param nr 数量
 * @return int 
 */
static int variance_read(struct ts_sample *samp, int nr)
{
    struct tslib_variance *var = &TsVariance;

    struct ts_sample cur;
    int count = 0, dist;

    while (count < nr)
    {
        /*
            如果N+1、N+2两个点跟N点的距离超出阀值，则可能是快速移动，
            这时会将VAR_SUBMITNOISE标识置起，
            置这个标识是为了下一个循环判断N+1跟N+2之间是否也超出阀值，
        */
        if (var->flags & VAR_SUBMITNOISE)
        {
            cur = var->noise; ////不重新获取新样点，而是将noise中的样点作为当前样点
            var->flags &= ~VAR_SUBMITNOISE;
        }
        else
        {
            /*
            读取一个新样点
            */
            if (linear_read(&cur, 1) < 1)
                return count;
        }

        if (cur.pressure == 0) // 样点压力值为0,
        {
            /* Flush the queue immediately when the pen is just
             * released, otherwise the previous layer will
             * get the pen up notification too late. This
             * will happen if info->next->ops->read() blocks.
             */
            if (var->flags & VAR_PENDOWN)
            {
                /*上一点pressure不为0，会将VAR_PENDOWN 标识置起，
                这次压力为0，说明可能是提笔，可能而已，也可能是个噪声样点
                先保存到noise*/
                var->flags |= VAR_SUBMITNOISE;
                var->noise = cur; // 先将样点保存到noise
            }
            /* Reset the state machine on pen up events. */
            var->flags &= ~(VAR_PENDOWN | VAR_NOISEVALID | VAR_LASTVALID);
            goto acceptsample;
        }
        else
            var->flags |= VAR_PENDOWN;

        if (!(var->flags & VAR_LASTVALID))
        {
            var->last = cur;
            var->flags |= VAR_LASTVALID;
            continue;
        }

        if (var->flags & VAR_PENDOWN)
        {
            /* Compute the distance between last sample and current */
            dist = sqr(cur.x - var->last.x) +
                   sqr(cur.y - var->last.y);

            if (dist > var->delta)
            {
                // uart_printf("%d-",dist);
                /*
                Do we suspect the previous sample was a noise?

                上一个样点如果也超出阈值，就会将VAR_NOISEVALID置位，
                这次的样点又超出阈值，那么就可以认为是快速移动
                */
                if (var->flags & VAR_NOISEVALID)
                {
                    // uart_printf("q-");
                    /* Two "noises": it's just a quick pen movement */
                    samp[count++] = var->last = var->noise;

                    var->flags = (var->flags & ~VAR_NOISEVALID) |
                                 VAR_SUBMITNOISE;
                }
                else
                {
                    /*第一次超出阈值，置位标志*/
                    var->flags |= VAR_NOISEVALID;
                }
                /* The pen jumped too far, maybe it's a noise ... */
                var->noise = cur;
                continue;
            }
            else
            {
                // uart_printf("g ");
                var->flags &= ~VAR_NOISEVALID;
            }
        }

    acceptsample:
        samp[count++] = var->last;
        var->last = cur;
    }

    return count;
}

/**
 * @brief 电阻触摸去噪算法处理函数
 * @param samp 采样值
 * @param nr 数量
 * @return 
 */
static int dejitter_read(struct ts_sample *samp, int nr)
{
    struct tslib_dejitter *djt = &TsDejitter;
    struct ts_sample *s;
    int count = 0, ret;

    ret = variance_read(samp, nr);

    for (s = samp; ret > 0; s++, ret--)
    {
        if (s->pressure == 0)
        {
            /*
             * Pen was released. Reset the state and
             * forget all history events.
             */
            djt->nr = 0;
            samp[count++] = *s;
            continue;
        }

        /* If the pen moves too fast, reset the backlog. */
        if (djt->nr)
        {
            int prev = (djt->head - 1) & (NR_SAMPHISTLEN - 1);
            if (sqr(s->x - djt->hist[prev].x) +
                    sqr(s->y - djt->hist[prev].y) >
                djt->delta)
            {
                djt->nr = 0;
            }
        }

        djt->hist[djt->head].x = s->x;
        djt->hist[djt->head].y = s->y;
        djt->hist[djt->head].p = s->pressure;

        if (djt->nr < NR_SAMPHISTLEN)
            djt->nr++;

        /* We'll pass through the very first sample since
         * we can't average it (no history yet).
         */
        if (djt->nr == 1)
            samp[count] = *s;
        else
        {
            average(djt, samp + count);
            // samp [count].tv = s->tv;
        }
        count++;
        /*
        巧妙的处理环形缓冲索引循环问题，不过只有当缓冲个数是2的N次方是才可以这样，
        这种方法的根本原理是通过与操作清掉进位。
        */
        djt->head = (djt->head + 1) & (NR_SAMPHISTLEN - 1);
    }

    return count;
}

/**
 * @brief 电阻触摸直接读样点接口，样点不经过TSLIB处理函数
 * 
 * @param ts TS设备名字
 * @param samp 采样值
 * @param nr 数量
 * @return int 
 */
int ts_read_raw(struct tsdev *ts, struct ts_sample *samp, int nr)
{
    int result = ts_input_read(samp, nr);

    return result;
}

/**
 * @brief 电阻触摸读取去噪处理后数据
 * 
 * @param ts TS设备名字
 * @param samp 采样值
 * @param nr 数量
 * @return int 
 */
int ts_read(struct tsdev *ts, struct ts_sample *samp, int nr)
{
    int result;

    result = dejitter_read(samp, nr);

    return result;
}

/**
 * @brief 电阻触摸设置校准参数
 * 
 * @param CalSet 校准参数
 */
void ts_set_cal(calibration *CalSet)
{
    memcpy(&TsCalSet, CalSet, sizeof(calibration));
}

/**
 * @brief 电阻触摸采样点记录函数
 * 
 * @param samp 采样值
 * @param nr 数量
 * @return s32 
 */
s32 dev_touchscreen_write(struct ts_sample *samp, int nr)
{
    int index;
    struct ts_sample *p;

    index = 0;
    while (1)
    {
        if (index >= nr)
            break;
        p = samp + index;

        DevTpSampleQue[TpQueWindex].pressure = p->pressure;
        DevTpSampleQue[TpQueWindex].x = p->x;
        DevTpSampleQue[TpQueWindex].y = p->y;
        TpQueWindex++;
        if (TpQueWindex >= DEV_TP_QUE_MAX)
            TpQueWindex = 0;

        index++;
    }

    return index;
}


/**
 * @brief 电阻触摸读取坐标函数
 * 
 * @param samp 采样值
 * @param nr 数量
 * @return s32 
 */
s32 dev_touchscreen_read(struct ts_sample *samp, int nr)
{
    int i = 0;

    while (1)
    {
        if (i >= nr)
            break;

        if (TpQueWindex == TpQueRindex)
            break;

        samp->pressure = DevTpSampleQue[TpQueRindex].pressure;
        samp->x = DevTpSampleQue[TpQueRindex].x;
        samp->y = DevTpSampleQue[TpQueRindex].y;

        TpQueRindex++;
        if (TpQueRindex >= DEV_TP_QUE_MAX)
            TpQueRindex = 0;

        i++;
    }

    return i;
}


/** @} */  // 结束 TSLIB 模块分组
/** @} */  // 结束外设模块分组