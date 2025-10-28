/*
 * protocol.c
 *
 *  Created on: 2024年4月7日
 *      Author: TianPing Xu
 */

#include "protocol.h"
#include "def.h"
#include "uart_test.h"
#include "sys.h"

DEV_INFO dev_info;
DEV_DEF_ATTR dev_def_attr;

#define RCV_QUEUE_LEN   (360)

static uint8_t *rcv_queue_in;
static uint8_t *rcv_queue_out;
static uint8_t rcv_sQueue[RCV_QUEUE_LEN];

static void rcv_queue_input(uint8_t value) {
    if(1 == rcv_queue_out - rcv_queue_in || (rcv_queue_in > rcv_queue_out && (rcv_queue_in - rcv_queue_out) >= RCV_QUEUE_LEN)) {
        // queue full
    }else {
        // queue not full
        if(rcv_queue_in >= rcv_sQueue + RCV_QUEUE_LEN){
            rcv_queue_in = rcv_sQueue;
        }
        *rcv_queue_in++ = value;
    }
}

static uint8_t rcv_queue_output(void) {
    uint8_t value = 0;
    if(rcv_queue_out != rcv_queue_in) {
        // have data in queue
        if(rcv_queue_out >= rcv_sQueue + RCV_QUEUE_LEN) {
            rcv_queue_out = rcv_sQueue;
        }
        value = *rcv_queue_out++;
    }
    return value;
}

static uint8_t rcv_is_empty(void) {
    return rcv_queue_out != rcv_queue_in;
}

uint8_t rcv_buff_len = 7;
uint8_t rcv_buff[RCV_QUEUE_LEN];

void rx_data_hadle(void)
{
    static uint16_t rx_in = 0;
    uint16_t rx_offset = 0;
    uint16_t crc_data = 0;
    while((rx_in < RCV_QUEUE_LEN) && rcv_is_empty()){
        rcv_buff[rx_in++] = rcv_queue_output();
    }

    while((rx_in - rx_offset) >= 5) {
        //帧头校验
        if((rcv_buff[rx_offset] != HEADER_1) || (rcv_buff[rx_offset + 1] != HEADER_2)){
            rx_offset++;
            printf("rcv_head_err\r\n");
            if(rx_in == rx_offset) { // 没有找到帧头
                rx_in -= rx_offset;
                return;
            }else {
                continue;
            }
        }
        if(rcv_buff[rx_offset + 2 == M_TO_T]) {
            switch(rcv_buff[rx_offset + 3]) {
            case HUMAN_SENSE_STATE:
                rcv_buff_len = 7;
                dev_info.human_sense_status = rcv_buff[4 + rx_offset];
                buff_generate(HUMAN_SENSE_STATE, dev_info.human_sense_status);
                // human_sense_handle();
                break;
            case FAN_SPEED:
                rcv_buff_len = 7;
                break;
            case M_LIGHT_LUM:
                rcv_buff_len = 7;
                break;
            case M_LIGHT_TEMP:
                rcv_buff_len = 7;
                break;
            case S_LIGHT_LUM:
                rcv_buff_len = 7;
                break;
            case S_LIGHT_TEMP:
                rcv_buff_len = 7;
                break;
            case ATMOSPHERE_LUM:
                rcv_buff_len = 7;
                break;
            case ATMOSPHERE_COLOR:
                rcv_buff_len = 7;
                break;
            case FAN_COUNTDOWN_SET:
                rcv_buff_len = 8;
                break;
            case HUMAN_SENSE_DELAY:
                rcv_buff_len = 8;
                break;
            default:
                break;
            }
        }
		
        if(rcv_buff[2 + rx_offset] == 0xEF && rcv_buff[3 + rx_offset] == 0xEF && rcv_buff[4 + rx_offset] == 0xEF) {
            sys_startupconfig(0, ENABLE);
                while (1)
                    ;
        }else if(rcv_buff[2 + rx_offset] == 0xFE && rcv_buff[3 + rx_offset] == 0xFE && rcv_buff[4 + rx_offset] == 0xFE) {
            rcv_buff_len = 5;
            uint8_t data_len = 0;
            uint16_t crc_data = 0;
            uint8_t frame1[64] = {HEADER_1, HEADER_2, 0xFE, 0xFE};
            data_len = 6 + strlen(DEV_VERSION);
            for(uint8_t i = 0; i < data_len; i++) {
                frame1[4 + i] = DEV_VERSION[i];
            }
            crc_data = gen_crc16_ccitt_stream(frame1, data_len - 2);
            frame1[data_len - 2] = crc_data & 0xFF;
            frame1[data_len - 1] = crc_data >> 8;
            buff_send_to_uart(frame1, data_len);
        }else {
        }
        rx_offset += rcv_buff_len;
        break;
    }
    rx_in -= rx_offset;
    if(rx_in > 0) xtp_memcpy(rcv_buff, rcv_buff + rx_offset, rx_in);
}

//接收数据
void rx_data_input(uint8_t* buf, uint16_t len)
{
    // printf("len = %d ---- ", len);
    for(uint8_t i = 0; i < len; i++) {
        rcv_queue_input(buf[i]);
        printf("%02X ", buf[i]);
    }
    // printf("\r\n");
}


/**********************************************************protocol cmd send ***********************************************************/

#define SEND_QUEUE_LEN   (360)

static uint8_t *send_queue_in;
static uint8_t *send_queue_out;
static uint8_t send_sQueue[SEND_QUEUE_LEN];

static void send_queue_input(uint8_t value) {
    if(1 == send_queue_out - send_queue_in || (send_queue_in > send_queue_out && (send_queue_in - send_queue_out) >= SEND_QUEUE_LEN)) {
        // queue full
    }else {
        // queue not full
        if(send_queue_in >= send_sQueue + SEND_QUEUE_LEN){
            send_queue_in = send_sQueue;
        }
        *send_queue_in++ = value;
    }
}
static uint8_t send_queue_output(void) {
    uint8_t value = 0;
    if(send_queue_out != send_queue_in) {
        // have data in queue
        if(send_queue_out >= send_sQueue + SEND_QUEUE_LEN) {
            send_queue_out = send_sQueue;
        }
        value = *send_queue_out++;
    }
    return value;
}

static uint8_t send_is_empty(void) {
    return send_queue_out != send_queue_in;
}

uint8_t send_buff_len = 7;
uint8_t send_buff[SEND_QUEUE_LEN];

void tx_data_hadle(void)
{
    // printf("tx_data_hadle\r\n");
    static uint16_t tx_in = 0;
    uint16_t offset = 0;
    uint16_t crc_data = 0;
    while((tx_in < SEND_QUEUE_LEN) && send_is_empty()){
        send_buff[tx_in++] = send_queue_output();
    }

    while((tx_in - offset) >= 7) {
        //帧头校验
        if((send_buff[offset] != HEADER_1) || (send_buff[offset + 1] != HEADER_2)){
            offset++;
            // printf("head_err\r\n");
            if(tx_in == offset) { // 没有找到帧头
                tx_in -= offset;
                return;
            }else {
                continue;
            }
        }
        if(send_buff[offset + 3] == HUMAN_SENSE_DELAY || send_buff[offset + 3] == FAN_COUNTDOWN_SET) {
            send_buff_len = 8;
        }else {
            send_buff_len = 7;
        }
        //数据处理
        buff_send_to_uart(send_buff + offset, send_buff_len);
        offset += send_buff_len;
        break;
    }
    tx_in -= offset;
    if(tx_in > 0) xtp_memcpy(send_buff, send_buff + offset, tx_in);
}

void dev_attr_init(void)
{
    send_queue_in = send_sQueue;
    send_queue_out = send_sQueue;

    rcv_queue_in = rcv_sQueue;
    rcv_queue_out = rcv_sQueue;

    XY_Read();
    dev_info.fan_speed = dev_def_attr.default_fan_speed;
    dev_info.m_light_lum = dev_def_attr.default_m_light_lum;
    dev_info.s_light_lum = dev_def_attr.default_s_light_lum;
    dev_info.m_light_temp = dev_def_attr.default_m_light_temp;
    dev_info.s_light_temp = dev_def_attr.default_s_light_temp;
}

//指令生成
void buff_generate(uint8_t fun, uint8_t data) {
	//指令数组
    send_buff_len = 7;
    uint16_t crc_data1 = 0x00;
	uint8_t frame1[7] = {HEADER_1, HEADER_2, T_TO_M, fun, data};
    crc_data1 = gen_crc16_ccitt_stream(frame1, 5);
    frame1[5] = crc_data1 & 0xFF;
	frame1[6] = crc_data1 >> 8;
	for(uint8_t i = 0; i < 7; i++) {
		send_queue_input(frame1[i]);
	}
}

void rodar_buff_generate(uint16_t time) {
	send_buff_len = 8;
    uint16_t crc_data2 = 0x00;
	uint8_t data_low = 0x00, data_high = 0x00;

	data_low = time & 0x00FF;
	data_high = (time >> 8) & 0x00FF;

	uint8_t frame2[8] = {HEADER_1, HEADER_2, T_TO_M, HUMAN_SENSE_DELAY, data_low, data_high};
    crc_data2 = gen_crc16_ccitt_stream(frame2, 6);
    frame2[6] = crc_data2 & 0xFF;
	frame2[7] = crc_data2 >> 8;

	for(uint8_t i = 0; i < 8; i++) {
		send_queue_input(frame2[i]);
	}
}

void auto_buff_generate(uint8_t time1, uint16_t time2) {
	send_buff_len = 8;
    uint16_t crc_data3 = 0x00;

	uint8_t frame3[8] = {HEADER_1, HEADER_2, T_TO_M, FAN_COUNTDOWN_SET, time1, time2};
    crc_data3 = gen_crc16_ccitt_stream(frame3, 6);
    frame3[6] = crc_data3 & 0xFF;
	frame3[7] = crc_data3 >> 8;

	for(uint8_t i = 0; i < 8; i++) {
		send_queue_input(frame3[i]);
	}
}

/****************************************************************flash program************************************************************/
#include "ssi_hal.h"

#define DATA_BEGIN_ADDR     (0x14E98000)
#define DATA_LEN            (0x1000)
uint8_t wr_data[DATA_LEN];

void XY_Reset(void) {
    printf("XY_Reset\r\n");
    dev_def_attr.default_fan_speed = 60;
    dev_def_attr.default_m_light_lum = 60;
    dev_def_attr.default_s_light_lum = 60;
    dev_def_attr.default_a_light_lum = 60;
    dev_def_attr.default_m_light_temp = 50;
    dev_def_attr.default_s_light_temp = 50;
    dev_def_attr.default_a_light_temp = 50;
    
    dev_def_attr.dev_rodar_time = 8;
    dev_def_attr.Auto_vent_onoff = 1;
    dev_def_attr.Interval_time = 1;
    dev_def_attr.Duration_time = 3;

    dev_def_attr.language_type = LANGUAGE_EN;

    dev_def_attr.ui_version = 1;

    dev_def_attr.save_cnt = 0;
}

int XY_Write(void)
{
    printf("XY_Write\r\n");
	int idx = 0;
	memset(wr_data, 0x00, DATA_LEN);

    dev_def_attr.power_first = FIRST_POWER_ON;
	dev_def_attr.save_flag = DATA_SAVE_OK;
	dev_def_attr.save_cnt++;

	wr_data[idx++] = dev_def_attr.default_fan_speed;
	wr_data[idx++] = dev_def_attr.default_m_light_lum;
	wr_data[idx++] = dev_def_attr.default_s_light_lum;
    wr_data[idx++] = dev_def_attr.default_a_light_lum;
	wr_data[idx++] = dev_def_attr.default_m_light_temp;
	wr_data[idx++] = dev_def_attr.default_s_light_temp;
    wr_data[idx++] = dev_def_attr.default_a_light_temp;

    wr_data[idx++] = dev_def_attr.dev_rodar_time;
    wr_data[idx++] = dev_def_attr.Auto_vent_onoff;
    wr_data[idx++] = dev_def_attr.Interval_time;
    wr_data[idx++] = dev_def_attr.Duration_time;

    wr_data[idx++] = dev_def_attr.language_type;

    wr_data[idx++] = dev_def_attr.ui_version;

	wr_data[idx++] = dev_def_attr.power_first;
	wr_data[idx++] = dev_def_attr.save_flag;
	wr_data[idx++] = dev_def_attr.save_cnt;

    printf("save_dev_def_attr.ui_version = %d\r\n", dev_def_attr.ui_version);

    /*暂时关闭所有的中断允许*/
    __disable_irq();

	// printf("Erase start\r\n");
	if(hal_ssi_flash_sector_erase(DATA_BEGIN_ADDR) == STATUS_OK) {
		// printf("Program start\r\n");
		if(hal_ssi_flash_program(DATA_BEGIN_ADDR, wr_data, DATA_LEN) == STATUS_OK) {
			printf("saved!\r\n");

            /*打开所有中断允许*/
            __enable_irq();
			return 1;
		}
	}else {
        /*打开所有中断允许*/
        __enable_irq();
        return 1;
	}
	return 0;
}
int XY_Read(void)
{
    printf("XY_Read\r\n");
	int idx = 0;
	uint8_t low_byte, high_byte;
	memset(wr_data, 0x00, DATA_LEN);
	hal_ssi_flash_read(DATA_BEGIN_ADDR, wr_data, DATA_LEN);

	dev_def_attr.default_fan_speed = wr_data[idx++];
	dev_def_attr.default_m_light_lum = wr_data[idx++];
	dev_def_attr.default_s_light_lum = wr_data[idx++];
	dev_def_attr.default_a_light_lum = wr_data[idx++];
	dev_def_attr.default_m_light_temp = wr_data[idx++];
    dev_def_attr.default_s_light_temp = wr_data[idx++];
    dev_def_attr.default_a_light_temp = wr_data[idx++];

    dev_def_attr.dev_rodar_time = wr_data[idx++];
    dev_def_attr.Auto_vent_onoff = wr_data[idx++];
    dev_def_attr.Interval_time = wr_data[idx++];
    dev_def_attr.Duration_time = wr_data[idx++];

    dev_def_attr.language_type = wr_data[idx++];

    dev_def_attr.ui_version = wr_data[idx++];
	
	dev_def_attr.power_first = wr_data[idx++];
	dev_def_attr.save_flag = wr_data[idx++];
	dev_def_attr.save_cnt = wr_data[idx++];

    printf("read_dev_def_attr.ui_version = %d\r\n", dev_def_attr.ui_version);

	if(dev_def_attr.power_first == FIRST_POWER_ON) {
		printf("language_type = %d\r\n", dev_def_attr.language_type);
	}else {
        printf("first_power_on\r\n");
        XY_Reset();
        XY_Write();
    }
	return 1;
}













