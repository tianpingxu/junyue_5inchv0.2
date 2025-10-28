/**
 * @file axidma_hal.h
 * @author Product application department
 * @brief  AXIDMA 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __AXIDMA_HAL_H
#define __AXIDMA_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "axidma_drv.h"
#include "interrupt.h"

/**
 *@brief    AXIDMA 模块设备枚举定义
 */

 typedef enum
 {
     HAL_AXIDMAC_PERIPHERAL_SSI1_RX = 0X00,
     HAL_AXIDMAC_PERIPHERAL_SSI1_TX = 0X01,
     HAL_AXIDMAC_PERIPHERAL_SSI2_RX = 0X02,
     HAL_AXIDMAC_PERIPHERAL_SSI2_TX = 0X03,
     HAL_AXIDMAC_PERIPHERAL_SSI3_RX = 0X04,
     HAL_AXIDMAC_PERIPHERAL_SSI3_TX = 0X05,
     HAL_AXIDMAC_PERIPHERAL_PSRAM_RX = 0X06,
     HAL_AXIDMAC_PERIPHERAL_PSRAM_TX = 0X07,
     
 } axidmac_periperal_t;
// 函数声明
status_t hal_axidma_init(axidma_handle_t *initpara);
void hal_axidma_start(axidma_handle_t *initpara);
void hal_axidma_disable(axidma_handle_t *initpara);
void hal_axidma_transfer_polling(axidma_handle_t *initpara);
uint32_t hal_axidma_get_chx_ctl(axidma_handle_t *initpara);
status_t hal_axidma_config_llp(axidma_handle_t *initpara, uint32_t llp_addr);
void hal_axidma_irq_handler(void);

#ifdef __cplusplus
}
#endif

#endif