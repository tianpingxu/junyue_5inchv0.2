/**
 * @file image_decoder_hal.h
 * @author Product Application Department
 * @brief  IMGDECODE 模块硬件抽象层头文件
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __IMAGE_DECODER_HAL_H
#define __IMAGE_DECODER_HAL_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "image_decoder_drv.h"
#include "interrupt.h"
    
    
// 函数声明

status_t hal_imagedecoder_init(image_decoder_initstructure_t *image_decoder_init);
status_t hal_png_decode(image_decoder_initstructure_t *png_decoder_init);
status_t hal_jpeg_decode(image_decoder_initstructure_t *jpeg_decoder_init);

png_parse_err_t hal_png_fileparse(uint8_t inputStream[]);
png_parse_info_t hal_png_getparsedinfo(void);
jpeg_parse_err_t hal_jpeg_parse(uint8_t buf[], uint32_t len, jfif_info_t *jfif_info);

void hal_jpeg_init(uint8_t irq_en);
void hal_jpeg_decode_set(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset);

void hal_png_init(uint8_t irq_en);
png_config_err_t hal_png_decode_set(png_parse_info_t m_parsed_info, png_param_cfg_t m_param_cfg);

void hal_imagedecoder_start(void);
status_t hal_get_imagedecoder_status(void);
status_t hal_imagedecoder_clr_status(void);
void hal_image_irq_handler(void);

void hal_jpeg_accelerate_set(jfif_info_t *jfif_info, jpeg_outset_t *jpeg_outset);
void hal_jpeg_accelerate_start(void);
void hal_jpeg_accelerate_reset(void);

#ifdef __cplusplus
}
#endif

#endif