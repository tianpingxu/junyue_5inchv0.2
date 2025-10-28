/**
 * @file uart_test.c
 * @author Product application department
 * @brief UART 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup UART UART模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "uart_test.h"


// 全局变量定义
#define UART_POLLING_TEST	0
#define UART_IRQ_TEST		0
#define UART_DMA_IDLE_TEST	0
#define UART_IRQ_IDLE_TEST	1

uart_typedef_t *g_uart_type = UART2;
uart_handle_t g_uart_handle;
uint8_t uart_rx_buf[UART_BUFFER_SIZE];
uint8_t uart_tx_buf[UART_BUFFER_SIZE];
static uint8_t uart_ringbuff[6][UART_BUFFER_SIZE] = {0};

// 函数定义


/**
 * @brief UART 模块轮询测试函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void uart_polling_test(uart_typedef_t *puart)
{
    status_t ret = STATUS_OK;
    uint32_t len;
    uint32_t timeout;
    g_uart_handle.Init.BaudRate = 115200;
    g_uart_handle.Init.IPSFreq = g_ips_clk;
    g_uart_handle.Init.Parity = UART_PARITY_MODE_NONE;
    g_uart_handle.Init.DatabitsLength = UART_DATA_BITS_LENGTH_8;
    g_uart_handle.Init.StopbitsLength = UART_STOP_BITS_LENGTH_1;
    g_uart_handle.Instance = puart;
    g_uart_handle.Init.IdleEn = DISABLE;
    g_uart_handle.Init.RxFifoEn = DISABLE;
    g_uart_handle.Init.RxFifoFull = UART_FIFO_1_8;
    g_uart_handle.Init.TxFifoEn = DISABLE;
    g_uart_handle.Init.TxFifoFull = UART_FIFO_1_8;
    
    hal_uart_init(&g_uart_handle);
    
    len = 16;
    timeout = 0;

    while(1)
    {
        memset(uart_rx_buf,0,sizeof(uart_rx_buf));
        ret = hal_uart_receive(&g_uart_handle, uart_rx_buf, len, timeout);
        if(ret != STATUS_OK)
        {
            printf("uart receive failed, ret = %04x\r\n",ret);
            continue;
        }
        ret = hal_uart_transmit(&g_uart_handle, uart_rx_buf, len, timeout);
        if(ret != STATUS_OK)
        {
            printf("uart tranmit failed, ret = %04x\r\n",ret);
            continue;
        }
    }
}

/**
 * @brief UART 模块中断测试函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void uart_it_test(uart_typedef_t *puart)
{
    status_t ret = STATUS_OK;
    uint32_t len;
    g_uart_handle.Init.BaudRate = 115200;
    g_uart_handle.Init.IPSFreq = g_ips_clk;
    g_uart_handle.Init.Parity = UART_PARITY_MODE_NONE;
    g_uart_handle.Init.DatabitsLength = UART_DATA_BITS_LENGTH_8;
    g_uart_handle.Init.StopbitsLength = UART_STOP_BITS_LENGTH_1;
    g_uart_handle.Instance = puart;
    g_uart_handle.Init.IdleEn = DISABLE;
    g_uart_handle.Init.RxFifoEn = ENABLE;
    g_uart_handle.Init.RxFifoFull = UART_FIFO_1_8;
    g_uart_handle.Init.TxFifoEn = ENABLE;
    g_uart_handle.Init.TxFifoFull = UART_FIFO_1_8;
    
    hal_uart_init(&g_uart_handle);
    hal_uart_itinit();
    
    len = 16;
    while(1)
    {
        memset(uart_rx_buf, 0x00, sizeof(uart_rx_buf));
        hal_uart_receiveit(&g_uart_handle,  uart_rx_buf, len);
        if(ret != STATUS_OK)
        {
            printf("uart receive it failed, ret = %04x\r\n",ret);
            continue;
        }
        while(g_uart_handle.State != HAL_UART_STATE_READY);

        hal_uart_transmitit(&g_uart_handle, uart_rx_buf, len);
        if(ret != STATUS_OK)
        {
            printf("uart tranmit failed, ret = %04x\r\n",ret);
            continue;
        }
        while(g_uart_handle.State != HAL_UART_STATE_READY);
    }
}

/**
 * @brief UART 模块DMA中断测试函数
 * @param puart 指向uart_typedef_t结构体的指针
 */
void uart_dma_ringbuf_transfer(uart_typedef_t *puart)
{
    uint8_t dma_channel;
    uint16_t ret;

    g_uart_handle.Init.BaudRate = 115200;
    g_uart_handle.Init.IPSFreq = g_ips_clk;
    g_uart_handle.Init.Parity = UART_PARITY_MODE_NONE;
    g_uart_handle.Init.DatabitsLength = UART_DATA_BITS_LENGTH_8;
    g_uart_handle.Init.StopbitsLength = UART_STOP_BITS_LENGTH_1;
    g_uart_handle.Instance = puart;
    g_uart_handle.Init.IdleEn = ENABLE;
    g_uart_handle.Init.RxFifoEn = ENABLE;
    g_uart_handle.Init.TxFifoEn = DISABLE;
    g_uart_handle.Init.RxFifoFull = UART_FIFO_1_8;
    hal_uart_init(&g_uart_handle);
    hal_uart_setrxfifotiemout(puart, 15);
    hal_uart_enrxdma(puart);
    hal_uart_receiveit(&g_uart_handle, uart_rx_buf, UART_BUFFER_SIZE);
    hal_uart_itinit();
    if (puart == UART1)
    {
        dma_channel = 0;
        ret = hal_uart_dmareceive_ringbuf_init(UART1, dma_channel, uart_ringbuff[0], UART_BUFFER_SIZE);
    }
    else if (puart == UART2)
    {
        dma_channel = 0;
        ret = hal_uart_dmareceive_ringbuf_init(UART2, dma_channel, uart_ringbuff[1], UART_BUFFER_SIZE);
    }
    else if (puart == UART3)
    {
        dma_channel = 1;
        ret = hal_uart_dmareceive_ringbuf_init(UART3, dma_channel, uart_ringbuff[2], UART_BUFFER_SIZE);
    }
    else if (puart == UART4)
    {
        dma_channel = 1;
        ret = hal_uart_dmareceive_ringbuf_init(UART4, dma_channel, uart_ringbuff[3], UART_BUFFER_SIZE);
    }
    else if (puart == UART5)
    {
        dma_channel = 2;
        ret = hal_uart_dmareceive_ringbuf_init(UART5, dma_channel, uart_ringbuff[4], UART_BUFFER_SIZE);
    }
    else if (puart == UART6)
    {
        dma_channel = 3;
        ret = hal_uart_dmareceive_ringbuf_init(UART6, dma_channel, uart_ringbuff[5], UART_BUFFER_SIZE);
    }
}

uint8_t buff[1] = {0xAA};
void uart_irq_idle_transfer(uart_typedef_t *puart)
{
    g_uart_handle.Init.BaudRate = 9600;
    g_uart_handle.Init.IPSFreq = g_ips_clk;
    g_uart_handle.Init.Parity = UART_PARITY_MODE_NONE;
    g_uart_handle.Init.DatabitsLength = UART_DATA_BITS_LENGTH_8;
    g_uart_handle.Init.StopbitsLength = UART_STOP_BITS_LENGTH_1;
    g_uart_handle.Instance = puart;
    g_uart_handle.Init.IdleEn = DISABLE;
    g_uart_handle.Init.RxFifoEn = ENABLE;
    g_uart_handle.Init.TxFifoEn = DISABLE;
    g_uart_handle.Init.RxFifoFull = UART_FIFO_1_8;
    g_uart_handle.Init.TxFifoFull = UART_FIFO_1_8;
    hal_uart_init(&g_uart_handle);
    hal_uart_itinit();

    drv_uart_enfifoit(puart, UART_IT_INDEX_RXFIE | UART_IT_INDEX_RXORIE | UART_IT_INDEX_RXFTOIE | UART_IT_INDEX_RXFTOE);
	_uart_fifo_rx_clr(puart);

    buff_send_to_uart(buff, 1);
}
/**
 * @brief UART 模块测试示例函数
 */
void uart_demo(void)
{
#if UART_POLLING_TEST
    uart_polling_test(g_uart_type);
#endif
#if UART_IRQ_TEST
    uart_it_test(g_uart_type);
#endif	
#if UART_DMA_IDLE_TEST
    uart_dma_ringbuf_transfer(g_uart_type);
#endif
#if UART_IRQ_IDLE_TEST
    uart_irq_idle_transfer(g_uart_type);
#endif
}

void buff_send_to_uart(uint8_t* buf, uint16_t len){
    // printf("tx_buff -- ");
    // for(uint8_t i = 0; i < len; i++) {
    //     printf("%02X ", buf[i]);
    // }
    // printf("\r\n");
    for(int i = 0; i < len; i++)
	{
		g_uart_type->DRL = (uint8_t)buf[i];
		while ((g_uart_type->SR1 & UART_SR1_TC_MASK) == 0x00);
	}
}


/** @} */  // 结束 UART 模块分组
/** @} */  // 结束外设模块分组

