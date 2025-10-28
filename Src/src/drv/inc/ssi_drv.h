/**
 *  @file ssi_drv.h
 *  @author Product application department
 *  @brief  SSI 模块驱动层头文件
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef __SSI_DRV_H
#define __SSI_DRV_H

#ifdef __cplusplus
"C"
{
#endif

// 头文件包含
#include "cpm_drv.h"
#include "ccm_drv.h"
#include "ssi_reg.h"
#include "debug.h"
#include "status.h"
    
// 全局变量定义
// p_ssi 地址范围, x取值1~3
#define SSI1_LOW_ADDR 0x10000000
#define SSI1_HIGH_ADDR 0x12000000

#define SSI2_LOW_ADDR 0x12000000
#define SSI2_HIGH_ADDR 0x14000000

#define SSI3_LOW_ADDR 0x14000000
#define SSI3_HIGH_ADDR 0x1C000000
// 等待状态计数值

#define SSI_TIMEOUT 0x00FFFFFF

// W25Q128 cmd
#define DUMMY_BYTE 0xA5
#define READ_ID_CMD 0x90
#define WRITE_EN_CMD 0x06
#define SECT_ERASE_CMD 0x20  // 4K
#define BLOCK_ERASE_CMD 0x52 // 0x52-32K, 0xD8-64K
#define GET_SAT1_CMD 0x05
#define READ_CMD 0x03
#define PAGE_PROG_CMD 0x02
#define GET_SAT2_CMD 0x35
#define PROG_STA12_CMD 0x01
#define PROG_STA2_CMD 0x31
#define DUAL_READ_CMD 0x3B
#define QUAD_PROG_CMD 0x32
#define QUAD_READ_CMD 0x6B
#define QPI_READ_CMD 0x0B
#define QPI_ENTER_CMD 0x38
#define QPI_EXIT_CMD 0xFF
#define SET_READ_PARA_CMD 0xC0
#define RESET_EN_CMD 0x66
#define RESET_CMD 0x99

// ssi ops: read, write
#define READ_ID 0x9F
#define MR_READ 0xB5
#define WRITE 0x02
#define READ 0x03
#define ENTER_QPI_mode 0x35
#define EXIT_QPI_mode 0xF5
#define QPI_WRITE 0x38
#define QPI_FAST_READ 0xEB
#define WRAPPED_READ 0x8B
#define WRAPPED_WRITE 0x82

// ssi ops: program
#define QUAD_PROGRAM 0x04
#define QUAD_DMA_PROGRAM 0x40
#define QUAD_DMA_CH0_PROGRAM 0x40
#define QUAD_DMA_CH1_PROGRAM 0x41
#define QUAD_DMA_CH2_PROGRAM 0x42
#define QUAD_DMA_CH3_PROGRAM 0x43

#define STD_PROGRAM 0x01
#define STD_DMA_PROGRAM 0x10
#define STD_DMA_CH0_PROGRAM 0x10
#define STD_DMA_CH1_PROGRAM 0x11
#define STD_DMA_CH2_PROGRAM 0x12
#define STD_DMA_CH3_PROGRAM 0x13

#define QPI_PROGRAM 0x08
#define QPI_DMA_PROGRAM 0x80
#define QPI_DMA_CH0_PROGRAM 0x80
#define QPI_DMA_CH1_PROGRAM 0x81
#define QPI_DMA_CH2_PROGRAM 0x82
#define QPI_DMA_CH3_PROGRAM 0x83

// ssi status
#define SR_BUSY 0x01
#define SR_TFNF 0x02
#define SR_TFE 0x04
#define SR_RFNE 0x08
#define SR_RFF 0x10
#define SR_TXE 0x20


#define SPI_FRF(n)    (n<<22) //0-stand  1-dual  2-quad
#define SPI_STAND     SPI_FRF(0)
#define SPI_DUAL      SPI_FRF(1)
#define SPI_QUAD      SPI_FRF(2)
#define TMOD(n)       (n<<10) 
#define TX_ONLY       TMOD(1)
#define RX_ONLY       TMOD(2)
#define  QUAD_BAUDR  (0x04)
#define TXFTHR(n)     (n<<16)
#define TFT(n)        (n)
#define RFT(n)        (n)
#define TRANS_LEVEL(n)  (n) 
#define RSD(n)        (n) 

#define CLK_STRETCH     (1<<30)
#define WAIT_CYCLES(n)  (n<<11)
#define INST_L(n)       (n<<8)
#define INST_L8_BITS    INST_L(2)
#define ADDR_L(n)       (n<<2)

#define TRANS_TYPE(n)   (n)     //0-(stand ins and addr) 1-(stand ins and addr with FRF)   2-( ins and addr with FRF) 


// ssi page size
#define SSI_PAGE_SIZE 0x100

// ssi sector size
#define SSI_SECTOR_SIZE 0x1000
// ssi ctrl0 register
// ssi spi frf
#define SSI_SPI_FRF_MASK (0x3 << 22)
#define SSI_SPI_FRF_UNMASK (~(0x3 << 22))
#define _ssi_spi_frf_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_SPI_FRF_UNMASK, ((value & 0x3) << 22))
// ssi cfs
#define SSI_CFS_MASK (0xF << 16)
#define SSI_CFS_UNMASK (~(0xF << 16))
#define _ssi_cfs_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_CFS_UNMASK, ((value & 0xF) << 16))
// ssi sste
#define SSI_SSTE_MASK (0x1 << 14)
#define SSI_SSTE_UNMASK (~(0x1 << 14))
#define _ssi_sste_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_SSTE_UNMASK, ((value & 0x1) << 14))
// ssi sste
#define SSI_SRL_MASK (0x1 << 13)
#define SSI_SRL_UNMASK (~(0x1 << 13))
#define _ssi_srl_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_SRL_UNMASK, ((value & 0x1) << 13))
// ssi tmod
#define SSI_TMOD_MASK (0x3 << 10)
#define SSI_TMOD_UNMASK (~(0x3 << 10))
#define _ssi_tmod_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_TMOD_UNMASK, ((value & 0x3) << 10))
// ssi scopl
#define SSI_SCOPL_MASK (0x1 << 9)
#define SSI_SCOPL_UNMASK (~(0x1 << 9))
#define _ssi_scopl_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_SCOPL_UNMASK, ((value & 0x1) << 9))
// ssi scph
#define SSI_SCPH_MASK (0x1 << 8)
#define SSI_SCPH_UNMASK (~(0x1 << 8))
#define _ssi_scph_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_SCPH_UNMASK, ((value & 0x1) << 8))
// ssi frf
#define SSI_FRF_MASK (0x3 << 6)
#define SSI_FRF_UNMASK (~(0x3 << 6))
#define _ssi_frf_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_FRF_UNMASK, ((value & 0x3) << 6))
// ssi dfs
#define SSI_DFS_MASK (0x1F << 0)
#define SSI_DFS_UNMASK (~(0x1F << 0))
#define _ssi_dfs_set(ssi, value) _reg_modify(ssi->CTRLR0, SSI_DFS_UNMASK, ((value & 0x1F) << 0))
// ssi ctrl0 set
#define SSI_CTRL0_MASK (SSI_CFS_MASK | SSI_CFS_MASK | SSI_SSTE_MASK | SSI_SRL_MASK | SSI_TMOD_MASK | SSI_SCOPL_MASK | SSI_SCPH_MASK | SSI_FRF_MASK | SSI_DFS_MASK)
#define _ssi_ctrl0_set(ssi, value) _reg_write(ssi->CTRLR0, (value & SSI_CTRL0_MASK))
#define _ssi_ctrl0_get(ssi) (_reg_read(ssi->CTRLR0) & SSI_CTRL0_MASK)

// ssi ctrl1 register
// ssi ndf set
#define SSI_NDF_MASK (0xFF << 0)
#define SSI_NDF_UNMASK (~(0xFF << 0))
#define _ssi_ndf_set(ssi, value) _reg_modify(ssi->CTRLR1, SSI_NDF_UNMASK, ((value & 0xFF) << 0))
// ssi ctrl1 set
#define _ssi_ctrl1_set(ssi, value) _reg_write(ssi->CTRLR1, (value & SSI_NDF_MASK))
#define _ssi_ctrl1_get(ssi) (_reg_read(ssi->CTRLR1) & SSI_NDF_MASK)

// ssi enr register set
#define SSI_SSIC_EN_MASK (0x1 << 0)
#define _ssi_enr_set(ssi, value) _reg_write(ssi->SSIENR, (value & SSI_SSIC_EN_MASK))
#define _ssi_enr_get(ssi) (_reg_read(ssi->SSIENR) & SSI_SSIC_EN_MASK)

// ssi microwire register
// ssi mhs
#define SSI_MHS_MASK (0x1 << 2)
#define SSI_MHS_UNMASK (~(0x1 << 2))
#define _ssi_mhs_set(ssi, value) _reg_modify(ssi->MWCR, SSI_MHS_UNMASK, ((value & 0x1) << 2))
// ssi mdd
#define SSI_MDD_MASK (0x1 << 1)
#define SSI_MDD_UNMASK (~(0x1 << 1))
#define _ssi_mdd_set(ssi, value) _reg_modify(ssi->MWCR, SSI_MDD_UNMASK, ((value & 0x1) << 1))
// ssi mwmod
#define SSI_MWMOD_MASK (0x1 << 0)
#define SSI_MWMOD_UNMASK (~(0x1 << 0))
#define _ssi_mwmod_set(ssi, value) _reg_modify(ssi->MWCR, SSI_MWMOD_UNMASK, ((value & 0x1) << 0))
// ssi microwire register set
#define SSI_MICROWIRE_MASK (SSI_MHS_MASK | SSI_MDD_MASK | SSI_MWMOD_MASK)
#define _ssi_microwire_set(ssi, value) _reg_write(ssi->MWCR, (value & SSI_MICROWIRE_MASK))
#define _ssi_microwire_get(ssi) (_reg_read(ssi->MWCR) & SSI_MICROWIRE_MASK)

// ssi ser register
#define SSI_SER_MASK (0x1 << 0)
#define _ssi_ser_set(ssi, value) _reg_write(ssi->SER, (value & SSI_SER_MASK))
#define _ssi_ser_get(ssi) (_reg_read(ssi->SER) & SSI_SER_MASK)

// ssi baudr register
#define SSI_SCKDV_MASK (0xFFFF << 0)
#define SSI_SCKDV_UNMASK (~(0xFFFF << 0))
#define _ssi_sckdv_set(ssi, value) _reg_modify(ssi->BAUDR, SSI_SCKDV_UNMASK, ((value & 0xFFFF) << 0))
// ssi baudr set
#define SSI_BAUDR_MASK (SSI_SCKDV_MASK)
#define _ssi_baudr_set(ssi, value) _reg_write(ssi->BAUDR, (value & SSI_BAUDR_MASK))
#define _ssi_baudr_get(ssi) (_reg_read(ssi->BAUDR) & SSI_BAUDR_MASK)

// ssi txftlr register
// ssi txfthr
#define SSI_TXFTHR_MASK (0x1F << 16)
#define SSI_TXFTHR_UNMASK (~(0x1F << 16))
#define _ssi_txfthr_set(ssi, value) _reg_modify(ssi->TXFTLR, SSI_TXFTHR_UNMASK, ((value & 0x1F) << 16))
// ssi txfthr
#define SSI_TFT_MASK (0x1F << 0)
#define SSI_TFT_UNMASK (~(0x1F << 0))
#define _ssi_tft_set(ssi, value) _reg_modify(ssi->TXFTLR, SSI_TFT_UNMASK, ((value & 0x1F) << 0))
// ssi txftlr set
#define SSI_TXFTLR_MASK (SSI_TXFTHR_MASK | SSI_TFT_MASK)
#define _ssi_txftlr_set(ssi, value) _reg_write(ssi->TXFTLR, (value & SSI_TXFTLR_MASK))
#define _ssi_txftlr_get(ssi) (_reg_read(ssi->TXFTLR) & SSI_TXFTLR_MASK)

// ssi rxftlr register
// ssi rxftlr
#define SSI_RFT_MASK (0x1F << 0)
#define SSI_RFT_UNMASK (~(0x1F << 0))
#define _ssi_rft_set(ssi, value) _reg_modify(ssi->RXFTLR, SSI_RFT_UNMASK, ((value & 0x1F) << 0))
// ssi rxftlr set
#define SSI_RXFTLR_MASK (SSI_RFT_MASK)
#define _ssi_rxftlr_set(ssi, value) _reg_write(ssi->RXFTLR, (value & SSI_RXFTLR_MASK))
#define _ssi_rxftlr_get(ssi) (_reg_read(ssi->RXFTLR) & SSI_RXFTLR_MASK)

// ssi txflr register
// ssi txflr
#define SSI_TXFLR_MASK (0x3F << 0)
#define SSI_TXFLR_UNMASK (~(0x3F << 0))
#define _ssi_txflr_get(ssi) (_reg_read(ssi->TXFLR) & SSI_TXFLR_MASK)

// ssi rxflr register
// ssi rxflr
#define SSI_RXFLR_MASK (0x3F << 0)
#define SSI_RXFLR_UNMASK (~(0x3F << 0))
#define _ssi_rxflr_get(ssi) (_reg_read(ssi->RXFLR) & SSI_RXFLR_MASK)

// ssi sr register
// ssi rff
#define _ssi_sr_get_status(ssi)   _reg_read(ssi->SR) 
#define SSI_RFF_MASK (0x1 << 4)
#define SSI_RFF_UNMASK (~(0x1 << 4))
#define _ssi_rff_get(ssi) (_reg_read(ssi->SR) & SSI_RFF_MASK)
// ssi rfne
#define SSI_RFNE_MASK (0x1 << 3)
#define SSI_RFNE_UNMASK (~(0x1 << 3))
#define _ssi_rfne_get(ssi) (_reg_read(ssi->SR) & SSI_RFF_MASK)
// ssi tfe
#define SSI_TFE_MASK (0x1 << 2)
#define SSI_TFE_UNMASK (~(0x1 << 2))
#define _ssi_tfe_get(ssi) (_reg_read(ssi->SR) & SSI_TFE_MASK)
// ssi tfne
#define SSI_TFNE_MASK (0x1 << 1)
#define SSI_TFNE_UNMASK (~(0x1 << 1))
#define _ssi_tfne_get(ssi) (_reg_read(ssi->SR) & SSI_TFNE_MASK)
// ssi busy
#define SSI_BUSY_MASK (0x1 << 0)
#define SSI_BUSY_UNMASK (~(0x1 << 0))
#define _ssi_busy_get(ssi) (_reg_read(ssi->SR) & SSI_BUSY_MASK)
// ssi sr get
#define SSI_SR_L_MASK (0x1F)
#define _ssi_sr_l_get(ssi) (_reg_read(ssi->SR) & SSI_SR_L_MASK)
// ssi sr set
#define SSI_SR_MASK (SSI_RFF_MASK | SSI_RFNE_MASK | SSI_TFE_MASK | SSI_TFNE_MASK | SSI_BUSY_MASK | SSI_SR_L_MASK)
#define _ssi_sr_set(ssi, value) _reg_write(ssi->SR, (value & SSI_SR_MASK))
#define _ssi_sr_get(ssi) (_reg_read(ssi->SR) & SSI_SR_MASK)

// ssi imr register
// ssi xrxoim
#define SSI_XRXOIM_MASK (0x1 << 6)
#define SSI_XRXOIM_UNMASK (~(0x1 << 6))
#define _ssi_xrxoim_set(ssi, value)   _reg_modify(ssi->IMR, SSI_XRXOIM_UNMASK, ((value & 0x1) << 6))
// ssi rxfim
#define SSI_RXFIM_MASK (0x1 << 4)
#define SSI_RXFIM_UNMASK (~(0x1 << 4))
#define _ssi_rxfim_set(ssi, value)   _reg_modify(ssi->IMR, SSI_RXFIM_UNMASK, ((value & 0x1) << 4))
// ssi rxoim
#define SSI_RXOIM_MASK (0x1 << 3)
#define SSI_RXOIM_UNMASK (~(0x1 << 3))
#define _ssi_rxoim_set(ssi, value)   _reg_modify(ssi->IMR, SSI_RXOIM_UNMASK, ((value & 0x1) << 3))
// ssi rxuim
#define SSI_RXUIM_MASK (0x1 << 2)
#define SSI_RXUIM_UNMASK (~(0x1 << 2))
#define _ssi_rxuim_set(ssi, value)   _reg_modify(ssi->IMR, SSI_RXUIM_UNMASK, ((value & 0x1) << 2))
// ssi txoim
#define SSI_TXOIM_MASK (0x1 << 1)
#define SSI_TXOIM_UNMASK (~(0x1 << 1))
#define _ssi_txoim_set(ssi, value)   _reg_modify(ssi->IMR, SSI_TXOIM_UNMASK, ((value & 0x1) << 1))
// ssi txeim
#define SSI_TXEIM_MASK (0x1 << 0)
#define SSI_TXEIM_UNMASK (~(0x1 << 0))
#define _ssi_txeim_set(ssi, value)   _reg_modify(ssi->IMR, SSI_TXEIM_UNMASK, ((value & 0x1) << 0))
// ssi imr set
#define SSI_IMR_MASK (SSI_XRXOIM_MASK | SSI_RXFIM_MASK | SSI_RXOIM_MASK | SSI_RXUIM_MASK | SSI_TXOIM_MASK | SSI_TXEIM_MASK)
#define _ssi_imr_set(ssi, value) _reg_write(ssi->IMR, (value & SSI_IMR_MASK))
#define _ssi_imr_get(ssi) (_reg_read(ssi->IMR) & SSI_IMR_MASK)

// ssi isr register
// ssi xrxois
#define SSI_XRXOIS_MASK (0x1 << 6)
#define SSI_XRXOIS_UNMASK (~(0x1 << 6))
#define _ssi_xrxois_get(ssi) (_reg_read(ssi->ISR) & SSI_XRXOIS_MASK)
// ssi rxfis
#define SSI_RXFIS_MASK (0x1 << 4)
#define SSI_RXFIS_UNMASK (~(0x1 << 4))
#define _ssi_rxfis_get(ssi) (_reg_read(ssi->ISR) & SSI_RXFIS_MASK)
// ssi rxois
#define SSI_RXOIS_MASK (0x1 << 3)
#define SSI_RXOIS_UNMASK (~(0x1 << 3))
#define _ssi_rxois_get(ssi) (_reg_read(ssi->ISR) & SSI_RXOIS_MASK)
// ssi rxuis
#define SSI_RXUIS_MASK (0x1 << 2)
#define SSI_RXUIS_UNMASK (~(0x1 << 2))
#define _ssi_rxuis_get(ssi) (_reg_read(ssi->ISR) & SSI_RXUIS_MASK)
// ssi txois
#define SSI_TXOIS_MASK (0x1 << 1)
#define SSI_TXOIS_UNMASK (~(0x1 << 1))
#define _ssi_txois_get(ssi) (_reg_read(ssi->ISR) & SSI_TXOIS_MASK)
// ssi txeis
#define SSI_TXEIS_MASK (0x1 << 0)
#define SSI_TXEIS_UNMASK (~(0x1 << 0))
#define _ssi_txeis_get(ssi) (_reg_read(ssi->ISR) & SSI_TXEIS_MASK)
// ssi isr get
#define SSI_ISR_MASK (SSI_XRXOIS_MASK | SSI_RXFIS_MASK | SSI_RXOIS_MASK | SSI_RXUIS_MASK | SSI_TXOIS_MASK | SSI_TXEIS_MASK)
#define _ssi_isr_get(ssi) (_reg_read(ssi->ISR) & SSI_ISR_MASK)

// ssi risr register
// ssi xrxoir
#define SSI_XRXOIR_MASK (0x1 << 6)
#define SSI_XRXOIR_UNMASK (~(0x1 << 6))
#define _ssi_xrxoir_get(ssi) (_reg_read(ssi->RISR) & SSI_XRXOIR_MASK)
// ssi rxfir
#define SSI_RXFIR_MASK (0x1 << 4)
#define SSI_RXFIR_UNMASK (~(0x1 << 4))
#define _ssi_rxfir_get(ssi) (_reg_read(ssi->RISR) & SSI_RXFIR_MASK)
// ssi rxoir
#define SSI_RXOIR_MASK (0x1 << 3)
#define SSI_RXOIR_UNMASK (~(0x1 << 3))
#define _ssi_rxoir_get(ssi) (_reg_read(ssi->RISR) & SSI_RXOIR_MASK)
// ssi rxuir
#define SSI_RXUIR_MASK (0x1 << 2)
#define SSI_RXUIR_UNMASK (~(0x1 << 2))
#define _ssi_rxuir_get(ssi) (_reg_read(ssi->RISR) & SSI_RXUIR_MASK)
// ssi txoir
#define SSI_TXOIR_MASK (0x1 << 1)
#define SSI_TXOIR_UNMASK (~(0x1 << 1))
#define _ssi_txoir_get(ssi) (_reg_read(ssi->RISR) & SSI_TXOIR_MASK)
// ssi txeir
#define SSI_TXEIR_MASK (0x1 << 0)
#define SSI_TXEIR_UNMASK (~(0x1 << 0))
#define _ssi_txeir_get(ssi) (_reg_read(ssi->RISR) & SSI_TXEIR_MASK)
// ssi isr get
#define SSI_RISR_MASK (SSI_XRXOIR_MASK | SSI_RXFIR_MASK | SSI_RXOIR_MASK | SSI_RXUIR_MASK | SSI_TXOIR_MASK | SSI_TXEIR_MASK)
#define _ssi_risr_get(ssi) (_reg_read(ssi->RISR) & SSI_RISR_MASK)

// ssi txoicr register
// ssi txoicr
#define SSI_TXOICR_MASK (0x1 << 0)
#define SSI_TXOICR_UNMASK (~(0x1 << 0))
#define _ssi_txoicr_read_clr(ssi) (_reg_read(ssi->TXOICR) & SSI_TXOICR_MASK)

// ssi rxoicr register
// ssi rxoicr
#define SSI_RXOICR_MASK (0x1 << 0)
#define SSI_RXOICR_UNMASK (~(0x1 << 0))
#define _ssi_rxoicr_read_clr(ssi) (_reg_read(ssi->RXOICR) & SSI_RXOICR_MASK)

// ssi rxuicr register
// ssi rxuicr
#define SSI_RXUICR_MASK (0x1 << 0)
#define SSI_RXUICR_UNMASK (~(0x1 << 0))
#define _ssi_rxuicr_read_clr(ssi) (_reg_read(ssi->RXUICR) & SSI_RXUICR_MASK)

// ssi icr register
// ssi icr
#define SSI_ICR_MASK (0x1 << 0)
#define SSI_ICR_UNMASK (~(0x1 << 0))
#define _ssi_icr_read_clr(ssi) (_reg_read(ssi->ICR) & SSI_ICR_MASK)

// ssi dmacr register
// ssi tdma en
#define SSI_TDMAE_MASK (0x1 << 1)
#define SSI_TDMAE_UNMASK (~(0x1 << 1))
#define _ssi_tdma_en_set(ssi, value)   _reg_modify(ssi->DMACR, SSI_TXEIM_UNMASK, ((value & 0x1) << 1))
// ssi rdma en
#define SSI_RDMAE_MASK (0x1 << 0)
#define SSI_RDMAE_UNMASK (~(0x1 << 0))
#define _ssi_rdma_en_set(ssi, value)   _reg_modify(ssi->DMACR, SSI_RDMAE_MASK, ((value & 0x1) << 0))
// ssi dmacr set
#define SSI_DMA_CR_MASK (SSI_TDMAE_MASK | SSI_RDMAE_MASK)
#define _ssi_dma_cr_set(ssi, value) _reg_write(ssi->DMACR, value &SSI_DMA_CR_MASK)
#define _ssi_dma_cr_get(ssi) (_reg_read(ssi->DMACR) & SSI_DMA_CR_MASK)

// ssi dma tdlr register
// ssi dmatdl set
#define SSI_DMATDL_MASK (0x1F)
#define _ssi_dma_tdlr_set(ssi, value) _reg_write(ssi->DMATDLR, value &SSI_DMATDL_MASK)
#define _ssi_dma_tdlr_get(ssi) (_reg_read(ssi->DMATDLR) & SSI_DMATDL_MASK)

// ssi dma rdlr register
// ssi dma rdl set
#define SSI_DMARDL_MASK (0x1F)
#define _ssi_dma_rdlr_set(ssi, value) _reg_write(ssi->DMARDLR, value &SSI_DMARDL_MASK)
#define _ssi_dma_rdlr_get(ssi) (_reg_read(ssi->DMARDLR) & SSI_DMARDL_MASK)

// ssi dr register
// ssi dr set
#define SSI_DR_MASK (0xFFFFFFFF)
#define _ssi_dr_set(ssi, value) _reg_write(ssi->DR, value &SSI_DR_MASK)
#define _ssi_dr_get(ssi) (_reg_read(ssi->DR) & SSI_DR_MASK)

// ssi rxsdr register
// ssi se set
#define SSI_SE_MASK (0x1 << 16)
#define SSI_SE_UNMASK (~(0x1 << 16))
#define _ssi_se_set(ssi, value)   _reg_modify(ssi->RXSDR, SSI_SE_UNMASK, ((value & 0x1) << 16))
// ssi rsd set
#define SSI_RSD_MASK (0xFF << 0)
#define SSI_RSD_UNMASK (~(0xFF << 0))
#define _ssi_rsd_set(ssi, value)   _reg_modify(ssi->RXSDR, SSI_RSD_UNMASK, ((value & 0xFF) << 0))
// ssi rxsdr set
#define SSI_RXSDR_MASK (SSI_SE_MASK | SSI_RSD_MASK)
#define _ssi_rxsdr_set(ssi, value) _reg_write(ssi->RXSDR, value &SSI_RXSDR_MASK)
#define _ssi_rxsdr_get(ssi) (_reg_read(ssi->RXSDR) & SSI_RXSDR_MASK)

// ssi spi ctrl0 register
// ssi clk stretch set
#define SSI_CLK_STRETCH_MASK (0x1 << 30)
#define SSI_CLK_STRETCH_UNMASK (~(0x1 << 30))
#define _ssi_clk_stretch_set(ssi, value)   _reg_modify(ssi->SPICTRLR0, SSI_CLK_STRETCH_UNMASK, ((value & 0x1) << 30))
// ssi wait cycles set
#define SSI_WAIT_CYCLES_MASK (0x1F << 11)
#define SSI_WAIT_CYCLES_UNMASK (~(0x1F << 11))
#define _ssi_wait_cycles_set(ssi, value)   _reg_modify(ssi->SPICTRLR0, SSI_WAIT_CYCLES_UNMASK, ((value & 0x1F) << 11))
// ssi inst l set
#define SSI_INST_L_MASK (0x3 << 8)
#define SSI_INST_L_UNMASK (~(0x3 << 8))
#define _ssi_inst_l_set(ssi, value)   _reg_modify(ssi->SPICTRLR0, SSI_INST_L_UNMASK, ((value & 0x3) << 8))
// ssi addr l set
#define SSI_ADDR_L_MASK (0x7 << 2)
#define SSI_ADDR_L_UNMASK (~(0x7 << 2))
#define _ssi_addr_l_set(ssi, value)   _reg_modify(ssi->SPICTRLR0, SSI_ADDR_L_UNMASK, ((value & 0x7) << 2))
// ssi trans_type set
#define SSI_TRANS_TYPE_MASK (0x3 << 0)
#define SSI_TRANS_TYPE_UNMASK (~(0x3 << 0))
#define _ssi_trans_type_set(ssi, value)   _reg_modify(ssi->SPICTRLR0, SSI_TRANS_TYPE_UNMASK, ((value & 0x3) << 0))
// ssi spi ctrl0 set
#define SSI_SPI_CTRL0_MASK (SSI_CLK_STRETCH_MASK | SSI_WAIT_CYCLES_MASK | SSI_INST_L_MASK | SSI_ADDR_L_MASK | SSI_TRANS_TYPE_MASK)
#define _ssi_spi_ctrl0_set(ssi, value) _reg_write(ssi->SPICTRLR0, value &SSI_SPI_CTRL0_MASK)
#define _ssi_spi_ctrl0_get(ssi) (_reg_read(ssi->SPICTRLR0) & SSI_SPI_CTRL0_MASK)

// ssi xip mbr register
// ssi xip md bits set
#define SSI_XIP_MD_BITS_MASK (0xFFFF << 0)
#define _ssi_xip_mbr_set(ssi, value) _reg_write(ssi->XIPMBR, value &SSI_XIP_MD_BITS_MASK)
#define _ssi_xip mbr_get(ssi)(_reg_read(ssi->XIPMBR) & SSI_XIP_MD_BITS_MASK)

// ssi xip iir register
// ssi incr inst set
#define SSI_INCR_INST_MASK (0xFFFF << 0)
#define _ssi_xip_iir_set(ssi, value) _reg_write(ssi->XIPIIR, value &SSI_INCR_INST_MASK)
#define _ssi_xip_iir_get(ssi) (_reg_read(ssi->XIPIIR) & SSI_INCR_INST_MASK)

// ssi xip wir register
// ssi wrap inst set
#define SSI_WRAP_INST_MASK (0xFFFF << 0)
#define _ssi_xip_wir_set(ssi, value) _reg_write(ssi->XIPWIR, value &SSI_WRAP_INST_MASK)
#define _ssi_xip_wir_get(ssi) (_reg_read(ssi->XIPWIR) & SSI_WRAP_INST_MASK)

// ssi xip cr register
// ssi xip prefetch en set
#define SSI_XIP_PRETCH_EN_MASK (0x1 << 29)
#define SSI_XIP_PRETCH_EN_UNMASK (~(0x1 << 29))
#define _ssi_xip_pretch_en_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_PRETCH_EN_UNMASK, ((value & 0x1) << 29))
// ssi xip mbl set
#define SSI_XIP_MBL_MASK (0x3 << 26)
#define SSI_XIP_MBL_UNMASK (~(0x3 << 26))
#define _ssi_xip_mbl_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_MBL_UNMASK, ((value & 0x3) << 26))
// ssi xip cont xfer en set
#define SSI_XIP_CONT_XFER_EN_MASK (0x1 << 23)
#define SSI_XIP_CONT_XFER_EN_UNMASK (~(0x1 << 23))
#define _ssi_xip_cont_xfer_en_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_CONT_XFER_EN_UNMASK, ((value & 0x1) << 23))
// ssi xip inst en set
#define SSI_XIP_INST_EN_MASK (0x1 << 22)
#define SSI_XIP_INST_EN_UNMASK (~(0x1 << 22))
#define _ssi_xip_inst_en_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_INST_EN_UNMASK, ((value & 0x1) << 22))
// ssi xip dfc hc set
#define SSI_XIP_DFS_HC_MASK (0x1 << 18)
#define SSI_XIP_DFS_HC_UNMASK (~(0x1 << 18))
#define _ssi_xip_dfs_hc_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_DFS_HC_UNMASK, ((value & 0x1) << 18))
// ssi xip wait cycles set
#define SSI_XIP_WAIT_CYCLES_MASK (0x1F << 13)
#define SSI_XIP_WAIT_CYCLES_UNMASK (~(0x1F << 13))
#define _ssi_xip_wait_cycles_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_WAIT_CYCLES_UNMASK, ((value & 0x1F) << 13))
// ssi xip md bist en set
#define SSI_XIP_MD_BIST_EN_MASK (0x1 << 12)
#define SSI_XIP_MD_BIST_EN_UNMASK (~(0x1 << 12))
#define _ssi_xip_md_bist_en_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_MD_BIST_EN_UNMASK, ((value & 0x1) << 12))
// ssi xip inst l set
#define SSI_XIP_INST_L_MASK (0x3 << 9)
#define SSI_XIP_INST_L_UNMASK (~(0x3 << 9))
#define _ssi_xip_inst_l_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_INST_L_UNMASK, ((value & 0x3) << 9))
// ssi xip addr l set
#define SSI_XIP_ADDR_L_MASK (0xF << 4)
#define SSI_XIP_ADDR_L_UNMASK (~(0xF << 4))
#define _ssi_xip_addr_l_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_ADDR_L_UNMASK, ((value & 0xF) << 4))
// ssi xip trans type set
#define SSI_XIP_TRANS_TYPE_MASK (0x3 << 2)
#define SSI_XIP_TRANS_TYPE_UNMASK (~(0x3 << 2))
#define _ssi_xip_trans_type_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_TRANS_TYPE_UNMASK, ((value & 0x3) << 2))
// ssi xip frf set
#define SSI_XIP_FRF_MASK (0x3 << 0)
#define SSI_XIP_FRF_UNMASK (~(0x3 << 0))
#define _ssi_xip_frf_set(ssi, value)   _reg_modify(ssi->XIPCR, SSI_XIP_FRF_UNMASK, ((value & 0x3) << 0))
// ssi xip cr set
#define SSI_XIP_CR_MASK (SSI_XIP_PRETCH_EN_MASK | SSI_XIP_MBL_MASK | SSI_XIP_CONT_XFER_EN_MASK | SSI_XIP_INST_EN_MASK | SSI_XIP_DFS_HC_MASK | SSI_XIP_WAIT_CYCLES_MASK | SSI_XIP_MD_BIST_EN_MASK | SSI_XIP_INST_L_MASK | SSI_XIP_ADDR_L_MASK | SSI_XIP_TRANS_TYPE_MASK | SSI_XIP_FRF_MASK)
#define _ssi_xip_cr_set(ssi, value) _reg_write(ssi->XIPCR, value &SSI_XIP_CR_MASK)
#define _ssi_xip_cr_get(ssi) (_reg_read(ssi->XIPCR) & SSI_XIP_CR_MASK)

// ssi xip ser set
#define SSI_XIP_SER_MASK (0x1 << 0)
#define _ssi_xip_ser_set(ssi, value) _reg_write(ssi->XIPSER, value &SSI_XIP_SER_MASK)
#define _ssi_xip_ser_get(ssi) (_reg_read(ssi->XIPSER) & SSI_XIP_SER_MASK)

// ssi xip xrxiocr set
#define SSI_XIP_XRXOICR_MASK (0x1 << 0)
#define _ssi_xip_xrxiocr_clr(ssi) (_reg_read(ssi->XRXIOCR) & SSI_XIP_XRXOICR_MASK)

/**
 *  @brief SSI 模块数据类型结构体定义
 *
 */
typedef struct
{
    uint8_t dfs;                       // SSI数据帧大小：默认值 0x00，CTRLR0
    uint8_t frf;                       // SSI数据帧格式：默认值 0x00, CTRLR0
    uint8_t scph;                      // 串行时钟相位：默认值 0x00
    uint8_t scpol;                     // 串行时钟极性：默认值 0x00
    uint8_t tmod;                      // 传输模式：默认值 0x00
    uint8_t srl;                       // 位移寄存器循环：默认值 0x00
    uint8_t sste;                      // 从设备选择切换使能：默认值 0x00
    uint8_t cfs;                       // 控制帧大小：默认值 0x00
    uint8_t format;                    // SSI通讯格式: Standard SPI Format, Dual SPI Format, Quad SPI Format
    uint16_t ndf;                      // 数据帧数量: 默认值 0x04，CTRLR1
    uint16_t ssi_baud_rate_prescaler;  // SSI时钟分频值
    uint8_t transfer_start_fifo_level; // TXFTLR << 16
    uint8_t transmit_fifo_threshold;   // TXFTLR
    uint8_t receive_fifo_threshold;    // RXFTLR
    uint8_t trans_type;                // SSI传输类型
    uint8_t address_length;            // SSI地址长度
    uint8_t instruction_length;        // SSI指令长度
    uint8_t wait_cycles;               // 等待cycle数
    uint8_t clk_stretch_en;            // SPI传输扩展使能
    uint32_t rx_sample_delay;          // 接收延迟采样设置
} ssi_init_t;
/**
 *  @brief  SSI 模块状态标志索引枚举定义
 *
 */
typedef enum
{
    SSI_FLAG_INDEX_BUSY = 0x01,
    SSI_FLAG_INDEX_TFNF = 0x02,
    SSI_FLAG_INDEX_TFE = 0x04,
    SSI_FLAG_INDEX_RFNE = 0x08,
    SSI_FLAG_INDEX_RFF = 0x10
} ssi_flag_index_t;

/**
 *  @brief  SSI 模块读写操作类型枚举定义
 *
 */
typedef enum
{
    DRV_SSI_READ = 0x00,
    DRV_SSI_WRITE = 0x01,
} drv_ssi_read_t;
/**
 *  @brief  SSI 模块DFS 数据帧长度类型枚举定义
 *
 */
typedef enum
{
    DFS_01_BIT = 0x00,
    DFS_02_BIT = 0x01,
    DFS_03_BIT = 0x02,
    DFS_04_BIT = 0x03,
    DFS_05_BIT = 0x04,
    DFS_06_BIT = 0x05,
    DFS_07_BIT = 0x06,
    DFS_08_BIT = 0x07,
    DFS_09_BIT = 0x08,
    DFS_10_BIT = 0x09,
    DFS_11_BIT = 0x0a,
    DFS_12_BIT = 0x0b,
    DFS_13_BIT = 0x0c,
    DFS_14_BIT = 0x0d,
    DFS_15_BIT = 0x0e,
    DFS_16_BIT = 0x0f,
    DFS_17_BIT = 0x10,
    DFS_18_BIT = 0x11,
    DFS_19_BIT = 0x12,
    DFS_20_BIT = 0x13,
    DFS_21_BIT = 0x14,
    DFS_22_BIT = 0x15,
    DFS_23_BIT = 0x16,
    DFS_24_BIT = 0x17,
    DFS_25_BIT = 0x18,
    DFS_26_BIT = 0x19,
    DFS_27_BIT = 0x1a,
    DFS_28_BIT = 0x1b,
    DFS_29_BIT = 0x1c,
    DFS_30_BIT = 0x1d,
    DFS_31_BIT = 0x1e,
    DFS_32_BIT = 0x1f
} ssi_dfs_t;
/**
 *  @brief  SSI 模块串行传输协议类型枚举定义
 *
 */
typedef enum
{
    FRF_SPI = 0x00,
    FRF_SSP = 0x01,
    FRF_MICROWIRE = 0x02
} ssi_frf_t;
/**
 * @brief SSI 模块SCPH串行时钟相位类型枚举定义
 */
typedef enum
{
    SCPH_MIDDLE_BIT = 0x00,
    SCPH_START_BIT = 0x01
} ssi_scph_t;
/**
 * @brief SSI 模块SCPOL串行时钟极性类型枚举定义
 */
typedef enum
{
    SCPOL_INACTIVE_HIGH = 0x00,
    SCPOL_INACTIVE_LOW = 0x01
} ssi_scpol_t;
/**
 * @brief SSI 模块TMOD串行通信的传输方式类型枚举定义
 */
typedef enum
{
    TMOD_TX_AND_RX = 0x00,
    TMOD_TX_ONLY = 0x01,
    TMOD_RX_ONLY = 0x02,
    TMOD_EEPROM_READ = 0x03
} ssi_tmod_t;
/**
 * @brief SSI 模块SRL移位寄存器模式类型枚举定义
 */
typedef enum
{
    SRL_NORMAL_MODE = 0x00,
    SRL_TESTING_MODE = 0x01
} ssi_srl_t;
/**
 *  @brief  SSI 模块SSTE片选切换类型枚举定义
 *
 */
typedef enum
{
    TOGGLE_DISABLE = 0x00,
    TOGGLE_EN = 0x01
} ssi_sste_t;
/**
 * @brief SSI 模块CFS控制框架大小类型（Microwire 帧格式）枚举定义
 */
typedef enum
{
    CFS_01_BIT = 0x00,
    CFS_02_BIT = 0x01,
    CFS_03_BIT = 0x02,
    CFS_04_BIT = 0x03,
    CFS_05_BIT = 0x04,
    CFS_06_BIT = 0x05,
    CFS_07_BIT = 0x06,
    CFS_08_BIT = 0x07,
    CFS_09_BIT = 0x08,
    CFS_10_BIT = 0x09,
    CFS_11_BIT = 0x0a,
    CFS_12_BIT = 0x0b,
    CFS_13_BIT = 0x0c,
    CFS_14_BIT = 0x0d,
    CFS_15_BIT = 0x0e,
    CFS_16_BIT = 0x0f
} ssi_cfs_t;
/**
 * @brief SSI 模块FORMAT帧格式类型枚举定义
 */
typedef enum
{
    FORMAT_STD_MODE = 0x00,
    FORMAT_DUAL_MODE = 0x01,
    FORMAT_QUAD_MODE = 0x02
} ssi_format_t;
/**
 * @brief SSI 模块TRANS_TYPE 地址和指令传输格式类型枚举定义
 */
typedef enum
{
    TT0 = 0x00,
    TT1 = 0x01,
    TT2 = 0x02,
    TT3 = 0x03
} ssi_trans_t;
/**
 * @brief  SSI 模块ADDR_L XIP地址长度类型枚举定义
 */
typedef enum
{
    ADDR_L0 = 0x00,
    ADDR_L4 = 0x01,
    ADDR_L8 = 0x02,
    ADDR_L12 = 0x03,
    ADDR_L16 = 0x04,
    ADDR_L20 = 0x05,
    ADDR_L24 = 0x06,
    ADDR_L28 = 0x07,
    ADDR_L32 = 0x08,
    ADDR_L36 = 0x09,
    ADDR_L40 = 0x0a,
    ADDR_L44 = 0x0b,
    ADDR_L48 = 0x0c,
    ADDR_L52 = 0x0d,
    ADDR_L56 = 0x0e,
    ADDR_L60 = 0x0f
} ssi_address_t;

/**
 * @brief SSI 模块INST_L 双线/四线模式指令长度类型枚举定义
 */
typedef enum
{
    INST_L0 = 0x00,
    INST_L4 = 0x01,
    INST_L8 = 0x02,
    INST_L16 = 0x03
} ssi_instruction_t;

/**
 * @brief SSI 模块CLK_STRETCH 时钟扩展功能类型枚举定义
 */
typedef enum
{
    CLK_STRETCH_DISABLE = 0x00,
    CLK_STRETCH_ENABLE = 0x01
} ssi_clk_stretch_t;

/**
 *  @brief SSI 模块参数结构体类型结构体定义
 *
 */
typedef struct
{
    uint8_t ssi_id; // 1,2,3
    uint8_t sys_div;
    uint8_t is_qpi_mode;     // 当前是否处于QPI模式
    uint16_t std_baud_rate;  // 波特率设置
    uint16_t quad_baud_rate; // 波特率设置
    uint32_t rx_sample_delay;
    uint8_t cmd;               // 当前操作首指令
    uint32_t value;            // 当前操作次命令或数据
    uint8_t is_mask_interrupt; // 是否屏蔽中断
    uint8_t program_mode;      // 编程模式，是否DMA
    uint32_t addr;             // 擦除编程的起始地址
    uint16_t len;              // 编程长度
    uint32_t buf;              // 编程buf
    uint32_t delay;            // 操作完延时
    uint32_t timeout;          // 等待操作超时操作
    uint8_t  isfouraddr;     //是否使用4byte地址
    uint8_t  dummyvalue ;     // bit[7:6]: DC value,  bit[4:0]: wait cycle
} ssi_para_t;

/**
 *  @brief  SSI 模块操作函数指针结构体定义
 *
 */
typedef struct
{
    uint8_t (*xip_sys_clk_switch)(ssi_para_t *p_ssi_para);
    void (*ssi_open_xip)(ssi_para_t *p_ssi_para);
    void (*ssi_close_xip)(ssi_para_t *p_ssi_para);
    uint8_t (*xip_enter_qpi)(ssi_para_t *p_ssi_para);
    uint8_t (*xip_exit_qpi)(ssi_para_t *p_ssi_para);
    uint8_t (*ssi_flash_erase)(ssi_para_t *p_ssi_para);
    uint8_t (*ssi_flash_program)(ssi_para_t *p_ssi_para);
    uint8_t (*xip_flash_erase)(ssi_para_t *p_ssi_para);
    uint8_t (*xip_flash_program)(ssi_para_t *p_ssi_para);
} ssi_ops_func_t;

/**
 *  @brief SSI 模块读写数据/指令类型结构体定义
 *
 */
typedef enum
{
    CMD_READ = 0,
    CMD_WRITE = 1,
    DATA_READ = 2,
    DATA_WRITE = 3
} qpi_opt_mode_t;

/**
 *  @brief SSI 模块DMA传输数据宽度类型枚举定义
 *
 */
typedef enum
{
    WIDTH_B = 0,
    WIDTH_W = 1
} ssi_psram_dma_trans_t;

/**
 *  @brief SSI 模块使能/禁能枚举定义
 *
 */
typedef enum
{
    SSI_DIS = 0,
    SSI_EN = 1
} ssi_en_dis_t;

/**
 *  @brief  SSI 模块状态0/1标志类型枚举定义
 *
 */
typedef enum
{
    SSI_FLAG_0 = 0,
    SSI_FLAG_1 = 1
} ssi_flag_t;

// 函数声明
uint8_t drv_ssi_get_ssi_id(uint32_t addr);
uint8_t drv_ssi_get_xip_state(uint32_t addr);

uint8_t drv_xip_flash_erase(uint32_t addr);
uint8_t drv_xip_flash_program(uint32_t addr, uint8_t *p_buff, uint32_t len);

status_t drv_ssi_get_flag(reg_ssi_t *p_ssi, ssi_flag_index_t flag_index, uint8_t *pflag);
status_t drv_ssi_wait_flag_timeout(reg_ssi_t *p_ssi, ssi_flag_index_t index, uint8_t status, uint32_t timeout);

void drv_ssitx_set_axidmaen(reg_ssi_t *p_ssi);
void drv_ssirx_set_axidmaen(reg_ssi_t *p_ssi);

void drv_ssi_struct_init(ssi_init_t *pinit);
status_t drv_ssi_deinit(reg_ssi_t *p_ssi);
void drv_ssi_cmd(reg_ssi_t *p_ssi, ssi_en_dis_t state);
status_t drv_ssi_initt(reg_ssi_t *p_ssi, ssi_init_t *pinit, uint32_t timeout);

void drv_ssi_xip_init(uint8_t ssi_id);

void drv_open_xip(uint8_t ssi_id);
void drv_close_xip(uint8_t ssi_id);

void drv_ssi_flash_erase(reg_ssi_t *p_ssi,uint32_t addr);

uint8_t drv_ssi_flash_program( uint32_t addr, uint8_t *buf,uint32_t num);
void drv_ssi_flash_read(reg_ssi_t *p_ssi,uint32_t addr, uint8_t *buf, int num);
#ifdef __cplusplus
}
#endif

#endif
