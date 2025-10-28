/**
 * @file png_drv.h
 * @author Product Application Department
 * @brief  PNG 模块驱动头文件
 * @version V1.0
 * @date 2025-02-17
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __PNG_DRV_H
#define __PNG_DRV_H

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
#define JPEG_AXI_CONFIG (*(volatile uint32_t *)(0X400D0004))
#define PNG_SRAM_CONFIG (*(volatile uint32_t *)(0x40001010))
#define JPEG_AXI_EN 0X01
#define PNG_SRAM_EN 0x00030000
#define PNG_CHUNK_LEN_SIZE (4)
#define PNG_CHUNK_TYPE_SIZE (4)
#define PNG_CHUNK_CRC_SIZE (4)
#define PNG_IHDR_CHUNK_SIZE (13)

/**
 * @brief PNG 模块状态枚举定义
 *
 */
typedef enum
{
    DRV_PNG_OK = 0x00,
    DRV_PNG_BUSY = 0x01,
    DRV_PNG_ERROR = 0x02
} png_status_t;
/**
 * @brief PNG 模块解析错误枚举定义
 *
 */
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
 * @brief PNG 模块中断使能结构体定义
 *
 */
typedef struct
{
    uint8_t done_en;  // 解码完成中断使能
    uint8_t error_en; // 解码出错中断使能
} png_irq_init_structure_t;
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
 * @brief PNG 模块PLTE信息结构体定义
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
} png_param_cfg_t;
/**
 * @brief PNG 模块解码器初始化结构体定义
 *
 */
typedef struct
{
    uint8_t is_rgb;
    png_out_rgb_format_t out_rgb_datatype;
    uint32_t image_addr;
    uint32_t image_len;
    uint32_t out_addr0;
    uint8_t dither_en;
    uint8_t out_alpha_val;
    uint8_t xip_src;
    image_deocoder_callback_t png_irq_cb;
} png_decoder_initstructure_t;
// 函数声明
void drv_png_close_jpeg_axi(void);
void drv_enable_png_sram(void);
void drv_png_gate_enable(reg_decoder_t *PNGx);
png_config_err_t drv_png_init(reg_decoder_t *PNGx, png_parse_info_t m_parsed_info, png_param_cfg_t m_param_cfg);
void drv_png_start(reg_decoder_t *PNGx);
png_status_t drv_get_png_status(reg_decoder_t *PNGx);
void drv_png_clr_status(reg_decoder_t *PNGx);

#ifdef __cplusplus
}
#endif

#endif