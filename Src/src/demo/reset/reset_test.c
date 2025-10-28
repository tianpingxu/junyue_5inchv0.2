/**
 * @file reset_test.c
 * @author Product application department
 * @brief  RESET 模块测试用例，仅供参考
 * @version V1.0
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

/**
 * @defgroup Peripherals 外设模块
 * @{
 *
 * @defgroup RESET RESET模块
 * @ingroup Peripherals
 * @{
 */

// 头文件包含
#include "reset_test.h"

// 函数定义
/**
 * @brief RESET 模块测试示例函数
 * @param
 */
void reset_demo(void)
{
    reset_status_t status;

    hal_reset_getstatus(&status);

    if (HAL_RESET_POR == status)
    {
        printf("POR reset\n");
    }

    if (HAL_RESET_WDT == status)
    {
        printf("Watch dog timer reset\n");
    }

    if (HAL_RESET_SOFT == status)
    {
        printf("Soft reset\n");
    }

    if (HAL_RESET_TC == status)
    {
        printf("TC reset\n");
    }

    delay(0xffffff);
    hal_reset_softreset();
}

/** @} */  // 结束 RESET 模块分组
/** @} */  // 结束外设模块分组
