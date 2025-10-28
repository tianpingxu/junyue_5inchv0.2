/**
 * @file image_decoder_drv.h
 * @author Product Application Department
 * @brief  IMGDECODE 模块驱动层头文件
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __IMAGE_DECODER_DRV_H
#define __IMAGE_DECODER_DRV_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "status.h"
#include "image_decoder_reg.h"

// 全局变量定义

#define JFIF_MKR_SOF0 0xFFC0 // Start Of Frame (SOF0 for baseline DCT)
#define JFIF_MKR_DHT 0xFFC4  // Define Huffman Table
#define JFIF_MKR_SOI 0xFFD8  // Start Of Image
#define JFIF_MKR_EOI 0xFFD9  // End Of Image
#define JFIF_MKR_SOS 0xFFDA  // Start Of Scan
#define JFIF_MKR_DQT 0xFFDB  // Define Quantization Table
#define JFIF_MKR_DRI 0xFFDD  // Define restart interval
#define JFIF_MKR_APP0 0xFFE0 // Application 0
#define JFIF_MKR_APP1 0xFFE1
#define JFIF_MKR_APP2 0xFFE2
#define JFIF_MKR_APP3 0xFFE3
#define JFIF_MKR_APP4 0xFFE4
#define JFIF_MKR_APP5 0xFFE5
#define JFIF_MKR_APP6 0xFFE6
#define JFIF_MKR_APP7 0xFFE7
#define JFIF_MKR_APP8 0xFFE8
#define JFIF_MKR_APP9 0xFFE9
#define JFIF_MKR_APPa 0xFFEa
#define JFIF_MKR_APPb 0xFFEb
#define JFIF_MKR_APPc 0xFFEc
#define JFIF_MKR_APPd 0xFFEd
#define JFIF_MKR_APPe 0xFFEe
#define JFIF_MKR_APPf 0xFFEf
#define JFIF_MKR_COM 0xFFFE // Comment

#define IHDR_CHUNK_SIGN 0x49484452
#define PLTE_CHUNK_SIGN 0x504C5445
#define IDAT_CHUNK_SIGN 0x49444154
#define IEND_CHUNK_SIGN 0x49454E44

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

#define JPEG_AXI_EN 0X01
#define PNG_SRAM_EN 0x00030000
#define PNG_CHUNK_LEN_SIZE (4)
#define PNG_CHUNK_TYPE_SIZE (4)
#define PNG_CHUNK_CRC_SIZE (4)
#define PNG_IHDR_CHUNK_SIZE (13)

#define JPEG_ACCELERATE_INTR_DONE (0X01 << 2)
#define JPEG_ACCELERATE_INTR_FIFOSWITCH (0X01 << 1)
#define JPEG_ACCELERATE_SRAM_EN (0X01 << 0)

/**
 * @brief jpeg解析错误枚举定义
 * 
 */
typedef enum
{
    JFIF_RES_OK = 0,
    JFIF_FORMAT_ERR = 1,
    JFIF_NO_SUPPORT = 2
} jpeg_parse_err_t;

/**
 * @brief IMAGE DECODER 模块状态枚举定义
 * 
 */
typedef enum
{
    IMAGEDECODER_OK = 0x00,
    IMAGEDECODER_BUSY = 0x01,
    IMAGEDECODER_ERROR = 0x02
} imagedecoder_status_t;

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
 * @brief JPEG 模块输出设置结构体定义
 * 
 */
typedef struct
{
    uint8_t format; // 解码输出格式
        /* for RGB output */
    uint8_t output_rgb; // RGB
    uint32_t rgb_addr;
    uint8_t dither_en;
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


typedef enum
{
    PARSE_SUCCESS = 0x0,
    PARSE_FILE_SING_ERR = 0x1,
    PARSE_IDAT_LOSS_ERR = 0x2,
} png_parse_err_t;

/**
 * @brief PNG 模块IHDR颜色类型枚举定义
 * 
 */
typedef enum
{
    IHDR_COLOR_GREYSCALE = 0x0,
    IHDR_COLOR_TRUECOLOR = 0x2,
    IHDR_COLOR_INDEXD_COLOR = 0x3,
    IHDR_COLOR_GREYSCAL_ALPHA = 0x4,
    IHDR_COLOR_TURECOLOR_ALPHA = 0x6,
} png_color_type_t;

/**
 * @brief PNG 模块配置错误枚举定义
 * 
 */
typedef enum
{
    PNG_CONFIG_SUCCESS = 0x0,
    PNG_CONFIG_CHN_NUM_ERR = 0x1,
    PNG_CONFIG_PLTE_ADDR_ERR = 0x02,
} png_config_err_t;

/**
 * @brief PNG 模块输出格式枚举定义
 * 
 */
typedef enum
{
    PNG_OUT_LUMA_ONLY = 4,
    PNG_OUT_RGB = 11,
} png_output_format_t;

/**
 * @brief PNG 模块输出RGB格式枚举定义
 * 
 */
typedef enum
{
    PNG_OUT_RGB888 = 0,
    PNG_OUT_BGR888 = 1,
    PNG_OUT_ABGR888 = 4,
    PNG_OUT_ARGB888 = 5,
} png_out_rgb_format_t;

/**
 * @brief PNG 模块输出设置结构体定义
 * 
 */
typedef struct
{
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    png_color_type_t color_type;
    uint8_t compression_method; // invalid
    uint8_t filter_method;      // invalid
    uint8_t interface_method;   // invalid
} png_ihdr_t;

/**
 * @brief  PNG 模块PLTE信息结构体定义
 * 
 */
typedef struct
{
    uint8_t is_chunkExist;
    uint32_t plte_payload_addr;
    uint32_t plte_payload_len;
} png_plte_info_t;

/**
 * @brief PNG 模块IDAT信息结构体定义
 * 
 */
typedef struct
{
    uint32_t idat_start_addr;
    uint32_t idat_total_len;
    uint8_t idat_stream_offset;
} png_idat_info_t;

/**
 * @brief PNG 模块IEND信息结构体定义
 * 
 */
typedef struct
{
    uint32_t iend_chunk_addr;
} png_iend_info_t;

/**
 * @brief PNG 模块解析信息结构体定义
 * 
 */
typedef struct
{
    png_ihdr_t ihdr_info;
    png_plte_info_t plte_info;
    png_idat_info_t idat_info;
    png_iend_info_t iend_info;
} png_parse_info_t;

/**
 * @brief PNG 模块参数配置结构体定义
 * 
 */
typedef struct
{
    uint32_t out_width;
    uint32_t out_height;
    png_output_format_t out_format;
    png_out_rgb_format_t out_rgb_format;
    uint8_t out_channel_num;
    uint32_t out_base_addr;
    uint32_t out_chroma_addr; // set address if nv12 mode, out_u_addr if planner mode
    uint32_t out_v_addr;      // set address if planner mode
    uint8_t dither_en;
    uint8_t out_alpha_val;
    uint32_t plte_copy_addr;
    uint8_t crop_enable;
    uint32_t crop_width;
    uint32_t crop_height;
} png_param_cfg_t;

/**
 * @brief 图像格式枚举定义
 * 
 */
typedef enum
{
    IMAGE_JPEG,
    IMAGE_PNG
} image_type_t;

/**
 * @brief 输出图像格式枚举定义
 * 
 */
typedef enum
{
    JPEG_OUTPUT_YUV420_0 = 0,
    JPEG_OUTPUT_YUV400_0,
    JPEG_OUTPUT_YUV422_0,
    JPEG_OUTPUT_YUV444_0,
    JPEG_OUTPUT_BGR888 = 10,
    JPEG_OUTPUT_RGB888,
    JPEG_OUTPUT_ABGR888,
    JPEG_OUTPUT_ARGB888,
    JPEG_OUTPUT_BGRA888,
    JPEG_OUTPUT_RGBA888,
    JPEG_OUTPUT_BGR565,
    JPEG_OUTPUT_RGB565,
    PNG_OUTPUT_RGB888 = 20,
    PNG_OUTPUT_BGR888,
    PNG_OUTPUT_ABGR888,
    PNG_OUTPUT_ARGB888,
} image_output_type_t;

typedef void (*image_deocoder_callback_t)(void);

/**
 * @brief 图像解码器初始化结构体定义
 * 
 */
typedef struct
{
    image_type_t image_type;
    image_output_type_t output_type;
    uint32_t image_addr; // 图像地址
    uint32_t image_len;  // 图像长度
    uint32_t out_addr0;  // 输出地址0（Y）/（RGB）
    uint32_t out_addr1;  // 输出地址1（U/plannar）/(UV/nv12)
    uint32_t out_addr2;  // 输出地址2（V/plannar）
    uint8_t alpha;
    uint8_t dither_en;
    uint8_t crop_en;
    uint8_t crop_width;
    uint8_t crop_height;
    uint8_t decoder_irq_en; // 透明度
    image_deocoder_callback_t image_decoder_irq_cb;
} image_decoder_initstructure_t;

// 函数声明
void drv_enbale_jpeg_sram(void);
void drv_enable_png_sram(void);
void drv_jpeg_axi_reset(void);
void drv_png_close_jpeg_axi(void);
void drv_imagedecoder_gate_enable(void);
void drv_jpeg_init(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset);
png_config_err_t drv_png_init(png_parse_info_t m_parsed_info, png_param_cfg_t m_param_cfg);
void drv_imagedecoder_start(void);
imagedecoder_status_t drv_get_imagedecoder_status(void);
status_t drv_imagedecoder_clr_status(uint32_t timeout);
void drv_jpeg_accelerate_set(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset);

#ifdef __cplusplus
}
#endif

#endif
