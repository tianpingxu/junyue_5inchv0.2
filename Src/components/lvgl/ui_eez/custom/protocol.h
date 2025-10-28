/*
 * protocol.h
 *
 *  Created on: 2025年4月7日
 *      Author: TianPing Xu
 */

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "stdint.h"
#include "crc16.h"

#define DEV_VERSION        "HEM_JYC_5_250731_V1.0.0"

#define DATA_SAVE_OK       0x98
#define FIRST_POWER_ON     0x10

//包头
#define HEADER_1           0x55
#define HEADER_2           0xAA

//数据收发
#define T_TO_M             0x25
#define M_TO_T             0x26

//功能
#define M_LIGHT_ONOFF      0x01
#define M_LIGHT_LUM        0x02
#define M_LIGHT_TEMP       0x03

#define FAN_ONOFF          0x04
#define FAN_SPEED          0x05

#define S_LIGHT_ONOFF      0x06
#define S_LIGHT_LUM        0x07
#define S_LIGHT_TEMP       0x08

#define ATMOSPHERE_ONOFF   0x09
#define ATMOSPHERE_LUM     0x10
#define ATMOSPHERE_COLOR   0x11

#define HUMAN_SENSE_STATE  0x20

#define FAN_COUNTDOWN_SET  0x21

#define HUMAN_SENSE_DELAY  0x22

void rx_data_hadle(void);

void rx_data_input(uint8_t* buf, uint16_t len);
void tx_data_hadle(void);

void buff_generate(uint8_t fun, uint8_t data);
void rodar_buff_generate(uint16_t time);
void auto_buff_generate(uint8_t time1, uint16_t time2);

void dev_attr_init(void);

void XY_Reset(void);
int XY_Write(void);
int XY_Read(void);

#endif //PROTOCOL_H
