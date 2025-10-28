/**
 * @file uart_drv.c
 * @author Product application department
 * @brief  UART 模块驱动层
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "uart_drv.h"
#include "dma_drv.h"
#include "cpm_drv.h"
// 全局变量定义
static uart_ringbuf_t g_uart_ringbuf_para[6];
static dmac_lli_t g_uart_dma_lli[6];
// 函数定义

/**
 * @brief UART 模块管脚切换为UART功能函数
 * @param puart 指向uart_typedef_t结构体的指针
 *
 */
void drv_uart_funcswap(uart_typedef_t *puart)
{

}

/**
 * @brief UART 模块初始化设置函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param Init uart_init_t，包含初始化信息
 */
void drv_uart_init(uart_typedef_t *puart, uart_init_t Init)
{
    uint8_t reg = 0;
    uint16_t bd = 0;

    // 9bits or 8bits
    if (Init.DatabitsLength == UART_DATA_BITS_LENGTH_8)
    {
        reg = UART_DATA_BITS_LENGTH_8;
    }

    // parity
    if (Init.Parity == UART_PARITY_MODE_EVEN)
    {
        reg |= UART_PARITY_MODE_EVEN;
    }
    else if (Init.Parity == UART_PARITY_MODE_ODD)
    {
        reg |= UART_PARITY_MODE_ODD;
    }

    // CR1
    puart->CR1 = reg;
    if(Init.StopbitsLength == UART_STOP_BITS_LENGTH_2)
    {
        puart->CR3 = UART_STOP_BITS_LENGTH_2;
    }

    // baudrate
    puart->BRDF = (((Init.IPSFreq * 8 / Init.BaudRate) + 1) / 2) & 0x003f;

    bd = (Init.IPSFreq * 4 / Init.BaudRate) >> 6;
    puart->BDH = (uint8_t)((bd >> 8) & 0x00ff);
    puart->BDL = (uint8_t)((bd) & 0x00ff);

    if (Init.IdleEn == ENABLE)
    {
        _uart_en_idle_it(puart);
        _uart_idle_start_afer_stop(puart);
    }
    else
    {
        _uart_dis_idle_it(puart);
    }
    if (Init.RxFifoEn == ENABLE)
    {
        _uart_fifo_rx_en(puart);
        _uart_set_rx_fifo_level(puart, Init.RxFifoFull);

    }
    else
    {
        _uart_fifo_rx_dis(puart);
    }

    if (Init.TxFifoEn == ENABLE)
    {
        _uart_fifo_tx_en(puart);
        _uart_set_tx_fifo_level(puart, Init.TxFifoFull);
    }
    else
    {
        _uart_fifo_tx_dis(puart);
    }
}

/**
 * @brief UART 模块初始设置函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_deinit(uart_typedef_t *puart)
{
    puart->CR1 = 0;
    puart->CR2 = 0;
}

/**
 * @brief UART 模块查询方式发送单个字节数据函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param outbyte 待发送字节数据
 */
void drv_uart_sendbyte(uart_typedef_t *puart, uint8_t outbyte)
{
    while (0 == (puart->SR1 & UART_IT_FLAG_TDRE))
    {
        ;
    }

    puart->DRL = outbyte;

    while (0 == (puart->SR1 & UART_IT_FLAG_TC))
    {
        ;
    }
}

/**
 * @brief UART 模块查询方式发送指定长度字节数据函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pbuf 指向待发送数据指针
 * @param len 待发送数据长度
 */
void drv_uart_sendbytes(uart_typedef_t *puart, uint8_t *pbuf, uint16_t len)
{
    uint16_t loop = 0;

    for (loop = 0; loop < len; loop++)
    {
        drv_uart_sendbyte(puart, *(pbuf + loop));
    }
}

/**
 * @brief UART 模块使能发送函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_entx(uart_typedef_t *puart)
{
    _uart_en_txd(puart);
}

/**
 * @brief UART 模块使能接收函数
 * @param puart puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_enrx(uart_typedef_t *puart)
{
    _uart_en_rxd(puart);
}

/**
 * @brief UART 模块禁止发送函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_distx(uart_typedef_t *puart)
{
    _uart_dis_txd(puart);
}

/**
 * @brief UART 模块禁止接收函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_disrx(uart_typedef_t *puart)
{
    _uart_dis_rxd(puart);
}

/**
 * @brief UART 模块禁止发送和接收函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_dis(uart_typedef_t *puart)
{
    if(puart == UART1)
    {
        drv_cpm_module_reset(UART1_MODULE);
    }
    else if(puart == UART2)
    {
        drv_cpm_module_reset(UART2_MODULE);
    }
    else if(puart == UART3)
    {
        drv_cpm_module_reset(UART3_MODULE);
    }	
    else if(puart == UART4)
    {
        drv_cpm_module_reset(UART4_MODULE);
    }
    else if(puart == UART5)
    {
        drv_cpm_module_reset(UART5_MODULE);
    }
    else if(puart == UART6)
    {
        drv_cpm_module_reset(UART6_MODULE);
    }		
    drv_uart_distx(puart);
    drv_uart_disrx(puart);
}

/**
 * @brief UART 模块使能发送和接收函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_en(uart_typedef_t *puart)
{
    drv_uart_entx(puart);
    drv_uart_enrx(puart);
}

/**
 * @brief UART 模块查询方式发送单个字节数据的高和低4位ASCII格式函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param send 待发送字节数据
 */
static void drv_uart_sendone(uart_typedef_t *puart, uint8_t send)
{
    if (send <= 0x09)
    {
        drv_uart_sendbyte(puart, send + 0x30);
    }

    else if ((send > 0x09) && (send <= 0x0f))
    {
        drv_uart_sendbyte(puart, send - 0x0a + 'A');
    }
}

/**
 * @brief UART 模块查询方式发送单个字节数据,ASCII 16进制格式函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param send 待发送字节数据
 */
void drv_uart_sendbytehex(uart_typedef_t *puart, uint8_t send)
{
    uint8_t high;
    uint8_t low;

    high = send >> 4;
    low = send & 0x0f;

    drv_uart_sendone(puart, high);
    drv_uart_sendone(puart, low);
}

/**
 * @brief UART 模块查询方式发送字符串函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param str 字符串指针
 */
void drv_uart_sendstring(uart_typedef_t *puart, char *str)
{
    while (*str)
    {
        drv_uart_sendbyte(puart, *str);
        str++;
    }
}

/**
 * @brief UART 模块禁止TIE中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_disittie(uart_typedef_t *puart)
{
    _uart_dis_tdre_it(puart);
}

/**
 * @brief UART 模块禁止TC中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_disittcie(uart_typedef_t *puart)
{
    _uart_dis_tc_it(puart);
}

/**
 * @brief UART 模块禁止RE中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_disitre(uart_typedef_t *puart)
{
    _uart_dis_rx_it(puart);
}

/**
 * @brief UART 模块使能指定中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断索引
 */
void drv_uart_enit(uart_typedef_t *puart, uart_itindex_t index)
{
    puart->CR2 |= index;
}

/**
 * @brief UART 模块禁止指定中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断索引
 */
void drv_uart_disit(uart_typedef_t *puart, uart_itindex_t index)
{
    puart->CR2 &= ~index;
}

/**
 * @brief UART 模块禁止指定中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index FIFO中断索引
 */
void drv_uart_disfifoit(uart_typedef_t *puart, uint8_t index)
{
    puart->FCR2 &= ~index;
}

/**
 * @brief UATR 模块使能指定中断函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index FIFO中断索引
 */
void drv_uart_enfifoit(uart_typedef_t *puart, uint8_t index)
{
    puart->FCR2 |= index;
}

/**
 * @brief UART 模块获取指令标志状态函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断索引
 * @param flag 状态指值
 * @return status_t 获取结果
 */
status_t drv_uart_getflag(uart_typedef_t *puart,
                          uart_flagindex_t index,
                          flagstatus_t *flag)
{
    uint8_t tmp = 0;

    *flag = RESET;

    if (index != UART_FLAG_INDEX_RAF)
    {
        tmp = puart->SR1 & (1 << index);
    }
    else
    {
        tmp = puart->SR2 & (1);
    }

    *flag = tmp ? SET : RESET;

    return STATUS_OK;
}

/**
 * @brief UART 模块清除指定标志函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断索引
 * @return status_t 获取结果
 */
status_t drv_uart_clearflag(uart_typedef_t *puart,
                            uart_flagindex_t index)
{
    uint8_t reg = 0;

    if (index != UART_FLAG_INDEX_RAF)
    {
        reg = puart->SR1;
        puart->SR1 &= ~(1 << index);
    }
    else
    {
        reg = puart->SR2;
        puart->SR2 &= ~(0X01);
    }

    return STATUS_OK;
}

/**
 * @brief UART 模块超时方式获取指定标志SET或RESET状态函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断索引
 * @param status 状态值
 * @param timeout 超时时间
 * @return status_t 获取结果
 */
status_t drv_uart_waitonflagtimeout(uart_typedef_t *puart,
                                    uart_flagindex_t index,
                                    flagstatus_t status,
                                    uint32_t timeout)
{
    flagstatus_t tmp_flag = RESET;

    if (timeout == 0)
    {
        do
        {
            drv_uart_getflag(puart, index, &tmp_flag);
        } while (tmp_flag != SET);
    }
    else
    {
        if (status == SET)
        {
            drv_uart_getflag(puart, index, &tmp_flag);

            while (tmp_flag != SET)
            {
                timeout--;

                if (timeout == 0)
                {
                    drv_uart_clearflag(puart, index);

                    return STATUS_TIMEOUT;
                }

                drv_uart_getflag(puart, index, &tmp_flag);
            }
        }
        else if (status == RESET)
        {
            drv_uart_getflag(puart, index, &tmp_flag);

            while (tmp_flag != RESET)
            {
                timeout--;

                if (timeout == 0)
                {
                    drv_uart_clearflag(puart, index);

                    return STATUS_TIMEOUT;
                }

                drv_uart_getflag(puart, index, &tmp_flag);
            }
        }
    }

    return STATUS_OK;
}

/**
 * @brief UART 模块查询方式发送数据函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param tosend 待发送数据
 * @param bits 数据长度单位bit
 * @return status_t 操作结果
 */
status_t drv_uart_senddata(uart_typedef_t *puart, uint16_t tosend, uint8_t bits)
{
    puart->DRL = (uint8_t)tosend;
    return STATUS_OK;
}

/**
 * @brief UART 模块查询方式接收数据函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pres 读取数据指针
 * @param bits 数据长度单位bit
 * @return status_t 操作结果
 */
status_t drv_uart_getdata(uart_typedef_t *puart, uint16_t *pres, uint8_t bits)
{
    uint16_t tmp_val = 0;
    tmp_val = puart->DRL;
    *pres = tmp_val;
    return STATUS_OK;
}

/**
 * @brief UART 模块获取模块状态函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pstatus1 状态1指针
 * @param pstatus2 状态2指针
 * @return status_t 获取结果
 */
status_t drv_uart_getstatus(uart_typedef_t *puart, uint8_t *pstatus1, uint8_t *pstatus2)
{
    *pstatus1 = puart->SR1;
    *pstatus2 = puart->SR2;

    return STATUS_OK;
}

/**
 * @brief UART 模块指定中源断是否置位函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断源过引
 * @return flagstatus_t
 */
flagstatus_t drv_uart_getitsource(uart_typedef_t *puart, uart_itindex_t index)
{
    uint8_t tmp_val = 0x00;

    tmp_val = puart->CR2;

    if (tmp_val & index)
    {
        return SET;
    }

    return RESET;
}

/**
 * @brief UART 模块指定FIFO中源断是否置位函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param index 中断源过引
 * @return flagstatus_t 获取结果
 */
flagstatus_t drv_uart_getfifoitsource(uart_typedef_t *puart, uint8_t index)
{
    uint8_t tmp_val = 0x00;

    tmp_val = puart->FCR2;

    if (tmp_val & index)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
 * @brief UART 模块TXD管脚方向输出函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_settxddiroutput(uart_typedef_t *puart)
{
    _uart_txd_output(puart);
}

/**
 * @brief UART 模块TXD管脚方向输入函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_settxddirinput(uart_typedef_t *puart)
{
    _uart_txd_input(puart);
}

/**
 * @brief UART 模块RXD管脚方向输出函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_setrxddiroutput(uart_typedef_t *puart)
{
    _uart_rxd_output(puart);
}

/**
 * @brief UART 模块RXD管脚方向输入函数
 * @param puart 指向uart_typedef_t结构体的指针;
 */
void drv_uart_setrxddirinput(uart_typedef_t *puart)
{
    _uart_rxd_input(puart);
}

/**
 * @brief UART 模块使能TXD/RXD管脚上拉函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_enpullup(uart_typedef_t *puart)
{
    _uart_en_pullup(puart);
}

/**
 * @brief UART 模块禁止TXD/RXD管脚上拉函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_dispullup(uart_typedef_t *puart)
{
    _uart_dis_pullup(puart);
}

/**
 * @brief UART 模块TXD/RXD管脚OPENDRAIN输出函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_setoutputopendrain(uart_typedef_t *puart)
{
    _uart_pin_output_opendrain(puart);
}

/**
 * @brief UART 模块TXD/RXD管脚CMOS输出函数
 * @param puart puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_setoutputcmos(uart_typedef_t *puart)
{
    _uart_pin_output_cmos(puart);
}

/**
 * @brief UART 模块置位TXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_settxdpinbit(uart_typedef_t *puart)
{
    _uart_set_tx_bit(puart);
}

/**
 * @brief UART 模块复位TXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_resettxdpinbit(uart_typedef_t *puart)
{
    _uart_reset_tx_bit(puart);
}

/**
 * @brief UART 模块置位RXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_serxdpinbit(uart_typedef_t *puart)
{
    _uart_set_rx_bit(puart);
}

/**
 * @brief UART 模块复位RXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_resetrxdpinbit(uart_typedef_t *puart)
{
    _uart_reset_rx_bit(puart);
}

/**
 * @brief UART模块 获取TXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @return gpio_pinstate_t 管脚电平
 */
gpio_pinstate_t drv_uart_gettxdpinbit(uart_typedef_t *puart)
{
    return ((gpio_pinstate_t)_uart_get_tx_bit(puart));
}

/**
 * @brief UART 模块获取RXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @return gpio_pinstate_t 管脚电平
 */
gpio_pinstate_t drv_uart_getrxdpinbit(uart_typedef_t *puart)
{
    return ((gpio_pinstate_t)_uart_get_rx_bit(puart));
}

/**
 * @brief UART 模块置位TXD或RXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pin 指定管脚
 *- UART_PIN_TXD;
 *- UART_PIN_RXD;
 */
void drv_uart_setpinbit(uart_typedef_t *puart, uint8_t pin)
{
    _uart_set_pin_bit(puart, pin);
}

/**
 * @brief UART 模块复位TXD或RXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pin 指定管脚
 *- UART_PIN_TXD;
 *- UART_PIN_RXD;
 */
void drv_uart_resetpinbit(uart_typedef_t *puart, uint8_t pin)
{
    _uart_reset_pin_bit(puart, pin);
}

/**
 * @brief UART 模块获取TXD或RXD管脚电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pin 指定管脚
 * @return uint8_t
 *- UART_PIN_TXD;
 *- UART_PIN_RXD;
 */
uint8_t drv_uart_getpinbit(uart_typedef_t *puart, uint8_t pin)
{
    return (_uart_get_pin_bit(puart, pin));
}

/**
 * @brief UART 模块RXD管脚电平翻转函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_rxdPinToggle(uart_typedef_t *puart)
{

    if (puart->PORT & (1 << UART_PIN_INDEX_RXD))
    {
        puart->PORT &= ~(1 << UART_PIN_INDEX_RXD);
    }
    else
    {
        puart->PORT |= (1 << UART_PIN_INDEX_RXD);
    }
}

/**
 * @brief UART 模块TXD管脚电平翻转函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void drv_uart_txdPinToggle(uart_typedef_t *puart)
{

    if (puart->PORT & (1 << UART_PIN_INDEX_TXD))
    {
        puart->PORT &= ~(1 << UART_PIN_INDEX_TXD);
    }
    else
    {
        puart->PORT |= (1 << UART_PIN_INDEX_TXD);
    }
}

/**
 * @brief UART 模块串口1查询方式发送单个字节数据用于DEBUG函数
 * @param c 字符串指针
 */
void drv_uart_putcdev(volatile const uint8_t c)
{
    if (c == '\n')
    {
        drv_uart_putcdev('\r');
    }

    drv_uart_sendbyte(UART1, c);
}

/**
 * @brief UART 模块查询方式发送数据用于DEBUG函数
 * @param s 字符串指针
 */
void drv_uart_putsdev(volatile const uint8_t *s)
{
    while (*s)
    {
        drv_uart_putcdev(*s++);
    }
}

/**
 * @brief UART 模块获取uart ringbuf数据长度函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @return uint32_t 数据长度
 */
uint32_t drv_uart_ringbuf_getdatalen(uart_typedef_t *puart)
{
    uint8_t ringbuf_id = 0;
    uint32_t data_len = 0;
    uint8_t *p_wr = NULL;

    if (puart == UART1)
    {
        ringbuf_id = 0;
    }
    else if (puart == UART2)
    {
        ringbuf_id = 1;
    }
    else if (puart == UART3)
    {
        ringbuf_id = 2;
    }
    else if (puart == UART4)
    {
        ringbuf_id = 3;
    }
    else if (puart == UART5)
    {
        ringbuf_id = 4;
    }
    else if (puart == UART6)
    {
        ringbuf_id = 5;
    }
    dcache_invalidate_range(g_uart_ringbuf_para[ringbuf_id].p_src,g_uart_ringbuf_para[ringbuf_id].buff_len);
    p_wr = *g_uart_ringbuf_para[ringbuf_id].pp_wr;

    if (p_wr >= g_uart_ringbuf_para[ringbuf_id].p_rd)
    {
        data_len = (p_wr - g_uart_ringbuf_para[ringbuf_id].p_rd);
    }
    else
    {
        data_len = (p_wr + g_uart_ringbuf_para[ringbuf_id].buff_len - g_uart_ringbuf_para[ringbuf_id].p_rd);
    }

    return data_len;
}

/**
 * @brief uart 模块ringbuf读数据函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param prxbuf 读取数据缓存
 * @param rxlen 读取数据长度
 * @return uint16_t 结果状态值
 */
status_t drv_uart_ringbuf_read(uart_typedef_t *puart, uint8_t *prxbuf, uint32_t rxlen)
{
    uint8_t ringbuf_id = 0;

    if (puart == UART1)
    {
        ringbuf_id = 0;
    }
    else if (puart == UART2)
    {
        ringbuf_id = 1;
    }
    else if (puart == UART3)
    {
        ringbuf_id = 2;
    }
    else if (puart == UART4)
    {
        ringbuf_id = 3;
    }
    else if (puart == UART5)
    {
        ringbuf_id = 4;
    }
    else if (puart == UART6)
    {
        ringbuf_id = 5;
    }

    while (rxlen > 0)
    {
        *(prxbuf++) = *(g_uart_ringbuf_para[ringbuf_id].p_rd++);
        if (g_uart_ringbuf_para[ringbuf_id].p_rd >= (g_uart_ringbuf_para[ringbuf_id].p_src + g_uart_ringbuf_para[ringbuf_id].buff_len))
        {
            g_uart_ringbuf_para[ringbuf_id].p_rd = g_uart_ringbuf_para[ringbuf_id].p_src;
        }

        rxlen--;
    }

    return STATUS_OK;
}
/**
 * @brief UART 模块DMA接收处理函数
 *
 * @param puart 指向uart_typedef_t结构体的指针
 * @param n DMA 通道
 * @param dest 读取数据缓存
 * @param len 读取数据长度
 * @return uint16_t
 */
uint16_t dma_uartdmaRec_lli(uart_typedef_t *puart, uint8_t n, uint8_t *dest, uint32_t len)
{
    uint8_t dmaNum = 0;
    uint8_t lli_id = 0;
    uint16_t ret = STATUS_OK;
    dmac_controlreg_t *m_dma_control;
    dmac_channel_t *sci_dma_channel[2][DMAC_CHNUM] = {{(dmac_channel_t *)(DMAC1_BASE_ADDR), (dmac_channel_t *)(DMAC1_BASE_ADDR + 0x58),
                                                       (dmac_channel_t *)(DMAC1_BASE_ADDR + 0xB0), (dmac_channel_t *)(DMAC1_BASE_ADDR + 0x108)},
                                                      {(dmac_channel_t *)(DMAC2_BASE_ADDR), (dmac_channel_t *)(DMAC2_BASE_ADDR + 0x58),
                                                       (dmac_channel_t *)(DMAC2_BASE_ADDR + 0xB0), (dmac_channel_t *)(DMAC2_BASE_ADDR + 0x108)}}; // global struct variable for for Channel registers


    if (puart == UART1)
    {
        m_dma_control = (dmac_controlreg_t *)(DMAC1_BASE_ADDR + 0x2C0);
        lli_id = 0;
    }
    else if (puart == UART2)
    {
        m_dma_control = (dmac_controlreg_t *)(DMAC2_BASE_ADDR + 0x2C0);
        dmaNum = 1;
        lli_id = 1;
    }
    else if (puart == UART3)
    {
        m_dma_control = (dmac_controlreg_t *)(DMAC1_BASE_ADDR + 0x2C0);
        lli_id = 2;
    }
    else if (puart == UART4)
    {
        m_dma_control = (dmac_controlreg_t *)(DMAC2_BASE_ADDR + 0x2C0);
        dmaNum = 1;
        lli_id = 3;
    }
    else if (puart == UART5)
    {
        m_dma_control = (dmac_controlreg_t *)(DMAC1_BASE_ADDR + 0x2C0);
        lli_id = 4;
    }
    else if (puart == UART6)
    {
        m_dma_control = (dmac_controlreg_t *)(DMAC1_BASE_ADDR + 0x2C0);
        lli_id = 5;
    }
    m_dma_control->DMA_CHEN = CHANNEL_WRITE_ENABLE(n); // DMA disable.

    m_dma_control->DMA_CONFIG = DMACEN;

    if (puart == UART1)
    {
        sci_dma_channel[dmaNum][n]->SRCADDR = UART1_BASE_ADDR + 0x06;
        g_uart_dma_lli[lli_id].src_addr = UART1_BASE_ADDR + 0x06;
    }
    else if (puart == UART2)
    {
        sci_dma_channel[dmaNum][n]->SRCADDR = UART2_BASE_ADDR + 0x06;
        g_uart_dma_lli[lli_id].src_addr = UART2_BASE_ADDR + 0x06;
    }
    else if (puart == UART3)
    {
        sci_dma_channel[dmaNum][n]->SRCADDR = UART3_BASE_ADDR + 0x06;
        g_uart_dma_lli[lli_id].src_addr = UART3_BASE_ADDR + 0x06;
    }
    else if (puart == UART4)
    {
        sci_dma_channel[dmaNum][n]->SRCADDR = UART4_BASE_ADDR + 0x06;
        g_uart_dma_lli[lli_id].src_addr = UART4_BASE_ADDR + 0x06;
    }
    else if (puart == UART5)
    {
        sci_dma_channel[dmaNum][n]->SRCADDR = UART5_BASE_ADDR + 0x06;
        g_uart_dma_lli[lli_id].src_addr = UART5_BASE_ADDR + 0x06;
    }
    else if (puart == UART6)
    {
        sci_dma_channel[dmaNum][n]->SRCADDR = UART6_BASE_ADDR + 0x06;
        g_uart_dma_lli[lli_id].src_addr = UART6_BASE_ADDR + 0x06;
    }
    sci_dma_channel[dmaNum][n]->DSTADDR = (uint32_t)dest;
    sci_dma_channel[dmaNum][n]->CTRL = DI | SNOCHG | P2M_DMA | LLP_DST_EN | LLP_SRC_EN;
    sci_dma_channel[dmaNum][n]->CTRL_HIGH = len;
    sci_dma_channel[dmaNum][n]->CONFIG &= DST_SOFT;

    if (puart == UART1)
    {
        sci_dma_channel[dmaNum][n]->CONFIG_HIGH = SRC_PER_SCI1_RX;
    }
    else if (puart == UART2)
    {
        sci_dma_channel[dmaNum][n]->CONFIG_HIGH = SRC_PER_SCI2_RX;
    }
    else if (puart == UART3)
    {
        sci_dma_channel[dmaNum][n]->CONFIG_HIGH = SRC_PER_SCI3_RX;
    }
    else if (puart == UART4)
    {
        sci_dma_channel[dmaNum][n]->CONFIG_HIGH = SRC_PER_SCI4_RX;
    }
    else if (puart == UART5)
    {
        sci_dma_channel[dmaNum][n]->CONFIG_HIGH = SRC_PER_SCI5_RX;
    }
    else if (puart == UART6)
    {
        sci_dma_channel[dmaNum][n]->CONFIG_HIGH = SRC_PER_SCI6_RX;
    }

    sci_dma_channel[dmaNum][n]->LLI = (uint32_t)&g_uart_dma_lli[lli_id];

    g_uart_dma_lli[lli_id].dst_addr = (uint32_t)dest;
    g_uart_dma_lli[lli_id].next_lli = (uint32_t)&g_uart_dma_lli[lli_id];
    g_uart_dma_lli[lli_id].control = DI | SNOCHG | P2M_DMA | LLP_DST_EN | LLP_SRC_EN;
    g_uart_dma_lli[lli_id].len = len;

    m_dma_control->DMA_MASKTFR = CHANNEL_UMASK(n);
    m_dma_control->DMA_CHEN = (CHANNEL_WRITE_ENABLE(n) | CHANNEL_ENABLE(n));

    return ret;
}

/**
 * @brief UART 模块ringbuf初始化函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param channel dma channnel通道
 * @param dest 传输的buffer
 * @param len 传输长度
 * @return uint16_t 结果状态值
 */
status_t drv_uart_dmareceive_ringbuf_init(uart_typedef_t *puart, uint8_t channel, uint8_t *dest, uint32_t len)
{
    uint16_t ret = 0;
    uint8_t ringbuf_id = 0;

    if (puart == UART1)
    {
        ringbuf_id = 0;
        g_uart_ringbuf_para[ringbuf_id].pp_wr = (uint8_t **)(DMAC1_BASE_ADDR + 0x58 * channel + 0x08);
    }
    else if (puart == UART2)
    {
        ringbuf_id = 1;
        g_uart_ringbuf_para[ringbuf_id].pp_wr = (uint8_t **)(DMAC2_BASE_ADDR + 0x58 * channel + 0x08);
    }
    else if (puart == UART3)
    {
        ringbuf_id = 2;
        g_uart_ringbuf_para[ringbuf_id].pp_wr = (uint8_t **)(DMAC1_BASE_ADDR + 0x58 * channel + 0x08);
    }
    else if (puart == UART4)
    {
        ringbuf_id = 3;
        g_uart_ringbuf_para[ringbuf_id].pp_wr = (uint8_t **)(DMAC2_BASE_ADDR + 0x58 * channel + 0x08);
    }
    else if (puart == UART5)
    {
        ringbuf_id = 4;
        g_uart_ringbuf_para[ringbuf_id].pp_wr = (uint8_t **)(DMAC1_BASE_ADDR + 0x58 * channel + 0x08);
    }
    else if (puart == UART6)
    {
        ringbuf_id = 5;
        g_uart_ringbuf_para[ringbuf_id].pp_wr = (uint8_t **)(DMAC1_BASE_ADDR + 0x58 * channel + 0x08);
    }
    g_uart_ringbuf_para[ringbuf_id].p_src = dest;
    g_uart_ringbuf_para[ringbuf_id].buff_len = len;
    g_uart_ringbuf_para[ringbuf_id].p_rd = dest;

    ret = dma_uartdmaRec_lli(puart, channel, dest, len);
    if (ret != STATUS_OK)
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}
