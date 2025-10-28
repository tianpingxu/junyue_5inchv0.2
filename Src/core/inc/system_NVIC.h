/**
  ******************************************************************************
             Copyright(c) 2020 China Core Co. Ltd.
                      All Rights Reserved
  ******************************************************************************
  * @file    system_NVIC.h
  * @author  Product application department
  * @version V1.0
  * @date    2020.02.18
  * @brief   Header file of system_NVIC.
  *
  ******************************************************************************
*/

#ifndef __SYSTEM_NVIC_H__
#define __SYSTEM_NVIC_H__

#include "type.h"
#include "ccm4211.h" 

/**
 * @brief NVIC 模块中断优先级设置结构体定义
 * 
 */
typedef struct
{
    uint8_t NVIC_PreemptionPriority;
    uint8_t NVIC_SubPriority;
    uint8_t NVIC_Group;
} irq_init_t;
extern void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);    //设置偏移地址
extern void NVIC_PriorityGroupConfig(uint8_t NVIC_Group);            //设置NVIC分组
extern void NVIC_Init(uint8_t NVIC_PreemptionPriority,uint8_t NVIC_SubPriority,uint8_t NVIC_Channel,uint8_t NVIC_Group);//设置中断
extern void Ex_NVIC_Config(uint8_t GPIOx,uint8_t BITx,uint8_t TRIM);                //外部中断配置函数(只对GPIOA~I)
extern void NVIC_Clear(uint8_t NVIC_Channel);                   /*清除中断位*/

//以下为汇编函数
extern void INTX_DISABLE(void);//关闭所有中断
extern void INTX_ENABLE(void);    //开启所有中断
#endif  /* __SYSTEM_NVIC__ */


