/**
 * @file i2c_reg.h
 * @author Product Application Department
 * @brief  I2C 模块寄存器配置文件
 * @version V1.0
 * @date 2025-02-12
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I2C_REG_H_
#define __I2C_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define I2C1_BASE_ADDR (0x40017000)
#define I2C2_BASE_ADDR (0x4001B000)
#define I2C1 ((reg_i2c_t *)I2C1_BASE_ADDR)
#define I2C2 ((reg_i2c_t *)I2C2_BASE_ADDR)

// I2CC
#define I2C_EN (1 << 0)
#define I2C_DIS (0xFE)
#define I2C_EN_IT (1 << 1)
#define I2C_DIS_IT (0xFD)
#define I2C_MASTER (1 << 2)
#define I2C_SLAVE (0xFB)
#define I2C_EN_ACK (1 << 3)
#define I2C_DIS_ACK (0xF7)
#define I2C_EN_REPEAT_START (1 << 4)
#define I2C_DIS_REPEAT_START (0xEF)
#define I2C_EN_ADDRESS_MATCH_IT (1 << 5)
#define I2C_DIS_ADDRESS_MATCH_IT (0xDF)
#define I2C_EN_HIGH_SPEED_MODE (1 << 6)
#define I2C_DIS_HIGH_SPEED_MODE (0xBF)
#define I2C_EN_SLAVE_HIGH_SPEED_MODE_IT (1 << 7)
#define I2C_DIS_SLAVE_HIGH_SPEED_MODE_IT (0x7F)

// I2CP
#define I2C_CLOCK_MODE_TEST (1 << 6)
#define I2C_CLOCK_MODE_NORMAL (~I2C_CLOCK_MODE_TEST)
#define I2C_CLOCK_PRESCALE (0x3F)

// I2CS
#define I2C_FLAG_TF (1 << 0)
#define I2C_FLAG_RC (1 << 1)
#define I2C_FLAG_AASLV (1 << 2)
#define I2C_FLAG_BUSY (1 << 3)
#define I2C_FLAG_ARBL (1 << 4)
#define I2C_FLAG_RXTX (1 << 5)
#define I2C_FLAG_DACK (1 << 6)
#define I2C_FLAG_AACK (1 << 7)
#define I2C_FLAG_RX_MASK (0)
#define I2C_FLAG_TX_MASK (0x20)

// I2CSHIR
#define I2C_FLAG_SLAVE_HIGH_SPEED (1 << 0)

// I2CSHT
#define I2C_EN_SDA_FILTER (1 << 6)
#define I2C_EN_SCL_FILTER (1 << 7)

// I2CSHIR
#define I2C_SLAVE_HIGH_SPEED (1 << 0)

// I2PCR
#define I2C_PIN_SCL (0)
#define I2C_PIN_SDA (1)
#define I2C_PA_SHIFT_MASK (6)
#define I2C_WOM_SHIFT_MASK (4)
#define I2C_PD_SHIFT_MASK (2)
#define I2C_PU_SHIFT_MASK (0)
#define I2C_PIN_SDA_GPIO (0x80)
#define I2C_PIN_SDA_PRIMARY_FUN (~(I2C_PIN_SDA_GPIO))
#define I2C_PIN_SCL_GPIO (0x40)
#define I2C_PIN_SCL_PRIMARY_FUN (~(I2C_PIN_SCL_GPIO))
#define I2C_PIN_SDA_OPEN_DRAIN_MODE (0x20)
#define I2C_PIN_SDA_CMOS_MODE (~(I2C_PIN_SDA_OPEN_DRAIN_MODE))
#define I2C_PIN_SCL_OPEN_DRAIN_MODE (0x10)
#define I2C_PIN_SCL_CMOS_MODE (~(I2C_PIN_SCL_OPEN_DRAIN_MODE))
#define I2C_PIN_SDA_EN_PULLDOWN (0x04)
#define I2C_PIN_SDA_DIS_PULLDOWN (~(I2C_PIN_SDA_EN_PULLDOWN))
#define I2C_PIN_SCL_EN_PULLDOWN (0x02)
#define I2C_PIN_SCL_DIS_PULLDOWN (~(I2C_PIN_SCL_EN_PULLDOWN))
#define I2C_PIN_SDA_EN_PULLUP (0x02)
#define I2C_PIN_SDA_DIS_PULLUP (~(I2C_PIN_SDA_EN_PULLUP))
#define I2C_PIN_SCL_EN_PULLUP ((uint32_t)1)
#define I2C_PIN_SCL_DIS_PULLUP (~(I2C_PIN_SCL_EN_PULLUP))

// I2CPDR
#define I2C_PIN_SCL_DIR_GPIO_OUT (1 << 0)
#define I2C_PIN_SCL_DIR_GPIO_IN (~(I2C_PIN_SCL_DIR_GPIO_OUT))
#define I2C_PIN_SDA_DIR_GPIO_OUT (1 << 1)
#define I2C_PIN_SDA_DIR_GPIO_IN (~(I2C_PIN_SDA_DIR_GPIO_OUT))

/**
 * @brief I2C 模块寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint8_t SARH;
    __IO uint8_t SARL;
    //    __IO uint16_t SAR;
    __IO uint8_t CCR;
    __IO uint8_t PR;
    __IO uint8_t SR;
    __IO uint8_t DR;
    __IO uint8_t SHTR;
    __IO uint8_t SHIR;
    __IO uint8_t PCR;
    __IO uint8_t PDR;
    __IO uint8_t DDR;
    __IO uint8_t FCTR;
    __IO uint8_t NSFTVR_10;
    __IO uint8_t NSFTVR_50;
} reg_i2c_t;

#ifdef __cplusplus
}
#endif

#endif
