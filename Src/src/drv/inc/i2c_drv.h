/**
 * @file i2c_drv.h
 * @author Product Application Department
 * @brief  I2C 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __I2C_DRV_H
#define __I2C_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "iomacros.h"
#include "drv_gpio_def.h"
#include "i2c_reg.h"
#include "delay.h"
#include "status.h"
    
// 全局变量定义
#define I2C_SPEED_NORMAL     (1)
#define I2C_SPEED_HIGH         (2)
#define I2C_DIR_READ         (1)
#define I2C_DIR_WRITE         (2)

#define I2C_MASTER_CODE ((uint8_t)(0X0A))
#define I2C_SUBADD         ((uint8_t)(0x80))

#define I2C_SUB_ADD_BYTES_1 ((uint8_t)(0x01))
#define I2C_SUB_ADD_BYTES_2 ((uint8_t)(0x02))
#define I2C_SUB_ADD_BYTES_3 ((uint8_t)(0x03))
#define I2C_SUB_ADD_BYTES_4 ((uint8_t)(0x04))

#define I2C_ERROR_OK                 (0X00)
#define I2C_ERROR_CLOCK_FACTOR         (0X01)
#define I2C_ERROR_CLOCK_PRESCALER     (0X02)
#define I2C_ERROR_ABRL                 (0X03)
#define I2C_ERROR_AACK                 (0X04)

#define _i2c_slave_set_addr(i2c, addr) _reg_write(i2c->SAR, addr)
#define _i2c_en(i2c) _bit_set(i2c->CCR, I2C_EN)
#define _i2c_dis(i2c) _bit_clr(i2c->CCR, I2C_EN)
#define _i2c_en_it(i2c) _bit_set(i2c->CCR, I2C_EN_IT)
#define _i2c_dis_it(i2c) _bit_clr(i2c->CCR, I2C_EN_IT)

#define _i2c_bus_start _bit_set(I2C->CR, I2C_MASTER)
#define _i2c_bus_stop _bit_clr(I2C->CR, I2C_MASTER)
#define _i2c_bus_ack _bit_set(I2C->CR, I2C_EN_ACK)
#define _i2c_bus_nack _bit_clr(I2C->CR, I2C_EN_ACK)

#define _i2c_generate_start(i2c) _bit_set(i2c->CCR, I2C_MASTER)
#define _i2c_generate_stop(i2c) _bit_clr(i2c->CCR, I2C_MASTER)
#define _i2c_ack(i2c) _bit_set(i2c->CCR, I2C_EN_ACK)
#define _i2c_nack(i2c) _bit_clr(i2c->CCR, I2C_EN_ACK)
#define _i2c_repeat_start(i2c) _bit_set(i2c->CCR, I2C_EN_REPEAT_START)
#define _i2c_reset_repeat_start(i2c) _bit_clr(i2c->CCR, I2C_EN_REPEAT_START)
#define _i2c_en_add_match_it(i2c) _bit_set(i2c->CCR, I2C_EN_ADDRESS_MATCH_IT)
#define _i2c_dis_add_match_it(i2c) _bit_clr(i2c->CCR, I2C_EN_ADDRESS_MATCH_IT)
#define _i2c_en_highspeed(i2c) _bit_set(i2c->CCR, I2C_EN_HIGH_SPEED_MODE)
#define _i2c_dis_highspeed(i2c) _bit_clr(i2c->CCR, I2C_EN_HIGH_SPEED_MODE)
#define _i2c_en_slave_highspeed_it(i2c) _bit_set(i2c->CCR, I2C_EN_SLAVE_HIGH_SPEED_MODE_IT)
#define _i2c_dis_slave_highspeed_it(i2c) _bit_clr(i2c->CCR, I2C_EN_SLAVE_HIGH_SPEED_MODE_IT)

#define _i2c_get_flag_tf(i2c) _bit_get(i2c->SR, I2C_FLAG_TF)
#define _i2c_get_flag_rc(i2c) _bit_get(i2c->SR, I2C_FLAG_RC)
#define _i2c_get_flag_aaslv(i2c) _bit_get(i2c->SR, I2C_FLAG_AASLV)
#define _i2c_get_flag_busy(i2c) _bit_get(i2c->SR, I2C_FLAG_BUSY)
#define _i2c_get_flag_arbl(i2c) _bit_get(i2c->SR, I2C_FLAG_ARBL)
#define _i2c_get_flag_rxtx(i2c) _bit_get(i2c->SR, I2C_FLAG_RXTX)
#define _i2c_get_flag_dack(i2c) _bit_get(i2c->SR, I2C_FLAG_DACK)
#define _i2c_get_flag_aack(i2c) _bit_get(i2c->SR, I2C_FLAG_AACK)
#define _i2c_get_flag_slave_high_speed(i2c) _bit_get(i2c->SHIR, I2C_FLAG_SLAVE_HIGH_SPEED)
#define _i2c_clr_flag_slave_high_speed(i2c) _bit_set(i2c->SHIR, I2C_FLAG_SLAVE_HIGH_SPEED)
#define _i2c_get_status(i2c) _reg_read(i2c->SR)

#define _i2c_en_clock_test_mode(i2c) _bit_set(i2c->PR, I2C_CLOCK_MODE_TEST)
#define _i2c_dis_clock_test_mode(i2c) _bit_clr(i2c->PR, I2C_CLOCK_MODE_TEST)
#define _i2c_en_clock_normal_mode(i2c) _bit_clr(i2c->PR, I2C_CLOCK_MODE_TEST)
#define _i2c_dis_clock_normal_mode(i2c) _bit_set(i2c->PR, I2C_CLOCK_MODE_TEST)

#define _i2c_pin_pullup_en(i2c, pin) _bit_set(i2c->PCR, 1 << (pin + I2C_PU_SHIFT_MASK))
#define _i2c_pin_pullup_dis(i2c, pin) _bit_clr(i2c->PCR, 1 << (pin + I2C_PU_SHIFT_MASK))
#define _i2c_pin_pulldown_en(i2c, pin) _bit_set(i2c->PCR, 1 << (pin + I2C_PD_SHIFT_MASK))
#define _i2c_pin_pulldown_dis(i2c, pin) _bit_clr(i2c->PCR, 1 << (pin + I2C_PD_SHIFT_MASK))
#define _i2c_pin_output_cmos(i2c, pin) _bit_clr(i2c->PCR, 1 << (pin + I2C_WOM_SHIFT_MASK))
#define _i2c_pin_output_opendrain(i2c, pin) _bit_set(i2c->PCR, 1 << (pin + I2C_WOM_SHIFT_MASK))

#define _i2c_set_sda_bit(i2c) _bit_set(i2c->PDR, 1 << I2C_PIN_SDA)
#define _i2c_reset_sda_bit(i2c) _bit_clr(i2c->PDR, (1 << I2C_PIN_SDA))
#define _i2c_set_scl_bit(i2c) _bit_set(i2c->PDR, 1 << I2C_PIN_SCL)
#define _i2c_reset_scl_bit(i2c) _bit_clr(i2c->PDR, (1 << I2C_PIN_SCL))
#define _i2c_get_sda_bit(i2c) _bit_get(i2c->PDR, (1 << I2C_PIN_SDA))
#define _i2c_get_scl_bit(i2c) _bit_get(i2c->PDR, (1 << I2C_PIN_SCL))
#define _i2c_pin_gpio(i2c, pin) _bit_set(i2c->PCR, 1 << (pin + I2C_PA_SHIFT_MASK))
#define _i2c_pin_primary_fun(i2c, pin) _bit_clr(i2c->PCR, 1 << (pin + I2C_PA_SHIFT_MASK))

#define _i2c_scl_configure_as_gpio(i2c) _bit_set(i2c->PCR, I2C_PIN_SCL_GPIO)
#define _i2c_scl_configure_as_primary(i2c) _bit_clr(i2c->PCR, I2C_PIN_SCL_GPIO)
#define _i2c_sda_configure_as_gpio(i2c) _bit_set(i2c->PCR, I2C_PIN_SDA_GPIO)
#define _i2c_sda_configure_as_primary(i2c) _bit_clr(i2c->PCR, I2C_PIN_SDA_GPIO)

#define _i2c_scl_cmos_mode(i2c) _bit_clr(i2c->PCR, I2C_PIN_SCL_CMOS_MODE)
#define _i2c_scl_open_drain_mode(i2c) _bit_set(i2c->PCR, I2C_PIN_SCL_CMOS_MODE)
#define _i2c_sda_cmos_mode(i2c) _bit_clr(i2c->PCR, I2C_PIN_SDA_CMOS_MODE)
#define _i2c_sda_open_drain_mode(i2c) _bit_set(i2c->PCR, I2C_PIN_SDA_CMOS_MODE)

#define _i2c_scl_dis_pullup(i2c) _bit_clr(i2c->PCR, I2C_PIN_SCL_EN_PULLUP)
#define _i2c_scl_en_pullup(i2c) _bit_set(i2c->PCR, I2C_PIN_SCL_DIS_PULLUP)
#define _i2c_sda_dis_pullup(i2c) _bit_clr(i2c->PCR, I2C_PIN_SDA_EN_PULLUP)
#define _i2c_sda_en_pullup(i2c) _bit_set(i2c->PCR, I2C_PIN_SDA_DIS_PULLUP)

#define _i2c_sda_dir_output(i2c) _bit_set(i2c->DDR, 0X02)
#define _i2c_sda_dir_input(i2c) _bit_clr(i2c->DDR, 0X02)
#define _i2c_scl_dir_output(i2c) _bit_set(i2c->DDR, 0X01)
#define _i2c_scl_dir_input(i2c) _bit_clr(i2c->DDR, 0X01)

#define _i2c_pin_dir_output(i2c, pin) _bit_set(i2c->DDR, (1 << pin))
#define _i2c_pin_dir_input(i2c, pin) _bit_clr(i2c->DDR, (1 << pin))
#define _i2c_set_pin_bit(i2c, pin) _bit_set(i2c->PDR, (1 << pin))
#define _i2c_reset_pin_bit(i2c, pin) _bit_clr(i2c->PDR, (1 << pin))
#define _i2c_get_pin_bit(i2c, pin) _bit_get(i2c->PDR, (1 << pin))

/**
 * @brief I2C 模块主从模式枚举定义
 * 
 */
typedef enum
{
    I2C_MODE_MASTER,
    I2C_MODE_SLAVE,
} i2c_mode_t;

 /**
  * @brief I2C 模块bit位枚举定义
  * 
  */
 typedef enum
 {
    I2C_SLAVE_ADD_7BITS = 0x00,
    I2C_SLAVE_ADD_10BITS = 0x01,
} i2c_slave_addbits_t;

/**
 * @brief I2C 模块标志枚举定义
 * 
 */
typedef enum
{
    I2C_FLAG_INDEX_TF,
    I2C_FLAG_INDEX_RC,
    I2C_FLAG_INDEX_ASLV,
    I2C_FLAG_INDEX_BUSY,
    I2C_FLAG_INDEX_ARBL,
    I2C_FLAG_INDEX_RXTX,
    I2C_FLAG_INDEX_DACK,
    I2C_FLAG_INDEX_AACK,
} i2c_flag_index_t;

/**
 * @brief I2C 模块中断枚举定义
 * 
 */
typedef enum
{
    I2C_IT_INDEX_IEN = 0X02,
    I2C_IT_INDEX_AMIE = 0X20,
    I2C_IT_INDEX_SLV_HSIE = 0X80,
} i2c_it_index_t;

/**
 * @brief I2C 模块初始化枚举定义
 * 
 */
typedef struct
{
    uint8_t Mode;
    uint8_t Prescaler;
    uint8_t ClockMode;
    functionalstate_t HighSpeed;
    uint16_t Add;
    i2c_slave_addbits_t AddBits;
} i2c_init_t;

// 函数声明
void drv_i2c_clrflagslavehighspeed(reg_i2c_t *pi2c);
void drv_i2c_generate_stop(reg_i2c_t *pi2c);
void drv_i2c_generate_start(reg_i2c_t *pi2c);
void drv_i2c_enaddmatchit(reg_i2c_t *pi2c);
void drv_i2c_disaddmatchit(reg_i2c_t *pi2c);
void drv_i2c_enit(reg_i2c_t *pi2c);
void drv_i2c_disit(reg_i2c_t *pi2c);
void drv_i2c_ack(reg_i2c_t *pi2c);
void drv_i2c_nack(reg_i2c_t *pi2c);
status_t drv_i2c_deinit(reg_i2c_t *pi2c);
status_t drv_i2c_init(reg_i2c_t *pi2c, i2c_init_t *pinit);
void drv_i2c_cmd(reg_i2c_t *pi2c, functionalstate_t NewState);
void drv_i2c_itcmd(reg_i2c_t *pi2c,i2c_it_index_t index,functionalstate_t NewState);
status_t drv_i2c_getflag(reg_i2c_t *pi2c,i2c_flag_index_t index,flagstatus_t *pFlag);
status_t drv_i2c_waitonflagtimeout(reg_i2c_t *pi2c,i2c_flag_index_t index,flagstatus_t status,uint32_t timeout);
status_t drv_i2c_waitonslvhsflagtimeout(reg_i2c_t *pi2c,flagstatus_t status,uint32_t timeout);
status_t drv_i2c_masterwriterequest(reg_i2c_t *pi2c,uint8_t SlaveAdd,i2c_slave_addbits_t Addbits,uint32_t timeout);
status_t drv_i2c_masterreadrequest(reg_i2c_t *pi2c,uint8_t SlaveAdd,i2c_slave_addbits_t Addbits,uint32_t timeout);
status_t drv_i2c_mastergeneratestop(reg_i2c_t *pi2c,functionalstate_t NewState,uint32_t timeout);
status_t drv_i2c_masterrestartreadrequest(reg_i2c_t *pi2c,uint8_t SlaveAdd,uint32_t timeout);
status_t drv_i2c_masterhighspeedwriterequest(reg_i2c_t *pi2c,uint8_t SLaveAdd,i2c_slave_addbits_t Addbits,uint32_t timeout);
status_t drv_i2c_transmitbyte(reg_i2c_t *pi2c,uint8_t tosend,uint32_t timeout);
status_t drv_i2c_receivebyte(reg_i2c_t *pi2c,uint8_t *Rx,uint32_t timeout);
status_t drv_i2c_transmit(reg_i2c_t *pi2c,uint8_t SlaveAdd,i2c_slave_addbits_t Addbits,functionalstate_t Highspeed,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_receive(reg_i2c_t *pi2c,uint8_t SlaveAdd,i2c_slave_addbits_t Addbits,functionalstate_t Highspeed,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_transmitit(reg_i2c_t *pi2c,uint8_t SlaveAdd,functionalstate_t Highspeed,uint8_t *pBuf,uint32_t Size);
status_t drv_i2c_receiveit(reg_i2c_t *pi2c,uint8_t SlaveAdd,functionalstate_t Highspeed,uint8_t *pBuf,uint32_t Size);
status_t drv_i2c_memwrite(reg_i2c_t *pi2c,uint8_t SlaveAdd,i2c_slave_addbits_t Addbits,uint32_t MemAdd,uint8_t MemAddBytes,functionalstate_t Highspeed,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_memread(reg_i2c_t *pi2c,uint8_t SlaveAdd,i2c_slave_addbits_t Addbits,uint32_t MemAdd,uint8_t MemAddBytes,functionalstate_t Highspeed,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_slavetransmitreceive(reg_i2c_t *pi2c,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_slavetransmit(reg_i2c_t *pi2c,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_slavereceive(reg_i2c_t *pi2c,uint8_t *pBuf,uint32_t Size,uint32_t timeout);
status_t drv_i2c_getitsource(reg_i2c_t *pi2c,uint8_t *pItSource);
status_t drv_i2c_getitflags(reg_i2c_t *pi2c,uint8_t *pBasicFlags,uint8_t *pSlvHighspeedFlags);
void drv_i2c_getdr(reg_i2c_t *pi2c, uint8_t *pData);
void drv_i2c_setdr(reg_i2c_t *pi2c, uint8_t Data);
status_t drv_i2c_gpioinit(reg_i2c_t *pi2c, gpio_init_t *Init);
status_t drv_i2c_gpiodeinit(reg_i2c_t *pi2c, uint8_t pin);
void drv_i2c_writepin(reg_i2c_t *pi2c,uint8_t pin,gpio_pinstate_t state);
void drv_i2c_togglepin(reg_i2c_t *pi2c, uint8_t pin);
gpio_pinstate_t drv_i2c_readpin(reg_i2c_t *pi2c, uint8_t pin);
void drv_i2c_dis(reg_i2c_t *pi2c);
void drv_i2c_en(reg_i2c_t *pi2c);
#ifdef __cplusplus
}

#endif

#endif
