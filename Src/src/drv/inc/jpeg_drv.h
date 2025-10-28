/**
 * @file jpeg_drv.h
 * @author Product application department
 * @brief  JPEG 模块驱动层头文件
 * @version V1.0
 * @date 2025-02-17
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __JPEG_DRV_H
#define __JPEG_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"
#include "iomacros.h"
#include "decoder_reg.h"
#include "debug.h"

// 全局变量定义
#define JPEG_PIC_INFO (*(volatile uint32_t *)(0X400D0000))
#define JPEG_PIC_CONFIG (*(volatile uint32_t *)(0X400D0004))
#define JPEG_PIC_RST (*(volatile uint32_t *)(0X400D0008))
#define JPEG_PIC_SR (*(volatile uint32_t *)(0X400D000C))
#define JPEG_PIC_CNT (*(volatile uint32_t *)(0X400D0010))
#define JPEG_PIC_JW (*(volatile uint32_t *)(0X400D0014))
#define JPEG_PIC_LW (*(volatile uint32_t *)(0X400D0018))
#define JPEG_PIC_MC (*(volatile uint32_t *)(0X400D001C))
#define CPM_JPEG_AXI_RST (*(volatile uint32_t *)(0X400040B0))
#define JPEG_SRAM_CONFIG (*(volatile uint32_t *)(0x40001010))
#define JFIF_QTAB_MAX 3
#define JFIF_HTAB_MAX 2
#define DECODE_JPEG 0X03
#define BASELINE_MODE 0X00
#define PROGRESSIVE_MODE 0X01
#define SAMPLE_DEPTH_8 0X00
#define SAMPLE_DEPTH_12 0X01
#define OUTPUT_RAM_ENABLE 0X00
#define OUTPUT_RAM_DISABLE 0X01
#define EOI_IN 0X01
#define EOI_OUT 0X00
#define JPEG_AXI_RST (0X01 << 19)
#define JPEG_SRAM_EN 0x00030000

/**
 * @brief JEPG 模块状态枚举定义
 *
 */
typedef enum
{
    DRV_JPEG_OK = 0x00,
    DRV_JPEG_BUSY = 0x01,
    DRV_JPEG_ERROR = 0x02
} jpeg_status_t;
/**
 * @brief 量化表序号枚举定义
 *
 */
typedef enum
{
    QTABLE_NUMBER_1 = 1,
    QTABLE_NUMBER_2,
    QTABLE_NUMBER_3
} qtable_number_t;
/**
 * @brief JPEG 模块图像YUV扫描方式枚举定义
 *
 */
typedef enum
{
    PIC_SAMPLE_YUV400 = 0,
    PIC_SAMPLE_YUV420 = 2,
    PIC_SAMPLE_YUV422,
    PIC_SAMPLE_YUV444,
    PIC_SAMPLE_YUV440,
    PIC_SAMPLE_YUV411
} jpeg_pic_sample_mode_t;
/**
 * @brief JPEG 模块图像输入格式枚举定义
 *
 */
typedef enum
{
    PP_INPUT_YUV422_1 = 0,
    PP_INPUT_YUV420_1,
    PP_INPUT_YUV420_2,
    PP_INPUT_YUV400,
    PP_INPUT_YUV422_2,
    PP_INPUT_YUV420_3,
    PP_INPUT_YUV440,
    PP_INPUT_YUV444,
    PP_INPUT_RGB888 = 20,
    PP_INPUT_BGR888,
    PP_INPUT_ARGB888,
    PP_INPUT_ABGR888,
} pp_input_format_t;
/**
 * @brief JPEG 模块图像输出格式枚举定义
 *
 */
typedef enum
{
    PP_OUTPUT_YUV420_0 = 0,
    PP_OUTPUT_YUV400_0 = 4,
    PP_OUTPUT_RGB = 11,
    PP_OUTPUT_YUV422_0 = 16,
    PP_OUTPUT_YUV444_0 = 24
} pp_output_format_t;
/**
 * @brief JPEG 模块图像输出RGB格式枚举定义
 *
 */
typedef enum
{
    PP_OUTPUT_BGR888 = 0,
    PP_OUTPUT_RGB888 = 1,
    PP_OUTPUT_ABGR888 = 4,
    PP_OUTPUT_ARGB888 = 5,
    PP_OUTPUT_BGRA888 = 14,
    PP_OUTPUT_RGBA888 = 15,
    PP_OUTPUT_BGR565 = 20,
    PP_OUTPUT_RGB565 = 21
} pp_output_rgb_format_t;
/**
 * @brief JPEG 模块中断使能结构体定义
 *
 */
typedef struct
{
    uint8_t done_en;  // 解码完成中断使能
    uint8_t error_en; // 解码出错中断使能
} jpeg_irq_init_structure_t;
/**
 * @brief JPEG 模块输出设置结构体定义
 *
 */
typedef struct
{
    uint8_t format; // 解码输出格式
    /* for RGB output */
    uint8_t output_rgb; // RGB
    uint32_t rgb_addr;
    uint8_t output_alpha;
    /* for YUV output */
    uint32_t y_addr;
    uint32_t u_addr;
    uint32_t v_addr;
    uint8_t crop_enable;
    uint32_t crop_width;
    uint32_t crop_height;
} jpeg_outset_t; // output setting
/**
 * @brief JPEG 模块图像信息结构体定义
 *
 */
typedef struct
{
    uint32_t jpeg_addr;
    uint32_t jpeg_len;

    uint16_t width;
    uint16_t height;

    uint16_t start_byte;
    uint16_t start_bit;
    uint16_t sample_depth;
    struct
    {
        uint8_t id;         // 1：Y   2：Cb   3：Cr
        uint8_t hfactor;    // 颜色分量水平采样因子
        uint8_t vfactor;    // 颜色分量垂直采样因子
        uint8_t qtab_id;    // 颜色分量使用的量化表ID
        uint8_t htab_id_dc; // 直流分量使用的霍夫曼表ID
        uint8_t htab_id_ac; // 交流分量使用的霍夫曼表ID
    } compinfo[3];          // Component Information
    uint8_t compcnt;
    uint8_t qtablecnt;
} jfif_info_t;

/**
 * @brief JPEG 模块解码器初始化结构体定义
 * 
 */
typedef struct
{
    uint8_t is_rgb;                          // 0: YUV  1: RGB
    pp_output_format_t out_yuv_datatype;     // 输出YUV格式
    pp_output_rgb_format_t out_rgb_datatype; // 输出RGB格式
    uint32_t image_addr;                     // 图像地址
    uint32_t image_len;                      // 图像长度
    uint32_t out_addr0;                      // 输出地址0（Y）/（RGB）
    uint32_t out_addr1;                      // 输出地址1（U）
    uint32_t out_addr2;                      // 输出地址2（V）
    uint8_t alpha;                           // 透明度
    uint8_t xip_src;                         // 解码图像源地址；0：SPIFLASH  1：PSRAM
    image_deocoder_callback_t jpeg_irq_cb;
} jpeg_decoder_initstructure_t;

// 函数声明
void drv_enbale_jpeg_sram(void);
void drv_jpeg_axi_reset(reg_decoder_t *JPEGx);
void drv_jpeg_gate_enable(reg_decoder_t *JPEGx);
void drv_jpeg_init(reg_decoder_t *JPEGx, jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset);
void drv_jpeg_enable(reg_decoder_t *JPEGx);
jpeg_status_t drv_get_jpeg_status(reg_decoder_t *JPEGx);
void drv_jpeg_clr_status(reg_decoder_t *JPEGx);
void drv_jpeg_accelerate_set(reg_decoder_t *JPEGx, jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset);
#ifdef __cplusplus
}

#endif

#endif
