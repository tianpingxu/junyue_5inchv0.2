/**
 * @file eport_hal.h
 * @author Product Application Department
 * @brief EPORT 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef _EPORT_HAL_H
#define _EPORT_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "eport_drv.h"
#include "ioctrl_hal.h"

// 全局变量定义

/**
 * @brief EPORT 模块初始化结构体定义
 * 
 */
typedef struct
{
    reg_eport_t *Instance;
    hal_ioctrl_eportinit_t ioctrl_init;
    gpio_dir_t dir;
    eport_outputmode_t output_mode;
    eport_intmode_t it_type;
    functionalstate_t it_status;
    functionalstate_t pull_up_status;
    uint8_t pins;
    irq_init_t irq;
} eport_init_t;
// 函数声明
status_t hal_eport_init(eport_init_t *pEportInit);
void hal_eport_output(reg_eport_t *pEport, uint8_t Pinx);
void hal_eport_writepinlevel(reg_eport_t *pEport, uint8_t Pinx, gpio_pinstate_t Level);
void hal_eport_input(reg_eport_t *pEport, uint8_t Pinx, ioctrl_ps_t ps);
uint8_t hal_eport_readpinslevel(reg_eport_t *pEport, uint8_t pins);
void hal_eport_interrupt(reg_eport_t *pEport, uint8_t Pinx, eport_intmode_t int_type, ioctrl_ps_t ps);

#ifdef __cplusplus
}
#endif

#endif
