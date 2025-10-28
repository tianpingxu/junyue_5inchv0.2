/**
 *  @file ssi_hal.h
 *  @author Product application department
 *  @brief  SSI 模块硬件抽象层头文件
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __SSI_HAL_H
#define __SSI_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "ssi_drv.h"


// 全局变量定义
#define SSI_MULTI_PAGE_PROGRAM (1)
#define ALIGN_DOWN(x, a) ((x) & ~((a) - 1))

/**
 * @brief SSI 模块句柄结构体定义
 * 
 */
typedef struct
{
    reg_ssi_t *Instance; 
    ssi_init_t Init; 
} ssi_handle_t;

/**
 * @brief SSI 模块频率结构体定义
 * 
 */
typedef enum
{
    SSIFreq100M = 2,
    SSIFreq50M = 4,
    SSIFreq40M = 5,
    SSIFreq33M = 6,
    SSIFreq25M = 8,
    SSIFreq10M = 20,
    SSIFreq5M = 40,
    SSIFreq2M = 100,
    SSIFreq1M = 200,
    SSIFreq500K = 400,
    SSIFreq250K = 800,
} SSIFq;
// 函数声明
status_t hal_ssi_flash_program(uint32_t addr, uint8_t *p_buff, uint32_t len);
void hal_ssi_flash_read(uint32_t addr, uint8_t *p_buff, uint32_t len);
status_t hal_ssi_flash_sector_erase(uint32_t addr);
void hal_ssi_init(ssi_handle_t*SSIHandle);
void hal_ssi_qualinit(ssi_handle_t *SSIHandle,uint32_t len,SSIFq bound,uint8_t isread,uint8_t isaxidma,uint32_t sample_delay);
status_t hal_ssi_tx(reg_ssi_t *pssi, uint8_t *buf, uint32_t buf_len);
status_t hal_ssi_rx(reg_ssi_t *pssi, uint8_t *buf, uint32_t buf_len);
void hal_axidma_tx(uint8_t channel, uint32_t *addr_peri, uint8_t *buf, uint32_t buf_len);
void hal_axidma_rx(uint8_t channel, uint8_t *buf, uint32_t buf_len);
void hal_ssi_deinit(ssi_handle_t *pinit);

#ifdef __cplusplus
}
#endif

#endif
