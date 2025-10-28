/**
 * @file gt911.h
 * @author Product application department
 * @brief 驱动芯片gt911驱动程序头文件
 * @version V1.0
 * @date 2025-05-02
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 * 
 */

 /**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup GT911 GT911模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __GT911_H__
#define __GT911_H__

#include "type.h"
#include "tp_interface.h"
#define TOUCH_CPT_SCAN_TIMES 1 // 触摸扫描频率

// I2C读写命令
#define GT_CMD_WR 0X28 // 写命令
#define GT_CMD_RD 0X29 // 读命令

// GT911 部分寄存器定义
#define GT_CTRL_REG 0X8040  // GT911控制寄存器
#define GT_CFGS_REG 0X8047  // GT911配置起始地址寄存器
#define GT_CHECK_REG 0X80FF // GT911校验和寄存器
#define GT_PID_REG 0X8140   // GT911产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT911当前检测到的触摸情况

#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 0X8158 // 第二个触摸点数据地址
#define GT_TP3_REG 0X8160 // 第三个触摸点数据地址
#define GT_TP4_REG 0X8168 // 第四个触摸点数据地址
#define GT_TP5_REG 0X8170 // 第五个触摸点数据地址

extern tp_status_t gt911_init(void);
extern uint8_t gt911_scan(uint8_t mode);

#endif

/** @} */  // 结束 GT9XX 模块分组
/** @} */  // 结束外设模块分组
