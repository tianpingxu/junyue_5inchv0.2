
#include "usb_drv.h"
#include "usb_ms_protocol.h"

/*************************************************
Function: USB_MS_Receive
Description: USB端点接收一包数据
Input:  -usbEpx :USB接收端口号
        -buf    :接收数据的起始地址
Output: 无
Return: 接收数据的长度
Others: 无
*************************************************/
void USB_MS_Receive(uint8_t usbEpx, uint8_t *buf, uint16_t length)
{
    if (gUSBC_DMA_mode == 1)
    {
        drv_usbc_readepxdatabydma(usbEpx, buf, length);
    }
    else
    {
        drv_usbc_readepxdata(usbEpx, buf, length);
    }
}

/*************************************************
Function: USB_MS_send
Description: USB端点发送一包数据
Input:--usbEpx :USB发送端口号
      -buf:发送数据的起始地址
      -len:发送数据的长度
Output: 无
Return: 无
Others: 无
*************************************************/
void USB_MS_Send(uint8_t usbEpx, uint8_t *buf, uint16_t len)
{
    uint16_t n, m;
    uint16_t i;

    n = len / gUSBC_PacketSize;
    m = len % gUSBC_PacketSize;

    for (i = 0; i < n; i++)
    {
        drv_usbc_senddata(usbEpx, buf + gUSBC_PacketSize * i, gUSBC_PacketSize);
    }
    if (m)
    {
        drv_usbc_senddata(usbEpx, buf + gUSBC_PacketSize * n, m);
    }
}
