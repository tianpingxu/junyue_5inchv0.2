/**
 *  @file ssi_hal.c
 *  @author Product application department
 *  @brief  SSI 模块硬件抽象层，供应用层调用，仅供参考
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

// 头文件包含
#include "ssi_hal.h"
#include "axidma_hal.h"
#include "ssi_sram.h"
#include "eport_hal.h"
#include "pinswap_drv.h"
// 全局变量定义
static uint32_t qspi_axi_dma_flag = 0;
// 函数定义

/**
 * @brief AXIDMA 模块llp mode中断处理函数
 *
 */
void dbg_axi_dma_llp_isr1(void)
{
    qspi_axi_dma_flag = 1;
}

/**
 *  @brief  SSI 模块批量写入算法函数
 *
 *  @param p_prog_func 写入函数指针如 drv_xip_flash_program
 *  @param addr 写入的地址
 *  @param p_buff 写入的数据指针
 *  @param len 写入的长度
 */
static void hal_ssi_bulk_progra_algorithm(uint8_t (*p_prog_func)(uint32_t, uint8_t *, uint32_t), uint32_t addr, uint8_t *p_buff, uint32_t len)
{
    uint32_t end_addr;
    end_addr = addr + len;

    // if the program region spread in more than one page
    if ((addr ^ (end_addr - 1)) >= SSI_PAGE_SIZE)
    {
        // program the first 256Byte unaligned data
        if ((addr % SSI_PAGE_SIZE) != 0)
        {
            len = SSI_PAGE_SIZE - (addr & 0xff);
            p_prog_func(addr, p_buff, len);
            addr += len;
            p_buff += len;
        }

        while (addr < ALIGN_DOWN(end_addr, SSI_PAGE_SIZE))
        {
            // 256Byte page program
            p_prog_func(addr, p_buff, SSI_PAGE_SIZE);
            addr += SSI_PAGE_SIZE;
            p_buff += SSI_PAGE_SIZE;
        }

        if (addr < end_addr)
        {
            // program the last 256Byte unaligned data
            p_prog_func(addr, p_buff, (end_addr - addr));
        }
    }
    else if (len > 0)
    {
        p_prog_func(addr, p_buff, len);
    }
}

/**
 *  @brief  SSI 模块Flash 写入函数
 *
 *  @param addr 写入的地址
 *  @param p_buff 写入的数据指针
 *  @param len 写入的长度
 *  @return status_t 返回函数运行状态
 */
status_t hal_ssi_flash_program(uint32_t addr, uint8_t *p_buff, uint32_t len)
{
    if (drv_ssi_get_xip_state(addr) != 0)
    {
        // the present flash is in xip mode
#if (SSI_MULTI_PAGE_PROGRAM)
        // spi flash multiple page program
        hal_ssi_bulk_progra_algorithm(drv_xip_flash_program, addr, p_buff, len);
#else
        // spi flash single page program
        drv_xip_flash_program(addr, p_buff, len);
#endif
        // 需要修改该函数
        dcache_invalidate_range((uint32_t *)addr, len);
    }
    else
    {

#if (SSI_MULTI_PAGE_PROGRAM)
        // spi flash multiple page program
        hal_ssi_bulk_progra_algorithm(drv_ssi_flash_program, addr, p_buff, len);
#else
        // spi flash single page program
        drv_ssi_flash_program(addr, p_buff, len);
#endif
        // the present flash is in ssi contorller mode, spi flash single page program
        
        dcache_invalidate_range((uint32_t *)addr, len);
    }

    return STATUS_OK;
}

/**
 *  @brief  SSI 模块Flash 读取函数
 *
 *  @param addr 读取的地址
 *  @param p_buff 读取的数据指针
 *  @param len 读取的长度
 */
void hal_ssi_flash_read(uint32_t addr, uint8_t *p_buff, uint32_t len)
{
    if (drv_ssi_get_xip_state(addr) != 0)
    {
        // the present flash is in xip mode
        memcpy(p_buff, (void *)addr, len);
    }
    else
    {
        reg_ssi_t *SSIReg;
        if ((addr >= SSI1_LOW_ADDR) && (addr < SSI1_HIGH_ADDR))
        {
            SSIReg = SSI1;
        }
        else if ((addr >= SSI2_LOW_ADDR) && (addr < SSI2_HIGH_ADDR))
        {
            SSIReg = SSI2;
        }
        else if ((addr >= SSI3_LOW_ADDR) && (addr < SSI3_HIGH_ADDR))
        {
            SSIReg = SSI3;
           
        }
        drv_ssi_flash_read(SSIReg,addr, p_buff, len);
       
    }
}

/**
 *  @brief  SSI 模块Flash Sector 擦除函数
 *
 *  @param addr 擦除的地址
 *  @return status_t 返回函数运行状态
 */
status_t hal_ssi_flash_sector_erase(uint32_t addr)
{
    if (drv_ssi_get_xip_state(addr) != 0)
    {
        // the present flash is in xip mode
        drv_xip_flash_erase(addr);

        dcache_invalidate_range((uint32_t *)addr, 0x1000);
    }
    else
    {
         reg_ssi_t *SSIReg;
         if ((addr >= SSI1_LOW_ADDR) && (addr < SSI1_HIGH_ADDR))
         {
            SSIReg = SSI1;
            SwitchPinFunction(SPI4_CS_FUN,EPORT2_PIN0_FUN);
            hal_eport_output(EPORT2,EPORT2_PIN0);
        }
        else if ((addr >= SSI2_LOW_ADDR) && (addr < SSI2_HIGH_ADDR))
        {
            SSIReg = SSI2;
        }
        else if ((addr >= SSI3_LOW_ADDR) && (addr < SSI3_HIGH_ADDR))
        {
            SSIReg = SSI3;
            SwitchPinFunction(SPI6_CS_FUN,EPORT4_PIN0_FUN);
            hal_eport_output(EPORT4,EPORT4_PIN0);
        }
        // the present flash is in ssi contorller mode
        drv_ssi_flash_erase(SSIReg,addr);
        dcache_invalidate_range((uint32_t *)addr, 0x1000);
    }

    return STATUS_OK;
}


/**
 * @brief SSI 模块单线初始化函数
 * @param SSIHandle 指向SSIx_HandleTypeDef结构体的指针,此结构体包含了QSPI单线模块的配置信息;
 */
void hal_ssi_init(ssi_handle_t *SSIHandle)
{
    drv_ssi_struct_init(&SSIHandle->Init);
    drv_ssi_deinit(SSIHandle->Instance);

    SSIHandle->Init.dfs = DFS_08_BIT;
    SSIHandle->Init.format = FORMAT_STD_MODE;
    SSIHandle->Init.ssi_baud_rate_prescaler = SSIFreq100M;
    SSIHandle->Init.rx_sample_delay = 0x2;
    status_t ret = drv_ssi_initt(SSIHandle->Instance, &SSIHandle->Init, SSI_TIMEOUT);
    if (ret != STATUS_OK)
    {
        return;
    }
}

 /**
  * @brief SSI 模块四线初始化函数
  * 
  * @param SSIHandle 指向SSIx_HandleTypeDef结构体的指针,此结构体包含了QSPI单线模块的配置信息;
  * @param len 传输长度
  * @param bound 频率
  * @param isread 读取/写入
  * @param sample_delay 延迟时间
  */
void hal_ssi_qualinit(ssi_handle_t *SSIHandle,uint32_t len,SSIFq bound,uint8_t isread,uint8_t isaxidma,uint32_t sample_delay)
{
    status_t tmp_flag;
    ssi_init_t ssi_ini;
    reg_ssi_t *pssi = SSIHandle->Instance;
    uint32_t waitCycles = 8;
    uint32_t timeout = 0xFFFF;

    drv_ssi_cmd(pssi, SSI_DIS);
    drv_ssi_struct_init(&ssi_ini);
    ssi_ini.dfs = DFS_08_BIT;
    ssi_ini.format = FORMAT_QUAD_MODE;
    ssi_ini.ndf = len; // be 0 when tx 
    ssi_ini.sste = TOGGLE_EN;
    ssi_ini.ssi_baud_rate_prescaler = bound;

    if (isread)
    {
        ssi_ini.tmod = TMOD_RX_ONLY;
    }
    else
    {
        ssi_ini.tmod = TMOD_TX_ONLY;
    }

    if (isread)
    {
      if(isaxidma)
       {
        ssi_ini.transfer_start_fifo_level = 0x01;
        ssi_ini.transmit_fifo_threshold = 0;
        ssi_ini.receive_fifo_threshold = 0x07;
        ssi_ini.address_length = ADDR_L16;
        ssi_ini.instruction_length = INST_L8;
        ssi_ini.trans_type =TT0; // CMD and DATA follow STD SPI Format
       }
      else
       {
        ssi_ini.transfer_start_fifo_level = 1;
        ssi_ini.transmit_fifo_threshold = 0;
        ssi_ini.receive_fifo_threshold = 7;
        ssi_ini.address_length = ADDR_L0;
        ssi_ini.instruction_length = INST_L0;
        ssi_ini.trans_type =TT0; // CMD and DATA follow STD SPI Format
       }
    }
    else
    {
        ssi_ini.transfer_start_fifo_level = 1;
        ssi_ini.transmit_fifo_threshold = 7;
        ssi_ini.receive_fifo_threshold = 0;
        ssi_ini.address_length = ADDR_L0;
        ssi_ini.instruction_length = INST_L8;
        // ssi_ini.ndf = 1;
        ssi_ini.trans_type =TT2; // L0+L0+TT0的配置也行，但是逻辑分析仪不能识别，遂单独发cmd以及数据，L16+L8需要4线发送
    }

    ssi_ini.wait_cycles = waitCycles;
    ssi_ini.clk_stretch_en = CLK_STRETCH_ENABLE;
    ssi_ini.rx_sample_delay = sample_delay;
    pssi->IMR = 0x00;

    tmp_flag = drv_ssi_initt(pssi, &ssi_ini, timeout);
   
    drv_ssi_cmd(pssi, SSI_EN);
}

/**
 * @brief SSI 模块CPU传输函数
 * @param pssi  指向SSI_TypeDef结构体的指针;
 * @param buf   数据缓存
 * @param buf_len 数据长度
 * @return status_t
 */
status_t hal_ssi_tx(reg_ssi_t *pssi, uint8_t *buf, uint32_t buf_len)
{
    volatile uint32_t temp;
    status_t tmp_flag = STATUS_OK;

    while (buf_len > 0)
    {
        // while (pssi->SR & SR_TFNF)
        {
            pssi->DR = *buf;
            buf++;
            buf_len--;
        }
        __DSB(); // 数据同步屏障  
        __ISB(); // 数据同步屏障  
       //  volatile __ASM("dsb");
        // while ((pssi->SR & SR_TFE) == 0){;}
    }

    while ((pssi->SR & SR_TFE) == 0){;}
    while ((pssi->SR & SR_BUSY) == 1){;}
    while (pssi->SR & SR_RFNE)
    {
        temp = pssi->DR;
    }

    // tmp_flag = drv_ssi_wait_flag_timeout(pssi, SSI_FLAG_INDEX_BUSY, SET, 10);
    // if (tmp_flag != STATUS_OK)
    // {
    //     printf("busy.\r\n");
    //     return STATUS_ERROR;
    // }

    return STATUS_OK;
}

/**
 * @brief SSI 模块CPU收函数
 * 
 * @param pssi 指向SSI_TypeDef结构体的指针
 * @param buf 数据缓存
 * @param buf_len 数据长度
 * @return status_t 
 */
status_t hal_ssi_rx(reg_ssi_t *pssi, uint8_t *buf, uint32_t buf_len)
{
    const int TIMEOUT_VAL = 0;
    int i = 0, j = 0, timeout;
    volatile uint32_t txnum, temp = 0;
    status_t tmp_flag;

    txnum = buf_len;
    timeout = TIMEOUT_VAL;
    // read data to clead fifo
    while (pssi->SR & SR_RFNE)
    {
        temp = pssi->DR;
        // printf("fifoclr: 0x%02x\n", temp);
    }
    while (buf_len > 0)
    {
        if ((pssi->SR & SR_TFNF) && (txnum > 0))
        {
            pssi->DR = DUMMY_BYTE;
            txnum--;
        }
        if (pssi->SR & SR_RFNE)
        {
            *(buf + i) = (pssi->DR);
            i++;
            buf_len--;
        }
        // else
        // {
        //     timeout--;
        //     if (timeout == 0)
        //     {
        //         return STATUS_TIMEOUT;
        //     }
        // }
    }

    while ((SSI3->SR & SR_RFF) == 1){;}
    // while ((SSI3->SR & SR_BUSY) == 1){;} // quad 模式下必现 busy.

    // tmp_flag = drv_ssi_wait_flag_timeout(pssi, SSI_FLAG_INDEX_BUSY, SET, TIMEOUT_VAL);
    // if (tmp_flag != STATUS_OK)
    // {
    //     printf("warning: rxtimeout.\r\n");
    //     return tmp_flag;
    // }

    return 0;
}

/**
 * @brief SSI3 模块AXIDMA 传输函数
 *
 * @param channel AXIDMA 通道
 * @param addr_peri 目的地址
 * @param buf 源地址
 * @param buf_len 传输长度
 */
void hal_axidma_tx(uint8_t channel, uint32_t *addr_peri, uint8_t *buf, uint32_t buf_len)
{
    dcache_clean_range((uint32_t *)buf,buf_len);
    axidma_handle_t qspi_axidma_handle;
    // status_t tmp_flag;
    // int TIMEOUT_VAL = 0;
    uint8_t temp;

    drv_ssitx_set_axidmaen(SSI3);
    qspi_axidma_handle.instance = AXI_DMAC1;
    qspi_axidma_handle.channel_num = channel;
    qspi_axidma_handle.src_msize = AXI_DMAC_MIZE_16;              // burst size 16
    qspi_axidma_handle.dst_msize = AXI_DMAC_MIZE_16;              // burst size 16
    qspi_axidma_handle.src_tr_width = AXI_DMAC_TRANSWIDTH_8_BITS; // transfer width 8 bits
    qspi_axidma_handle.dst_tr_width = AXI_DMAC_TRANSWIDTH_8_BITS; // transfer width 8 bits
    qspi_axidma_handle.src_inc = AXI_DMAC_SINC_INC;
    qspi_axidma_handle.dst_inc = AXI_DMAC_DINC_NO_CHANGE;
    qspi_axidma_handle.src_multblk_type = AXI_DMAC_MULTIBLK_SRC_CONTIGUOUS;
    qspi_axidma_handle.dst_multblk_type = AXI_DMAC_MULTIBLK_DST_CONTIGUOUS;
    qspi_axidma_handle.transfer_type = AXI_DMAC_TRANSFERTYPE_M2P_CONTROLLER_DMA;
    qspi_axidma_handle.dst_peri_type = HAL_AXIDMAC_PERIPHERAL_SSI3_TX;
    qspi_axidma_handle.src_addr = (uint32_t)buf;
    qspi_axidma_handle.dst_addr = (uint32_t)addr_peri;
    qspi_axidma_handle.nBlocks = buf_len-1;
    qspi_axidma_handle.irq_en = 1;
    qspi_axidma_handle.blk_tfr_en = 0;
    qspi_axidma_handle.axidma_cb = dbg_axi_dma_llp_isr1;
    qspi_axi_dma_flag = 0;
    hal_axidma_init(&qspi_axidma_handle);
    // NVIC_Init(3, 3, AXIDMA_IRQn, 2);
    hal_axidma_start(&qspi_axidma_handle);

    if (!qspi_axidma_handle.irq_en)
        hal_axidma_transfer_polling(&qspi_axidma_handle);
    else
    {
        while (!qspi_axi_dma_flag)
            ;
        qspi_axi_dma_flag = 0;
    }

    while ((SSI3->SR & SR_TFE) == 0){;}
    while ((SSI3->SR & SR_BUSY) == 1){;}

    // tmp_flag = drv_ssi_wait_flag_timeout(SSI3, SSI_FLAG_INDEX_BUSY, SET, TIMEOUT_VAL);
    // if (tmp_flag != STATUS_OK)
    // {
    //     printf("warning: rxtimeout.\r\n");
    // }
    dcache_invalidate_range((uint32_t *)buf,buf_len);
    return;
}

/**
 * @brief SSI3 模块AXIDMA 传输函数
 *
 * @param channel AXIDMA 通道
 * @param addr_peri 目的地址
 * @param buf 源地址
 * @param buf_len 传输长度
 */
void hal_axidma_rx(uint8_t channel, uint8_t *buf, uint32_t buf_len)
{
    dcache_clean_range((uint32_t *)buf,buf_len);
    axidma_handle_t nanddma_handle={0};
    volatile uint32_t reg;	
    drv_ssirx_set_axidmaen(SSI3);
    nanddma_handle.instance = AXI_DMAC1;
    nanddma_handle.channel_num = channel;
    nanddma_handle.src_addr =  (uint32_t)&SSI3->DR;
    nanddma_handle.dst_addr = (uint32_t)buf;
    nanddma_handle.nBlocks = buf_len - 1;
    nanddma_handle.src_inc = AXI_DMAC_SINC_NO_CHANGE;
    nanddma_handle.dst_inc = AXI_DMAC_DINC_INC;
    nanddma_handle.transfer_type = AXI_DMAC_TRANSFERTYPE_P2M_CONTROLLER_DMA;
    nanddma_handle.src_peri_type = AXI_DMAC1_PERIPHERAL_SSI3_RX;
    hal_axidma_init(&nanddma_handle);
    drv_axidma_enable_channel(&nanddma_handle);
    SSI3->DR = 0x6b;
    __DSB();
    __ISB();
    SSI3->DR = 0xff<<16|0x00;
     __DSB();
     __ISB();
    SSI3->DR = 0x00;	
    __DSB();
    __ISB();	

    do
    {
        reg=drv_axidma_chx_get_intstatus(&nanddma_handle);
    }while((reg & 0x02) == 0);
    drv_axidma_chx_clr_intstatus_l(&nanddma_handle,reg);
    SSI3->DMACR = 0x00;
    dcache_invalidate_range((uint32_t *)buf,buf_len);
}

/**
 *@brief 赋予SSI结构体默认值.
 *
 *@param[in] pinit 指向SSI_InitTypeDef结构体的指针;
 *@return 无 @ref 无
 */
void hal_ssi_deinit(ssi_handle_t *pinit)
{
    drv_ssi_deinit(pinit->Instance);
    pinit->Init.format = FORMAT_STD_MODE;
    pinit->Init.dfs   = DFS_08_BIT;
    pinit->Init.frf   = FRF_SPI;
    pinit->Init.scph  = SCPH_MIDDLE_BIT;
    pinit->Init.scpol = SCPOL_INACTIVE_HIGH;
    pinit->Init.tmod  = TMOD_TX_AND_RX;
    pinit->Init.srl   = SRL_NORMAL_MODE;
    pinit->Init.sste  = TOGGLE_DISABLE;
    pinit->Init.cfs   = CFS_01_BIT;
    pinit->Init.ndf   = 0;
    pinit->Init.ssi_baud_rate_prescaler = 0xffff;
    pinit->Init.transfer_start_fifo_level = 0;
    pinit->Init.transmit_fifo_threshold = 0;
    pinit->Init.receive_fifo_threshold = 0;
    pinit->Init.trans_type = TT0;
    pinit->Init.address_length = ADDR_L0;
    pinit->Init.instruction_length = INST_L0;
    pinit->Init.wait_cycles = 0x10;
    pinit->Init.clk_stretch_en = CLK_STRETCH_DISABLE;
}





