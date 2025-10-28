/**
 * @file drv_gpio_def.h
 * @author Product application department
 * @brief  GPIO 驱动层头文件
 * @version V1.0
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef DRV_GPIO_DEF_H_
#define DRV_GPIO_DEF_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
/**
 * @brief  GPIO输入/输出定义
 *
 */
typedef enum
{
    GPIO_DIR_IN,
    GPIO_DIR_OUT,
    GPIo_DIR_TRIGATE,

} gpio_dir_t,
    eport_dir_t;

/**
 * @brief  GPIO输入模式定义
 *
 */
typedef enum
{
    GPIO_INPUT_MODE_CMOS,
    GPIO_INPUT_MODE_SCHMITT,
} gpio_inputmode_t;

/**
 * @brief  GPIO输出模式定义
 *
 */
typedef enum
{
    GPIO_OUTPUT_MODE_CMOS,
    GPIO_OUTPUT_MODE_OPEN_DRAIN,
} gpio_outputmode_t;

/**
 * @brief  上下拉模式定义
 *
 */
typedef enum
{
    GPIO_PULL_MODE_NOPULL,
    GPIO_PULL_MODE_UP,
    GPIO_PULL_MODE_DOWN,
} gpio_pullmode_t;

/**
 * @brief  GPIO反转速度定义
 *
 */
typedef enum
{
    GPIO_SLEW_RATE_FALST,
    GPIO_SLEW_RATE_SLOW,
} gpio_slewrate_t;

/**
 * @brief  GPIO驱动电流定义
 *
 */
typedef enum
{
    GPIO_DRIVE_STRENGTH_2MA,
    GPIO_DRIVE_STRENGTH_4MA,
    GPIO_DRIVE_STRENGTH_8MA,
    GPIO_DRIVE_STRENGTH_12MA,
} gpio_drivesrrength_t;

/**
 * @brief  GPIO初始化结构体定义
 *
 */
typedef struct
{
    uint8_t Pin;
    uint8_t Dir;
    uint8_t PullMode;
    uint8_t OutputMode;
    uint8_t InputMode;
    uint8_t SlewRateSel;
    uint8_t DriveStrength;
} gpio_init_t;

#ifdef __cplusplus
}
#endif

#endif
