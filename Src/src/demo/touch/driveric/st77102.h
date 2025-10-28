/**
 * @file st77102.h
 * @author Product application department
 * @brief 驱动芯片st77102驱动程序头文件
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
 * @defgroup ST77102 ST77102模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __ST77102_H__
#define __ST77102_H__

#include "type.h"
#include "tp_interface.h"
#include "delay.h"
#include "eport_hal.h"
#include "eport_drv.h"
#include "pinswap_drv.h"

#define TOUCH_SDA_GPIO_PORT      EPORT4
#define TOUCH_SDA_GPIO_PIN       EPORT4_PIN6
#define TOUCH_SCL_GPIO_PORT      EPORT4
#define TOUCH_SCL_GPIO_PIN       EPORT4_PIN7

#define Touch_I2C_WR	0		/* Write data. */
#define Touch_I2C_RD	1		/* Read data.  */

struct ST_i2c_msg {
   uint8_t addr;        /*从设备的I2C设备地址 */
   uint16_t flags;      /*控制标志*/
   uint16_t len;        /*读写数据的长度           */
   uint8_t *buf;        /*存储读写数据的指针 */
};

#define TOUCH_CPT_SCAN_TIMES 1 // 触摸扫描频率

#define ST77102_REGITER_LEN         2
#define ST77102_SALVE_ADDR          0xAA
#define ST77102_MAX_TOUCH           5

#define ST_CMD_WR 0xAA
#define ST_CMD_RD 0xAB

/* ST77102 REGISTER */
#define ST77102_FW_VERSION          0x0000
#define ST77102_DEV_STATUS          0x0001
#define ST77102_DEV_CONTROL         0x0002
#define ST77102_MAX_X_COORD         0x0005
#define ST77102_TOUCH_INFO          0x0010
#define ST77102_X0_COORD_HIGH       0x0014
#define ST77102_TOUCH_COUNTER          0x000A


extern tp_status_t st77102_init(void);
extern uint8_t st77102_scan(uint8_t mode);

#endif

/** @} */  // 结束 GT9XX 模块分组
/** @} */  // 结束外设模块分组
