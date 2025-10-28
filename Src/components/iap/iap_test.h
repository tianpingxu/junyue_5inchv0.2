/**
 * @file iap_test.h
 * @author Product application department
 * @brief  iap 测试用例头文件，仅供参考
 * @version V1.0
 * @date 2025-06-24
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */
/**
 * @defgroup ThirdPart 第三方模块
 * @{
 *
 * @defgroup IAP IAP模块
 * @ingroup ThirdPart
 * @{
 */

#ifndef __IAP_TEST_H__
#define __IAP_TEST_H__
#ifdef __cplusplus
extern "C"
{
#endif 

// 头文件包含
#include <string.h>
#include <stdbool.h>
#include "type.h"

//全局变量定义

#define BootVersion         "Version 0.1"
#define SD_PARA_COFIG 	    "3:Config.ini"     
#define APP_FILE            "3:app.bin"



typedef enum 
{
    APP_UPDATE_MODE  = 0,
    APP_NORMAL_MODE
}BootMode;

typedef struct 
{
 uint32_t AppCrcValue;      // APP 区域段的CRC 值
 uint32_t ImgCrcValue;      // 图片区的CRC值
 uint32_t ParamCrcValue;   // 参数结构体的 CRC值
}DataInfo;

typedef struct 
{
    uint8_t UpdateBoot;     //Boot 升级标志
    uint8_t UpdateApp;      //APP 升级标志
    uint8_t UpdateImg;      //图片升级标志
    uint8_t CheckAppCrc;    //固件校验标志 调试使用
    uint8_t CheckImgCrc;    //图库校验标志 调试使用
    uint8_t CheckBootCrc;    //图库校验标志 调试使用
    uint8_t DebugPrint;     //打印标志   调试使用
}ConfigParam;

typedef enum
{
    BootArea = 0,
    AppArea ,
    ImgArea ,
}UpdateArea;

//函数声明
BootMode getstartmode(void);
 void bootjumpapp(uint32_t addr);
int8_t mount_fatfs();
int8_t readparam(ConfigParam * config);
int8_t updateappfirmware(ConfigParam * config, UpdateArea area);
void iap_demo(void);
#ifdef __cplusplus
}
#endif

#endif 

/** @} */  // 结束 IAP 模块分组
/** @} */  // 结束外设模块分组

