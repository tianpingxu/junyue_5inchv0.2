/**
 * @file ssislv_drv.h 
 * @author Product application department 
 * @brief  SSI SLV 模块驱动层头文件
 * @version V1.0 
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */
#ifndef __SSISLV_DRV_H
#define __SSISLV_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

// 头文件包含
#include "ssislv_reg.h"

// 全局变量定义
#define SSISLV_DMACR_TDMAE     0x02
#define SSISLV_DMACR_RDMAE     0x01
#define SSISLV_SR_BUSY         0x01
#define SSISLV_SR_TFNF         0x02
#define SSISLV_SR_TFE          0x04
#define SSISLV_SR_RFNE         0x08
#define SSISLV_SR_RFF          0x10
#define SSISLV_SR_TXE          0x20

/**
  *@brief SSISLAVE 模块初始化结构体定义.
  *
  */
typedef struct
{
    uint8_t dfs;    // 数据帧大小    
    uint8_t frf;    // SSI数据帧格式 
    uint8_t scpha;  // 串行时钟相位
    uint8_t scpol;  // 串行时钟极性 
    uint8_t tmod;   // 传输模式                       
    uint8_t format; // SSI通讯格式                                             
} ssislv_init_t;



/**
 *  @brief SSISLAVE 模块使能/禁能枚举定义
 * 
 */
typedef enum
{
    SSISLV_DIS = 0,
    SSISLV_EN = 1
} ssislv_en_dis_t;


/**
 *  @brief  SSISLAVE 串行传输协议类型枚举定义
 * 
 */
typedef enum
{
    SSISLV_FRF_SPI       = 0x00,
    SSISLV_FRF_SSP       = 0x01,
    SSISLV_FRF_MICROWIRE = 0x02
} ssislv_frf_t;

/**
  * @brief SSISLAVE TMOD 串行通信的传输方式类型枚举定义
  * 
  */
typedef enum
{
    SSISLV_TX_AND_RX   = 0x00,
    SSISLV_TX_ONLY     = 0x01,
    SSISLV_RX_ONLY     = 0x02,
    SSISLV_EEPROM_READ = 0x03
} ssislv_tmod_t;

/**
  * @brief SSISLAVE 帧格式类型枚举定义
  * 
  */
typedef enum
{
    SSISLV_STD_MODE   = 0x00,
    SSISLV_DUAL_MODE  = 0x01,
    SSISLV_QUAD_MODE  = 0x02
} ssislv_format_t;

/**
  * @brief SSISLAVE DFS数据帧长度类型枚举定义
  * 
  */
typedef enum
{
    SSISLV_DFS_01_BIT  = 0x00,
    SSISLV_DFS_02_BIT  = 0x01,
    SSISLV_DFS_03_BIT  = 0x02,
    SSISLV_DFS_04_BIT  = 0x03,
    SSISLV_DFS_05_BIT  = 0x04,
    SSISLV_DFS_06_BIT  = 0x05,
    SSISLV_DFS_07_BIT  = 0x06,
    SSISLV_DFS_08_BIT  = 0x07,
    SSISLV_DFS_09_BIT  = 0x08,
    SSISLV_DFS_10_BIT  = 0x09,
    SSISLV_DFS_11_BIT  = 0x0a,
    SSISLV_DFS_12_BIT  = 0x0b,
    SSISLV_DFS_13_BIT  = 0x0c,
    SSISLV_DFS_14_BIT  = 0x0d,
    SSISLV_DFS_15_BIT  = 0x0e,
    SSISLV_DFS_16_BIT  = 0x0f,
    SSISLV_DFS_17_BIT  = 0x10,
    SSISLV_DFS_18_BIT  = 0x11,
    SSISLV_DFS_19_BIT  = 0x12,
    SSISLV_DFS_20_BIT  = 0x13,
    SSISLV_DFS_21_BIT  = 0x14,
    SSISLV_DFS_22_BIT  = 0x15,
    SSISLV_DFS_23_BIT  = 0x16,
    SSISLV_DFS_24_BIT  = 0x17,
    SSISLV_DFS_25_BIT  = 0x18,
    SSISLV_DFS_26_BIT  = 0x19,
    SSISLV_DFS_27_BIT  = 0x1a,
    SSISLV_DFS_28_BIT  = 0x1b,
    SSISLV_DFS_29_BIT  = 0x1c,
    SSISLV_DFS_30_BIT  = 0x1d,
    SSISLV_DFS_31_BIT  = 0x1e,
    SSISLV_DFS_32_BIT  = 0x1f,
} ssislv_dfs_t;

// 函数声明
void drv_ssislv_standard_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init);
void drv_ssislv_dual_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init);
void drv_ssislv_quad_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init);
void drv_ssislv_wait_tx_fifo_empty(reg_ssislv_t *p_ssislv);
void drv_ssislv_standard_xfer(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint8_t *p_send_buff, uint32_t xfer_len);
void drv_ssislv_dual_quad_rec(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint32_t xfer_len);
void drv_ssislv_dual_quad_send(reg_ssislv_t *p_ssislv, uint8_t *p_send_buff, uint32_t xfer_len);
void drv_ssislv_rx_dma_config(reg_ssislv_t *p_ssislv, uint32_t dma_en, uint32_t dma_data_level);
void drv_ssislv_tx_dma_config(reg_ssislv_t *p_ssislv, uint32_t dma_en, uint32_t dma_data_level);
                                
#ifdef __cplusplus
}
#endif   

#endif 
