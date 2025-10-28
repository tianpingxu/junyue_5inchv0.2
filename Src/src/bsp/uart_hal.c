/**
 * @file uart_hal.c
 * @author Product application department
 * @brief  UART 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "uart_hal.h"
#include "cpm_drv.h"
// 全局变量定义
static uint8_t *g_uart_rxbuf;
static uint8_t *g_uart_txbuf;
static uart_handle_t *g_huart;

// 函数定义

/**
 * @brief UART 模块初始化函数
 * @param huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 * @return status_t 返回状态值
 */
status_t hal_uart_init(uart_handle_t *huart)
{
    if (huart->Instance == NULL)
    {
        return STATUS_ERROR;
    }

    if (huart->State == HAL_UART_STATE_RESET)
    {
    }

    huart->State = HAL_UART_STATE_BUSY;

    drv_uart_dis(huart->Instance);
    drv_uart_init(huart->Instance, huart->Init);

    drv_uart_entx(huart->Instance);
    drv_uart_enrx(huart->Instance);

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->State = HAL_UART_STATE_READY;
    g_huart = huart;
    return STATUS_OK;
}

/**
 *@brief 串口发送接口
 *
 *@param[in] uart_type  指向UART_TypeDef结构体的指针;
 *@param[in] txbuf  待发送数据
 *@param[in] txLen   数据长度单位bit;
 *@retval @ref null
 */
void hal_uart_comm_send(uart_typedef_t *uart_type, uint8_t *txBuf, uint16_t txLen)
{
    for (int i = 0; i < txLen; i++)
    {
        while ((uart_type->SR1 & UART_SR1_TDRE_MASK) == 0x00)
            ;
        uart_type->DRL = (uint8_t)txBuf[i];
        while ((uart_type->SR1 & UART_SR1_TC_MASK) == 0x00)
            ;
    }
}

/**
 * @brief UART 模块DMA回调函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void hal_uart_ringbuf_int_callback(uart_typedef_t *puart)
{
    uint32_t len;

    len = drv_uart_ringbuf_getdatalen(puart);
    if (len > 0)
    {
        drv_uart_ringbuf_read(puart, g_uart_rxbuf, len);
        hal_uart_comm_send(puart, g_uart_rxbuf, len);
    }   

}

/**
 * @brief UART 模块ringbuf初始化函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param channel dma channnel通道
 * @param dest 传输的buffer
 * @param len 传输长度
 * @return uint16_t 返回状态值
 */
status_t hal_uart_dmareceive_ringbuf_init(uart_typedef_t *puart, uint8_t channel, uint8_t *dest, uint32_t len)
{
    return drv_uart_dmareceive_ringbuf_init(puart, channel, dest, len);
}

/**
 * @brief UART 模块发送完成回调函数
 * @param huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 */
void hal_uart_txcpltcallback(uart_handle_t *huart)
{
    // add sth to handle tx irq event
}

/**
 * @brief UART 模块接收完成回调函数.
 * @param huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 */
void hal_uart_rxcpltcallback(uart_handle_t *huart)
{
    hal_uart_comm_send(huart->Instance, g_uart_rxbuf, huart->RxXferCount);
    huart->RxXferSize = UART_BUFFER_SIZE;
    huart->RxXferCount = 0;
    huart->pRxBuffPtr = g_uart_rxbuf;
}

extern void rx_data_input(uint8_t* buf, uint16_t len);
/**
 * @brief UART 模块中断服务函数
 * @param 指向uart_handle_t结构体的指针
 */
extern uint8_t uart_rx_buf[];
int uart_cnt = 0;
void hal_uart_irqhandler(uart_handle_t *huart)
{
    uint8_t status1, status2;
    uint16_t tmp_val = 0x00;

    flagstatus_t it_src_flag = RESET;
    drv_uart_getstatus(huart->Instance, &status1, &status2);

    it_src_flag = drv_uart_getitsource(huart->Instance, UART_IT_INDEX_TCIE);

    if ((status1 & (1 << UART_FLAG_INDEX_TC)) && (it_src_flag == SET))
    {
        /*发送完成中断*/
        drv_uart_disit(huart->Instance, UART_IT_INDEX_TCIE);

        if ((huart->State & HAL_UART_STATE_BUSY_TX_RX) == HAL_UART_STATE_BUSY_RX)
        {
            huart->State = HAL_UART_STATE_BUSY_RX;
        }
        else
        {
            huart->State = HAL_UART_STATE_READY;
        }
        /*回调函数*/
        hal_uart_txcpltcallback(huart);
    }

    /*发送空中断*/
    it_src_flag = drv_uart_getitsource(huart->Instance, UART_IT_INDEX_TDRE);

    if ((status1 & (1 << UART_FLAG_INDEX_TDRE)) && (it_src_flag == SET))
    {
        /*发送剩余的数据*/
        drv_uart_senddata(huart->Instance, *huart->pTxBuffPtr, huart->Init.DatabitsLength);
        huart->TxXferCount++;

        if (huart->TxXferCount == huart->TxXferSize)
        {
            drv_uart_enit(huart->Instance, UART_IT_INDEX_TCIE);
            drv_uart_disit(huart->Instance, UART_IT_INDEX_TDRE);
        }
        else
        {
            huart->pTxBuffPtr++;
        }
    }

    /*接收中断*/
	
#if 1
	
//	hal_uart_comm_send(huart->Instance, uart_rx_buf, 1);
	if (huart->Init.RxFifoEn == ENABLE) // 接收FIFO使能
    {
		if (((drv_uart_getfifoitsource(huart->Instance, UART_IT_INDEX_RXFIE) == SET) && (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_RFTS)) == (1 << UART_FLAG_INDEX_RFTS))) ||
		((drv_uart_getfifoitsource(huart->Instance, UART_IT_INDEX_RXFTOIE) == SET) && (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_RTOS)) == (1 << UART_FLAG_INDEX_RTOS))))
        {
            /*UART 接收FIFO触发状态*/
			while (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_R_EMPTY)) != (1 << UART_FLAG_INDEX_R_EMPTY))
			{
				drv_uart_getdata(huart->Instance, &tmp_val, huart->Init.DatabitsLength);
				// uart_rx_buf[uart_cnt] = tmp_val;
				// uart_cnt++;
				// hal_uart_comm_send(huart->Instance, &tmp_val, 1);
				if(huart->Instance == UART2) {
                    rx_data_input(&tmp_val, 1);
				}
			}

        }
		
	}
	
#else
	
    if (huart->Init.IdleEn == ENABLE)
    {
        if (_uart_get_rx_flag(huart->Instance) == UART_RX_DMA_EN) 
        {
            if (_uart_get_idle_flag(huart->Instance) == UART_IT_FLAG_IDLE)
            {
                while (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_R_EMPTY)) == UART_FLAG_INDEX_R_EMPTY)
                {
                    if (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_RTOS)) != UART_FLAG_INDEX_RTOS)
                    {
                        _uart_clear_fifo_mode_overrun_flag(huart->Instance);
                        _uart_clear_fifo_mode_noise_flag(huart->Instance);
                        _uart_clear_fifo_mode_frame_err_flag(huart->Instance);
                        _uart_clear_fifo_mode_parity_err_flag(huart->Instance);
                        break;
                    }
                }
                while (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_R_EMPTY)) == UART_FLAG_INDEX_R_EMPTY)
                    ;

                hal_uart_ringbuf_int_callback(huart->Instance);
            }
        }
           else
        {
           _uart_en_idle_it(huart->Instance);
           if (_uart_get_idle_flag(huart->Instance) == UART_IT_FLAG_IDLE)
            {
                while (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_R_EMPTY)) == UART_FLAG_INDEX_R_EMPTY)
                {
                    drv_uart_getdata(huart->Instance, &tmp_val, huart->Init.DatabitsLength);
                    *huart->pRxBuffPtr = tmp_val;
                     huart->RxXferCount++;
    }
                _uart_dis_idle_it(huart->Instance);
                hal_uart_rxcpltcallback(huart);
            }
        }
    }

    if (huart->Init.RxFifoEn == ENABLE) // 接收FIFO使能
    {
        if (((drv_uart_getfifoitsource(huart->Instance, UART_IT_INDEX_RXFIE) == SET) && (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_RFTS)) == (1 << UART_FLAG_INDEX_RFTS))) ||
            ((drv_uart_getfifoitsource(huart->Instance, UART_IT_INDEX_RXFTOIE) == SET) && (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_RTOS)) == (1 << UART_FLAG_INDEX_RTOS))))
        {
            /*UART 接收FIFO触发状态*/
            if ((huart->State == HAL_UART_STATE_BUSY_RX) || (huart->State == HAL_UART_STATE_BUSY_TX_RX))
            {
                while (_uart_get_fifo_flag(huart->Instance, (1 << UART_FLAG_INDEX_R_EMPTY)) != (1 << UART_FLAG_INDEX_R_EMPTY))
                {
                    drv_uart_getdata(huart->Instance, &tmp_val, huart->Init.DatabitsLength);
                    huart->RxXferCount++;
                    if (huart->RxXferCount <= huart->RxXferSize)
                    {
                        *huart->pRxBuffPtr = tmp_val;
                        huart->pRxBuffPtr++;
                    }
                }
                if (huart->RxXferCount >= huart->RxXferSize)
                {
                    drv_uart_disfifoit(huart->Instance, UART_IT_INDEX_RXFIE | UART_IT_INDEX_RXORIE | UART_IT_INDEX_RXFTOIE | UART_IT_INDEX_RXFTOE);
                    huart->State = (huart->State == HAL_UART_STATE_BUSY_TX_RX) ? HAL_UART_STATE_BUSY_TX : HAL_UART_STATE_READY;

                    hal_uart_rxcpltcallback(huart);
                }
            }
        }
    }
    else
    {
        it_src_flag = drv_uart_getitsource(huart->Instance, UART_IT_INDEX_RIE);

        if (((status1 & (1 << UART_FLAG_INDEX_RDRF))) && (it_src_flag == SET))
        {
            if ((huart->State == HAL_UART_STATE_BUSY_RX) || (huart->State == HAL_UART_STATE_BUSY_TX_RX))
            {
                drv_uart_getdata(huart->Instance, &tmp_val, huart->Init.DatabitsLength);
                *huart->pRxBuffPtr = tmp_val;
                huart->RxXferCount++;

                if (huart->RxXferCount == huart->RxXferSize)
                {
                    drv_uart_disit(huart->Instance, UART_IT_INDEX_RIE);

                    huart->State = (huart->State == HAL_UART_STATE_BUSY_TX_RX) ? HAL_UART_STATE_BUSY_TX : HAL_UART_STATE_READY;

                    hal_uart_rxcpltcallback(huart);
                }
                else
                {
                    huart->pRxBuffPtr++;
                }
            }
        }
    }
	
#endif
}

/**
 * @brief UART 模块中断处理函数
 */
void hal_uart_irqhandler_cb(void)
{
    hal_uart_irqhandler(g_huart);
}

/**
 * @brief UART 模块中断初始化函数
 */
void hal_uart_itinit(void)
{
    /*暂时关闭所有的中断允许*/
    __disable_irq();

    if (g_huart->Instance == UART1)
    {
        NVIC_Init(3, 3, UART1_IRQn, 2);
        UART1_IRQHandler_Callback = hal_uart_irqhandler_cb;
    }
    else if (g_huart->Instance == UART2)
    {
        NVIC_Init(3, 3, UART2_IRQn, 2);
        UART2_IRQHandler_Callback = hal_uart_irqhandler_cb;
    }
    else if (g_huart->Instance == UART3)
    {
        NVIC_Init(3, 3, UART3_IRQn, 2);
        UART3_IRQHandler_Callback = hal_uart_irqhandler_cb;
    }
    else if (g_huart->Instance == UART4)
    {
        NVIC_Init(3, 3, UART4_IRQn, 2);
        UART4_IRQHandler_Callback = hal_uart_irqhandler_cb;
    }
    else if (g_huart->Instance == UART5)
    {
        NVIC_Init(3, 3, UART5_IRQn, 2);
        UART5_IRQHandler_Callback = hal_uart_irqhandler_cb;
    }
    else if (g_huart->Instance == UART6)
    {
        NVIC_Init(3, 3, UART6_IRQn, 2);
        UART6_IRQHandler_Callback = hal_uart_irqhandler_cb;
    }

    /*打开所有中断允许*/
    __enable_irq();
}

/**
 * @brief UART 模块发送数据函数
 * @param huart huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 * @param pdata 待发送数据指针
 * @param size  待发送数据长度
 * @param timeout  超时时间
 * @return  status_t 返回状态值
 */
status_t hal_uart_transmit(uart_handle_t *huart, uint8_t *pdata, uint16_t size, uint32_t timeout)                                                                                                         
{
    uint16_t loop = 0;
    status_t DrvStatus = STATUS_OK;
    status_t tmp_status = STATUS_OK;

    /**/
    huart->TxXferSize = size;
    huart->TxXferCount = 0;
    huart->pTxBuffPtr = pdata;

    if(huart->State & HAL_UART_STATE_BUSY_RX)
    {
        huart->State = HAL_UART_STATE_BUSY_TX_RX;
    }
    else
    {
        huart->State = HAL_UART_STATE_BUSY_TX;
    }

    for(loop = 0; loop < huart->TxXferSize; loop++)
    {
        /*是否为空*/
        tmp_status = drv_uart_waitonflagtimeout(huart->Instance,
                                              UART_FLAG_INDEX_TDRE,
                                              SET,
                                              timeout);

        if(tmp_status != STATUS_OK)
        {
            return(STATUS_TIMEOUT);
        }

        drv_uart_senddata(huart->Instance, *(huart->pTxBuffPtr + loop), huart->Init.DatabitsLength);
        /*发送完成*/
        DrvStatus = drv_uart_waitonflagtimeout(huart->Instance,
                                              UART_FLAG_INDEX_TC,
                                              SET,
                                              timeout);

        if(DrvStatus != STATUS_OK)			
        {
            return(STATUS_TIMEOUT);
        }

        huart->TxXferCount++;
    }

    huart->State = HAL_UART_STATE_READY;

    return(STATUS_OK);
}

/**
 * @brief UART 模块接收数据函数
 * @param huart huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 * @param pdata 待接收数据指针
 * @param size  待接收数据长度
 * @param timeout  超时时间
 * @return  status_t 返回状态值
 */
status_t hal_uart_receive(uart_handle_t *huart, uint8_t *pdata, uint16_t size, uint32_t timeout)                                                                  
{
    uint16_t loop = 0;
    uint16_t tmp_val = 0x00;
    status_t DrvStatus;
    status_t tmp_status = STATUS_OK;

    /**/
    huart->RxXferSize = size;
    huart->RxXferCount = 0;
    huart->pRxBuffPtr = pdata;

    for(loop = 0; loop < huart->RxXferSize; loop++)
    {
        /*是否为空*/
        DrvStatus = drv_uart_waitonflagtimeout(huart->Instance,
                                              UART_FLAG_INDEX_RDRF,
                                              SET,
                                              timeout);

        if(DrvStatus != STATUS_OK)
        {
            return(STATUS_TIMEOUT);
        }

        drv_uart_getdata(huart->Instance, &tmp_val, huart->Init.DatabitsLength);
        *(huart->pRxBuffPtr + loop) = tmp_val;

        huart->RxXferCount++;
    }

    return(tmp_status);
}

/**
 * @brief UART 模块中断方式发送数据函数
 * @param huart huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 * @param pdata 待发送数据指针
 * @param size  待发送数据长度
 * @return  status_t 返回状态值
 */
status_t hal_uart_transmitit(uart_handle_t *huart, uint8_t *pdata, uint16_t size)
{
    status_t tmp_status = STATUS_OK;

    /**/
    huart->TxXferSize = size;
    huart->TxXferCount = 0;
    huart->pTxBuffPtr = pdata;

    if((huart->State & HAL_UART_STATE_BUSY_RX) == HAL_UART_STATE_BUSY_RX)
    {
        huart->State = HAL_UART_STATE_BUSY_TX_RX;
    }
    else
    {
        huart->State = HAL_UART_STATE_BUSY_TX;

    }

    /*使能TDRE中断*/
    drv_uart_disit(huart->Instance, UART_IT_INDEX_TCIE);
    drv_uart_enit(huart->Instance, UART_IT_INDEX_TDRE);

    return(tmp_status);
}


/**
 * @brief UART 模块中断方式接收数据函数
 * @param huart huart 指向uart_handle_t结构体的指针,此结构体包含了UART模块的配置信息
 * @param pdata 待接收数据指针
 * @param size  待接收数据长度
 * @return  status_t 返回状态值
 */
status_t hal_uart_receiveit(uart_handle_t *huart, uint8_t *pdata, uint16_t size)
{
    status_t tmp_status = STATUS_OK;

    /**/
    huart->RxXferSize = size;
    huart->RxXferCount = 0;
    huart->pRxBuffPtr = pdata;

    if (huart->State == HAL_UART_STATE_BUSY_TX)
    {
        huart->State = HAL_UART_STATE_BUSY_TX_RX;
    }
    else
    {
        huart->State = HAL_UART_STATE_BUSY_RX;
    }

    if (huart->Init.RxFifoEn == ENABLE)
    {
        /*使能接收FIFO中断使能位、接收FIFO溢出中断使能位、接收FIFO超时功能中断使能位*/
        drv_uart_enfifoit(huart->Instance, UART_IT_INDEX_RXFIE | UART_IT_INDEX_RXORIE | UART_IT_INDEX_RXFTOIE | UART_IT_INDEX_RXFTOE);
    }
    else
    {
        /*使能接收中断*/
        drv_uart_enit(huart->Instance, UART_IT_INDEX_RIE);
    }
    _uart_fifo_tx_clr(huart->Instance);
    _uart_fifo_rx_clr(huart->Instance);
    
    g_uart_rxbuf = pdata;

    return (tmp_status);
}

/**
 * @brief UART模块 IO初始化函数
 * @param puart     指向uart_typedef_t结构体的指针
 * @param GPIO_Init 指向gpio_init_t结构体的指针
 * @note
 *- 方向可独立设置;
 *- 上拉/下拉/三态影响
 *- 输出方式影响所有的管脚
 *- 输入方式影响所有的管脚
 *- 驱动能力影响所有的管脚
 *- SLEWRATE影响所有的管脚
 */
void hal_uart_gpioinit(uart_typedef_t *puart, gpio_init_t *gpio_init)
{
    /*切换为UART功能引脚  */
    drv_uart_funcswap(puart);

    if (gpio_init->Pin == UART_PIN_TXD)
    {
        drv_uart_distx(puart);

        if (gpio_init->Dir == GPIO_DIR_IN)
        {
            drv_uart_settxddirinput(puart);
        }
        else if (gpio_init->Dir == GPIO_DIR_OUT)
        {
            drv_uart_settxddiroutput(puart);

            /*cmos还是OPENDRAIN输出*/
            if (gpio_init->OutputMode == GPIO_OUTPUT_MODE_OPEN_DRAIN)
            {
            }
            else if (gpio_init->OutputMode == GPIO_OUTPUT_MODE_CMOS)
            {
            }
        }
        else if (gpio_init->Dir == GPIo_DIR_TRIGATE)
        {
            /*IO control 控制*/
        }

        /*上拉\下拉的控制在IO conttrol*/
        if (gpio_init->PullMode == GPIO_PULL_MODE_NOPULL)
        {
            /*既不上拉也不下拉*/
        }
        else if (gpio_init->PullMode == GPIO_PULL_MODE_UP)
        {
            /*上拉*/
        }
        else if (gpio_init->PullMode == GPIO_PULL_MODE_DOWN)
        {
            /*下拉*/
        }
    }
    else if (gpio_init->Pin == UART_PIN_RXD)
    {
        drv_uart_disrx(puart);

        if (gpio_init->Dir == GPIO_DIR_IN)
        {
            drv_uart_setrxddirinput(puart);
        }
        else if (gpio_init->Dir == GPIO_DIR_OUT)
        {
            drv_uart_setrxddiroutput(puart);

            /*cmos还是OPENDRAIN输出*/
            if (gpio_init->OutputMode == GPIO_OUTPUT_MODE_OPEN_DRAIN)
            {
            }
            else if (gpio_init->OutputMode == GPIO_OUTPUT_MODE_CMOS)
            {
            }
        }
        else if (gpio_init->Dir == GPIo_DIR_TRIGATE)
        {
            /*IO control 控制*/
        }
    }
}

/**
 * @brief UART 模块读取pin指定的UART的管脚当电平函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @param pin 具体管脚
 *- UART_PIN_TXD
 *- UART_PIN_RXD
 * @return gpio_pinstate_t
 */
gpio_pinstate_t hal_uart_gpioreadpin(uart_typedef_t *puart, uart_pin_t Pin)
{
    gpio_pinstate_t tmp_val;

    if (Pin == UART_PIN_RXD)
    {
        tmp_val = drv_uart_getrxdpinbit(puart);

        if (tmp_val)
        {
            return (GPIO_HIGH);
        }
        else
        {
            return (GPIO_LOW);
        }
    }
    else if (Pin == UART_PIN_TXD)
    {
        tmp_val = drv_uart_gettxdpinbit(puart);

        if (tmp_val)
        {
            return (GPIO_HIGH);
        }
        else
        {
            return (GPIO_LOW);
        }
    }
    return (tmp_val);
}

/**
 * @brief UART 模块使能RX DMA函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void hal_uart_enrxdma(uart_typedef_t *huart)
{
    _uart_rx_dma_en(huart);
}

/**
 * @brief UART 模块设置接收fifo超时时间函数
 * @param puart 指向uart_typedef_t结构体的指针
 * @return status_t 返回状态值
 */
status_t hal_uart_setrxfifotiemout(uart_typedef_t *huart, uint8_t cnt)
{
    _uart_set_rx_fifo_tiemout_cnt(huart, cnt);

    return STATUS_OK;
}

/**
 * @brief UART串口发送函数函数
 * @param huart 指向uart_typedef_t结构体的指针;
 * @param send 待发送数据
 * @param len 发送长度
 */
void hal_uart_senddata(uart_typedef_t *huart, uint8_t *send, uint16_t len)
{
    uint16_t i = 0;

    for (; i < len; i++)
    {
        while ((_uart_get_tdre_it_flag(huart)) == 0)
            ;
        drv_uart_senddata(huart, send[i], g_huart->Init.DatabitsLength);
        while ((_uart_get_tc_flag(huart)) == 0)
            ;
    }
}
void hal_uart_reset(void)
{
    drv_cpm_module_reset(UART1_MODULE);
    drv_cpm_module_reset(UART2_MODULE);	
    drv_cpm_module_reset(UART3_MODULE);
    drv_cpm_module_reset(UART4_MODULE);	
    drv_cpm_module_reset(UART5_MODULE);
    drv_cpm_module_reset(UART6_MODULE);
}