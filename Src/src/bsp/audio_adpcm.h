/**
 * @file audio_adpcm.h
 * @author Product application department
 * @brief adpcm 压缩解压驱动头文件
 * @version V1.0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif
#ifndef _AUDIO_ADPCM_H_
#define _AUDIO_ADPCM_H_

// 头文件包含
#include "type.h"

// 函数声明
void audiodecodeinit(void);
int16_t audiodecodeproc(uint8_t code);
int16_t audioencodeproc(uint32_t code);

#ifdef __cplusplus
}
#endif

#endif
