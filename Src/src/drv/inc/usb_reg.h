/**
 * @file usb_reg.h
 * @author Product application department
 * @brief  USB 模块寄存器配置文件
 * @version  V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __USB_REG_H_
#define __USB_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
    
// 全局变量定义
#define USBC_BASE_ADDR (0x4004C000)

#define USBC_INDEXED_ADDR (USBC_BASE_ADDR + 0x10)
#define USBC_FIFOCFG_ADDR (USBC_BASE_ADDR + 0x60)
#define USBC_FIFOREG_ADDR (USBC_BASE_ADDR + 0x20)
#define USBC_DMACCFG_ADDR (USBC_BASE_ADDR + 0x200)
#define USBC_PHYREG_ADDR (USBC_BASE_ADDR + 0x800)

#define gUSBC_CommonReg ((usbccommon_t *)(USBC_BASE_ADDR))
#define gUSBC_IndexReg ((usbcindexed_t *)USBC_INDEXED_ADDR)
#define gUSBC_ControlReg ((usbcfifocfg_t *)USBC_FIFOCFG_ADDR)
#define gUSBC_FIFOReg ((reg_usbcfifo_t *)USBC_FIFOREG_ADDR)
#define gUSBC_DMAReg ((usbcdmacfg_t *)USBC_DMACCFG_ADDR)
#define gUSBC_PHYReg ((reg_usbcphy_t *)USBC_PHYREG_ADDR)

#define USB_POWER_ENAB_SUSP (1 << 0)
#define USB_POWER_SUSP_MODE (1 << 1)
#define USB_POWER_RESUME (1 << 2)
#define USB_POWER_RESET (1 << 3)
#define USB_POWER_HS_MODE (1 << 4)
#define USB_POWER_HS_ENAB (1 << 5)
#define USB_POWER_SOFT_CONN (1 << 6)
#define USB_POWER_ISO_UPDATE (1 << 7)

// usb common interrupt number
#define USB_INTERRUPT_SUSPEND (1 << 0)
#define USB_INTERRUPT_RESUME (1 << 1)
#define USB_INTERRUPT_RESET (1 << 2)
#define USB_INTERRUPT_SOF (1 << 3)
#define USB_INTERRUPT_CONNECT (1 << 4)
#define USB_INTERRUPT_DISCON (1 << 5)
#define USB_INTERRUPT_SESSREQ (1 << 6)
#define USB_INTERRUPT_VBUSERR (1 << 7)

#define USB_TESTMODE_SE0NAK (1 << 0)
#define USB_TESTMODE_TESTJ (1 << 1)
#define USB_TESTMODE_TESTK (1 << 2)
#define USB_TESTMODE_TESTPACKET (1 << 3)

// usb tx interrupt number
#define USB_INTERRUPT_EP0 (1 << 0)
#define USB_TX_INTERRUPT_EP1 (1 << 1)
#define USB_TX_INTERRUPT_EP2 (1 << 2)
#define USB_TX_INTERRUPT_EP3 (1 << 3)
#define USB_TX_INTERRUPT_EP4 (1 << 4)
#define USB_TX_INTERRUPT_EP5 (1 << 5)
#define USB_TX_INTERRUPT_EP6 (1 << 6)
#define USB_TX_INTERRUPT_EP7 (1 << 7)

// Usb Rx Interrupt Number
#define USB_RX_INTERRUPT_EP0 (1 << 0)
#define USB_RX_INTERRUPT_EP1 (1 << 1)
#define USB_RX_INTERRUPT_EP2 (1 << 2)
#define USB_RX_INTERRUPT_EP3 (1 << 3)
#define USB_RX_INTERRUPT_EP4 (1 << 4)
#define USB_RX_INTERRUPT_EP5 (1 << 5)
#define USB_RX_INTERRUPT_EP6 (1 << 6)
#define USB_RX_INTERRUPT_EP7 (1 << 7)
// Device CSR0 Bit Define
#define DEV_CSR0_RXPKTRDY (1 << 0)
#define DEV_CSR0_TXPKTRDY (1 << 1)
#define DEV_CSR0_SENTSTALL (1 << 2)
#define DEV_CSR0_DATAEND (1 << 3)
#define DEV_CSR0_SETUPEND (1 << 4)
#define DEV_CSR0_SENDSTALL (1 << 5)
#define DEV_CSR0_SERVICE_RXPKTRDY (1 << 6)
#define DEV_CSR0_SERVICE_SETUPEND (1 << 7)

// TX Register Bit Low as Device
#define DEV_TXCSR_TXPKTRDY (1 << 0)
#define DEV_TXCSR_FIFO_NOT_EMPTY (1 << 1)
#define DEV_TXCSR_UNDER_RUN (1 << 2)
#define DEV_TXCSR_FLUSH_FIFO (1 << 3)
#define DEV_TXCSR_SEND_STALL (1 << 4)
#define DEV_TXCSR_SENT_SATLL (1 << 5)
#define DEV_TXCSR_CLR_DATA_TOG (1 << 6)
#define DEV_TXCSR_INCOMP_TX (1 << 7)

// TX Register Bit High as Device
#define DEV_TXCSR_DMAMODE (1 << 2)
#define DEV_TXCSR_FRC_DATA_TOG (1 << 3)
#define DEV_TXCSR_DMA_ENAB (1 << 4)
#define DEV_TXCSR_TXMODE (1 << 5)
#define DEV_TXCSR_ISO (1 << 6)
#define DEV_TXCSR_AUTO_SET (1 << 7)

// RX Register Bit Low as Device
#define DEV_RXCSR_RXPKTRDY (1 << 0)
#define DEV_RXCSR_FIFOFULL (1 << 1)
#define DEV_RXCSR_FLUSH_FIFO (1 << 4)
#define DEV_RXCSR_SEND_STALL (1 << 5)
#define DEV_RXCSR_SENT_STALL (1 << 6)
#define DEV_RXCSR_CLR_DATA_TOG (1 << 7)

// RX Register Bit High as Device
#define DEV_RXCSR_INCOMP_RX (1 << 0)
#define DEV_RXCSR_DMAMODE (1 << 3)
#define DEV_RXCSR_DISNYET (1 << 4)
#define DEV_RXCSR_DMA_ENAB (1 << 5)
#define DEV_RXCSR_ISO (1 << 6)
#define DEV_RXCSR_AUTOCLEAR (1 << 7)

#define DEV_INTR_CHANNEL(n) (1 << (n - 1))

// dma cntl
#define DEV_CNTL_DMAEN (1 << 0)
#define DEV_CNTL_DIRECTION_READ (1 << 1)
#define DEV_CNTL_DMAMODE (1 << 2)
#define DEV_CNTL_INTERE (1 << 3)
#define DEV_CNTL_EP(x) ((x & 0x07) << 4)
#define DEV_CNTL_BUSERROR (1 << 8)
#define DEV_CNTL_BURSTMODE(x) ((x & 0x03) << 9)

/**
 * @brief USB 模块寄存器结构体定义
 *
 */

typedef struct
{
    __IO uint8_t FADDRR;
    __IO uint8_t UCSR;

    __IO uint8_t INTRTX_L;
    __IO uint8_t INTRTX_H;

    __IO uint8_t INTRRX_L;
    __IO uint8_t INTRRX_H;
    __IO uint8_t INTRTXE_L;
    __IO uint8_t INTRTXE_H;
    __IO uint8_t INTRRXE_L;
    __IO uint8_t INTRRXE_H;

    __IO uint8_t INTRUSB;
    __IO uint8_t INTRUSBE;
    __IO uint8_t FNUMR_L;
    __IO uint8_t FNUMR_H;

    __IO uint8_t EINDEX;
    __IO uint8_t TSTMODE;
} usbccommon_t;

/**
 * @brief USB 模块Indexed结构体定义
 *
 */
typedef struct
{
    __IO uint8_t TXMAXP_L;
    __IO uint8_t TXMAXP_H;
    union
    {
        __IO uint8_t E0CSR_L;
        __IO uint8_t TXCSR_L;
    };
    union
    {
        __IO uint8_t E0CSR_H;
        __IO uint8_t TXCSR_H;
    };
    __IO uint8_t RXMAXP_L;
    __IO uint8_t RXMAXP_H;
    __IO uint8_t RXCSR_L;
    __IO uint8_t RXCSR_H;
    union
    {
        __IO uint8_t E0COUNTR_L;
        __IO uint8_t RXCOUNTR_L;
    };
    union
    {
        __IO uint8_t E0COUNTR_H;
        __IO uint8_t RXCOUNTR_H;
    };
    __IO uint8_t TXTYPE;
    union
    {
        __IO uint8_t NAKLIMIT0;
        __IO uint8_t TXINTERVAL;
    };
    __IO uint8_t RXTYPE;
    __IO uint8_t RXINTERVAL;
} usbcindexed_t;

/**
 * @brief USB 模块 FIFO 配置寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint8_t OTGCTRL;
    __IO uint8_t RESERVED;
    __IO uint8_t TXFIFOSZ;
    __IO uint8_t RXFIFOSZ;
    __IO uint8_t TX_fifoadd_L;
    __IO uint8_t TX_fifoadd_H;
    __IO uint8_t RX_fifoadd_L;
    __IO uint8_t RX_fifoadd_H;
} usbcfifocfg_t;

/**
 * @brief USB 模块FIFO寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t FIFO_ENDPOINTx[15];
} reg_usbcfifo_t;

/**
 * @brief USB 模块DMA 结构体定义
 *
 */
typedef struct
{
    __IO uint32_t DMA_CNTL;
    __IO uint32_t DMA_ADDR;
    __IO uint32_t DMA_COUNT;
    __IO uint32_t RESERVED;
} reg_usbdma_t;

/**
 * @brief USB 模块DMA 寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t DMA_INTR;
    reg_usbdma_t USB_DMAReg[7];
} usbcdmacfg_t;

/**
 * @brief USB 模块PHY寄存器结构体定义
 *
 */
typedef struct
{
    __IO uint32_t PHY_ADDR;
    __IO uint32_t PHY_WDATA;
    __IO uint32_t PHY_WREN;
    __IO uint32_t PHY_RDEN;
    __IO uint32_t PHY_RDATA;
} reg_usbcphy_t;


#ifdef __cplusplus
}
#endif

#endif
