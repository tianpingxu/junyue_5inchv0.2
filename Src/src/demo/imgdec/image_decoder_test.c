/**
 * @file image_decoder_test.c
 * @author Product Application Department
 * @brief  image decoder 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup IMGDEC IMGDEC模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "image_decoder_test.h"

// 全局变量定义
#define JPEG_SRC_ADDR1 0X1C000000
#define JPEG_OUT_ADDR1 0X1C100000

#define PNG_SRC_ADDR1 0X1C200000
#define PNG_OUT_ADDR1 0X1C300000

volatile uint32_t imagedecoder_flg;
// 函数定义

/**
 * @brief 图像解码器中断处理函数
 *
 */
static void image_irq_handler(void)
{
    imagedecoder_flg = 1;
    printf("image decode irq\n");
}
/**
 * @brief jpeg解码测试
 *
 */
void image_jpeg_decode_test(void)
{
    status_t ret;
    imagedecoder_flg = 0;
    image_decoder_initstructure_t image_decoder_init;
    image_decoder_init.image_type = IMAGE_JPEG;
    image_decoder_init.output_type = JPEG_OUTPUT_RGB888;
    image_decoder_init.image_addr = (uint32_t)jpeg_image; // 地址必须是8字节对齐
    image_decoder_init.image_len = jpeg_image_len;
    image_decoder_init.out_addr0 = JPEG_OUT_ADDR1;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0; // 输出ARGB才会生效
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 1;
    image_decoder_init.image_decoder_irq_cb = image_irq_handler;

    ret = hal_imagedecoder_init(&image_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }
    if(image_decoder_init.decoder_irq_en)
    {
        while (imagedecoder_flg == 0)
            ;
        imagedecoder_flg = 0;
    }else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
        ;
        hal_imagedecoder_clr_status();
    }
    printf("jpeg decode ok\n");
}
/**
 * @brief png解码测试
 *
 */
void image_png_decode_test(void)
{
    status_t ret;
    imagedecoder_flg = 0;
    image_decoder_initstructure_t image_decoder_init;
    image_decoder_init.image_type = IMAGE_PNG;
    image_decoder_init.output_type = PNG_OUTPUT_ARGB888;
    image_decoder_init.image_addr = (uint32_t)png_image; // 地址必须是8字节对齐
    image_decoder_init.image_len = png_image_len;
    image_decoder_init.out_addr0 = PNG_OUT_ADDR1;
    image_decoder_init.out_addr1 = 0;
    image_decoder_init.out_addr2 = 0;
    image_decoder_init.alpha = 0;
    image_decoder_init.dither_en = 1;
    image_decoder_init.crop_en = 0;
    image_decoder_init.crop_width = 0;
    image_decoder_init.crop_height = 0;
    image_decoder_init.decoder_irq_en = 0;
    image_decoder_init.image_decoder_irq_cb = image_irq_handler;

    ret = hal_imagedecoder_init(&image_decoder_init);
    if (ret != STATUS_OK)
    {
        printf("image decoder error, ret = %d\n", ret);
        return;
    }

    if(image_decoder_init.decoder_irq_en)
    {
        while (imagedecoder_flg == 0)
            ;
        imagedecoder_flg = 0;
    }else
    {
        while (hal_get_imagedecoder_status() != STATUS_OK)
        ;
        hal_imagedecoder_clr_status();
    }

    printf("png decode ok\n");
}
/**
 * @brief 图像解码器测试
 *
 */
void image_decoder_demo(void)
{
    image_jpeg_decode_test();
    image_png_decode_test();
}

/** @} */  // 结束 IMGDEC 模块分组
/** @} */  // 结束外设模块分组
