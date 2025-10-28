/**
 * @file touch_adc.c
 * @author Product application department
 * @brief  ADC电阻触摸驱动
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
 * @defgroup TOUCHADC TOUCHADC模块
 * @ingroup Peripherals
 * @{
 */

// 头文件定义
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "tp_interface.h"
#include "tslib.h"
#include "pinswap_drv.h"
#include "pit32_hal.h"
#include "lcdc_drv.h"
#include "touch_adc.h"
#include "rgb_lcd.h"
#include "color_def.h"
#include "ssi_hal.h"
#include "adc_hal.h"
#include "common.h"

// 变量定义
calibration cal;
#define TSJUST_LIMIT_L 0.9
#define TSJUST_LIMIT_H 1.1
#define TS_ADJUST_DATA_ADDR 0x101FF000 // 存放校准数据地址，可修改
#define READ_TIMES 10                  // 读取次数
#define LOST_VAL 2                     // 丢弃值
#define DEV_PENDOWN_GATE (266)         // 校准下限值
#define DEV_PENUP_GATE (300)           // 校准上限值
#define TOUCH_DRAW_ADDR 0x1C000000     // 电阻触摸校准刷图地址

extern tp_handle_t tp_dev;
volatile uint16_t X_Buff[10];
volatile uint16_t Y_Buff[10];
static struct tsdev *ts;
static struct ts_sample samp;
hal_pit32_handler_t hal_adcpit32;
// 函数定义

/**
 * @brief 电阻触摸定时器中断处理函数
 *
 */
void ts_pit32_1_irqhandler(void)
{
    static uint16_t rdata, temp = 0;
    static int pendownup = 1;
    struct ts_sample tss;

    rdata = touch_r_get_value();

    if (rdata < DEV_PENDOWN_GATE)
    {
        // pen down
        tss.pressure = rdata;
        tss.x = touch_x_get_value();
        tss.y = touch_y_get_value();

        dev_touchscreen_write(&tss, 1);
        pendownup = 0;
    }
    else if (rdata > DEV_PENUP_GATE)
    {
        if (pendownup == 0)
        {
            pendownup = 1;
            // pen up
            tss.pressure = 0;
            tss.x = 0xffff;
            tss.y = 0xffff;
            dev_touchscreen_write(&tss, 1);
        }
    }
}

/**
 * @brief 电阻触摸定时器初始化
 *
 * @param time 定时时间，单位ms
 */
void touch_pit_init(uint32_t time)
{
    double time_cnt = time * 0.001;
    hal_adcpit32.instance = PIT1;
    hal_adcpit32.init.counter = hal_pit32_calc_counter(g_ips_clk, PIT32_CLK_DIV_32, time_cnt);
    hal_adcpit32.init.enable_ie = 1;
    hal_adcpit32.init.reload = 1;
    hal_adcpit32.init.prescaler = PIT32_CLK_DIV_32;
    hal_adcpit32.init.run_at_debug = 1;
    hal_adcpit32.init.run_at_doze = 1;
    hal_adcpit32.init.update_cnt = 1;
    hal_adcpit32.callback = ts_pit32_1_irqhandler;
    hal_pit32_init(&hal_adcpit32);
}

/**
 * @brief 电阻触摸定时器停止函数
 *
 */
void touch_pit_stop(void)
{
    drv_pit32_cmd(PIT1, DISABLE);
}

/**
 * @brief 底图纯色刷图接口
 *
 * @param buf_addr 刷图buffer地址
 * @param width 屏幕宽度
 * @param height 屏幕高度
 * @param Color 颜色
 */
void color_rgb565_init(unsigned int buf_addr, unsigned int width, unsigned int height, unsigned short Color)
{
    unsigned int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            writew((buf_addr + (i * width + j) * 2), Color);
    }
}

/**
 * @brief 小窗刷图接口
 *
 * @param buf_addr 刷图buffer地址
 * @param width 屏幕宽度
 * @param height 屏幕高度
 * @param x 窗口x轴位置
 * @param y 窗口y轴位置
 * @param size 窗口大小
 * @param Color 颜色
 */
void touch_draw_point(int buf_addr, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int size, unsigned short Color)
{
    unsigned int i, j;

    for (i = (y - size); i < (y + size); i++)
    {
        for (j = (x - size); j < (x + size); j++)
            writew((buf_addr + (i * width + j) * 2), Color);
    }
}
/**
 * @brief 电阻触摸校准刷图函数
 * @param x  x轴地址
 * @param y  y轴地址
 * @param colidx 底图
 * @param colidy 前景图
 */
void put_cross(int x, int y, unsigned short colidx, unsigned short colidy)
{
    color_rgb565_init(TOUCH_DRAW_ADDR, LCD_DISP_HOR_RES, LCD_DISP_VER_RES, colidx);
    touch_draw_point(TOUCH_DRAW_ADDR, LCD_DISP_HOR_RES, LCD_DISP_VER_RES, x, y, 10, colidy);
    LCD_RGB_Color_Fill(0, 0, LCD_DISP_HOR_RES, LCD_DISP_VER_RES, (uint16_t *)(TOUCH_DRAW_ADDR));
}

/**
 * @brief 电阻触摸保存校准值函数
 *
 */
void ts_save_calidata(void)
{
    unsigned int temp[8];
    uint8_t read[32];
    for (int i = 0; i < 7; i++)
    {
        temp[i] = cal.a[i];
        printf("temp[%d] = %d \r\n", i, temp[i]);
    }
    temp[7] = 0x5A;
    printf("temp[7] = %d \r\n", temp[7]);

    hal_ssi_flash_sector_erase(TS_ADJUST_DATA_ADDR);

    hal_ssi_flash_program(TS_ADJUST_DATA_ADDR, (uint8_t *)temp, 8 * 4);
    hal_ssi_flash_read(TS_ADJUST_DATA_ADDR, read, 32);
    for (uint8_t i = 0; i < 32; i++)
        printf("read[%d]=0x%0x\r\n", i, read[i]);
    printf("program over\r\n");
}

/**
 * @brief 电阻触摸校准函数
 * @param xres x轴长度
 * @param yres y轴长度
 * @return 成功/失败
 */
int ts_calibrate(int xres, int yres)
{
    struct tsdev *ts;
    char *tsdevice = NULL;
    int i;

    printf(" main ts calibrate!\r\n");

    ts = ts_open(tsdevice, 0);
    if (!ts)
    {
        return -1;
    }

    /*下面开始进入校准*/
    /*刷LCD背景*/
    printf("xres = %d, yres = %d\n", xres, yres);

    int ret = 1;
    int ca_X[5], ca_Y[5];
    do
    {
        //----校准过程，获取5个点的数据-------
        put_cross(50, 50, RGB565_GREEN, RGB565_WHITE);
        get_sample(ts, &cal, 0, 50, 50, "Top left");
        ca_X[0] = cal.x[0];
        ca_Y[0] = cal.y[0];
        printf("\r\n: CAX = %4d CAY = %4d\r\n", ca_X[0], ca_Y[0]);
        printf("-----------------------Top left finish\r\n");

        put_cross(xres - 50, 50, RGB565_GREEN, RGB565_WHITE);
        get_sample(ts, &cal, 1, xres - 50, 50, "Top right");
        ca_X[1] = cal.x[1];
        ca_Y[1] = cal.y[1];
        printf("\r\n: CAX = %4d CAY = %4d\r\n", ca_X[1], ca_Y[1]);
        printf("-----------------------Top right finish\r\n");

        put_cross(xres - 50, yres - 50, RGB565_GREEN, RGB565_WHITE);
        get_sample(ts, &cal, 2, xres - 50, yres - 50, "Bot right");
        ca_X[2] = cal.x[2];
        ca_Y[2] = cal.y[2];
        printf("\r\n: CAX = %4d CAY = %4d\r\n", ca_X[2], ca_Y[2]);
        printf("-----------------------Bot right finish\r\n");

        put_cross(50, yres - 50, RGB565_GREEN, RGB565_WHITE);
        get_sample(ts, &cal, 3, 50, yres - 50, "Bot left");
        ca_X[3] = cal.x[3];
        ca_Y[3] = cal.y[3];
        printf("\r\n: CAX = %4d CAY = %4d\r\n", ca_X[3], ca_Y[3]);
        printf("-----------------------Bot left finish\r\n");

        put_cross(xres / 2, yres / 2, RGB565_GREEN, RGB565_WHITE);
        get_sample(ts, &cal, 4, xres / 2, yres / 2, "Center");
        ca_X[4] = cal.x[4];
        ca_Y[4] = cal.y[4];
        printf("\r\n: CAX = %4d CAY = %4d\r\n", ca_X[4], ca_Y[4]);
        printf("-----------------------Center\r\n");

        int tem1, tem2;
        double d1, d2, d3, d4;
        double fac, fac1, fac2, fac3;
        tem1 = abs(ca_X[1] - ca_X[0]);          // x1-x2
        tem2 = abs(ca_Y[1] - ca_Y[0]);          // y1-y2
        d1 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到1,2的距离
        printf("tem1 = %d, tem2 = %d, d1= %f\r\n", tem1, tem2, d1);

        tem1 = abs(ca_X[3] - ca_X[2]);          // x3-x4
        tem2 = abs(ca_Y[3] - ca_Y[2]);          // y3-y4
        d2 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到3,4的距离
        printf("tem1 = %d, tem2 = %d, d2= %f\r\n", tem1, tem2, d2);
        fac = (float)(d1 / d2);
        printf("fac = %f\r\n", fac);

        if (fac < TSJUST_LIMIT_L || fac > TSJUST_LIMIT_H || d1 == 0 || d2 == 0) // 不合格
        {
            printf("1-2/3-4 incorrect\r\n");
            continue;
        }

        tem1 = abs(ca_X[3] - ca_X[2]);          // x1-x3
        tem2 = abs(ca_Y[3] - ca_Y[2]);          // y1-y3
        d1 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到1,3的距离
        printf("tem1 = %d, tem2 = %d, d1= %f\r\n", tem1, tem2, d1);
        tem1 = abs(ca_X[3] - ca_X[2]);          // x2-x4
        tem2 = abs(ca_Y[3] - ca_Y[2]);          // y2-y4
        d2 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到2,4的距离
        printf("tem1 = %d, tem2 = %d, d2= %f\r\n", tem1, tem2, d2);
        fac = (float)(d1 / d2);
        printf("fac = %f\r\n", fac);

        if (fac < TSJUST_LIMIT_L || fac > TSJUST_LIMIT_H) // 不合格
        {
            printf("1-3/2-4 incorrect\r\n");
            continue;
        } // 正确了

        // 对角线相等
        tem1 = abs(ca_X[3] - ca_X[0]);          // x1-x3
        tem2 = abs(ca_Y[3] - ca_Y[0]);          // y1-y3
        d1 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到1,4的距离
        printf("tem1 = %d, tem2 = %d, d1= %f\r\n", tem1, tem2, d1);
        tem1 = abs(ca_X[2] - ca_X[1]);          // x2-x4
        tem2 = abs(ca_Y[2] - ca_Y[1]);          // y2-y4
        d2 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到2,3的距离
        printf("tem1 = %d, tem2 = %d, d2= %f\r\n", tem1, tem2, d2);

        fac = (float)(d1 / d2);
        printf("fac = %f\r\n", fac);

        if (fac < TSJUST_LIMIT_L || fac > TSJUST_LIMIT_H) // 不合格
        {
            printf("1-4/2-3 incorrect\r\n");
            continue;
        } // 正确了

        // 4对角线相等
        tem1 = abs(ca_X[4] - ca_X[0]);          // x1-x3
        tem2 = abs(ca_Y[4] - ca_Y[0]);          // y1-y3
        d1 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到1,5的距离
        printf("tem1 = %d, tem2 = %d, d1= %f\r\n", tem1, tem2, d1);
        tem1 = abs(ca_X[4] - ca_X[1]);          // x2-x4
        tem2 = abs(ca_Y[4] - ca_Y[1]);          // y2-y4
        d2 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到2,5的距离
        printf("tem1 = %d, tem2 = %d, d2= %f\r\n", tem1, tem2, d2);
        tem1 = abs(ca_X[4] - ca_X[2]);          // x1-x3
        tem2 = abs(ca_Y[4] - ca_Y[2]);          // y1-y3
        d3 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到3,5的距离
        printf("tem1 = %d, tem2 = %d, d1= %f\r\n", tem1, tem2, d1);
        tem1 = abs(ca_X[4] - ca_X[3]);          // x2-x4
        tem2 = abs(ca_Y[4] - ca_Y[3]);          // y2-y4
        d4 = sqrt(pow(tem1, 2) + pow(tem2, 2)); // 得到4,5的距离
        printf("tem1 = %d, tem2 = %d, d2= %f\r\n", tem1, tem2, d2);

        fac = (float)(d1 / d2);
        printf("fac = %f\r\n", fac);
        fac1 = (float)(d2 / d3);
        printf("fac = %f\r\n", fac1);
        fac2 = (float)(d3 / d4);
        printf("fac = %f\r\n", fac2);
        fac3 = (float)(d4 / d1);
        printf("fac = %f\r\n", fac3);

        if (((fac < TSJUST_LIMIT_L || fac > TSJUST_LIMIT_H)) || ((fac1 < TSJUST_LIMIT_L || fac1 > TSJUST_LIMIT_H)) || ((fac2 < TSJUST_LIMIT_L || fac2 > TSJUST_LIMIT_H)) || ((fac3 < TSJUST_LIMIT_L || fac3 > TSJUST_LIMIT_H))) // 不合格
        {
            printf("1-5/2-5/3-5/4-5 incorrect\r\n");
            continue;
        } // 正确了

        ret = 0;

    } while (ret);
    touch_pit_stop();

    if (0 == perform_calibration(&cal))
    {
        // 校准后得到的数据
        printf("Calibration constants: ");
        for (i = 0; i < 7; i++)
            printf("%d ", cal.a[i]);
        printf("\n");

        //		//PROGRAM EFLASH
        //		put_cross(xres / 2, yres / 2, WHITE_565,WHITE_565);
        ts_save_calidata();
        printf("calibration data saved\r\n");
    }
    else
    {
        printf("Calibration failed.\n");
        i = -1;
    }

    return i;
}
/**
 * @brief 是否需要校准，通过wakeup脚是否拉低判断，客户可自己修改
 * @param
 */
void touch_adc_calibrate_determine(void)
{
    uint8_t pin_val;

    SwitchPinFunction(WAKEUP_FUN, EPORT6_PIN3_FUN);
    hal_eport_input(EPORT6, EPORT6_PIN3, PS_PULL_UP);
    pin_val = hal_eport_readpinslevel(EPORT6, EPORT6_PIN3);
    if (pin_val == BIT_SET)
    {
        touch_pit_init(30);
        while (1)
        {
            uint8_t ret = ts_calibrate(LCD_DISP_HOR_RES, LCD_DISP_VER_RES);
            printf("calibratie result = %d\r\n", ret);
            if (ret > 0)
                break;
        }
        touch_pit_stop();
    }
}

/**
 * @brief 电阻触摸获取校准数据函数
 * @param CalSet 校准数据
 * @return
 */
int touch_get_calidata(calibration *CalSet)
{
    uint32_t read[8] = {0};
    uint8_t adjust_flg;

    hal_ssi_flash_read(TS_ADJUST_DATA_ADDR, (uint8_t *)read, 8 * 4);

    adjust_flg = read[7];

    if (adjust_flg == 0X5A) // 触摸屏已经校准过了
    {
        for (int i = 0; i < 7; i++)
        {
            CalSet->a[i] = read[i];
            printf("CalSet[%d] = %d \r\n", i, CalSet->a[i]);
        }
        return 1;
    }
    return 0;
}
/**
 * @brief 电阻触摸tslib打开函数
 *
 * @return struct tsdev*
 */
struct tsdev *ts_open_module(void)
{
    struct tsdev *ts;
    char *tsdevice = NULL;
    unsigned int i;
    uint8_t ret = touch_get_calidata(&cal);

    if (ret == 0)
    {
        printf("no calibration\r\n");
        touch_pit_init(25);
        while (1)
        {
            ret = ts_calibrate(LCD_DISP_HOR_RES, LCD_DISP_VER_RES);
            printf("calibratie result = %d\r\n", ret);
            if (ret > 0)
                break;
        }
    }
    /*先配置校准参数，再调ts_open*/
    ts_set_cal(&cal);

    printf("env Calibration constants: ");
    for (i = 0; i < 7; i++)
        printf("%d ", cal.a[i]);
    printf("\n");

    ts = ts_open(tsdevice, 0);

    if (!ts)
    {
        return NULL;
    }

    return ts;
}
/**
 * @brief 电阻触摸adc获取函数
 *
 * @param channel_1 adc通道
 * @return uint16_t
 */
static uint16_t adc_voltage_get(uint8_t channel_1)
{

    uint32_t resVC;
    uint16_t DATA;
    adc_init_t adc;

    adc.channel = channel_1;

    adc.align = ADC_RIGHT_ALIGN;
    adc.clk_div = ADC_CLK_DIV_4;
    adc.conv = ADC_CONTINUOUS_CONV_MODE;
    adc.overrun = ADC_OVERRUN_MODE_LAST;
    adc.resolution = ADC_RESOLUTION_12BIT;
    adc.smp_time = 0x20;
    adc.stab_time = 0x20;
    adc.trigger_mode = HAL_ADC_TRIGGER_SOFT;
    adc.vref = ADC_EXTERNAL_VREF;
    adc.int_kind = 0;
    hal_adc_init(&adc);
    hal_adc_moduleen(TRUE);

    DATA = hal_adc_getconversionvalue();

    resVC = 330 * DATA / 4095;

    hal_adc_moduleen(FALSE);
    drv_adc_channel_disselect(channel_1);
    return resVC;
}
/**
 * @brief 电阻触摸获取x轴电压值函数
 *
 * @return uint16_t 电压值
 */
uint16_t touch_x_get_value(void)
{
    uint16_t xdata = 0;

    hal_eport_input(GINT_YD_PORT, GINT_YD, PS_PULL_NULL);
    hal_eport_input(GINT_YU_PORT, GINT_YU, PS_PULL_DOWN);
    hal_eport_output(GINT_XL_PORT, GINT_XL);
    hal_eport_output(GINT_XR_PORT, GINT_XR);
    hal_eport_writepinlevel(GINT_XR_PORT, GINT_XR, GPIO_LOW);
    hal_eport_writepinlevel(GINT_XL_PORT, GINT_XL, GPIO_HIGH);

    xdata = adc_voltage_get(ADC_CH_YD);

    return xdata;
}
/**
 * @brief 电阻触摸获取y轴电压值函数
 *
 * @return uint16_t 电压值
 */
uint16_t touch_y_get_value(void)
{
    uint16_t ydata = 0;
    hal_eport_input(GINT_XR_PORT, GINT_XR, PS_PULL_NULL);
    hal_eport_input(GINT_XL_PORT, GINT_XL, PS_PULL_DOWN);
    hal_eport_output(GINT_YD_PORT, GINT_YD);
    hal_eport_output(GINT_YU_PORT, GINT_YU);
    hal_eport_writepinlevel(GINT_YU_PORT, GINT_YU, GPIO_LOW);
    hal_eport_writepinlevel(GINT_YD_PORT, GINT_YD, GPIO_HIGH);

    ydata = adc_voltage_get(ADC_CH_XR);

    return ydata;
}
/**
 * @brief 电阻触摸获取x轴y轴电压差函数
 *
 * @return uint16_t 电压值
 */
uint16_t touch_r_get_value(void)
{
    uint16_t xdata = 0, ydata = 0;
    uint16_t rdata = 0;
    hal_eport_input(GINT_XR_PORT, GINT_XR, PS_PULL_NULL);
    hal_eport_input(GINT_YD_PORT, GINT_YD, PS_PULL_NULL);
    hal_eport_output(GINT_YU_PORT, GINT_YU);
    hal_eport_output(GINT_XL_PORT, GINT_XL);
    //	IOCTRL->UARTCR &= ~(1<<17);
    hal_eport_writepinlevel(GINT_XL_PORT, GINT_XL, GPIO_LOW);
    hal_eport_writepinlevel(GINT_YU_PORT, GINT_YU, GPIO_HIGH);
    xdata = adc_voltage_get(ADC_CH_YD);
    ydata = adc_voltage_get(ADC_CH_XR);

    rdata = xdata - ydata;
    // printf("xdata=%d,ydata=%d,rdata=%d\r\n",xdata,ydata,rdata);
    return rdata;
}

/**
 * @brief 电阻触摸获取x/y轴电压值函数
 * @param CMD x/y轴
 * @return 电压值
 */
static uint16_t tp_read_ad(uint8_t CMD)
{
    uint16_t data;

    if (CMD)
        data = touch_x_get_value();
    else
        data = touch_y_get_value();

    return data;
}

/**
 * @brief 电阻触摸多次获取x/y轴电压值函数
 * @param CMD x/y轴
 * @return 电压值
 */
static uint16_t tp_read_xoy(uint8_t xy)
{
    uint32_t i, j;
    uint32_t buf[READ_TIMES];
    uint32_t sum = 0;
    uint32_t temp;

    for (i = 0; i < READ_TIMES; i++)
        buf[i] = tp_read_ad(xy);

    for (i = 0; i < READ_TIMES - 1; i++) // 排序
    {
        for (j = i + 1; j < READ_TIMES; j++)
        {
            if (buf[i] > buf[j]) // 升序排列
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    sum = 0;

    for (i = LOST_VAL; i < READ_TIMES; i++)
        sum += buf[i];

    temp = sum / (READ_TIMES - LOST_VAL);
    return temp;
}
/**
 * @brief 电阻触摸获取x/y轴电压值函数
 * @param CMD x/y轴
 * @return 电压值
 */
static uint8_t tp_read_xy(volatile uint16_t *x, volatile uint16_t *y)
{
    uint16_t xtemp, ytemp;

    xtemp = tp_read_xoy(1);
    ytemp = tp_read_xoy(0);

    *x = xtemp;
    *y = ytemp;
    return 1; // 读数成功
}

/**
 * @brief 电阻触摸初始化函数
 * @param
 * @return tp_status_t
 */
tp_status_t touch_adc_init(void)
{
    // touch_pit_init(30);
    SwitchPinFunction(UART3_RX_FUN, EPORT2_PIN7_FUN);
    hal_eport_output(EPORT2, EPORT2_PIN7);
    hal_eport_writepinlevel(EPORT2, EPORT2_PIN7, GPIO_HIGH);
    RGBLCD_Init(RGB_1024600);
    SwitchPinFunction(UART4_RX_FUN, EPORT3_PIN7_FUN);
    SwitchPinFunction(UART4_TX_FUN, EPORT3_PIN6_FUN);
    SwitchPinFunction(UART5_RX_FUN, EPORT4_PIN7_FUN);
    SwitchPinFunction(UART5_TX_FUN, EPORT4_PIN6_FUN);

    dev_touchscreen_init();
    dev_touchscreen_open();
    touch_adc_calibrate_determine();
    ts_open_module();
    touch_pit_init(30);
    return TP_OK;
}
/**
 * @brief 电阻触摸扫描函数
 *
 * @param tp
 * @return uint8_t
 */

uint8_t touch_adc_sacn(uint8_t mode)
{
    struct tsdev *ts;
    struct ts_sample samp;
    int ret;
    int temp;

    ret = ts_read(ts, &samp, 1);
    if (ret == 1)
    {
        if (samp.pressure != 0)
        {
            printf("pen down\r\n");
            printf(">%d %d %d-\r\n", samp.pressure, samp.x, samp.y);
        }
    }
    return 0;
}

/** @} */  // 结束 TOUCHADC 模块分组
/** @} */  // 结束外设模块分组