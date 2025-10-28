/**
 * @file ssislv_hal.h 
 * @author Product application department 
 * @brief  SSI SLV 模块硬件抽象层头文件
 * @version V1.0 
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */
#ifndef __SSISLV_HAL_H
#define __SSISLV_HAL_H


#ifdef __cplusplus
extern "C" {
#endif

// 头文件包含
#include "ssislv_drv.h"
#include "dma_hal.h"
#include "status.h"  

// 全局变量定义
#define SSI_TIMEOUT 0xFFFFFFFF

// 函数声明
void hal_ssislv_standard_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init);
void hal_ssislv_dual_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init);
void hal_ssislv_quad_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init);
void hal_ssislv_standard_xfer(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint8_t *p_send_buff, uint32_t xfer_len);
void hal_ssislv_dual_quad_rec(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint32_t xfer_len);
void hal_ssislv_dual_quad_send(reg_ssislv_t *p_ssislv, uint8_t *p_send_buff, uint32_t xfer_len);
status_t hal_ssislv_standard_xfer_dma(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint8_t *p_send_buff, uint32_t xfer_len, uint8_t dma_ch_rx, uint8_t dma_ch_tx);
status_t hal_ssislv_dual_quad_rec_dma(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint32_t xfer_len, uint8_t dma_ch_rx);
status_t hal_ssislv_dual_quad_send_dma(reg_ssislv_t *p_ssislv, uint8_t *p_send_buff, uint32_t xfer_len, uint8_t dma_ch_tx);
status_t hal_ssislv_rec_dma_pingpong_buffer(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff0, uint8_t *p_rec_buff1, uint32_t buff_len, uint8_t dma_ch_rx);
void hal_ssislv_dma_pingpong_buffer_disable(reg_ssislv_t *p_ssislv, uint8_t dma_ch_rx);
             
#ifdef __cplusplus
}
#endif   

#endif
