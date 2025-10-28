/**
 * @file iap_ex_flash.h
 * @author Product application department
 * @brief  flash ���������������ο�
 * @version V1.0
 * @date 2025-06-24
 * 
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 * 
 */

#ifndef __IAP_EX_FLASH_H_
#define __IAP_EX_FLASH_H_

/**
 * @defgroup ThirdPart ������ģ��
 * @{
 *
 * @defgroup FLASH FLASHģ��
 * @ingroup ThirdPart
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif
//ͷ�ļ�����
#include "type.h"
#include "diskio.h"
#include "ff.h"

//ȫ�ֱ�������
#define CCM_START_BASE              (0x14000000)
#define CCM_SECTOR_SIZE             (4*1024)
#define CCM_BOOT_SIZE               (30)
#define CCM_FLASH_SIZE              (481)
#define CCM_FLASH_BASE             (CCM_START_BASE + CCM_SECTOR_SIZE)// 

#define CCM_BOOT_BASE               CCM_FLASH_BASE
#define CCM_BOOT_INFO_BASE          (CCM_BOOT_BASE + CCM_BOOT_SIZE *CCM_SECTOR_SIZE)  // ������ 124 KB֮�������  4KB ���ڴ洢 info ���� 

#define CCM_APP_BASE                (CCM_BOOT_INFO_BASE + CCM_SECTOR_SIZE)       // 128kB ��ʼ APP ����


#define CCM_BOOT_MAX_SIZE           (120 *1024U)        // Boot ���������
#define CCM_APP_MAX_SIZE            ((2 *1024 *1024U)-(CCM_APP_BASE - CCM_START_BASE))
//#define CCM_IMAGE_MAX_SIZE          (1 *1024 *1024U)
#define CCM_POS_ADDR                CCM_START_BASE

#define ReadSize                    (512)

//��������
int8_t flashfile_write(FIL* TempFile ,uint32_t BaseAddr,void *ptr);

#ifdef __cplusplus
 }
 
#endif

#endif 
/** @} */  // ���� FLASH ģ�����
/** @} */  // ��������ģ�����