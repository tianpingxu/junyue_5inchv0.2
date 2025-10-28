/**
 * @file ssislv_drv.c 
 * @author Product application department 
 * @brief  SSI SLV 模块驱动层
 * @version V1.0 
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */

// 头文件包含
#include "ssislv_drv.h"
          
// 全局变量定义


// 函数定义
/**
 *  @brief  SSI SLV 初始化
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void drv_ssislv_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    p_ssislv->SSIENR = 0x00000000;              // 禁止 SSISLV 模块
    p_ssislv->CTRLR0 = (p_init->dfs << 0) | (p_init->frf << 6) | \
                       (p_init->scpha << 8) | (p_init->scpol << 9) | \
                       (p_init->tmod << 10) | (p_init->format << 22);
    p_ssislv->TXFTLR = 0x00000000;
    p_ssislv->RXFTLR = 0x00000000;
    p_ssislv->IMR = 0x00000000;                 // 禁止所有中断
    p_ssislv->SSIENR = SSISLV_EN;               // 使能 SSISLV 模块
}

/**
 *  @brief  SSI SLV 标准模式初始化
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void drv_ssislv_standard_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    p_init->frf = SSISLV_FRF_SPI;
    p_init->tmod = SSISLV_TX_AND_RX;
    p_init->format = SSISLV_STD_MODE;           // 标准模式，全双工传输

    drv_ssislv_init(p_ssislv, p_init);
}

/**
 *  @brief  SSI SLV 双线模式初始化
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void drv_ssislv_dual_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    p_init->frf = SSISLV_FRF_SPI;
    p_init->format = SSISLV_DUAL_MODE;          // 双线模式，半双工传输

    drv_ssislv_init(p_ssislv, p_init);
}

/**
 *  @brief  SSI SLV 四线模式初始化
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void drv_ssislv_quad_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    p_init->frf = SSISLV_FRF_SPI;
    p_init->format = SSISLV_QUAD_MODE;          // 四线模式，半双工传输

    drv_ssislv_init(p_ssislv, p_init);
}

/**
 *  @brief  SSI SLV 获取帧格式大小
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @return uint32_t 帧格式大小
 */
uint32_t drv_ssislv_get_frame_size(reg_ssislv_t *p_ssislv)
{
    uint32_t ssislv_para_dfs = 0;
    uint32_t frame_data_size = 0;

    ssislv_para_dfs = p_ssislv->CTRLR0 & 0x1f;

    if(ssislv_para_dfs > SSISLV_DFS_16_BIT)
    {
        frame_data_size = 4;
    }
    else if(ssislv_para_dfs > SSISLV_DFS_08_BIT)
    {
        frame_data_size = 2;
    }
    else
    {
        frame_data_size = 1;
    }

    return frame_data_size;
}

/**
 *  @brief  SSI SLV 等待 TX FIFO 清空
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 */
void drv_ssislv_wait_tx_fifo_empty(reg_ssislv_t *p_ssislv)
{
    while((p_ssislv->SR & SSISLV_SR_TFE) == 0x00);     // 等待 TX FIFO 清空
}

/**
 *  @brief  SSI SLV 标准模式传输数据
 * 
 *  @param p_ssislv  SSI SLV 寄存器结构体
 *  @param p_rec_buff 接收数据
 *  @param p_send_buff 预填发送数据
 *  @param xfer_len 接收数据长度
 *  @note CPU传输方式只支持8bit frame size
 */
void drv_ssislv_standard_xfer(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint8_t *p_send_buff, uint32_t xfer_len)
{
    uint32_t i = 0;

    if(xfer_len > 4)
    {
        p_ssislv->DR = *(p_send_buff ++);                       // 预填几个数据，防止连续传输时来不及填数据
        p_ssislv->DR = *(p_send_buff ++);
        p_ssislv->DR = *(p_send_buff ++);
        p_ssislv->DR = *(p_send_buff ++);

        while(xfer_len > 4)
        {
            p_ssislv->DR = *(p_send_buff ++);
            while((p_ssislv->SR & SSISLV_SR_RFNE) == 0x00);     // 等待RX FIFO收到数据
            *(p_rec_buff ++) = p_ssislv->DR;
            xfer_len--;
        }

        while(xfer_len > 0)
        {
            while((p_ssislv->SR & SSISLV_SR_RFNE) == 0x00);     // 等待RX FIFO收到数据
            *(p_rec_buff ++) = p_ssislv->DR;
            xfer_len --;
        }
    }
    else
    {
        for(i = 0; i < xfer_len; i ++)
        {
            p_ssislv->DR = *(p_send_buff ++);                   // 预填几个数据，防止连续传输时来不及填数据
        }

        for(i = 0; i < xfer_len; i ++)
        {
            while((p_ssislv->SR & SSISLV_SR_RFNE) == 0x00);     // 等待 RX FIFO收到数据
            *(p_rec_buff ++) = p_ssislv->DR;
        }
    }
}

/**
 *  @brief  SSI SLV 双线或四线模式接收数据
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_rec_buff 接收数据
 *  @param xfer_len 接收数据长度
 *  @note CPU传输方式只支持8bit frame size
 */
void drv_ssislv_dual_quad_rec(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint32_t xfer_len)
{
    while(xfer_len > 0)
    {
        while((p_ssislv->SR & SSISLV_SR_RFNE) == 0x00);     // 等待 RX FIFO 收到数据
        *(p_rec_buff++) = p_ssislv->DR;
        xfer_len --;
    }
}

/**
 *  @brief  SSI SLV 双线或四线模式发送数据
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_send_buff 发送数据
 *  @param xfer_len 发送数据长度
 */
void drv_ssislv_dual_quad_send(reg_ssislv_t *p_ssislv, uint8_t *p_send_buff, uint32_t xfer_len)
{
    while(xfer_len > 0)
    {
        while((p_ssislv->SR & SSISLV_SR_TFNF) == 0x00);        // 等待 TX FIFO 有空间后，填入新的数据
        p_ssislv->DR = *(p_send_buff ++);
        xfer_len --;
    }
}

/**
 *  @brief  SSI DMA 接收 FIFO 数据水平设定
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param dma_en SSI DMA 使能
 *  @param dma_data_level DMA 接收数据水平
 */
void drv_ssislv_rx_dma_config(reg_ssislv_t *p_ssislv, uint32_t dma_en, uint32_t dma_data_level)
{
    p_ssislv->DMARDLR = dma_data_level - 1;

    if(dma_en)
    {
        p_ssislv->DMACR |= SSISLV_DMACR_RDMAE;
    }
    else
    {
        p_ssislv->DMACR &=~ SSISLV_DMACR_RDMAE;
    }
}

/**
 *  @brief  SSI DMA 发送 FIFO 数据水平设定
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param dma_en SSI DMA 使能
 *  @param dma_data_level DMA 发送数据水平
 */
void drv_ssislv_tx_dma_config(reg_ssislv_t *p_ssislv, uint32_t dma_en, uint32_t dma_data_level)
{
    p_ssislv->DMATDLR = dma_data_level;

    if(dma_en)
    {
        p_ssislv->DMACR |= SSISLV_DMACR_TDMAE;
    }
    else
    {
        p_ssislv->DMACR &=~ SSISLV_DMACR_TDMAE;
    }
}
                                