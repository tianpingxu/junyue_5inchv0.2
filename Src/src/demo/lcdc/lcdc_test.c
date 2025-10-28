/**
 * @file lcdc_test.c 
 * @author Product application department 
 * @brief  LCDC 模块测试用例，仅供参考
 * @version V1.0 
 * @date 2025-02-14 
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved. 
 * 
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup LCDC LCDC模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "lcdc_test.h"
#include "lcdc_test_pic.h"
#include "image_decoder_drv.h"
#include "image_decoder_hal.h"
#include "image_decoder_test.h"
#include "libaxiflow.h"
#include "lcdc_dma2d_test.h"
// 全局变量定义
#define DECODER_IN_ADDR 0x1C400000
#define L1_ADDR 0x1C000000
#define L2_ADDR 0x1C200000
#define PSRAM_ADDR_SWITCH_D0(x) (uint32_t)(x & 0x00ffffff | 0xd0000000)

volatile uint32_t imagedecoder_clcdflg;

static rgb_input_timing_para_t p_rgb_para =
{
    .vsync = 3,
    .vbp = 20,
    .vfp = 12,
    .height = 600,
    .hsync = 20,
    .hbp = 140,
    .hfp = 160,
    .width = 1024,
    .clcdclk = 50*1000000,
    .background_color = RGB_RED,
    .l1_default_color = ARGB_CLEAR,
    .l2_default_color = ARGB_CLEAR, 
};

// 函数定义

/**
 * @brief 图像解码器中断处理函数
 *
 */
static void image_clcd_irq_handler(void)
{
    imagedecoder_clcdflg = 1;
    printf("image decode irq\n");
}
/**
 * @brief jepg图解压缩函数
 * 
 * @param xip_en flash是否使能xip
 * @param img_addr 压缩图片地址
 * @param image_len 压缩图片长度
 * @param in_addr 压缩图片拷贝到psram地址
 * @param out_addr 解压后的图片地址
 * @param width 宽度
 * @param height 高度
 */
void image_jpeg_decode(uint32_t xip_en, uint32_t img_addr,uint32_t image_len,uint32_t in_addr,uint32_t out_addr,uint32_t width,uint32_t height)
{
    status_t ret;
    uint8_t *jpeg_image_sdr;
    uint32_t i = 0;
    imagedecoder_clcdflg = 0;
    image_decoder_initstructure_t image_decoder_init;
if (!xip_en)
{
    jpeg_image_sdr = (uint8_t *)in_addr;
    memcpy(jpeg_image_sdr, (uint8_t *)img_addr, image_len);
    dcache_clean_range((uint32_t*)jpeg_image_sdr, image_len);
    for (i = 0; i < image_len; i++)
    {
        if (jpeg_image_sdr[i] != *(uint8_t *)(img_addr + i))
        {
            printf("memcpy data error\r\n");
            while (1)
                ;
        }
    }
    image_decoder_init.image_type = IMAGE_JPEG;
    image_decoder_init.output_type = JPEG_OUTPUT_RGB888;
    image_decoder_init.image_addr = (uint32_t)jpeg_image_sdr; // 地址必须是8字节对齐
    image_decoder_init.image_len = image_len;
    image_decoder_init.out_addr0 = out_addr;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0; // 输出ARGB才会生效
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_clcd_irq_handler;
}
else
{
    image_decoder_init.image_type = IMAGE_JPEG;
    image_decoder_init.output_type = JPEG_OUTPUT_RGB888;
    image_decoder_init.image_addr = (uint32_t)img_addr; // 地址必须是8字节对齐
    image_decoder_init.image_len = image_len;
    image_decoder_init.out_addr0 = out_addr;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0; // 输出ARGB才会生效
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_clcd_irq_handler;
}

    printf("JPEG DATA ADDR = 0X%X\r\n", image_decoder_init.image_addr);
    printf("JPEG DATA LEN = %d\r\n", image_decoder_init.image_len);
    printf("JPEG OUT ADDR = 0X%X\r\n", image_decoder_init.out_addr0);
    ret = hal_imagedecoder_init(&image_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }
    if (image_decoder_init.decoder_irq_en)
    {
        while (imagedecoder_clcdflg == 0)
            ;
        imagedecoder_clcdflg = 0;
    }
    else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
            ;
        hal_imagedecoder_clr_status();
    }
    printf("jpeg decode ok\n");
}
/**
 * @brief png图解压缩函数
 * 
 * @param xip_en 是否使能xip
 * @param img_addr 压缩图片地址
 * @param image_len 压缩图片长度
 * @param in_addr 压缩图片拷贝到psram地址
 * @param out_addr 解压后的图片地址
 * @param width 宽度
 * @param height 高度
 */
void image_png_decode(uint32_t xip_en,uint32_t img_addr,uint32_t image_len,uint32_t in_addr,uint32_t out_addr,uint32_t width,uint32_t height)
{
    status_t ret;
    uint8_t *png_image_sdr;
    uint32_t i = 0;
    imagedecoder_clcdflg = 0;
    image_decoder_initstructure_t image_decoder_init;
if (!xip_en)
{
    png_image_sdr = (uint8_t *)(in_addr);
    memcpy(png_image_sdr, (uint8_t *)img_addr, image_len);
    dcache_clean_range((uint32_t*)png_image_sdr, image_len);
    for (i = 0; i < image_len; i++)
    {
        if (png_image_sdr[i] != *(uint8_t *)(img_addr + i))
        {
            printf("memcpy data error\r\n");
            while (1)
                ;
        }
    }

    image_decoder_init.image_type = IMAGE_PNG;
    image_decoder_init.output_type = PNG_OUTPUT_ARGB888;
    image_decoder_init.image_addr = (uint32_t)png_image_sdr; // 地址必须是8字节对齐
    image_decoder_init.image_len = image_len;
    image_decoder_init.out_addr0 = out_addr;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0;
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_clcd_irq_handler;
}
else
{
    image_decoder_init.image_type = IMAGE_PNG;
    image_decoder_init.output_type = PNG_OUTPUT_ARGB888;
    image_decoder_init.image_addr = (uint32_t)img_addr; // 地址必须是8字节对齐
    image_decoder_init.image_len = image_len;
    image_decoder_init.out_addr0 = out_addr;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0;
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_clcd_irq_handler;
}
    printf("PNG DATA ADDR = 0X%X\r\n", image_decoder_init.image_addr);
    printf("PNG DATA LEN = %d\r\n", image_decoder_init.image_len);
    printf("PNG OUT ADDR = 0X%X\r\n", image_decoder_init.out_addr0);
    
    ret = hal_imagedecoder_init(&image_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }

    if (image_decoder_init.decoder_irq_en)
    {
        while (imagedecoder_clcdflg == 0)
            ;
        imagedecoder_clcdflg = 0;
    }
    else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
            ;
        hal_imagedecoder_clr_status();
    }

    printf("png decode ok\n");
}

/**
 * @brief LCDC 模块测试用例
 * 
 * @param blend_en 是否叠图
 */
void app_lcdc_init(uint8_t blend_en)
{
    status_t status = STATUS_OK;
    uint8_t layern = 0;
    uint8_t layer_en = 0;
    lcdc_pixel_format_t l1_format = LCDC_RGB888;
    lcdc_pixel_format_t l2_format = LCDC_ARGB8888;
    uint32_t l1_addr = PSRAM_ADDR_SWITCH_D0(L1_ADDR);
    uint32_t l2_addr = PSRAM_ADDR_SWITCH_D0(L2_ADDR);
    uint32_t l1_alpha = 0xFF;
    uint32_t l2_alpha = 0xFF;
    uint8_t l1_f1 = 1;
    uint8_t l1_f2 = 1;
    uint8_t l2_f1 = 1;
    uint8_t l2_f2 = 1;

    status = hal_lcdc_init(&p_rgb_para);
    if (status != STATUS_OK)
    {
        printf("LCDC init fail!\n");
        return;
    }

    status = hal_lcdc_layer_switch(LAYER_OFF);
    if (status != STATUS_OK)
    {
        printf("LCDC background display fail!\n");
        return;
    }
    delay(100);

    status = hal_lcdc_format_and_addr_config(&p_rgb_para, l1_format, l2_format, l1_addr, l2_addr);
    if (status != STATUS_OK)
    {
        printf("LCDC sets L1 layer and L2 layer color format fail!\n");
        return;
    }
    if (blend_en)
    {
        hal_lcdc_layer_blend_config(l1_alpha, l2_alpha, l1_f1, l1_f2, l2_f1, l2_f2);
        status = hal_lcdc_layer_switch(LAYER_ALL_ON);
        if (status != STATUS_OK)
        {
            printf("LCDC L1 & L2层显示失败\n");
            return;
        }
        delay(100);
    }
    else
    {
        status = hal_lcdc_layer_switch(LAYER1_ON);
        if (status != STATUS_OK)
        {
            printf("LCDC L1层显示失败\n");
            return;
        }
        delay(100);
    }
}
/**
 * @brief DMA2D 初始化函数  Blend模式
 * 
 * @param fg_addr 前景图像地址
 * @param bg_addr 背景图像地址
 * @param out_addr 输出图像地址
 * @param fg_offset 前景图像偏移
 * @param bg_offset 背景图像偏移
 * @param out_offset 输出图像偏移
 * @param width 图像宽度
 * @param height 图像高度
 */
void app_dma2d_init(uint32_t fg_addr, uint32_t bg_addr, uint32_t out_addr, uint32_t fg_offset, uint32_t bg_offset, uint32_t out_offset, uint32_t width, uint32_t height)
{
    dma2d_mem2mem_blend_t p_mem2mem_blend;

    p_mem2mem_blend.fg_color_mode = CM_ARGB8888;
    p_mem2mem_blend.bg_color_mode = CM_RGB888;
    p_mem2mem_blend.out_color_mode = CM_RGB888;
    p_mem2mem_blend.fg_alpha_mode = NO_MODIFY;
    p_mem2mem_blend.bg_alpha_mode = NO_MODIFY;
    p_mem2mem_blend.fg_fixed_alpha = 0xFF;
    p_mem2mem_blend.bg_fixed_alpha = 0xFF;

    p_mem2mem_blend.pixels_per_line = width;
    p_mem2mem_blend.lines = height;

    p_mem2mem_blend.fg_offset = fg_offset;
    p_mem2mem_blend.bg_offset = bg_offset;
    p_mem2mem_blend.output_offset = out_offset;

    p_mem2mem_blend.fg_addr = fg_addr;
    p_mem2mem_blend.bg_addr = bg_addr;
    p_mem2mem_blend.out_addr = out_addr;
    hal_dma2d_mem2mem_blend(DMA2D, &p_mem2mem_blend);
    printf("DMA2D blend over!\n");
}

/**
 *  @brief  LCDC 模块测试示例函数
 * 
 */
void lcdc_demo(void)
{
    axiflow_cdc_blend();
    image_jpeg_decode(0, (uint32_t)jpeg_image, jpeg_image_len, DECODER_IN_ADDR, L1_ADDR, 1024, 600);
    image_png_decode(0, (uint32_t)png_image, png_image_len, DECODER_IN_ADDR, L2_ADDR, 1024, 600);
    app_dma2d_init(L2_ADDR, L1_ADDR, L1_ADDR, 0, 0, 0, 1024, 600);
    app_lcdc_init(0);	
  while (1);
}

/** @} */  // 结束 LCDC 模块分组
/** @} */  // 结束外设模块分组
