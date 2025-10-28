/**
 * @file spi_hal.c
 * @author Product application department
 * @brief  SPI 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件定义
#include "spi_hal.h"
#include "eport_hal.h"
#include "cpm_hal.h"

// 全局变量定义
static volatile spi_handletypedef_t *g_hspi;
dmac_lli_t g_hal_spi_dma_lli[100];
static dmac_hdle_t g_hdma;

// 函数定义
/**
 * @brief SPI 模块dma链表中断服务函数
 */
void hal_spi_lli_irqhandler(void)
{
    if (drv_dmac_getrawstatus(DMAC1, 0))
    {
        drv_dmac_clearrawstatus(DMAC1, 0);

        /*add your code */
        while ((SPI1->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
            ;

        //        LCD_CS_HIGH;
        drv_spi_dis(SPI1);
        drv_spi_set_frame_size(SPI1, 0x07);
        drv_spi_en(SPI1);
        drv_dmac_set_raw_intdis(DMAC1, 0);
        drv_dma_dis(DMAC1);
    }
}

/**
 * @brief SPI 模块初始化函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 */
void hal_spi_init(volatile spi_handletypedef_t *hspi)
{
    drv_spi_deinit(hspi->Instance);
    if(hspi->Instance == SPI1)
    {
        SwitchPinFunction(SDH_DATA2_FUN,SPI1_MOSI_FUN);
        SwitchPinFunction(SDH_DATA3_FUN,SPI1_MISO_FUN);
        SwitchPinFunction(SDH_CMD_FUN,SPI1_CLK_FUN);
        SwitchPinFunction(SDH_CLK_FUN,SPI1_SS_FUN);
    }
    else if(hspi->Instance == SPI3)
    {
        SwitchPinFunction(SPI6_DATA2_FUN,SPI3_MOSI_FUN);
        SwitchPinFunction(SPI6_DATA3_FUN,SPI3_MISO_FUN);
        SwitchPinFunction(SPI6_DATA1_FUN,SPI3_CLK_FUN);
        SwitchPinFunction(SPI6_DATA0_FUN,SPI3_SS_FUN);
    }
    hspi->State = HAL_SPI_STATE_BUSY;
    drv_spi_init(hspi->Instance, &hspi->Init);
    hspi->RxCnt = 0;
    hspi->RxSize = 0;
    hspi->TxCnt = 0;
    hspi->TxSize = 0;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    hspi->State = HAL_SPI_STATE_READY;
    g_hspi = hspi;
}

/**
 * @brief SPI 模块查询方式通过指定的SPI端口发送数据函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 * @param pdata   待发送数据指针
 * @param size    待发送数据长度
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t hal_spi_transmit(volatile spi_handletypedef_t *hspi, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    status_t drvstatus = STATUS_OK;

    if (hspi->State != HAL_SPI_STATE_READY)
    {
        return STATUS_ERROR;
    }

    hspi->State = HAL_SPI_STATE_BUSY_TX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    hspi->pTxBuf = pdata;
    hspi->TxCnt = 0;
    hspi->TxSize = size;

    hspi->pRxBuf = NULL;
    hspi->RxCnt = 0;
    hspi->RxSize = 0;

    /*是否已经使能*/
    if (_spi_get_en(hspi->Instance) == 0)
    {
        drv_spi_en(hspi->Instance);
    }

    if (hspi->Init.Mode == SPI_MASTER)
    {
        drv_spi_transmitbytes(hspi->Instance, pdata, size);

        hspi->State = HAL_SPI_STATE_READY;
    }
    else if (hspi->Init.Mode == SPI_SLAVE)
    {
        drvstatus = drv_spi_slavetransmitbytes(hspi->Instance, pdata, size, timeout);

        if (drvstatus != STATUS_OK)
        {
            return drvstatus;
        }

        hspi->State = HAL_SPI_STATE_READY;
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块查询方式读取指定的SPI端口数据函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 * @param pdata   待接收数据指针
 * @param size    待接收数据长度
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t hal_spi_receive(volatile spi_handletypedef_t *hspi, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    status_t drvstatus = STATUS_OK;

    if (hspi->State != HAL_SPI_STATE_READY)
    {
        return STATUS_ERROR;
    }

    hspi->State = HAL_SPI_STATE_BUSY_RX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    hspi->pTxBuf = NULL;
    hspi->TxCnt = 0;
    hspi->TxSize = 0;

    hspi->pRxBuf = pdata;
    hspi->RxCnt = 0;
    hspi->RxSize = size;

    /*是否已经使能*/
    if (_spi_get_en(hspi->Instance) == 0)
    {
        drv_spi_en(hspi->Instance);
    }

    if (hspi->Init.Mode == SPI_MASTER)
    {
        drv_spi_receivebytes(hspi->Instance, pdata, size);
        hspi->State = HAL_SPI_STATE_READY;
    }
    else if (hspi->Init.Mode == SPI_SLAVE)
    {
        drv_spi_clr_rx_fifo(hspi->Instance);
        drvstatus = drv_spi_slavereceivebytes(hspi->Instance, pdata, size, timeout);

        if (drvstatus != STATUS_OK)
        {
            return drvstatus;
        }

        hspi->State = HAL_SPI_STATE_READY;
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块lli transfer函数
 * @param DMAC 指向dmac_typedef_t结构体的指针
 * @param channel DMA通道号
 * @param addr_peri 目的地址
 * @param buf 数据缓存
 * @param buf_len 数据长度
 * @param pkt_len 单次链表传输长度
 */
void hal_spi_dmac_lli_m2p_transfer(reg_dmac_t *DMAC, uint8_t channel, uint32_t *addr_peri, uint8_t *buf, int buf_len, int pkt_len)
{
    uint32_t pkt_residue = buf_len % pkt_len;
    uint32_t times = (buf_len / pkt_len) + 1;
    uint32_t timeout = 0x1ffff;

    g_hdma.instance = DMAC;
    g_hdma.init.channel_num = channel;

    hal_dmac_deinit(&g_hdma);

    g_hspi->Instance = SPI1;
    drv_spi_dis(g_hspi->Instance);
    drv_spi_set_frame_size(g_hspi->Instance, 0x0F);
    drv_spi_en(g_hspi->Instance);

    hal_spi_entxdma(g_hspi); // enable SPI DMACTX
    NVIC_Init(2, 2, DMA1_IRQn, 2);
    DMA1_IRQHandler_Callback = hal_spi_lli_irqhandler;
    if (pkt_residue == 0)
        times--;

    for (int i = 0; i < times; i++)
    {
        g_hal_spi_dma_lli[i].src_addr = (uint32_t)buf + pkt_len * i;
        g_hal_spi_dma_lli[i].dst_addr = (uint32_t)addr_peri;

        if (i == times - 1)
        {
            if (pkt_residue == 0)
            {
                g_hal_spi_dma_lli[i].len = pkt_len / 2;
                g_hal_spi_dma_lli[i].next_lli = NULL;
            }
            else
            {
                g_hal_spi_dma_lli[i].len = pkt_residue / 2;
                g_hal_spi_dma_lli[i].next_lli = NULL;
            }

            g_hal_spi_dma_lli[i].control = INTEN | SIEC | DNOCHG | M2P_DMA | DWIDTH_HW | SWIDTH_HW; //|0x2<<14|0x2<<11;
        }
        else
        {
            g_hal_spi_dma_lli[i].len = pkt_len / 2;
            g_hal_spi_dma_lli[i].next_lli = (uint32_t)&g_hal_spi_dma_lli[i + 1];
            g_hal_spi_dma_lli[i].control = INTEN | SIEC | DNOCHG | M2P_DMA | DWIDTH_HW | SWIDTH_HW | LLP_SRC_EN | LLP_DST_EN; //|0x2<<14|0x2<<11;
        }
    }

    drv_dmac_en(DMAC);
    drv_dmac_set_transfer_srcaddr(DMAC, channel, g_hal_spi_dma_lli[0].src_addr);
    drv_dmac_set_transfer_dstaddr(DMAC, channel, g_hal_spi_dma_lli[0].dst_addr);
    hal_dmac_set_LLI(DMAC, channel, (uint32_t)g_hal_spi_dma_lli);
    drv_damc_set_ch_ctrl(DMAC, channel, g_hal_spi_dma_lli[0].control);
    drv_dmac_set_transfer_length(DMAC, channel, g_hal_spi_dma_lli[0].len);
#if 1
    drv_dmac_set_src_soft(DMAC, channel);
    drv_dmac_set_dst_hard(DMAC, channel);
    drv_dmac_set_dst_peripheral(DMAC, channel, HAL_DMAC_PERIPHERAL_SPI1_TX);
    drv_dmac_set_raw_inten(DMAC, channel); //
#else
    _dmac_raw_interrupt_en(DMAC, channel);
#endif
    drv_dmac_ch_enable(DMAC, channel);
    //_dmac_ch_en(DMAC, channel);

    //   while (!LCD_TE_STA)
    //   {
    //       ;
    //   }

    while ((drv_dmac_getrawstatus(DMAC1, channel) || timeout--))
        ;
}

/**
 * @brief SPI 模块禁止函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void hal_spi_dis(volatile spi_handletypedef_t *hspi)
{
    drv_spi_dis(hspi->Instance);
}

/**
 * @brief SPI 模块使能函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void hal_spi_en(volatile spi_handletypedef_t *hspi)
{
    drv_spi_en(hspi->Instance);
}

/**
 * @brief SPI 模块清除RXFIFO函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void hal_spi_clrrxfifo(volatile spi_handletypedef_t *hspi)
{
    drv_spi_clr_rx_fifo(hspi->Instance);
}

/**
 * @brief SPI 模块清除TXFIFO函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void hal_spi_clrtxfifo(volatile spi_handletypedef_t *hspi)
{
    drv_spi_clr_tx_fifo(hspi->Instance);
}
/**
 * @brief SPI 模块pin指定的SPI的管脚输出pinstate指定电平函数
 * @param pspi 指向spi_typedef_t结构体的指针,此结构体包含了SPI模块的配置信息
 * @param pin SPI具体管脚
 *- SPI_PIN_CS
 *- SPI_PIN_CLK
 *- SPI_PIN_MOSI
 *- SPI_PIN_MISO
 * @param pinstate
 *- HAL_BIT_SET
 *- HAL_BIT_RESET
 */
void hal_spi_gpiowritepin(reg_spi_t
                              *pspi,
                          uint16_t pin, gpio_pinstate_t pinstate)
{
    drv_spi_writepin(pspi, pin, pinstate);
}

/**
 * @brief SPI 模块中断处理函数
 */
void hal_spi_irqhandler(void)
{
    /*如果中断源是SPIF且使能了中断*/
    if (_spi_get_flag_finish(g_hspi->Instance))
    {
        if (_spi_get_it(g_hspi->Instance))
        {
            /*判断接收还是发送*/
            if (g_hspi->State == HAL_SPI_STATE_BUSY_TX)
            {
                if (g_hspi->TxIsrCallback)
                {
                    g_hspi->TxIsrCallback((void *)g_hspi); // 自定义
                }
                else
                {
                    if (g_hspi->TxCnt < g_hspi->TxSize)
                    {
                        /*发送下一个数据*/
                        drv_spi_setdr(g_hspi->Instance, g_hspi->pTxBuf[g_hspi->TxCnt]);
                        g_hspi->TxCnt++;
                    }
                    else
                    {
                        /*发送完毕*/
                        drv_spi_dis_it(g_hspi->Instance);
                        g_hspi->State = HAL_SPI_STATE_READY;
                    }
                }
            }
            else
            {
                /*接收模式*/
                if (g_hspi->RxIsrCallback)
                {
                    g_hspi->RxIsrCallback((void *)g_hspi); // 自定义
                }
                else
                {
                    drv_spi_getdr(g_hspi->Instance, &g_hspi->pRxBuf[g_hspi->RxCnt]);
                    if (g_hspi->Init.Mode == SPI_MASTER)
                    {
                        if (g_hspi->pRxBuf[0] != CMD_HEAD)
                        {
                            if (g_hspi->Init.Mode == SPI_MASTER)
                            {
                                drv_spi_setdr(g_hspi->Instance, DUMMY_DATA);
                            }
                            return;
                        }
                    }
                    g_hspi->RxCnt++;
                    if (g_hspi->RxCnt < g_hspi->RxSize)
                    {
                        if (g_hspi->Init.Mode == SPI_MASTER)
                        {
                            drv_spi_setdr(g_hspi->Instance, DUMMY_DATA);
                        }
                    }
                    else
                    {
                        /*接收完毕*/
                        drv_spi_dis_it(g_hspi->Instance);
                        g_hspi->State = HAL_SPI_STATE_READY;
                    }
                }
            }
        }
    }
}

/**
 * @brief SPI 模块中断方式读取指定的SPI端口数据函数.
 * @param hspi  指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 * @param pdata   待接收数据指针
 * @param size    待接收数据长度
 * @return @ref status_t 当前状态
 */
status_t hal_spi_receiveit(volatile spi_handletypedef_t *hspi, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    status_t drvstatus = STATUS_OK;

    hspi->State = HAL_SPI_STATE_BUSY_RX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;

    hspi->pTxBuf = NULL;
    hspi->TxCnt = 0;
    hspi->TxSize = 0;

    hspi->pRxBuf = pdata;
    hspi->RxCnt = 0;
    hspi->RxSize = size;

    /*是否已经使能*/
    //    if(_spi_get_en(hspi->Instance) == 0)
    //    {
    //        _spi_en(hspi->Instance);
    //    }

    drv_spi_dis(hspi->Instance);
    drv_spi_en(hspi->Instance);

    drv_spi_clr_rx_fifo(hspi->Instance);
    drv_spi_clr_tx_fifo(hspi->Instance);

    if (hspi->Init.Mode == SPI_MASTER)
    {
        drv_spi_setdr(hspi->Instance, DUMMY_DATA);
    }

    drv_spi_en_it(hspi->Instance);

    return STATUS_OK;
}

/**
 * @brief SPI 模块 中断方式通过指定的SPI端口发送数据函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 * @param pdata 待发送数据指针
 * @param size  待发送数据长度
 * @return status_t 当前状态
 */
status_t hal_spi_transmitit(volatile spi_handletypedef_t *hspi, uint8_t *pdata, uint16_t size, uint32_t timeout)
{
    status_t drvstatus = STATUS_OK;

    if (hspi->State != HAL_SPI_STATE_READY)
    {
        return STATUS_ERROR;
    }

    hspi->State = HAL_SPI_STATE_BUSY_TX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    hspi->pTxBuf = pdata;
    hspi->TxCnt = 1;
    hspi->TxSize = size;

    hspi->pRxBuf = NULL;
    hspi->RxCnt = 0;
    hspi->RxSize = 0;

    /*是否已经使能*/
    if (_spi_get_en(hspi->Instance) == 0)
    {
        drv_spi_en(hspi->Instance);
    }

    /*使能SPI的中断*/
    //    _spi_en_it(hspi->Instance);

    /*第一个字节*/
    drv_spi_setdr(hspi->Instance, hspi->pTxBuf[0]);

    /*使能SPI的中断*/
    drv_spi_en_it(hspi->Instance);

    /*后续的数据在ISR中处理*/
    return STATUS_OK;
}

/**
 * @brief SPI 模块使能TX DMA函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void hal_spi_entxdma(volatile spi_handletypedef_t *hspi)
{
    drv_spi_en_tx_dma(hspi->Instance);
}

/**
 * @brief SPI 模块使能RX DMA函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void hal_spi_enrxdma(volatile spi_handletypedef_t *hspi)
{
    drv_spi_en_rx_dma(hspi->Instance);
}

/**
 * @brief SPI 模块获取标志状态函数
 * @param  hspi 指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 * @param  flagindex SPI标志索引
 *- SPI_FLAG_INDEX_RXFEMP
 *- SPI_FLAG_INDEX_RXFFULL
 *- SPI_FLAG_INDEX_XFEMP
 *- SPI_FLAG_INDEX_TXFFFUL
 *- SPI_FLAG_INDEX_MODE
 *- SPI_FLAG_INDEX_EOTF
 *- SPI_FLAG_INDEX_FLOST
 *- SPI_FLAG_INDEX_SPIF
 *- SPI_FLAG_INDEX_RXFSER
 *- SPI_FLAG_INDEX_RXFUDF
 *- SPI_FLAG_INDEX_RXFOVFM
 *- SPI_FLAG_INDEX_RXFTO
 *- SPI_FLAG_INDEX_TXFSER
 *- SPI_FLAG_INDEX_TXFUDF
 *- SPI_FLAG_INDEX_TXFOVFM
 *- SPI_FLAG_INDEX_TXFTO
 * @param staus 标志状态
 *- SET
 *- REST
 * @param timeout 超时时间
 * @return status_t 当前状态
 */
status_t hal_spi_waitonflagtimeout(volatile spi_handletypedef_t *hspi,
                                   spi_flagindex_t index,
                                   flagstatus_t status,
                                   uint32_t timeout)
{
    status_t drvstatus;

    drvstatus = drv_spi_waitonflagtimeout(hspi->Instance,
                                          index,
                                          status,
                                          timeout);

    if (drvstatus != STATUS_OK)
    {
        return drvstatus;
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块清除标志状态函数
 * @param  hspi 指向SPI_HandleTypeDef结构体的指针,此结构体包含了SPI模块的配置信息
 * @param  flagindex SPI标志索引
 *- SPI_FLAG_INDEX_RXFEMP
 *- SPI_FLAG_INDEX_RXFFULL
 *- SPI_FLAG_INDEX_XFEMP
 *- SPI_FLAG_INDEX_TXFFFUL
 *- SPI_FLAG_INDEX_MODE
 *- SPI_FLAG_INDEX_EOTF
 *- SPI_FLAG_INDEX_FLOST
 *- SPI_FLAG_INDEX_SPIF
 *- SPI_FLAG_INDEX_RXFSER
 *- SPI_FLAG_INDEX_RXFUDF
 *- SPI_FLAG_INDEX_RXFOVFM
 *- SPI_FLAG_INDEX_RXFTO
 *- SPI_FLAG_INDEX_TXFSER
 *- SPI_FLAG_INDEX_TXFUDF
 *- SPI_FLAG_INDEX_TXFOVFM
 *- SPI_FLAG_INDEX_TXFTO
 * @return status_t 当前状态
 */
status_t hal_spi_clrflag(volatile spi_handletypedef_t *hspi, spi_flagindex_t flagindex)
{
    status_t drvstatus;

    drvstatus = drv_spi_clrflag(hspi->Instance, flagindex);
    if (drvstatus != STATUS_OK)
    {
        return drvstatus;
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块DmaMasterTxPolling函数
 * @param pdmac 指向dmac_typedef_t结构体的指针
 * @param hspi 指向SPI_HandleTypeDef结构体的指针
 * @param ch 通道号
 * @param pbuf 数据缓存
 * @param len 数据长度
 * @return status_t 当前状态
 */
status_t hal_spi_dma_mastertxpolling(reg_dmac_t *pdmac, uint8_t ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len)
{
    status_t st;

    g_hdma.instance = pdmac;
    g_hdma.init.channel_num = ch;

    hal_spi_entxdma(hspi);

    /*复位DMAC*/
    hal_dmac_deinit(&g_hdma);
    g_hdma.init.dst_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.src_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.dst_inc = HAL_DMAC_DINC_NO_CHANGE;
    g_hdma.init.src_inc = HAL_DMAC_SINC_INC;
    g_hdma.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.transfer_type = HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;
    if (hspi->Instance == SPI1)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI1_TX;
    }
    else if (hspi->Instance == SPI2)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI2_TX;
    }
    else if (hspi->Instance == SPI3)
    {
        g_hdma.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SPI3_TX;
    }
    g_hdma.init.transfer_lli = HAL_DMAC_LLP_DIS;

    g_hdma.init.dst_addr = (uint32_t)(&hspi->Instance->DR);

    g_hdma.init.src_addr = (uint32_t)pbuf;
    g_hdma.init.transfer_size = len;

    /*初始化DMAC*/
    st = hal_dmac_init(&g_hdma);
    if (st != STATUS_OK)
    {
        return st;
    }

    /*开启非中断模式DMAC传输*/
    st = hal_dmac_startpolling(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*轮询传输完成*/
    st = hal_dmac_pollfortransfer(&g_hdma, 0, MAX_DELAY);

    if (st != STATUS_OK)
    {
        return st;
    }
    hal_dmac_clearrawstatus(&g_hdma, ch);
    st = hal_spi_waitonflagtimeout(hspi, SPI_FLAG_INDEX_EOTF, SET, 0);

    if (st != STATUS_OK)
    {
        return st;
    }
    else
    {
        hal_spi_clrflag(hspi, SPI_FLAG_INDEX_EOTF);
    }
    dcache_invalidate_range((uint32_t*)pbuf,len);
    return STATUS_OK;
}

/**
 * @brief SPI 模块DmaMasterRxPolling函数
 * @param pdmac 指向dmac_typedef_t结构体的指针
 * @param hspi 指向SPI_HandleTypeDef结构体的指针
 * @param tx_ch 发送通道号
 * @param rx_ch 接收通道号
 * @param pbuf 数据缓存
 * @param len 数据长度
 * @return  status_t 当前状态
 */
status_t hal_spi_dma_masterrxpolling(reg_dmac_t *pdmac,
                                     uint8_t tx_ch,
                                     uint8_t rx_ch,
                                     volatile spi_handletypedef_t *hspi,
                                     uint8_t *pbuf,
                                     uint32_t len)
{
    uint32_t tmp_tx_data = 0XAABBCCDD;

    status_t st;

    /****************************************************************************/
    /*RX通道初始化*/
    hal_spi_enrxdma(hspi);
    /*复位DMAC*/
    g_hdma.instance = pdmac;
    g_hdma.init.channel_num = rx_ch;
    hal_dmac_deinit(&g_hdma);

    g_hdma.init.dst_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.src_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.dst_inc = HAL_DMAC_DINC_INC;
    g_hdma.init.src_inc = HAL_DMAC_SINC_NO_CHANGE;
    g_hdma.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.transfer_type = HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA;
    if (hspi->Instance == SPI1)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI1_RX;
    }
    else if (hspi->Instance == SPI2)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI2_RX;
    }
    else if (hspi->Instance == SPI3)
    {
        g_hdma.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SPI3_RX;
    }
    g_hdma.init.transfer_lli = HAL_DMAC_LLP_DIS;

    g_hdma.init.src_addr = (uint32_t)(&hspi->Instance->DR);
    g_hdma.init.dst_addr = (uint32_t)(pbuf);
    g_hdma.init.transfer_size = len;

    /*初始化DMAC*/
    st = hal_dmac_init(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*开启非中断模式DMAC传输*/
    st = hal_dmac_startpolling(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /****************************************************************************/
    /*TX通道初始化*/
    hal_spi_entxdma(hspi);
    hal_spi_clrflag(hspi, SPI_FLAG_INDEX_EOTF);

    /*复位DMAC*/
    g_hdma.instance = pdmac;
    g_hdma.init.channel_num = tx_ch;
    hal_dmac_deinit(&g_hdma);

    g_hdma.init.dst_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.src_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.dst_inc = HAL_DMAC_DINC_NO_CHANGE;
    g_hdma.init.src_inc = HAL_DMAC_SINC_NO_CHANGE;
    g_hdma.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.transfer_type = HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;
    if (hspi->Instance == SPI1)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI1_TX;
    }
    else if (hspi->Instance == SPI2)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI2_TX;
    }
    else if (hspi->Instance == SPI3)
    {
        g_hdma.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SPI3_TX;
    }
    g_hdma.init.transfer_lli = HAL_DMAC_LLP_DIS;

    g_hdma.init.dst_addr = (uint32_t)(&hspi->Instance->DR);
    g_hdma.init.src_addr = (uint32_t)(&tmp_tx_data);
    g_hdma.init.transfer_size = len;
    /*初始化DMAC*/
    st = hal_dmac_init(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*开启非中断模式DMAC传输*/
    st = hal_dmac_startpolling(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*轮询传输完成*/
    g_hdma.init.channel_num = rx_ch;
    st = hal_dmac_pollfortransfer(&g_hdma, 0, MAX_DELAY);

    if (st != STATUS_OK)
    {
        return st;
    }

    st = hal_spi_waitonflagtimeout(hspi, SPI_FLAG_INDEX_EOTF, SET, 0);

    if (st != STATUS_OK)
    {
        return st;
    }
    else
    {
        hal_spi_clrflag(hspi, SPI_FLAG_INDEX_EOTF);
    }

    hal_dmac_clearrawstatus(&g_hdma, tx_ch);
    dcache_invalidate_range((uint32_t*)pbuf,len);
    return STATUS_OK;
}

/**
 * @brief DMA 模块DmaSlaveRxPolling函数
 * @param pdmac 指向dmac_typedef_t结构体的指针
 * @param hspi 指向SPI_HandleTypeDef结构体的指针
 * @param ch DMA通道号
 * @param pbuf 数据缓存
 * @param len 数据长度
 * @return status_t 当前状态
 */
status_t hal_spi_dma_slaverxpolling(reg_dmac_t *pdmac, uint8_t ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len)
{
    uint32_t tmp_add = 0;
    status_t st;

    g_hdma.instance = pdmac;
    g_hdma.init.channel_num = ch;

    _spi_dis_rx_dma(hspi->Instance);
    _spi_dis_tx_dma(hspi->Instance);

    /*复位DMAC*/
    hal_dmac_deinit(&g_hdma);
    g_hdma.init.dst_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.src_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.dst_inc = HAL_DMAC_DINC_INC;
    g_hdma.init.src_inc = HAL_DMAC_SINC_NO_CHANGE;
    g_hdma.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.transfer_type = HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA;
    if (hspi->Instance == SPI1)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI1_RX;
    }
    else if (hspi->Instance == SPI2)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI2_RX;
    }
    else if (hspi->Instance == SPI3)
    {
        g_hdma.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SPI3_RX;
    }
    g_hdma.init.transfer_lli = HAL_DMAC_LLP_DIS;

    tmp_add = (uint32_t)(&hspi->Instance->DR);
    g_hdma.init.src_addr = tmp_add;
    g_hdma.init.dst_addr = (uint32_t)pbuf;
    g_hdma.init.transfer_size = len;
    /*初始化DMAC*/
    st = hal_dmac_init(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*开启非中断模式DMAC传输*/
    hal_spi_enrxdma(hspi);
    st = hal_dmac_startpolling(&g_hdma);

    if (st != STATUS_OK)
    {
        _spi_dis_rx_dma(hspi->Instance);
        return st;
    }

    /*轮询传输完成*/
    st = hal_dmac_pollfortransfer(&g_hdma, 0, MAX_DELAY);
    
    if (st != STATUS_OK)
    {
        _spi_dis_rx_dma(hspi->Instance);
        return st;
    }
    dcache_invalidate_range((uint32_t*)pbuf,len);
    _spi_dis_rx_dma(hspi->Instance);

    return STATUS_OK;
}

/**
 * @brief SPI 模块DmaSlaveTxPolling函数
 * @param pdmac 指向dmac_typedef_t结构体的指针
 * @param hspi 指向SPI_HandleTypeDef结构体的指针
 * @param ch DMA通道号
 * @param pbuf 数据缓存
 * @param len 数据长度
 * @return status_t 当前状态
 */
status_t hal_spi_dma_slavetxpolling(reg_dmac_t *pdmac, uint8_t ch, volatile spi_handletypedef_t *hspi, uint8_t *pbuf, uint32_t len)
{
    status_t st;

    g_hdma.instance = pdmac;
    g_hdma.init.channel_num = ch;

    hal_spi_entxdma(hspi);
    /*复位DMAC*/
    hal_dmac_deinit(&g_hdma);
    g_hdma.init.dst_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.src_msize = HAL_DMAC_MSIZE_1;
    g_hdma.init.dst_inc = HAL_DMAC_DINC_NO_CHANGE;
    g_hdma.init.src_inc = HAL_DMAC_SINC_INC;
    g_hdma.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    g_hdma.init.transfer_type = HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;
    if (hspi->Instance == SPI1)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI1_TX;
    }
    else if (hspi->Instance == SPI2)
    {
        g_hdma.init.peripheral_type = HAL_DMAC_PERIPHERAL_SPI2_TX;
    }
    else if (hspi->Instance == SPI3)
    {
        g_hdma.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SPI3_TX;
    }
    g_hdma.init.transfer_lli = HAL_DMAC_LLP_DIS;

    g_hdma.init.dst_addr = (uint32_t)(&hspi->Instance->DR);
    g_hdma.init.src_addr = (uint32_t)pbuf;
    g_hdma.init.transfer_size = len;

    /*初始化DMAC*/
    st = hal_dmac_init(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*开启非中断模式DMAC传输*/
    st = hal_dmac_startpolling(&g_hdma);

    if (st != STATUS_OK)
    {
        return st;
    }

    /*轮询传输完成*/
    st = hal_dmac_pollfortransfer(&g_hdma, 0, MAX_DELAY);

    if (st != STATUS_OK)
    {
        return st;
    }
   
    hal_dmac_clearrawstatus(&g_hdma, ch);

    st = hal_spi_waitonflagtimeout(hspi, SPI_FLAG_INDEX_EOTF, SET, 0);

    if (st != STATUS_OK)
    {
        return st;
    }
    else
    {
        hal_spi_clrflag(hspi, SPI_FLAG_INDEX_EOTF);
    }
    dcache_invalidate_range((uint32_t*)pbuf,len);
    return STATUS_OK;
}
