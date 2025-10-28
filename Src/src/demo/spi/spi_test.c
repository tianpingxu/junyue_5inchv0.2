/**
 * @file spi_test.c
 * @author Product application department
 * @brief  SPI 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup SPI SPI模块
 * @ingroup Peripherals
 * @{
 */

// 头文件定义
#include "spi_test.h"

// 全局变量定义
volatile spi_handletypedef_t g_spi_handle;
uint8_t g_spi_txbuf[128];
uint8_t g_spi_rxbuf[128];

// 一次只能运行一个demo TEST
#define SPI_MASTER_DEV_TEST 1
#define SPI_SLAVE_DEV_TEST 0

#define SPI_MASTER_DEV_IT_TEST 0
#define SPI_SLAVE_DEV_IT_TEST 0

#define SPI_MASTER_DEV_DMA_TEST 0
#define SPI_SLAVE_DEV_DMA_TEST 0

// 函数定义

/**
 * @brief SPI 模块Master初始化函数
 * @param pspi 指向spi_typedef_t结构体的指针
 */
static void spi_master_init(reg_spi_t *pspi)
{
    g_spi_handle.Instance = pspi;
    hal_spi_dis(&g_spi_handle);

    /*CS独立控制*/
    g_spi_handle.Init.Ssoe = DISABLE;
    g_spi_handle.Init.Mode = SPI_MASTER;
    g_spi_handle.Init.OutputMode = GPIO_OUTPUT_MODE_CMOS;
    g_spi_handle.Init.Cpol = SPI_CPOL_HIGH;
    g_spi_handle.Init.Cpha = SPI_CPHA_2EDGE;
    g_spi_handle.Init.Ssoe = DISABLE;
    g_spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    g_spi_handle.Init.GuradTimeEn = DISABLE;
    g_spi_handle.Init.GuardTime = 0;
    g_spi_handle.Init.DozeMode = DISABLE;
    g_spi_handle.Init.Spc0 = DISABLE;
    g_spi_handle.Init.BaudratePreselectionBits = SPI_SPPR1_DIV20;
    g_spi_handle.Init.BaudrateBits = SPI_SPPR0_DIV20;
    g_spi_handle.Init.SlaveHighSpeedEn = DISABLE;
    g_spi_handle.Init.Pullup = DISABLE;
    g_spi_handle.Init.ReducedDriveCap = DISABLE;
    hal_spi_init(&g_spi_handle);
}

/**
 * @brief  SPI 模块Slave初始化函数
 * @param pspi 指向spi_typedef_t结构体的指针
 */
static void spi_slave_init(reg_spi_t *pspi)
{

    g_spi_handle.Instance = pspi;
    hal_spi_dis(&g_spi_handle);

    g_spi_handle.Init.Mode = SPI_SLAVE;
    /*mode 3*/
    g_spi_handle.Init.Cpha = SPI_CPHA_2EDGE;
    g_spi_handle.Init.Cpol = SPI_CPOL_HIGH;
    g_spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    g_spi_handle.Init.Ssoe = DISABLE;

    hal_spi_init(&g_spi_handle);
}

/**
 * @brief  SPI 模块中断配置函数
 */
static void spi_ininit(void)
{
    if (g_spi_handle.Instance == SPI1)
    {
        NVIC_Init(3, 1, SPI1_IRQn, 2);
        SPI1_IRQHandler_Callback = hal_spi_irqhandler;
    }
    else if (g_spi_handle.Instance == SPI2)
    {
        NVIC_Init(3, 1, SPI2_IRQn, 2);
        SPI2_IRQHandler_Callback = hal_spi_irqhandler;
    }
    else if (g_spi_handle.Instance == SPI3)
    {
        NVIC_Init(3, 1, SPI3_IRQn, 2);
        SPI3_IRQHandler_Callback = hal_spi_irqhandler;
    }
    else
    {
    }
}

/**
 * @brief  SPI 模块Master轮询测试例程
 * @param pinstance 指向spi_typedef_t结构体的指针
 */
void spi_master_test(reg_spi_t *pinstance)
{
    uint8_t loop = 0;
    uint8_t TmpVal = 0;
    uint32_t len;
    uint32_t timeout = 0; // timeout = 0:不运行超时机制；timeout != 0:运行超时机制
    status_t ret = STATUS_OK;
    uint8_t sn = 0;

    if (pinstance == SPI1)
    {
        printf("\r\nSPI1-->\r\n");
    }
    else if (pinstance == SPI2)
    {
        printf("\r\nSPI2-->\r\n");
    }
    else if (pinstance == SPI3)
    {
        printf("\r\nSPI3-->\r\n");
    }
    spi_master_init(pinstance);

    /*set baseadd 指令:55 00 B9 00 80 00 04 c2 */
    g_spi_txbuf[0] = 0x55;
    g_spi_txbuf[1] = 0X00;
    g_spi_txbuf[2] = 0XB9;
    g_spi_txbuf[3] = 0X00;
    g_spi_txbuf[4] = 0X80;
    g_spi_txbuf[5] = 0X00;
    g_spi_txbuf[6] = 0X04;
    g_spi_txbuf[7] = 0XC2;
    while (1)
    {
        g_spi_txbuf[3] = sn++;
        printf("\r\n*****************************************\r\n");
        printf("spi tx:");
        len = 8;
        for (loop = 0; loop < len; loop++)
        {
            printf("%02x ", g_spi_txbuf[loop]);
        }
        printf("\r\n");
        printf("master send begin...\r\n");
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
        ret = hal_spi_transmit(&g_spi_handle, g_spi_txbuf, len, timeout);
        if (ret != STATUS_OK)
        {
            printf("master send failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);
        delayms(100);

        /*读取8字节*/
        printf("check 0x55\r\n");
        while (1)
        {
            TmpVal = 0;
            len = 1;
            hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
            ret = hal_spi_receive(&g_spi_handle, &TmpVal, len, timeout);
            if (ret != STATUS_OK)
            {
                printf("master check failed,value = %02x,ret = %04x\r\n", TmpVal, ret);
                delayms(1000);
                continue;
            }
            hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);
            if (TmpVal == CMD_HEAD)
            {
                break;
            }
            else
            {
                delayms(10);
            }
        }
        printf("master receive bebin...\r\n");
        len = 9;
        memset(g_spi_rxbuf, 0, sizeof(g_spi_rxbuf));
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
        ret = hal_spi_receive(&g_spi_handle, g_spi_rxbuf, len, timeout);
        if (ret != STATUS_OK)
        {
            printf("master receive failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);

        printf("spi rx:");
        for (loop = 0; loop < len; loop++)
        {
            printf("%02x ", g_spi_rxbuf[loop]);
        }
        printf("\r\n");
        delayms(100);
    }
}

/**
 * @brief SPI 模块Master中断测试例程
 * @param pinstance 指向spi_typedef_t结构体的指针
 */
void spi_master_it_test(reg_spi_t *pinstance)
{
    uint8_t loop = 0;
    uint32_t len;
    uint32_t timeout = 0; // timeout = 0:不运行超时机制；timeout != 0:运行超时机制
    status_t ret = STATUS_OK;
    uint8_t sn = 0;
    if (pinstance == SPI1)
    {
        printf("\r\nSPI1-->\r\n");
    }
    else if (pinstance == SPI2)
    {
        printf("\r\nSPI2-->\r\n");
    }
    else if (pinstance == SPI3)
    {
        printf("\r\nSPI3-->\r\n");
    }
    spi_master_init(pinstance);
    spi_ininit();
    g_spi_txbuf[0] = 0x55;
    g_spi_txbuf[1] = 0X00;
    g_spi_txbuf[2] = 0XB9;
    g_spi_txbuf[3] = 0X00;
    g_spi_txbuf[4] = 0X80;
    g_spi_txbuf[5] = 0X00;
    g_spi_txbuf[6] = 0X04;
    g_spi_txbuf[7] = 0XC2;

    while (1)
    {
        g_spi_txbuf[3] = sn++;
        printf("\r\n*****************************************\r\n");
        printf("spi tx:");
        for (loop = 0; loop < 8; loop++)
        {
            printf("%02x ", g_spi_txbuf[loop]);
        }
        printf("\r\n");
        printf("master it send begin...\r\n");
        len = 8;
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
        ret = hal_spi_transmitit(&g_spi_handle, g_spi_txbuf, len, timeout);
        if (ret != STATUS_OK)
        {
            printf("master it send failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
        while (g_spi_handle.State != HAL_SPI_STATE_READY)
        {
            //    delayms(1);
            //    printf("g_spi_handle.State=%d\r\n",g_spi_handle.State);
        };
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);
        delayms(500);

        /*读取8字节*/
        memset(g_spi_rxbuf, 0, sizeof(g_spi_rxbuf));
        printf("master receive bebin...\r\n");
        len = 10;
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
        ret = hal_spi_receiveit(&g_spi_handle, g_spi_rxbuf, len, timeout);
        if (ret != STATUS_OK)
        {
            printf("master receive failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
        while (g_spi_handle.State != HAL_SPI_STATE_READY)
        {

            //                    printf("g_spi_handle.State=%d\r\n",g_spi_handle.State);
        };
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);

        printf("spi rx:");
        for (loop = 0; loop < len; loop++)
        {
            printf("%02x ", g_spi_rxbuf[loop]);
        }
        printf("\r\n");
        delayms(100);
    }
}

/**
 * @brief  SPI 模块Slave轮询测试例程
 * @param pinstance 指向spi_typedef_t结构体的指针
 */
void spi_slave_test(reg_spi_t *pinstance)
{
    /*read version 指令:55 00 B9 00 00 00 24 22 */
    uint8_t loop = 0;
    uint32_t len;
    uint32_t timeout = 0; // timeout = 0:不运行超时机制；timeout != 0:运行超时机制
    status_t ret = STATUS_OK;
    uint8_t sn = 0;
    spi_slave_init(pinstance);

    if (pinstance == SPI1)
    {
        printf("\r\nSPI1-->\r\n");
    }
    else if (pinstance == SPI2)
    {
        printf("\r\nSPI2-->\r\n");
    }
    else if (pinstance == SPI3)
    {
        printf("\r\nSPI3-->\r\n");
    }

    g_spi_txbuf[0] = 0x55;
    g_spi_txbuf[1] = 0x90;
    g_spi_txbuf[2] = 0x00;
    g_spi_txbuf[3] = 0x00;
    g_spi_txbuf[4] = 0x04;
    g_spi_txbuf[5] = 0x30;
    g_spi_txbuf[6] = 0x31;
    g_spi_txbuf[7] = 0x32;
    g_spi_txbuf[8] = 0x33;
    g_spi_txbuf[9] = 0x34;

    while (1)
    {
        g_spi_txbuf[3] = sn++;
        printf("\r\n*****************************************\r\n");
        /*读取8字节:规定时间内收不到数据返回超时
         *测试之时可将超时参数设置为0(死等)
         * */
        hal_spi_dis(&g_spi_handle);
        hal_spi_en(&g_spi_handle);
        memset(g_spi_rxbuf, 0, sizeof(g_spi_rxbuf));
        printf("slave receive bebin...\r\n");
        printf("check 0x55\r\n");
        len = 1;
        hal_spi_clrrxfifo(&g_spi_handle);
        while (1)
        {
            ret = hal_spi_receive(&g_spi_handle, &g_spi_rxbuf[0], len, timeout);
            if (ret != STATUS_OK)
            {
                printf("slave check failed,value = %02x,ret = %04x\r\n", g_spi_rxbuf[0], ret);
                delayms(1000);
                continue;
            }
            if (g_spi_rxbuf[0] == CMD_HEAD)
            {
                break;
            }
            else
            {
                delayms(10);
            }
        }
        len = 7;
        ret = hal_spi_receive(&g_spi_handle, &g_spi_rxbuf[1], len, timeout);
        if (ret != STATUS_OK)
        {
            printf("slave receive failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
        printf("spi rx:");
        for (loop = 0; loop < (len + 1); loop++)
        {
            printf("%02x ", g_spi_rxbuf[loop]);
        }
        printf("\r\n");
        /*回复10字节:建议从机响应加入超时处理*/
        printf("slave send bebin...\r\n");
        len = 10;
        printf("spi tx:");
        for (loop = 0; loop < len; loop++)
        {
            printf("%02x ", g_spi_txbuf[loop]);
        }
        printf("\r\n");

        ret = hal_spi_transmit(&g_spi_handle, g_spi_txbuf, len, timeout);
        hal_spi_dis(&g_spi_handle);
        if (ret != STATUS_OK)
        {
            printf("slave send failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
    }
}

/**
 * @brief  SPI 模块Slave中断测试例程
 * @param pinstance 指向spi_typedef_t结构体的指针
 */
void spi_slave_it_test(reg_spi_t *pinstance)
{
    uint8_t loop = 0;
    uint32_t len;
    uint32_t timeout = 0; // timeout = 0:不运行超时机制；timeout != 0:运行超时机制
    status_t ret = STATUS_OK;
    uint8_t sn = 0;
    if (pinstance == SPI1)
    {
        printf("\r\nSPI1-->\r\n");
    }
    else if (pinstance == SPI2)
    {
        printf("\r\nSPI2-->\r\n");
    }
    else if (pinstance == SPI3)
    {
        printf("\r\nSPI3-->\r\n");
    }
    spi_slave_init(pinstance);

    spi_ininit();

    g_spi_txbuf[0] = 0x55;
    g_spi_txbuf[1] = 0x90;
    g_spi_txbuf[2] = 0x00;
    g_spi_txbuf[3] = 0x00;
    g_spi_txbuf[4] = 0x04;
    g_spi_txbuf[5] = 0x30;
    g_spi_txbuf[6] = 0x31;
    g_spi_txbuf[7] = 0x32;
    g_spi_txbuf[8] = 0x33;
    g_spi_txbuf[9] = 0x34;

    while (1)
    {
        g_spi_txbuf[3] = sn++;
        /*读取8字节*/
        hal_spi_dis(&g_spi_handle);
        hal_spi_en(&g_spi_handle);
        printf("\r\n*****************************************\r\n");
        memset(g_spi_rxbuf, 0, sizeof(g_spi_rxbuf));

        len = 8;
        ret = hal_spi_receiveit(&g_spi_handle, g_spi_rxbuf, len, timeout);
        if (ret != STATUS_OK)
        {
            printf("slave receive failed,ret = %04x\r\n", ret);
            delayms(1000);
            continue;
        }
        while (g_spi_handle.State != HAL_SPI_STATE_READY)
        {

            //    printf("g_spi_handle.State=%d\r\n",g_spi_handle.State);
        }

        printf("spi rx:");
        for (loop = 0; loop < len; loop++)
        {
            printf("%02x ", g_spi_rxbuf[loop]);
        }
        printf("\r\n");

        len = 10;
        printf("spi tx:");
        for (loop = 0; loop < 10; loop++)
        {
            printf("%02x ", g_spi_txbuf[loop]);
        }
        printf("\r\n");
        delayms(100);
        /*回复10字节:建议从机响应加入超时处理*/
        ret = hal_spi_transmit(&g_spi_handle, g_spi_txbuf, 10, 10000000);
        if (ret != STATUS_OK)
        {
            printf("\r\nspi slave response failed\r\n");
        }
    }
}

/**
 * @brief  SPI 模块Master DMA测试例程
 * @param pdmac 指向dmac_typedef_t结构体的指针
 * @param pinstance 指向spi_typedef_t结构体的指针
 */
void spi_master_dma_test(reg_dmac_t *pdmac, reg_spi_t *pinstance)
{
    uint32_t i;
    uint8_t *ptx = 0;
    uint8_t *prx = 0;
    uint8_t sn = 0;
    uint8_t TmpVal = 0;

    if (pinstance == SPI1)
    {
        printf("\r\nSPII-->\r\n");
    }
    else if (pinstance == SPI2)
    {
        printf("\r\nSPI2-->\r\n");
    }
    if (pinstance == SPI3)
    {
        printf("\r\nSPI3->\r\n");
    }

    printf("spi dmac master test\r\n");
    spi_master_init(pinstance);

    while (1)
    {
        ptx = (uint8_t *)g_spi_txbuf;
        ptx[0] = 0x55;
        ptx[1] = 0x80;
        ptx[2] = 0x01;
        ptx[3] = sn++;
        ptx[4] = 0x00;
        ptx[5] = 0x00;
        ptx[6] = 0x00;
        ptx[7] = 0x7e;
        printf("SPIx_DmaMasterTxPolling\r\n");

        for (i = 0; i < 8; i++)
        {
            printf("%x ", ptx[i]);
        }

        printf("\r\n");

        hal_spi_clrtxfifo(&g_spi_handle);
        hal_spi_clrrxfifo(&g_spi_handle);
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
        hal_spi_dma_mastertxpolling(pdmac,
                                    0,
                                    &g_spi_handle,
                                    ptx,
                                    8);
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);
        hal_spi_clrtxfifo(&g_spi_handle);
        hal_spi_clrrxfifo(&g_spi_handle);
        printf("DMAC_SPI1TxPolling over\r\n");

        printf("SPIx_DmaMasterRxPolling\r\n");
        prx = (uint8_t *)g_spi_rxbuf;
        hal_spi_clrrxfifo(&g_spi_handle);

        delayms(500);
        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_LOW);
        while (1)
        {
            hal_spi_receive(&g_spi_handle, &TmpVal, 1, 100000);
            if (TmpVal == CMD_HEAD)
            {
                break;
            }
        }
        hal_spi_dis(&g_spi_handle);
        hal_spi_en(&g_spi_handle);
        hal_spi_dma_masterrxpolling(pdmac,
                                    0,
                                    1,
                                    &g_spi_handle,
                                    prx,
                                    9);

        hal_spi_clrtxfifo(&g_spi_handle);
        hal_spi_clrrxfifo(&g_spi_handle);

        hal_spi_gpiowritepin(g_spi_handle.Instance, SPI_PIN_CS, GPIO_HIGH);

        printf("SPIx_DmaMasterRxPolling over\r\n");
        for (i = 0; i < 9; i++)
        {
            printf("%x ", prx[i]);
        }
        printf("\r\n");
    }
}

/**
 * @brief  SPI 模块Slave DMA测试例程
 * @param pdmac 指向dmac_typedef_t结构体的指针
 * @param pinstance 指向spi_typedef_t结构体的指针
 */
void spi_slave_dma_test(reg_dmac_t *pdmac, reg_spi_t *pinstance)
{
    uint32_t i;
    uint8_t *ptx = 0;
    uint8_t *prx = 0;
    uint8_t sn = 0;

    if (pinstance == SPI1)
    {
        printf("\r\nSPII-->\r\n");
    }
    else if (pinstance == SPI2)
    {
        printf("\r\nSPI2-->\r\n");
    }
    if (pinstance == SPI3)
    {
        printf("\r\nSPI3->\r\n");
    }

    printf("spi dmac slave test\r\n");

    spi_slave_init(pinstance);

    while (1)
    {

        hal_spi_dis(&g_spi_handle);
        hal_spi_en(&g_spi_handle);
        hal_spi_clrrxfifo(&g_spi_handle);
        hal_spi_dma_slaverxpolling(pdmac,
                                   0,
                                   &g_spi_handle,
                                   g_spi_rxbuf,
                                   8);
        hal_spi_clrrxfifo(&g_spi_handle);
        prx = g_spi_rxbuf;
        printf("DMA_SPI1RxPolling over\r\n");

        for (i = 0; i < 8; i++)
        {
            printf("%x ", prx[i]);
        }
        printf("\r\n");

        ptx = g_spi_txbuf;
        ptx[0] = 0x55;

        ptx[1] = 0x90;
        ptx[2] = 0x00;

        ptx[3] = sn++;
        ptx[4] = 0x05;

        ptx[5] = 0x31;
        ptx[6] = 0x32;
        ptx[7] = 0x33;
        ptx[8] = 0x34;
        ptx[9] = 0x35;
        
        printf("SPIx_DmaSlaveTxPolling\r\n");

        for (i = 0; i < 10; i++)
        {
            printf("%x ", ptx[i]);
        }

        printf("\r\n");
        hal_spi_clrtxfifo(&g_spi_handle);
        hal_spi_dma_slavetxpolling(pdmac,
                                   0,
                                   &g_spi_handle,
                                   ptx,
                                   10);
        hal_spi_clrtxfifo(&g_spi_handle);
        hal_spi_dis(&g_spi_handle);
        // printf("SPIx_DmaSlaveTxPolling over\r\n");
    }
}

/**
 * @brief SPI 模块测试示例函数
 */
void spi_demo(void)
{
    reg_spi_t *spi_type_id;
    spi_type_id = SPI1;

#if SPI_MASTER_DEV_TEST
    spi_master_test(spi_type_id);
#endif

#if SPI_MASTER_DEV_IT_TEST
    spi_master_it_test(spi_type_id);
#endif

#if SPI_SLAVE_DEV_TEST
    spi_slave_test(spi_type_id);
#endif

#if SPI_SLAVE_DEV_IT_TEST
    spi_slave_it_test(spi_type_id);
#endif

#if SPI_MASTER_DEV_DMA_TEST
    reg_dmac_t *dma_type_id;
    if (spi_type_id == SPI3)
        dma_type_id = DMAC2;
    else
        dma_type_id = DMAC1;

    spi_master_dma_test(dma_type_id, spi_type_id);
#endif

#if SPI_SLAVE_DEV_DMA_TEST
    reg_dmac_t *dma_type_id;
    if (spi_type_id == SPI3)
        dma_type_id = DMAC2;
    else
        dma_type_id = DMAC1;

    spi_slave_dma_test(dma_type_id, spi_type_id);
#endif
}

/** @} */  // 结束 SPI 模块分组
/** @} */  // 结束外设模块分组
