/**
 * @file i2s_drv.c
 * @author Product Application Department
 * @brief  I2S 模块驱动层
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */


// 头文件包含
#include "i2s_drv.h"
#include "cpm_drv.h"

// 函数定义
/**
 * @brief I2S 模块管脚切换功能函数
 *
 * @param pi2s I2S实例化
 */
void drv_i2s_funcswap(reg_i2s_t *pi2s)
{
    // ATT: 功能切换方式已变更，此处保留，无内容实体。具体功能见 pinswap_drv.h
}

/**
 * @brief I2S 模块初始化设置函数
 *
 * @param pi2s I2S寄存器实例化
 * @param pinit I2S初始化实例化
 * @return status_t
 */
status_t drv_i2s_init(reg_i2s_t *pi2s, i2s_init_t *pinit)
{
    uint32_t tmp_val = 0x00;

    /*引脚swap*/
    drv_i2s_funcswap(pi2s);

    /*分频*/
    tmp_val = (CPM->PCDIVR4);
    tmp_val &= 0x0000ffff;
    tmp_val |= (pinit->SclkPrescaler << 24) | (pinit->MclkPrescaler << 16);
    (CPM->PCDIVR4) = tmp_val;
    (CPM->CDIVUPDR) |= CPM_CDIVUPDR_PERIPHERAL_DIV_UPDATE;

    pi2s->CDR = pinit->LrcPrescaler;

    if (pinit->Mode == I2S_MODE_PLAY)
    {
        pi2s->CR =  I2S_CR_SCLKOBE | I2S_CR_SDOBE | I2S_CR_TXFWL(2) | I2S_CR_RXFWL(2); // 0x00002230;
    }
    else if (pinit->Mode == I2S_MODE_RECORD)
    {
        // pi2s->CR = 0x00002214;
        pi2s->CR =  I2S_CR_SCLKOBE | I2S_CR_TXFWL(2) | I2S_CR_RXFWL(2); // 0x00002210;
    }
    else
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/**
 * @brief I2S 模块的发送函数
 *
 * @param pi2s I2S寄存器实例化
 * @param pBuf I2S发送数据指针
 * @param Size I2S发送数据长度
 * @param timeout I2S发送超时设定
 * @return status_t
 */
status_t drv_i2s_transmit(reg_i2s_t *pi2s, uint8_t *pBuf, uint32_t Size, uint32_t timeout)
{
    uint32_t i = 0;
    volatile uint32_t temp = 0;
    pi2s->TXDR = *(volatile uint32_t *)(&pBuf[i]);
    pi2s->TXDR = *(volatile uint32_t *)(&pBuf[i + 0x4]);
    pi2s->CR |= I2S_CR_TXE;

    for (i = 8; i < Size; i = i + 4)
    {
        do
        {
            temp = pi2s->SR;
        } while (!(temp & 0x00000001));

        pi2s->TXDR = *(volatile uint32_t *)(&pBuf[i]);
    }
    while ((pi2s->SR & I2S_SR_TXBE) == 0)
        ;
    while ((pi2s->ESR & I2S_ESR_TXAU) == 0)
        ;
    pi2s->CR &= ~I2S_CR_TXE;
    return STATUS_OK;
}

/**
 * @brief I2S 模块的接收函数
 *
 * @param pi2s I2S寄存器实例化
 * @param pBuf I2S接收数据指针
 * @param Size I2S接收数据长度
 * @param timeout I2S接收超时设定
 * @return status_t
 */
status_t drv_i2s_receive(reg_i2s_t *pi2s, uint8_t *pBuf, uint32_t Size, uint32_t timeout)
{
    uint32_t i = 0;
    volatile uint32_t temp = 0;
    pi2s->CR |= I2S_CR_RXE;
    for (i = 0; i < Size; i = i + 4)
    {
        do
        {
            temp = pi2s->SR;
        } while (temp & 0x00000010);
        *(volatile uint32_t *)(&pBuf[i]) = pi2s->RXDR;
    }
    while ((pi2s->SR & I2S_SR_RXBE) == 0)
        ;
    pi2s->CR &= ~I2S_CR_RXE;
    return STATUS_OK;
}

/**
 * @brief I2S 模块DMA TX使能函数
 *
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_dmatxen(reg_i2s_t *pi2s)
{
    pi2s->DMACR |= I2S_DMACR_TXEN;
}

/**
 * @brief I2S 模块DMA TX禁止函数
 * 
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_dmatxdis(reg_i2s_t *pi2s)
{
    pi2s->DMACR &= ~I2S_DMACR_TXEN;
}

/**
 * @brief I2S 模块DMA RX使能函数
 *
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_dmarxen(reg_i2s_t *pi2s)
{
    pi2s->DMACR |= I2S_DMACR_RXEN;
}

/**
 * @brief I2S 模块DMA TX计数函数
 *
 * @param pi2s I2S寄存器实例化
 * @param cnt 计数
 */
void drv_i2s_dmarxcnt(reg_i2s_t *pi2s, uint8_t cnt)
{
    pi2s->DMACR |= I2S_DMACR_RXCNT(cnt);
}

/**
 * @brief I2S 模块发送使能函数
 *
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_txen(reg_i2s_t *pi2s)
{
    pi2s->CR |= I2S_CR_TXE;
}

/**
 * @brief I2S 模块发送禁止函数
 *
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_txdis(reg_i2s_t *pi2s)
{
    pi2s->CR &= ~I2S_CR_TXE;
}

/**
 * @brief I2S 模块接收使能函数
 *
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_rxen(reg_i2s_t *pi2s)
{
    pi2s->CR |= I2S_CR_RXE;
}

/**
 * @brief I2S 模块接收禁止函数
 *
 * @param pi2s I2S寄存器实例化
 */
void drv_i2s_rxdis(reg_i2s_t *pi2s)
{
    pi2s->CR &= ~I2S_CR_RXE;
}

