/**
 * @file usb_drv.c
 * @author Product application department
 * @brief  USB 模块驱动层
 * @version V1.0
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
 
// 头文件包含
#include "usb_drv.h"

// 全局变量定义
#define SSI1_ID 1

__IO uint16_t gUSBC_PacketSize;
__IO uint32_t gUSBC_NewAddress;
__IO uint8_t gUSBC_RxINT_Flag;
__IO uint8_t gUSBC_TxINT_Flag;

uint8_t g_enumeration = 0;
uint8_t g_flag_suspend = 0;
uint8_t g_flag_resume = 0;

static __IO uint8_t g_Ep0DataStage;
static __IO uint8_t g_Version;         // USB版本号
static __IO uint8_t gUSBC_SuspendMode; // 支持挂起标志位
static __IO uint8_t gUSBC_DMAINTR;     // DMA传输中断标志
__IO uint8_t gUSBC_DMA_mode;           // DMA传输模式

static const uint32_t USB_FIFO_TAB[8] =
{
        USB_FIFO_EP0_ADDR,
        USB_FIFO_EP1_ADDR,
        USB_FIFO_EP2_ADDR,
        USB_FIFO_EP3_ADDR,
        USB_FIFO_EP4_ADDR,
        USB_FIFO_EP5_ADDR,
        USB_FIFO_EP6_ADDR,
        USB_FIFO_EP7_ADDR,
};
void (*drv_usbc_varinit_callback)(void);


// 函数定义
/**
 * @brief USB 模块读寄存器函数
 *
 * @param phy_addr 寄存器地址
 * @return uint32_t
 */
uint32_t drv_phy_reg_read(uint32_t phy_addr)
{
    uint32_t phy_data;
    gUSBC_PHYReg->PHY_ADDR = phy_addr;
    gUSBC_PHYReg->PHY_RDEN = 0x1;
    gUSBC_PHYReg->PHY_RDEN = 0x0;
    phy_data = gUSBC_PHYReg->PHY_RDATA;
    return phy_data;
}

/**
 * @brief USB 模块写寄存器函数
 * @param phy_addr 寄存器地址
 * @param phy_data 寄存器值
 */
void drv_phy_reg_write(uint32_t phy_addr, uint32_t phy_data)
{
    gUSBC_PHYReg->PHY_ADDR = phy_addr;
    gUSBC_PHYReg->PHY_WDATA = phy_data;
    gUSBC_PHYReg->PHY_WREN = 0x1;
    gUSBC_PHYReg->PHY_WREN = 0x0;
}

/**
 * @brief USB 模块初始化函数
 * @param husb USB初始化句柄
 */
void drv_usbc_init(usbc_handle_t *husb)
{
    uint32_t i;

    g_Ep0DataStage = husb->Ep0DataStage;

    g_Version = husb->version;

    gUSBC_DMA_mode = husb->dma_mode;

    if (husb->version == USB_VERSION_20)
    {
        gUSBC_PacketSize = USB_MAX_PACKET_SIZE_V20;
    }
    else
    {
        gUSBC_PacketSize = USB_MAX_PACKET_SIZE_V11;
    }

    drv_usbc_varinit_callback();

    husb->vbus_mode = 0;

    gUSBC_SuspendMode = 1;

    gUSBC_DMAINTR = 0;

    drv_cpm_usbphyinit(husb->osc);

    if (husb->vbus_mode == 0)
    {
        CCM->PHYPA |= 0x0e00; /*No VBUS*/
    }
    else
    {
        CCM->PHYPA &= ~0x0e00; /*Need VBUS*/
    }

    for (i = 0; i < husb->reg_num; i++)
    {
        drv_phy_reg_write(husb->reg_cfg[i].addr, husb->reg_cfg[i].data);
    }

    /* Setup USB register */
    // enable usb common interrupt
    // 0     1       2       3       4       5       6       7 (bit)
    // Susp  Resume  Reset   SOF     Conn    Discon  SessReq VBusErr
    gUSBC_CommonReg->INTRUSBE = USB_INTERRUPT_RESET |
                                USB_INTERRUPT_CONNECT |
                                USB_INTERRUPT_DISCON |
                                USB_INTERRUPT_SUSPEND |
                                USB_INTERRUPT_RESUME;

    // enable ep0 and ep1 tx interrupts,clear other tx interrupts
    gUSBC_CommonReg->INTRTXE_L = CONTROL_EP |
                                 (1 << BULKIN_EP) |
                                 (1 << BULKIN_INT);

    gUSBC_CommonReg->INTRRXE_L = (1 << BULKOUT_EP);

    // ensure ep0 control/status regesters appeare in the memory map.
    gUSBC_CommonReg->EINDEX = CONTROL_EP;

    drv_usbc_setfifoaddr(USB_FIFO_TAB[0], 0);

    if (g_Version == USB_VERSION_20)
    {
        gUSBC_CommonReg->UCSR = USB_POWER_SOFT_CONN | USB_POWER_HS_ENAB | USB_POWER_ENAB_SUSP;
    }
    else
    {
        gUSBC_CommonReg->UCSR = USB_POWER_SOFT_CONN | USB_POWER_ENAB_SUSP;
    }
    USB_IRQHandler_Callback = drv_drv_usbc_Irqhandler;
    NVIC_Init(3, 3, USBC_Irqn, 2);

    // From M31USB200SL040L IP spec
    // 1：OSCOUT is active in the suspend mode,In the suspend mode,USB PHY Current>8mA
    // 0：OSCOUT is powered down in the suspend mode,In the suspend mode,USB PHY Current<1mA
    //  set0x4004c900 bit12=0
    (*(uint32_t *)(0x4004c900)) &= ~(0x00001000);
    //=========================================================================
}

/**
 * @brief USB 模块断开函数
 * @param
 */
void drv_disconnect(void)
{
    gUSBC_CommonReg->UCSR &= ~USB_POWER_SOFT_CONN;
}
/**
 * @brief USB 模块连接函数
 *
 */
void drv_usbc_connect(void)
{
    gUSBC_CommonReg->UCSR |= USB_POWER_SOFT_CONN;
}

/**
 * @brief USB 模块设置FIFO的地址函数
 *
 * @param FIFOAddr FIFO的地址
 * @param mode 模式
 */
void drv_usbc_setfifoaddr(uint32_t FIFOAddr, uint8_t mode)
{
    if (mode == 0)
    {
        // reset to default fifo address
        gUSBC_ControlReg->TX_fifoadd_L = ((FIFOAddr >> 3) & 0x00FF);
        gUSBC_ControlReg->TX_fifoadd_H = ((FIFOAddr >> 11) & 0x00FF);
        gUSBC_ControlReg->RX_fifoadd_L = ((FIFOAddr >> 3) & 0x00FF);
        gUSBC_ControlReg->RX_fifoadd_H = ((FIFOAddr >> 11) & 0x00FF);
    }
    else if (mode == 1)
    {
        // Set Tx fifo Address
        gUSBC_ControlReg->TX_fifoadd_L = ((FIFOAddr >> 3) & 0x00FF);
        gUSBC_ControlReg->TX_fifoadd_H = ((FIFOAddr >> 11) & 0x00FF);
    }
    else if (mode == 2)
    {
        // Set Rx fifo Address
        gUSBC_ControlReg->RX_fifoadd_L = ((FIFOAddr >> 3) & 0x00FF);
        gUSBC_ControlReg->RX_fifoadd_H = ((FIFOAddr >> 11) & 0x00FF);
    }
}

/**
 * @brief USB 模块清除接收状态
 * @param
 */
void drv_usbc_clearrx(void)
{
    uint8_t ucReg = 0;

    ucReg = gUSBC_IndexReg->RXCSR_L;

    ucReg &= ~DEV_RXCSR_RXPKTRDY;

    gUSBC_IndexReg->RXCSR_L = ucReg;
}

/**
 * @brief USB 模块设置发送状态函数
 * @param
 */
void drv_usbc_settx(void)
{
    uint8_t ucReg = 0;

    ucReg = gUSBC_IndexReg->TXCSR_L;

    ucReg |= DEV_TXCSR_TXPKTRDY;

    gUSBC_IndexReg->TXCSR_L = ucReg;
}

/**
 * @brief USB 模块从endpointx 的fifo寄存器读取数据函数
 * @param usbcEPx 端口号
 * @param src 接收数据buff
 * @param Length 接收数据长度
 */
void drv_usbc_readepxdata(uint8_t usbcEPx, uint8_t *src, uint16_t Length)
{
    uint16_t i = 0;

    for (i = 0; i < Length; i++)
    {
        src[i] = _io_read8((uint32_t)&gUSBC_FIFOReg->FIFO_ENDPOINTx[usbcEPx]);
    }
}

/**
 * @brief USB 模块数据写到endpointx 的fifo寄存器函数
 *
 * @param usbcEPx 端口号
 * @param dest 要发送的数据buff
 * @param Length 发送的数据长度
 */
void drv_usbc_writeepxdata(uint8_t usbcEPx, uint8_t *dest, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++)
    {
        _io_write8((uint32_t)&gUSBC_FIFOReg->FIFO_ENDPOINTx[usbcEPx], dest[i]);
    }
}

/**
 * @brief USB 模块通过DMA从endpointx的FIFO寄存器中读取数据函数
 * @param usbcEPx 端口号
 * @param src 接收数据buff
 * @param Length 接收的数据长度
 */
void drv_usbc_readepxdatabydma(uint8_t usbcEPx, uint8_t *src, uint16_t Length)
{
    gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_ADDR = (uint32_t)src;
    gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_COUNT = Length;
    gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_CNTL = DEV_CNTL_DMAEN |
                                                     DEV_CNTL_EP(usbcEPx) |
                                                     DEV_CNTL_BURSTMODE(0);

    while (gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_CNTL & DEV_CNTL_DMAEN)
        ;
}

/**
 * @brief USB 模块通过DMA写数据到endpointx的FIFO寄存器中函数
 * @param usbcEPx 端口号
 * @param src 接收数据buff
 * @param Length 接收的数据长度
 */
void drv_usbc_writeepxdatabydma(uint8_t usbcEPx, uint8_t *dest, uint16_t Length)
{
    gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_ADDR = (uint32_t)dest;

    gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_COUNT = Length;

    gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_CNTL = DEV_CNTL_DMAEN |
                                                     DEV_CNTL_DIRECTION_READ |
                                                     DEV_CNTL_EP(usbcEPx) |
                                                     DEV_CNTL_BURSTMODE(0);
    while (gUSBC_DMAReg->USB_DMAReg[usbcEPx - 1].DMA_CNTL & DEV_CNTL_DMAEN)
        ;
}

/**
 * @brief USB 模块设置EP0空闲态函数
 *
 */
void drv_usbc_ep0sendstall(void)
{
    uint8_t ucReg = gUSBC_IndexReg->E0CSR_L;

    ucReg |= DEV_CSR0_SENDSTALL;

    gUSBC_IndexReg->E0CSR_L = ucReg;
}

/**
 * @brief USB 模块设置EPx位空闲态函数
 * @param EPx 端口号
 */
void drv_usbc_epxsendstall(uint8_t EPx)
{
    uint8_t ucReg;

    gUSBC_CommonReg->EINDEX = EPx;
    if (EPx == BULKIN_EP)
    {

        ucReg = gUSBC_IndexReg->TXCSR_L;

        ucReg |= DEV_TXCSR_SEND_STALL;

        gUSBC_IndexReg->TXCSR_L = ucReg;
    }
    else
    {
        ucReg = gUSBC_IndexReg->RXCSR_L;

        ucReg |= DEV_RXCSR_SEND_STALL;

        gUSBC_IndexReg->RXCSR_L = ucReg;
    }
}

/**
 * @brief USB 模块将数据写入到EPORT0的FIFO寄存器中，写完之后进入中断函数
 *
 * @param src 要发送的数据的起始地址
 * @param Length 要发送的数据长度
 * @param Status 包状态
 */
void drv_usbc_writeep0data(uint8_t *src, uint16_t Length, uint8_t Status)
{
    uint8_t ucReg = gUSBC_IndexReg->E0CSR_L;

    drv_usbc_writeepxdata(CONTROL_EP, src, Length);

    // set DataEnd =1
    if (Status == PACKET_END)
    {
        ucReg |= DEV_CSR0_DATAEND;
    }
    // set TxPktRdy =1
    ucReg |= DEV_CSR0_TXPKTRDY;

    gUSBC_IndexReg->E0CSR_L = ucReg;
}

/**
 * @brief USB 模块接收数据函数
 * @param usbcEPx 接收端口号
 * @param buf 接收数据指针
 * @return
 */
uint16_t drv_usbc_receivedata(uint8_t usbcEPx, uint8_t *buf)
{
    uint16_t uiRxCount = 0;
    uint8_t ucRegLow;
    uint8_t EPx;

    if ((usbcEPx == CONTROL_EP) || (usbcEPx > INDEX_EP7))
        return 0;
    // 备份端点
    EPx = gUSBC_CommonReg->EINDEX;

    // access DATA_OUT_EP register map
    gUSBC_CommonReg->EINDEX = usbcEPx;

    ucRegLow = gUSBC_IndexReg->RXCSR_L;

    // Clear sentstall and restart data toggle.
    if (ucRegLow & DEV_RXCSR_SENT_STALL)
    {
        // clear SendStall bit
        ucRegLow &= ~DEV_RXCSR_SEND_STALL;

        ucRegLow |= DEV_RXCSR_CLR_DATA_TOG;
        // set ClrDataTog
        gUSBC_IndexReg->RXCSR_L = ucRegLow;
    }

    // Start receive data packet
    if (ucRegLow & DEV_RXCSR_RXPKTRDY)
    {
        uiRxCount = gUSBC_IndexReg->RXCOUNTR_H;
        uiRxCount <<= 8;
        uiRxCount += gUSBC_IndexReg->RXCOUNTR_L;

        if (gUSBC_DMA_mode == 1)
        {
            drv_usbc_readepxdatabydma(usbcEPx, buf, uiRxCount);
        }
        else
        {
            drv_usbc_readepxdata(usbcEPx, buf, uiRxCount);
        }
        drv_usbc_clearrx();
    }

    // 还原端点
    gUSBC_CommonReg->EINDEX = EPx;

    return uiRxCount;
}

/**
 * @brief USB 模块EP0发送数据
 * @param requestLen 请求长度
 * @param databuf 发送数据buff
 * @param dataLen 发送数据长度
 * @return
 */
uint16_t drv_usbc_ep0senddata(uint16_t requestLen, uint8_t *databuf, uint16_t dataLen)
{
    uint16_t SendLen = 0;

    requestLen = (requestLen > dataLen) ? dataLen : requestLen; // host可能会发送长度字节为FF的请求

    // 关闭EP0中断
    gUSBC_CommonReg->INTRTXE_L &= ~USB_INTERRUPT_EP0;

    if (dataLen > USB_MAX_PACKET_SIZE_EP0)
    {
        if (requestLen > USB_MAX_PACKET_SIZE_EP0)
        {
            while ((requestLen - SendLen) > USB_MAX_PACKET_SIZE_EP0)
            {
                drv_usbc_writeep0data(databuf + SendLen, USB_MAX_PACKET_SIZE_EP0, PACKET_MID);
                while ((gUSBC_CommonReg->INTRTX_L & USB_INTERRUPT_EP0) == 0x00)
                    ;
                SendLen += USB_MAX_PACKET_SIZE_EP0;
            }
        }
    }
    drv_usbc_writeep0data(databuf + SendLen, requestLen - SendLen, PACKET_END);

    // 打开EP0中断
    gUSBC_CommonReg->INTRTXE_L |= USB_INTERRUPT_EP0;

    return requestLen;
}

/**
 * @brief USB 模块设置FIFO中待发送的数据长度函数
 * @param Size 待发送数据的长度
 */
void drv_usbc_settxsize(uint16_t Size)
{
    if (Size > gUSBC_PacketSize)
    {
        gUSBC_IndexReg->TXMAXP_L = _byte_low(gUSBC_PacketSize);
        gUSBC_IndexReg->TXMAXP_H = _byte_high(gUSBC_PacketSize);
    }
    else
    {
        gUSBC_IndexReg->TXMAXP_L = _byte_low(Size);
        gUSBC_IndexReg->TXMAXP_H = _byte_high(Size);
    }
}

/**
 * @brief USB 模块发送函数
 * @param usbcEPx usb端口号
 * @param buf 要发送数据的缓冲
 * @param len 要发送数据的长度
 * @return
 */
uint8_t drv_usbc_senddata(uint8_t usbcEPx, uint8_t *buf, uint16_t len)
{
    uint8_t EPx;
    if ((usbcEPx == CONTROL_EP) || (usbcEPx > INDEX_EP7))
        return 1;

    // 备份端点
    EPx = gUSBC_CommonReg->EINDEX;

    // 检测发送端口的发送情况
    gUSBC_CommonReg->EINDEX = BULKIN_EP;

    if (gUSBC_IndexReg->RXCSR_L & (DEV_RXCSR_RXPKTRDY | DEV_RXCSR_FIFOFULL))
        return 1;
    // 检查发送缓冲是否有数据，等待为空；
    while ((gUSBC_IndexReg->TXCSR_L & DEV_TXCSR_TXPKTRDY) == DEV_TXCSR_TXPKTRDY)
        ;

    gUSBC_CommonReg->EINDEX = usbcEPx;

    drv_usbc_settxsize(len);
    // write data into TX FIFO and wait for send

    if (gUSBC_DMA_mode == 1)
    {
        drv_usbc_writeepxdatabydma(usbcEPx, buf, len);
    }
    else
    {
        drv_usbc_writeepxdata(usbcEPx, buf, len);
    }
    // set TxPktRdy=1
    drv_usbc_settx();

    // 还原端点
    gUSBC_CommonReg->EINDEX = EPx;
    return 0;
}

/**
 * @brief  USB 模块发送0数据孔函数
 *
 * @param usbcEPx usb端口号
 * @return uint8_t
 */
uint8_t drv_usbc_senddatanull(uint8_t usbcEPx)
{
    uint8_t EPx;
    if ((usbcEPx == CONTROL_EP) || (usbcEPx > INDEX_EP7))
        return 1;

    // 备份端点
    EPx = gUSBC_CommonReg->EINDEX;

    // 检测发送端口的发送情况
    gUSBC_CommonReg->EINDEX = BULKIN_EP;

    if (gUSBC_IndexReg->RXCSR_L & (DEV_RXCSR_RXPKTRDY | DEV_RXCSR_FIFOFULL))
        return 1;
    // 检查发送缓冲是否有数据，等待为空；
    while ((gUSBC_IndexReg->TXCSR_L & DEV_TXCSR_TXPKTRDY) == DEV_TXCSR_TXPKTRDY)
        ;

    gUSBC_CommonReg->EINDEX = usbcEPx;

    drv_usbc_settxsize(0);
    // write data into TX FIFO and wait for send

    // set TxPktRdy=1
    drv_usbc_settx();

    // 还原端点
    gUSBC_CommonReg->EINDEX = EPx;
    return 0;
}

/**
 * @brief USB 模块暂停函数
 *
 */
static void drv_usbc_suspend(void)
{
    //    uint8_t ucMode;

    if (gUSBC_SuspendMode)
    {
        //        ucMode= gUSBC_CommonReg->UCSR;
        //        ucMode |= USB_POWER_ENAB_SUSP;
        //        gUSBC_CommonReg->UCSR = ucMode;
        //
        //        //Enable USB FILE Clock
        //        ucMode= gUSBC_CommonReg->UCSR;
        //        ucMode &= ~USB_POWER_ENAB_SUSP;
        //        gUSBC_CommonReg->UCSR = ucMode;
        if (g_enumeration) // 此处判断枚举成功标志  成功后才能进入低功耗，否则提前进入低功耗无法完成正常枚举
        {
            g_flag_suspend = 1;
        }
    }
}

/**
 * @brief USB 模块唤醒函数
 *
 */
static void drv_usbc_resume(void)
{
    g_flag_suspend = 0;
    g_flag_resume = 1;
}

// 用于主动回复USB主线  在被其他源唤醒时调用
void USBC_WakeUp_Host(void) // 当设备工作在挂起模式时，通过 CPU 置 1，产生恢复信号。在 10ms 后（最多为 15ms）CPU 应该清除该位，关闭恢复信号。
// 0=关闭恢复信号
// 1=产生恢复信号  BIT2
{
    gUSBC_CommonReg->UCSR |= USB_POWER_RESUME;
    delayms(10);
    gUSBC_CommonReg->UCSR &= ~(USB_POWER_RESUME);
}

/**
 * @brief USB 模块复位函数
 *
 */
static void drv_usbc_busreset(void)
{
    __IO uint8_t EPx;

    /*初始化协议变量*/
    drv_usbc_varinit_callback();

    /*Interrupt Var*/
    gUSBC_RxINT_Flag = 0;
    gUSBC_TxINT_Flag = 0;
    gUSBC_DMAINTR = 0;

    gUSBC_CommonReg->FADDRR = 0;

    for (EPx = 1; EPx < 8; EPx++)
    {
        // access DATA_OUT_EP register map
        gUSBC_CommonReg->EINDEX = EPx;

        // set FIFO size
        if (g_Version == USB_VERSION_20)
        {
            gUSBC_ControlReg->TXFIFOSZ = 0x06;
            gUSBC_ControlReg->RXFIFOSZ = 0x06;
        }
        else
        {
            gUSBC_ControlReg->TXFIFOSZ = 0x03;
            gUSBC_ControlReg->RXFIFOSZ = 0x03;
        }

        // set fifo offset address
        drv_usbc_setfifoaddr(USB_FIFO_TAB[EPx], 0);

        gUSBC_IndexReg->TXCSR_L = DEV_TXCSR_CLR_DATA_TOG;
        gUSBC_IndexReg->TXCSR_H = 0;

        gUSBC_IndexReg->TXMAXP_L = _byte_low(gUSBC_PacketSize);
        gUSBC_IndexReg->TXMAXP_H = _byte_high(gUSBC_PacketSize);

        gUSBC_IndexReg->RXCSR_L = DEV_RXCSR_CLR_DATA_TOG;
        gUSBC_IndexReg->RXCSR_H = 0x0;

        gUSBC_IndexReg->RXMAXP_L = _byte_low(gUSBC_PacketSize);
        gUSBC_IndexReg->RXMAXP_H = _byte_high(gUSBC_PacketSize);
        //=================================

        // Flush Tx Ep FIFO
        gUSBC_IndexReg->TXCSR_L = DEV_TXCSR_FLUSH_FIFO;

        // Flush Rx Ep FIFO
        gUSBC_IndexReg->RXCSR_L = DEV_RXCSR_FLUSH_FIFO;
    }
}

/**
 * @brief USB 模块EP0中断处理函数
 *
 */
void (*drv_usbc_ep0handler_callback)(void);

/**
 * @brief USB 模块EP0中断处理函数
 *
 */
void __weak drv_usbc_ep0process(void)
{
    uint8_t ucReg = 0;

    // enable ep0 register map to be accessed
    gUSBC_CommonReg->EINDEX = CONTROL_EP;

    ucReg = gUSBC_IndexReg->E0CSR_L;

    // clear SentStall bit
    if (ucReg & DEV_CSR0_SENTSTALL)
    {
        ucReg &= ~(DEV_CSR0_SENTSTALL);
    }
    // clear SetupEnd bit
    if (ucReg & DEV_CSR0_SETUPEND)
    {
        ucReg |= DEV_CSR0_SERVICE_SETUPEND;
    }
    gUSBC_IndexReg->E0CSR_L = ucReg;

    // if RxPktRdy=1,Data come into ep0 buf
    if ((ucReg & DEV_CSR0_RXPKTRDY) || (g_Ep0DataStage))
    {
        drv_usbc_ep0handler_callback();
    }
}
/**
 * @brief USB 模块中断函数
 * @param
 */
void drv_usbc_Irq(void)
{
}

/**
 * @brief USB 模块中断回调函数
 *
 */
void (*drv_drv_usbc_Irq_callback)(void);

/**
 * @brief USB 模块中断处理函数
 *
 */
void __weak drv_drv_usbc_Irqhandler(void)
{
    uint8_t ComINTFlag, TxINTFlag, RxINTFlag;
    uint8_t uUSBC_INDEX_EPx;

    uUSBC_INDEX_EPx = gUSBC_CommonReg->EINDEX;

    /*获取中断状态*/
    ComINTFlag = gUSBC_CommonReg->INTRUSB;

    /*获取Tx状态*/
    TxINTFlag = gUSBC_CommonReg->INTRTX_L;

    /*获取Rx状态*/
    RxINTFlag = gUSBC_CommonReg->INTRRX_L;

    //  /*获取DMA中断的逻辑通道号*/
    //  gUSBC_DMAINTR = gUSBC_DMAReg->DMA_INTR;

    /*处理相关状态*/
    /*处理命令中断事物*/
    if (ComINTFlag & USB_INTERRUPT_RESET) // 复位请求中断
    {
        drv_usbc_busreset();
    }

    if (ComINTFlag & USB_INTERRUPT_SUSPEND) // 挂起中断事物
    {
        drv_usbc_suspend();
    }
    if (ComINTFlag & USB_INTERRUPT_RESUME) // 恢复中断事物
    {
        drv_usbc_resume();
    }
    /*处理Tx中断事务*/
    if (TxINTFlag & USB_INTERRUPT_EP0)
    {
        if (gUSBC_NewAddress)
        {
            gUSBC_CommonReg->FADDRR = gUSBC_NewAddress;
            gUSBC_NewAddress = 0;
        }
        drv_usbc_ep0process();
    }
    /*接收数据中断处理*/
    if (RxINTFlag)
    {
        gUSBC_RxINT_Flag = RxINTFlag;
    }
    /*发送数据中断处理*/
    if (TxINTFlag & (~USB_INTERRUPT_EP0))
    {
        gUSBC_TxINT_Flag = TxINTFlag;
    }

    drv_drv_usbc_Irq_callback();

    gUSBC_CommonReg->EINDEX = uUSBC_INDEX_EPx;
}

/**
 * @brief USB 模块进入低功耗函数
 * @param
 */
void drv_usbc_suspend_lowpower(void)
{

    // SSI_Enable_Four_Line_Mode(SSI1_ID);
    drv_cpm_lowpower();
}
