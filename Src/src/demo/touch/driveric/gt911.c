/**
 * @file gt911.c
 * @author Product application department
 * @brief 驱动芯片gt911驱动程序
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
/*** 头文件定义 ***************************************************************/
#include "type.h"
#include "eport_drv.h"
#include "tp_interface.h"
#include "gt911.h"
#include "pinswap_drv.h"
#include "i2c_hal.h"
#include "pinswap_drv.h"
#include "delay.h"
/*** 全局变量定义 ***************************************************************/
static i2c_handle_t I2Cx_Touch_Handle;

const uint16_t GT911_TPX_TBL[5] = {GT_TP1_REG, GT_TP2_REG, GT_TP3_REG, GT_TP4_REG, GT_TP5_REG};
extern uint8_t long_press_cnt;
extern tp_handle_t tp_dev;
#define TOUCH_CPT_PORT_SDA EPORT4
#define TOUCH_CPT_PIN_SDA EPORT4_PIN6
#define TOUCH_CPT_PORT_SCL EPORT4
#define TOUCH_CPT_PIN_SCL EPORT4_PIN7


#define CT_SDA_IN()      hal_eport_input(TOUCH_CPT_PORT_SDA, TOUCH_CPT_PIN_SDA,PS_PULL_UP)
#define CT_SDA_OUT()    hal_eport_output(TOUCH_CPT_PORT_SDA, TOUCH_CPT_PIN_SDA)
#define CT_READ_SDA     hal_eport_readpinslevel(TOUCH_CPT_PORT_SDA, TOUCH_CPT_PIN_SDA)
#define CT_IIC_SDA(x)   x ?(hal_eport_writepinlevel(TOUCH_CPT_PORT_SDA, TOUCH_CPT_PIN_SDA, GPIO_HIGH)) : (hal_eport_writepinlevel(TOUCH_CPT_PORT_SDA, TOUCH_CPT_PIN_SDA, GPIO_LOW))
#define CT_IIC_SCL(x)   x ?(hal_eport_writepinlevel(TOUCH_CPT_PORT_SCL, TOUCH_CPT_PIN_SCL, GPIO_HIGH)) : (hal_eport_writepinlevel(TOUCH_CPT_PORT_SCL, TOUCH_CPT_PIN_SCL, GPIO_LOW))
/*** 函数定义 *******************************************************************/

/**
 * @brief 延迟函数
 * 
 */
void ct_delay(void)
{
    delayus(2);
} 



/**
 * @brief 产生IIC起始信号函数
 * 
 */
void ct_i2c_start(void)
{
    CT_SDA_OUT();     //sda线输出
    CT_IIC_SDA(1);	  	  
    CT_IIC_SCL(1);
    ct_delay();
    CT_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
    ct_delay();
    CT_IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
    ct_delay();
}	  

/**
 * @brief 产生IIC停止信号函数
 * 
 */
void ct_i2c_stop(void)
{
    CT_SDA_OUT();//sda线输出
    CT_IIC_SCL(0);
    CT_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
    ct_delay();
    CT_IIC_SCL(1);
    ct_delay(); 
    CT_IIC_SDA(1);//发送I2C总线结束信号  
    ct_delay();
}

/**
 * @brief 等待应答信号到来函数
 * 
 * @return uint8_t 
 * 1 接收应答失败
 * 0 接收应答成功
 */
uint8_t ct_i2c_wait_ack(void)
{
    uint8_t ucErrTime=0;
    CT_SDA_IN();      //SDA设置为输入  
    CT_IIC_SDA(1); 
    ct_delay();
    CT_IIC_SCL(1);
    ct_delay();
    while(CT_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            ct_i2c_stop();
            return 1;
        } 
        ct_delay();
    }
    CT_IIC_SCL(0);//时钟输出0 
    ct_delay();	
    return 0;  
} 

/**
 * @brief 产生ACK应答函数
 * 
 */
void ct_i2c_ack(void)
{
    CT_SDA_OUT(); 
    CT_IIC_SDA(0);
    ct_delay();
    CT_IIC_SCL(1);
    ct_delay();
    CT_IIC_SCL(0);
    ct_delay();
    CT_IIC_SDA(1);//主机释放SDA线
    ct_delay();
}
/**
 * @brief 不产生ACK应答函数		
 * 
 */
void ct_i2c_nack(void)
{
    CT_SDA_OUT(); 
    CT_IIC_SDA(1);
    ct_delay();
    CT_IIC_SCL(1);
    ct_delay();
    CT_IIC_SCL(0);
    ct_delay();
}					 				     

/**
 * @brief IIC发送一个字节函数
 * 
 * @param txd 发送数据
 */
void ct_i2c_send_byte(uint8_t txd)
{                        
    uint8_t t;   
    CT_SDA_OUT(); 	    
    CT_IIC_SCL(0);//拉低时钟开始数据传输 
    for(t=0;t<8;t++)
    {              
        CT_IIC_SDA((txd&0x80)>>7);
        txd<<=1; 
        ct_delay();	      
        CT_IIC_SCL(1); 
        ct_delay();
        CT_IIC_SCL(0);	 
    }	
    CT_IIC_SDA(1);                     /* 发送完成, 主机释放SDA线 */
} 	    

/**
 * @brief 读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
 * 
 * @param ack 读取数据 
 * @return uint8_t 
 */
uint8_t ct_i2c_read_byte(unsigned char ack)
{
    uint8_t i,receive=0;
    CT_SDA_IN();//SDA设置为输入 
    for(i=0;i<8;i++ )
    { 
        receive<<=1;
        CT_IIC_SCL(1);
        ct_delay();	
        if(CT_READ_SDA)receive++; 
        CT_IIC_SCL(0);
        ct_delay();  
    }	  				 
    if (!ack)ct_i2c_nack();//发送nACK
    else ct_i2c_ack(); //发送ACK   
    return receive;
}

/**
 * @brief 从GT911读出一次数据函数
 * 
 * @param reg 起始寄存器地址
 * @param buf 数据缓缓存区
 * @param len 读数据长度	
 */
void gt911_i2c_rd_reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t i; 
    ct_i2c_start();	
    ct_i2c_send_byte(GT_CMD_WR);   //发送写命令 	 
    ct_i2c_wait_ack();
    ct_i2c_send_byte(reg>>8);   	//发送高8位地址
    ct_i2c_wait_ack(); 	 										  		   
    ct_i2c_send_byte(reg&0XFF);   	//发送低8位地址
    ct_i2c_wait_ack();  
    ct_i2c_start();  	 	   
    ct_i2c_send_byte(GT_CMD_RD);   //发送读命令		   
    ct_i2c_wait_ack();	   
    for(i=0;i<len;i++)
    {	   
        buf[i]=ct_i2c_read_byte(i==(len-1)?0:1); //发数据	  
    } 
    ct_i2c_stop();//产生一个停止条件    
}


/**
 * @brief 从GT911写一次数据函数
 * 
 * @param reg 起始寄存器地址
 * @param buf 数据缓缓存区
 * @param len 写数据长度	
 */
uint8_t gt911_i2c_wr_reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t i;
    uint8_t ret=0;
    ct_i2c_start();	
    ct_i2c_send_byte(GT_CMD_WR);   	//发送写命令 	 
    ct_i2c_wait_ack();
    ct_i2c_send_byte(reg>>8);   	//发送高8位地址
    ct_i2c_wait_ack(); 	 										  		   
    ct_i2c_send_byte(reg&0XFF);   	//发送低8位地址
    ct_i2c_wait_ack();  
    for(i=0;i<len;i++)
    {	   
        ct_i2c_send_byte(buf[i]);  	//发数据        
        ret=ct_i2c_wait_ack();
        if(ret)break;  
    }
    ct_i2c_stop();					//产生一个停止条件	    
    return ret; 
}


/**
 * @brief GT9XX I2C 写寄存器函数
 * @param addr 寄存器地址
 * @param buffer 传输数组
 * @param len 传输长度
 */
void gt911_wr_reg(uint16_t addr, uint8_t *buffer, uint8_t len)
{
    addr = (((addr >> 8) & 0x00ff) + ((addr << 8) & 0xff00)) & 0xffff; // MSB
    hal_i2c_memwrite(&I2Cx_Touch_Handle, GT_CMD_WR, addr, 2, buffer, len, 10);
}

/**
 * @brief GT9XX I2C 读寄存器函数
 * @param addr 寄存器地址
 * @param buffer 读取数组
 * @param len 读取长度
 */
void gt911_rd_reg(uint16_t addr, uint8_t *buffer, uint8_t len)
{
    addr = (((addr >> 8) & 0x00ff) + ((addr << 8) & 0xff00)) & 0xffff; // MSB
    hal_i2c_memread(&I2Cx_Touch_Handle, GT_CMD_RD, addr, 2, buffer, len, 10);
}
 
/**
 * @brief GT9XX 中断IO 输出模块初始化函数
 * 
 */
void int_io_init(void)
{
    SwitchPinFunction(UART4_TX_FUN,EPORT3_PIN6_FUN);
    hal_eport_output(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT);
}
/**
 * @brief GT9XX 中断IO输入模式上拉初始化函数
 * 
 */
void int_init(void)
{
    hal_eport_input(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT,PS_PULL_UP);
}
/**
 * @brief GT9XX 复位IO输出模式初始化函数
 * 
 */
void reset_io_init(void)
{
    SwitchPinFunction(UART4_RX_FUN,EPORT3_PIN7_FUN);
    hal_eport_output(TOUCH_CPT_PORT_RST, TOUCH_CPT_PIN_RST);
}
/**
 * @brief GT9XX I2C初始化函数
 * 
 */
void gt911_i2c_init(void)
{
   SwitchPinFunction(UART5_RX_FUN,EPORT4_PIN7_FUN);
   SwitchPinFunction(UART5_TX_FUN,EPORT4_PIN6_FUN);
   hal_eport_output(TOUCH_CPT_PORT_SDA, TOUCH_CPT_PIN_SDA);
   hal_eport_output(TOUCH_CPT_PORT_SCL, TOUCH_CPT_PIN_SCL);
}
/**
 * @brief GT9XX 上电复位函数
 * 
 */
void gt911_reset(void)
{
    int_io_init();
    hal_eport_writepinlevel(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT, GPIO_HIGH);
    delayms(10);
    reset_io_init();
    hal_eport_writepinlevel(TOUCH_CPT_PORT_RST, TOUCH_CPT_PIN_RST, GPIO_LOW);
    delayms(10);
    hal_eport_writepinlevel(TOUCH_CPT_PORT_RST, TOUCH_CPT_PIN_RST, GPIO_HIGH);
    delayms(10);  
    hal_eport_writepinlevel(TOUCH_CPT_PORT_INT, TOUCH_CPT_PIN_INT, GPIO_LOW);
    delayms(100);
    int_init();
    delayms(10); 
		
}

/**
 * @brief GT9XX 初始化函数
 * 
 * @return tp_status_t 初始化成功/失败
 */
tp_status_t gt911_init(void)
{
    uint8_t temp[5];
    memset(temp, 0, 5);
    gt911_reset();
    gt911_i2c_init();
    gt911_i2c_rd_reg(GT_PID_REG, temp, 1);
    printf("temp=%d\r\n",temp[0]);
    if(temp[0] == 0)
    {
        return TP_ERR; // 通信失败
    }
    return TP_OK;
}
/**
 * @brief GT9XX 扫描函数
 * 
 * @param mode 读取值
 * @return uint8_t 触摸状态
 */
uint8_t gt911_scan(uint8_t mode)
{
	uint8_t buf[4];
	uint8_t i = 0;
	uint8_t res = TP_OK;
	uint8_t temp;
	uint8_t tempsta;
	static uint8_t check_t = 0; // 控制查询间隔,从而降低CPU占用率
    check_t++;

    if ((check_t % TOUCH_CPT_SCAN_TIMES) == 0 || check_t < TOUCH_CPT_SCAN_TIMES) // 空闲时,每进入5次CTP_Scan函数才检测1次,从而节省CPU使用率
    {
        gt911_i2c_rd_reg(GT_GSTID_REG, &mode, 1); // 读取触摸点的状态
        if (mode & 0X80 && ((mode & 0XF) < 6))
        {
            temp = 0;
            gt911_i2c_wr_reg(GT_GSTID_REG, &temp, 1); // 清标志
                
                // 提取Y坐标
                
              
        }

        if ((mode & 0XF) && ((mode & 0XF) < 6))
        {
            temp = 0XFF << (mode & 0XF); // 将点的个数转换为1的位数,匹配tp_dev.sta定义
            tempsta = tp_dev.sta;		 // 保存当前的tp_dev.sta值
            tp_dev.sta = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
            tp_dev.x[4] = tp_dev.x[0]; // 保存触点0的数据
            tp_dev.y[4] = tp_dev.y[0];

            for (i = 0; i < 5; i++)
            {
                if (tp_dev.sta & (1 << i)) // 触摸有效?
                {
                    gt911_i2c_rd_reg(GT911_TPX_TBL[i], buf, 4); // 读取XY坐标值
                    #if 0

                    if(tp_dev.touchtype & 0X01) //横屏
                    {
                        tp_dev.x[i] = (((u16)buf[1] << 8) + buf[0]);
                        tp_dev.y[i] = (((u16)buf[3] << 8) + buf[2]);
                    } else
                    {
                        tp_dev.y[i] = ((u16)buf[1] << 8) + buf[0];
                        tp_dev.x[i] = 480 - (((u16)buf[3] << 8) + buf[2]);
                    }

                    #endif
                    tp_dev.x[i] = (((uint16_t)buf[1] << 8) + buf[0]);
                    tp_dev.y[i] = (((uint16_t)buf[3] << 8) + buf[2]);
                }
            }

            res = 1;

            if (tp_dev.x[0] > tp_dev.width || tp_dev.y[0] > tp_dev.height) // 非法数据(坐标超出了)
            {

                if ((mode & 0XF) > 1) // 有其他点有数据,则复第二个触点的数据到第一个触点.
                {
                    tp_dev.x[0] = tp_dev.x[1];
                    tp_dev.y[0] = tp_dev.y[1];
                    check_t = 0; // 触发一次,则会最少连续监测10次,从而提高命中率
                }
                else // 非法数据,则忽略此次数据(还原原来的)
                {
                    tp_dev.x[0] = tp_dev.x[4];
                    tp_dev.y[0] = tp_dev.y[4];
                    mode = 0X80;
                    tp_dev.sta = tempsta; // 恢复tp_dev.sta
                }
            }
            else
                check_t = 0; // 触发一次,则会最少连续监测10次,从而提高命中率
        }
    }

    if ((mode & 0X8F) == 0X80) // 无触摸点按下
    {
        if (tp_dev.sta & TP_PRES_DOWN) // 之前是被按下的
        {
            tp_dev.sta &= ~(1 << 7); // 标记按键松开
        }
        else // 之前就没有被按下
        {
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
            tp_dev.sta &= 0XE0; // 清除点有效标记
        }
    }

    if (check_t > 240)
        check_t = TOUCH_CPT_SCAN_TIMES; // 重新?开始计数

    return res;
}


/** @} */  // 结束 GT9XX 模块分组
/** @} */  // 结束外设模块分组
