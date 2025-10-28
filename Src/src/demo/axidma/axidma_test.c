/**
 * @file axidma_demo.c
 * @author Product application department
 * @brief  AXIDMA 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup AXIDMA AXIDMA模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "axidma_test.h"

// 全局变量定义
#define DMA_DEMO_BUF_SIZE 1024
#define DMA_LLP_RELOAD 0
static axidma_handle_t axidma_handle;
static uint8_t databuftx[DMA_DEMO_BUF_SIZE];
static uint8_t databufrx[DMA_DEMO_BUF_SIZE];

static uint8_t databuftx_llp[DMA_DEMO_BUF_SIZE];
static uint8_t databufrx_llp[DMA_DEMO_BUF_SIZE];

static uint32_t dbg_axi_dma_inrtflag;

__attribute__((aligned(64))) axi_dma_llp_t dbg_axidma_llp[16] = {0};

// 函数定义

/**
 * @brief 测试数据初始化函数
 *
 */
void dbg_prepare_data(void)
{
    uint32_t i;
    for (i = 0; i < DMA_DEMO_BUF_SIZE; i++)
    {
        databuftx[i] = i;
        databufrx[i] = 0xff;
    }
}
/**
 * @brief 测试数据验证函数
 *
 * @return uint8_t  0：数据错误
 *                  1：数据正确
 */
uint8_t dbg_verify_data(void)
{
    uint32_t i;
    for (i = 0; i < DMA_DEMO_BUF_SIZE; i++)
    {
        if (databuftx[i] != databufrx[i])
        {
            return 0;
        }
    }
    return 1;
}
/**
 * @brief LLP测试数据初始化函数
 *
 */
void dbg_prepare_data_llp(void)
{
    uint32_t i;
    for (i = 0; i < DMA_DEMO_BUF_SIZE; i++)
    {
        databuftx[i] = i;
        databuftx_llp[i] = i;
        databufrx[i] = 0xff;
        databufrx_llp[i] = 0xff;
    }
}
/**
 * @brief LLP测试数据验证函数
 *
 * @return uint8_t  0：数据错误
 *                  1：数据正确
 */
uint8_t dbg_verify_data_llp(void)
{
    uint32_t i;
    for (i = 0; i < DMA_DEMO_BUF_SIZE; i++)
    {
        if ((databuftx[i] != databufrx[i]) || (databuftx_llp[i] != databufrx_llp[i]))
        {
            return 0;
        }
    }
    return 1;
}
/**
 * @brief AXIDMA 模块llp链表节点初始化赋值函数
 *
 * @param initpara axidma配置参数
 */
void dbg_axidma_llp_init(axidma_handle_t *initpara)
{
    dbg_axidma_llp[0].SRC_ADDR_L = (uint32_t)databuftx;
    dbg_axidma_llp[0].SRC_ADDR_H = 0;
    dbg_axidma_llp[0].DST_ADDR_L = (uint32_t)databufrx;
    dbg_axidma_llp[0].DST_ADDR_H = 0;
    dbg_axidma_llp[0].BLOCK_TS = initpara->nBlocks;
    dbg_axidma_llp[0].CHx_CTL_L = hal_axidma_get_chx_ctl(initpara);
    dbg_axidma_llp[0].CHx_CTL_H = (AXI_DMAC_LLI_VALID_MASK | AXI_DMAC_LLI_IOC_BLK_MASK);
    dbg_axidma_llp[0].NEXT_LLI_L = (uint32_t)&dbg_axidma_llp[1];
    dbg_axidma_llp[0].NEXT_LLI_H = 0;

    dbg_axidma_llp[1].SRC_ADDR_L = (uint32_t)databuftx_llp;
    dbg_axidma_llp[1].SRC_ADDR_H = 0;
    dbg_axidma_llp[1].DST_ADDR_L = (uint32_t)databufrx_llp;
    dbg_axidma_llp[1].DST_ADDR_H = 0;
    dbg_axidma_llp[1].BLOCK_TS = initpara->nBlocks;
    dbg_axidma_llp[1].CHx_CTL_L = hal_axidma_get_chx_ctl(initpara);
#if DMA_LLP_RELOAD
    dbg_axidma_llp[1].CHx_CTL_H = (AXI_DMAC_LLI_VALID_MASK | AXI_DMAC_LLI_IOC_BLK_MASK);
    dbg_axidma_llp[1].NEXT_LLI_L = (uint32_t)&dbg_axidma_llp[0];
#else
    dbg_axidma_llp[1].CHx_CTL_H = (AXI_DMAC_LLI_VALID_MASK | AXI_DMAC_LLI_LAST_MASK | AXI_DMAC_LLI_IOC_BLK_MASK);
    dbg_axidma_llp[1].NEXT_LLI_L = 0;
#endif
    dbg_axidma_llp[1].NEXT_LLI_H = 0;
}
/**
 * @brief AXIDMA 模块contigous mode中断处理函数
 *
 */
void dbg_axi_dma_contigous_isr(void)
{
    dbg_axi_dma_inrtflag = 1;
    printf("axidma contigous mode isr\r\n");
}
/**
 * @brief AXIDMA 模块llp mode中断处理函数
 *
 */
void dbg_axi_dma_llp_isr(void)
{
    dbg_axi_dma_inrtflag = 1;
    printf("axidma llp mode isr\r\n");
}

/**
 * @brief AXIDMA contigous mode 测试
 *
 */
void axidma_contigousmode_demo(void)
{
    axidma_handle.instance = AXI_DMAC1;
    axidma_handle.channel_num = AXI_DMAC_CH0;
    axidma_handle.src_msize = AXI_DMAC_MIZE_16;              // burst size 16
    axidma_handle.dst_msize = AXI_DMAC_MIZE_16;              // burst size 16
    axidma_handle.src_tr_width = AXI_DMAC_TRANSWIDTH_8_BITS; // transfer width 8 bits
    axidma_handle.dst_tr_width = AXI_DMAC_TRANSWIDTH_8_BITS; // transfer width 8 bits
    axidma_handle.src_inc = AXI_DMAC_SINC_INC;
    axidma_handle.dst_inc = AXI_DMAC_DINC_INC;
    axidma_handle.src_multblk_type = AXI_DMAC_MULTIBLK_SRC_CONTIGUOUS;
    axidma_handle.dst_multblk_type = AXI_DMAC_MULTIBLK_DST_CONTIGUOUS;
    axidma_handle.transfer_type = AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA;

    axidma_handle.src_addr = (uint32_t)databuftx;
    axidma_handle.dst_addr = (uint32_t)databufrx;
    axidma_handle.nBlocks = DMA_DEMO_BUF_SIZE - 1;
    axidma_handle.irq_en = 1;
    axidma_handle.blk_tfr_en = 0;
    axidma_handle.axidma_cb = dbg_axi_dma_contigous_isr;

    dbg_prepare_data();
    dbg_axi_dma_inrtflag = 0;
    
    hal_axidma_init(&axidma_handle);
    hal_axidma_start(&axidma_handle);

    if (!axidma_handle.irq_en)
        hal_axidma_transfer_polling(&axidma_handle);
    else
    {
        while (!dbg_axi_dma_inrtflag)
            ;
        dbg_axi_dma_inrtflag = 0;
    }

    if (dbg_verify_data() == 0)
        printf("axidma trans fail,data error\r\n");
    else
        printf("axidma trans success\r\n");
    return;
}

/**
 * @brief AXIDMA 模块llp mode测试
 *
 */
void axidma_llpmode_demo()
{
    axidma_handle.instance = AXI_DMAC1;
    axidma_handle.channel_num = AXI_DMAC_CH0;
    axidma_handle.src_msize = AXI_DMAC_MIZE_16;              // burst size 16
    axidma_handle.dst_msize = AXI_DMAC_MIZE_16;              // burst size 16
    axidma_handle.src_tr_width = AXI_DMAC_TRANSWIDTH_8_BITS; // transfer width 8 bits
    axidma_handle.dst_tr_width = AXI_DMAC_TRANSWIDTH_8_BITS; // transfer width 8 bits
    axidma_handle.src_inc = AXI_DMAC_SINC_INC;
    axidma_handle.dst_inc = AXI_DMAC_DINC_INC;
    axidma_handle.src_multblk_type = AXI_DMAC_MULTIBLK_SRC_LINKEDLIST;
    axidma_handle.dst_multblk_type = AXI_DMAC_MULTIBLK_DST_LINKEDLIST;
    axidma_handle.transfer_type = AXI_DMAC_TRANSFERTYPE_M2M_CONTROLLER_DMA;

    axidma_handle.src_addr = (uint32_t)databuftx;
    axidma_handle.dst_addr = (uint32_t)databufrx;
    axidma_handle.nBlocks = DMA_DEMO_BUF_SIZE - 1;
    axidma_handle.irq_en = 1;
    axidma_handle.blk_tfr_en = 0;
    axidma_handle.axidma_cb = dbg_axi_dma_llp_isr;

    dbg_prepare_data_llp();
    dbg_axi_dma_inrtflag = 0;

    hal_axidma_init(&axidma_handle);
    dbg_axidma_llp_init(&axidma_handle);
    if ((hal_axidma_config_llp(&axidma_handle, (uint32_t)&dbg_axidma_llp[0])) != STATUS_OK)
    {
        printf("axidma llp config error\r\n");
        return;
    }

    hal_axidma_start(&axidma_handle);

    if (!axidma_handle.irq_en)
        hal_axidma_transfer_polling(&axidma_handle);
    else
    {
        while (!dbg_axi_dma_inrtflag)
            ;
        dbg_axi_dma_inrtflag = 0;
    }

    if (dbg_verify_data_llp() == 0)
        printf("axidma trans llp fail,data error\r\n");
    else
        printf("axidma trans llp success\r\n");
    return;
}
/**
 * @brief AXIDMA 模块测试示例函数
 *
 */
void axidma_demo(void)
{
    axidma_contigousmode_demo();
    axidma_llpmode_demo();
}

 
 /** @} */  // 结束 AXIDMA 模块分组
 /** @} */  // 结束外设模块分组

