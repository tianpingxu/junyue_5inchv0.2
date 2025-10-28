/**
 * @file sdio_reg.h
 * @author Product Application Department
 * @brief  SDIO 模块寄存器配置文件
 * @version V1.0
 * @date 2025-03-03
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef _SDIO_REG_H_
#define _SDIO_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
#include "cpm_drv.h"
    
// 全局变量定义
#define SD_EMMC_HOST_BASE (0x50000000)

#define _SBF(f, v)        ((v) << (f))
#define BIT_X(x) (1 << (x))

#define SDMMC_CTRL (SD_EMMC_HOST_BASE + 0x00)
#define SDMMC_PWREN (SD_EMMC_HOST_BASE + 0x04)
#define SDMMC_CLKDIV (SD_EMMC_HOST_BASE + 0x08)
#define SDMMC_CLKSRC (SD_EMMC_HOST_BASE + 0x0C)
#define SDMMC_CLKENA (SD_EMMC_HOST_BASE + 0x10)
#define SDMMC_TMOUT (SD_EMMC_HOST_BASE + 0x14)
#define SDMMC_CTYPE (SD_EMMC_HOST_BASE + 0x18)
#define SDMMC_BLKSIZ (SD_EMMC_HOST_BASE + 0x1C)
#define SDMMC_BYTCNT (SD_EMMC_HOST_BASE + 0x20)
#define SDMMC_INTMASK (SD_EMMC_HOST_BASE + 0x24)
#define SDMMC_CMDARG (SD_EMMC_HOST_BASE + 0x28)
#define SDMMC_CMD (SD_EMMC_HOST_BASE + 0x2C)
#define SDMMC_RESP0 (SD_EMMC_HOST_BASE + 0x30)
#define SDMMC_RESP1 (SD_EMMC_HOST_BASE + 0x34)
#define SDMMC_RESP2 (SD_EMMC_HOST_BASE + 0x38)
#define SDMMC_RESP3 (SD_EMMC_HOST_BASE + 0x3C)
#define SDMMC_MINTSTS (SD_EMMC_HOST_BASE + 0x40)
#define SDMMC_RINTSTS (SD_EMMC_HOST_BASE + 0x44)
#define SDMMC_STATUS (SD_EMMC_HOST_BASE + 0x48)
#define SDMMC_FIFOTH (SD_EMMC_HOST_BASE + 0x4C)
#define SDMMC_CDETECT (SD_EMMC_HOST_BASE + 0x50)
#define SDMMC_WRTPRT (SD_EMMC_HOST_BASE + 0x54)
#define SDMMC_GPIO (SD_EMMC_HOST_BASE + 0x58)
#define SDMMC_TCBCNT (SD_EMMC_HOST_BASE + 0x5C)
#define SDMMC_TBBCNT (SD_EMMC_HOST_BASE + 0x60)
#define SDMMC_DEBNCE (SD_EMMC_HOST_BASE + 0x64)
#define SDMMC_USRID (SD_EMMC_HOST_BASE + 0x68)
#define SDMMC_VERID (SD_EMMC_HOST_BASE + 0x6C)
#define SDMMC_HCON (SD_EMMC_HOST_BASE + 0x70)
#define SDMMC_UHS_REG (SD_EMMC_HOST_BASE + 0x74)
#define SDMMC_RST_N (SD_EMMC_HOST_BASE + 0x78)
#define SDMMC_BMOD (SD_EMMC_HOST_BASE + 0x80)
#define SDMMC_PLDMND (SD_EMMC_HOST_BASE + 0x84)
// #define SDMMC_DBADDR            (SD_EMMC_HOST_BASE +0x88)
#define SDMMC_DBADDRL (SD_EMMC_HOST_BASE + 0x88)
#define SDMMC_DBADDRU (SD_EMMC_HOST_BASE + 0x8C)
#define SDMMC_IDSTS (SD_EMMC_HOST_BASE + 0x90)
#define SDMMC_IDINTEN (SD_EMMC_HOST_BASE + 0x94)
// #define SDMMC_DSCADDR            (SD_EMMC_HOST_BASE +0x94)
#define SDMMC_DSCADDRL (SD_EMMC_HOST_BASE + 0x98)
#define SDMMC_DSCADDRU (SD_EMMC_HOST_BASE + 0x9C)
// #define SDMMC_BUFADDR                (SD_EMMC_HOST_BASE +0x98)
#define SDMMC_BUFADDRL (SD_EMMC_HOST_BASE + 0xA0)
#define SDMMC_BUFADDRU (SD_EMMC_HOST_BASE + 0xA4)
#define SDMMC_CARDTHRCTL (SD_EMMC_HOST_BASE + 0x100)
#define SDMMC_BACK_END_POWER (SD_EMMC_HOST_BASE + 0x104)
#define SDMMC_UHS_EXT (SD_EMMC_HOST_BASE + 0x108)
#define SDMMC_EMMC_DDR (SD_EMMC_HOST_BASE + 0x10C)
#define SDMMC_ENABLE_SHIFT (SD_EMMC_HOST_BASE + 0x110)
#define SDMMC_DATA(x) (x)
#define SDMMC_FIFO_DATA (SD_EMMC_HOST_BASE + 0x200)
#define DATA_OFFSET 0x200

// SDMMC_CTRL 0x00: Control register defines
#define SDMMC_CTRL_USE_IDMAC BIT_X(25)
#define SDMMC_CTRL_EN_OD BIT_X(24)
#define SDMMC_CTRL_CEATA_INT_EN BIT_X(11)
#define SDMMC_CTRL_SEND_AS_CCSD BIT_X(10)
#define SDMMC_CTRL_SEND_CCSD BIT_X(9)
#define SDMMC_CTRL_ABRT_READ_DATA BIT_X(8)
#define SDMMC_CTRL_SEND_IRQ_RESP BIT_X(7)
#define SDMMC_CTRL_READ_WAIT BIT_X(6)
#define SDMMC_CTRL_DMA_ENABLE BIT_X(5)
#define SDMMC_CTRL_INT_ENABLE BIT_X(4)
#define SDMMC_CTRL_DMA_RESET BIT_X(2)
#define SDMMC_CTRL_FIFO_RESET BIT_X(1)
#define SDMMC_CTRL_RESET BIT_X(0)

// SDMMC_CLKENA 0x010: Clock Enable register defines
#define SDMMC_CLKEN_LOW_PWR (16)
#define SDMMC_CLKEN_ENABLE (0)

// SDMMC_TMOUT 0x014: time-out register defines
#define SDMMC_TMOUT_DATA(n) _SBF(8, (n))
#define SDMMC_TMOUT_DATA_MSK 0xFFFFFF00
#define SDMMC_TMOUT_RESP(n) ((n) & 0xFF)
#define SDMMC_TMOUT_RESP_MSK 0xFF

// SDMMC_CTYPE 0x18
#define SDMMC_CTYPE_8BIT BIT_X(16)
#define SDMMC_CTYPE_4BIT BIT_X(0)
#define SDMMC_CTYPE_1BIT 0

// SDMMC_INTMASK 0x24
// SDMMC_MINTSTS 0x40
// SDMMC_RINTSTS 0x44 Interrupt status & mask register defines
#define SDMMC_INT_SDIO(n) BIT_X(16 + (n))
#define SDMMC_INT_EBE BIT_X(15)
#define SDMMC_INT_ACD BIT_X(14)
#define SDMMC_INT_SBE BIT_X(13)
#define SDMMC_INT_BCI BIT(13)
#define SDMMC_INT_HLE BIT_X(12)
#define SDMMC_INT_FRUN BIT_X(11)
#define SDMMC_INT_HTO BIT_X(10)
#define SDMMC_INT_VOLT_SWITCH BIT_X(10)
// #define SDMMC_INT_DTO            BIT_X(9)
#define SDMMC_INT_DRTO BIT_X(9)
#define SDMMC_INT_RTO BIT_X(8)
#define SDMMC_INT_DCRC BIT_X(7)
#define SDMMC_INT_RCRC BIT_X(6)
#define SDMMC_INT_RXDR BIT_X(5)
#define SDMMC_INT_TXDR BIT_X(4)
#define SDMMC_INT_DATA_OVER BIT_X(3)
#define SDMMC_INT_CMD_DONE BIT_X(2)
#define SDMMC_INT_RESP_ERR BIT_X(1)
#define SDMMC_INT_CD BIT_X(0)
#define SDMMC_INT_ERROR 0xbfc2

// SDMMC_CMD 0x2C: Command register defines
#define SDMMC_CMD_START BIT_X(31)
#define SDMMC_CMD_USE_HOLD 0 // BIT_X(29)
#define SDMMC_CMD_VOLT_SWITCH BIT_X(28)
#define SDMMC_CMD_CCS_EXP BIT_X(23)
#define SDMMC_CMD_CEATA_RD BIT_X(22)
#define SDMMC_CMD_UPD_CLK BIT_X(21)
#define SDMMC_CMD_INIT BIT_X(15)
#define SDMMC_CMD_STOP BIT_X(14)
#define SDMMC_CMD_PRV_DAT_WAIT BIT_X(13)
// #define SDMMC_CMD_SEND_STOP    BIT_X(12)//---------
#define SDMMC_CMD_SEND_AUTO_STOP BIT_X(12) //
#define SDMMC_CMD_STRM_MODE BIT_X(11)
#define SDMMC_CMD_DAT_WR BIT_X(10)
#define SDMMC_CMD_DAT_EXP BIT_X(9)
#define SDMMC_CMD_RESP_CRC BIT_X(8)
#define SDMMC_CMD_RESP_LONG BIT_X(7)
#define SDMMC_CMD_RESP_EXP BIT_X(6)

#define SDMMC_CMD_INDX(n) ((n) & 0x3F)
//  Status register defines
#define SDMMC_GET_FCNT(x) (((x) >> 17) & 0x1FFF) // fifo_count

// SDMMC_CDETECT 0x50: Card Detect Register
#define SDMMC_CDETECT_CARD_PRESENT 0

// SDMMC_RST_N 0x78: Hardware reset
#define SDMMC_RST_SLOT_0 0xFFFFFFFE
#define SDMMC_RST_SLOT_1 0xFFFFFFFD

// SDMMC_IDSTS 0x8C
// SDMMC_IDINTEN 0x90:  Internal DMAC interrupt defines
#define SDMMC_IDMAC_INT_AI BIT_X(9)
#define SDMMC_IDMAC_INT_NI BIT_X(8)
#define SDMMC_IDMAC_INT_CES BIT_X(5)
#define SDMMC_IDMAC_INT_DU BIT_X(4)
#define SDMMC_IDMAC_INT_FBE BIT_X(2)
#define SDMMC_IDMAC_INT_RI BIT_X(1) // Receive
#define SDMMC_IDMAC_INT_TI BIT_X(0) // Transmit

// SDMMC_BMOD 0x80
#define SDMMC_IDMAC_ENABLE BIT_X(7)
#define SDMMC_IDMAC_FB BIT_X(1)
#define SDMMC_IDMAC_SWRESET BIT_X(0)

#define SDMMC_GET_VERID(x) ((x) & 0xFFFF)

#define SDMMC_HCON_CARD_TYPE(n) (n & 0x00000001)
#define CARD_TYPE_MMC_ONLY 0
#define CARD_TYPE_SD_MMC 1
#define SDMMC_HCON_NUM_CARDS(n) (((n & 0x0000003E) >> 1) + 1)
#define SDMMC_HCON_H_BUS_TYPE(n) ((n & 0x00000040) >> 6)
#define H_BUS_TYPE_APB 0
#define H_BUS_TYPE_AHB 1
#define SDMMC_HCON_H_DATA_WIDTH(n) ((n & 0x00000380) >> 7)
#define H_DATA_WIDTH_16BIT 0
#define H_DATA_WIDTH_32BIT 1
#define H_DATA_WIDTH_64BIT 2
#define SDMMC_HCON_H_ADDR_WIDTH(n) (((n & 0x0000FC00) >> 10) + 1)
#define SDMMC_HCON_FIFO_RAM_INSIDE(n) ((n & 0x00200000) >> 21)
#define FIFO_RAM_OUTSIDE 0
#define FIFO_RAM_INSIDE 1
#define SDMMC_HCON_ADDR_CONFIG(n) ((n & 0x08000000) >> 27)
#define ADDR_CONFIG_32BIT 0
#define ADDR_CONFIG_64BIT 1

#define RESP_TIMEOUT 0x50000
#define SD_SLOT1 0
#define NUM_SLOTS 1
#define VALUE_RINTSTS *(volatile uint32_t *)(SD_EMMC_HOST_BASE + 0x44)
#define CMD0ARG_GO_IDLE_STATE 0x00000000
#define OCR_POWER_BUSY (0 << 31)
#define OCR_BUSY_Bit31 BIT_X(31)
#define OCR_S18A_Bit24 BIT_X(24)

// Card Threshold size; N depends on the FIFO size:
// N = 25, FIFO Size = 128, FIFO_DEPTH = FIFO_SIZE*2
#define FIFO_DEPTH 256
#define CARD_THRESHOLD 25
#define BLOCK_SIZE 512

#define SDIO_PowerState_OFF ((uint32_t)0x00000000)
#define SDIO_PowerState_ON ((uint32_t)0x00000003)

// 公式: div = source_clk / (target_clk * 2)
#define SYS_CLK 50000000
#define FPGA_CLKOUT_400kHz_DIV (SYS_CLK / (400000 * 2)) 
#define FPGA_CLKOUT_100kHz_DIV (SYS_CLK / (100000 * 2)) 
#define FPGA_CLKOUT_25MHz_DIV  (SYS_CLK / (25000000 * 2))  
#define FPGA_CLKOUT_50MHz_DIV  (SYS_CLK / (50000000 * 2))    
// #define FPGA_CLKOUT_100MHz_DIV  (SYS_CLK / (100000000 * 2))  

#define DWC_MSH_DATA_ERROR_FLAGS (SDMMC_INT_DRTO | SDMMC_INT_DCRC | SDMMC_INT_HTO | SDMMC_INT_SBE | SDMMC_INT_EBE)
#define DWC_MSH_CMD_ERROR_FLAGS (SDMMC_INT_RTO | SDMMC_INT_RCRC | SDMMC_INT_RESP_ERR)
#define DWC_MSH_ERROR_FLAGS (DWC_MSH_DATA_ERROR_FLAGS | \
                             DWC_MSH_CMD_ERROR_FLAGS |  \
                             SDMMC_INT_HLE)

#define DESCRIPTION_ADDR (0x20008000 - 0x1000)

#define OWN (1 << 31)
#define ER (1 << 5)
#define SD_CH (1 << 4)
#define FS (1 << 3)
#define LD (1 << 2)
#define DIC (1 << 1)

#define _SBF(f, v) ((v) << (f))
#define BIT_X(x) (1 << (x))

/**
 * @brief SDIO 模块寄存器结构体定义
 */
typedef struct
{
    uint32_t card_type : 1;
    uint32_t num_card : 5;
    uint32_t h_bus_type : 1;
    uint32_t h_data_width : 3;
    uint32_t h_addr_width : 6;
    uint32_t dma_interface : 2;
    uint32_t dma_data_width : 3;
    uint32_t fifo_ram_inside : 1;
    uint32_t implement_hold_reg : 1;
    uint32_t set_clk_false_path : 1;
    uint32_t num_clk_divider : 2;
    uint32_t area_optimized : 1;
    uint32_t addr_config : 5;
} sdio_hcon_t;

#ifdef __cplusplus
}
#endif

#endif
