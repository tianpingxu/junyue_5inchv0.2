/**
 * @file st77102.c
 * @author Product application department
 * @brief 驱动芯片st77102驱动程序
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
/*** 头文件定义 ***************************************************************/
#include "type.h"
#include "eport_drv.h"
#include "tp_interface.h"
#include "st77102.h"
#include "pinswap_drv.h"
#include "i2c_hal.h"
/*** 全局变量定义 ***************************************************************/
extern tp_handle_t tp_dev;

/*** 函数定义 *******************************************************************/

#define Touch_I2C_SCL_1()	hal_eport_writepinlevel(TOUCH_SCL_GPIO_PORT, TOUCH_SCL_GPIO_PIN, GPIO_HIGH)    /* SCL = 1 */
#define Touch_I2C_SCL_0()	hal_eport_writepinlevel(TOUCH_SCL_GPIO_PORT, TOUCH_SCL_GPIO_PIN, GPIO_LOW)      /* SCL = 0 */

#define Touch_I2C_SDA_1()	hal_eport_writepinlevel(TOUCH_SDA_GPIO_PORT, TOUCH_SDA_GPIO_PIN, GPIO_HIGH)     /* SDA = 1 */
#define Touch_I2C_SDA_0()	hal_eport_writepinlevel(TOUCH_SDA_GPIO_PORT, TOUCH_SDA_GPIO_PIN, GPIO_LOW)      /* SDA = 0 */

#define Touch_I2C_SDA_OUTPUT()	hal_eport_output(TOUCH_SDA_GPIO_PORT, TOUCH_SDA_GPIO_PIN)
#define Touch_I2C_SDA_INPUT()	hal_eport_input(TOUCH_SDA_GPIO_PORT, TOUCH_SDA_GPIO_PIN, PS_PULL_UP)

#define Touch_I2C_SDA_READ()	hal_eport_readpinslevel(TOUCH_SDA_GPIO_PORT, TOUCH_SDA_GPIO_PIN)            /*read SDA*/

void Touch_I2C_Delay()
{
	delay(10);
}

void Touch_I2C_Delay1_2()
{
    delayus(100);
}

void Touch_I2C_Start(void)
{
    Touch_I2C_SDA_OUTPUT();
    Touch_I2C_SDA_1();
	Touch_I2C_SCL_1();
    Touch_I2C_Delay1_2();
	Touch_I2C_SDA_0();
    Touch_I2C_Delay1_2();
	Touch_I2C_SCL_0();
    Touch_I2C_Delay1_2();
}

void Touch_I2C_Stop(void)
{  
    Touch_I2C_SDA_OUTPUT();
    Touch_I2C_SDA_0();
	Touch_I2C_SCL_1();
    Touch_I2C_Delay1_2();
	Touch_I2C_SDA_1();
    Touch_I2C_Delay1_2();
}

void Touch_I2C_SendByte(uint8_t ucByte)
{
    Touch_I2C_SDA_OUTPUT();
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		if(ucByte & 0x80)
		{
			Touch_I2C_SDA_1();
		}
		else
		{
			Touch_I2C_SDA_0();
		}
		Touch_I2C_Delay1_2();
		Touch_I2C_SCL_1();
        Touch_I2C_Delay1_2();
		Touch_I2C_SCL_0();
        Touch_I2C_Delay1_2();
		if(i == 7)
		{
			Touch_I2C_SDA_1();
		}
		ucByte <<= 1;
	}
}

uint8_t Touch_I2C_ReadByte(void)
{
    uint8_t i;
	uint8_t value = 0x00;
    Touch_I2C_SDA_INPUT();
	for( i = 0; i < 8; i++)
	{
		value <<= 1;
		Touch_I2C_SCL_1();
        Touch_I2C_Delay1_2();

		if(Touch_I2C_SDA_READ())
		{
			value++;
		}
        Touch_I2C_Delay1_2();
		Touch_I2C_SCL_0();
        Touch_I2C_Delay1_2();
	}
    return value;
}

uint8_t Touch_I2C_WaitAck(void)
{   
    uint8_t re;
    Touch_I2C_SDA_OUTPUT();
	Touch_I2C_SDA_1();
    Touch_I2C_Delay1_2();
	Touch_I2C_SCL_1();
    Touch_I2C_Delay1_2();
    Touch_I2C_SDA_INPUT();
	if(Touch_I2C_SDA_READ())
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
    Touch_I2C_Delay1_2();
	Touch_I2C_SCL_0();
    Touch_I2C_Delay1_2();
	return re;
}

void Touch_I2C_Ack(void)
{
    Touch_I2C_SDA_OUTPUT();
    Touch_I2C_SDA_0();
    Touch_I2C_Delay1_2();
	Touch_I2C_SCL_1();
	Touch_I2C_Delay1_2();
	Touch_I2C_SCL_0();
    Touch_I2C_Delay1_2();
	Touch_I2C_SDA_1();
}

void Touch_I2C_NoAck(void)
{
    Touch_I2C_SDA_OUTPUT();
    Touch_I2C_SDA_1();
    Touch_I2C_Delay1_2();
	Touch_I2C_SCL_1();
	Touch_I2C_Delay1_2();
	Touch_I2C_SCL_0();
    Touch_I2C_Delay1_2();
}

uint32_t Touch_I2C_ReadBytes(uint8_t deviceAddr, uint8_t* pBuffer, uint16_t NumByteToRead)
{
	
	/* step 1: start I2C */
	Touch_I2C_Start();
	/* step 2: send device address and w/r control. */
	Touch_I2C_SendByte(deviceAddr | Touch_I2C_RD);
	/* step 3: wait ack. */
	if (Touch_I2C_WaitAck() != 0)
	{
		/* stop I2C */ 
        Touch_I2C_Stop();
        return 1;
	}
	Touch_I2C_Delay();
    while(NumByteToRead) 
    {
        *pBuffer = Touch_I2C_ReadByte();
        
        /* increment the pointer. */
        pBuffer++; 
		
        if(NumByteToRead == 1)
        {
            Touch_I2C_NoAck();	/* Read the last byte data,then cpu send NoACK(SDA = 1). */
        }  
        else 
		{
        	Touch_I2C_Ack();	/* Send ack(SDA = 0). */     
        }      
        /* decrement the counter. */
        NumByteToRead--;
    }
	/* Stop I2C. */
	Touch_I2C_Stop();
	return 0;	/* Seccessful. */
}

uint32_t Touch_I2C_WriteBytes(uint8_t deviceAddr, uint8_t* pBuffer, uint8_t NumByteToWrite)
{
    uint16_t m;	
    Touch_I2C_Stop();
    for (m = 0; m < 10; m++)
    {				
        /* step 1: start I2C */
        Touch_I2C_Start();
        /* step 2: send device address and w/r control. */
        Touch_I2C_SendByte(deviceAddr | Touch_I2C_WR);	/* ?????? */
        /* step 3: wait ack. */
        if (Touch_I2C_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 10)
    {
        Touch_I2C_Stop();
        return 1;
    }	
    Touch_I2C_Delay();
    while(NumByteToWrite--)
    {
        /* step 4:send data */
        Touch_I2C_SendByte(*pBuffer);
        /* step 5:wait ack. */
        if (Touch_I2C_WaitAck() != 0)
        {
            Touch_I2C_Stop();
            return 1;
        }
        Touch_I2C_Delay();
        pBuffer++;	/* increment the pointer. */
    }
	/* stop I2C */
	Touch_I2C_Stop();
	return 0;
}

static int ST__I2C_Transfer( struct ST_i2c_msg *msgs,int num)
{
    int im = 0;
    int ret = 0;
    for (im = 0; ret == 0 && im != num; im++)
    {
        if ((msgs[im].flags & Touch_I2C_RD))
        {
            ret = Touch_I2C_ReadBytes(msgs[im].addr, msgs[im].buf, msgs[im].len);
        }
        else
        {
            ret = Touch_I2C_WriteBytes(msgs[im].addr, msgs[im].buf, msgs[im].len);
        }
    }
    if(ret) return ret;

    return im;
}

int32_t ST__I2C_Read(uint8_t client_addr, uint8_t *buf, int32_t len)
{
    struct ST_i2c_msg msgs[2];
    int32_t ret = -1;
    int32_t retries = 0;
 
    msgs[0].flags = Touch_I2C_WR;
    msgs[0].addr  = client_addr;
    msgs[0].len   = ST77102_REGITER_LEN;
    msgs[0].buf   = &buf[0];

    msgs[1].flags = Touch_I2C_RD;
    msgs[1].addr  = client_addr;
    msgs[1].len   = len - ST77102_REGITER_LEN;
    msgs[1].buf   = &buf[ST77102_REGITER_LEN];

    while(retries < 5)
    {
        ret = ST__I2C_Transfer(msgs, 2);
        if(ret == 2)break;
        retries++;
    }
    if((retries >= 5))
    {
        return -1;
    }
    return ret;
}

int32_t ST__I2C_Write(uint8_t client_addr,uint8_t *buf,int32_t len)
{
    struct ST_i2c_msg msg;
    int32_t ret = -1;
    int32_t retries = 0;

    msg.flags = Touch_I2C_WR;
    msg.addr  = client_addr;
    msg.len   = len;
    msg.buf   = buf;

    while(retries < 5)
    {
        ret = ST__I2C_Transfer(&msg, 1);
        if (ret == 1)break;
        retries++;
    }
    if((retries >= 5))
    {
    }
    return ret;
}
 
/**
 * @brief GT9XX 中断IO 输出模块初始化函数
 * 
 */
static void int_io_init(void)
{
    SwitchPinFunction(UART4_TX_FUN,EPORT3_PIN6_FUN);
    hal_eport_output(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT);
}
/**
 * @brief GT9XX 中断IO输入模式上拉初始化函数
 * 
 */
static void int_init(void)
{
    hal_eport_input(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT,PS_PULL_UP);
}
/**
 * @brief GT9XX 复位IO输出模式初始化函数
 * 
 */
static void reset_io_init(void)
{
    SwitchPinFunction(UART4_RX_FUN,EPORT3_PIN7_FUN);
    hal_eport_output(TOUCH_CPT_PORT_RST, TOUCH_CPT_PIN_RST);
}
/**
 * @brief GT9XX I2C初始化函数
 * 
 */
void st77102_i2c_init(void)
{
	SwitchPinFunction(UART5_TX_FUN, EPORT4_PIN6_FUN); // EPORT4_PIN6_FUN
    hal_eport_output(EPORT4, EPORT4_PIN6);
    SwitchPinFunction(UART5_RX_FUN, EPORT4_PIN7_FUN); // EPORT4_PIN7_FUN
    hal_eport_output(EPORT4, EPORT4_PIN7);
    
    //i2c stop
	Touch_I2C_Stop();
}
/**
 * @brief GT9XX 上电复位函数
 * 
 */
void st77102_reset(void)
{
    reset_io_init();
    hal_eport_writepinlevel(TOUCH_CPT_PORT_RST, TOUCH_CPT_PIN_RST, GPIO_LOW);
    delayms(10);
    hal_eport_writepinlevel(TOUCH_CPT_PORT_RST, TOUCH_CPT_PIN_RST, GPIO_HIGH);
    delayms(10);  
    hal_eport_writepinlevel(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT, GPIO_LOW);
    delayms(100);	
}

/**
 * @brief GT9XX 初始化函数
 * 
 * @return tp_status_t 初始化成功/失败
 */
tp_status_t st77102_init(void)
{
    uint8_t temp[4];
    memset(temp, 0, 4);
    st77102_reset();
    st77102_i2c_init();

    temp[0] = 0x00;
    temp[1] = 0x0A;
    ST__I2C_Read(ST77102_SALVE_ADDR, temp, 4);
    printf("counter=%d\r\n",temp[2]);
    if(temp[2] == 0)
    {
        return TP_ERR; // 通信失败
    }
    return TP_OK;
}

static int16_t last_x = 0;
static int16_t last_y = 0;
static int16_t last_state = 0;
void st7102_data_proc(uint8_t *input_buff)
{
	uint8_t *read_buf = input_buff;
	int16_t input_x = 0;
	int16_t input_y = 0;
	int16_t input_w = 0;

    // printf("read_buf: ");
    // for(int i = 0; i < 9; i++)
    // {
    //     printf("0x%02X ", read_buf[i]);
    // }
    // printf("\r\n");
	if(read_buf[4] & 0x80)
	{
		read_buf[3 + 1] &= 0x3f;

		input_x = read_buf[3 + 2] | (read_buf[3 + 1] << 8);	/* x */
		input_y = read_buf[3 + 4] | (read_buf[3 + 3] << 8);	/* y */
		input_w = read_buf[3 + 5];

		if(input_x > 480 || input_y < 0)
		{
            // printf("read_point_over_range");
            // printf("---err %d %d \r\n", input_x, input_y);
			tp_dev.x[0] = last_x;
            tp_dev.y[0] = last_y;
            tp_dev.sta &= last_state;
			return;
		}

        tp_dev.x[0] = input_x;
		tp_dev.y[0] = input_y;
		tp_dev.sta = TP_PRES_DOWN;

        last_x = tp_dev.x[0];
        last_y = tp_dev.y[0];
        last_state = tp_dev.sta;
			
		// printf("tp down %d %d \r\n", input_x, input_y);
	}else {
		input_x = read_buf[3 + 2] | (read_buf[3 + 1] << 8);	/* x */
		input_y = read_buf[3 + 4] | (read_buf[3 + 3] << 8);	/* y */
		input_w = read_buf[3 + 5];

        if (tp_dev.sta & TP_PRES_DOWN) // 之前是被按下的
        {
            tp_dev.sta &= ~(1 << 7); // 标记按键松开
        }
        else // 之前就没有被按下
        {
            tp_dev.x[0] = 0x00;
            tp_dev.y[0] = 0x00;
            tp_dev.sta &= 0XE0; // 清除点有效标记
        }

        last_x = tp_dev.x[0];
        last_y = tp_dev.y[0];
        last_state = tp_dev.sta;

		// printf("tp up %d %d \r\n", input_x, input_y);
	}
	
}

static int st77102_status_check()
{
	uint8_t read_buf[4] = {0};
	uint16_t new_tp_cnt = 0x00;
	static uint16_t last_tp_cnt = 0x00;
    read_buf[0] = (uint8_t)((ST77102_TOUCH_COUNTER >> 8) & 0xFF);
    read_buf[1] = (uint8_t)(ST77102_TOUCH_COUNTER & 0xFF);
    ST__I2C_Read(ST77102_SALVE_ADDR, read_buf, sizeof(read_buf));
	new_tp_cnt = (uint16_t)read_buf[2] << 8 | read_buf[3];
	// printf("new_tp_cnt:%d\r\n", new_tp_cnt);
	if(last_tp_cnt == new_tp_cnt)
	{
		printf("st77102 rst\r\n");
		st77102_reset();
		return 1;
	}
	last_tp_cnt = new_tp_cnt;
	return 0;
}

uint8_t read_cnt = 0;
/**
 * @brief GT9XX 扫描函数
 * 
 * @param mode 读取值
 * @return uint8_t 触摸状态
 */
uint8_t st77102_scan(uint8_t mode)
{
    uint8_t read_buf[7 * ST77102_MAX_TOUCH + 6];
    static uint16_t err_count = 0;
	static uint16_t rd_count = 0;
    uint8_t res = TP_OK;

    read_buf[0] = (uint8_t)((ST77102_TOUCH_INFO >> 8) & 0xFF);
    read_buf[1] = (uint8_t)(ST77102_TOUCH_INFO & 0xFF);
    if(ST__I2C_Read(ST77102_SALVE_ADDR, read_buf, sizeof(read_buf))) {
        st7102_data_proc(read_buf + 2);
        rd_count++;
        res = 1;
        if(rd_count > 10)
        {
            rd_count = 0;
            st77102_status_check();
        }
    }else {
        err_count++;
        //printf("#:%d\r\n",err_count);
    }

	return res;
}


/** @} */  // 结束 GT9XX 模块分组
/** @} */  // 结束外设模块分组
