/**
 * @file libpsram.h
 * @author Product application department
 * @brief PSRAM 模块库头文件
 * @version V1.0
 * @date 2025-02-13
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */
#ifndef __LIBPSRAM_H
#define __LIBPSRAM_H
#ifdef __cplusplus
extern "C"
{
}
#endif
// 头文件包含
#include "type.h"
#include "iomacros.h"
// 结构体定义
typedef enum
{
    PSRAM_TYPE_256 = 0,
    PSRAM_TYPE_128,
    PSRAM_TYPE_3208X2,
    PSRAM_TYPE_3208,
} psram_type_t;

typedef enum
{
    PSRAM_DRIV_0 = 0X00,//3208:400ohm; 128:250ohm; 
    PSRAM_DRIV_1 = 0X01,//50ohm
    PSRAM_DRIV_2 = 0X02,//100ohm
    PSRAM_DRIV_3 = 0X03,//200ohm
} psram_drive_strength_t;

// 函数声明
/**
 * @brief PSRAM初始化
 *
 * @param psram_type PSRAM型号
 * @param psram_clk PSRAM使用的时钟频率
 * @param drive_str PSRAM驱动能力
 */
void psram_int(psram_type_t psram_type, uint32_t psram_clk,psram_drive_strength_t drive_str);

#endif
