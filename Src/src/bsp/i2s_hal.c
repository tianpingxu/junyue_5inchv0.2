/**
 * @file i2s_reg.h
 * @author Product Application Department
 * @brief  I2S 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "i2s_hal.h"

// 全局变量定义
#define DMA_MAX_TRANSLEN 0xFF1

// 函数定义
/**
 * @brief I2S 模块HAL层初始化函数
 *
 * @param hi2s hi2s实例化
 * @return status_t
 */
status_t hal_i2s_init(i2s_handle_t *hi2s)
{
    if (hi2s->State == HAL_I2S_STATE_RESET)
    {
        // hal_i2c_mspinit(hi2s);
    }

    hi2s->State = HAL_I2S_STATE_BUSY;

    /*初始化硬件层相关*/
    drv_i2s_init(hi2s->Instance, &hi2s->Init);

    hi2s->XferCnt = 0;
    hi2s->XferSize = 0;
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
    /*状态更改为READY*/
    hi2s->State = HAL_I2S_STATE_READY;

    return STATUS_OK;
}

/**
 * @brief I2S 模块发送函数
 *
 * @param hi2s hi2s实例化
 * @param pData I2S发送的数据指针
 * @param Size I2S发送的数据长度
 * @param Timeout I2S发送超时设定
 * @return status_t
 */
status_t hal_i2s_mastertransmit(i2s_handle_t *hi2s, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2s->State == HAL_I2S_STATE_READY)
    {
        /*                              */
        hi2s->State = HAL_I2S_STATE_BUSY_TX;
        hi2s->Mode = I2S_MODE_PLAY;
        hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
        hi2s->pXferBuf = pData;
        hi2s->XferCnt = 0;
        hi2s->XferSize = Size;

        DrvStatus = drv_i2s_transmit(hi2s->Instance, hi2s->pXferBuf, hi2s->XferSize, Timeout);
        if (DrvStatus != STATUS_OK)
        {
            hi2s->State = HAL_I2S_STATE_READY;
            return (DrvStatus);
        }
        hi2s->State = HAL_I2S_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}

/**
 * @brief I2S 模块接收函数
 *
 * @param hi2s hi2s实例化
 * @param pData I2S接收的数据指针
 * @param Size I2S接收的数据长度
 * @param Timeout I2S接收超时设定
 * @return status_t
 */
status_t hal_i2s_masterreceive(i2s_handle_t *hi2s, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    status_t DrvStatus;

    /*不能双工工作，同时只能有发送或者接收*/
    if (hi2s->State == HAL_I2S_STATE_READY)
    {
        /**/
        hi2s->State = HAL_I2S_STATE_BUSY_TX;
        hi2s->Mode = I2S_MODE_RECORD;
        hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
        hi2s->pXferBuf = pData;
        hi2s->XferCnt = 0;
        hi2s->XferSize = Size;
        /*中断处理函数为空*/
        // hi2c->XferISR = 0;

        DrvStatus = drv_i2s_receive(hi2s->Instance, hi2s->pXferBuf, hi2s->XferSize, Timeout);

        if (DrvStatus != STATUS_OK)
        {
            hi2s->State = HAL_I2S_STATE_READY;
            return (DrvStatus);
        }

        hi2s->State = HAL_I2S_STATE_READY;
    }
    else
    {
        return (STATUS_BUSY);
    }

    return (STATUS_OK);
}
/**
 * @brief I2S 模块中断回调处理函数
 *
 */
void hal_i2s_callback_handle(void)
{
}
/**
 * @brief I2S 模块用DMA发送函数
 *
 * @param ch DMA通道编号
 * @param pi2s i2s模块实例化
 * @param pbuf i2s发送数据指针
 * @param len i2s发送数据长度
 * @return status_t
 */
status_t hal_i2s_dmactx(uint8_t ch, reg_i2s_t *pi2s, uint8_t *pbuf, uint32_t len)
{
    dmac_lli_t g_dma_lli[70];
    dmac_hdle_t hdma;
    status_t st;
    uint32_t i;
    uint32_t lli_num;
    uint32_t pkt_len, pkt_residue;

    if (pi2s == I2S1)
    {
        hdma.instance = DMAC1;
    }
    else
    {
        hdma.instance = DMAC2;
    }

    hdma.init.channel_num = ch;

    hal_dmac_deinit(&hdma);

    st = hal_dmac_init(&hdma);
    if (st != STATUS_OK)
    {
        return (st);
    }
    hdma.dma_raw_callback = hal_i2s_callback_handle;
    if (pi2s == I2S1)
        DMA1_IRQHandler_Callback = hal_dmac_irqhandler; // HAL_DMAC_IRQHandler;
    else
        DMA2_IRQHandler_Callback = hal_dmac_irqhandler;

    if (pi2s == I2S1)
        NVIC_Init(DMA1_IRQn, 1, 0, 3);
    else
        NVIC_Init(DMA2_IRQn, 1, 0, 3);

    dcache_clean_range(pbuf, sizeof(len));

    drv_dmac_en(hdma.instance);

    pkt_len = DMA_MAX_TRANSLEN;
    pkt_residue = len % pkt_len;

    lli_num = len / pkt_len + 1;
    if (pkt_residue == 0)
    {
        lli_num--;
    }

    for (i = 0; i < lli_num; i++)
    {
        g_dma_lli[i].src_addr = (uint32_t)pbuf + pkt_len * i;
        g_dma_lli[i].dst_addr = (uint32_t)(&pi2s->TXDR);
        if (i < (lli_num - 1))
        {
            g_dma_lli[i].next_lli = (uint32_t)&g_dma_lli[i + 1];
            g_dma_lli[i].len = pkt_len/2 ;// due to DMAC_SRC_TR_WIDTH_SHIFT_MASK
            g_dma_lli[i].control = DMAC_INT_EN | DMAC_DINC_NO_CHANGE | DMAC_SINC_INC | DMAC_LLP_DST_EN | DMAC_LLP_SRC_EN 
                                    | (HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA << DMAC_TT_FC_SHIFT_MASK) 
                                    | (HAL_DMAC_TR_WIDTH_32BITS << DMAC_DST_TR_WIDTH_SHIFT_MASK) 
                                    | (HAL_DMAC_TR_WIDTH_16BITS << DMAC_SRC_TR_WIDTH_SHIFT_MASK);
        }
        else
        {
            g_dma_lli[i].next_lli = 0;
            g_dma_lli[i].len = pkt_residue/2 ;// due to DMAC_SRC_TR_WIDTH_SHIFT_MASK
            g_dma_lli[i].control = DMAC_INT_EN | DMAC_DINC_NO_CHANGE | DMAC_SINC_INC 
                                    | (HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA << DMAC_TT_FC_SHIFT_MASK) 
                                    | (HAL_DMAC_TR_WIDTH_32BITS << DMAC_DST_TR_WIDTH_SHIFT_MASK) 
                                    | (HAL_DMAC_TR_WIDTH_16BITS << DMAC_SRC_TR_WIDTH_SHIFT_MASK);
        }


    }

    drv_damc_set_ch_ctrl(hdma.instance, ch, g_dma_lli[0].control);
    drv_dmac_llireginit(hdma.instance, ch, &g_dma_lli[0]);

    drv_dmac_set_src_soft(hdma.instance, ch);
    drv_dmac_set_dst_hard(hdma.instance, ch);

    if (pi2s == I2S1)
    {
        drv_i2s_dmatxen(I2S1);
        drv_dmac_set_dst_peripheral(hdma.instance, ch, HAL_DMAC_PERIPHERAL_I2S1_TX);
    }
    else if (pi2s == I2S2)
    {
        drv_i2s_dmatxen(I2S2);
        drv_dmac_set_dst_peripheral(hdma.instance, ch, HAL_DMAC2_PERIPHERAL_I2S2_TX);
    }

    /* Enable the transfer complete flag*/
    // _dmac_raw_interrupt_en(DMAC3, ch);
    drv_dmac_set_raw_inten(hdma.instance, ch);
    drv_dmac_ch_enable(hdma.instance, ch);
    drv_i2s_txen(pi2s);

    // st = hal_dmac_pollfortransfer_it(&hdma, 0, MAX_DELAY);
    while(!drv_dmac_getrawstatus(hdma.instance, ch));

    while ((pi2s->ESR & I2S_ESR_TXAU) == 0)
        ;

    drv_i2s_txdis(pi2s);

    drv_i2s_dmatxdis(pi2s);

    if (st != STATUS_OK)
    {
        return (st);
    }

    st = hal_dmac_deinit(&hdma);
    if (st != STATUS_OK)
    {
        return (st);
    }

    return (STATUS_OK);
}

/**
 * @brief I2S 模块用DMA接收函数
 *
 * @param ch DMA通道编号
 * @param pi2s i2s模块实例化
 * @param pbuf i2s接收数据指针
 * @param len i2s接收数据长度
 * @return status_t
 */
status_t hal_i2s_dmacrx(uint8_t ch, reg_i2s_t *pi2s, uint8_t *pbuf, uint32_t len)
{
    dmac_lli_t g_dma_lli[70];
    dmac_hdle_t hdma;
    status_t st;
    uint32_t i = 0;
    uint32_t lli_num = 0;
    uint32_t point = 0;
    uint32_t tran_len = 0;

    // TO DO: 接收缺少硬件暂未测试
    drv_i2s_dmarxcnt(pi2s, 4);
    drv_i2s_dmarxen(pi2s);
    if (pi2s == I2S1)
        hdma.instance = DMAC1;
    else
        hdma.instance = DMAC2;
    hdma.init.channel_num = ch;
    hal_dmac_deinit(&hdma);

    st = hal_dmac_init(&hdma);
    if (st != STATUS_OK)
        return st;

    hdma.dma_raw_callback = hal_i2s_callback_handle;
    if (pi2s == I2S1)
        DMA1_IRQHandler_Callback = hal_dmac_irqhandler; // HAL_DMAC_IRQHandler;
    else
        DMA2_IRQHandler_Callback = hal_dmac_irqhandler;

    if (pi2s == I2S1)
        NVIC_Init(DMA1_IRQn, 1, 0, 3);
    else
        NVIC_Init(DMA2_IRQn, 1, 0, 3);

    drv_dmac_en(hdma.instance);

    tran_len = DMA_MAX_TRANSLEN;
    lli_num = len / (DMA_MAX_TRANSLEN << 2);
    if (len % (DMA_MAX_TRANSLEN << 2))
    {
        lli_num++;
    }

    for (i = 0; i < lli_num; i++)
    {
        g_dma_lli[i].src_addr = (uint32_t)(&pi2s->RXDR);
        g_dma_lli[i].dst_addr = (uint32_t)pbuf + point;
        if (i < (lli_num - 1))
        {
            g_dma_lli[i].next_lli = (uint32_t)&g_dma_lli[i + 1];
        }
        else
        {
            g_dma_lli[i].next_lli = 0;
        }
        g_dma_lli[i].control = DMAC_INT_EN | DMAC_DINC_INC | DMAC_SINC_NO_CHANGE | DMAC_LLP_DST_EN | DMAC_LLP_SRC_EN | (HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA << DMAC_TT_FC_SHIFT_MASK) | (HAL_DMAC_TR_WIDTH_32BITS << DMAC_DST_TR_WIDTH_SHIFT_MASK) | (HAL_DMAC_TR_WIDTH_32BITS << DMAC_SRC_TR_WIDTH_SHIFT_MASK);
        g_dma_lli[i].len = tran_len;

        point += (tran_len << 2);
        len -= (tran_len << 2);
        if (len > (DMA_MAX_TRANSLEN << 2))
        {
            tran_len = DMA_MAX_TRANSLEN;
        }
        else
        {
            tran_len = (len >> 2);
        }
    }

    drv_damc_set_ch_ctrl(hdma.instance, ch, g_dma_lli[0].control);
    drv_dmac_llireginit(hdma.instance, ch, &g_dma_lli[0]);

    drv_dmac_set_src_hard(hdma.instance, ch);
    drv_dmac_set_dst_soft(hdma.instance, ch);

    if (pi2s == I2S1)
    {
        // _dmac_set_dst_peripheral(DMAC3, ch, HAL_DMAC3_PERIPHERAL_I2S1_TX);
        drv_dmac_set_dst_peripheral(hdma.instance, ch, HAL_DMAC_PERIPHERAL_I2S1_TX);
    }
    else if (pi2s == I2S2)
    {
        // _dmac_set_dst_peripheral(DMAC3, ch, HAL_DMAC3_PERIPHERAL_I2S2_TX);
        drv_dmac_set_dst_peripheral(hdma.instance, ch, HAL_DMAC2_PERIPHERAL_I2S2_TX);
    }
    /* Enable the transfer complete flag*/
    // _dmac_raw_interrupt_en(DMAC3, ch);
    drv_dmac_set_raw_inten(hdma.instance, ch);
    drv_i2s_rxen(pi2s);
    drv_dmac_ch_enable(hdma.instance, ch);

    st = hal_dmac_pollfortransfer_it(&hdma, 0, MAX_DELAY);

    // while( (pi2s->SR & (1<<4)) == 0)
    // {
    // }
    drv_i2s_rxdis(pi2s);
    drv_i2s_dmarxen(pi2s);

    st = hal_dmac_deinit(&hdma);
    if (st != STATUS_OK)
        return (st);

    dcache_invalidate_range(pbuf, len);

    return STATUS_OK;
}
