/**
 * @file chipconfig.h
 * @author Product application department
 * @brief  芯片封装配置头文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __CHIP_CONFIG_H
#define __CHIP_CONFIG_H

    // <<< Use Configuration Wizard in Context Menu >>>

/**
 *  该文件存放启动引导相关的参数信息，用户根据不同的封装选择修改对应的参数即可
 *
 **/
 

//QFN68_D      合封4MPSRAM, 不合封flash，主频不支持500M
//QFN68_B      合封16MPSAM, 合封2M flash，主频支持500M
//QFN88_A      合封32MPSAM, 合封2M flash，主频支持480M
//QFN88_B     合封16MPSAM, 不合封 flash，主频支持480M
 
//SSI_SSI1_NORFLASH   //使用内部合封SSI1 flash启动
//SSI_SSI3_NORFLASH   //使用外部SSI3 flash启动
//SSI_SSI3_NANDFLASH  //使用外部SSI3 nand flash 加载到psram启动


// <h> CCM4211 Chip Pakeage
// <o>Set CCM4211_CHIP_PACKAGE
//  <00000000UL=> QFN68_D  
//  <00000001UL=> QFN68_B
//  <00000002UL=> QFN88_A
//  <00000003UL=> QFN88_B

#define CCM4211_CHIP_PACKAGE 1U

// </h>


// <h> CCM4211 START MODE
// <o>Set CCM4211_START_MODE
//  <00000000UL=> SSI_SSI1_NORFLASH   
//  <00000001UL=> SSI_SSI3_NORFLASH   
//  <00000002UL=> SSI_SSI3_NANDFLASH  

#define CM4211_START_MODE 1U

// </h>


// <h> CCM4211 FATFS MODE
// <o>Set  CCM4211 FATFS_MODE
//  <00000000UL=> SD MODE
//  <00000001UL=> NORFLASH_MODE 
//  <00000002UL=> NANDFLASH_MODE
//  <00000003UL=> UDISK_MODE

#define CM4211_FAFTS_MODE 1U

// </h>

#if(CCM4211_CHIP_PACKAGE == 0)
#define PSRAM_START_ADDR    0x1C000000
#define PSRAM_LENGTH        0x800000
#elif(CCM4211_CHIP_PACKAGE == 1)
#define PSRAM_START_ADDR    0x1C000000
#define PSRAM_LENGTH        0x1000000
#elif(CCM4211_CHIP_PACKAGE == 2)
#define PSRAM_START_ADDR    0x1C000000
#define PSRAM_LENGTH        0x2000000
#elif(CCM4211_CHIP_PACKAGE == 3)
#define PSRAM_START_ADDR    0x1C000000
#define PSRAM_LENGTH        0x1000000
#endif

// <h> PSRAM_APP_USED_LENGTH
// <o> APP SIZE
#ifndef PSRAM_APP_USED_LENGTH
#define PSRAM_APP_USED_LENGTH       0x200000 //客户应用大小，根据实际使用的大小手动更改
#endif
 // </h>
	
#if(CM4211_START_MODE == 0)
#define START_CONFIG_ADDR           0x10000000 //FLASH 基地址，根据 SSI_ID 变更
#define START_USER_ADDR             (START_CONFIG_ADDR + 0x1000)
#define SSI_ID SSIID1
#define SSI_LENGTH                  0x200000

#define PSRAM_REMAIN_START_ADDR     (PSRAM_START_ADDR )
#define PSRAM_APP_REMAIN_LENGTH     (PSRAM_LENGTH )
#elif(CM4211_START_MODE == 1)
#define START_CONFIG_ADDR           0x14000000 //FLASH 基地址，根据 SSI_ID 变更 app -- 0x14066000  烧录 -- 0x14000000
#define START_USER_ADDR             (START_CONFIG_ADDR + 0x1000)
#define SSI_ID SSIID3
#define SSI_LENGTH                  0x1000000

#define PSRAM_REMAIN_START_ADDR     (PSRAM_START_ADDR)
#define PSRAM_APP_REMAIN_LENGTH     (PSRAM_LENGTH )
#elif(CM4211_START_MODE == 2)
#define START_CONFIG_ADDR           0x1C000000 //FLASH 基地址，根据 SSI_ID 变更
#define START_USER_ADDR             (START_CONFIG_ADDR + 0x1000)
#define SSI_ID SSIID3



#define SSI_LENGTH                  PSRAM_APP_USED_LENGTH
#define PSRAM_REMAIN_START_ADDR     (START_CONFIG_ADDR + PSRAM_APP_USED_LENGTH)
#define PSRAM_APP_REMAIN_LENGTH     (PSRAM_LENGTH - PSRAM_APP_USED_LENGTH)
#endif

#define START_DEFAULT_ADDR          0x14000000
#define FATFS_NORFLASH_ADDR         (START_DEFAULT_ADDR + 0x500000) //预留 flash 文件系统起始地址, 需要匹配下载的镜像文件
#define FATFS_NANDFLASH_ADDR        0x0000000

#endif
