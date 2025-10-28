/**
 * @file usb_drv.h
 * @author Product application department
 * @brief  USB 模块驱动层头文件
 * @version V1.0
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __USB_DRV_H__
#define __USB_DRV_H__

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "status.h"
#include "interrupt.h"
#include "usb_reg.h"
#include "cpm_drv.h"
#include "iomacros.h"

// 全局变量定义
// #define USB_DMA                  //关闭此宏，USB将采用CPU方式通信
#define USB_FIFO_SIZE (0)
#define USB_FIFO_EP0_ADDR (0)
#define USB_FIFO_EP1_ADDR (USB_FIFO_EP0_ADDR + USB_FIFO_SIZE)
#define USB_FIFO_EP2_ADDR (USB_FIFO_EP1_ADDR + USB_FIFO_SIZE)
#define USB_FIFO_EP3_ADDR (USB_FIFO_EP2_ADDR + USB_FIFO_SIZE)
#define USB_FIFO_EP4_ADDR (USB_FIFO_EP3_ADDR + USB_FIFO_SIZE)
#define USB_FIFO_EP5_ADDR (USB_FIFO_EP4_ADDR + USB_FIFO_SIZE)
#define USB_FIFO_EP6_ADDR (USB_FIFO_EP5_ADDR + USB_FIFO_SIZE)
#define USB_FIFO_EP7_ADDR (USB_FIFO_EP6_ADDR + USB_FIFO_SIZE)

// bulk transfer packet size
#define USB_MAX_PACKET_SIZE_V20 0x200
#define USB_MAX_PACKET_SIZE_V11 0x40
#define USB_MAX_PACKET_SIZE_EP0 0x40

#define CONTROL_EP 0
#define INDEX_EP1 1
#define INDEX_EP2 2
#define INDEX_EP3 3
#define INDEX_EP4 4
#define INDEX_EP5 5
#define INDEX_EP6 6
#define INDEX_EP7 7

#define BULKIN_EP INDEX_EP1
#define BULKOUT_EP INDEX_EP2
#define BULKIN_INT INDEX_EP3

/**
 * @brief USB 模块包枚举定义
 *
 */
enum
{
    PACKET_MID,
    PACKET_END = 1,
};
/**
 * @brief USB 模块版本协议枚举定义
 *
 */
typedef enum
{
    USB_VERSION_11 = 0,
    USB_VERSION_20,
} usbcversion_t;
/**
 * @brief USB 模块句柄结构体定义
 *
 */
typedef struct
{
    uint8_t addr;
    uint8_t data;
} reg_usbphy_cfg_t;
/**
 * @brief USB 模块句柄结构体定义
 *
 */
typedef struct
{
    uint8_t osc;
    usbcversion_t version;
    uint8_t Ep0DataStage;
    uint8_t vbus_mode;
    uint8_t dma_mode;
    uint8_t reg_num;
    reg_usbphy_cfg_t reg_cfg[6];
} usbc_handle_t;
extern __IO uint16_t gUSBC_PacketSize;
extern __IO uint32_t gUSBC_NewAddress;
extern __IO uint8_t gUSBC_RxINT_Flag;
extern __IO uint8_t gUSBC_TxINT_Flag;
extern __IO uint8_t gUSBC_DMA_mode;
// 函数声明
void drv_usbc_init(usbc_handle_t *husb);
void drv_disconnect(void);
void drv_usbc_connect(void);
void drv_usbc_setfifoaddr(uint32_t FIFOAddr, uint8_t mode);
void drv_usbc_clearrx(void);
void drv_usbc_settx(void);
void drv_usbc_readepxdata(uint8_t usbcEPx, uint8_t *src, uint16_t Length);
void drv_usbc_writeepxdata(uint8_t usbcEPx, uint8_t *dest, uint16_t Length);
void drv_usbc_readepxdatabydma(uint8_t usbcEPx, uint8_t *src, uint16_t Length);
void drv_usbc_writeepxdatabydma(uint8_t usbcEPx, uint8_t *dest, uint16_t Length);
void drv_usbc_ep0sendstall(void);
void drv_usbc_epxsendstall(uint8_t EPx);
void drv_usbc_writeep0data(uint8_t *src, uint16_t Length, uint8_t Status);
uint16_t drv_usbc_receivedata(uint8_t usbcEPx, uint8_t *buf);
uint16_t drv_usbc_ep0senddata(uint16_t requestLen, uint8_t *databuf, uint16_t dataLen);
void drv_usbc_settxsize(uint16_t Size);
uint8_t drv_usbc_senddata(uint8_t usbcEPx, uint8_t *buf, uint16_t len);
void drv_drv_usbc_Irqhandler(void);
extern void (*drv_usbc_varinit_callback)(void);
extern void (*drv_usbc_ep0handler_callback)(void);
extern void (*drv_drv_usbc_Irq_callback)(void);
uint8_t drv_usbc_senddatanull(uint8_t usbcEPx);
void drv_usbc_suspend_lowpower(void);
void drv_usbc_Irq(void);

#ifdef __cplusplus
}
#endif

#endif
