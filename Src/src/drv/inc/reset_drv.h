/**
 * @file reset_drv.h
 * @author Product application department
 * @brief  RESET 模块驱动头文件
 * @version V1.0
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __RESET_DRV_H
#define __RESET_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include <stdbool.h>
#include "iomacros.h"
#include "reset_reg.h"

// 全局变量定义
#define _reset_softreset _bit_set(RST->RCR, RESET_RCR_SOFTRST)
#define _reset_en_frcr_stout _bit_set(RST->RCR, RESET_RCR_FRCR_STOUT)
#define _reset_dis_frcr_stout _bit_clr(RST->RCR, RESET_RCR_FRCR_STOUT)
#define _reset_get_status _reg_read(RST->RSR)
#define _reset_en_simcard_wakeup _bit_set(RST->RCR, RESET_RCR_CRWE)
#define _reset_dis_simcard_wakeup _bit_clr(RST->RCR, RESET_RCR_CRWE)
#define _reset_en_simcard_rst _bit_set(RST->RCR, RESET_RCR_CRE)
#define _reset_dis_simcard_rst _bit_clr(RST->RCR, RESET_RCR_CRE)
#define _reset_en_hvd_rst_control _bit_set(RST->RCR, RESET_RCR_HVDE)
#define _reset_dis_hvd_rst_control _bit_clr(RST->RCR, RESET_RCR_HVDE)
#define _reset_en_hvd_rst _bit_set(RST->RCR, RESET_RCR_HVDRE)
#define _reset_dis_hvd_rst _bit_clr(RST->RCR, RESET_RCR_HVDRE)
#define _reset_en_lvd_control _bit_set(RST->RCR, RESET_RCR_LVDE)
#define _reset_dis_lvd_control _bit_clr(RST->RCR, RESET_RCR_LVDE)
#define _reset_en_lvd_rst _bit_set(RST->RCR, RESET_RCR_LVDRE)
#define _reset_dis_lvd_rst _bit_clr(RST->RCR, RESET_RCR_LVDRE)
#define _reset_get_lfd_status _bit_get(RST->RCR, RESET_RCR_LFDF)
#define _reset_en_lfd_int _bit_set(RST->RCR, RESET_RCR_LFDIE)
#define _reset_dis_lfd_int _bit_clr(RST->RCR, RESET_RCR_LFDIE)
#define _reset_en_lfd_control _bit_set(RST->RCR, RESET_RCR_LFDE)
#define _reset_dis_lfd_control _bit_clr(RST->RCR, RESET_RCR_LFDE)
#define _reset_en_lfd_rst _bit_set(RST->RCR, RESET_RCR_LFDRE)
#define _reset_dis_lfd_rst _bit_clr(RST->RCR, RESET_RCR_LFDRE)
#define _reset_get_hfd_status _bit_get(RST->RCR, RESET_RCR_HFDF)
#define _reset_en_hfd_int _bit_set(RST->RCR, RESET_RCR_HFDIE)
#define _reset_dis_hfd_int _bit_clr(RST->RCR, RESET_RCR_HFDIE)
#define _reset_en_hfd_control _bit_set(RST->RCR, RESET_RCR_HFDE)
#define _reset_dis_hfd_control _bit_clr(RST->RCR, RESET_RCR_HFDE)
#define _reset_en_hfd_rst _bit_set(RST->RCR, RESET_RCR_HFDRE)
#define _reset_dis_hfd_rst _bit_clr(RST->RCR, RESET_RCR_HFDRE)

/**
 * @brief RESET 模块电压枚举定义
 *
 */
typedef enum
{
    POWER_1P8_V,
    POWER_3P3_V,
    POWER_5P0_V,
} POWER;

// 函数声明
void drv_reset_softreset(void);
void drv_lvd_reset_enable(void);
void drv_lvd_reset_disable(void);
void DRV_SmartCardReset_Enable(void);
void DRV_SmartCardReset_Disable(void);
void DRV_SmartCard_WakeUp_Enable(void);
void DRV_SmartCard_WakeUp_Disable(void);
void drv_hvd_reset_enable(void);
void drv_hvd_reset_disable(void);
bool drv_lfd_gerstatus(void);
void drv_lfd_interrupt_enable(void);
void drv_lfd_interrupt_disable(void);
void drv_lfd_reset_enable(void);
void drv_lfd_reset_disable(void);
bool drv_hfd_getstatus(void);
void drv_hfd_interrupt_enable(void);
void drv_hfd_interrupt_disable(void);
void drv_hfd_reset_enable(void);
void drv_hfd_reset_disable(void);
uint8_t drv_reset_getstatus(void);
void drv_set_lvdthreahold(uint8_t power, uint8_t threshold);
void drv_set_hvdthreahold(uint8_t power, uint8_t threshold);

#ifdef __cplusplus
}
#endif

#endif
