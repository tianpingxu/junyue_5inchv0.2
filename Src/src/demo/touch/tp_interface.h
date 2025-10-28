/**
 * @file tp_interface.h
 * @author Product Application Department
 * @brief  TP 硬件抽象层头文件
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

#ifndef _TP_INTERFACE_H
#define _TP_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif
    
// 头文件定义
#include "delay.h"
#include "eport_hal.h"
#include "adc_drv.h"
// 全局变量定义
#define TPLOG_DEBUG(...) printf(__VA_ARGS__)
#define CT_MAX_TOUCH 5    // 电容屏支持的点数,固定为5点
#define TP_PRES_DOWN 0x80 // 触屏被按下
#define TP_CATH_PRES 0x40 // 有按键按下了

#define TOUCH_ADC6LINE_USE 0
#define TOUCH_ADC4LINE_USE 1

#define TP_INTERFACE  ST77102
#define TOUCH_I2C    I2C1  
#define TOUCH_CPT_PORT_INT EPORT3
#define TOUCH_CPT_PIN_INT EPORT3_PIN6
#define TOUCH_CPT_PORT_RST EPORT3
#define TOUCH_CPT_PIN_RST EPORT3_PIN7

#define GINT_XR_PORT   EPORT4
#define GINT_XR   EPORT4_PIN7

#define GINT_YU_PORT EPORT3
#define GINT_YU   EPORT3_PIN7
 
#define GINT_XL_PORT EPORT3   
#define GINT_XL EPORT3_PIN6

#define GINT_YD_PORT EPORT4
#define GINT_YD  EPORT4_PIN6


#define ADC_CH_YD ADC_IN6 
#define ADC_CH_XR ADC_IN2 
/**
 * @brief TP 接口类型枚举定义
 *
 */
typedef enum
{
    TPADC = 0,
    TPI2C = 1
} tp_interface_t;

/**
 * @brief TP 驱动芯片枚举定义
 *
 */
typedef enum
{
    GT911 = 0,
	ST77102 = 1,
    TP_ADC = 2

} tp_driveric_t;

/**
 * @brief TP 状态给返回枚举定义
 *
 */
typedef enum
{
    TP_OK = 0,
    TP_ERR = 1,
    TP_WARN = 2
} tp_status_t;

/**
 * @brief TP 配置结构体定义
 *
 */
typedef struct
{
    tp_status_t (*init)(void);
    uint8_t (*scan)(uint8_t);
    void (*calibrate)(void);
    uint16_t x[CT_MAX_TOUCH];
    uint16_t y[CT_MAX_TOUCH];
    uint16_t sta;
    float xfac;
    float yfac;
    short xoff;
    short yoff;
    uint8_t touchtype;
    uint16_t width;
    uint16_t height;
} tp_handle_t;

// 函数声明
tp_status_t tp_init(tp_handle_t *itf);
uint8_t tp_get_status(void);
void tp_getxy(int16_t *lastx, int16_t *lasty);
void tp_scan(tp_handle_t *itf);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 TOUCH 模块分组
/** @} */  // 结束外设模块分组

#endif
