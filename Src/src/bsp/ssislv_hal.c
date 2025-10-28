/**
 * @file ssislv_hal.c 
 * @author Product application department 
 * @brief  SSI SLV 模块硬件抽象层，供应用层调用，仅供参考
 * @version v1.0 
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */

// 头文件包含
#include "ssislv_hal.h"
  
// 全局变量定义
dmac_hdle_t hdma_ssislv_rx;
dmac_hdle_t hdma_ssislv_tx;
static dmac_lli_t dma_lli[2];      // DMA需要访问该 linked list，该变量必须分配在通用SRAM内
uint8_t *ssislv_app_data_buff = (uint8_t*) 0x18000000;
volatile uint32_t packet_cnt = 0;

// 函数定义
/**
 *  @brief  SSISLAVE 模块标准模式初始化函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void hal_ssislv_standard_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    // _ioctrl_swapcr_swap8_set;
    // _ioctrl_swapcr_swap9_set;
    // _ioctrl_swapcr_swap10_set;
    // _ioctrl_swapcr_swap11_set;       // 将SPI2管脚复用成 SSISLV1 功能
    drv_ssislv_standard_init(p_ssislv, p_init);
}

/**
 *  @brief  SSISLAVE 模块双线模式初始化函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void hal_ssislv_dual_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    // _ioctrl_swapcr_swap8_set;
    // _ioctrl_swapcr_swap9_set;
    // _ioctrl_swapcr_swap10_set;
    // _ioctrl_swapcr_swap11_set;       // 将SPI2管脚复用成 SSISLV1 功能 
    drv_ssislv_dual_init(p_ssislv, p_init);
}

/**
 *  @brief  SSISLAVE 模块四线模式初始化函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_init SSI SLV 初始化参数结构体
 */
void hal_ssislv_quad_init(reg_ssislv_t *p_ssislv, ssislv_init_t *p_init)
{
    // _ioctrl_swapcr_swap8_set;
    // _ioctrl_swapcr_swap9_set;
    // _ioctrl_swapcr_swap10_set;
    // _ioctrl_swapcr_swap11_set;       // 将SPI2管脚复用成 SSISLV1 功能 

    // _ioctrl_swapcr_swap12_set;
    // _ioctrl_swapcr_swap13_set;       // 将I2C2管脚复用成 SSISLV1 功能 
    drv_ssislv_quad_init(p_ssislv, p_init);
}

/**
 *  @brief  SSISLAVE 模块标准模式传输数据函数
 * 
 *  @param p_ssislv  SSI SLV 寄存器结构体
 *  @param p_rec_buff 接收数据
 *  @param p_send_buff 预填发送数据
 *  @param xfer_len 接收数据长度
 *  @note CPU传输方式只支持8bit frame size
 */
void hal_ssislv_standard_xfer(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint8_t *p_send_buff, uint32_t xfer_len)
{
    drv_ssislv_standard_xfer(p_ssislv, p_rec_buff, p_send_buff, xfer_len);
}

/**
 *  @brief  SSISLAVE 模块双线或四线模式接收数据函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_rec_buff 接收数据
 *  @param xfer_len 接收数据长度
 *  @note CPU传输方式只支持8bit frame size
 */
void hal_ssislv_dual_quad_rec(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint32_t xfer_len)
{
    drv_ssislv_dual_quad_rec(p_ssislv, p_rec_buff,xfer_len);
}

/**
 *  @brief  SSISLAVE 模块双线或四线模式发送数据函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_send_buff 发送数据
 *  @param xfer_len 发送数据长度
 */
void hal_ssislv_dual_quad_send(reg_ssislv_t *p_ssislv, uint8_t *p_send_buff, uint32_t xfer_len)
{
    drv_ssislv_dual_quad_send(p_ssislv, p_send_buff, xfer_len);
    drv_ssislv_wait_tx_fifo_empty(p_ssislv);
}

/**
 *  @brief  SSISLAVE 模块标准模式 DMA 方式传输数据函数
 * 
 *  @param p_ssislv  SSI SLV 寄存器结构体
 *  @param p_rec_buff  接收数据
 *  @param p_send_buff 发送数据
 *  @param xfer_len 发送数据长度
 *  @param dma_ch_rx DMA 接收通道
 *  @param dma_ch_tx DMA 发送通道
 *  @return ssislv_status_t 函数运行状态
 */
status_t hal_ssislv_standard_xfer_dma(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint8_t *p_send_buff, uint32_t xfer_len, uint8_t dma_ch_rx, uint8_t dma_ch_tx)
{
      status_t result = STATUS_OK;

    hdma_ssislv_rx.instance = DMAC2;
    hdma_ssislv_rx.init.channel_num = dma_ch_rx;

    // 复位 DMAC
    hal_dmac_deinit(&hdma_ssislv_rx);
    hdma_ssislv_rx.init.dst_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_rx.init.src_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_rx.init.dst_inc = HAL_DMAC_DINC_INC;
    hdma_ssislv_rx.init.src_inc = HAL_DMAC_SINC_NO_CHANGE;
    hdma_ssislv_rx.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_rx.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_rx.init.transfer_type = HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA;
    hdma_ssislv_rx.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SSISLV_RX;
    hdma_ssislv_rx.init.transfer_lli = HAL_DMAC_LLP_DIS;
    hdma_ssislv_rx.init.src_addr = (uint32_t)&p_ssislv->DR;
    hdma_ssislv_rx.init.dst_addr = (uint32_t)p_rec_buff;
    hdma_ssislv_rx.init.transfer_size = xfer_len;

    // 初始化 DMAC 
    result = hal_dmac_init(&hdma_ssislv_rx);
    if(result != STATUS_OK)
    {
        return result;
    }

    // 开启非中断模式DMAC传输
    result = hal_dmac_startpolling(&hdma_ssislv_rx);
    if(result != STATUS_OK)
    {
        return result;
    }

    hdma_ssislv_tx.instance = DMAC2;
    hdma_ssislv_tx.init.channel_num = dma_ch_tx;

    // 复位 DMAC
    hal_dmac_deinit(&hdma_ssislv_tx);
    hdma_ssislv_tx.init.dst_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_tx.init.src_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_tx.init.dst_inc = HAL_DMAC_DINC_NO_CHANGE;
    hdma_ssislv_tx.init.src_inc = HAL_DMAC_SINC_INC;
    hdma_ssislv_tx.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_tx.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_tx.init.transfer_type = HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;
    hdma_ssislv_tx.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SSISLV_TX;
    hdma_ssislv_tx.init.transfer_lli = HAL_DMAC_LLP_DIS;
    hdma_ssislv_tx.init.src_addr = (uint32_t)p_send_buff;
    hdma_ssislv_tx.init.dst_addr = (uint32_t)&p_ssislv->DR;
    hdma_ssislv_tx.init.transfer_size = xfer_len;

    // 初始化 DMAC 
    result = hal_dmac_init(&hdma_ssislv_tx);
    if(result != STATUS_OK)
    {
        return result;
    }
    // 开启非中断模式DMAC传输
    result = hal_dmac_startpolling(&hdma_ssislv_tx);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_rx_dma_config(p_ssislv, 1, 1);
    drv_ssislv_tx_dma_config(p_ssislv, 1, 1);

    // 轮询传输完成 
    result = hal_dmac_pollfortransfer(&hdma_ssislv_tx, 0, SSI_TIMEOUT);
    if(result != STATUS_OK)
    {
        return result;
    }

    // 轮询传输完成 
    result = hal_dmac_pollfortransfer(&hdma_ssislv_rx, 0, SSI_TIMEOUT);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_rx_dma_config(p_ssislv, 0, 1);
    drv_ssislv_tx_dma_config(p_ssislv, 0, 1);

    return STATUS_OK;
}

/**
 *  @brief  SSISLAVE 模块双线或四线模式 DMA 方式接收数据函数
 * 
 *  @param p_ssislv  SSI SLV 寄存器结构体
 *  @param p_rec_buff 接收数据
 *  @param xfer_len 接收数据长度
 *  @param dma_ch_rx DMA 接收通道
 *  @return ssislv_status_t 函数运行状态
 */
status_t hal_ssislv_dual_quad_rec_dma(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff, uint32_t xfer_len, uint8_t dma_ch_rx)
{
    status_t result = STATUS_OK;

    hdma_ssislv_rx.instance = DMAC2;
    hdma_ssislv_rx.init.channel_num = dma_ch_rx;

    // 复位 DMAC
    hal_dmac_deinit(&hdma_ssislv_rx);
    hdma_ssislv_rx.init.dst_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_rx.init.src_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_rx.init.dst_inc = HAL_DMAC_DINC_INC;
    hdma_ssislv_rx.init.src_inc = HAL_DMAC_SINC_NO_CHANGE;
    hdma_ssislv_rx.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_rx.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_rx.init.transfer_type = HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA;
    hdma_ssislv_rx.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SSISLV_RX;
    hdma_ssislv_rx.init.transfer_lli = HAL_DMAC_LLP_DIS;
    hdma_ssislv_rx.init.src_addr = (uint32_t)&p_ssislv->DR;
    hdma_ssislv_rx.init.dst_addr = (uint32_t)p_rec_buff;
    hdma_ssislv_rx.init.transfer_size = xfer_len;

    // 初始化 DMAC 
    result = hal_dmac_init(&hdma_ssislv_rx);
    if(result != STATUS_OK)
    {
        return result;
    }

    // 开启非中断模式DMAC传输
    result = hal_dmac_startpolling(&hdma_ssislv_rx);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_rx_dma_config(p_ssislv, 1, 1);

    // 轮询传输完成 
    result = hal_dmac_pollfortransfer(&hdma_ssislv_rx, 0, SSI_TIMEOUT);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_rx_dma_config(p_ssislv, 0, 1);

    return STATUS_OK;
}

/**
 *  @brief  SSISLAVE 模块双线或四线模式 DMA 方式发送数据函数
 * 
 *  @param p_ssislv  SSI SLV 寄存器结构体
 *  @param p_send_buff 发送数据
 *  @param xfer_len 发送数据长度
 *  @param dma_ch_tx DMA 发送通道
 *  @return ssislv_status_t 函数运行状态
 */
status_t hal_ssislv_dual_quad_send_dma(reg_ssislv_t *p_ssislv, uint8_t *p_send_buff, uint32_t xfer_len, uint8_t dma_ch_tx)
{
    status_t result = STATUS_OK;

    hdma_ssislv_tx.instance = DMAC2;
    hdma_ssislv_tx.init.channel_num = dma_ch_tx;

    // 复位 DMAC
    hal_dmac_deinit(&hdma_ssislv_tx);
    hdma_ssislv_tx.init.dst_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_tx.init.src_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_tx.init.dst_inc = HAL_DMAC_DINC_NO_CHANGE;
    hdma_ssislv_tx.init.src_inc = HAL_DMAC_SINC_INC;
    hdma_ssislv_tx.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_tx.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_tx.init.transfer_type = HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;
    hdma_ssislv_tx.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SSISLV_TX;
    hdma_ssislv_tx.init.transfer_lli = HAL_DMAC_LLP_DIS;
    hdma_ssislv_tx.init.src_addr = (uint32_t)p_send_buff;
    hdma_ssislv_tx.init.dst_addr = (uint32_t)&p_ssislv->DR;
    hdma_ssislv_tx.init.transfer_size = xfer_len;

    // 初始化 DMAC 
    result = hal_dmac_init(&hdma_ssislv_tx);
    if(result != STATUS_OK)
    {
        return result;
    }

    // 开启非中断模式DMAC传输
    result = hal_dmac_startpolling(&hdma_ssislv_tx);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_tx_dma_config(p_ssislv, 1, 1);

    // 轮询传输完成 
    result = hal_dmac_pollfortransfer(&hdma_ssislv_tx, 0, SSI_TIMEOUT);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_tx_dma_config(p_ssislv, 0, 1);

    drv_ssislv_wait_tx_fifo_empty(p_ssislv);

    return STATUS_OK;
}

/**
 *  @brief  SSISLAVE 模块callback 函数
 * 
 */
static void hal_ssislv_dma_callback_handler(void)
{
    uint32_t dma_ch_tmp = hdma_ssislv_rx.init.channel_num;

    memcpy(ssislv_app_data_buff + packet_cnt * dma_lli[0].len, (void *)DMAC2->MIN_CH[dma_ch_tmp].DSTADDR, dma_lli[0].len);
    packet_cnt ++; 
}

/**
 *  @brief  SSISLAVE 模块ping-pong buffer 模式 DMA 方式接收数据函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param p_rec_buff0 接收数据 buffer0
 *  @param p_rec_buff1 接收数据 buffer1
 *  @param buff_len 接收数据长度
 *  @param dma_ch_rx DMA 接收通道
 *  @return ssislv_status_t 函数运行状态
 */
status_t hal_ssislv_rec_dma_pingpong_buffer(reg_ssislv_t *p_ssislv, uint8_t *p_rec_buff0, uint8_t *p_rec_buff1, uint32_t buff_len, uint8_t dma_ch_rx)
{ 
    status_t result = STATUS_OK;

    hdma_ssislv_rx.instance = DMAC2;
    hdma_ssislv_rx.init.channel_num = dma_ch_rx;

    // 复位 DMAC
    hal_dmac_deinit(&hdma_ssislv_rx);
    hdma_ssislv_rx.init.dst_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_rx.init.src_msize = HAL_DMAC_MSIZE_1;
    hdma_ssislv_rx.init.dst_inc = HAL_DMAC_DINC_INC;
    hdma_ssislv_rx.init.src_inc = HAL_DMAC_SINC_NO_CHANGE;
    hdma_ssislv_rx.init.dst_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_rx.init.src_tr_width = HAL_DMAC_TR_WIDTH_8BITS;
    hdma_ssislv_rx.init.transfer_type = HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA;
    hdma_ssislv_rx.init.peripheral_type = HAL_DMAC2_PERIPHERAL_SSISLV_RX;
    hdma_ssislv_rx.init.transfer_lli = HAL_DMAC_LLP_SRC_DST_EN;
    hdma_ssislv_rx.init.src_addr = (uint32_t)&p_ssislv->DR;
    hdma_ssislv_rx.init.dst_addr = (uint32_t)p_rec_buff0;
    hdma_ssislv_rx.init.transfer_size = buff_len;
    hdma_ssislv_rx.dma_raw_callback = NULL;
    hdma_ssislv_rx.dma_block_callback = NULL;
    hdma_ssislv_rx.dma_min_callback = hal_ssislv_dma_callback_handler;

    // 初始化 DMAC 
    result = hal_dmac_init(&hdma_ssislv_rx);
    if(result != STATUS_OK)
    {
        return result;
    }

    DMAC2->CH[dma_ch_rx].CTRL |= (DMAC_LLP_SRC_EN | DMAC_LLP_DST_EN);
    _dmac_int_min_en(DMAC2, dma_ch_rx);
    dma_lli[0].src_addr = (uint32_t)&p_ssislv->DR;
    dma_lli[0].dst_addr = (uint32_t)p_rec_buff0;
    dma_lli[0].next_lli = (uint32_t)&dma_lli[1];
    dma_lli[0].control = DMAC2->CH[dma_ch_rx].CTRL;
    dma_lli[0].len = buff_len;

    dma_lli[1].src_addr = (uint32_t)&p_ssislv->DR;
    dma_lli[1].dst_addr = (uint32_t)p_rec_buff1;
    dma_lli[1].next_lli = (uint32_t)&dma_lli[0];
    dma_lli[1].control = dma_lli[0].control;
    dma_lli[1].len = buff_len;

    drv_dmac_llireginit(hdma_ssislv_rx.instance, hdma_ssislv_rx.init.channel_num, dma_lli);

    // 开启非中断模式DMAC传输
    _dmac_min_interrupt_en(DMAC2, dma_ch_rx);
    _dmac_int_min_en(DMAC2, dma_ch_rx);

    result = hal_dmac_start_it(&hdma_ssislv_rx);
    if(result != STATUS_OK)
    {
        return result;
    }

    drv_ssislv_rx_dma_config(p_ssislv, 1, 1);

    return STATUS_OK;
}

/**
 *  @brief  SSISLAVE 模块ping-pong buffer 模式关闭函数
 * 
 *  @param p_ssislv SSI SLV 寄存器结构体
 *  @param dma_ch_rx DMA 接收通道
 */
void hal_ssislv_dma_pingpong_buffer_disable(reg_ssislv_t *p_ssislv, uint8_t dma_ch_rx)
{
    drv_ssislv_rx_dma_config(p_ssislv, 0, 1);
    _dmac_ch_dis(DMAC2, dma_ch_rx);
   // hdma_ssislv_rx.state = SSISLV_READY;
}
