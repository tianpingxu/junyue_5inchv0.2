/**
  ******************************************************************************
             Copyright(c) 2020 China Core Co. Ltd.
                      All Rights Reserved
  ******************************************************************************
  * @file    i2c_hal.h
  * @author  Product application department
  * @version V1.0
  * @date    2020.02.13
  * @brief   Header file of I2C HAL module.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WM8978_HAL_H
#define __WM8978_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "i2c_drv.h"
#include "type.h"


// 全局变量定义
#define WM8978_ADDR 0X1A // WM8978的器件地址,固定为0X1A

#define EQ1_80Hz 0X00
#define EQ1_105Hz 0X01
#define EQ1_135Hz 0X02
#define EQ1_175Hz 0X03

#define EQ2_230Hz 0X00
#define EQ2_300Hz 0X01
#define EQ2_385Hz 0X02
#define EQ2_500Hz 0X03

#define EQ3_650Hz 0X00
#define EQ3_850Hz 0X01
#define EQ3_1100Hz 0X02
#define EQ3_14000Hz 0X03

#define EQ4_1800Hz 0X00
#define EQ4_2400Hz 0X01
#define EQ4_3200Hz 0X02
#define EQ4_4100Hz 0X03

#define EQ5_5300Hz 0X00
#define EQ5_6900Hz 0X01
#define EQ5_9000Hz 0X02
#define EQ5_11700Hz 0X03

// 函数声明
uint8_t WM8978_Init(reg_i2c_t *pi2c);
void WM8978_ADDA_Cfg(uint8_t dacen, uint8_t adcen);
void WM8978_Input_Cfg(uint8_t micen, uint8_t lineinen, uint8_t auxen);
void WM8978_Output_Cfg(uint8_t dacen, uint8_t bpsen);
void WM8978_MIC_Gain(uint8_t gain);
void WM8978_LINEIN_Gain(uint8_t gain);
void WM8978_AUX_Gain(uint8_t gain);
uint8_t WM8978_Write_Reg(uint8_t reg, uint16_t val);
uint16_t WM8978_Read_Reg(uint8_t reg);
void WM8978_HPvol_Set(uint8_t voll, uint8_t volr);
void WM8978_SPKvol_Set(uint8_t volx);
void WM8978_I2S_Cfg(uint8_t fmt, uint8_t len);
void WM8978_3D_Set(uint8_t depth);
void WM8978_EQ_3D_Dir(uint8_t dir);
void WM8978_EQ1_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ2_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ3_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ4_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ5_Set(uint8_t cfreq, uint8_t gain);

#ifdef __cplusplus
}

#endif

#endif /* __WM8978_H */
