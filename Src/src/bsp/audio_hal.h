/**
 * @file audio_hal.h
 * @author Product application department
 * @brief AUDIO 模块硬件抽象层头文件
 * @version v1.0
 * @date 2025-02-17
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

#ifndef _AUDIO_HAL_H_
#define _AUDIO_HAL_H_

#ifdef __cplusplus
extern "C"
{
#endif
    
// 头文件包含
#include "type.h"
#include "delay.h"
    
// 全局变量定义
#define TEST_AUDIO_NUMBER 0xFF
#define ENTER_CRITICAL() __disable_irq()
#define EXIT_CRITICAL() __enable_irq()

/**
 * @brief AUDIO 状态枚举定义
 * 
 */
typedef enum
{
    _ERROR = 0,
    _SUCCESS = 1,
    COMMUNICATIOM_FAIL = 2
} errorstatus;

// 函数声明
void hal_audioisrhandler(void);
void hal_audiodecode(uint8_t *dst, uint8_t *src, uint32_t *length);
uint32_t hal_audioflashaddr(uint16_t playNumber, uint32_t *length);
void hal_audioreadbytes(uint8_t *dst, uint32_t length, uint32_t addr);
void hal_audiodrvinit(void);
void hal_audioinit(void);
void hal_audiosetvolume(uint8_t volume);
uint8_t hal_audiogetcurvolume(void);
uint8_t hal_audiogetmaxvolume(void);
void hal_audiodrvstop(void);
void hal_audiodrvconfig(uint32_t addr, uint32_t length);
void hal_audiosetplaynumber(uint16_t playNumber);
void hal_audiodrvhandle(void);
errorstatus hal_audioplay(void);
void hal_audiostop(void);
BOOL hal_audiobusystatus(void);
errorstatus hal_audiogetstatus(void);

#ifdef __cplusplus
}
#endif

#endif
