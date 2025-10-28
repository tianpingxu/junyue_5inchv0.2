/**
 *  @file ssi_test.h
 *  @author Product application department
 *  @brief  SSI 模块测试用例头文件，仅供参考
 *  @version V1.0
 *  @date 2025-02-14
 *
 *  @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved.
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup SSI SSI模块
 * @ingroup Peripherals
 * @{
 */

#ifndef __SSI_TEST_H
#define __SSI_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

// 头文件包含
#include "ssi_hal.h"

// 全局变量定义
#define DATA_FIELDS_BEGIN_ADDR (0x14900000)
#define DATA_FIELDS_SIZE (0x100000)
#define DTAT_FIELDS_OFFSET_NUM (0x55)
#define DATA_FIELDS_END_ADDR (DATA_FIELDS_BEGIN_ADDR + DATA_FIELDS_SIZE)
#define DTAT_FIELDS_PAGE_NUM (0x1000)
#define DTAT_FIELDS_SECTOR_NUM (0x100)

// 函数声明
static void dummy_trng(uint32_t seed, uint8_t *psrc, uint32_t len);
void ssi_demo(void);

#ifdef __cplusplus
}
#endif

/** @} */  // 结束 SSI 模块分组
/** @} */  // 结束外设模块分组

#endif
