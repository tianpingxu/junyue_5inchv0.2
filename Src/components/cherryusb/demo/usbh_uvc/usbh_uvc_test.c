/**
 * @file usbh_uvc_test.c
 * @author Product application department
 * @brief  UVC摄像头 测试用例，仅供参考
 * @version  V1.0
 * @date 2025-07-30
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

 /**
 * @defgroup ThirdPart 第三方模块
 * @{
 *
 * @defgroup UVC UVC模块
 * @ingroup ThirdPart
 * @{
 */

// 头文件包含
#include "usbh_uvc_test.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "systick_drv.h"
#include "debug.h"
#include "usb_uvc_lcd.h"
#include "lcd_interface.h"
#include "cmsis_armclang.h"

// 全局变量定义
#ifdef USBH_UVC_DEMO

static struct usbh_urb *video_urb = NULL;
TaskHandle_t uvc_task_handle = NULL;

__attribute__((section("NO_INIT")))  __ALIGNED(8) uint8_t video_buffer_0[FRAME_NUM_PACKETS * UVC_MAX_FRAME_SIZE]={0};//should be 8 byte alignment
__attribute__((section("NO_INIT"))) USB_MEM_ALIGNX uint8_t video_buffer_RGB[UVC_FRAME_RGB888_SIZE]={0};
__attribute__((section("NO_INIT"))) USB_MEM_ALIGNX uint8_t pipe_buffer[4096*10]={0};

// 函数定义

/**
 * @brief USB UVC摄像头线程函数
 * 
 * @param argument 
 */
static void usbh_video_thread(void *argument)
{
    int ret = 0;
    uint8_t current_index = 0;
    uint8_t *ptr = NULL;
    uint8_t *tmp_buf = video_buffer_0;
    uint64_t timestamp_1sec = 0;
    uint32_t frame_cnt = 0;
    uint32_t prev_frame_cnt = 0;
    uint8_t last_fps = 0;
    struct usbh_video *video_class = (struct usbh_video*)argument;
    uint8_t fpsbuffer[16]={0};
    while(1)
    {
        video_class = (struct usbh_video *)usbh_find_class_instance("/dev/video0");
        if (video_class == NULL) 
        {
            elog_raw("do not find /dev/video0 Please instert USB Camera device !!!\r\n");
        }else
        {
            USB_LOG_INFO("Success find /dev/video0\r\n");
            break;
        }
    }

    ret = usbh_video_open(video_class, OUT_FORMAT, UVC_TARGET_WIDTH, UVC_TARGET_HEIGHT, 1);//2
    if (ret < 0) {
    	USB_LOG_ERR("no such setting, ret:%d\r\n", ret);
        goto delete;
    }
    usb_osal_msleep(10);
    video_urb = usb_osal_malloc(sizeof(struct usbh_urb) + sizeof(struct usbh_iso_frame_packet) * FRAME_NUM_PACKETS);
  // printf("video_urb=0x%0x,sizeof()=0x%0x\r\n",(uint32_t)video_urb,sizeof((uint32_t)video_urb));
		if (video_urb == NULL) {
        USB_LOG_ERR("No memory to alloc urb\r\n");
        goto delete;
    }
		
    memset(video_urb, 0, sizeof(struct usbh_urb) + sizeof(struct usbh_iso_frame_packet) * FRAME_NUM_PACKETS);
    video_urb->ep = video_class->isoin;
    video_urb->hport = video_class->hport;
    video_urb->num_of_iso_packets = FRAME_NUM_PACKETS;
    video_urb->timeout = 0xffffffff;

    for (uint32_t i = 0; i < FRAME_NUM_PACKETS; i++) {
        video_urb->iso_packet[i].transfer_buffer = tmp_buf;
        video_urb->iso_packet[i].actual_length =0;
        tmp_buf += UVC_MAX_FRAME_SIZE;
    }

    // 单次传输所需的buffer ,分配大内存应对 高速&&高带宽传输
    //video_urb->transfer_buffer = usb_osal_malloc(USB_GET_MAXPACKETSIZE(video_class->isoin->wMaxPacketSize) * (USB_GET_MULT(video_class->isoin->wMaxPacketSize) +1));
    video_urb->transfer_buffer = pipe_buffer;
    if(video_urb->transfer_buffer == NULL)
    {
        USB_LOG_ERR("No memory to alloc transfer_buffer\r\n");
        goto delete;
    }
    // 创建一个可用消息队列
    video_urb->arg = (void *) xQueueCreate(FRAME_NUM_PACKETS, sizeof(uint8_t));
    if(NULL == video_urb->arg)
    {
        USB_LOG_ERR("Create Queue failed \r\n");
        goto delete;
    }
    video_urb->timeout = 0;
    ret = usbh_submit_urb(video_urb);
    USB_LOG_INFO("Start Display video !!!\r\n");
    while(1)
    {
        xQueuePeek((QueueHandle_t)video_urb->arg ,&current_index, portMAX_DELAY);
        ptr = video_urb->iso_packet[current_index].transfer_buffer;
        frame_cnt++;
			
			 printf("video_urb=0x%0x\r\n",(uint32_t)video_urb->iso_packet[current_index].transfer_buffer);
        uvc_lcd_jpeg_decode((uint32_t)video_urb->iso_packet[current_index].transfer_buffer, video_urb->iso_packet[current_index].actual_length, (uint32_t)video_buffer_RGB);
        //lcd draw from rgb565 stream source	
			
			printf("video_urb123=0x%0x\r\n",(uint32_t)video_urb->iso_packet[current_index].transfer_buffer);
        if(uvc_task_handle != NULL)
        {

        }
        else
        {
            uvc_lcd_rgb_dma2d_draw((uint32_t*)video_buffer_RGB, 0, 0, UVC_TARGET_WIDTH, UVC_TARGET_HEIGHT, LCD_DISP_HOR_RES);		
        }
        video_urb->iso_packet[current_index].actual_length = 0;
        xQueueReceive((QueueHandle_t)video_urb->arg, &current_index, portMAX_DELAY);
    }

delete:
    usb_osal_thread_delete(NULL);
}

/**
 * @brief USB UVC摄像头线程创建函数
 * 
 * @param video_class 
 */
void usbh_video_run(struct usbh_video *video_class)
{
    usb_osal_thread_create("usbh_video1", 8192, CONFIG_USBHOST_PSC_PRIO + 2, usbh_video_thread, video_class);
}

/**
 * @brief USB UVC摄像头测试示例函数
 * 
 */
void usbh_uvc_demo(void)
{
    uvc_lcd_rgb_init();	
    SysTick_IRQHandler_Callback = drv_systick_handler;
    usbh_initialize(0, 0x4004C000);
    vTaskStartScheduler();
}
#endif

/** @} */  // 结束 UVC 模块分组
/** @} */  // 结束外设模块分组