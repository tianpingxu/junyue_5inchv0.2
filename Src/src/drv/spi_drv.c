/**
 * @file spi_drv.c
 * @author Product application department
 * @brief  SPI 模块驱动层
 * @version V1.0
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件定义
#include "spi_drv.h"

// 函数定义
/**
 * @brief SPI 模块管脚切换为SPI功能函数
 * @param pspi 指向spi_typedef_t的指针
 */
void drv_spi_funcswap(reg_spi_t *pspi)
{
    if (pspi == SPI1)
    {
        _ioctrl_swapcr5_swap28_set;
        _ioctrl_swapcr5_swap29_set;
        _ioctrl_swapcr5_swap30_set;
        _ioctrl_swapcr5_swap31_set;
    }
    else if (pspi == SPI2)
    {
    }
    else if (pspi == SPI3)
    {
        _ioctrl_swapcr8_swap8_set;
        _ioctrl_swapcr8_swap9_clr;
        _ioctrl_swapcr8_swap10_clr;
        _ioctrl_swapcr8_swap11_clr;		
    }

}

/**
 * @brief SPI 模块恢复SPI为默认设置函数
 * @param pspi 指向spi_typedef_t的指针
 */
void drv_spi_deinit(reg_spi_t *pspi)
{
    pspi->CR1 = 0x00;
    pspi->CR2 = 0x00;
    pspi->RXFTOCTR = 0x00;
    pspi->TXFTOCTR = 0x00;
    pspi->RXFCR = 0x00;
    pspi->TXFCR = 0x00;
    pspi->ICR = 0x00;
    pspi->DMACR = 0x00;
}

/**
 * @brief SPI 模块初始化函数
 * @param pspi 指向spi_typedef_t的指针
 * @param init 指向spi_init_t的指针
 * @return status_t 初始化结果
 */
status_t drv_spi_init(reg_spi_t *pspi, volatile spi_init_t *init)
{
    uint8_t reg = 0;
    uint8_t tmp = 0;

    _spi_dis(pspi);
    _spi_dis_it(pspi);

    /*CR0*/
    if (init->OutputMode == SPI_WIRED_OR_MODE_OPEN_DRAIN)
    {
        tmp = SPI_WIRED_OR_MODE_OPEN_DRAIN;
    }
    reg = tmp;

    /*CR1*/
    if (init->Mode == SPI_MASTER)
    {
        reg |= SPI_MASTER;

        /*配置管脚的方向*/
#if 1
        _spi_set_cs_bit(pspi);
        _spi_set_clk_bit(pspi);
        _spi_set_mosi_bit(pspi);
        _spi_pin_dir_input(pspi, SPI_PIN_MISO);
        _spi_pin_dir_output(pspi, SPI_PIN_CS);
        _spi_pin_dir_output(pspi, SPI_PIN_CLK);
        _spi_pin_dir_output(pspi, SPI_PIN_MOSI);
#endif
    }
    else
    {
        _spi_pin_dir_input(pspi, SPI_PIN_CS);
        _spi_pin_dir_input(pspi, SPI_PIN_CLK);
        _spi_pin_dir_input(pspi, SPI_PIN_MOSI);
        _spi_pin_dir_output(pspi, SPI_PIN_MISO);
    }

    if (init->Cpol == SPI_CPOL_HIGH)
    {
        reg |= SPI_CPOL_HIGH;
    }

    if (init->Cpha == SPI_CPHA_2EDGE)
    {
        reg |= SPI_CPHA_2EDGE;
    }

    if (init->Ssoe == ENABLE)
    {
        reg |= SPI_EN_SSOE;
    }

    if (init->FirstBit == SPI_FIRSTBIT_LSB)
    {
        reg |= SPI_FIRSTBIT_LSB;
    }

    pspi->CR1 = reg;

    reg = 0;
    /*CR2*/
    if (init->GuradTimeEn == ENABLE)
    {
        reg = init->GuardTime;
        reg &= 0x3f;
        reg <<= 2;
        _spi_en_guard_time(pspi);
    }
    else
    {
        _spi_dis_guard_time(pspi);
    }

    /*CR2*/
    if (init->DozeMode == DISABLE)
    {
        reg |= SPI_DOZE_INACTIVE_MODE;
    }

    if (init->Spc0 == ENABLE)
    {
        reg |= SPI_SPC0_BIDIR_MODE;
    }

    pspi->CR2 = reg;

    /*波持率*/
    if (init->Mode == SPI_MASTER)
    {
        reg = 0;
        init->BaudratePreselectionBits &= 0x07;
        reg = init->BaudratePreselectionBits;
        reg <<= 4;
        init->BaudrateBits &= 0x07;
        reg |= init->BaudrateBits;
        pspi->BR = reg;
    }

    reg = 0;
    if (init->Mode == SPI_SLAVE)
    {
        /*高速模式:只针对从机*/
        if (init->SlaveHighSpeedEn == ENABLE)
        {
            reg |= SPI_EN_HIGH_SPEED;
        }
    }

    /*上拉*/
    if (init->Pullup == ENABLE)
    {
        reg |= SPI_EN_PULLUP_DEVICE;
    }

    /*驱动能力*/
    if (init->ReducedDriveCap == ENABLE)
    {
        reg |= SPI_REDUCE_CAP;
    }

    pspi->PURD = reg;

    /*清队fifo*/
    _spi_clr_tx_fifo(pspi);
    _spi_clr_rx_fifo(pspi);

#if 1
    if (init->FifoInit.rx_fifo_en == ENABLE)
    {
        _spi_set_rx_fifo_threshold(pspi, init->FifoInit.rx_fifo_threshold);
        _spi_set_rx_fifo_time_cnt(pspi, init->FifoInit.rx_fifo_timeout_cnt);
    }
    else
    {
        /*FIFO深度为1*/
    }

    if (init->FifoInit.tx_fifo_en == ENABLE)
    {
        _spi_set_tx_fifo_threshold(pspi, init->FifoInit.tx_fifo_threshold);
        _spi_set_tx_fifo_time_cnt(pspi, init->FifoInit.tx_fifo_timeout_cnt);
    }
    else
    {
        /*深度为1*/
    }
#endif

    /**/
    _spi_en(pspi);

    return STATUS_OK;
}

/**
 * @brief SPI 模块使能函数
 * @param pspi 指向spi_typedef_t的指针
 */
void drv_spi_en(reg_spi_t *pspi)
{
    _spi_en(pspi);
}

/**
 * @brief SPI 模块禁止函数
 * @param pspi 指向spi_typedef_t的指针
 */
void drv_spi_dis(reg_spi_t *pspi)
{
    _spi_dis(pspi);
}

/**
 * @brief SPI 模块使能或禁止函数
 * @param pspi 指向spi_typedef_t的指针
 * @param newstate 新的状态
 * -ENABLE
 * -DISABLE
 */
void drv_spi_cmd(reg_spi_t *pspi, functionalstate_t newstate)
{
    if (newstate == ENABLE)
        _spi_en(pspi);
    else
        _spi_dis(pspi);
}
/**
 * @brief SPI 模块设置设置frame长度
 * @param pspi 指向spi_typedef_t的指针
 * @param value 长度值
 */
void drv_spi_set_frame_size(reg_spi_t *pspi, uint8_t value)
{
    _spi_set_frame_size(pspi, value);
}

/**
 * @brief SPI 模块清除RXFIFO函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void drv_spi_clr_rx_fifo(volatile reg_spi_t *hspi)
{
    _spi_clr_rx_fifo(hspi);
}

/**
 * @brief SPI 模块清除TXFIFO函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void drv_spi_clr_tx_fifo(volatile reg_spi_t *hspi)
{
    _spi_clr_tx_fifo(hspi);
}

/**
 * @brief SPI 模块禁止中断函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void drv_spi_dis_it(volatile reg_spi_t *hspi)
{
    _spi_dis_it(hspi);
}

/**
 * @brief SPI 模块使能中断函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void drv_spi_en_it(volatile reg_spi_t *hspi)
{
    _spi_en_it(hspi);
}

/**
 * @brief SPI 模块使能TX DMA函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void drv_spi_en_tx_dma(volatile reg_spi_t *hspi)
{
    _spi_en_tx_dma(hspi);
}

/**
 * @brief SPI 模块使能RX DMA函数
 * @param hspi  指向SPI_HandleTypeDef结构体的指针
 */
void drv_spi_en_rx_dma(volatile reg_spi_t *hspi)
{
    _spi_en_rx_dma(hspi);
}

/**
 * @brief SPI 模块使能中断函数
 * @param pspi 指向spi_typedef_t的指针
 */
void drv_spi_iten(reg_spi_t *pspi)
{
}

/**
 * @brief SPI 模块主机查询方式发送一字节函数
 * @param pspi   指向spi_typedef_t的指针
 * @param tosend 代发送数据
 * @return status_t 发送结果
 */
status_t drv_spi_transmitbyte(reg_spi_t *pspi, uint8_t tosend)
{
    while (pspi->SR & SPI_FLAG_TX_FIFO_FULL)
        ;

    pspi->DR = tosend;

    while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
        ;

    _spi_clr_tx_fifo(pspi);

    return STATUS_OK;
}

/**
 * @brief SPI 模块主机查询方式收取一字节函数
 * @param pspi  指向spi_typedef_t的指针
 * @param *rx   收取数据指针
 * @return status_t 接收结果
 */
status_t drv_spi_receivebyte(reg_spi_t *pspi, uint8_t *rx)
{
    _spi_clr_tx_fifo(pspi);

    while (pspi->SR & SPI_FLAG_TX_FIFO_FULL)
        ;

    pspi->DR = 0XFF;

    while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
        ;

    _spi_clr_tx_fifo(pspi);

    while (pspi->SR & SPI_FLAG_RX_FIFO_EMPTY)
        ;

    *rx = pspi->DR;

    _spi_clr_rx_fifo(pspi);

    return STATUS_OK;
}

/**
 * @brief SPI 模块主机查询方式发送一字节函数
 * @param pspi 指向spi_typedef_t的指针
 * @param pbuf 数据指针
 * @param size 发送数据长度
 * @return status_t 操作结果
 */
status_t drv_spi_transmitbytes(reg_spi_t *pspi,
                               uint8_t *pbuf,
                               uint32_t size)
{
    uint32_t loop = 0;

    for (loop = 0; loop < size; loop++)
    {
        while (pspi->SR & SPI_FLAG_TX_FIFO_FULL)
            ;

        pspi->DR = *(pbuf + loop);

        while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
            ;
    }

    _spi_clr_tx_fifo(pspi);
    _spi_clr_rx_fifo(pspi);

    return STATUS_OK;
}

/**
 * @brief SPI 模块主机查询方式接收数据函数
 * @param pspi 指向spi_typedef_t的指针
 * @param pbuf 数据指针
 * @param size 数据长度
 * @return status_t 操作结果
 */
status_t drv_spi_receivebytes(reg_spi_t *pspi, uint8_t *pbuf, uint32_t len)
{
    uint32_t loop = 0;

    for (loop = 0; loop < len; loop++)
    {
#if 1
        while (pspi->SR & SPI_FLAG_TX_FIFO_FULL)
            ;

        pspi->DR = 0XFF;
#endif

        while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
            ;

        _spi_clr_tx_fifo(pspi);

        while (pspi->SR & SPI_FLAG_RX_FIFO_EMPTY)
            ;

        *(pbuf + loop) = pspi->DR;

        _spi_clr_rx_fifo(pspi);
    }

    _spi_clr_rx_fifo(pspi);

    return STATUS_OK;
}

/**
 * @brief SPI 模块从机查询方式接收数据函数
 * @param  pspi 指向spi_typedef_t的指针
 * @param  pbuf 数据指针
 * @param  timeout 超时时间
 * -0   无限等待
 * -非0 超时退出
 * @return status_t 操作结果
 */
status_t drv_spi_slavereceivebyte(reg_spi_t *pspi,
                                  uint8_t *rx,
                                  uint32_t timeout)
{
    if (timeout == 0)
    {
        while (pspi->SR & SPI_FLAG_RX_FIFO_EMPTY)
            ;

        *rx = pspi->DR;

        _spi_clr_rx_fifo(pspi);
    }
    else
    {
        do
        {
            if (timeout == 0)
            {
                return STATUS_TIMEOUT;
            }

            timeout--;
        } while ((pspi->SR & SPI_FLAG_RX_FIFO_EMPTY));
    }

    *rx = pspi->DR;

    return STATUS_OK;
}

/**
 * @brief SPI 模块从机查询方式接收数据函数.
 * @param pspi 指向spi_typedef_t的指针
 * @param pbuf 数据指针;
 * @param len  数据长度;
 * @param timeout 超时时间;
 * -0   无限等待
 * -非0 超时退出
 * @return ref status_t 操作结果
 */
status_t drv_spi_slavereceivebytes(reg_spi_t *pspi,
                                   uint8_t *pbuf,
                                   uint32_t len,
                                   uint32_t timeout)
{
    uint32_t loop = 0;
    uint32_t tmptimeout;

    if (timeout == 0)
    {
        for (loop = 0; loop < len; loop++)
        {
            while (pspi->SR & SPI_FLAG_RX_FIFO_EMPTY)
                ;

            *(pbuf + loop) = pspi->DR;

            _spi_clr_rx_fifo(pspi);
        }
    }
    else
    {
        tmptimeout = timeout;

        for (loop = 0; loop < len; loop++)
        {
            do
            {
                if (tmptimeout == 0)
                {
                    return STATUS_TIMEOUT;
                }

                tmptimeout--;
            } while ((pspi->SR & SPI_FLAG_RX_FIFO_EMPTY));

            *(pbuf + loop) = pspi->DR;
            tmptimeout = timeout;
        }
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块从机查询方式发送数据函数
 * @param pspi 指向spi_typedef_t的指针
 * @param pbuf 数据指针
 * @param timeout 超时时间
 * -0   无限等待
 * -非0 超时退出
 * @return status_t 操作结果
 */
status_t drv_spi_slavetransmitbyte(reg_spi_t *pspi, uint8_t tosend, uint32_t timeout)
{
    uint32_t tmptimeout = timeout;

    if (timeout == 0)
    {
        while (pspi->SR & SPI_FLAG_TX_FIFO_FULL)
            ;

        pspi->DR = tosend;

        while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
            ;
    }
    else
    {
        do
        {
            if (tmptimeout == 0)
            {
                return STATUS_TIMEOUT;
            }

            tmptimeout--;
        } while ((pspi->SR & SPI_FLAG_TX_FIFO_FULL));

        pspi->DR = tosend;

        tmptimeout = timeout;

        do
        {
            if (tmptimeout == 0)
            {
                return STATUS_TIMEOUT;
            }

            tmptimeout--;
        } while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH);
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块从机查询方式发送多个数据函数
 * @param pspi 指向spi_typedef_t的指针
 * @param pbuf 数据指针
 * @param len  数据长度
 * @param timeout 超时时间
 * -0   无限等待
 * -非0 超时退出
 * @return ref status_t 操作结果
 */
status_t drv_spi_slavetransmitbytes(reg_spi_t *pspi, uint8_t *pbuf, uint32_t len, uint32_t timeout)
{
    uint32_t loop = 0;
    uint32_t tmptimeout = timeout;

    if (timeout == 0)
    {
        for (loop = 0; loop < len; loop++)
        {
            pspi->DR = *(pbuf + loop);

            while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH)
                ;
        }
    }
    else
    {
        for (loop = 0; loop < len; loop++)
        {
            tmptimeout = timeout;
            pspi->DR = *(pbuf + loop);

            do
            {
                if (tmptimeout == 0)
                {
                    return STATUS_TIMEOUT;
                }

                tmptimeout--;
            } while ((pspi->SR & SPI_FLAG_FINISH) != SPI_FLAG_FINISH);
        }
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块设置数据寄存器值函数
 * @param pspi 指向spi_typedef_t的指针
 * @param val  数据
 */
void drv_spi_setdr(reg_spi_t *pspi, uint8_t val)
{
    pspi->DR = val;
}

/**
 * @brief SPI 模块获取数据寄存器值函数
 * @param  pspi 指向spi_typedef_t的指针
 * @param pval 数据指针
 */
void drv_spi_getdr(reg_spi_t *pspi, uint8_t *pval)
{
    *pval = pspi->DR;
}

/**
 * @brief SPI 模模块取标志状态函数
 * @param  pspi 指向spi_typedef_t的指针
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
 * @param pflag 标志状态
 *- SET
 *- REST
 * @return status_t 当前状态
 */
status_t drv_spi_getflag(reg_spi_t *pspi, spi_flagindex_t flagindex, flagstatus_t *pflag)
{

    if (flagindex <= SPI_FLAG_INDEX_SPIF)
    {
        if (pspi->SR & (1 << flagindex))
            *pflag = SET;
        else
            *pflag = RESET;
    }
    else if ((flagindex >= SPI_FLAG_INDEX_RXFSER) && (flagindex <= SPI_FLAG_INDEX_TXFTO))
    {
        if (pspi->SRH & (1 << (flagindex - 8)))
            *pflag = SET;
        else
            *pflag = RESET;
    }
    else
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块清除标志状态函数
 * @param  pspi 指向spi_typedef_t的指针
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
status_t drv_spi_clrflag(reg_spi_t *pspi, spi_flagindex_t flagindex)
{
    uint8_t TmpStatus = 0;

    if (flagindex <= SPI_FLAG_INDEX_SPIF)
    {
        TmpStatus = pspi->SR;
        switch (flagindex)
        {
        case SPI_FLAG_INDEX_FLOST:
        case SPI_FLAG_INDEX_EOTF:
        {
            pspi->SR |= (1 << flagindex);
            break;
        }
        default:
            break;
        }
    }
    else if ((flagindex >= SPI_FLAG_INDEX_RXFSER) && (flagindex <= SPI_FLAG_INDEX_TXFTO))
    {
        TmpStatus = pspi->SRH;
        TmpStatus = TmpStatus;
        flagindex -= 8;
        switch (flagindex)
        {
        case SPI_FLAG_INDEX_RXFUDF:
        case SPI_FLAG_INDEX_RXFOVFM:
        case SPI_FLAG_INDEX_TXFUDF:
        case SPI_FLAG_INDEX_TXFOVFM:
        case SPI_FLAG_INDEX_TXFTO:
        {
            pspi->SR |= (1 << flagindex);
            break;
        }
        default:
            break;
        }
    }
    else
    {
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

/**
 * @brief SPI 模块获取标志状态函数
 * @param  pspi 指向spi_typedef_t的指针
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
status_t drv_spi_waitonflagtimeout(reg_spi_t *pspi,
                                   spi_flagindex_t index,
                                   flagstatus_t status,
                                   uint32_t timeout)
{
    flagstatus_t tmp_flag = RESET;

    if (timeout == 0)
    {
        do
        {
            drv_spi_getflag(pspi, index, &tmp_flag);
        } while (tmp_flag != status);
    }
    else
    {
        if (status == SET)
        {
            drv_spi_getflag(pspi, index, &tmp_flag);

            while (tmp_flag != SET)
            {
                timeout--;

                if (timeout == 0)
                {
                    return STATUS_TIMEOUT;
                }

                drv_spi_getflag(pspi, index, &tmp_flag);
            }
        }
        else if (status == RESET)
        {
            drv_spi_getflag(pspi, index, &tmp_flag);

            while (tmp_flag != RESET)
            {
                timeout--;

                if (timeout == 0)
                {
                    return STATUS_TIMEOUT;
                }

                drv_spi_getflag(pspi, index, &tmp_flag);
            }
        }
    }

    return STATUS_OK;
}

/**
 * @brief SPI 模块管脚用作GPIO初始状态函数
 * @param pspi pspi 指向spi_typedef_t结构体的指针
 * @param init init 指向gpio_init_t结构体的指针
 * @return status_t 当前状态
 */
status_t drv_spi_gpioinit(reg_spi_t *pspi, gpio_init_t *init)
{
    /*切换SPI引脚复用*/
    drv_spi_funcswap(pspi);

    /*方向*/
    if (init->Dir == GPIO_DIR_OUT)
    {
        _spi_pin_dir_output(pspi, init->Pin);

#if 0

        /*影响全部的4个管脚*/
        if(init->OutputMode == GPIO_OUTPUT_MODE_CMOS)
        {
            _spi_pin_output_cmos(pspi);
        }
        else if(init->OutputMode == GPIO_OUTPUT_MODE_CMOS)
        {
            _spi_pin_output_opendrain(pspi);
        }
        else
        {
            return(STATUS_ERROR);
        }

#endif
    }
    else if (init->Dir == GPIO_DIR_IN)
    {
        _spi_pin_dir_input(pspi, init->Pin);
    }
    else if (init->Dir == GPIo_DIR_TRIGATE)
    {
        /*用作输主之后IOCONTROL部分禁止输入*/
        _spi_pin_dir_input(pspi, init->Pin);
        /**/
    }

    /*上下拉影响全部4个管脚*/

    /**/
    return STATUS_OK;
}

/**
 * @brief SPI 模块管脚恢复初始设置函数
 * @param pspi pspi 指向spi_typedef_t结构体的指针
 * @param pin  pin  SPI的管脚
 *- SPI_PIN_CS
 *- SPI_PIN_CLK
 *- SPI_PIN_MOSI
 *- SPI_PIN_MISO
 */
void drv_spi_gpiodeinit(reg_spi_t *pspi, uint8_t pin)
{
}

/**
 * @brief SPI 模块管脚输出指定电平函数
 * @param pspi pspi 指向spi_typedef_t结构体的指针
 * @param init pin  SPI的管脚
 *- SPI_PIN_CS
 *- SPI_PIN_CLK
 *- SPI_PIN_MOSI
 *- SPI_PIN_MISO
 */
void drv_spi_writepin(reg_spi_t *pspi, uint8_t pin, gpio_pinstate_t state)
{
    if (state == RESET)
    {
        _spi_reset_pin_bit(pspi, pin);
    }
    else
    {
        _spi_set_pin_bit(pspi, pin);
    }
}

/**
 * @brief SPI 模块获取管脚电平函数
 * @param pspi pspi 指向spi_typedef_t结构体的指针
 * @param init pin  SPI的管脚
 *- SPI_PIN_CS
 *- SPI_PIN_CLK
 *- SPI_PIN_MOSI
 *- SPI_PIN_MISO
 * @return gpio_pinstate_t_t 管脚电平状态
 */
gpio_pinstate_t drv_spi_readpin(reg_spi_t *pspi, uint8_t pin)
{
    if (_spi_get_pin_bit(pspi, pin))
    {
        return GPIO_HIGH;
    }
    else
    {
        return GPIO_LOW;
    }
}
