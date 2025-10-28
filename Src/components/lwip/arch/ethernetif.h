/**
 * @file ethernetif.h
 * @author Product application department
 * @brief  ethernetif 驱动头文件
 * @version V1.0
 * @date 2025-03-02
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */

#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

//头文件包含 
#include "lwip/err.h"
#include "lwip/netif.h"

// 全局变量定义
#define NETIF_MTU                           ( 1500 )

#define NETIF_IN_TASK_STACK_SIZE            ( 1024 )
#define NETIF_IN_TASK_PRIORITY              ( 12 )

#define NETIF_OUT_TASK_STACK_SIZE            ( 1024 )
#define NETIF_OUT_TASK_PRIORITY              ( 3 )

//函数声明
err_t ethernetif_init(struct netif *netif);

void ethernetif_input( void *argument );
void ethernetif_output( void *argument );
void ethernetif_update_config(struct netif *netif);
void ethernetif_notify_conn_changed(struct netif *netif);

u32_t sys_jiffies(void);
u32_t sys_now(void);
#endif
