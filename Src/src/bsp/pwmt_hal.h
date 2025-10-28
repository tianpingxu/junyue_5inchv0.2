/**
 * @file pwmt_hal.h
 * @author Product Application Department
 * @brief  PWMT模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-17
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef PWMT_HAL_H
#define PWMT_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "pwmt_drv.h"

// 函数声明
void hal_pwmt_swapenable(reg_pwmt_t *module, uint8_t ch);
uint8_t hal_pwmt_pwmoutputinit(pwmt_handle_t *hpwmt);
void hal_pwmt_pwmenable(pwmt_handle_t *hpwmt, functionalstate_t status);
void hal_pwmt_irqhandler(void);
void hal_pwmt_capturecallback(void *pwmt);
uint8_t hal_pwmt_inputcaptureinit(pwmt_handle_t *hpwmt);
uint8_t hal_channel_outputconfiguration(pwmt_handle_t *hpwmt, uint8_t ch);
void hal_pwmt_dmaupdatereqen(reg_pwmt_t *ppwmt);
void hal_pwmt_dmacc1reqen(reg_pwmt_t *ppwmt);
void hal_pwmt_dmacc2reqen(reg_pwmt_t *ppwmt);
void hal_pwmt_dmacc3reqen(reg_pwmt_t *ppwmt);
void hal_pwmt_dmacc4reqen(reg_pwmt_t *ppwmt);
void hal_pwmt_counten(reg_pwmt_t *ppwmt);
uint8_t hal_pwmt_getitstatus(reg_pwmt_t *ppwmt);
uint16_t hal_pwmt_getcapval(reg_pwmt_t *ppwmt, uint8_t portnum);
void hal_pwmt_clritstatus(reg_pwmt_t *ppwmt, pwmt_int_t flag);
flagstatus_t hal_pwmt_getcapflag(reg_pwmt_t *ppwmt, pwmt_int_t flag);
void hal_pwmt_clrcapflag(reg_pwmt_t *ppwmt, pwmt_int_t flag);

#ifdef __cplusplus
}
#endif

#endif
