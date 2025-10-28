/**
 * @file image_decoder_data.h
 * @author Product Application Department
 * @brief  image decoder 模块测试数据头文件文件
 * @version V1.0
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

#ifndef __IMAGE_DECODER_DATA_H
#define __IMAGE_DECODER_DATA_H

// 头文件包含
#include "type.h"
#include "iomacros.h"
// JPEG
#define JPEG_1024600_1 0
#define JPEG_1024600_2 1
// PNG
#define PNG_480272_01 0
#define PNG_1024600_01 1

extern const uint8_t png_image[];
extern uint32_t png_image_len;

extern const uint8_t jpeg_image[];
extern uint32_t jpeg_image_len;

#endif

