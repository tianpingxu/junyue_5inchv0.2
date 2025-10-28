/**
 * @file dma_hal.c
 * @author Product application department
 * @brief  DMA 模块硬件抽象层，供应用层调用，仅供参考
 * @version V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "dma_hal.h"
#include "lcd_interface.h"

// 全局变量定义
extern lcd_handle_t lcd_dev;
extern dmac_hdle_t *g_hdma;

// 函数定义

/**
 * @brief DMA 模块复位函数.
 *
 * @param [in] hdmac DMAC句柄指针
 * @return
 * - STATUS_OK;
 * - STATUS_ERROR;
 */
status_t hal_dmac_deinit(dmac_hdle_t *hdma)
{
    /* Check the DMA handle allocation */
    if (hdma == NULL)
    {
        return STATUS_ERROR;
    }

    /* Disable the selected DMA Channelx */
    drv_dmac_ch_disable(hdma->instance, hdma->init.channel_num);
    /* Reset DMA Channel control register */
    drv_dmac_ch_reset(hdma->instance, hdma->init.channel_num);

    /* Clear all flags */
    /* Clear raw interrupt status flag */
    drv_dmac_clearrawstatus(hdma->instance, hdma->init.channel_num);
    /* Clear block interrupt status flag */
    drv_dmac_clearblocktatus(hdma->instance, hdma->init.channel_num);
    /* Clear error interrupt status flag */

    return STATUS_OK;
}

/**
 * @brief  DMA 模块传输参数函数
 *
 * @param [in] hedmac: DMAC句柄指针
 * @param [in] SrcAddress: DMA的源地址
 * @param [in] DstAddress: DMA的目的地址
 * @param [in] DataLength:传输的数据长度
 * @retval 无
 */
static void hal_dmac_setconfig(dmac_hdle_t *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
    dmac_lli_t pdma_lli;

    if (hdma->init.transfer_lli == HAL_DMAC_LLP_DIS)
    {
        /* Configure DMA Channel data length */
        drv_dmac_set_transfer_length(hdma->instance, hdma->init.channel_num, DataLength);

        /* Configure DMA Channel source address */
        drv_dmac_set_transfer_srcaddr(hdma->instance, hdma->init.channel_num, SrcAddress);

        /* Configure DMA Channel destination address */
        drv_dmac_set_transfer_dstaddr(hdma->instance, hdma->init.channel_num, DstAddress);
    }
    else
    {

        pdma_lli.dst_addr = DstAddress;
        pdma_lli.src_addr = SrcAddress;
        pdma_lli.len = DataLength;

        drv_dmac_llireginit(hdma->instance, hdma->init.channel_num, &pdma_lli);
    }

    /*memory to peripheral, dmac controller*/
    if (hdma->init.transfer_type == HAL_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA)
    {
        /*硬件握手*/
        drv_dmac_set_src_soft(hdma->instance, hdma->init.channel_num);
        drv_dmac_set_dst_hard(hdma->instance, hdma->init.channel_num);

        /*目标外围设备*/
        drv_dmac_set_dst_peripheral(hdma->instance, hdma->init.channel_num, hdma->init.peripheral_type);
    }
    /*peripheral to memory, dmac controlller*/
    else if (hdma->init.transfer_type == HAL_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA)
    {
        /*硬件握手*/
        drv_dmac_set_src_hard(hdma->instance, hdma->init.channel_num);
        drv_dmac_set_dst_soft(hdma->instance, hdma->init.channel_num);

        /*目标外围设备*/
        drv_dmac_set_src_peripheral(hdma->instance, hdma->init.channel_num, hdma->init.peripheral_type);
    }
    /*memory to memory, dmac controller*/
    else if (hdma->init.transfer_type == HAL_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA)
    {
        /*硬件握手*/
        drv_dmac_set_src_hard(hdma->instance, hdma->init.channel_num);
        drv_dmac_set_dst_hard(hdma->instance, hdma->init.channel_num);
    }
    else
    {
        //
    }
}
/**
 * @brief DMA 模块初始化函数
 *
 * @param [in] hdmac: DMAC实例化
 * @return
 */
status_t hal_dmac_init(dmac_hdle_t *hdma)
{
    /* Check the DMA handle allocation */
    if (hdma == NULL)
    {
        return STATUS_ERROR;
    }

    if (hdma->init.channel_num > HAL_DMAC_CHANNEL_7)
    {
        return STATUS_ERROR;
    }

    /* Clear SRC_MSIZE, DEST_MSIZE, SINC, DINC, SRC_TR_WIDTH, DST_TR_WIDTH bits */
    drv_dmac_ch_reset(hdma->instance, hdma->init.channel_num);

    drv_dmac_ctrlregconfig(hdma->instance,
                           hdma->init.channel_num,
                           hdma->init.transfer_type,
                           hdma->init.src_msize,
                           hdma->init.dst_msize,
                           hdma->init.src_inc,
                           hdma->init.dst_inc,
                           hdma->init.src_tr_width,
                           hdma->init.dst_tr_width);

    hal_dmac_setconfig(hdma, hdma->init.src_addr, hdma->init.dst_addr, hdma->init.transfer_size);
    g_hdma = hdma;
    return STATUS_OK;
}

/**
 * @brief DMA 模块开启非中断模式传输函数
 *
 * @param [in] hedmac: DMAC实例化
 * @return
 */
status_t hal_dmac_startpolling(dmac_hdle_t *hdma)
{
    /*Enable DMAC*/
    drv_dmac_en(hdma->instance);

    /* Disable the selected DMA Channelx */
    drv_dmac_ch_disable(hdma->instance, hdma->init.channel_num);

    /*采用查询的方式*/
    drv_dmac_distfrit(hdma->instance, hdma->init.channel_num);
    //_dmac_raw_interrupt_dis(hdma->init.channel_num);

    /* Enable the selected DMA Channelx */
    drv_dmac_ch_enable(hdma->instance, hdma->init.channel_num);

    return STATUS_OK;
}

/**
 * @brief DMA 模块轮询普通模式传输完成函数
 *
 * @param [in] hdmac EDMAC句柄指针
 * @param [in] CompleteLevel DMA完成级别
 * @param [in] Timeout 超时时间
 * @return
 */
status_t hal_dmac_pollfortransfer(dmac_hdle_t *hdma, uint32_t CompleteLevel, uint32_t Timeout)
{
    uint32_t tickstart = 0x00;
    volatile BitActionTypeDef raw_status;

    /* Transfer Complete flag */
    raw_status = drv_dmac_getrawstatus(hdma->instance, hdma->init.channel_num);

    /* Get tick */
    // tickstart = HAL_GetTick();

    while (raw_status == BIT_RESET)
    {
        raw_status = drv_dmac_getrawstatus(hdma->instance, hdma->init.channel_num);
    }

    /* Clear the transfer complete flag */
    drv_dmac_clearrawstatus(hdma->instance, hdma->init.channel_num);

    return STATUS_OK;
}

static uint32_t hal_dmac_gettick(void)
{
    static __O uint32_t ret = 0;
    static __O uint32_t cnt = 0;

    cnt++;
    if (cnt > 0x10000)
    {
        cnt = 0;
        ret++;
    }

    return ret;
}
/**
 * @brief DMA 模块轮询中断模式传输完成函数.
 *
 * @param [in] hdmac EDMAC句柄指针
 * @param [in] CompleteLevel DMA完成级别
 * @param [in] Timeout 超时时间
 * @return
 * - STATUS_OK;
 * - STATUS_ERROR;
 */
status_t hal_dmac_pollfortransfer_it(dmac_hdle_t *hdma, uint32_t CompleteLevel, uint32_t Timeout)
{
    uint32_t tickstart = 0x00;
    uint8_t raw_status;
    uint8_t dmac_flag = 0;
    /* Transfer Complete flag */
    raw_status = dmac_flag;

    /* Get tick */
    tickstart = hal_dmac_gettick();

    while ((raw_status & (1 << hdma->init.channel_num)) != (1 << hdma->init.channel_num))
    {
        raw_status = dmac_flag;

        /* Check for the Timeout */
        if (Timeout != MAX_DELAY)
        {
            if ((Timeout == 0) || ((hal_dmac_gettick() - tickstart) > Timeout))
            {

                /* Process Unlocked */

                return STATUS_TIMEOUT;
            }
        }
    }

    /* Clear the transfer complete flag */
    dmac_flag &= ~(1 << hdma->init.channel_num);

    /* The selected Channelx EN bit is cleared (DMA is disabled and
    all transfers are complete) */

    /* Process unlocked */

    return STATUS_OK;
}

/**
 * @brief DMA 模块中止DMA传输函数
 *
 * @param [in] hdmac DMAC句柄指针
 * @return
 */
void hal_dmac_clearrawstatus(dmac_hdle_t *hdma, uint32_t ch)
{
    drv_dmac_clearrawstatus(hdma->instance, ch);
}

/**
 * @brief DMAC 模块使能函数
 *
 * @param [in] hdmac DMAC句柄指针
 * @return
 */
void hal_dmac_enable(dmac_hdle_t *hdma)
{
    drv_dmac_en(hdma->instance);
}

/**
 * @brief DMA 模块中断处理函数
 * @param
 */
void hal_dmac_irqhandler(void)
{
    if (lcd_dev.lcd_itf_type == LCD_SPI)
    {
        hal_spi_lli_irqhandler();
    }
    else if (lcd_dev.lcd_itf_type == LCD_QSPI)
    {
    }
}

/**
 * @brief DMA 模块开启中断模式DMA传输函数.
 *
 * @param [in] hedmac DMAC句柄指针
 * @param [in] SrcAddress DMA的源地址
 * @param [in] DstAddress DMA的目的地址
 * @param [in] DataLength 传输的数据长度
 * @return
 * - STATUS_OK;
 * - STATUS_ERROR;
 */
status_t hal_dmac_start_it(dmac_hdle_t *hdma)
{

    /*Enable DMAC*/
    drv_dmac_en(hdma->instance);

    /* Disable the selected DMA Channelx */
    drv_dmac_ch_disable(hdma->instance, hdma->init.channel_num);

    /* Enable the transfer complete flag*/
    drv_dmac_set_raw_inten(hdma->instance, hdma->init.channel_num);

    /*DMAC interrupt enable*/
    drv_dmac_int_en(hdma->instance, hdma->init.channel_num);

    /* Enable the selected DMA Channelx */
    drv_dmac_ch_enable(hdma->instance, hdma->init.channel_num);

    return STATUS_OK;
}