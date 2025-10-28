/**
 * @file crc_reg.h
 * @author Product application department
 * @brief  CRC 模块寄存器配置文件
 * @version  V1.0
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
#ifndef __CRC_REG_H_
#define __CRC_REG_H_

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "type.h"

// 全局变量定义
#define CRC1_BASE_ADDR      (0x40044000)       
#define CRC2_BASE_ADDR      (0x40045000)        

#define CRC1 ((reg_crc_t *)CRC1_BASE_ADDR)
#define CRC2 ((reg_crc_t *)CRC2_BASE_ADDR)
#define CRC_MODE_CRC_32                 ((uint32_t)4)                  
#define CRC_MODE_CRC_16                 ((uint32_t)2)                  
#define CRC_MODE_CRC_8                  ((uint32_t)1)                  
#define CRC_MODE_MASK                     ((uint32_t)0x1FFFFFFF)         
#define CRC_MODE_UPDATA                 (((uint32_t)1 << 28))          
#define CRC_MODE_SOURCE_SEL_DMAC_WRITE     (((uint32_t)1 << 27))            
#define CRC_MODE_BIG_ENDING             (((uint32_t)1 << 26))          
#define CRC_MODE_BYTE_SWAP                 (((uint32_t)1 << 25))          
#define CRC_EDMAC_SEL                     (((uint32_t)1 << 24))          
#define CRC_EDMAC_UPDATA                 (((uint32_t)1 << 20))          
#define CRC_EDMAC_CRCLAT                 (((uint32_t)1 << 19))          
#define CRC_DECODE                         (((uint32_t)1 << 18))          
#define CRC_SEND_CRC_CODE_EN             (((uint32_t)1 << 17))          
#define CRC_WRITE_CRC_CODE_EN             (((uint32_t)1 << 16))          
#define CRC_EDMAC_SEND_CODE_BS             (((uint32_t)1 << 9))           
#define CRC_EDMAC_DEC_CODE_BS             (((uint32_t)1 << 8))           
#define CRC_CRCLAT_ERR                     (((uint32_t)1 << 1))           
#define CRC_OK                             (((uint32_t)1 << 0))           


/**
* @brief  CRC 模块寄存器定义
*/
typedef struct
{
    __IO uint32_t CR;                 
    __IO uint32_t RES;                
    __IO uint32_t INIT_DATA;          
    __IO uint32_t DATA_IN;            
    __IO uint32_t DMAC_DATA_IN;       
    __IO uint32_t EDMAC_CRC_OK;       
    __IO uint32_t EDMAC_CRC_FIRST_ERR;
    __IO uint32_t EDMAC_CRC_COUNT;    
} reg_crc_t;

#ifdef __cplusplus
}
#endif

#endif
