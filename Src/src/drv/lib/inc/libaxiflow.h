/**
 * @file libaxiflow.h
 * @author Product application department
 * @brief  AXIFLOW 模块库头文件
 * @version V1.0
 * @date 2025-02-13
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __LIBAXIFLOW_H
#define __LIBAXIFLOW_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
#include "iomacros.h"

 // 全局变量定义

 /**
  * @brief AXIFLOW 模块类型枚举定义
  *
  */
 typedef enum
 {
     AXI_M1_DECODER_PORT_QOS_ID = 0,
     AXI_M2_AHB2AXI_PORT_QOS_ID,
     AXI_M3_CDC_PORT_QOS_ID,
     AXI_M4_DMA2D_PORT_QOS_ID,
     AXI_M6_CPU_PORT_QOS_ID = 5,
     AXI_AXIDMA_CH0_PORT_QOS_ID,
     AXI_AXIDMA_CH1_PORT_QOS_ID,
     AXI_AXIDMA_CH2_PORT_QOS_ID,
     AXI_AXIDMA_CH3_PORT_QOS_ID,
 } axi_masterid_qos_t;

 /**
  * @brief AXIFLOW 模块tocken枚举定义
  *
  */
 typedef enum
 {
     AXI_M1_DECODER_PORT_TOKEN_ID = 0,
     AXI_M2_AHB2AXI_PORT_TOKEN_ID,
     AXI_M3_CDC_PORT_TOKEN_ID,
     AXI_M4_DMA2D_PORT_TOKEN_ID,
     AXI_M5_AXIDMA_PORT_TOKEN_ID,
     AXI_M6_CPU_PORT_TOKEN_ID,
 } axi_masterid_token_t;

 /**
  * @brief AXIFLOW 模块传输长度枚举定义
  *
  */
 typedef enum
 {
     TOKEN_H_2 = 0X800,
     TOKEN_H_4 = 0X400,
     TOKEN_H_8 = 0X200,
     TOKEN_H_16 = 0X100,
     TOKEN_H_32 = 0X80,
     TOKEN_H_64 = 0X40,
     TOKEN_H_128 = 0X20,
     TOKEN_H_256 = 0X10,
     TOKEN_H_512 = 0X08,
     TOKEN_H_1024 = 0X04,
     TOKEN_H_2048 = 0X02,
     TOKEN_H_4096 = 0X01,
 } axi_token_transcation_t;

 // 函数声明
 /**
 * @brief 使用CDC BLEND模式需要调用此接口
 *
 */
void axiflow_cdc_blend(void);
/**
 * @brief 不使用CDC BLEND模式需要调用此接口
 *
 */
void axiflow_cdc_noblend(void);
/**
 * @brief Bypass功能，不做任何处理
 *
 */
void axiflow_cdc_bypass(void);
/**
 * @brief 获取当前AXI总线上各个master的写Qos优先级
 *
 * @param masterid 指定的AXI总线的masterid
 * @return uint8_t 指定master的Qos当前写优先级
 */
uint8_t axi_get_wr_qos(axi_masterid_qos_t masterid);
/**
 * @brief 获取当前AXI总线上各个master的读Qos优先级
 *
 * @param masterid 指定的AXI总线的masterid
 * @return uint8_t 指定master的Qos当前读优先级
 */
uint8_t axi_get_rd_qos(axi_masterid_qos_t masterid);
/**
 * @brief 指定master的写Qos优先级
 *
 * @param masterid 指定的AXI总线的masterid
 * @param qos 优先级（数字越大优先级越高，共16级，0-15）
 */
void axi_set_wr_qos(axi_masterid_qos_t masterid, uint8_t qos);
/**
 * @brief 指定master的读Qos优先级
 *
 * @param masterid 指定的AXI总线的masterid
 * @param qos 优先级（数字越大优先级越高，共16级，0-15）
 */
void axi_set_rd_qos(axi_masterid_qos_t masterid, uint8_t qos);
/**
 * @brief 使能通过令牌机制对指定master的写通道进行限速
 *
 * @param masterid 指定的AXI总线的masterid
 * @param transcation_rate 令牌传输速率，指定transcation_rate个周期内最多响应一个指定master的写请求
 * @param request_burtiness 令牌请求处理突发性，指定transcation_rate个周期内最多接收request_burtiness个指定master的写请求；
 */
void axi_set_wr_token_enable(axi_masterid_token_t masterid, axi_token_transcation_t transcation_rate, uint8_t request_burtiness);
/**
 * @brief 使能通过令牌机制对指定master的读通道进行限速
 *
 * @param masterid 指定的AXI总线的masterid
 * @param transcation_rate 令牌传输速率，指定transcation_rate个周期内最多响应一个指定master的读请求
 * @param request_burtiness 令牌请求处理突发性，指定transcation_rate个周期内最多接收request_burtiness个指定master的读请求；
 */
void axi_set_rd_token_enable(axi_masterid_token_t masterid, axi_token_transcation_t transcation_rate, uint8_t request_burtiness);
/**
 * @brief 关闭通过令牌机制对指定master的写通道进行限速
 *
 * @param masterid 指定的AXI总线的masterid
 */
void axi_set_wr_token_disable(axi_masterid_token_t masterid);
/**
 * @brief 关闭通过令牌机制对指定master的读通道进行限速
 *
 * @param masterid 指定的AXI总线的masterid
 */
void axi_set_rd_token_disable(axi_masterid_token_t masterid);

#endif
