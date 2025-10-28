/**
 * @file tp_interface.c
 * @author Product Application Department
 * @brief  TP 硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup TOUCH TOUCH模块
 * @ingroup Peripherals
 * @{
 */

// 头文件定义
#include "tp_interface.h"
#include "lcd_interface.h"
#include "tp_interface.h"
#include "touch_adc.h"
#include "gt911.h"
#include "st77102.h"
#include "tslib.h"
// 全局变量定义
extern tp_handle_t tp_dev;

// 函数定义

/**
 * @brief 触摸初始化接口函数
 *
 * @param itf 触摸配置参数
 * @return tp_status_t 配置返回值
 */
tp_status_t tp_init(tp_handle_t *itf)
{
    switch (itf->touchtype)
    {
    case GT911:
        itf->width = LCD_DISP_HOR_RES;
        itf->height = LCD_DISP_VER_RES;
        itf->init = gt911_init;
        itf->scan = gt911_scan; // 扫描函数指向GT911触摸屏扫描
        TPLOG_DEBUG("/****GT Scan****/\r\n");
        break;
    
    case ST77102:
        itf->width = LCD_DISP_HOR_RES;
        itf->height = LCD_DISP_VER_RES;
        itf->init = st77102_init;
        itf->scan = st77102_scan; // 扫描函数指向ST77102触摸屏扫描
        TPLOG_DEBUG("/****ST77102 Scan****/\r\n");
        break;

    case TP_ADC:

        itf->init = touch_adc_init;
        itf->scan = touch_adc_sacn;
        break;
    default:
        TPLOG_DEBUG("Nothing init.\n");
        break;
    }

    return itf->init();
}

/**
 * @brief 触摸获取事件状态函数
 *
 * @return uint8_t 是否有触摸事件
 */
uint8_t tp_get_status(void)
{
    struct tsdev *ts;
    struct ts_sample samp;
    tp_dev.scan(0);
    if (tp_dev.touchtype == TP_ADC)
    {
        if (ts_read(ts, &samp, 1) == 1)
        {
            if (samp.pressure != 0)
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    else
    {
        if (tp_dev.sta & TP_PRES_DOWN)
            return 1;
        else
            return 0;
    }
}
/**
 * @brief 触摸获取坐标值
 *
 * @param lastx X轴值
 * @param lasty Y轴值
 */
void tp_getxy(int16_t *lastx, int16_t *lasty)
{
    *lastx = tp_dev.x[0];
    *lasty = tp_dev.y[0];
}

/**
 * @brief 触摸扫描函数
 *
 * @param itf 触摸配置参数
 */
void tp_scan(tp_handle_t *itf)
{
    short last_x, last_y;
    uint8_t t;
    uint8_t maxp = 5;

    switch (itf->touchtype)
    {
    case TP_ADC:
        while (1)
        {
            itf->scan(0);

            delayms(30);
        }

        break;

    case GT911:
        while (1)
        {
            itf->scan(0);

            for (t = 0; t < maxp; t++)
            {
                if ((tp_dev.sta) & (1 << t))
                {
                    if (tp_dev.x[t] < tp_dev.width && tp_dev.y[t] < tp_dev.height)
                    {
                        TPLOG_DEBUG("x[%d]:%d,y[%d]:%d\r\n", t, tp_dev.x[t], t, tp_dev.y[t]);
                    }
                }
            }

            delayms(5);
        }

        break;

    default:
        TPLOG_DEBUG("No write.\n");
        break;
    }
}

/** @} */ // 结束 TOUCH 模块分组
/** @} */ // 结束外设模块分组
