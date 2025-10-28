/**
 * @file can_hal.h
 * @author Product application department 
 * @brief  CAN 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-02-27
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

#ifndef _CAN_HAL_H
#define _CAN_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

// 头文件包含
#include "can_drv.h"
#include "debug.h"
#include "system_NVIC.h"

// 全局变量定义
#define HAL_CAN_ERROR_NONE        ((uint32_t)0x00)    
#define HAL_CAN_ERROR_PE          ((uint32_t)0x01)    
#define HAL_CAN_ERROR_NE          ((uint32_t)0x02)    
#define HAL_CAN_ERROR_FE          ((uint32_t)0x04)    
#define HAL_CAN_ERROR_ORE         ((uint32_t)0x08)    
#define HAL_CAN_DEBUG(...)        printf(__VA_ARGS__)
#define HAL_CAN_ARGV_ERROR(NUM)   HAL_CAN_DEBUG("Argv[%d] Error\r\n", NUM)

typedef void (*HAL_CAN_CALLBACK)(reg_can_t *);

/**
 * @brief CAN 模块状态枚举定义
 */

typedef enum
{
    HAL_CAN_STATE_RESET       = 0x00U,     
    HAL_CAN_STATE_READY       = 0x01U,     
    HAL_CAN_STATE_BUSY        = 0x02U,     
    HAL_CAN_STATE_BUSY_TX     = 0x12U,     
    HAL_CAN_STATE_BUSY_RX     = 0x22U,     
    HAL_CAN_STATE_BUSY_TX_RX  = 0x32U,     
    HAL_CAN_STATE_TIMEOUT     = 0x03U,     
    HAL_CAN_STATE_ERROR       = 0x04U      
} can_statetypedef_t;  

/**
 * @brief CAN 模块句柄结构体定义
 */

typedef struct
{
  reg_can_t *Instance;         
  can_init_t Init;             
  can_txmsg_t *pTxMsg;        
  uint32_t TxSize;                    
  uint32_t TxCnt;                     
  can_rxmsg_t *pRxMsg;        
  uint32_t RxSize;                    
  uint32_t RxCnt;                     
  __IO can_statetypedef_t State;      
  __IO uint32_t ErrorCode;            
  HAL_CAN_CALLBACK BOFFCallback;      
  HAL_CAN_CALLBACK ErrCallback;       
  HAL_CAN_CALLBACK RwrnCallback;      
  HAL_CAN_CALLBACK TwrnCallback;      
  HAL_CAN_CALLBACK MBIsrCallback;     
} can_handle_typedef_t, *pcan_handle_typedef_t; 

// 函数声明
status_t hal_can_deinit(can_handle_typedef_t *hcan);
status_t hal_can_init(can_handle_typedef_t *hcan);
status_t hal_can_transmitbytes(can_handle_typedef_t *hcan, uint32_t timeout);
void hal_can_irqhandle(void);
status_t hal_can_receivebytes(can_handle_typedef_t *hcan, uint32_t timeout);
void hal_can_transmit_init(can_handle_typedef_t *hcan, uint8_t argc, uint32_t argv[]);
void hal_can_receive_init(can_handle_typedef_t *hcan, uint8_t argc, uint32_t argv[]);
void hal_can_transmit(uint32_t argv[], uint32_t timeout);
void hal_can_receive(uint32_t argv[], uint32_t timeout);
status_t hal_can_readrxmb(reg_can_t *pcan, can_rxmsg_t *prxmsg);
void hal_can_isr(reg_can_t *pcan);
void hal_can_rxmb_it_config(reg_can_t *pcan, can_rxmsg_t *prxmsg);
void hal_can_transfer_intinit(can_handle_typedef_t *hcan, uint32_t argv[], uint32_t timeout);
void hal_can_query_rxintstatus(int *rx_int_status);
void hal_can_select_crystal_oscillator(can_handle_typedef_t *hcan);

#ifdef __cplusplus
}
#endif

#endif 
